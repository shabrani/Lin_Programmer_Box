#pragma once

#include "CTest_State.h"

class CFunc_RegBase  
{
public:
	CFunc_RegBase(HKEY hKey, LPCTSTR Subkey);
	virtual ~CFunc_RegBase();
	
	void	save  (LPCTSTR lpValue, LPCTSTR lpData);
	LPCTSTR read  (LPCTSTR lpValue, LPCTSTR lpDefaultString = "");


private:
	HKEY	m_key;
	DWORD	m_dwDisp;	
	char	m_szBuf[MAX_PATH];	
};

class CFunc_RegUser
{
public:
	CFunc_RegUser(LPCTSTR Subkey);
	virtual ~CFunc_RegUser();

	void save_CString(const CString strValueName, const CString strWriteData);										// $ 2016.01.30
	void read_CString(const CString strValueName, CString &strReadData, const CString strDefaultReadData = "");		// $ 2016.01.30


	void save_int  (const CString strValueName, int nWriteData);
	void read_int  (const CString strValueName, int &nReadData, int nDefault = 0 );

	void save_uint(const CString strValueName, unsigned nWriteData);
	void read_uint(const CString strValueName, unsigned &nReadData, unsigned nDefault = 0);

	void save_bool (const CString strValueName, bool bWriteData);
	void read_bool (const CString strValueName, bool &bReadData, bool bDefault = false );

private:
	HKEY	m_key;
	DWORD	m_dwDisp;
	char	m_szBuf[MAX_PATH];	
};


class CFunc_RegMain
{
public:
	CFunc_RegMain();
	virtual ~CFunc_RegMain();


	//void f_Default_Save (const CTest_State &ts);
	//void f_Default_Load (CTest_State &ts);

	void f_regiSave_Password (const CString strPWD);
	void f_regiRead_Password (CString &strPWD);

	void f_regiSave_BasePath_DataFile (const CString str);
	void f_regiRead_BasePath_DataFile (CString &str);


	void f_regiSave_BasePath_UserDataFile (const CString str);
	void f_regiRead_BasePath_UserDataFile (CString &str);


	void f_regiSave_Path_TestSpec(const CString str);
	void f_regiRead_Path_TestSpec(CString &str);


	void f_regiSave_Prog_SpecEdit (const CString str);
	void f_regiRead_Prog_SpecEdit (CString &str);



	void f_regiSave_Prog_DataProc (const CString str);
	void f_regiRead_Prog_DataProc (CString &str);


	void f_regiSave_file_default_tinf (const CString str);
	void f_regiRead_file_default_tinf (CString &str);

	void f_regiSave_file_address_map (const CString str);
	void f_regiRead_file_address_map (CString &str);


	void f_regiSave_file_system_info (const CString str);
	void f_regiRead_file_system_info (CString &str);


	void f_regiSave_path_tinf (const CString str);
	void f_regiRead_path_tinf (CString &str);

	void f_regiSave_testQty_total (const unsigned uPassTotal, const unsigned uFailTotal);
	void f_regiRead_testQty_total (unsigned &uPassTotal, unsigned &uFailTotal);


	void f_regiSave_testMode_EngMode (const bool  bMode);
	void f_regiRead_testMode_EndMode (      bool &bMode);

	void f_regiSave_testMode_HandlerOn (const bool  bHdlrOn);			// $ Change by sjkim 2012-06-21 HdlrSkip->HdlrOn
	void f_regiRead_testMode_HandlerOn (      bool &bHdlrOn);			// $ Change by sjkim 2012-06-21 HdlrSkip->HdlrOn

	void f_RegiSave_testMode_StopMode (const bool &bStopMode);
	void f_RegiLoad_testMode_StopMode (		 bool &bStopMode);

	void f_regiSave_DisplayOrderMode (const   bool  bAutoOrder);		// $ Add by sjkim 2014-02-11
	void f_regiRead_DisplayOrderMode (        bool &bAutoOrder);		// $ Add by sjkim 2014-02-11


	void f_regiSave_Company_Name (const CString str);
	void f_regiRead_Company_Name (      CString &str);


	void f_regiSave_Division_Name (const CString str);
	void f_regiRead_Division_Name (      CString &str);

	//void f_DataFoldOption_bEnable_RegSave (bool &bFoldOption);
	//void f_DataFoldOption_bEnable_RegRead (bool &bFoldOption);
	//void f_DataFoldOption_nNumber_RegSave (unsigned &uFoldNum);
	//void f_DataFoldOption_nNumber_RegRead (unsigned &uFoldNum);

	
	void f_regiSave_DataFileChgTime (const unsigned nTime[]);
	void f_regiRead_DataFileChgTime (      unsigned nTime[]);

};