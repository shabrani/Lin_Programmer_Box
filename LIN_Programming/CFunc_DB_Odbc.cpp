#include "stdafx.h"
#include "CFunc_DB_Odbc.h"


CFunc_DB_Odbc::CFunc_DB_Odbc(void)
{
}


CFunc_DB_Odbc::~CFunc_DB_Odbc(void)
{
}



void  CFunc_DB_Odbc::f_SQL_Update_AddString_CStr (CString &sSQL, const char *szField, const CString &sData,	const char charSeperator )
{

	CString sBuf;
	sBuf.Format ("%s='%s'%c",	szField, sData.GetString(), charSeperator	);	sSQL += sBuf;

}



void  CFunc_DB_Odbc::f_SQL_Update_AddString_text (CString &sSQL, const char *szField, const char *szData, const char charSeperator )
{
	CString sBuf;
	sBuf.Format ("%s='%s'%c",	szField, szData, charSeperator	);	sSQL += sBuf;
}

void  CFunc_DB_Odbc::f_SQL_Update_AddString_uint (CString &sSQL, const char *szField, unsigned uData,  const char charSeperator)
{
	CString sBuf;
	sBuf.Format ("%s=%d%c",	szField, uData, charSeperator	);	sSQL += sBuf;
}

//void CFunc_DB_Odbc::f_SQL_Update_AddString_ulong	(CString &sSQL, const char *szField, unsigned long long uData,		const char charSeperator )
//{
//	CString sBuf;
//	sBuf.Format ("%s=%d%c",	szField, uData, charSeperator	);	sSQL += sBuf;
//}

void  CFunc_DB_Odbc::f_SQL_Update_AddString_bool (CString &sSQL, const char *szField, bool         bData,  const char charSeperator )
{
	CString sBuf;
			sBuf.Format ("%s=%d%c",	szField, (bData) ? 1 : 0, charSeperator );	sSQL += sBuf;
}

void  CFunc_DB_Odbc::f_SQL_Update_AddString_double (CString &sSQL, const char *szField, double fData,  const char charSeperator)
{
	CString sBuf;
	sBuf.Format ("%s=%f%c",	szField, fData, charSeperator	);	sSQL += sBuf;
}



bool CFunc_DB_Odbc::f_SQL_Update_SpecInfo_Record(CDatabase &database, const char *szDBTable, const char *szField, const char *szData)
{
	CString sBuf, sSQL;

    TRY
    {
		sBuf.Format ("Update %s%c",			szDBTable, CH_BLANK);	sSQL =  sBuf;
		sBuf.Format ("set%c",				CH_BLANK );				sSQL += sBuf;
		sBuf.Format ("DATA='%s'",			szData);				sSQL += sBuf;
		sBuf.Format ("%cwhere FIELD='%s'",  CH_BLANK, szField);		sSQL += sBuf;		
		database.ExecuteSQL(sSQL);
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
					
		CString SErrMsg;
		SErrMsg.Format("SPEC SAVE ERROR - %s", szField );
		AfxMessageBox ( SErrMsg );

		database.Close();
		return false;
    }
    END_CATCH;

	return true;
}


bool CFunc_DB_Odbc::f_SQL_Update_SpecInfo_CStr	  (CDatabase &database, const char *szDBTable, const char *szField, CString sData  )
{
	//CString sData;
	//sData.Format ("%s", szData);
	return f_SQL_Update_SpecInfo_Record(database, szDBTable, szField, sData);
}


bool CFunc_DB_Odbc::f_SQL_Update_SpecInfo_uint(CDatabase &database, const char *szDBTable, const char *szField, unsigned uData)
{
	CString sData;
	sData.Format ("%d", uData);
	return f_SQL_Update_SpecInfo_Record(database, szDBTable, szField, sData);
}

	bool CFunc_DB_Odbc::f_SQL_Update_SpecInfo_u32_to_hex (CDatabase &database, const char *szDBTable, const char *szField, UINT32 uData	 )
{
	CString sData;
	sData.Format ("0x%08X", uData);

	return f_SQL_Update_SpecInfo_Record(database, szDBTable, szField, sData);
}
bool CFunc_DB_Odbc::f_SQL_Update_SpecInfo_u16_to_hex (CDatabase &database, const char *szDBTable, const char *szField, UINT16 uData	 )
{
	CString sData;
	sData.Format ("0x%04X", uData);

	return f_SQL_Update_SpecInfo_Record(database, szDBTable, szField, sData);
}



