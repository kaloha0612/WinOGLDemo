#pragma once
#include <stdio.h> 
#include "pch.h"

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y);
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
	void SetXY(float x, float y);

	//�@���_��X���W��ǂݍ��ލ���
	int GetX();
	//�@���_��Y���W��ǂݍ���
	int GetY();

	//�@���̒��_���X�g���w���|�C���^��ǂݍ���
	Vertex* GetNext();

	//�@���̒��_���X�g���w���|�C���^����������
	Vertex* SetNext(Vertex* vertex);

	void FreeVertex();
};
