// CFunc_DataTable.h: interface for the CFunc_DataTable class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "CFunc_Spec.h"
#include "CFunc_TestData.h"
#include "CTest_State.h"
#include "afxdao.h"

#include "CFunc_DB_Odbc.h"
#include "CFunc_DB_Dao.h"


#pragma warning(disable:4995) 


/*
	Ver 2.0 - 데이터 저장 구조를 변경 (LIN Test하면서 Unsigned Data를 처리해야할 필요가 있었음)
	Ver 2.1 - Tool 번호를 BIN 번호로 변경, Test Time을 TestStartTime으로 변경 

	Ver 2.2 - Note1의 구조가 숫자로 잘목 적용됨 -> Text로 수정함

	ver 2.3.0	- 20135.07.02
				- Text Data의 저장공간 확보

				- TEST_MAIN: TEXT_TABLENAME,SAVEFAIL_YN 추가
				- TEST_SPEC: TEXTDATA_YN,TEXTSPEC1, TEXTSPEC2 추가,PID 삭제(의미없음)
				- TEST_DATA: TNO_001->T001, CHK_001->T001_CHK로 변경 (TEST번호 통일성 확보), PID삭제(의미없음)
				- TEST_SPEC TABLE 삭제 (불필요)
				- 

				- 필드의 데이터는 정확하게 넣지 못함. 공간만 확보함, 처리프로세스도 정립이 필요함.
				- 검사항목의 액세스한계로 인하여 120개 MAX임 (데이터와 검사결과를 분리하면 240개까지 가능함)

	ver 2.3.1 - 2015.07.07
			- TEST_MAIN : TEXTDATA_YN 필드추가
			- TEST_DATA : SERIAL_NO->255로 변경
			- TEXTDATA_SAVE_ENABLE 기능 추가 
*/


#define TESTDATA_DB_FILENAME_HEADER		"TESTDATA_V231"


#define DATA_DB_REV_NO					"Ver 2.3.1"				
#define DATA_DB_REV_DATE				"2015-07-07"
#define DATA_DB_REV_NOTE				"Ver 2.3.1 - TEXTDATA_YN 필드추가,SERIAL_NO(255로 변경)"


#define TEXTDATA_SAVE_ENABLE

class CFunc_TestData_SaveAccess  
{
public:
	CFunc_TestData_SaveAccess();
	virtual ~CFunc_TestData_SaveAccess();

	//global data 변수


	//ST_CDATATABLE_TESTSPECHEADER		m_stTestSpecHeader;

	struct
	{
		CFunc_Spec		*pCSpec;
		CTest_State		*pts;
		CFunc_TestData	*pCData;

	}m_cfg;

	struct
	{	
		unsigned nAr;
		unsigned nTitem;
		bool bSaveComplete;

		CTime	tmCreateTime;		//Spec load & Database Create
		CString strCreateTime;

		unsigned nTestSpec	;

		CString	strDBFilePath;
		CString	strDBFileName;
		CString	strDsn;						//데이타베이스 오픈 퀘리문
		int		nPID;						//TESTSPECHEADER의 DB ID
		CString	strTableName_DATA;			//데이타베이스 데이타 테이블명
		CString	strTableName_DATA_SPEC;		//// $ 2015.05.05 Add 
		CString strTableName_DATA_TEXT;		//	 $ 2015.07.02 Add

		CString strDBFilname_start;			// $ 2015. 06.20 sjkim
	}m_var;

	struct
	{	
		bool bInitDB		;
		bool bDataTable_Config	;
		bool bTestSpec			;

		bool DBFile_bExist;			// DB가 있을때.DBFile이 있다면 기본 테이블도 있다고 간주한다.
		bool DBFile_bCreate;		// DBFile이 생성되었는지를 확인할때 필요함->생성된경우 DBInfo Table도 생성되어야 함.	

		bool Table_DATA_bExist;
		bool DATA_TEXTNOTE_bSave;	// $ 2015.03.25 sjkim 데이터 저장시 Info Field 저장여부를 결정.
	}m_BOOL;						// $ 2015.03.03 sjkim 

	struct
	{
		CTime	tDBFile;
		CTime	tDBTable;
		CTime	sDBFile;
		CTime	sDBTable;
	}m_time;

	bool f_Create_New_DBFile (unsigned nAr,bool bSave_TextData = false);

	
	
	void f_saveData( );		// $ Change 2013-0911	// $ Change by sjkim 2012-06-20 -> Test End Time으로 변경
	BOOL f_Change_New_LotNumber (CString strNewLotNum);



	CFunc_DB_Odbc	m_odbcFunc;
	CFunc_DB_Dao    m_daoFunc;
	

//	void f_spec_copyHeader();
//	void f_createArray_DataAndSpec (unsigned nTitem, unsigned nAr);


private:


	BOOL f_Create_DBTable_TestData_TEXT ();						// $ 2015.07.02 Add
	BOOL f_Create_DBTable_TestData		();
	BOOL f_Create_DBTable_TestData_Spec	();

	BOOL f_Create_DBTable_TestSpec	(CDaoDatabase	*pdb);
	BOOL f_Create_DBTable_TestMain	(CDaoDatabase	*pdb);
	BOOL f_Create_DBTable_DBInfo	(CDaoDatabase	*pdb);

	BOOL f_DB_Init					(CString strDBFilePath,			CString strFileMiddle);

	BOOL f_Init_TestMain           ();
	BOOL f_Input_TestMain_to_Table ();
	BOOL f_Input_TestSpec_to_TABLE ();
	BOOL f_Input_TestData_to_TABLE ();
	BOOL f_Input_TEXTData_to_TABLE ();				// $ 2015.07.02 Add

	BOOL f_input_DBInfo_to_TABLE();  // $ 2015.03.03 Add sjkim 


	CString f_GetDriverStringX	(CString drivername); 
	BOOL	f_DB_Make				( );	//데이타베이스 처음 만들때

};
