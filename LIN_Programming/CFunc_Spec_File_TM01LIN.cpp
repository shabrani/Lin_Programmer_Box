#include "stdafx.h"
#include "CFunc_Spec_File.h"
#include "CTest_Main.h"
#include "CFunc_BackupFile.h"


extern CTest_Main	*pTest;
using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define    DBTABLE_DATABASE_FORM_REV_NO					"DATABASE_FORM_REV_NO"     

#define    DATABASE_TEST_ITEM							"TM01LIN"
#define    DATABASE_REV_MAIN_NO							2
#define    DATABASE_REV_SUB_NO                          1
#define    DATABASE_REV_DATE                            "2017-12-19"
#define    DATABASE_REV_NOTE                            "TESTSPEC_MAIN->50_RETEST_INDEX추가"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		TM01LIN_CSPEC_TESTPROC_NAME					"TM01LIN"
#define		TM01LIN_CSPEC_TESTPROC_REVNO				0
#define		TM01LIN_CSPEC_TESTPROC_REVDATE				"2015-03-02"

#define		TM01LIN_DBTABLE_SPECINFO_HEADER				"SPECINFO_HEADER"
#define		TM01LIN_DBTABLE_SPECINFO_HDLR				"SPECINFO_HANDLER"
#define		TM01LIN_DBTABLE_SPECINFO_LIN				"SPECINFO_LIN"

#define		TM01LIN_DBTABLE_TESTSPEC_MAIN				"TESTSPEC_MAIN"
#define		TM01LIN_DBTABLE_TESTSPEC_MAIN_GROUP			"TESTSPEC_MAIN_GROUP_ITEM"
#define		TM01LIN_DBTABLE_TESTCOND_LIN				"TESTCOND_LIN"

#define		DBTABLE_DATABASE_FORM_REVNO					"DATABASE_FORM_REVNO"





bool CFunc_Spec_File::f_extract_CSpec_from_SFile (CString sFilename)
{
    CString sSql;
    CString sDriver;
    CString sDsn;
	
	TS_CSPEC_FIELD				buf_recd;

	std::vector<TS_CSPEC_FIELD>		vec_proc;
	std::vector<TS_CSPEC_FIELD>		vec_spec;

	CString sField, sData;

	CDatabase database;
	CDBVariant varValue;
    sDriver = "MICROSOFT ACCESS DRIVER (*.MDB)";

    if(sDriver.IsEmpty())
    {
        AfxMessageBox("No ACCESS ODBC driver found");
		return false;
    }
    
     sDsn.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s",sDriver, sFilename );

    TRY
    {
        unsigned rtn = database.Open(NULL,false,false,sDsn);
		if (rtn == 0)
		{
			database.Close();

			AfxMessageBox("Fail Database Open");
			return false;
		}



		if (false == f_extract_SpecInfo_HEADER_from_CDatabase(database) ) 
		{
			database.Close();
			return false;
		}

		if (false == f_extract_SpecInfo_LIN_from_CDatabase(database) ) 
		{
			database.Close();
			return false;
		}

		if (false == f_extract_SpecInfo_HDLR_from_CDatabase(database) ) 
		{
			database.Close();
			return false;
		}


		CString sPName;
		sPName = m_pCSpec->m_stSpecInfo.tproc.strProcName;
		if ( sPName.CompareNoCase( TM01LIN_CSPEC_TESTPROC_NAME ) )
		{
			display_msg_for_warning ("spec Loading Error - not equal PROC_NAME");	
			database.Close();		
			return false;
		}


		if (false ==  f_extract_SpecItem_MAIN_from_CDatabase (database) )
		{
			database.Close();
			return false;
		}

		if (false ==  f_extract_SpecItem_LIN_from_CDatabase(database) )
		{
			database.Close();
			return false;
		}


		database.Close();
    }

    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		return false;
    }
    END_CATCH;


	m_pCSpec->m_stStatus.isLoading_spec = true;

	m_pCSpec->m_stStatus.strFilename = sFilename;


	return true;
}


