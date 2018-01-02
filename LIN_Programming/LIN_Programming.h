
// LIN_Programming.h : main header file for the LIN_Programming application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLIN_ProgrammingApp:
// See LIN_Programming.cpp for the implementation of this class
//

class CLIN_ProgrammingApp : public CWinAppEx
{
public:
	CLIN_ProgrammingApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();




// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLIN_ProgrammingApp theApp;
