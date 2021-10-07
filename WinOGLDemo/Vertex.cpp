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


//　頂点のX・Y座標の両方を書き込む
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

//　頂点のX座標を読み込む込む
int Vertex::GetX()
{
	return x;
}

//　頂点のY座標を読み込む
int Vertex::GetY()
{
	return y;
}


//　次の頂点リストを指すポインタを書き込む
void Vertex::SetNext(Vertex* vertex)
{
	next_vertex = vertex;
}

//　次の頂点リストを指すポインタを読み込む
Vertex* Vertex::GetNext()
{
	return next_vertex;
}
