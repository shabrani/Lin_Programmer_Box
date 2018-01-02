#pragma once

#include "CFunc_Spec.h"
#include "CFunc_DB_Odbc.h"
#include "CFunc_DB_Dao.h"


#define   DBFORM_SPECITEM		"TM02VR"
#define   DBFORM_REV_NO_MAIN	5
#define	  DBFORM_REV_NO_SUB		4
#define	  DBFORM_REV_DATE		"2015-04-20"
#define	  DBFORM_REV_NOTE		"-"



class CFunc_Spec_File
{
public:
	CFunc_Spec_File(CFunc_Spec *pCSpec);
	~CFunc_Spec_File(void);

	CFunc_Spec			*m_pCSpec;
	CFunc_DB_Odbc		m_odbcFunc;
	CFunc_DB_Dao 		m_daoFunc;

	struct
	{
		bool		bExist_DBFORMTable;
		CString		strSpecItem;
		unsigned	nRevMainNo;
		unsigned	nRevSubNo;
	}m_dbform;



	bool f_SpecFile_Load       (CTest_State *ts, unsigned nVersion = 0);
	bool f_specFile_Form_Update(CString sFilename);

	bool f_SpecFile_LoadSpec_set_Data_Initialize();



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//			DB Form Upgrade
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool f_DBForm_Upgrade_v5003_to_v5004(CString sFilename);	//Retest기능 항목 추가		//$ Add 2015.04.23

	bool f_DBForm_Info_extract	(CString strFilename);
	bool f_DBForm_Info_extract	(CDatabase &database);
	bool f_DBForm_Info_update   (CString strFilename);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		TM02H Spec Save
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool f_Save_CSpec_to_SFile();

	bool f_Save_Table_100_SpecITem_Main			(CDatabase &database);	// $ Add 2015.03.12
	bool f_Save_Table_140_SpecITem_LIN			(CDatabase &database);

	bool f_Save_Table_SpecInfo_HEADER			(CDatabase &database);
	bool f_Save_Table_SpecInfo_HDLR				(CDatabase &database);
	bool f_Save_Table_SpecInfo_LIN				(CDatabase &database);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		TM01LIN Spec Load 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool f_extract_CSpec_from_SFile   (CString sFilename);

	bool f_extract_SpecInfo_HEADER_from_CDatabase	(CDatabase &database);
	bool f_extract_SpecInfo_HDLR_from_CDatabase		(CDatabase &database);
	bool f_extract_SpecInfo_LIN_from_CDatabase		(CDatabase &database);

	bool f_extract_SpecItem_MAIN_from_CDatabase		(CDatabase &database);
	bool f_extract_SpecItem_LIN_from_CDatabase		(CDatabase &database);

};

