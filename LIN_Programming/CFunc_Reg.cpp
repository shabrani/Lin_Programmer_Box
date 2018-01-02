// CFunc_Reg.cpp: implementation of the CFunc_RegBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CFunc_Reg.h"

#include "CTest_System_Config.h"
#include <string>
#include "CFunc_FilePath.h"


/////////////////////////////////////////////////////////////////////////

#define REG_SUBKEY_TESTPROG				"testprog"

#define REGI_VALNAME_PASSWORD				"PASSWORD"
#define	REGIDEF_PASSWORD				"password"

//SPEC EDIT PROG
#define REGI_VALNAME_PROGRAM_SPECEDIT		"PROGRAM_SPECEDIT"
#define REGIDEF_PROGRAM_SPECEDIT		""

//DATA FILE PATH
#define REGI_VALNAME_BASEPATH_DATAFILE		"BASEPATH_DATAFILE"
#define REGIDEF_BASEPATH_DATAFILE		""

//DATA PROCESS PROGRAM
#define REGI_VALNAME_PROGRAM_DATAREPORT		"PROGRAM_DATAREPORT"
#define REGIDEF_PROGRAM_DATAREPORT		""

#define REG_SUBKEY_TESTSPEC			    "specpath"

//SPEC EDIT PROG
#define REGI_VALNAME_FILENAME_DEFAULT_TINF	"FILENAME_DEFAULT_TINF"
#define REGIDEF_FILENAME_DEFAULT_TINF	""

//SPEC EDIT PROG
#define REGI_VALNAME_BASEPATH_TINF			"BASEPATH_TINF"
#define REGIDEF_BASEPATH_TINF			""

//SPEC EDIT PROG
#define REGI_VALNAME_FILENAME_ADDRESS_MAP	"FILENAME_ADDRESS_MAP"
#define REGIDEF_FILENAME_ADDRESS_MAP	""

#define REGI_VALNAME_QTY_TOTAL_TESTNUM_PASS		"QTY_TOTAL_TESTNUM_PASS"
#define REGI_VALNAME_QTY_TOTAL_TESTNUM_FAIL		"QTY_TOTAL_TESTNUM_FAIL"
#define REGI_VALNAME_QTY_TOTAL_TESTNUM_SAVETIME	"QTY_TOTAL_TESTNUM_SAVETIME"

#define REGI_VALNAME_SAVEDATAFOLD_FOLDNUM		"SAVEDATAFOLD_FOLDNUM"
#define REGI_VALNAME_SAVEDATAFOLD_ISFOLD			"SAVEDATAFOLD_ISFOLD"

#define REGI_VALNAME_COMPANY_NAME				"COMPANY NAME"
#define REGIDEF_COMPANY_NAME				""
#define REGI_VALNAME_DIVISION_NAME				"DIVISION NAME"
#define REGIDEF_DIVISION_NAME				""


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFunc_RegBase::CFunc_RegBase(HKEY hKey, LPCTSTR Subkey)
{
	RegCreateKeyEx (hKey, Subkey, 0, NULL, 
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &m_key, &m_dwDisp);
}

CFunc_RegBase::~CFunc_RegBase()
{
	RegCloseKey (m_key);
}

void CFunc_RegBase::save  (LPCTSTR lpValue, LPCTSTR lpData)
{
	RegSetValueEx (m_key, lpValue, 0, REG_SZ, (LPBYTE)lpData, strlen(lpData) + 1 );

}

LPCTSTR CFunc_RegBase::read (LPCTSTR lpValue, LPCTSTR lpDefaultString)
{
	DWORD Size = MAX_PATH;

	unsigned long lValueType = (LONG)REG_SZ;

	if (RegQueryValueEx(m_key, lpValue, 0, NULL, (LPBYTE)m_szBuf, &Size) != ERROR_SUCCESS) 
		strncpy_s (m_szBuf, lpDefaultString, MAX_PATH);

	return (LPCTSTR)m_szBuf;
}

//////////////////////////////////////////////////////////////////////
// CFunc_RegUser Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// CFunc_RegUser Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFunc_RegUser::CFunc_RegUser(LPCTSTR Subkey)
{
//	CTest_System_Build_History system;

    char szBuf[256];
	wsprintf (szBuf, "software\\%s\\%s", SYSTEM_MODEL_NO_STRING, Subkey);

	RegCreateKeyEx (HKEY_CURRENT_USER, szBuf, 0, NULL, 
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &m_key, &m_dwDisp);
}

CFunc_RegUser::~CFunc_RegUser()
{
	RegCloseKey (m_key);
}

//////////////////////////////////////////////////////////////////////////////

