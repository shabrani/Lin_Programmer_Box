#include "stdafx.h"
#include "CFunc_DB_Dao.h"


CFunc_DB_Dao::CFunc_DB_Dao(void)
{
}


CFunc_DB_Dao::~CFunc_DB_Dao(void)
{
}





unsigned CFunc_DB_Dao::f_field_isExist_yesno (CString strFilename, CString strTableName, CString strFieldName)
{
	if (0 == strFilename.GetLength () ) return RETURN::FAIL;
	if (0 == strTableName.GetLength() ) return RETURN::FAIL;
	if (0 == strFieldName.GetLength() ) return RETURN::FAIL;


    CDaoDatabase* pDatabase = NULL;

	int iExist = ret_yesno::no;

	TRY
	{
		pDatabase = new CDaoDatabase;
		pDatabase->Open(strFilename);

		iExist = this->f_field_isExist_yesno (pDatabase, strTableName, strFieldName);
	}
    CATCH (CException, e) //예외처리 : 정확히는 CDaoException이지만 어짜피 CException 상속 클래스임.
    {
        TCHAR szCause[256];
        e->GetErrorMessage(szCause, 256);
        AfxMessageBox(szCause, MB_ICONERROR);

		iExist = ret_yesno::fail;
    }
    END_CATCH

    if (pDatabase != NULL)
    {
        if (pDatabase->IsOpen()) 
			pDatabase->Close();

        delete pDatabase;
        pDatabase = NULL;
    }

	return iExist;
}


unsigned CFunc_DB_Dao::f_field_isExist_yesno (CDaoDatabase* pdao, CString strTableName, CString strFieldName)
{

	int iExist = ret_yesno::no;

	CDaoTableDef* tableDef = NULL;
	tableDef = new CDaoTableDef(pdao);

	TRY
	{
		tableDef->Open(strTableName);

		int fieldCnt = tableDef->GetFieldCount();
		for (int i=0; i<fieldCnt; i++)
		{
			CDaoFieldInfo fieldInfo;
			tableDef->GetFieldInfo(i, fieldInfo, AFX_DAO_ALL_INFO);
			if (0 ==  strFieldName.CompareNoCase(fieldInfo.m_strName) )
			{
				iExist = ::ret_yesno::yes;
				break;
			}
		}
	}
    CATCH (CException, e) //예외처리 : 정확히는 CDaoException이지만 어짜피 CException 상속 클래스임.
    {
        TCHAR szCause[256];
        e->GetErrorMessage(szCause, 256);
        AfxMessageBox(szCause, MB_ICONERROR);

		iExist = ret_yesno::fail;
    }
    END_CATCH

    if (tableDef != NULL)
    {
        if (tableDef->IsOpen()) 
			tableDef->Close();

        delete tableDef;
        tableDef = NULL;
    }
	return iExist;
}


unsigned CFunc_DB_Dao::f_field_isExist_yesno (CDaoTableDef* pTableDef, CString strFieldName)
{
	int iExist = ret_yesno::no;

	TRY
	{
		int fieldCnt = pTableDef->GetFieldCount();
		for (int i=0; i<fieldCnt; i++)
		{
			CDaoFieldInfo fieldInfo;
			pTableDef->GetFieldInfo(i, fieldInfo, AFX_DAO_ALL_INFO);
			if (0 ==  strFieldName.CompareNoCase(fieldInfo.m_strName) )
			{
				iExist = ret_yesno::yes;
				break;
			}
		}
	}
    CATCH (CException, e) //예외처리 : 정확히는 CDaoException이지만 어짜피 CException 상속 클래스임.
    {
        TCHAR szCause[256];
        e->GetErrorMessage(szCause, 256);
        AfxMessageBox(szCause, MB_ICONERROR);

		iExist = ret_yesno::fail;
    }
    END_CATCH

	return iExist;
}

