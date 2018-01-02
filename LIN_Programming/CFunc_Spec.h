#pragma once

#include <afxdb.h>
#include <algorithm>
#include <fstream>
#include <functional>
#include <io.h>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <odbcinst.h>
#include <string>
#include <vector>

#include "CTest_State.h"

#include "CFunc_Spec_Item.h"
#include "CFunc_Spec_Item_Main.h"
#include "CFunc_Spec_Item_Main_Mode.h"

#include "CFunc_Mode_Vector.h"
#include "CFunc_DB_Odbc.h"
#include "CFunc_DB_Dao.h"




#define	CSPEC_MEAS_SETVAR_BUFSIZE 4


namespace ENUM_LIN_VREG_CFG_REGULATOR
{
	enum Enum
	{
		M00_REGULATOR_1		= 0,
		M01_REGULATOR_2		= 1,

		M99_END				= 99
	};
};

namespace ENUM_LIN_VREG_CFG_MSG_VERSION
{
	enum Enum
	{
		M00_MSG_VERSION_A	= 0,
		M01_MSG_VERSION_B	= 1,

		M99_END				= 99
	};
};



 typedef struct
{
	unsigned int nRX;
	unsigned int nTX1;
	unsigned int nTX2;
	unsigned int nTX3;
 }TS_CLIN_VREG_CFG_FRAME_ID;


typedef struct
{
	unsigned 		nId;
	std::string		sInfo;
	std::string		sDesc;
		
}TS_CSPEC_PAIR_INTSTRING;

typedef struct
{
//	unsigned		nSelectPnum;
//	unsigned		nSpecEditMode;
//	unsigned		SelectPort_nAddr;
//	unsigned		SelectPort_nData;

	bool			isSpecChange;
	
//	std::string		SelectPort_sMsg;

}TS_CSPEC_SPECINFO_SPECEDITDLG_SATE;

typedef struct
{
	TS_CSPEC_SPECINFO_SPECEDITDLG_SATE		seditDlgState;

	CString						strFilename;
	bool						isLoading_spec;


	unsigned					nTitem;
	CTime						tmSpecLoad;			//Add by sjkim 2012-0718
	double 						fElapsedTime;

	unsigned					nDisplayNum_max;

}TS_CSPEC_STATE;

typedef struct
{
	CString		strProcName;		//char		szProcName    [STRSIZE_PROCNAME + 1 ]; // $ 2016.01.30	Change 
	CString		strProcRevDate;		//char		szProcRevDate [STRSIZE_REVDATE + 1 ];  // $ 2016.01.30	Change 
	unsigned 	nProcRevNo;
}TS_CSPEC_SPECINFO_PROC;

typedef struct
{
//	TS_CSPEC_REVINFO		spec;
	
	CString strSpecName;								//char					szSpecName    [STRSIZE_SPECNAME + 1 ];     // $ 2016.01.30	Change 
	CString strSpecRevDate;								//char					szSpecRevDate [STRSIZE_REVDATE + 1 ];	   // $ 2016.01.30	Change	
	unsigned 				nSpecRevNo;

	CString strDeviceName;								//char 					szDeviceName [STRSIZE_DEVICENAME + 1];		// $ 2016.01.30



	unsigned			nTestRefModel;
	
	CString				sInfo_Device;
	CString				sInfo_Customer;
	CString				sInfo_Remarks;

	CString				sEditLastDate;

}TS_CSPEC_SPECINFO_SPEC;

typedef struct
{
	//char	szPinName[20][STRSIZE_CSPEC_PINNAME + 1];
	CString sPinName[20];

}TS_CSPEC_SPECINFO_PIN;

typedef struct
{
	unsigned	nProbe;
	double		fDlyMs_ProbeOn;
	double		fDlyMs_ProbeOff;

}TS_CSPEC_SPECINFO_HDLR;

typedef struct
{
	unsigned nP;
	unsigned nPrev;
	unsigned nNext;
}TS_CSPEC_NEXTPREV;


typedef struct
{
	unsigned ID_0000_NC;

	unsigned nLINREG_CR665_Verify;
	unsigned nLINREG_CR665_Program_and_Verify;

	unsigned nLINREG_TLE8880_Verify;
	unsigned nLINREG_TLE8880_Program_and_Verify;

	unsigned nLINREG_TLE8881_Verify;
	unsigned nLINREG_TLE8881_Program_and_Verify;

	unsigned nLINREG_L9916_Verify;
	unsigned nLINREG_L9916_Program_and_Verify;

	unsigned nLINREG_LIN2112_Verify;
	unsigned nLINREG_LIN2112_Program_and_Verify;

	unsigned nCOMM_Meas_Voltage;

}TS_CSPEC_REF_FUNCTEST_ITEM;

