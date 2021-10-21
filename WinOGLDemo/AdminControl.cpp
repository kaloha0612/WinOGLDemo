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
//•`‰æ‚·‚éŠÖ”
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

//V‚µ‚¢ƒŠƒXƒg‚ğæ“ª‚É‹²‚İ‚±‚ŞŠÖ”
void CAdminControl::AppendCShape()
{
    CShape* newCShape = new CShape();
    newCShape->SetNextS(cshape_head);
    cshape_head = newCShape;
}

//2“_ŠÔ‚Ì‹——£‚ğ‹‚ß•Ô‹p‚·‚éŠÖ”
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
    float sumresult = 0;//Šp‚Ì‘˜a

    //Šp‚Ì‘˜a‚ğ‹‚ß‚é‚½‚ß
    //‚·‚Å‚ÉŠ®¬‚µ‚Ä‚¢‚é}Œ`‚ğƒ‹[ƒv
    for (CShape* sp = startS->GetNextS(); sp != NULL; sp = sp->GetNextS()) {
        for (Vertex* vp = sp->GetV(); vp->GetNext() != NULL; vp = vp->GetNext()) {

            a = bekutorukun(Q, vp);
            b = bekutorukun(Q, vp->GetNext());
            
            angle = kakudokun(a,b);
            sumresult = sumresult + angle;//‘˜a‚É‰ÁZ
        }
    }
    if (sumresult < 0.001 && sumresult > -0.001) {//“à•ï‚µ‚Ä‚È‚¯‚ê‚Î
        return 0;
    }
    else {//“à•ï‚µ‚Ä‚ê‚Î
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
    float sumresult = 0;//Šp‚Ì‘˜a
    int count = 0;
    int result = 0;

    //Šp‚Ì‘˜a‚ğ‹‚ß‚é‚½‚ß
    //Š®¬‚µ‚Ä‚é}Œ`‚ğƒ‹[ƒv
    for (CShape* sp = startS->GetNextS(); sp != NULL; sp = sp->GetNextS()) {
        count = 0;
        //}Œ`“à‚Ì“_‚ğƒ‹[ƒv
        for (Vertex* vp = sp->GetV(); vp != NULL; vp = vp->GetNext()) {
            sumresult = 0;
            Q = new Vertex(vp->GetX(), vp->GetY());//1“_Œˆ‚ß‚é
            //cshape_head‚Ì“_‚ğƒ‹[ƒv
            for (Vertex* svp = startS->GetV(); svp->GetNext() != NULL; svp = svp->GetNext()) {

                a = bekutorukun(Q, svp);
                b = bekutorukun(Q, svp->GetNext());
                now0 = svp->GetNext();

                angle = kakudokun(a, b);
                sumresult = sumresult + angle;//‘˜a‚É‰ÁZ
            }
            a = bekutorukun(Q, now0);
            b = bekutorukun(Q, now);

            angle = kakudokun(a, b);
            sumresult = sumresult + angle;//‘˜a‚É‰ÁZ
            if (sumresult > 0.001 || sumresult < -0.001) {//“à•ï‚µ‚Ä‚½‚ç
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

        //ÅŒã”ö‚Ü‚Å‘—‚è‘Å‚¿‚½‚¢“_‚Ì1‚Â‘O‚ğg1‚É•Û‘¶
        while (nowV->GetNext() != NULL)
        {
            nowV = nowV->GetNext();
        }
        g1 = nowV;

        //cshape_head‚ÌƒŠƒXƒg(Œ»İ•`‚¢‚Ä‚¢‚é}Œ`)“à‚Ì©Œğ·”»’è
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

        //‚·‚Å‚ÉŠ®¬‚µ‚Ä‚¢‚é}Œ`‚Æ‚Ì‘¼Œğ·”»’è
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
    Vertex* s1;//”»’è‘ÎÌ‚Ìü•ª‚Ìn“_
    Vertex* s2;//”»’è‘ÎÌ‚Ìü•ª‚ÌI“_
    Vertex* g1;//Œğ·”»’è‚µ‚½‚¢ü•ª‚Ìn“_
    Vertex* g2 = new Vertex(x, y);//Œğ·”»’è‚µ‚½‚¢ü•ª‚ÌI“_
    float G1;//«ŠOÏ‚P`‚S
    float G2;
    float G3;
    float G4;

    //ÅŒã”ö‚Ì“_‚Ü‚Å‘—‚è•Û‘¶(‘Å‚¿‚½‚¢“_‚Ì1‚Â‘O‚ğg1‚É•Û‘¶)
    while (nowV->GetNext() != NULL)
    {
        nowV = nowV->GetNext();
    }
    g1 = nowV;

    //‚·‚Å‚ÉŠ®¬‚µ‚Ä‚¢‚é}Œ`‚Æ‚ÌŒğ·”»’è
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

/*•Ê‚Ì•û–@‚Å‚ÌŒğ·”»’è(“r’†)
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



    //ÅŒã”ö‚Ü‚Å‘—‚é
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
    //“_‚ª‰½‚à‚È‚¢‚Æ‚«(1“_–Ú)
    if (cshape_head == NULL) {
        AppendCShape();
    }
    
    //}Œ`‚ª1‚Â–Ú‚Ì
    if (cshape_head->GetNextS() == NULL) {
        //3“_‘Å‚Â‚Ü‚Å‚Í’Ç‰Á
        if (cshape_head->CountVertex() < 3) {
            cshape_head->AppendVertex(x, y);
        }
        //4“_–ÚˆÈ~‚Ì•Â‚¶‚é‚©”»’è
        else if (Distance(cshape_head->GetV(), x, y) <= 0.1) {
            //©Œğ·(n“_‚Â‚È‚°‚½‚Æ‚«‚Ì)‚µ‚Ä‚½‚ç
            if (StraightCross(cshape_head, cshape_head->GetV()->GetNext(), cshape_head->GetV()->GetX(), cshape_head->GetV()->GetY()) == 1) {
                //©Œğ·‚µ‚Ä‚È‚¯‚ê‚Î‘Å‚Â
                if (StraightCross(cshape_head, cshape_head->GetV(), x, y) != 1) {
                    cshape_head->AppendVertex(x, y);
                }
            }//©Œğ·(n“_‚Â‚È‚°‚½‚Æ‚«‚Ì)‚µ‚Ä‚È‚¯‚ê‚Î•Â‚¶‚é
            else {
                cshape_head->AppendVertex(cshape_head->GetV()->GetX(), cshape_head->GetV()->GetY());
                AppendCShape();
            }
        }//Œğ·”»’è
        else if (StraightCross(cshape_head, cshape_head->GetV(), x, y) == 1) {
            //‚È‚É‚à‚µ‚È‚¢
        }//•Â‚¶‚Ä‚È‚­‚ÄŒğ·‚µ‚Ä‚È‚¯‚ê‚Î‚»‚Ì‚Ü‚Ü’Ç‰Á
        else {
            cshape_head->AppendVertex(x, y);
        }
    }
    //}Œ`‚ª2‚Â–ÚˆÈ~‚Ì
    //‘Å‚Â“_‚ª“à•ï‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©
    else if (StraightAngle(cshape_head, cshape_head->GetV(), x, y) == 1) {
        //“à•ï‚µ‚Ä‚ê‚Î‚È‚É‚à‚µ‚È‚¢
    }//1“_–Ú‚Í
    else if (cshape_head->CountVertex() < 1) {
        cshape_head->AppendVertex(x, y);
    }
    //3“_–Ú‚Ü‚Å‚Í
    else if (cshape_head->CountVertex() < 3) {
        //Œğ·”»’è(“Áê)
        if (StraightCross2(cshape_head, cshape_head->GetV(), x, y) == 1) {
            //Œğ·‚µ‚Ä‚½‚ç‚È‚É‚à‚µ‚È‚¢
        }//•Â‚¶‚Ä‚È‚­‚ÄŒğ·‚µ‚Ä‚È‚¯‚ê‚Î‚»‚Ì‚Ü‚Ü’Ç‰Á
        else {
            cshape_head->AppendVertex(x, y);
        }
    }
    //4“_–ÚˆÈ~‚Ì•Â‚¶‚é‚©”»’è
    else if (Distance(cshape_head->GetV(), x, y) <= 0.1) {
        //©Œğ·(n“_‚Â‚È‚°‚½‚Æ‚«‚Ì)‚µ‚Ä‚½‚ç
        if (StraightCross(cshape_head, cshape_head->GetV()->GetNext(), cshape_head->GetV()->GetX(), cshape_head->GetV()->GetY()) == 1) {
            //©Œğ·‚µ‚Ä‚È‚¯‚ê‚Î‘Å‚Â
            if (StraightCross(cshape_head, cshape_head->GetV(), x, y) != 1) {
                cshape_head->AppendVertex(x, y);
            }
        }//©Œğ·(n“_‚Â‚È‚°‚½‚Æ‚«‚Ì)‚µ‚Ä‚È‚­‚Ä}Œ`‚ğ“à•ï‚µ‚Ä‚È‚¯‚ê‚Î
        else if (StraightAngleEX(cshape_head, cshape_head->GetV(), x, y) != 1) {
            cshape_head->AppendVertex(cshape_head->GetV()->GetX(), cshape_head->GetV()->GetY());
            AppendCShape();
        }
    }//Œğ·”»’è
    else if (StraightCross(cshape_head, cshape_head->GetV(), x, y) == 1) {
        //‚È‚É‚à‚µ‚È‚¢
    }//•Â‚¶‚Ä‚È‚­‚ÄŒğ·‚µ‚Ä‚È‚¯‚ê‚Î‚»‚Ì‚Ü‚Ü’Ç‰Á
    else {
        cshape_head->AppendVertex(x, y);
    }
}


