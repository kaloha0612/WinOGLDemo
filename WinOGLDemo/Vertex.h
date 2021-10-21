#pragma once
#include <stdio.h> 
#include "pch.h"

class Vertex
{
public:
	Vertex();
	Vertex(float new_x, float new_y);
	~Vertex();
private:
	//�@���_��X���W
	float x;
	//�@���_��Y���W
	float y;
	//�@���̒��_���X�g���w���|�C���^
	Vertex* pre_vertex = NULL;
	Vertex* next_vertex = NULL;
public:
	//�@���_��X�EY���W�̗�������������
	void SetXY(float new_x, float new_y);

	//�@���_��X���W��ǂݍ��ލ���
	float GetX();

	//�@���_��Y���W��ǂݍ���
	float GetY();

	//�@���̒��_���X�g���w���|�C���^��ǂݍ���
	Vertex* GetNext();

	//�@���̒��_���X�g���w���|�C���^����������
	Vertex* SetNext(Vertex* new_next);

	void FreeVertex();
};