void CFunc_RegUser::save_CString(const CString strValueName, const CString strWriteData)
{
	RegSetValueEx(m_key, (LPCTSTR)strValueName.GetString(), 0, REG_SZ, (LPBYTE)strWriteData.GetString(), strWriteData.GetLength());
}

void CFunc_RegUser::read_CString(const CString strValueName, CString &strReadData, const CString strDefaultReadData)
{
	DWORD Size = MAX_PATH;
	unsigned long lValueType = (LONG)REG_SZ;

	if (RegQueryValueEx(m_key, (LPCSTR)strValueName.GetString(), 0, NULL, (LPBYTE)m_szBuf, &Size) != ERROR_SUCCESS)
	{
		strReadData = strDefaultReadData;
	}
	else
	{
		strReadData.Format("%s", m_szBuf);
	}
}


void CFunc_RegUser::save_int  (const CString strValueName, const int nData)
{
	CString strData;

	strData.Format("%d",nData);

	save_CString(strValueName, strData);
}

void CFunc_RegUser::read_int   (const CString strValueName, int &nData, int nDefault)
{
	CString strData;

	read_CString(strValueName, strData, "");

	if (0 != strData.GetLength())
	{
		nData = atoi(strData.GetString());
	}
	else
	{
		nData = nDefault;
	}

}

void CFunc_RegUser::save_uint(const CString strValueName, const unsigned nData)
{
	CString strData;

	strData.Format("%d", nData);

	save_CString(strValueName, strData);
}

void CFunc_RegUser::read_uint(const CString strValueName, unsigned &nData, unsigned nDefault)
{
	CString strData;

	read_CString(strValueName, strData, "");

	if (0 != strData.GetLength())
	{
		nData = atoi(strData.GetString());
	}
	else
	{
		nData = nDefault;
	}

}

void CFunc_RegUser::save_bool  (const CString strValueName, const bool bData)
{
	CString strData;
	strData.Format ("%d",bData ? 1 : 0 );

	save_CString(strValueName, strData);
}

void CFunc_RegUser::read_bool   (const CString strValueName, bool &bRead, const bool bDefault)
{
	CString strData;

	read_CString(strValueName, strData, "");

	if (0 != strData.GetLength())
	{
		bRead = (0 != atoi(strData.GetString())) ? true : false;
	}
	else
	{
		bRead = bDefault;
	}

}


//	void write_bool (LPCTSTR lpValue, bool bData);
//	bool read_bool  (LPCTSTR lpValue, bool bDefault = false );

//////////////////////////////////////////////////////////////////////
// CFunc_RegMain Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFunc_RegMain::CFunc_RegMain()
{

}

CFunc_RegMain::~CFunc_RegMain()
{

}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void CFunc_RegMain::f_regiSave_Password (const CString str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_CString (REGI_VALNAME_PASSWORD, str);
}

void CFunc_RegMain::f_regiRead_Password (CString &str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_CString (REGI_VALNAME_PASSWORD, str, REGIDEF_PASSWORD);
}

///////////////////////////////////////////////////////////////////////////////////////////

void CFunc_RegMain::f_regiSave_BasePath_DataFile (const CString str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_CString (REGI_VALNAME_BASEPATH_DATAFILE, str);
}

void CFunc_RegMain::f_regiRead_BasePath_DataFile (CString &str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_CString (REGI_VALNAME_BASEPATH_DATAFILE, str, REGIDEF_BASEPATH_DATAFILE);
}


/////////////////////////////////////////////////////////////////////////////////////////////

#define REGI_VALNAME_BASEPATH_USERDATAFILE		"BASEPATH_USERDATAFILE"
#define REGIDEF_BASEPATH_USERDATAFILE		"*.xls"


void CFunc_RegMain::f_regiSave_BasePath_UserDataFile (const CString str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_CString (REGI_VALNAME_BASEPATH_USERDATAFILE, str);
}

void CFunc_RegMain::f_regiRead_BasePath_UserDataFile (CString &str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_CString (REGI_VALNAME_BASEPATH_USERDATAFILE, str, REGIDEF_BASEPATH_USERDATAFILE);
}

/////////////////////////////////////////////////////////////////////////////////////////////

void CFunc_RegMain::f_regiSave_Prog_SpecEdit (const CString str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_CString (REGI_VALNAME_PROGRAM_SPECEDIT, str);
}

