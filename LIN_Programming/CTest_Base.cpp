#include "stdafx.h"
#include "CTest_Base.h"


CTest_Base::CTest_Base(void)
{
	m_pCFile	 = new CFunc_File;
	m_pCSpec	 = new CFunc_Spec;
	m_pLin		 = new CLin_Func_Main;
	m_pReg		 = new CFunc_RegMain;
	m_pInst		 = new CInst_Main;
	m_pBeep		 = new CFunc_Beep;

	m_pFrdm		 = new CSerial_Func_FRDM;
	m_pCTestData = new CFunc_TestData;
	m_pCSaveDataAccess = new CFunc_TestData_SaveAccess;
	{
		m_pCSaveDataAccess->m_cfg.pCData   = m_pCTestData;
		m_pCSaveDataAccess->m_cfg.pCSpec   = m_pCSpec;
		m_pCSaveDataAccess->m_cfg.pts = &this->m_cState;
	}

	m_cUserMsg.m_cfg.pts = &this->m_cState;


	m_pVsrc		= this->m_pInst->m_pVsrc;

	this->f_ts_Initialize ();
}


CTest_Base::~CTest_Base(void)
{
	delete m_pCFile;
	delete m_pCSpec;
	delete m_pLin;
	delete m_pReg;
	delete m_pInst;
	delete m_pBeep;
	delete m_pCTestData;
	delete m_pFrdm;
	delete m_pCSaveDataAccess;
}


void CTest_Base::f_ts_Initialize (void)
{
	this->m_cState.Status.isTestRun		= false;
	this->m_cState.Status.isHdlrOn		= true;

	this->m_cState.SysInfo.isLoadingFail_SystemInformation = false;

	this->m_cState.SysInfo.sProcName	= TPROC_NAME_STRING;
	this->m_cState.SysInfo.sProcRevData	= TPROC_REV_DATE_STRING;
	this->m_cState.SysInfo.nProcRevNo	= TPROC_REV_NO;

	this->m_pCSpec->m_stSpecInfo.tproc.nProcRevNo	  = TPROC_REV_NO;
	this->m_pCSpec->m_stSpecInfo.tproc.strProcName    = TPROC_NAME_STRING;		// = TPROC_NAME_STRING;		//strcpy_s(this->m_pCSpec->m_stSpecInfo.tproc.szProcName,    TPROC_NAME_STRING);
	this->m_pCSpec->m_stSpecInfo.tproc.strProcRevDate = TPROC_REV_DATE_STRING;


//	this->m_pReg->f_Default_Load(this->m_cState);
//	this->m_pReg->f_Regi_Password_Initialize   ();
//	this->m_pReg->f_RegiLoad_BasePath_DataFile (this->m_cState.datasave.file.szBase_path , MAX_PATH);

/*
	this->m_pReg->f_regiRead_Company_Name (this->m_cState.SysInfo.sCompanyName);
	if (0 != this->m_cState.SysInfo.sCompanyName.GetLength())
	{
		this->m_cState.SysInfo.isLoading_CompanyName = true;
	}
	else
	{
		this->m_cState.SysInfo.isLoading_CompanyName      = false;
		this->m_cState.SysInfo.isLoadingFail_SystemInformation = true;
	}


	this->m_pReg->f_regiRead_Division_Name(this->m_cState.SysInfo.sDivisionName);
	if(0 != this->m_cState.SysInfo.sDivisionName.GetLength())
	{
		this->m_cState.SysInfo.isLoading_DivisionName = true;
	}
	else
	{
		this->m_cState.SysInfo.isLoading_DivisionName = false;
		this->m_cState.SysInfo.isLoadingFail_SystemInformation = true;
	}
*/
	
	{
		char szComputerName[100];
		unsigned long dwLength=100;
		GetComputerName(szComputerName, &dwLength);
	
		m_cState.SysInfo.sComputerName = szComputerName;

	}

	return ;
}