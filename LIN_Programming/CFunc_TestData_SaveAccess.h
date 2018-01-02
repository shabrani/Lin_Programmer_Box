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
	Ver 2.0 - ������ ���� ������ ���� (LIN Test�ϸ鼭 Unsigned Data�� ó���ؾ��� �ʿ䰡 �־���)
	Ver 2.1 - Tool ��ȣ�� BIN ��ȣ�� ����, Test Time�� TestStartTime���� ���� 

	Ver 2.2 - Note1�� ������ ���ڷ� �߸� ����� -> Text�� ������

	ver 2.3.0	- 20135.07.02
				- Text Data�� ������� Ȯ��

				- TEST_MAIN: TEXT_TABLENAME,SAVEFAIL_YN �߰�
				- TEST_SPEC: TEXTDATA_YN,TEXTSPEC1, TEXTSPEC2 �߰�,PID ����(�ǹ̾���)
				- TEST_DATA: TNO_001->T001, CHK_001->T001_CHK�� ���� (TEST��ȣ ���ϼ� Ȯ��), PID����(�ǹ̾���)
				- TEST_SPEC TABLE ���� (���ʿ�)
				- 

				- �ʵ��� �����ʹ� ��Ȯ�ϰ� ���� ����. ������ Ȯ����, ó�����μ����� ������ �ʿ���.
				- �˻��׸��� �׼����Ѱ�� ���Ͽ� 120�� MAX�� (�����Ϳ� �˻����� �и��ϸ� 240������ ������)

	ver 2.3.1 - 2015.07.07
			- TEST_MAIN : TEXTDATA_YN �ʵ��߰�
			- TEST_DATA : SERIAL_NO->255�� ����
			- TEXTDATA_SAVE_ENABLE ��� �߰� 
*/


#define TESTDATA_DB_FILENAME_HEADER		"TESTDATA_V231"


#define DATA_DB_REV_NO					"Ver 2.3.1"				
#define DATA_DB_REV_DATE				"2015-07-07"
#define DATA_DB_REV_NOTE				"Ver 2.3.1 - TEXTDATA_YN �ʵ��߰�,SERIAL_NO(255�� ����)"


#define TEXTDATA_SAVE_ENABLE

class CFunc_TestData_SaveAccess  
{
public:
	CFunc_TestData_SaveAccess();
	virtual ~CFunc_TestData_SaveAccess();

	//global data ����


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
		CString	strDsn;						//����Ÿ���̽� ���� ������
		int		nPID;						//TESTSPECHEADER�� DB ID
		CString	strTableName_DATA;			//����Ÿ���̽� ����Ÿ ���̺��
		CString	strTableName_DATA_SPEC;		//// $ 2015.05.05 Add 
		CString strTableName_DATA_TEXT;		//	 $ 2015.07.02 Add

		CString strDBFilname_start;			// $ 2015. 06.20 sjkim
	}m_var;

	struct
	{	
		bool bInitDB		;
		bool bDataTable_Config	;
		bool bTestSpec			;

		bool DBFile_bExist;			// DB�� ������.DBFile�� �ִٸ� �⺻ ���̺� �ִٰ� �����Ѵ�.
		bool DBFile_bCreate;		// DBFile�� �����Ǿ������� Ȯ���Ҷ� �ʿ���->�����Ȱ�� DBInfo Table�� �����Ǿ�� ��.	

		bool Table_DATA_bExist;
		bool DATA_TEXTNOTE_bSave;	// $ 2015.03.25 sjkim ������ ����� Info Field ���忩�θ� ����.
	}m_BOOL;						// $ 2015.03.03 sjkim 

	struct
	{
		CTime	tDBFile;
		CTime	tDBTable;
		CTime	sDBFile;
		CTime	sDBTable;
	}m_time;

	bool f_Create_New_DBFile (unsigned nAr,bool bSave_TextData = false);

	
	
	void f_saveData( );		// $ Change 2013-0911	// $ Change by sjkim 2012-06-20 -> Test End Time���� ����
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
	BOOL	f_DB_Make				( );	//����Ÿ���̽� ó�� ���鶧

};
