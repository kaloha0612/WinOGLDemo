#pragma onc
#include <gl/GL.h>
#include "Vertex.h"

class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();

	void Draw();

	Vertex* AppendVertex(float x, float y);

private:
	//�@���_���X�g�̃w�b�h
	Vertex* vertex_head = NULL;
};

