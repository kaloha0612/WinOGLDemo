
// WinOGLDemoView.cpp : CWinOGLDemoView クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "WinOGLDemo.h"
#endif

#include "WinOGLDemoDoc.h"
#include "WinOGLDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinOGLDemoView

IMPLEMENT_DYNCREATE(CWinOGLDemoView, CView)

BEGIN_MESSAGE_MAP(CWinOGLDemoView, CView)
END_MESSAGE_MAP()

// CWinOGLDemoView コンストラクション/デストラクション

CWinOGLDemoView::CWinOGLDemoView() noexcept
{
	// TODO: 構築コードをここに追加します。

}

CWinOGLDemoView::~CWinOGLDemoView()
{
}

BOOL CWinOGLDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CWinOGLDemoView 描画

void CWinOGLDemoView::OnDraw(CDC* /*pDC*/)
{
	CWinOGLDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}


// CWinOGLDemoView の診断

#ifdef _DEBUG
void CWinOGLDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CWinOGLDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinOGLDemoDoc* CWinOGLDemoView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinOGLDemoDoc)));
	return (CWinOGLDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinOGLDemoView メッセージ ハンドラー
