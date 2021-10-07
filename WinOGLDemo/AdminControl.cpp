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
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
}