bool CFunc_Spec_File::f_extract_SpecInfo_HEADER_from_CDatabase (CDatabase &database)
{
	CString buf;

	TS_CSPEC_FIELD				buf_recd;
	vector<TS_CSPEC_FIELD>		vec_proc;

	CString		sSql;
	sSql.Format ( "SELECT * FROM %s", TM01LIN_DBTABLE_SPECINFO_HEADER );

	CRecordset recset(&database);

    TRY
    {
		recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
			
		while(!recset.IsEOF())
		{
			recset.GetFieldValue("FIELD",	buf_recd.sField);
			recset.GetFieldValue("DATA",	buf_recd.sData);
			vec_proc.push_back (buf_recd);
			
			recset.MoveNext();
		}

		recset.Close();
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;


	// Check Test name
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_CStr (vec_proc, "01_PROC_NAME",				m_pCSpec->m_stSpecInfo.tproc.strProcName	)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_u32  (vec_proc, "02_PROC_REVNO",				m_pCSpec->m_stSpecInfo.tproc.nProcRevNo		)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_CStr (vec_proc, "03_PROC_REVDATE",			m_pCSpec->m_stSpecInfo.tproc.strProcRevDate	)) return false;

	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_CStr (vec_proc, "11_SPEC_DEVICE",			m_pCSpec->m_stSpecInfo.tspec.strDeviceName	)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_CStr (vec_proc, "12_SPEC_NAME",				m_pCSpec->m_stSpecInfo.tspec.strSpecName	)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_u32  (vec_proc, "13_SPEC_REVNO",				m_pCSpec->m_stSpecInfo.tspec.nSpecRevNo		)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_CStr (vec_proc, "14_SPEC_REVDATE",			m_pCSpec->m_stSpecInfo.tspec.strSpecRevDate	)) return false;

	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_u32  (vec_proc, "21_TEST_REF_MODEL_INDEX",	m_pCSpec->m_stSpecInfo.tspec.nTestRefModel	)) return false;

	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_u32  (vec_proc, "31_SPEC_TESTITEM",			m_pCSpec->m_stStatus.nTitem					)) return false;
	
	return true;
}


bool CFunc_Spec_File::f_extract_SpecInfo_HDLR_from_CDatabase (CDatabase &database)
{
	CString buf;

	TS_CSPEC_FIELD				buf_recd;
	vector<TS_CSPEC_FIELD>		vec_proc;

	CString		sSql;
	sSql.Format ( "SELECT * FROM %s", TM01LIN_DBTABLE_SPECINFO_HDLR );

	CRecordset recset(&database);

    TRY
    {
		recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
			
		while(!recset.IsEOF())
		{
			recset.GetFieldValue("FIELD",	buf_recd.sField);
			recset.GetFieldValue("DATA",	buf_recd.sData);
			vec_proc.push_back (buf_recd);
			
			recset.MoveNext();
		}

		recset.Close();
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;



	// Check Test name
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_u32 (vec_proc, "50_PROBE",			m_pCSpec->m_stSpecInfo.Hdlr.nProbe			)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_dbl  (vec_proc, "51_PROBE_ON_DLY",	m_pCSpec->m_stSpecInfo.Hdlr.fDlyMs_ProbeOn	)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_dbl  (vec_proc, "52_PROBE_OFF_DLY",	m_pCSpec->m_stSpecInfo.Hdlr.fDlyMs_ProbeOff	)) return false;


	return true;
}