bool CFunc_DB_Dao::f_field_check_exist_and_create_with_initial_value (CDaoDatabase* pdao, CString strTablename, CString strFieldname, int fieldType, long fieldSize, long attributes)
{
	if (0 == strTablename.GetLength() ) return false;
	if (0 == strFieldname.GetLength() ) return false;

    CDaoTableDef* pTableDef = NULL;
	CDaoFieldInfo fieldInfo;	
	
	CString strTemp;

	bool bExist = false;
	bool bCreate = false;;

	TRY
	{
		pTableDef = new CDaoTableDef(pdao);
		pTableDef->Open(strTablename);

		int fieldCnt = pTableDef->GetFieldCount();

		for (int i=0; i<fieldCnt; i++)
		{
			pTableDef->GetFieldInfo(i, fieldInfo, AFX_DAO_ALL_INFO);
			if (0 ==  strFieldname.CompareNoCase(fieldInfo.m_strName) )
			{
				bExist = true;
				break;
			}
		}
	
		if (false == bExist)
		{
			pTableDef->CreateField(strFieldname ,  fieldType , fieldSize, attributes);
		}

		CString strQry;
		strQry.Format("UPDATE %s SET %s=0", strTablename.GetString(), strFieldname.GetString());

		pdao->Execute(strQry);


		bCreate = true;
	}
    CATCH (CException, e) //예외처리 : 정확히는 CDaoException이지만 어짜피 CException 상속 클래스임.
    {
        TCHAR szCause[256];
        e->GetErrorMessage(szCause, 256);
        AfxMessageBox(szCause, MB_ICONERROR);

		bCreate = false;
    }
    END_CATCH

	if (pTableDef != NULL)
	{
		if (pTableDef->IsOpen() )
			pTableDef->Close();

		delete pTableDef;
		pTableDef = NULL;
	}

	return bCreate;
}


bool  CFunc_DB_Dao::f_field_create  (CString strFilename, CString strTablename, CString strFieldname, int fieldType, long fieldSize, long attributes)
{
	if (0 == strFilename.GetLength() )  return false;
	if (0 == strTablename.GetLength() ) return false;
	if (0 == strFieldname.GetLength() ) return false;

    CDaoDatabase* pDatabase = NULL;
    CDaoTableDef* pTableDef = NULL;
	CDaoTableDefInfo TableInfo;

	CString strTemp;

	bool bRtn = false;;

	TRY
	{
		//db open
		pDatabase = new CDaoDatabase;
		pDatabase->Open(strFilename);

		pTableDef = new CDaoTableDef (pDatabase);
		pTableDef->Open(strTablename);

		pTableDef->CreateField(strFieldname ,  fieldType , fieldSize, attributes);
		bRtn = true;

	}
    CATCH (CException, e) //예외처리 : 정확히는 CDaoException이지만 어짜피 CException 상속 클래스임.
    {
        TCHAR szCause[256];
        e->GetErrorMessage(szCause, 256);
        AfxMessageBox(szCause, MB_ICONERROR);

		bRtn = false;
    }
    END_CATCH

	if (pTableDef != NULL)
	{
		if (pTableDef->IsOpen() )
			pTableDef->Close();

		delete pTableDef;
		pTableDef = NULL;
	}

	if (pDatabase != NULL)
	{
		if (pDatabase->IsOpen() )
			pDatabase->Close();

		delete pDatabase;
		pDatabase = NULL;
	}


	return bRtn;

}


bool CFunc_DB_Dao::f_field_create  (CDaoDatabase* pdao, CString strTablename, CString strFieldname, int fieldType, long fieldSize, long attributes)
{
	if (0 == strTablename.GetLength() ) return false;
	if (0 == strFieldname.GetLength() ) return false;

    CDaoTableDef* pTableDef = NULL;
	CString strTemp;

	bool bRtn = false;;

	TRY
	{
		pTableDef = new CDaoTableDef (pdao);
		pTableDef->Open(strTablename);

		pTableDef->CreateField(strFieldname ,  fieldType , fieldSize, attributes);
		
		bRtn = true;

	}
    CATCH (CException, e) //예외처리 : 정확히는 CDaoException이지만 어짜피 CException 상속 클래스임.
    {
        TCHAR szCause[256];
        e->GetErrorMessage(szCause, 256);
        AfxMessageBox(szCause, MB_ICONERROR);

		bRtn = false;
    }
    END_CATCH

	if (pTableDef != NULL)
	{
		if (pTableDef->IsOpen() )
			pTableDef->Close();

		delete pTableDef;
		pTableDef = NULL;
	}

	return bRtn;
}


