#pragma onc
#include <gl/GL.h>
#include "Vertex.h"
#include "pch.h"]
#include "CShape.h"
#include <math.h>

class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();

	void Draw();

	//�_��cshape_head�ɒǉ�����
	void AppendCShape();

	//�V�����`��p�̃��X�g��cshape_head�ɒǉ�����
	void CreateShape(float x, float y);

	//2�_�Ԃ̋������v�Z����
	float Distance(Vertex* start, float x, float y);

	//�_�Ɛ}�`�̊p�x�̑��a�����ߓ���肷��֐�
	int StraightAngle(CShape* startS, Vertex* startV, float x, float y);

	//cshape_head�̃L�����p�X�Ƃ̓���������֐�
	int StraightAngleEX(CShape* startS, Vertex* startV, float x, float y);

	//���������������̔���֐�
	int StraightCross(CShape* startS, Vertex* startV, float x, float y);

	//�������݂̂̔���p�֐�
	int StraightCross2(CShape* startS, Vertex* startV, float x, float y);

	//2�_�̃x�N�g�����v�Z����
	Vertex* bekutorukun(Vertex* a, Vertex* b);

	//2�_�̊O�ς��v�Z����
	float gaisekikun(Vertex* a, Vertex* b);

	//2�̊O�ς�����ς��v�Z����
	float naisekikun(Vertex* a, Vertex* b);

	//2�����̊p�x�����߂�
	float kakudokun(Vertex* a, Vertex* b);

	/*
	//�ʂ̕��@�Ő����̌������������֐�(�r��)
	int LineCross(Vertex* start, float x, float y);
	*/
	//���钼���ɑ΂�2�_�����f����Ă��邩���肷��(�ʕ��@�p)
	int bundankun(Vertex* a, Vertex* b, Vertex* c, Vertex* d);
	

private:
	//�@���_���X�g�̃w�b�h
	//Vertex* vertex_head = NULL;
	CShape* cshape_head = NULL;
	CShape* cshape_change = NULL;
};

