#include "stdafx.h"
#include "CFunc_Spec_Item_Main.h"


CFunc_Spec_Item_Main::CFunc_Spec_Item_Main()
{
	f_init_variable();
}


CFunc_Spec_Item_Main::~CFunc_Spec_Item_Main()
{
}


void CFunc_Spec_Item_Main::f_init_variable()
{
	this->stCal.fMul		= 1;
	this->stCal.fSum		= 0;
	this->stCal.sRefText	= "";

	this->stDataFmt.nMode	= 0;
	this->stDataFmt.sFormat = "%8.3f";

	this->strTestUnit	= "";
	this->strTestSymbol = "";
	this->strTestName	= "";

}