void CFunc_RegMain::f_regiRead_Prog_SpecEdit (CString &str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_CString (REGI_VALNAME_PROGRAM_SPECEDIT, str, REGIDEF_PROGRAM_SPECEDIT);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

void CFunc_RegMain::f_regiSave_Prog_DataProc (const CString str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_CString (REGI_VALNAME_PROGRAM_DATAREPORT, str);
}

void CFunc_RegMain::f_regiRead_Prog_DataProc (CString &str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_CString (REGI_VALNAME_PROGRAM_DATAREPORT, str, REGIDEF_PROGRAM_DATAREPORT);
}

////////////////////////////////////////////////////////////////////////////////////////////////

//DATA FILE PATH
#define REGI_VALNAME_SPECPATH			"SPEC_PATH"

void CFunc_RegMain::f_regiSave_Path_TestSpec(const CString strPath)
{
	if (0 == strPath.GetLength()) return;

	char path[MAX_PATH] = { 0, };
	char drive[MAX_PATH] = { 0, };
	char dir[MAX_PATH] = { 0, };
	char fname[MAX_PATH] = { 0, };
	char ext[MAX_PATH] = { 0, };


	strcpy_s(path, MAX_PATH, strPath.GetString());

	_splitpath_s(path, drive, dir, fname, ext);
	_makepath_s(path, MAX_PATH, drive, dir, "*", ext);

	CFunc_RegUser Regi(REG_SUBKEY_TESTSPEC);
	Regi.save_CString(CString(REGI_VALNAME_SPECPATH), strPath);

}

void CFunc_RegMain::f_regiRead_Path_TestSpec(CString &strPath)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);
	Regi.read_CString(CString(REGI_VALNAME_SPECPATH), strPath, CString(""));
}



//////////////////////////////////////////////////////////////////////////////////////////////
//// Add 2004-08-12
void CFunc_RegMain::f_regiSave_file_default_tinf (const CString str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_CString (REGI_VALNAME_FILENAME_DEFAULT_TINF, str);
}

void CFunc_RegMain::f_regiRead_file_default_tinf (CString &str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_CString (REGI_VALNAME_FILENAME_DEFAULT_TINF, str, REGIDEF_FILENAME_DEFAULT_TINF);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//// Add 2004-08-12
void CFunc_RegMain::f_regiSave_file_address_map (const CString str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_CString (REGI_VALNAME_FILENAME_ADDRESS_MAP, str);
}

void CFunc_RegMain::f_regiRead_file_address_map (CString &str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_CString (REGI_VALNAME_FILENAME_ADDRESS_MAP, str, "");
}

//////////////////////////////////////////////////////////////////////////////////////////////

#define REGI_VALNAME_FILENAME_SYSTEM_INFO	"FILENAME_SYSTEM_INFO"
#define REGIDEF_FILENAME_SYSTEM_INFO	""

void CFunc_RegMain::f_regiSave_file_system_info (const CString str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_CString(REGI_VALNAME_FILENAME_SYSTEM_INFO, str);
}

void CFunc_RegMain::f_regiRead_file_system_info (CString &str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_CString (REGI_VALNAME_FILENAME_SYSTEM_INFO, str, REGIDEF_FILENAME_SYSTEM_INFO);
}


//////////////////////////////////////////////////////////////////////////////////////////////
//// Add 2004-08-12
void CFunc_RegMain::f_regiSave_Company_Name (const CString str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_CString (REGI_VALNAME_COMPANY_NAME, str);
}


void CFunc_RegMain::f_regiRead_Company_Name (CString &str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_CString (REGI_VALNAME_COMPANY_NAME, str, REGIDEF_COMPANY_NAME);
}

void CFunc_RegMain::f_regiSave_Division_Name (const CString str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_CString (REGI_VALNAME_DIVISION_NAME, str);
}

void CFunc_RegMain::f_regiRead_Division_Name (CString &str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_CString (REGI_VALNAME_DIVISION_NAME, str, REGIDEF_DIVISION_NAME);
}


//////////////////////////////////////////////////////////////////////////////////////////////
//// Add 2004-08-12
void CFunc_RegMain::f_regiSave_path_tinf (const CString str)
{
	if (0 == str.GetLength()) return;

	char path[MAX_PATH] = { 0, };
	char drive[MAX_PATH] = { 0, };
	char dir[MAX_PATH] = { 0, };
	char fname[MAX_PATH] = { 0, };
	char ext[MAX_PATH] = { 0, };


	strcpy_s(path, MAX_PATH, str.GetString());

	_splitpath_s( path, drive, dir, fname, ext);
	_makepath_s ( path, MAX_PATH, drive, dir, "*",   ext);

	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_CString (REGI_VALNAME_BASEPATH_TINF, path);
}

void CFunc_RegMain::f_regiRead_path_tinf (CString &str)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_CString (REGI_VALNAME_BASEPATH_TINF, str, REGIDEF_BASEPATH_TINF);
}

