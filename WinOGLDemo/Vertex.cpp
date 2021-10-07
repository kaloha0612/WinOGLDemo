#include "Vertex.h"

Vertex::Vertex()
{
	x = 0;
	y = 0;
	next_vertex = NULL;
}

Vertex::Vertex(float x, float y)
{
	SetXY(x, y);
	//SetNext(new_next);
}

Vertex::~Vertex()
{

}


//�@���_��X�EY���W�̗�������������
void Vertex::SetXY(float x, float y)
{
	if (x < 0) {
		x = x * (-1);
	}
	x = x;
	if (y < 0) {
		y = y * (-1);
	}
	y = y;
}

//�@���_��X���W��ǂݍ��ލ���
int Vertex::GetX()
{
	return x;
}

//�@���_��Y���W��ǂݍ���
int Vertex::GetY()
{
	return y;
}


//�@���̒��_���X�g���w���|�C���^����������
void Vertex::SetNext(Vertex* vertex)
{
	next_vertex = vertex;
}

//�@���̒��_���X�g���w���|�C���^��ǂݍ���
Vertex* Vertex::GetNext()
{
	return next_vertex;
}