bool CFunc_Spec_File::f_extract_SpecInfo_LIN_from_CDatabase(CDatabase &database)
{
	CString buf;

	TS_CSPEC_FIELD				buf_recd;
	vector<TS_CSPEC_FIELD>		vec_proc;

	CString		sSql;
	sSql.Format ( "SELECT * FROM %s", TM01LIN_DBTABLE_SPECINFO_LIN );


	CRecordset recset(&database);

    TRY
    {
		recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
			
		while(!recset.IsEOF())
		{
			recset.GetFieldValue("FIELD",	buf_recd.sField);
			recset.GetFieldValue("DATA",	buf_recd.sData);
			vec_proc.push_back (buf_recd);
			
			recset.MoveNext();
		}

		recset.Close();
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;


	//SPECFORM REVNO가 없으면 이름을 고체한다. 
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u8 (vec_proc, "NVM_A0",	m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr00)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u8 (vec_proc, "NVM_A1",	m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr01)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u8 (vec_proc, "NVM_A2",	m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr02)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u8 (vec_proc, "NVM_A3",	m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr03)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u8 (vec_proc, "NVM_A4",	m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr04)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u8 (vec_proc, "NVM_A5",	m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr05)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u8 (vec_proc, "NVM_A6",	m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr06)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u8 (vec_proc, "NVM_A7",	m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr07)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u8 (vec_proc, "NVM_A8",	m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr08)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u8 (vec_proc, "NVM_A9",	m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr09)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u8 (vec_proc, "NVM_A10",	m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr10)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u8 (vec_proc, "NVM_A11",	m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr11)) return false;
	
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u32 (vec_proc, "FID_RX",	m_pCSpec->m_stSpecInfo.Lin.Fid.nRx)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u32 (vec_proc, "FID_TX1",	m_pCSpec->m_stSpecInfo.Lin.Fid.nTx1)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u32 (vec_proc, "FID_TX2",	m_pCSpec->m_stSpecInfo.Lin.Fid.nTx2)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u32 (vec_proc, "FID_TX3",	m_pCSpec->m_stSpecInfo.Lin.Fid.nTx3)) return false;

	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_CStr		  (vec_proc, "M_INTERFACE",	m_pCSpec->m_stSpecInfo.Lin.sInterface)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u32 (vec_proc, "M_CHIP",		m_pCSpec->m_stSpecInfo.Lin.nChip)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u32 (vec_proc, "M_REGULATOR",	m_pCSpec->m_stSpecInfo.Lin.nRegulator)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u32 (vec_proc, "M_BAUDRATE",	m_pCSpec->m_stSpecInfo.Lin.nBaudrate)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u32 (vec_proc, "M_VERSION",	m_pCSpec->m_stSpecInfo.Lin.nVersion)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_hex_to_u32 (vec_proc, "M_WAIT_TIME",	m_pCSpec->m_stSpecInfo.Lin.nWaitTime)) return false;

	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_float (vec_proc, "VOLTAGE",	m_pCSpec->m_stSpecInfo.Lin.fVoltage)) return false;
	if (true != m_odbcFunc.f_extract_SpecInfo_from_vRecord_float (vec_proc, "CURRENT",	m_pCSpec->m_stSpecInfo.Lin.fCurrent)) return false;
	return true;
}


