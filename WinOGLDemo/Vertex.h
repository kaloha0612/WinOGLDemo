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
	//　頂点のX座標
	float x;
	//　頂点のY座標
	float y;
	//　次の頂点リストを指すポインタ
	Vertex* pre_vertex = NULL;
	Vertex* next_vertex = NULL;
public:
	//　頂点のX・Y座標の両方を書き込む
	void SetXY(float x, float y);

	//　頂点のX座標を読み込む込む
	int GetX();
	//　頂点のY座標を読み込む
	int GetY();

	//　次の頂点リストを指すポインタを読み込む
	Vertex* GetNext();

	//　次の頂点リストを指すポインタを書き込む
	Vertex* SetNext(Vertex* vertex);

	void FreeVertex();
};
