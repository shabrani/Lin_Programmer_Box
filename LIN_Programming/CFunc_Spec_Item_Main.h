#pragma once

#include "CTest_State.h"
#include "CFunc_Mode_Vector.h"
#include "CFunc_Spec_Item_Main_Mode.h"





typedef struct
{
	unsigned nMode;
	CString  sFormat;
}TS_CSPEC_TITEM_MAIN_DATA_FORMAT;

typedef struct
{
	unsigned nMode;
	CString sTrue;
	CString sFalse;
}TS_CSPEC_TITEM_MAIN_DATA_DISPLAY;

typedef struct
{
	double		fMul;
	double		fSum;
	CString     sRefText;
}TS_CSPEC_TITEM_SPEC_CAL;

typedef struct
{
	unsigned	nMode;

	VARIANT		HSL_VAR;
	VARIANT		LSL_VAR;
}TS_CSPEC_TITEM_SPEC_LIMIT;

typedef struct
{
	bool		bPrevTested;

	TU_UINT32	uTestYN;
	UINT32		nItem_IdxNo[10];
	UINT32		nItem_Max;
}TS_CSPEC_TITEM_SPEC_GROUPITEM;





class CFunc_Spec_Item_Main_Option
{
public:
	CFunc_Spec_Item_Main_Option() {}
	~CFunc_Spec_Item_Main_Option() {}


	bool isTest;			//1bit
	bool isPowerOnTest;		//1bit

};


class CFunc_Spec_Item_Main
{
public:
	CFunc_Spec_Item_Main(void);
	~CFunc_Spec_Item_Main(void);



	unsigned    nPnum;
	unsigned    nTnum;
	unsigned	nDispNum;
	unsigned	nPnum_Prev;
	unsigned	nPnum_Next;

	CString		strDataFormat;
	CString		strTestSymbol;
	CString		strTestName;
	CString		strTestUnit;


	unsigned	nRefTitem;



	CFunc_Spec_Item_Main_Option			Option;

	TS_CSPEC_TITEM_SPEC_GROUPITEM		stGroup;
	TS_CSPEC_TITEM_SPEC_LIMIT			stLimit;
	TS_CSPEC_TITEM_SPEC_CAL				stCal;

	TS_CSPEC_TITEM_MAIN_DATA_FORMAT		stDataFmt;
	TS_CSPEC_TITEM_MAIN_DATA_DISPLAY	stDataDisp;


	void f_init_variable();
};
