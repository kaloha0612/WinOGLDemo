#include "pch.h"
#include "AdminControl.h"
#include <math.h>

CAdminControl::CAdminControl()
{

}

CAdminControl::~CAdminControl()
{
    cshape_head->FreeCShape();
}
//描画する関数
void CAdminControl::Draw()
{
    CShape* nowS = cshape_head;

    while(nowS != NULL)
    {
        glColor3f(1.0, 1.0, 1.0);
        glPointSize(10);
        glBegin(GL_POINTS);

        Vertex* nowV = nowS->GetV();

        while (nowV != NULL)
        {
            glVertex2f(nowV->GetX(), nowV->GetY());

            nowV = nowV->GetNext();
        }

        glEnd();
        glColor3f(1.0, 1.0, 1.0);
        glPointSize(10);
        glBegin(GL_LINE_STRIP);

        nowV = nowS->GetV();

        while (nowV != NULL)
        {
            glVertex2f(nowV->GetX(), nowV->GetY());

            nowV = nowV->GetNext();
        }
        glEnd();
        nowS = nowS->GetNextS();

    }


    
}

//新しいリストを先頭に挟みこむ関数
void CAdminControl::AppendCShape()
{
    CShape* newCShape = new CShape();
    newCShape->SetNextS(cshape_head);
    cshape_head = newCShape;
}

//2点間の距離を求め返却する関数
float CAdminControl::Distance(Vertex* start, float x, float y)
{
    float d;
    float X, Y;

    X = x - start->GetX();
    Y = y - start->GetY();

    d = sqrt(pow(X,2)+pow(Y,2));

    return d;
}

int CAdminControl::StraightAngle(CShape* startS, Vertex* startV, float x, float y)
{
    Vertex* a;
    Vertex* b;
    Vertex* Q = new Vertex(x,y);
    float angle = 0;
    float sumresult = 0;//角の総和

    //角の総和を求めるため
    //すでに完成している図形をループ
    for (CShape* sp = startS->GetNextS(); sp != NULL; sp = sp->GetNextS()) {
        for (Vertex* vp = sp->GetV(); vp->GetNext() != NULL; vp = vp->GetNext()) {

            a = bekutorukun(Q, vp);
            b = bekutorukun(Q, vp->GetNext());
            
            angle = kakudokun(a,b);
            sumresult = sumresult + angle;//総和に加算
        }
    }
    if (sumresult < 0.001 && sumresult > -0.001) {//内包してなければ
        return 0;
    }
    else {//内包してれば
        return 1;
    }
}

int CAdminControl::StraightAngleEX(CShape* startS, Vertex* startV, float x, float y)
{
    Vertex* a;
    Vertex* b;
    Vertex* Q;
    Vertex* now = startV;
    Vertex* now0 = NULL;
    float angle = 0;
    float sumresult = 0;//角の総和
    int count = 0;
    int result = 0;

    //角の総和を求めるため
    //完成してる図形をループ
    for (CShape* sp = startS->GetNextS(); sp != NULL; sp = sp->GetNextS()) {
        count = 0;
        //図形内の点をループ
        for (Vertex* vp = sp->GetV(); vp != NULL; vp = vp->GetNext()) {
            sumresult = 0;
            Q = new Vertex(vp->GetX(), vp->GetY());//1点決める
            //cshape_headの点をループ
            for (Vertex* svp = startS->GetV(); svp->GetNext() != NULL; svp = svp->GetNext()) {

                a = bekutorukun(Q, svp);
                b = bekutorukun(Q, svp->GetNext());
                now0 = svp->GetNext();

                angle = kakudokun(a, b);
                sumresult = sumresult + angle;//総和に加算
            }
            a = bekutorukun(Q, now0);
            b = bekutorukun(Q, now);

            angle = kakudokun(a, b);
            sumresult = sumresult + angle;//総和に加算
            if (sumresult > 0.001 || sumresult < -0.001) {//内包してたら
                count++;
            }
        }
        if (count == sp->CountVertex()) {
            result = 1;
            break;
        }
    }

    return result;
}

