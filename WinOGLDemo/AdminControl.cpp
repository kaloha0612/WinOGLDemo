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
//�`�悷��֐�
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

//�V�������X�g��擪�ɋ��݂��ފ֐�
void CAdminControl::AppendCShape()
{
    CShape* newCShape = new CShape();
    newCShape->SetNextS(cshape_head);
    cshape_head = newCShape;
}

//2�_�Ԃ̋��������ߕԋp����֐�
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
    float sumresult = 0;//�p�̑��a

    //�p�̑��a�����߂邽��
    //���łɊ������Ă���}�`�����[�v
    for (CShape* sp = startS->GetNextS(); sp != NULL; sp = sp->GetNextS()) {
        for (Vertex* vp = sp->GetV(); vp->GetNext() != NULL; vp = vp->GetNext()) {

            a = bekutorukun(Q, vp);
            b = bekutorukun(Q, vp->GetNext());
            
            angle = kakudokun(a,b);
            sumresult = sumresult + angle;//���a�ɉ��Z
        }
    }
    if (sumresult < 0.001 && sumresult > -0.001) {//����ĂȂ����
        return 0;
    }
    else {//����Ă��
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
    float sumresult = 0;//�p�̑��a
    int count = 0;
    int result = 0;

    //�p�̑��a�����߂邽��
    //�������Ă�}�`�����[�v
    for (CShape* sp = startS->GetNextS(); sp != NULL; sp = sp->GetNextS()) {
        count = 0;
        //�}�`���̓_�����[�v
        for (Vertex* vp = sp->GetV(); vp != NULL; vp = vp->GetNext()) {
            sumresult = 0;
            Q = new Vertex(vp->GetX(), vp->GetY());//1�_���߂�
            //cshape_head�̓_�����[�v
            for (Vertex* svp = startS->GetV(); svp->GetNext() != NULL; svp = svp->GetNext()) {

                a = bekutorukun(Q, svp);
                b = bekutorukun(Q, svp->GetNext());
                now0 = svp->GetNext();

                angle = kakudokun(a, b);
                sumresult = sumresult + angle;//���a�ɉ��Z
            }
            a = bekutorukun(Q, now0);
            b = bekutorukun(Q, now);

            angle = kakudokun(a, b);
            sumresult = sumresult + angle;//���a�ɉ��Z
            if (sumresult > 0.001 || sumresult < -0.001) {//����Ă���
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

        //�Ō���܂ő���ł������_��1�O��g1�ɕۑ�
        while (nowV->GetNext() != NULL)
        {
            nowV = nowV->GetNext();
        }
        g1 = nowV;

        //cshape_head�̃��X�g(���ݕ`���Ă���}�`)���̎���������
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

        //���łɊ������Ă���}�`�Ƃ̑���������
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
    Vertex* s1;//����Ώ̂̐����̎n�_
    Vertex* s2;//����Ώ̂̐����̏I�_
    Vertex* g1;//�������肵���������̎n�_
    Vertex* g2 = new Vertex(x, y);//�������肵���������̏I�_
    float G1;//���O�ςP�`�S
    float G2;
    float G3;
    float G4;

    //�Ō���̓_�܂ő���ۑ�(�ł������_��1�O��g1�ɕۑ�)
    while (nowV->GetNext() != NULL)
    {
        nowV = nowV->GetNext();
    }
    g1 = nowV;

    //���łɊ������Ă���}�`�Ƃ̌�������
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

/*�ʂ̕��@�ł̌�������(�r��)
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



    //�Ō���܂ő���
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
    //�_�������Ȃ��Ƃ�(1�_��)
    if (cshape_head == NULL) {
        AppendCShape();
    }
    
    //�}�`��1�ڂ̎�
    if (cshape_head->GetNextS() == NULL) {
        //3�_�ł܂ł͒ǉ�
        if (cshape_head->CountVertex() < 3) {
            cshape_head->AppendVertex(x, y);
        }
        //4�_�ڈȍ~�̎����邩����
        else if (Distance(cshape_head->GetV(), x, y) <= 0.1) {
            //������(�n�_�Ȃ����Ƃ���)���Ă���
            if (StraightCross(cshape_head, cshape_head->GetV()->GetNext(), cshape_head->GetV()->GetX(), cshape_head->GetV()->GetY()) == 1) {
                //���������ĂȂ���Αł�
                if (StraightCross(cshape_head, cshape_head->GetV(), x, y) != 1) {
                    cshape_head->AppendVertex(x, y);
                }
            }//������(�n�_�Ȃ����Ƃ���)���ĂȂ���Ε���
            else {
                cshape_head->AppendVertex(cshape_head->GetV()->GetX(), cshape_head->GetV()->GetY());
                AppendCShape();
            }
        }//��������
        else if (StraightCross(cshape_head, cshape_head->GetV(), x, y) == 1) {
            //�Ȃɂ����Ȃ�
        }//���ĂȂ��Č������ĂȂ���΂��̂܂ܒǉ�
        else {
            cshape_head->AppendVertex(x, y);
        }
    }
    //�}�`��2�ڈȍ~�̎�
    //�ł_������Ă��邩�ǂ���
    else if (StraightAngle(cshape_head, cshape_head->GetV(), x, y) == 1) {
        //����Ă�΂Ȃɂ����Ȃ�
    }//1�_�ڂ�
    else if (cshape_head->CountVertex() < 1) {
        cshape_head->AppendVertex(x, y);
    }
    //3�_�ڂ܂ł�
    else if (cshape_head->CountVertex() < 3) {
        //��������(����)
        if (StraightCross2(cshape_head, cshape_head->GetV(), x, y) == 1) {
            //�������Ă���Ȃɂ����Ȃ�
        }//���ĂȂ��Č������ĂȂ���΂��̂܂ܒǉ�
        else {
            cshape_head->AppendVertex(x, y);
        }
    }
    //4�_�ڈȍ~�̎����邩����
    else if (Distance(cshape_head->GetV(), x, y) <= 0.1) {
        //������(�n�_�Ȃ����Ƃ���)���Ă���
        if (StraightCross(cshape_head, cshape_head->GetV()->GetNext(), cshape_head->GetV()->GetX(), cshape_head->GetV()->GetY()) == 1) {
            //���������ĂȂ���Αł�
            if (StraightCross(cshape_head, cshape_head->GetV(), x, y) != 1) {
                cshape_head->AppendVertex(x, y);
            }
        }//������(�n�_�Ȃ����Ƃ���)���ĂȂ��Đ}�`�����ĂȂ����
        else if (StraightAngleEX(cshape_head, cshape_head->GetV(), x, y) != 1) {
            cshape_head->AppendVertex(cshape_head->GetV()->GetX(), cshape_head->GetV()->GetY());
            AppendCShape();
        }
    }//��������
    else if (StraightCross(cshape_head, cshape_head->GetV(), x, y) == 1) {
        //�Ȃɂ����Ȃ�
    }//���ĂȂ��Č������ĂȂ���΂��̂܂ܒǉ�
    else {
        cshape_head->AppendVertex(x, y);
    }
}


