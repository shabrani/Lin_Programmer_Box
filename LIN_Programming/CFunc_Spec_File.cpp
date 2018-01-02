#include "stdafx.h"
#include "CFunc_Spec_File.h"
#include "CTest_Main.h"
#include "tmenu_file.h"
#include "CFunc_BackupFile.h"


extern CTest_Main	*pTest;
using namespace std;

#define DBTABLE_DATABASE_FORM_REVNO	"DATABASE_FORM_REVNO"


CFunc_Spec_File::CFunc_Spec_File(CFunc_Spec *pCSpec)
{
	m_pCSpec = pCSpec;
}


CFunc_Spec_File::~CFunc_Spec_File(void)
{
}


bool CFunc_Spec_File::f_SpecFile_Load (CTest_State *ts, unsigned nVersion /* =0 */)
{
	CString strTemp	= "";
	CString strMsg  = "";

	CString strFilename;
	CString strBasePath;




	pTest->m_pReg->f_regiRead_Path_TestSpec(strBasePath);


	//다이얼로그로 부터 파일 이름을 선택합니다. 
	BOOL b = f_open_file_dialog (strFilename, strBasePath, "SPEC FILE(*.SPEC)\0*.spec\0");
	if (b == FALSE ) return false;


	if (0 == strFilename.GetLength() ) return false;


	m_pCSpec->m_stSpecInfo.Lin.bLinSpecLoad = false;	


	BOOL bRtn = m_daoFunc.f_table_isExist_yesno ( strFilename, DBTABLE_DATABASE_FORM_REVNO ); 


	if (false == this->f_extract_CSpec_from_SFile (strFilename) ) return false;


	m_pCSpec->f_titem_stable_sort_with_isFuncTest (m_pCSpec->m_vTitem);


	this->f_SpecFile_LoadSpec_set_Data_Initialize();


	return true;
}


bool CFunc_Spec_File::f_specFile_Form_Update(CString sFilename)
{
	BOOL bRtn = m_daoFunc.f_table_isExist_yesno(sFilename, DBTABLE_DATABASE_FORM_REVNO);		// $ Add 2015.04.20  

	if (TRUE != bRtn)
	{
		m_dbform.bExist_DBFORMTable = false;
		int iRtn = AfxMessageBox("SPEC FILE에 DB FORM Rev.No 정보가 없읍니다.");

		return false;
	}
	else
	{
		m_dbform.bExist_DBFORMTable = true;
	}


	return true;
}


bool CFunc_Spec_File::f_SpecFile_LoadSpec_set_Data_Initialize()
{
	m_pCSpec->m_stStatus.tmSpecLoad = CTime::GetCurrentTime();
	return true;
}





bool CFunc_Spec_File::f_DBForm_Upgrade_v5003_to_v5004(CString strFilename)	//Retest기능 항목 추가
{
	if (0 == strFilename.GetLength()) return FALSE;


	//먼저 백업을 한다.
	CFunc_BackupFile backup;
	backup.f_create_backupfile(strFilename);

	CDaoDatabase* pDatabase = NULL;

	bool bRtn = true;

	TRY
	{
		pDatabase = new CDaoDatabase;
	pDatabase->Open(strFilename);

	if (true == bRtn)
		if (false == m_daoFunc.f_field_check_exist_and_create_with_initial_value(pDatabase, "TESTSPEC_MAIN", "50_RETEST_START_ITEM_OFFSET", dbLong, 4, 0)) bRtn = false;

	}
		CATCH(CException, e) //예외처리 : 정확히는 CDaoException이지만 어짜피 CException 상속 클래스임.
	{
		TCHAR szCause[256];
		e->GetErrorMessage(szCause, 256);
		AfxMessageBox(szCause, MB_ICONERROR);

		bRtn = false;
	}
	END_CATCH

		if (pDatabase != NULL)
		{
			if (pDatabase->IsOpen())
				pDatabase->Close();

			delete pDatabase;
			pDatabase = NULL;
		}


	if (true == bRtn)
	{
		this->f_DBForm_Info_update(strFilename);
	}

	return  bRtn;
}


