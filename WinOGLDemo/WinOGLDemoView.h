
// WinOGLDemoView.h : CWinOGLDemoView クラスのインターフェイス
//

#pragma once


class CWinOGLDemoView : public CView
{
protected: // シリアル化からのみ作成します。
	CWinOGLDemoView() noexcept;
	DECLARE_DYNCREATE(CWinOGLDemoView)

// 属性
public:
	CWinOGLDemoDoc* GetDocument() const;

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
};

#ifndef _DEBUG  // WinOGLDemoView.cpp のデバッグ バージョン
inline CWinOGLDemoDoc* CWinOGLDemoView::GetDocument() const
   { return reinterpret_cast<CWinOGLDemoDoc*>(m_pDocument); }
#endif