bool CFunc_DB_Odbc::f_SQL_Update_SpecInfo_u08_to_hex (CDatabase &database, const char *szDBTable, const char *szField, UINT8  uData	 )
{
	CString sData;
	sData.Format ("0x%02X", uData);

	return f_SQL_Update_SpecInfo_Record(database, szDBTable, szField, sData);
}

bool CFunc_DB_Odbc::f_SQL_Update_SpecInfo_u08_to_hex(CDatabase &database, const char *szDBTable, const char *szField, UINT32  uData)
{
	CString sData;
	sData.Format("0x%02X", uData & 0xff);

	return f_SQL_Update_SpecInfo_Record(database, szDBTable, szField, sData);
}


/*
bool CFunc_DB_Odbc::f_SQL_Update_SpecInfo_ulong(CDatabase &database, const char *szDBTable, const char *szField, unsigned long long uData)
{
	CString sData;
	sData.Format ("%d", uData);
	return f_SQL_Update_SpecInfo_Record(database, szDBTable, szField, sData);
}
*/

bool CFunc_DB_Odbc::f_SQL_Update_SpecInfo_float (CDatabase &database, const char *szDBTable, const char *szField, float fData)
{
	CString sData;
	sData.Format ("%f", fData);
	return f_SQL_Update_SpecInfo_Record(database, szDBTable, szField, sData);
}


bool CFunc_DB_Odbc::f_SQL_Update_SpecInfo_dbl (CDatabase &database, const char *szDBTable, const char *szField, double fData)
{
	CString sData;
	sData.Format ("%f", fData);
	return f_SQL_Update_SpecInfo_Record(database, szDBTable, szField, sData);
}

bool CFunc_DB_Odbc::f_SQL_Update_SpecInfo_bool (CDatabase &database, const char *szDBTable, const char *szField, bool bData)
{
	CString sData;
	sData.Format ("%d", bData);
	return f_SQL_Update_SpecInfo_Record(database, szDBTable, szField, sData);
}

	





/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		검사규격을 불러 옵니다. 
//
////////////////////////////////////////////////////////////////////////////////////////////////////

