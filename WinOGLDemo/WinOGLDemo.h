
// WinOGLDemo.h : WinOGLDemo アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CWinOGLDemoApp:
// このクラスの実装については、WinOGLDemo.cpp を参照してください
//

class CWinOGLDemoApp : public CWinApp
{
public:
	CWinOGLDemoApp() noexcept;


// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWinOGLDemoApp theApp;
