#include "pch.h"
#include "AdminControl.h"

CAdminControl::CAdminControl()
{

}

CAdminControl::~CAdminControl()
{

}

void CAdminControl::Draw()
{
    float x = vertex_head->GetX();
    float y = vertex_head->GetY();
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5);

    glBegin(GL_POINTS);

    glVertex2f(x, y);
    glEnd();
    /*glColor3f(1.0, 1.0, 1.0);
    glPointSize(5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glEnd();*/
}

Vertex* CAdminControl::AppendVertex(float x, float y)
{
    Vertex* nowV = vertex_head;
    Vertex* newVertex = new Vertex(x, y);

    if (nowV != NULL)
    {
        while (nowV->GetNext() != NULL)
        {
            nowV = nowV->GetNext();
        }
        nowV->SetNext(newVertex);
    }
    else
        {
        vertex_head = newVertex;
        }

    return newVertex;
}