bool CFunc_DB_Odbc::f_getFieldValue_CStr	(CRecordset &recset, char *field, CString &sData)
{
	TRY
    {
		recset.GetFieldValue(field,		sData);
		return true;
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;

}

bool CFunc_DB_Odbc::f_getFieldValue_byte  (CRecordset &recset, char *field, unsigned char &byteData)
{
	CString sBuf;

	TRY
    {
		recset.GetFieldValue(field,		sBuf);
		byteData = atoi(sBuf) & 0x00ff;
		return true;
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;
}

bool CFunc_DB_Odbc::f_getFieldValue_uint  (CRecordset &recset, char *field, unsigned  &uData)
{
	CString sBuf;

	TRY
    {
		recset.GetFieldValue(field,		sBuf);
		uData = atoi(sBuf);
		return true;
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;
}

bool CFunc_DB_Odbc::f_getFieldValue_uint16  (CRecordset &recset, char *field, unsigned short &uData)
{
	CString sBuf = "";

	TRY
    {
		recset.GetFieldValue(field,		sBuf);
		uData = atoi(sBuf);
		return true;
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;
}


bool CFunc_DB_Odbc::f_getFieldValue_ulong  (CRecordset &recset, char *field, unsigned  long &uData)
{
	CString sBuf = "";

	TRY
    {
		recset.GetFieldValue(field,		sBuf);
		uData = atoi(sBuf);
		return true;
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;
}

/*
bool CFunc_DB_Odbc::f_getFieldValue_udlong	(CRecordset &recset, char *field, unsigned long long &uData)
{
	CString sBuf = "";

	TRY
    {
		recset.GetFieldValue(field,		sBuf);
		uData = atoi(sBuf);
		return true;
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;
}
*/

bool CFunc_DB_Odbc::f_getFieldValue_double (CRecordset &recset, char *field, double    &fData)
{
	CString sBuf = "";

	TRY
    {
		recset.GetFieldValue(field,		sBuf);
		fData = atof(sBuf);
		return true;
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;
}


bool CFunc_DB_Odbc::f_getFieldValue_bool  (CRecordset &recset, char *field, bool      &bData)
{
	CString sBuf = "";

	TRY
    {
		recset.GetFieldValue(field,		sBuf);
		( atoi(sBuf) )? bData = true:bData = false;
		return true;
	}
    CATCH(CDBException, e)
    {
        AfxMessageBox("Database error: "+e->m_strError);
		recset.Close();
		return false;
    }
    END_CATCH;
}


bool CFunc_DB_Odbc::f_extract_SpecInfo_from_vRecord (std::vector<TS_CSPEC_FIELD> &vec,  char *ref, CString &buf)
{
	
	unsigned vec_size = vec.size();

	for (unsigned i= 0; i < vec_size; ++i)
	{

		vec[i].sField.Remove(CH_TAB);
		vec[i].sField.Remove(CH_BLANK);

		if (0 == vec[i].sField.CompareNoCase (ref))
		{
			buf = vec[i].sData;
			return true;
		}
	}
	return false;
}


bool CFunc_DB_Odbc::f_extract_SpecInfo_from_vRecord_dbl	(std::vector<TS_CSPEC_FIELD> &vec, char *ref, double  &fData)
{
	CString buf;

	if (f_extract_SpecInfo_from_vRecord (vec, ref, buf) )  	
	{	
		fData = atof (buf.GetString() );
	}	
	else  
	{
		char msg[128];
		sprintf_s (msg, "spec header loading error - %s - ", ref);
		
		AfxMessageBox (msg);	
		return false;		
	}


	return true;
}

bool CFunc_DB_Odbc::f_extract_SpecInfo_from_vRecord_float	(std::vector<TS_CSPEC_FIELD> &vec, char *ref, float &fData)
{
	CString buf;

	if (f_extract_SpecInfo_from_vRecord (vec, ref, buf) )  	
	{	
		fData = float(atof (buf.GetString() ));
	}	
	else  
	{
		char msg[128];
		sprintf_s (msg, "spec header loading error - %s - ", ref);
		
		AfxMessageBox (msg);	
		return false;		
	}

	return true;
}



bool CFunc_DB_Odbc::f_extract_SpecInfo_from_vRecord_bool	(std::vector<TS_CSPEC_FIELD> &vec, char *ref, bool   &bData)
{
	CString buf;

	if (f_extract_SpecInfo_from_vRecord (vec, ref, buf) )  	
	{	
		unsigned i = atoi (buf.GetString() );

		bData = i ? true:false;
	}	
	else  
	{
		char msg[128];
		sprintf_s (msg, "spec header loading error - %s - ", ref);
		
		AfxMessageBox (msg);	

		return false;		
	}

	return true;
}

bool CFunc_DB_Odbc::f_extract_SpecInfo_from_vRecord_u8		(std::vector<TS_CSPEC_FIELD> &vec, char *ref, UINT8  &u8)
{
	CString buf;

	if (f_extract_SpecInfo_from_vRecord (vec, ref, buf) )  	
	{	
		u8 = (unsigned char) (0xff & strtoul (buf.GetString(), NULL, 10) );
	}	
	else  
	{
		char msg[128];
		sprintf_s (msg, "spec header loading error - %s - ", ref);
		
		AfxMessageBox (msg);	
		return false;		
	}

	return true;
}

bool CFunc_DB_Odbc::f_extract_SpecInfo_from_vRecord_hex_to_u8		(std::vector<TS_CSPEC_FIELD> &vec, char *ref, UINT8  &u8)
{
	CString buf;

	if (f_extract_SpecInfo_from_vRecord (vec, ref, buf) )  	
	{	
		u8 = (unsigned char) (0xff & strtoul (buf.GetString(), NULL, 16) );
	}	
	else  
	{
		char msg[128];
		sprintf_s (msg, "spec header loading error - %s - ", ref);
		
		AfxMessageBox (msg);	
		return false;		
	}

	return true;
}

bool CFunc_DB_Odbc::f_extract_SpecInfo_from_vRecord_u16		(std::vector<TS_CSPEC_FIELD> &vec, char *ref, UINT16  &u16)
{
	CString buf;

	if (f_extract_SpecInfo_from_vRecord (vec, ref, buf) )  	
	{	
		u16 = (unsigned short)	( 0xffff & strtoul (buf.GetString(), NULL, 10) );
	}	
	else  
	{
		char msg[128];
		sprintf_s (msg, "spec header loading error - %s - ", ref);
		
		AfxMessageBox (msg);	
		return false;		
	}

	return true;
}

bool CFunc_DB_Odbc::f_extract_SpecInfo_from_vRecord_hex_to_u16		(std::vector<TS_CSPEC_FIELD> &vec, char *ref, UINT16  &u16)
{
	CString buf;

	if (f_extract_SpecInfo_from_vRecord (vec, ref, buf) )  	
	{	
		u16 = (unsigned short)	( 0xffff & strtoul (buf.GetString(), NULL, 16) );
	}	
	else  
	{
		char msg[128];
		sprintf_s (msg, "spec header loading error - %s - ", ref);
		
		AfxMessageBox (msg);	
		return false;		
	}

	return true;
}


bool CFunc_DB_Odbc::f_extract_SpecInfo_from_vRecord_u32		(std::vector<TS_CSPEC_FIELD> &vec, char *ref, UINT32  &u32)
{
	CString buf;

	if (f_extract_SpecInfo_from_vRecord (vec, ref, buf) )  	
	{	
		//u32 = (unsigned)atoi (buf.GetString() );
		u32 = strtoul (buf.GetString(), NULL, 10);
	}	
	else  
	{
		char msg[128];
		sprintf_s (msg, "spec header loading error - %s - ", ref);
		
		AfxMessageBox (msg);	
		return false;		
	}

	return true;
}

bool CFunc_DB_Odbc::f_extract_SpecInfo_from_vRecord_hex_to_u32		(std::vector<TS_CSPEC_FIELD> &vec, char *ref, UINT32  &u32)
{
	CString buf;

	if (f_extract_SpecInfo_from_vRecord (vec, ref, buf) )  	
	{	
		//u32 = (unsigned)atoi (buf.GetString() );
		u32 = strtoul (buf.GetString(), NULL, 16);
	}	
	else  
	{
		char msg[128];
		sprintf_s (msg, "spec header loading error - %s - ", ref);
		
		AfxMessageBox (msg);	
		return false;		
	}

	return true;
}



/*
bool CFunc_DB_Odbc::f_extract_SpecInfo_from_vRecord_u32	  (std::vector<TS_CSPEC_FIELD> &vec, char *ref, unsigned int  &iIntData)
{
	CString buf;

	if (f_extract_SpecInfo_from_vRecord (vec, ref, buf) )  	
	{	
		iIntData = atoi (buf.GetString() );
	}	
	else  
	{
		char msg[128];
		sprintf_s (msg, "spec header loading error - %s - ", ref);
		
		AfxMessageBox (msg);	
		return false;		
	}

	return true;
}

*/


bool CFunc_DB_Odbc::f_extract_SpecInfo_from_vRecord_CStr     (std::vector<TS_CSPEC_FIELD> &vec,  char *ref, CString &sBuf)
{
	CString buf;

	if (f_extract_SpecInfo_from_vRecord (vec, ref, buf) )  	
	{	
		sBuf = buf;

	}	
	else  
	{
		char msg[128];
		sprintf_s (msg, "spec header loading error - %s - ", ref);
		
		AfxMessageBox (msg);	
		return false;		
	}

	return true;
}