bool CFunc_Spec_File::f_extract_SpecItem_MAIN_from_CDatabase(CDatabase &database)
{
	bool bYN;

	CString sBuf;
	CFunc_Spec_Item			temp_ftest;
	CFunc_Spec_Item*		pTitem;

	m_pCSpec->m_stStatus.nTitem	= 0; 

	m_pCSpec->m_vTitem.clear ();

	CString		sSql;	//	= "SELECT * FROM SPEC_FUNCTEST_SPEC_TESTITEM";
	sSql.Format ("SELECT * FROM %s", TM01LIN_DBTABLE_TESTSPEC_MAIN);

	CRecordset recset(&database);

    TRY
    {
		recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
			
		while(!recset.IsEOF())
		{
			m_pCSpec->f_initialize_titem_spec (temp_ftest);
			pTitem  = & temp_ftest;
	

			if (true != m_odbcFunc.f_getFieldValue_uint (recset, "PNUM",				pTitem->Spec.nPnum			)) return false;

			if (true != m_odbcFunc.f_getFieldValue_uint	(recset, "10_TEST_TESTNUM",		pTitem->Spec.nTnum			)) return false;

			if (true != m_odbcFunc.f_getFieldValue_CStr	(recset, "20_SPEC_SYMBOL",		pTitem->Spec.strTestSymbol 	)) return false;					
			if (true != m_odbcFunc.f_getFieldValue_CStr	(recset, "20_SPEC_NAME",		pTitem->Spec.strTestName 	)) return false;
			if (true != m_odbcFunc.f_getFieldValue_CStr	(recset, "20_SPEC_UINT",		pTitem->Spec.strTestUnit 	)) return false;


			if (true != m_odbcFunc.f_getFieldValue_uint	(recset, "40_MODE_LIMIT",		pTitem->Spec.stLimit.nMode)) return false;
			if (true != m_odbcFunc.f_getFieldValue_uint	(recset, "40_MODE_DATA" ,		pTitem->Spec.stDataFmt.nMode)) return false;	


	
			switch(pTitem->Spec.stDataFmt.nMode)
			{
		
			case ENUM_CSPEC_DATA_MODE::M00_DBL_DEFAULT:
				if (true != m_odbcFunc.f_getFieldValue_double(recset, "20_SPEC_LSL_DBL",pTitem->Spec.stLimit.LSL_VAR.dblVal)) return false;
				if (true != m_odbcFunc.f_getFieldValue_double(recset, "20_SPEC_HSL_DBL",pTitem->Spec.stLimit.HSL_VAR.dblVal)) return false;	
				break;
		
			default:			
				unsigned int nLSL, nHSL;
				if (true != m_odbcFunc.f_getFieldValue_uint	(recset, "20_SPEC_LSL_UINT", nLSL)) return false;			
				if (true != m_odbcFunc.f_getFieldValue_uint	(recset, "20_SPEC_HSL_UINT", nHSL)) return false;

				pTitem->Spec.stLimit.LSL_VAR.ulVal = nLSL;
				pTitem->Spec.stLimit.HSL_VAR.ulVal = nHSL;

				break;
			}

			if (true != m_odbcFunc.f_getFieldValue_uint(recset, "90_TEST_REFITEM_INDEX",pTitem->Spec.nRefTitem)) return false;


			if (true != m_odbcFunc.f_getFieldValue_CStr	(recset, "40_DATA_FORMAT",pTitem->Spec.strDataFormat)) return false;
			if(0 == strlen(pTitem->Spec.strDataFormat))
			{
				pTitem->Spec.strDataFormat = "%8.3f";
			}


			m_pCSpec->m_vTitem.push_back (temp_ftest);


			if (pTitem->Spec.nPnum >= m_pCSpec->m_stStatus.nTitem)
			{
				m_pCSpec->m_stStatus.nTitem = pTitem->Spec.nPnum + 1;
			}

			
			recset.MoveNext();
		}

		recset.Close();
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;


	return true;
}


bool CFunc_Spec_File::f_extract_SpecItem_LIN_from_CDatabase  (CDatabase &database)
{
	CString sBuf;
	unsigned pnum;

	CFunc_Spec_Item* pTitem;

	CString		sSql;
	sSql.Format ("SELECT * FROM %s", TM01LIN_DBTABLE_TESTCOND_LIN);


	CRecordset recset(&database);


    TRY
    {
		recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
			
		while(!recset.IsEOF())
		{
			recset.GetFieldValue("PNUM",		sBuf);	
			pnum = atoi(sBuf);
			
			if ( pnum >= m_pCSpec->m_stStatus.nTitem) 
			{
				AfxMessageBox ("Warning DBTable.LIN Loading  : pnum is greater then SpecInfo.nTitem");	
				recset.Close();
				return true;
			}

			pTitem = &m_pCSpec->m_vTitem[pnum];


			if (true != m_odbcFunc.f_getFieldValue_uint	(recset, "300_MEAS_NVM_PARAM",		pTitem->Lin.meas_NVM_nParam	)) return false;

			recset.MoveNext();
		}

		recset.Close();
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;


	return true;
}





bool CFunc_Spec_File::f_Save_Table_SpecInfo_HEADER   (CDatabase &database)
{
	CString sDBTable;				
	CString SErrMsg;
    

    TRY
    {
		sDBTable.Format("%s", TM01LIN_DBTABLE_SPECINFO_HEADER);

		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_CStr (database,sDBTable, "01_PROC_NAME",		m_pCSpec->m_stSpecInfo.tproc.strProcName		)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint (database,sDBTable, "02_PROC_REVNO",		m_pCSpec->m_stSpecInfo.tproc.nProcRevNo			)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_CStr (database,sDBTable, "03_PROC_REVDATE",	m_pCSpec->m_stSpecInfo.tproc.strProcRevDate		)) return false;

		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_CStr (database,sDBTable, "11_SPEC_DEVICE",		m_pCSpec->m_stSpecInfo.tspec.strDeviceName		)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_CStr (database,sDBTable, "12_SPEC_NAME",		m_pCSpec->m_stSpecInfo.tspec.strSpecName		)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint (database,sDBTable, "13_SPEC_REVNO",		m_pCSpec->m_stSpecInfo.tspec.nSpecRevNo			)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_CStr (database,sDBTable, "14_SPEC_REVDATE",	m_pCSpec->m_stSpecInfo.tspec.strSpecRevDate		)) return false;

				
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint (database,sDBTable, "21_TEST_REF_MODEL_INDEX", m_pCSpec->m_stSpecInfo.tspec.nTestRefModel	)) return false;
//		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_CStr (database,sDBTable, "22_TEST_REF_MODEL_TEXT",	 m_pCSpec->m_stMode.Spec_vRefModel.f_find_sInfo(m_pCSpec->m_stSpecInfo.tspec.nTestRefModel)	)) return false;

		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint (database,sDBTable, "31_SPEC_TESTITEM",	m_pCSpec->m_stStatus.nTitem				)) return false;
    }

    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		return false;
    }
    END_CATCH;


	return true;
}


