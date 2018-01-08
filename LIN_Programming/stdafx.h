
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#include "NiUiComponent.h" 
#include "NiDAQmxComponent.h" 
#include <afxdlgs.h>
#include <afxctl.h>
using namespace NI;

#define	WM_ASYNC_SELECT					( WM_USER + 4000 )
#define	WM_ASYNC_SELECT_0				( WM_USER + 4000 )
#define	WM_ASYNC_SELECT_1				( WM_USER + 4001 )

//#define	WM_DEVICE_BARCODE_CLOSE_0		( WM_USER + 4010 )
//#define	WM_DEVICE_BARCODE_CLOSE_1		( WM_USER + 4011 )
//#define	WM_DEVICE_BARCODE_CONNECT_0		( WM_USER + 4012 )
//#define	WM_DEVICE_BARCODE_CONNECT_1		( WM_USER + 4013 )

#define WM_DEVICE_HDLR_PORT_CONNECTED        ( WM_USER + 4014 )
#define WM_DEVICE_HDLR_PORT_CLOSEED          ( WM_USER + 4015 )
#define WM_DEVICE_HDLR_PORT_RECEIVE          ( WM_USER + 4016 )

#define WM_DEVICE_MCU_PORT_CLOSEED           ( WM_USER + 4017 )
#define WM_DEVICE_MCU_PORT_CONNECTED         ( WM_USER + 4018 )



#define	WM_DEVICE_CLOSE_0				( WM_USER + 4020 )
#define	WM_DEVICE_CLOSE_1				( WM_USER + 4021 )
#define	WM_DEVICE_CONNECT_0				( WM_USER + 4022 )
#define	WM_DEVICE_CONNECT_1				( WM_USER + 4023 )



#define	BUF_SIZE						( 9999 + 6 )
#define	IP4_SIZE						( 15 )

#define	bzero(p, l)				( memset(p, 0, l) )


#include "Comu_CSerial.h"