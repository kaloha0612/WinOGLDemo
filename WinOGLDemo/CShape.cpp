#include "pch.h"
#include "CShape.h"

CShape::CShape()
{
}

CShape::CShape(Vertex* new_v)
{
    vertex_head = new_v;
}

CShape::~CShape()
{
    vertex_head->FreeVertex();
}

void CShape::SetV(Vertex* v)
{
	vertex_head = v;
}

Vertex* CShape::GetV()
{
	return vertex_head;
}

CShape* CShape::GetNextS()
{
	return next_cshape;
}

CShape* CShape::SetNextS(CShape* new_nextS)
{
	return next_cshape = new_nextS;
}

void CShape::FreeCShape()
{

	CShape* nowS = this;
	while (nowS != NULL) {
		CShape* del_cell = nowS;
		nowS = nowS->GetNextS();
		delete del_cell;
	}
}

Vertex* CShape::AppendVertex(float x, float y)
{
    //�w�b�h��ǂݍ���
    Vertex* nowV = vertex_head;
    //�ł��ꂽ�_��ۑ�����
    Vertex* newVertex = new Vertex(x, y);

    //�w�b�h�������Ă����
    if (nowV != NULL)
    {
        //�Ō���܂ő���
        while (nowV->GetNext() != NULL)
        {
            nowV = nowV->GetNext();
        }
        //�Ō���̎��ɒǉ�����
        nowV->SetNext(newVertex);
    }
    else
    {
        //�ł��ꂽ�_���w�b�h�ɂ���
        vertex_head = newVertex;
    }

    return newVertex;
}

int CShape::CountVertex()
{
    int c = 0;

    for (Vertex* vp = vertex_head; vp != NULL; vp = vp->GetNext()) {
        c++;
    }

    return c;
}