int CAdminControl::StraightCross(CShape* startS, Vertex* startV, float x, float y)
{
    int result = 0;
    Vertex* nowV = startV;
    Vertex* s1;
    Vertex* s2;
    Vertex* g1;
    Vertex* g2 = new Vertex(x,y);
    float G1;
    float G2;
    float G3;
    float G4;

        //最後尾まで送り打ちたい点の1つ前をg1に保存
        while (nowV->GetNext() != NULL)
        {
            nowV = nowV->GetNext();
        }
        g1 = nowV;

        //cshape_headのリスト(現在描いている図形)内の自交差判定
        for (Vertex* vp = startV; vp->GetNext()->GetNext() != NULL; vp = vp->GetNext()) {
            s1 = vp;
            s2 = vp->GetNext();

            G1 = gaisekikun(bekutorukun(s1, s2), bekutorukun(s1, g1));
            G2 = gaisekikun(bekutorukun(s1, s2), bekutorukun(s1, g2));
            G3 = gaisekikun(bekutorukun(g1, g2), bekutorukun(g1, s1));
            G4 = gaisekikun(bekutorukun(g1, g2), bekutorukun(g1, s2));

            if (G1 * G2 <= 0 && G3 * G4 <= 0) {
                result = 1;
            }
        }

        //すでに完成している図形との他交差判定
        for (CShape* sp = startS->GetNextS(); sp != NULL; sp = sp->GetNextS()) {

            for (Vertex* vp = sp->GetV(); vp->GetNext() != NULL; vp = vp->GetNext()) {
                s1 = vp;
                s2 = vp->GetNext();

                G1 = gaisekikun(bekutorukun(s1, s2), bekutorukun(s1, g1));
                G2 = gaisekikun(bekutorukun(s1, s2), bekutorukun(s1, g2));
                G3 = gaisekikun(bekutorukun(g1, g2), bekutorukun(g1, s1));
                G4 = gaisekikun(bekutorukun(g1, g2), bekutorukun(g1, s2));

                if (G1 * G2 <= 0 && G3 * G4 <= 0) {
                    result = 1;
                }
            }
        }

        
    return result;
}

int CAdminControl::StraightCross2(CShape* startS, Vertex* startV, float x, float y)
{
    int result = 0;
    Vertex* nowV = startV;
    Vertex* s1;//判定対称の線分の始点
    Vertex* s2;//判定対称の線分の終点
    Vertex* g1;//交差判定したい線分の始点
    Vertex* g2 = new Vertex(x, y);//交差判定したい線分の終点
    float G1;//↓外積１〜４
    float G2;
    float G3;
    float G4;

    //最後尾の点まで送り保存(打ちたい点の1つ前をg1に保存)
    while (nowV->GetNext() != NULL)
    {
        nowV = nowV->GetNext();
    }
    g1 = nowV;

    //すでに完成している図形との交差判定
    for (CShape* sp = startS->GetNextS(); sp != NULL; sp = sp->GetNextS()) {

        for (Vertex* vp = sp->GetV(); vp->GetNext() != NULL; vp = vp->GetNext()) {
            s1 = vp;
            s2 = vp->GetNext();

            G1 = gaisekikun(bekutorukun(s1, s2), bekutorukun(s1, g1));
            G2 = gaisekikun(bekutorukun(s1, s2), bekutorukun(s1, g2));
            G3 = gaisekikun(bekutorukun(g1, g2), bekutorukun(g1, s1));
            G4 = gaisekikun(bekutorukun(g1, g2), bekutorukun(g1, s2));

            if (G1 * G2 <= 0 && G3 * G4 <= 0) {
                result = 1;
            }
        }
    }


    return result;
}

/*別の方法での交差判定(途中)
int CAdminControl::LineCross(Vertex* start, float x, float y)
{
    int result = 0;
    Vertex* nowV = start;
    Vertex* s1;
    Vertex* s2;
    Vertex* g1;
    Vertex* g2 = new Vertex(x, y);
    float G1;
    float G2;
    float G3;
    float G4;



    //最後尾まで送る
    while (nowV->GetNext() != NULL)
    {
        nowV = nowV->GetNext();
    }
    g1 = nowV;

    for (Vertex* vp = start; vp->GetNext() != NULL; vp = vp->GetNext()) {
        s1 = vp;
        s2 = vp->GetNext();

        if (bundankun(s1, s2, g1, g2) == 1 && bundankun(s1, s2, g1, g2) == 1) {
            result = 1;
        }
    }

    return result;
}*/

Vertex* CAdminControl::bekutorukun(Vertex* a, Vertex* b)
{
    Vertex* result = new Vertex(b->GetX() - a->GetX(), b->GetY() - a->GetY());

    return result;
}