///////////////////////////////////////////////////////////////////////////////////////////////
//// Add 2004-08-12

void CFunc_RegMain::f_regiSave_testQty_total (const unsigned uPassTotal, const unsigned uFailTotal)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	
	Regi.save_int(REGI_VALNAME_QTY_TOTAL_TESTNUM_PASS, uPassTotal);
	Regi.save_int(REGI_VALNAME_QTY_TOTAL_TESTNUM_FAIL, uFailTotal);
}

void CFunc_RegMain::f_regiRead_testQty_total (unsigned &uPassTotal, unsigned &uFailTotal)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);

	Regi.read_uint(REGI_VALNAME_QTY_TOTAL_TESTNUM_PASS, uPassTotal, 0);
	Regi.read_uint(REGI_VALNAME_QTY_TOTAL_TESTNUM_FAIL, uFailTotal, 0);
}


#define REGI_VALNAME_TESTMODE_ENDMODE	"TESTMODE_ENGMODE"
void CFunc_RegMain::f_regiSave_testMode_EngMode (const bool bMode)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_bool(REGI_VALNAME_TESTMODE_ENDMODE, bMode);
}

void CFunc_RegMain::f_regiRead_testMode_EndMode (bool &bMode)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);
	Regi.read_bool(REGI_VALNAME_TESTMODE_ENDMODE, bMode, false);
}

// $ Change by sjkim 2012-06-21 HdlrSkip->HdlrOn
#define REGI_VALNAME_TESTMODE_HDLR_ON	"TESTMODE_HDLR_ON"


// $ Change by sjkim 2012-06-21 HdlrSkip->HdlrOn
void CFunc_RegMain::f_regiSave_testMode_HandlerOn (const bool bHdlrOn)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_bool(REGI_VALNAME_TESTMODE_HDLR_ON, bHdlrOn);
}

// $ Change by sjkim 2012-06-21 HdlrSkip->HdlrOn
void CFunc_RegMain::f_regiRead_testMode_HandlerOn (bool &bHdlrOn)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_bool(REGI_VALNAME_TESTMODE_HDLR_ON, bHdlrOn, false);
}

#define REGIVAL_TESTMODE_STOPMODE	"TESTMODE_STOPMODE"
void CFunc_RegMain::f_RegiSave_testMode_StopMode (const bool &bStopMode)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_bool(REGI_VALNAME_TESTMODE_HDLR_ON, bStopMode);
}

void CFunc_RegMain::f_RegiLoad_testMode_StopMode (bool &bStopMode)
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_bool(REGI_VALNAME_TESTMODE_HDLR_ON, bStopMode, false);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define REGI_VALNAME_DISPLAY_ORDER_MODE_AUTO	"DISPLAY_ORDER_MODE_AUTO"


void CFunc_RegMain::f_regiSave_DisplayOrderMode (const bool bAutoOrder)	// $ Add by sjkim 2014-02-11
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.save_bool(REGI_VALNAME_DISPLAY_ORDER_MODE_AUTO, bAutoOrder);
}

void CFunc_RegMain::f_regiRead_DisplayOrderMode (bool &bAutoOrder)	// $ Add by sjkim 2014-02-11
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	Regi.read_bool(REGI_VALNAME_DISPLAY_ORDER_MODE_AUTO, bAutoOrder, true);
}





//	void f_regiSave_testMode_HandlerSkip (bool &bSkip);
//	void f_regiRead_testMode_HandlerSkip (bool &bSkip);

//	void f_regiSave_testMode_RemoteEnable (bool &bMode);
//	void f_regiRead_testMode_RemoteEnable (bool &bMode);


///////////////////////////////////////////////////////////////////////


void CFunc_RegMain::f_regiSave_DataFileChgTime (const unsigned nTime[])
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	
	
	Regi.save_uint("DataFileChg_Time0", nTime[0]);
	Regi.save_uint("DataFileChg_Time1", nTime[1]);
	Regi.save_uint("DataFileChg_Time2", nTime[2]);
	Regi.save_uint("DataFileChg_Time3", nTime[3]);
}

void CFunc_RegMain::f_regiRead_DataFileChgTime (unsigned nTime[])
{
	CFunc_RegUser Regi(REG_SUBKEY_TESTPROG);	

	Regi.read_uint("DataFileChg_Time0",nTime[0], 0);
	Regi.read_uint("DataFileChg_Time1",nTime[1], 0);
	Regi.read_uint("DataFileChg_Time2",nTime[2], 0);
	Regi.read_uint("DataFileChg_Time3",nTime[3], 0);
}