bool CFunc_Spec_File::f_DBForm_Info_extract(CString strFilename)
{

	TS_CSPEC_FIELD					buf_recd;
	std::vector<TS_CSPEC_FIELD>		vec_proc;
	std::vector<TS_CSPEC_FIELD>		vec_spec;
	CString sField, sData;


	CString sSql;
	CString sDriver;
	CString sDsn;


	CDatabase  *pDatabase = NULL;
	CRecordset *pRecset = NULL;



	CDBVariant varValue;
	sDriver = "MICROSOFT ACCESS DRIVER (*.MDB)";

	if (sDriver.IsEmpty())
	{
		AfxMessageBox("No ACCESS ODBC driver found");
		return false;
	}

	sDsn.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver.GetString(), strFilename.GetString());

	TRY
	{
		pDatabase = new CDatabase;

	unsigned rtn = pDatabase->Open(NULL,false,false,sDsn);

	if (rtn == 0)
	{
		pDatabase->Close();

		if (NULL != pDatabase)
			delete pDatabase;

		AfxMessageBox("Fail Database Open");
		return false;
	}

	//	f_DBForm_Info_extract (pDatabase);

	//	CRecordset recset(pDatabase);

	pRecset = new CRecordset(pDatabase);


	sSql.Format("SELECT * FROM %s", DBTABLE_DATABASE_FORM_REVNO);



	pRecset->Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);

	while (!pRecset->IsEOF())
	{
		pRecset->GetFieldValue("FIELD",	buf_recd.sField);
		pRecset->GetFieldValue("DATA",	buf_recd.sData);
		vec_proc.push_back(buf_recd);

		pRecset->MoveNext();
	}


	}
		CATCH(CDBException, e)
	{
		AfxMessageBox("Database error: " + e->m_strError);

		pRecset->Close();
		if (NULL != pRecset)
			delete pRecset;

		pDatabase->Close();

		if (NULL != pDatabase)
			delete pDatabase;

		return false;
	}
	END_CATCH;

	pRecset->Close();
	if (NULL != pRecset)
		delete pRecset;

	pDatabase->Close();
	if (NULL != pDatabase)
		delete pDatabase;

	// Check Test name

	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_CStr(vec_proc, "10_SPEC_ITEM", this->m_dbform.strSpecItem)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_u32(vec_proc, "20_REV_NO_MAIN", this->m_dbform.nRevMainNo)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_u32(vec_proc, "20_REV_NO_SUB", this->m_dbform.nRevSubNo)) return false;



	m_pCSpec->m_stStatus.isLoading_spec = true;

	m_pCSpec->m_stStatus.strFilename = strFilename;


	return true;

}


bool CFunc_Spec_File::f_DBForm_Info_extract(CDatabase &database)
{

	TS_CSPEC_FIELD					buf_recd;
	std::vector<TS_CSPEC_FIELD>		vec_proc;
	std::vector<TS_CSPEC_FIELD>		vec_spec;
	CString sField, sData;


	CString sSql;
	CString sDriver;
	CString sDsn;

	CRecordset recset(&database);



	TRY
	{
		//pRecset = new CRecordset(&database);


		sSql.Format("SELECT * FROM %s", DBTABLE_DATABASE_FORM_REVNO);



	recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);

	while (!recset.IsEOF())
	{
		recset.GetFieldValue("FIELD",	buf_recd.sField);
		recset.GetFieldValue("DATA",	buf_recd.sData);
		vec_proc.push_back(buf_recd);

		recset.MoveNext();
	}


	}
		CATCH(CDBException, e)
	{
		AfxMessageBox("Database error: " + e->m_strError);

		recset.Close();

		return false;
	}
	END_CATCH;

	recset.Close();



	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_CStr(vec_proc, "10_SPEC_ITEM", this->m_dbform.strSpecItem)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_u32(vec_proc, "20_REV_NO_MAIN", this->m_dbform.nRevMainNo)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_u32(vec_proc, "20_REV_NO_SUB", this->m_dbform.nRevSubNo)) return false;


	m_pCSpec->m_stStatus.isLoading_spec = true;


	return true;

}


bool CFunc_Spec_File::f_DBForm_Info_update(CString strFilename)
{
	CString sSQL;
	CString sDriver;
	CString sDsn;
	CString sBuf;

	CString sField;
	CString sData;
	CString sDBTable;

	CString SErrMsg;


	if (_access(strFilename, 00))
	{
		AfxMessageBox("CSpec Save Error.. \n saveFile Not Found");
		return false;
	}


	CDatabase database;

	sDriver = "MICROSOFT ACCESS DRIVER (*.MDB)";

	TRY
	{


		sSQL.Format("DRIVER={%s};DSN='';READONLY=FALSE;DBQ=%s",
		sDriver.GetString(), strFilename.GetString());

	if (database.OpenEx(sSQL, CDatabase::noOdbcDialog))
	{
		{
			sDBTable.Format("%s", DBTABLE_DATABASE_FORM_REVNO);

			if (true != this->m_odbcFunc.f_SQL_Update_SpecInfo_CStr(database,sDBTable, "10_SPEC_ITEM",		DBFORM_SPECITEM)) return false;
			if (true != this->m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "20_REV_NO_MAIN",	DBFORM_REV_NO_MAIN)) return false;
			if (true != this->m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "20_REV_NO_SUB",		DBFORM_REV_NO_SUB)) return false;
			if (true != this->m_odbcFunc.f_SQL_Update_SpecInfo_CStr(database,sDBTable, "30_REV_DATE",		DBFORM_REV_DATE)) return false;
			if (true != this->m_odbcFunc.f_SQL_Update_SpecInfo_CStr(database,sDBTable, "40_HISTORY",		DBFORM_REV_NOTE)) return false;
		}

	}

	database.Close();
	}

		CATCH(CDBException, e)
	{
		AfxMessageBox("Database error: " + e->m_strError);
		database.Close();
		return false;
	}
	END_CATCH;


	return true;


}