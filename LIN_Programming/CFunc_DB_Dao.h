#pragma once

#include "afxdao.h"
#pragma warning(disable:4995) 

#include "CTest_State.h"

class CFunc_DB_Dao
{
public:
	CFunc_DB_Dao(void);
	~CFunc_DB_Dao(void);

	unsigned	f_table_isExist_yesno  (CDaoDatabase* pdao, CString strTableName);		// $ Add 2015.04.20 Table이 있으면 TRUE, ,읽는데 실패하거나 테이블이 없으면 FALSE
	bool		f_table_create             (CDaoDatabase* pdao, CString strTableName);		// $ Add 2015.04.20 Table 생성이 성공하면 TRUE, 실패하면 FALSE
	
	unsigned	f_table_isExist_yesno  (CString strFilename, CString strTableName);			// $ Add 2015.04.20 Table이 있으면 TRUE, ,읽는데 실패하거나 테이블이 없으면 FALSE
	bool		f_table_create             (CString strFilename, CString strTableName);			// $ Add 2015.04.20 Table 생성이 성공하면 TRUE, 실패하면 FALSE

	
	bool		f_field_check_exist_and_create_with_initial_value (CDaoDatabase* pdao, CString strTablename, CString strFieldname, int fieldType, long fieldSize, long attributes = 0);

	bool		f_field_create  (CString strFilename, CString strTablename, CString strFieldname, int fieldType, long fieldSize, long attributes = 0);
	bool		f_field_create  (CDaoDatabase* pdao, CString strTablename, CString strFieldname, int fieldType, long fieldSize, long attributes = 0);
	bool		f_field_create  (CDaoTableDef* pTableDef, CString strFieldname, int fieldType, long fieldSize, long attributes = 0);

	unsigned	f_field_isExist_yesno (CDaoDatabase* pdao,  CString strTableName, CString strFieldName);
	unsigned	f_field_isExist_yesno (CString strFilename, CString strTableName, CString strFieldName);
	unsigned	f_field_isExist_yesno (CDaoTableDef* pTableDef, CString strFieldName);

	bool		f_field_Create_dbText (CDaoTableDef* pTableDef, CString strFieldName,  bool bZeroSizeAllow, long lSize, long lAttributes = 0 );

};