bool CFunc_Spec_File::f_Save_Table_SpecInfo_HDLR   (CDatabase &database)
{
	CString sDBTable;		
	CString SErrMsg;


    TRY
    {
		sDBTable.Format("%s", TM01LIN_DBTABLE_SPECINFO_HEADER);

		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint (database,sDBTable, "50_PROBE",					m_pCSpec->m_stSpecInfo.Hdlr.nProbe			)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_dbl  (database,sDBTable, "51_PROBE_ON_DLY",			m_pCSpec->m_stSpecInfo.Hdlr.fDlyMs_ProbeOn	)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_dbl  (database,sDBTable, "52_PROBE_OFF_DLY",			m_pCSpec->m_stSpecInfo.Hdlr.fDlyMs_ProbeOff )) return false;
    }

    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		return false;
    }
    END_CATCH;


	return true;
}


bool CFunc_Spec_File::f_Save_Table_SpecInfo_LIN (CDatabase &database)
{
 	CString sDBTable;			
	CString SErrMsg;
   

    TRY
    {
		sDBTable.Format("%s", TM01LIN_DBTABLE_SPECINFO_LIN);

		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "NVM_A0",			m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr00)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "NVM_A1",			m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr01)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "NVM_A2",			m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr02)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "NVM_A3",			m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr03)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "NVM_A4",			m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr04)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "NVM_A5",			m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr05)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "NVM_A6",			m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr06)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "NVM_A7",			m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr07)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "NVM_A8",			m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr08)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "NVM_A9",			m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr09)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "NVM_A10",			m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr10)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database,sDBTable, "NVM_A11",			m_pCSpec->m_stSpecInfo.Lin.Nvm.Addr11)) return false;

		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_CStr(database, sDBTable, "M_INTERFACE",	m_pCSpec->m_stSpecInfo.Lin.sInterface)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database, sDBTable, "M_CHIP",			m_pCSpec->m_stSpecInfo.Lin.nChip	 )) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database, sDBTable, "M_WAIT_TIME",	m_pCSpec->m_stSpecInfo.Lin.nWaitTime )) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database, sDBTable, "M_VERSION",		m_pCSpec->m_stSpecInfo.Lin.nVersion	 )) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database, sDBTable, "M_REGULATOR",	m_pCSpec->m_stSpecInfo.Lin.nRegulator)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database, sDBTable, "M_BAUDRATE",		m_pCSpec->m_stSpecInfo.Lin.nBaudrate )) return false;

		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database, sDBTable, "FID_RX",			m_pCSpec->m_stSpecInfo.Lin.Fid.nRx)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database, sDBTable, "FID_TX1",		m_pCSpec->m_stSpecInfo.Lin.Fid.nTx1)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database, sDBTable, "FID_TX2",		m_pCSpec->m_stSpecInfo.Lin.Fid.nTx2)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_uint(database, sDBTable, "FID_TX3",		m_pCSpec->m_stSpecInfo.Lin.Fid.nTx3)) return false;

		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_float(database, sDBTable, "VOLTAGE",		m_pCSpec->m_stSpecInfo.Lin.fVoltage)) return false;
		if (true != m_odbcFunc.f_SQL_Update_SpecInfo_float(database, sDBTable, "CURRENT",		m_pCSpec->m_stSpecInfo.Lin.fCurrent)) return false;

    }

    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		return false;
    }
    END_CATCH;


	return true;
}






