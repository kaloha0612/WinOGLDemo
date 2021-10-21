#pragma once
#include <Windows.h>
#include "Vertex.h"

class CShape
{
public:
	CShape();
	CShape(Vertex* new_v);
	~CShape();



	//�@���_��X�EY���W�̗�������������
	void SetV(Vertex* v);

	Vertex* GetV();

	//�@���̒��_���X�g���w���|�C���^��ǂݍ���
	CShape* GetNextS();

	//�@���̒��_���X�g���w���|�C���^����������
	CShape* SetNextS(CShape* new_nextS);

	void FreeCShape();

	Vertex* AppendVertex(float x, float y);
	int CountVertex();

private:
	//�@���̒��_���X�g���w���|�C���^
	Vertex* vertex_head = NULL;
	CShape* next_cshape = NULL;
};

