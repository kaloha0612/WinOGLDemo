
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
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CWinOGLDemoView コンストラクション/デストラクション

CWinOGLDemoView::CWinOGLDemoView() noexcept
{
	// TODO: 構築コードをここに追加します。
	ClickX = 0;
	ClickY = 0;
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

void CWinOGLDemoView::OnDraw(CDC* pDC)
{
	CWinOGLDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	wglMakeCurrent(pDC->m_hDC, m_hRC);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT /* | GL_DEPTH_BUFFER_BIT
	*/);
	AC.Draw();
	/*glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);

	glBegin(GL_POINTS);

	glVertex2f(ClickX, ClickY);
	glEnd();*/

	//glBegin(GL_LINE_LOOP);

	//glVertex2f(-0.5, 0.5);
	//glVertex2f(0.5, 0.5);
	//glVertex2f(0.5, -0.5);
	//glVertex2f(-0.5, -0.5);
	//glEnd();

	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(pDC->m_hDC, NULL);
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


void CWinOGLDemoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	CRect rect;
	GetClientRect(rect); // 描画領域の大きさを取得
	/*---------------------------------*/
	/* この中は自分で考える(ヒント 3) */
	double X;
	double Y;
	double y;
	X = (double)point.x / rect.Width();
	Y = (double)point.y / rect.Height();
	y = (Y - 1) * -1;
	ClickX = X * 2 - 1;
	ClickY = y * 2 - 1;

	double hi;
	if (rect.Width() > rect.Height()) {
		hi = ((double)rect.Width() / rect.Height());
		ClickX = ClickX * hi;
	}
	else {
		hi = ((double)rect.Height() / rect.Width());
		ClickY = ClickY * hi;
	}
	/*---------------------------------*/


	AC.AppendVertex(ClickX, ClickY);

	RedrawWindow();
	CView::OnLButtonDown(nFlags, point);
}

// おわり

int CWinOGLDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: ここに特定な作成コードを追加してください。
	PIXELFORMATDESCRIPTOR pfd =
	{
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW |
	PFD_SUPPORT_OPENGL |
	PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	32,
	0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	24,
	0,0,
	PFD_MAIN_PLANE,
	0,
	0,0,0
	};
	CClientDC clientDC(this);
	int pixelFormat = ChoosePixelFormat(clientDC.m_hDC,
		&pfd);
	SetPixelFormat(clientDC.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(clientDC.m_hDC);

	return 0;
}


void CWinOGLDemoView::OnDestroy()
{
	CView::OnDestroy();
	wglDeleteContext(m_hRC);

	// TODO: ここにメッセージ ハンドラー コードを追加します。
}


BOOL CWinOGLDemoView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	return true;
}


void CWinOGLDemoView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ここにメッセージ ハンドラー コードを追加します。
	CClientDC clientDC(this);
	wglMakeCurrent(clientDC.m_hDC, m_hRC);
	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double w;
	

	if (cx > cy) {
		w = (double)cx / cy;
		glOrtho(-1.0 * w, 1.0 * w, -1.0, 1.0, -100, 100); // 問 5.2 で考える内容
	}
	else {
		w = (double)cy / cx;
		glOrtho(-1.0, 1.0, -1.0 * w, 1.0 * w, -100, 100); // 問 5.2 で考える内容
	}
	glMatrixMode(GL_MODELVIEW);
	RedrawWindow();
	wglMakeCurrent(clientDC.m_hDC, NULL);
}