bool CFunc_Spec_File::f_Save_CSpec_to_SFile  ()
{
    CString strSQL;
    CString sDriver;
    CString sDsn;
	CString sBuf;

	CString sField;
	CString sData;
	CString sDBTable;
					
	CString SErrMsg;


	CString		Sfilename = m_pCSpec->m_stStatus.strFilename;

	

	if (_access (Sfilename, 00 ))	
	{
		AfxMessageBox ("CSpec Save Error.. \n saveFile Not Found");
		return false;
	}

	CFunc_BackupFile Backup;
	Backup.f_create_backupfile (Sfilename);


	CDatabase database;
//	CDBVariant varValue;

    sDriver = "MICROSOFT ACCESS DRIVER (*.MDB)";
  
	
    TRY
    {

		strSQL.Format ( "DRIVER={%s};DSN='';READONLY=FALSE;DBQ=%s", 
		sDriver.GetString(), Sfilename.GetString());
		
		BOOL bRtn = database.OpenEx ( strSQL, CDatabase::noOdbcDialog);


		if( FALSE == bRtn )
		{
			AfxMessageBox( "Spec Save Error - Database File을 오픈하지 못했습니다." );

			database.Close();
			return false;
		}


		if( !this->f_Save_Table_100_SpecITem_Main  (database ) )
		{
			database.Close();

			SErrMsg.Format("SPEC SAVE ERROR - %s", "FUNCTEST_ITEM" );
			AfxMessageBox ( SErrMsg );
			return false;
		}


		if (false == this->f_Save_Table_140_SpecITem_LIN (database)  ) 
		{
			database.Close();

			SErrMsg.Format("SPEC SAVE ERROR - %s", "SAVE_SPECINFO_HEADER" );
			AfxMessageBox ( SErrMsg );
			return false;
		}





		if (false == this->f_Save_Table_SpecInfo_HEADER (database)  ) 
		{
			database.Close();

			SErrMsg.Format("SPEC SAVE ERROR - %s", "SAVE_SPECINFO_HEADER" );
			AfxMessageBox ( SErrMsg );
			return false;
		}


		if (false == this->f_Save_Table_SpecInfo_LIN    (database)  ) 
		{
			database.Close();

			SErrMsg.Format("SPEC SAVE ERROR - %s", "SAVE_SPECINFO_LIN" );
			AfxMessageBox ( SErrMsg );

			return false;
		}


		if (false == this->f_Save_Table_SpecInfo_HDLR    (database)  ) 
		{
			database.Close();

			SErrMsg.Format("SPEC SAVE ERROR - %s", "SAVE_SPECINFO_PIN" );
			AfxMessageBox ( SErrMsg );

			return false;
		}


		database.Close();
    }

    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		database.Close();
		return false;
    }
    END_CATCH;


	return true;
}


