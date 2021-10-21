#pragma once
#include <Windows.h>
#include "Vertex.h"

class CShape
{
public:
	CShape();
	CShape(Vertex* new_v);
	~CShape();



	//　頂点のX・Y座標の両方を書き込む
	void SetV(Vertex* v);

	Vertex* GetV();

	//　次の頂点リストを指すポインタを読み込む
	CShape* GetNextS();

	//　次の頂点リストを指すポインタを書き込む
	CShape* SetNextS(CShape* new_nextS);

	void FreeCShape();

	Vertex* AppendVertex(float x, float y);
	int CountVertex();

private:
	//　次の頂点リストを指すポインタ
	Vertex* vertex_head = NULL;
	CShape* next_cshape = NULL;
};