float CAdminControl::gaisekikun(Vertex* a, Vertex* b)
{
    float result;

    result = (a->GetX() * b->GetY()) - (a->GetY() * b->GetX());

    return result;
}

float CAdminControl::naisekikun(Vertex* a, Vertex* b)
{
    float result;

    result = (a->GetX() * b->GetX()) + (a->GetY() * b->GetY());

    return result;
}

float CAdminControl::kakudokun(Vertex* a, Vertex* b)
{
    float result;
    float y = gaisekikun(a,b);
    float x = naisekikun(a,b);

    /*if (y < 0) {
        y = y * -1;
    }*/
    result = atan2(y,x);
    
    return result;
}

int CAdminControl::bundankun(Vertex* a, Vertex* b, Vertex* c, Vertex* d)
{
    int result = 0;
    float s;
    float t;

    s = (b->GetX() - a->GetX()) * (c->GetY() - a->GetY()) - (c->GetX() - a->GetX()) * (b->GetY() - a->GetY());
    t = (b->GetX() - a->GetX()) * (d->GetY() - a->GetY()) - (d->GetX() - a->GetX()) * (b->GetY() - a->GetY());

    if (s * t < 0) {
        result = 1;
    }

    return result;
}

void CAdminControl::CreateShape(float x, float y)
{
    //点が何もないとき(1点目)
    if (cshape_head == NULL) {
        AppendCShape();
    }
    
    //図形が1つ目の時
    if (cshape_head->GetNextS() == NULL) {
        //3点打つまでは追加
        if (cshape_head->CountVertex() < 3) {
            cshape_head->AppendVertex(x, y);
        }
        //4点目以降の時閉じるか判定
        else if (Distance(cshape_head->GetV(), x, y) <= 0.1) {
            //自交差(始点つなげたときの)してたら
            if (StraightCross(cshape_head, cshape_head->GetV()->GetNext(), cshape_head->GetV()->GetX(), cshape_head->GetV()->GetY()) == 1) {
                //自交差してなければ打つ
                if (StraightCross(cshape_head, cshape_head->GetV(), x, y) != 1) {
                    cshape_head->AppendVertex(x, y);
                }
            }//自交差(始点つなげたときの)してなければ閉じる
            else {
                cshape_head->AppendVertex(cshape_head->GetV()->GetX(), cshape_head->GetV()->GetY());
                AppendCShape();
            }
        }//交差判定
        else if (StraightCross(cshape_head, cshape_head->GetV(), x, y) == 1) {
            //なにもしない
        }//閉じてなくて交差してなければそのまま追加
        else {
            cshape_head->AppendVertex(x, y);
        }
    }
    //図形が2つ目以降の時
    //打つ点が内包しているかどうか
    else if (StraightAngle(cshape_head, cshape_head->GetV(), x, y) == 1) {
        //内包してればなにもしない
    }//1点目は
    else if (cshape_head->CountVertex() < 1) {
        cshape_head->AppendVertex(x, y);
    }
    //3点目までは
    else if (cshape_head->CountVertex() < 3) {
        //交差判定(特殊)
        if (StraightCross2(cshape_head, cshape_head->GetV(), x, y) == 1) {
            //交差してたらなにもしない
        }//閉じてなくて交差してなければそのまま追加
        else {
            cshape_head->AppendVertex(x, y);
        }
    }
    //4点目以降の時閉じるか判定
    else if (Distance(cshape_head->GetV(), x, y) <= 0.1) {
        //自交差(始点つなげたときの)してたら
        if (StraightCross(cshape_head, cshape_head->GetV()->GetNext(), cshape_head->GetV()->GetX(), cshape_head->GetV()->GetY()) == 1) {
            //自交差してなければ打つ
            if (StraightCross(cshape_head, cshape_head->GetV(), x, y) != 1) {
                cshape_head->AppendVertex(x, y);
            }
        }//自交差(始点つなげたときの)してなくて図形を内包してなければ
        else if (StraightAngleEX(cshape_head, cshape_head->GetV(), x, y) != 1) {
            cshape_head->AppendVertex(cshape_head->GetV()->GetX(), cshape_head->GetV()->GetY());
            AppendCShape();
        }
    }//交差判定
    else if (StraightCross(cshape_head, cshape_head->GetV(), x, y) == 1) {
        //なにもしない
    }//閉じてなくて交差してなければそのまま追加
    else {
        cshape_head->AppendVertex(x, y);
    }
}


