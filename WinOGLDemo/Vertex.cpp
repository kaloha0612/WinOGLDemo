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


//　頂点のX・Y座標の両方を書き込む
void Vertex::SetXY(float new_x, float new_y)
{
	
		x = new_x;
		y = new_y;
}

//　頂点のX座標を読み込む込む
float Vertex::GetX()
{
	return x;
}

//　頂点のY座標を読み込む
float Vertex::GetY()
{
	return y;
}


//　次の頂点リストを指すポインタを書き込む
Vertex* Vertex::SetNext(Vertex* new_next)
{
	return next_vertex = new_next;
}

//　次の頂点リストを指すポインタを読み込む
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
