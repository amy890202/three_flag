
// flag.h: flag 應用程式的主要標頭檔
//
#pragma once

#ifndef __AFXWIN_H__
	#error "對 PCH 包含此檔案前先包含 'stdafx.h'"
#endif

#include "resource.h"       // 主要符號


// CflagApp:
// 查看 flag.cpp 以了解此類別的實作
//

class CflagApp : public CWinApp
{
public:
	CflagApp() noexcept;


// 覆寫
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 程式碼實作
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CflagApp theApp;
