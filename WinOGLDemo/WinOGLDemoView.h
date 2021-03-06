
// WinOGLDemoView.h : CWinOGLDemoView クラスのインターフェイス
//

#pragma once
#include <gl/GL.h>
#include "AdminControl.h"
#include "pch.h"


class CWinOGLDemoView : public CView
{
protected: // シリアル化からのみ作成します。
	CWinOGLDemoView() noexcept;
	DECLARE_DYNCREATE(CWinOGLDemoView)

// 属性
public:
	CWinOGLDemoDoc* GetDocument() const;
//	double ClickX;
//	double ClickY;

private:
	double ClickX;
	double ClickY;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CWinOGLDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	HGLRC m_hRC;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	CAdminControl AC;
};

#ifndef _DEBUG  // WinOGLDemoView.cpp のデバッグ バージョン
inline CWinOGLDemoDoc* CWinOGLDemoView::GetDocument() const
   { return reinterpret_cast<CWinOGLDemoDoc*>(m_pDocument); }
#endif