typedef struct
{
	TS_CSPEC_SPECINFO_PROC		tproc;
	TS_CSPEC_SPECINFO_SPEC		tspec;
	TS_CSPEC_SPECINFO_PIN		Pin;
	TS_CSPEC_SPECINFO_HDLR		Hdlr;
//	TS_CSPEC_SPECINFO_MARKING	Marking;

	TS_CSPEC_SPECINFO_LIN		Lin;
//	TS_CSPEC_SPECINFO_DATABASE_FORM_Info    DBInfo;

//	CTime					tmSpecLoad;

}TS_CSPEC_SPECINFO;


typedef struct _st_CSPEC_mode 
{
	TS_CSPEC_REF_FUNCTEST_ITEM			stRefTitem;	// referance functest test item


	std::vector<TS_CSPEC_REFFUNC> vInfoRefFuncTitem;


	CFunc_Mode_Vector	Spec_vRefModel;
	
	CFunc_Mode_Vector	Meas_vSetVar;							
	
	CFunc_Mode_Vector	Step_vMeasMode;;	
	CFunc_Mode_Vector	Step_vCntlSrc;	
	CFunc_Mode_Vector	Step_vTestItem;	
	CFunc_Mode_Vector	Step_vTestCond;	
	CFunc_Mode_Vector	Step_vJudgeItem;	

	CFunc_Mode_Vector	Lin_vSendData;

	CFunc_Spec_Item_Main_Mode	ItemMode;

}TS_CSPEC_MODE;


struct Compare_isFuncTest : public std::binary_function<CFunc_Spec_Item, CFunc_Spec_Item, bool>
{
	bool operator () (const CFunc_Spec_Item& lhs, const CFunc_Spec_Item& rhs)
	{
		return (lhs.Spec.Option.isPowerOnTest > rhs.Spec.Option.isPowerOnTest);
	}
};


struct Compare_RefTestItem : public std::binary_function<CFunc_Spec_Item, CFunc_Spec_Item, bool>
{
	bool operator () (const CFunc_Spec_Item& lhs, const CFunc_Spec_Item& rhs)
	{
		return (lhs.Spec.nRefTitem < rhs.Spec.nRefTitem);
	}
};





class CFunc_Spec
{
public:
	CFunc_Spec(void);
	~CFunc_Spec(void);

	std::vector<CFunc_Spec_Item>	m_vTitem;

	TS_CSPEC_SPECINFO				m_stSpecInfo;


	TS_CSPEC_STATE					m_stStatus;
	TS_CSPEC_MODE					m_stMode;


	CFunc_DB_Odbc					m_odbcFunc;
	CFunc_DB_Dao 					m_daoFunc;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void f_CSpec_Copy_to_class						 (CFunc_Spec &toClass  );
	void f_CSpec_Copy_from_class					 (CFunc_Spec &fromClass);
	void f_CSpec_AddItem_from_class					 (CFunc_Spec &fromClass);
	void f_CSpec_Replace_from_class_without_filename (CFunc_Spec &fromClass);

	void f_initialize_tspec_clear_all();


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void f_modeTable_initialize		(void);
	void f_modeTable_insert			(std::vector<TS_CSPEC_PAIR_INTSTRING> *v, int nId, CString sText, CString sDesc);
	void f_modetable_RefFunc_insert (std::vector<TS_CSPEC_REFFUNC> *pVec,     int nId, CString sText);
	void f_modetable_RefFunc_insert_Multi(std::vector<TS_CSPEC_REFFUNC> *pVec, TS_CSPEC_REFFUNC *pRef);
	int  f_modeTable_find_vec_record (int nId, 	std::vector<TS_CSPEC_PAIR_INTSTRING> &v);
	int	 f_modeTable_find_vec_record (int nId, 	std::vector<TS_CSPEC_REFFUNC> &v);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void f_titem_array_generate (unsigned proc_num);

	void f_titem_add_empty_record_to_final (void);

	void f_titem_delete  (int nIdx);
	void f_titem_move    (int fromIdx, int toIdx);
	void f_titem_copy    (int fromIdx, int toIdx);
	void f_titem_copy    (int fromIdx);

	void f_titem_replace (int nIdx, CFunc_Spec_Item ftest);
	void f_titem_insert  (int nIdx, CFunc_Spec_Item ftest);

	void f_titem_stable_sort_with_isFuncTest(std::vector<CFunc_Spec_Item> &v);

	bool f_titem_bSearch_NextItem(bool bPowerOnTestItem, int nBegin, int &nIdx, std::vector<CFunc_Spec_Item>	&v);
	bool f_titem_bSearch_PrevItem(bool bPowerOnTestItem, int nBegin, int &nIdx, std::vector<CFunc_Spec_Item>	&v);

	bool f_isExist_PowerOnTest_RefTitem(unsigned nRefTitem);
	bool f_isExist_PowerOffTest_RefTitem(unsigned nRefTitem);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void f_Initialize_SpecInfo();
	void f_initialize_titem_spec (CFunc_Spec_Item &ftest);

	void f_GROUP_PreTested_Item_find_and_flag_set ();

	void f_calculate_display_num();
};
