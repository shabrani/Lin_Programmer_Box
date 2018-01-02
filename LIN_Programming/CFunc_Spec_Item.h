#pragma once

#include <afxdb.h>
#include <algorithm>
#include <fstream>
#include <functional>
#include <io.h>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <odbcinst.h>
#include <string>
#include <vector>

#include "CLin_Data.h"
#include "CTest_State.h"
#include "CFunc_Mode_Vector.h"
#include "CFunc_Spec_Item_Main.h"
#include "CFunc_Spec_Item_Main_Mode.h"


// Define //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define	STRSIZE_CSPEC_STEPSOURCE			20
#define	STRSIZE_CSPEC_PINNAME				20
#define	STRSIZE_CSPEC_TITEM_DESC			100
#define	STRSIZE_CSPEC_TITEM_DATAFORMAT		20
#define	STRSIZE_CSPEC_TITEM_UNIT			20
#define	STRSIZE_CSPEC_TITEM_SYMBOL			20

#define CSPEC_REFFUNC_GROUPTEST_ITEM_MAX	10


// LIN 관련 구조체 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned	nId;

	TU_UINT64	Data;

	unsigned	nLen;

}TS_CSPEC_SPECINFO_LIN_MSG_DATA;

typedef struct
{
	// CR665	// TLE8880,8881		// LIN2112 
	unsigned char Addr00;	// R1 Low			// Offset0_5
	unsigned char Addr01;	// R1 High			// Offset0_6
	unsigned char Addr02;	// R2 Low			// Offset0_7
	unsigned char Addr03;	// R2 High			// Offset0_8

	unsigned char Addr04;	// R3 Low			// Offset1_5
	unsigned char Addr05;	// R3 High			// Offset1_6
	unsigned char Addr06;	// R4 Low			// Offset1_7
	unsigned char Addr07;	// R4 High			// Offset1_8

	unsigned char Addr08;	//   -				// Offset2_5
	unsigned char Addr09;	//   -				// Offset2_6
	unsigned char Addr10;	//	 -				// Offset2_7
	unsigned char Addr11;	//   -				// Offset2_8	

}TS_CSPEC_SPECINFO_LIN_NVM;

typedef struct
{
	unsigned nRx;
	unsigned nTx1;
	unsigned nTx2;
	unsigned nTx3;

}TS_CSPEC_SPECINFO_LIN_FID;

typedef struct
{
	TS_CSPEC_SPECINFO_LIN_NVM	Nvm;
	TS_CSPEC_SPECINFO_LIN_FID	Fid;

	CString		sInterface;
	unsigned	nBaudrate;
	unsigned	nChip;
	unsigned	nRegulator;
	unsigned	nVersion;
	unsigned	nWaitTime;

	float		fVoltage;
	float		fCurrent;

	bool		bLinSpecLoad;	// LIN Spec을 로드하였는지.. 확인하는 플래그

}TS_CSPEC_SPECINFO_LIN;

typedef struct
{
	TS_CSPEC_SPECINFO_LIN_MSG_DATA		msg_RX;
	TS_CSPEC_SPECINFO_LIN_MSG_DATA		msg_User;

	unsigned SendMsg_nSel;
	double   SendMsg_fRepeatSendTime_Ms;
	bool	 SendMsg_bRepeatSend;

	unsigned meas_NVM_nParam;

}TS_CSPEC_TITEM_LIN;


// etc... //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned 	nId;
	CString		sInfo;

	struct
	{
		UINT32		nItem_Max;										//몇개 항목을 추가할지 여부를 결정					-- 개발자 item

		CString		sSymbol[CSPEC_REFFUNC_GROUPTEST_ITEM_MAX];		//추가되는Item을 구별하기 위한 Symbol					-- 개발자 Item 
		UINT32		nProcYN[CSPEC_REFFUNC_GROUPTEST_ITEM_MAX];		//추가되는 Item의 프로세스를 적용할지 여부를 결정		-- 개발자 결정 
	}Group;

}TS_CSPEC_REFFUNC;

typedef struct
{
	CString				strInfo1;
	CString				strInfo2;
}TS_CSPEC_TITEM_INFO;






class CFunc_Spec_Item
{
public:

	CFunc_Spec_Item(void);
	~CFunc_Spec_Item(void);

	CFunc_Spec_Item_Main Spec;

	TS_CSPEC_TITEM_LIN	 Lin;

	TS_CSPEC_TITEM_INFO	 Info;
};
