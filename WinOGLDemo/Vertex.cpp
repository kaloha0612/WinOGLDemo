#include "pch.h"
#include "Vertex.h"

Vertex::Vertex()
{
	x = 0;
	y = 0;
	next_vertex = NULL;
}

Vertex::Vertex(float new_x, float new_y)
{
	SetXY(new_x, new_y);
	next_vertex = NULL;
	//SetNext(new_next);
}

Vertex::~Vertex()
{

}


//�@���_��X�EY���W�̗�������������
void Vertex::SetXY(float new_x, float new_y)
{
	
		x = new_x;
		y = new_y;
}

//�@���_��X���W��ǂݍ��ލ���
float Vertex::GetX()
{
	return x;
}

//�@���_��Y���W��ǂݍ���
float Vertex::GetY()
{
	return y;
}


//�@���̒��_���X�g���w���|�C���^����������
Vertex* Vertex::SetNext(Vertex* new_next)
{
	return next_vertex = new_next;
}

//�@���̒��_���X�g���w���|�C���^��ǂݍ���
Vertex* Vertex::GetNext()
{
	return next_vertex;
}

void Vertex::FreeVertex()
{
	Vertex* nowV = this;
	while (nowV != NULL) {
		Vertex* del_cell = nowV;
		nowV = nowV->GetNext();
		delete del_cell;
	}
}