bool CFunc_Spec_File::f_Save_Table_100_SpecITem_Main (CDatabase &database)
{
	CString			strSQL;
	CString			strBuf;	
	CString			strMsg;

	int nState		=	0;

	CFunc_Spec_Item* pTitem;

	CString strTableName = TM01LIN_DBTABLE_TESTSPEC_MAIN;
	
	int pnum = 0;

	int	nFinal = m_pCSpec->m_vTitem.size ();


    TRY
    {
		{
			strBuf.Format("DELETE FROM %s", strTableName.GetString());							// Table data 초기화 (삭제)
			database.ExecuteSQL(strBuf);
		}

		for ( pnum = 0; pnum < nFinal; pnum++)
		{
			strBuf.Format("Insert Into %s (%s) values (%d)", strTableName.GetString(), "PNUM", pnum);
			database.ExecuteSQL( strBuf );
		}

		for ( pnum = 0; pnum < nFinal; pnum ++)
		{
			pTitem = &m_pCSpec->m_vTitem[pnum];
			
			strBuf.Format ("Update %s%c", TM01LIN_DBTABLE_TESTSPEC_MAIN, CH_BLANK);		strSQL =  strBuf;
			strBuf.Format ("set%c",										 CH_BLANK);		strSQL += strBuf;

	
			m_odbcFunc.f_SQL_Update_AddString_uint  (strSQL, "10_TEST_TESTNUM",	pTitem->Spec.nTnum,			CH_COMMA);				

			m_odbcFunc.f_SQL_Update_AddString_CStr  (strSQL, "20_SPEC_SYMBOL",	pTitem->Spec.strTestSymbol,	CH_COMMA);
			m_odbcFunc.f_SQL_Update_AddString_CStr  (strSQL, "20_SPEC_NAME",	pTitem->Spec.strTestName,	CH_COMMA);		
			m_odbcFunc.f_SQL_Update_AddString_CStr  (strSQL, "20_SPEC_UNIT",	pTitem->Spec.strTestUnit,	CH_COMMA);	

			switch(pTitem->Spec.stDataFmt.nMode)
			{
		
			case ENUM_CSPEC_DATA_MODE::M00_DBL_DEFAULT:
				m_odbcFunc.f_SQL_Update_AddString_double(strSQL, "20_SPEC_LSL_DBL",	pTitem->Spec.stLimit.LSL_VAR.dblVal, CH_COMMA);	
				m_odbcFunc.f_SQL_Update_AddString_double(strSQL, "20_SPEC_HSL_DBL",	pTitem->Spec.stLimit.HSL_VAR.dblVal, CH_COMMA);	
				m_odbcFunc.f_SQL_Update_AddString_uint	(strSQL, "20_SPEC_LSL_UINT",0								   , CH_COMMA);	
				m_odbcFunc.f_SQL_Update_AddString_uint	(strSQL, "20_SPEC_HSL_UINT",0								   , CH_COMMA);		
				break;
		
			default:			
				m_odbcFunc.f_SQL_Update_AddString_double(strSQL, "20_SPEC_LSL_DBL", 0								  , CH_COMMA);	
				m_odbcFunc.f_SQL_Update_AddString_double(strSQL, "20_SPEC_HSL_DBL", 0								  , CH_COMMA);	
				m_odbcFunc.f_SQL_Update_AddString_uint	(strSQL, "20_SPEC_LSL_UINT",pTitem->Spec.stLimit.LSL_VAR.ulVal, CH_COMMA);	
				m_odbcFunc.f_SQL_Update_AddString_uint	(strSQL, "20_SPEC_HSL_UINT",pTitem->Spec.stLimit.HSL_VAR.ulVal, CH_COMMA);	
				break;
			}

			m_odbcFunc.f_SQL_Update_AddString_uint   (strSQL, "40_MODE_DATA",	pTitem->Spec.stDataFmt.nMode, CH_COMMA);
			m_odbcFunc.f_SQL_Update_AddString_uint   (strSQL, "40_MODE_LIMIT",	pTitem->Spec.stLimit.nMode, CH_COMMA);	
			m_odbcFunc.f_SQL_Update_AddString_text   (strSQL, "40_DATA_FORMAT",	pTitem->Spec.strDataFormat, CH_COMMA);

			int nIndex = m_pCSpec->f_modeTable_find_vec_record (pTitem->Spec.nRefTitem, m_pCSpec->m_stMode.vInfoRefFuncTitem);

			m_odbcFunc.f_SQL_Update_AddString_uint	(strSQL, "90_TEST_REFITEM_INDEX",pTitem->Spec.nRefTitem, CH_COMMA);	
			m_odbcFunc.f_SQL_Update_AddString_text	(strSQL, "90_TEST_REFITEM_TEXT", m_pCSpec->m_stMode.vInfoRefFuncTitem[nIndex].sInfo.GetString(), CH_BLANK);

	
			strBuf.Format ("%cwhere PNUM=%d", CH_BLANK, pnum );	
			
			strSQL += strBuf;
		
			database.ExecuteSQL(strSQL.GetString());
		}
	}
    CATCH(CDBException, e)
    {
		AfxMessageBox("Database error: "+e->m_strError);
	  
		strMsg.Format("데이터 TABLE 저장중 오류가 발생하였습니다.\n table = %s",strTableName.GetString());
		AfxMessageBox(strMsg);
		return false;
    }
    END_CATCH;

	return true;
}


