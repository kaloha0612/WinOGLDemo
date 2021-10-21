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

	//点をcshape_headに追加する
	void AppendCShape();

	//新しい形状用のリストをcshape_headに追加する
	void CreateShape(float x, float y);

	//2点間の距離を計算する
	float Distance(Vertex* start, float x, float y);

	//点と図形の角度の総和を求め内包判定する関数
	int StraightAngle(CShape* startS, Vertex* startV, float x, float y);

	//cshape_headのキャンパスとの内包判定をする関数
	int StraightAngleEX(CShape* startS, Vertex* startV, float x, float y);

	//自交差＆他交差の判定関数
	int StraightCross(CShape* startS, Vertex* startV, float x, float y);

	//他交差のみの判定用関数
	int StraightCross2(CShape* startS, Vertex* startV, float x, float y);

	//2点のベクトルを計算する
	Vertex* bekutorukun(Vertex* a, Vertex* b);

	//2点の外積を計算する
	float gaisekikun(Vertex* a, Vertex* b);

	//2つの外積から内積を計算する
	float naisekikun(Vertex* a, Vertex* b);

	//2線分の角度を求める
	float kakudokun(Vertex* a, Vertex* b);

	/*
	//別の方法で線分の交差判定をする関数(途中)
	int LineCross(Vertex* start, float x, float y);
	*/
	//ある直線に対し2点が分断されているか判定する(別方法用)
	int bundankun(Vertex* a, Vertex* b, Vertex* c, Vertex* d);
	

private:
	//　頂点リストのヘッド
	//Vertex* vertex_head = NULL;
	CShape* cshape_head = NULL;
	CShape* cshape_change = NULL;
};

