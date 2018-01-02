#pragma once

#include "CFunc_Spec.h"
#include "CTest_State.h"

class CFunc_File
{
public:
	CFunc_File(void);
	~CFunc_File(void);

	struct{
		CFunc_Spec	*pCTestSpec;
		CTest_State	*pCTestStatus;
	}m_cfg;

	struct{
		unsigned	nAr;
		unsigned	nTitem;
		bool		bSaveComplete;

		CTime		tmCreateTime;
	}m_var;

	struct _st_datasave{
		CString		sPathname;		// Registry에 저장된 기본 파일 이름
		CString		sFilename;		// 저장하려는 이름 
	}m_datafile;

	struct{
		unsigned int Year;	
		unsigned int Month;
		unsigned int Day;	
		unsigned int Hour;	
		unsigned int Min;	
		unsigned int Sec;
	}nDate;

	struct{
		CString		DevName;
		CString		SpecName;
		CString		LotNo;
		CString		TestDate;
		CString		Equipment;
		CString		CompanyName;
		CString		Operator;
		CString		Lotremark;
	}sInfo;

	struct
	{
		CString		Year;
		CString		Month;
		CString		Day;
		CString		Hour;
		CString		Min;
		CString		Sec;
	}sDate;


	void f_Open_File (void);
	void f_Save_Spec (void);

};