bool CFunc_Spec_File::f_Save_Table_140_SpecITem_LIN	(CDatabase &database)	// $ Add 2015.03.12
{
		CString		strSQL;
	CString			strBuf;	
	CString			strMsg;

	CFunc_Spec_Item* pTitem;

	int nState		=	0;

	CString strTableName = TM01LIN_DBTABLE_TESTCOND_LIN;
	
	int pnum = 0;

	int	nFinal = m_pCSpec->m_vTitem.size ();


    TRY
    {
		{
			strBuf.Format("DELETE FROM %s", strTableName.GetString());							// Table data 초기화 (삭제)
			database.ExecuteSQL(strBuf);
		}

		for ( pnum = 0; pnum < nFinal; pnum++)
		{
			strBuf.Format("Insert Into %s (%s) values (%d)", strTableName.GetString(), "PNUM", pnum);
			database.ExecuteSQL( strBuf );
		}

		for ( pnum = 0; pnum < nFinal; pnum ++)
		{
				pTitem = &m_pCSpec->m_vTitem[pnum];

				strBuf.Format ("Update %s%c", TM01LIN_DBTABLE_TESTCOND_LIN,	CH_BLANK);		strSQL =  strBuf;
				strBuf.Format ("set%c",										CH_BLANK);		strSQL += strBuf;

				
				m_odbcFunc.f_SQL_Update_AddString_double (strSQL, "200_SEND_REP_TIME_MS",	pTitem->Lin.SendMsg_fRepeatSendTime_Ms, CH_COMMA);	
				m_odbcFunc.f_SQL_Update_AddString_bool   (strSQL, "200_SEND_REP_TIME_YN",	pTitem->Lin.SendMsg_bRepeatSend		  , CH_COMMA);	
				m_odbcFunc.f_SQL_Update_AddString_uint	 (strSQL, "300_MEAS_NVM_PARAM",		pTitem->Lin.meas_NVM_nParam			  , CH_BLANK);


				strBuf.Format ("%cwhere PNUM=%d", CH_BLANK, pnum );
				
				strSQL += strBuf;
		
				database.ExecuteSQL( strSQL.GetString() );
		}


	}
    CATCH(CDBException, e)
    {
		AfxMessageBox("Database error: "+e->m_strError);
	  
		strMsg.Format("데이터베이스 TABLE 저장중 오류가 발생하였습니다.\n table = %s",strTableName.GetString());
		AfxMessageBox(strMsg);
		return false;
    }
    END_CATCH;

	return true;
}