bool CFunc_DB_Dao::f_field_create  (CDaoTableDef* pTableDef, CString strFieldname, int fieldType, long fieldSize, long attributes)
{
	if (0 == strFieldname.GetLength() ) return false;

	bool bRtn = false;;

	TRY
	{
		pTableDef->CreateField(strFieldname ,  fieldType , fieldSize, attributes);
		bRtn = true;

	}
    CATCH (CException, e) //예외처리 : 정확히는 CDaoException이지만 어짜피 CException 상속 클래스임.
    {
        TCHAR szCause[256];
        e->GetErrorMessage(szCause, 256);
        AfxMessageBox(szCause, MB_ICONERROR);

		bRtn = false;
    }
    END_CATCH

	return bRtn;
}



unsigned CFunc_DB_Dao::f_table_isExist_yesno (CString strFilename, CString strTableName)			// $ Add 2015.04.20 Table이 있으면 TRUE, ,읽는데 실패하거나 테이블이 없으면 FALSE
{
	if (0 == strFilename.GetLength()  ) ret_yesno::fail;
	if (0 == strTableName.GetLength() ) ret_yesno::fail;

    CDaoDatabase* pDatabase = NULL;
    CDaoTableDef* pTableDef = NULL;
	CDaoTableDefInfo TableInfo;

	CString strTemp;

	int iExist = ret_yesno::no;

	int iRtn = 0;

	TRY
	{
		//db open
		pDatabase = new CDaoDatabase;
		pDatabase->Open(strFilename);

		{
			int tableCnt = pDatabase->GetTableDefCount();

			for (int i=0; i<tableCnt; i++)
			{
				pDatabase->GetTableDefInfo(i, TableInfo, AFX_DAO_ALL_INFO);

				iRtn= strTableName.CompareNoCase(TableInfo.m_strName);
				if (0 == iRtn)
				{
					iExist = ret_yesno::yes;
					break;
				}
			}
		}

	}
    CATCH (CException, e) //예외처리 : 정확히는 CDaoException이지만 어짜피 CException 상속 클래스임.
    {
        TCHAR szCause[256];
        e->GetErrorMessage(szCause, 256);
        AfxMessageBox(szCause, MB_ICONERROR);

		iExist = ret_yesno::fail;
    }
    END_CATCH

	if (pTableDef != NULL)
	{
		if (pTableDef->IsOpen() )
			pTableDef->Close();

		delete pTableDef;
		pTableDef = NULL;
	}

	if (pDatabase != NULL)
	{
		if (pDatabase->IsOpen() )
			pDatabase->Close();

		delete pDatabase;
		pDatabase = NULL;
	}


	return iExist;

}


bool CFunc_DB_Dao:: f_table_create  (CDaoDatabase* pdao, CString strTableName)		//Table 생성이 성공하면 TRUE, 실패하면 FALSE
{

	CDaoTableDef	*pTableDef;
	pTableDef	= new CDaoTableDef(pdao);

	try//테이블 생성
	{
		pTableDef->Create( strTableName );
	}
	catch(CDaoException &ex)
	{
		AfxMessageBox("데이타베이스 테이블 생성 실패");
		delete pTableDef;

		return false;
	}
	catch(CMemoryException &ex)
	{ 
		//ex.GetErrorMessage()
		AfxMessageBox("데이타베이스 테이블 메모리 로드 실패");
		delete pTableDef;

		return false;
	}
		
	delete pTableDef;

	return true;
}


bool CFunc_DB_Dao::f_table_create  (CString strFilename, CString strTableName)			// $ Add 2015.04.20 Table 생성이 성공하면 TRUE, 실패하면 FALSE
{
    CDaoDatabase* pDatabase = NULL;
    CDaoTableDef* pTableDef = NULL;
	CDaoTableDefInfo TableInfo;

	CString strTemp;

	bool  bRtn = false;

	TRY
	{
		//db open
		pDatabase = new CDaoDatabase;
		pDatabase->Open(strFilename);

		pTableDef = new CDaoTableDef(pDatabase);
			
		pTableDef->Create(strTableName);

		bRtn = true;

	}
    CATCH (CException, e) //예외처리 : 정확히는 CDaoException이지만 어짜피 CException 상속 클래스임.
    {
        TCHAR szCause[256];
        e->GetErrorMessage(szCause, 256);
        AfxMessageBox(szCause, MB_ICONERROR);
		
		bRtn = false;
    }
    END_CATCH

	if (pTableDef != NULL)
	{
		if (pTableDef->IsOpen() )
			pTableDef->Close();

		delete pTableDef;
		pTableDef = NULL;
	}

	if (pDatabase != NULL)
	{
		if (pDatabase->IsOpen() )
			pDatabase->Close();

		delete pDatabase;
		pDatabase = NULL;
	}


	return bRtn;




}


unsigned CFunc_DB_Dao::f_table_isExist_yesno (CDaoDatabase* pdao, CString strTableName)
{
	int tablecnt = pdao->GetTableDefCount();

	CDaoTableDefInfo	tableDefInfo;
	CString				strTemp;

	int iRtn = ret_yesno::no;

	TRY
	{
		for (int i=0; i<tablecnt; i++)
		{
	
			pdao->GetTableDefInfo(i, tableDefInfo, AFX_DAO_ALL_INFO);
			strTemp = tableDefInfo.m_strName;

			if ( 0 == strTableName.CompareNoCase(strTemp) )
			{
				iRtn = ret_yesno::yes;
				break;
			}
		}
	}
    CATCH (CException, e) //예외처리 : 정확히는 CDaoException이지만 어짜피 CException 상속 클래스임.
    {
        TCHAR szCause[256];
        e->GetErrorMessage(szCause, 256);
        AfxMessageBox(szCause, MB_ICONERROR);

		iRtn = ret_yesno::fail;
    }
    END_CATCH


	return iRtn;
}


bool  CFunc_DB_Dao::f_field_Create_dbText (CDaoTableDef* pTableDef, CString strFieldName,  bool bZeroSizeAllow, long lSize, long lAttributes )
{
	CDaoFieldInfo wfinfo;

	wfinfo.m_strName			= strFieldName;
	wfinfo.m_nType				= dbText;
	wfinfo.m_lSize				= lSize;
	wfinfo.m_bAllowZeroLength	= bZeroSizeAllow;   ///////
	wfinfo.m_lAttributes		= lAttributes;

	wfinfo.m_bRequired = FALSE;
	wfinfo.m_nOrdinalPosition = 0;
	wfinfo.m_lCollatingOrder = 0;
	wfinfo.m_strForeignName = _T("");
	wfinfo.m_strSourceField = _T("");
	wfinfo.m_strSourceTable = _T("");
	wfinfo.m_strValidationRule = _T("");
	wfinfo.m_strValidationText = _T("");
	wfinfo.m_strDefaultValue = _T("");
	
	try
	{
		pTableDef->CreateField( wfinfo );	// $ 2015-03-05 <-- dbBoolean , 1 
		//CDaoFieldInfo rfinfo;
		//pTableDef->GetFieldInfo(strFieldName , rfinfo, AFX_DAO_PRIMARY_INFO );	// $ 2015-03-05 <-- dbBoolean , 1 
	}
	catch(CDaoException &ex)
	{
		CString strMsg;
		
		strMsg.Format("데이타베이스 필드 생성 실패, Field = %s",  strFieldName.GetString());
		AfxMessageBox(strMsg);

		return FALSE;
	}

	return TRUE;
}

