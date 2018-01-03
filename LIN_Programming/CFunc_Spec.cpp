#include "stdafx.h"
#include "tmenu_file.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h> 
#include <afxdb.h>
#include <odbcinst.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <io.h>
#include <iterator>

#include "CFunc_Spec.h"
#include "CFunc_UserMsg.h"
#include "CTest_Main.h"
#include "CFunc_BackupFile.h"



extern CTest_Main	*pTest;
using namespace std;



CFunc_Spec::CFunc_Spec(void)
{
	this->m_stStatus.nTitem				  = 0;	
	this->m_stSpecInfo.Hdlr.nProbe		  = 0;
	this->m_stSpecInfo.Hdlr.fDlyMs_ProbeOn  = 500;
	this->m_stSpecInfo.Hdlr.fDlyMs_ProbeOff = 500;


//	memset(this->m_stSpecInfo.tspec.strDeviceName,	0, STRSIZE_DEVICENAME );
//	memset(this->m_stSpecInfo.tspec.strSpecName,	0, STRSIZE_SPECNAME   ); 
//	memset(this->m_stSpecInfo.tspec.strSpecRevDate,	0, STRSIZE_REVDATE    );
//	memset(this->m_stSpecInfo.tproc.strProcName,	0, STRSIZE_PROCNAME   ); 
//	memset(this->m_stSpecInfo.tproc.strProcRevDate,	0, STRSIZE_REVDATE    );


	this->m_stStatus.isLoading_spec = 0;


	f_modeTable_initialize();
}


CFunc_Spec::~CFunc_Spec(void)
{
	this->m_vTitem.clear();
}



void CFunc_Spec::f_CSpec_Copy_to_class (CFunc_Spec &toClass)
{
	toClass.m_stStatus	 = this->m_stStatus;
	toClass.m_stSpecInfo = this->m_stSpecInfo;

	toClass.m_vTitem.clear();
	copy (this->m_vTitem.begin(), this->m_vTitem.end(), back_inserter(toClass.m_vTitem));
}


void CFunc_Spec::f_CSpec_Copy_from_class (CFunc_Spec &fromClass)
{
	this->m_stStatus	= fromClass.m_stStatus;
	this->m_stSpecInfo	= fromClass.m_stSpecInfo;

	this->m_vTitem.clear();
	copy (fromClass.m_vTitem.begin(), fromClass.m_vTitem.end(), back_inserter(this->m_vTitem));
}


void CFunc_Spec::f_CSpec_Replace_from_class_without_filename (CFunc_Spec &fromClass)	//File명은 두고 나머지는 모두 교체한다.
{
	this->m_stStatus.nTitem = fromClass.m_stStatus.nTitem;

	this->m_stSpecInfo.Hdlr	  = fromClass.m_stSpecInfo.Hdlr;
	this->m_stSpecInfo.Lin	  = fromClass.m_stSpecInfo.Lin;

	this->m_stSpecInfo.tspec  = fromClass.m_stSpecInfo.tspec;
	

	this->m_vTitem.clear();
	copy (fromClass.m_vTitem.begin(), fromClass.m_vTitem.end(), back_inserter(this->m_vTitem));
}


void CFunc_Spec::f_initialize_tspec_clear_all()
{
	this->m_vTitem.clear();
	this->f_Initialize_SpecInfo();
	this->m_stStatus.isLoading_spec = false;
}


void CFunc_Spec::f_CSpec_AddItem_from_class (CFunc_Spec &fromClass)
{
	copy (fromClass.m_vTitem.begin(), fromClass.m_vTitem.end(), back_inserter(this->m_vTitem));
	this->m_stStatus.nTitem = this->m_vTitem.size();
}





void CFunc_Spec::f_modeTable_initialize ()
{
	TS_CSPEC_REF_FUNCTEST_ITEM *p = &m_stMode.stRefTitem;
	m_stMode.vInfoRefFuncTitem.clear ();


	std::vector<TS_CSPEC_REFFUNC> *pVec;
	pVec = &m_stMode.vInfoRefFuncTitem;


	f_modetable_RefFunc_insert (pVec, p->ID_0000_NC								= 0,   "0000_NC"						  );
	
	f_modetable_RefFunc_insert (pVec, p->nLINREG_CR665_Verify 					= 1,  "LINREG_CR665_Verify"				  );
	f_modetable_RefFunc_insert (pVec, p->nLINREG_CR665_Program_and_Verify 		= 2,  "LINREG_CR665_Program_and_Verify"   );

	f_modetable_RefFunc_insert (pVec, p->nLINREG_TLE8880_Verify 				= 3,  "LINREG_TLE8880_Verify"			  );
	f_modetable_RefFunc_insert (pVec, p->nLINREG_TLE8880_Program_and_Verify 	= 4,  "LINREG_TLE8880_Program_and_Verify" );

	f_modetable_RefFunc_insert (pVec, p->nLINREG_TLE8881_Verify 				= 5,  "LINREG_TLE8881_Verify"			  );
	f_modetable_RefFunc_insert (pVec, p->nLINREG_TLE8881_Program_and_Verify 	= 6,  "LINREG_TLE8881_Program_and_Verify" );

	f_modetable_RefFunc_insert (pVec, p->nLINREG_L9916_Verify 					= 7,  "LINREG_L9916_Verify"				  );
	f_modetable_RefFunc_insert (pVec, p->nLINREG_L9916_Program_and_Verify 		= 8,  "LINREG_L9916_Program_and_Verify"	  );

	f_modetable_RefFunc_insert (pVec, p->nLINREG_LIN2112_Verify 				= 9,  "LINREG_LIN2112_Verify"			  );
	f_modetable_RefFunc_insert (pVec, p->nLINREG_LIN2112_Program_and_Verify 	= 10, "LINREG_LIN2112_Program_and_Verify" );

	f_modetable_RefFunc_insert (pVec, p->nCOMM_Meas_Voltage 					= 11,  "COMM_Meas_Voltage" );

}


void CFunc_Spec::f_modeTable_insert (std::vector<TS_CSPEC_PAIR_INTSTRING> *pVec, int nId, CString sText, CString sDesc )
{
	TS_CSPEC_PAIR_INTSTRING		p;

	p.nId	= nId;
	p.sInfo	= sText;
	p.sDesc = sDesc;

	pVec->push_back (p);
}


void  CFunc_Spec::f_modetable_RefFunc_insert(std::vector<TS_CSPEC_REFFUNC> *pVec, int nId, CString sText)  //multi=0인 경우 적용
{
	TS_CSPEC_REFFUNC	Ref;

	Ref.nId				= nId;
	Ref.sInfo			= sText;
	Ref.Group.nItem_Max = 0;
	
	for(unsigned n=0; n<CSPEC_REFFUNC_GROUPTEST_ITEM_MAX; n++)
	{
		Ref.Group.sSymbol[n] ="";
		Ref.Group.nProcYN[n] = 0;
	}

	pVec->push_back (Ref);
}


void  CFunc_Spec::f_modetable_RefFunc_insert_Multi(std::vector<TS_CSPEC_REFFUNC> *pVec, TS_CSPEC_REFFUNC *pRef)
{
	TS_CSPEC_REFFUNC		Ref;

	for (unsigned n = 0; n<CSPEC_REFFUNC_GROUPTEST_ITEM_MAX; n++)
	{
		Ref.Group.sSymbol[n] = "";
		Ref.Group.nProcYN[n] = 0;
		//Ref.Group.nPnumIdx[n]	= 0;
		//Ref.Group.bTestYN[n]	= false;
	}


	Ref.nId = pRef->nId;
	Ref.sInfo = pRef->sInfo;

	Ref.Group.nItem_Max = pRef->Group.nItem_Max;


	for (unsigned n = 0; n<Ref.Group.nItem_Max; n++)
	{
		Ref.Group.sSymbol[n] = pRef->Group.sSymbol[n];
		Ref.Group.nProcYN[n] = pRef->Group.nProcYN[n];
	}

	pVec->push_back(Ref);
}


int CFunc_Spec::f_modeTable_find_vec_record (int nId, std::vector<TS_CSPEC_PAIR_INTSTRING>	&v)
{
	int nSize = v.size ();
	
	for(int nIndex=0; nIndex < nSize; nIndex++)
	{
		if (v[nIndex].nId == nId) return nIndex;
	}

	return 0;
}


int CFunc_Spec::f_modeTable_find_vec_record (int nId, std::vector<TS_CSPEC_REFFUNC>	&v)
{
	int nSize = v.size ();
	
	for(int nIndex=0; nIndex < nSize; nIndex++)
	{
		if (v[nIndex].nId == nId) return nIndex;
	}

	return 0;
}



void CFunc_Spec::f_titem_array_generate (unsigned proc_num)
{
	this->m_stStatus.nTitem = proc_num;
	this->m_vTitem.clear();

	CFunc_Spec_Item ftest;

	unsigned i;
	for (i=0; i<proc_num; i++)
	{
		ftest.Spec.Option.isTest = false;
		ftest.Spec.nPnum = i;

		this->m_vTitem.push_back (ftest);
	}

	this->m_stStatus.isLoading_spec = false;
}


void CFunc_Spec::f_titem_add_empty_record_to_final ()
{
	int final;
	final = this->m_vTitem.size();

	CFunc_Spec_Item ftest;
	f_initialize_titem_spec ( ftest );

	ftest.Spec.nPnum = final;
	ftest.Spec.nTnum = final + 1;

	this->m_vTitem.push_back ( ftest );


	final = this->m_vTitem.size();	
	this->m_stStatus.nTitem = final; 
}


void CFunc_Spec::f_titem_delete (int nIdx)
{
	int final = this->m_vTitem.size();
	if (nIdx < 0) return;
	if (nIdx > final) return;

	std::vector<CFunc_Spec_Item>::iterator it;
	it = m_vTitem.begin() + nIdx;
//	it = &m_vTitem[nIdx];
	
	this->m_vTitem.erase (it);
	this->m_stStatus.nTitem = this->m_vTitem.size();	
}


void CFunc_Spec::f_titem_move (int fromIdx, int toIdx)
{
	int final = this->m_vTitem.size();

	if (fromIdx < 0)		return;
	if (fromIdx > final)	return;

	if (toIdx < 0)			return;
	if (toIdx > final)		return;

	CFunc_Spec_Item titem;
	titem = m_vTitem[fromIdx]; 

	if (toIdx > fromIdx)
	{
		f_titem_insert(toIdx, titem);
		f_titem_delete(fromIdx);
	}
	
	if ( fromIdx > toIdx)
	{
		f_titem_delete(fromIdx);
		f_titem_insert(toIdx, titem);
	}
}


void CFunc_Spec::f_titem_copy (int fromIdx, int toIdx)
{
	CFunc_Spec_Item ftest;
	ftest = this->m_vTitem[fromIdx];

	this->f_titem_insert (toIdx, ftest);
}


void CFunc_Spec::f_titem_copy (int fromIdx)
{
	int final = this->m_vTitem.size ();
	f_titem_copy (fromIdx, final);
}


void CFunc_Spec::f_titem_replace (int nIdx, CFunc_Spec_Item ftest)
{
	int final = this->m_vTitem.size();
	if (nIdx < 0) return;
	if (nIdx > final) return;

	this->m_vTitem[nIdx] = ftest;
}


void CFunc_Spec::f_titem_insert (int nIdx, CFunc_Spec_Item ftest)
{
	int final = this->m_vTitem.size();
	if (nIdx < 0) return;
	if (nIdx > final) return;

	std::vector<CFunc_Spec_Item>::iterator it;
	it = m_vTitem.begin() + nIdx;
//	it = &m_vTitem[nIdx]; 

	this->m_vTitem.insert(it, 1, ftest);
	this->m_stStatus.nTitem = this->m_vTitem.size();
}


void CFunc_Spec::f_titem_stable_sort_with_isFuncTest (std::vector<CFunc_Spec_Item> &v)
{
	//2010.6. 모두 POWER OFF인 경우 
	//2010.6. 모두 POWER ON인 경우 

	// Spec.isPowerOnTest로 소트하고 재정렬한다. 
	std::stable_sort (v.begin(), v.end(), Compare_isFuncTest());

	int nSize = v.size();
	int nIdx;

	//pnum과 tnum을 재설정한다.
	for (nIdx=0; nIdx < nSize; nIdx++)
	{
		v[nIdx].Spec.nPnum = nIdx;
		v[nIdx].Spec.nTnum = nIdx+1;
	}

	//선행 및 후행 프로세스 자동 설정 

	//파워테스트 끝항목을 조사 
	int nPowerEnd = 0;
	int nCount	  = 0;
	for (nIdx=0; nIdx < nSize; nIdx++)
	{
		if (v[nIdx].Spec.Option.isPowerOnTest)
		{
			nPowerEnd = nIdx;
			nCount++;
		}
	}

	/*
	if (nCount == 0)
	{
		std::stable_sort (v.begin(), v.end(), Compare_RefTestItem() );
	}
	else if (nCount < nSize)
	{
		std::stable_sort (v.begin() + nPowerEnd + 1, v.end(), Compare_RefTestItem());
	}
	else
	{

	}
	*/

//	int nNext, nPrev;
//	for (nIdx=0; nIdx<nSize; nIdx++) v[nIdx].Spec.nPnum_Next = nIdx;
//	for (nIdx=0; nIdx<nSize; nIdx++) v[nIdx].Spec.nPnum_Prev = nIdx;
	
/*
	for (nIdx=0; nIdx<nSize; nIdx++)
	{
		if ( ( true == v[nIdx].Spec.Option.isPowerOnTest) & v[nIdx].Spec.Option.isTest)
		{
			if (true == f_titem_bSearch_NextItem(true, nIdx + 1, nNext, v) )
			{
				v[nIdx].Spec.nPnum_Next = nNext;
			}
		}
	}

	for (nIdx=0; nIdx<nSize; nIdx++)
	{
		if ( ( true == v[nIdx].Spec.Option.isPowerOnTest) & v[nIdx].Spec.Option.isTest)
		{
			if (true == f_titem_bSearch_PrevItem(true, nIdx - 1, nPrev, v) )
			{
				v[nIdx].Spec.nPnum_Prev = nPrev;
			}
		}
	}

	for (nIdx=0; nIdx<nSize; nIdx++)
	{
		if ( ( false == v[nIdx].Spec.Option.isPowerOnTest) & v[nIdx].Spec.Option.isTest)
		{
			if (true == f_titem_bSearch_NextItem(false, nIdx + 1, nNext, v) )
			{
				v[nIdx].Spec.nPnum_Next = nNext;
			}
		}
	}

	for (nIdx=0; nIdx<nSize; nIdx++)
	{
		if ( ( false == v[nIdx].Spec.Option.isPowerOnTest) & v[nIdx].Spec.Option.isTest)
		{
			if (true == f_titem_bSearch_PrevItem(false, nIdx - 1, nPrev, v) )
			{
				v[nIdx].Spec.nPnum_Prev = nPrev;
			}
		}
	}
	*/
}


bool CFunc_Spec::f_titem_bSearch_NextItem(bool bPowerOnTestItem, int nBegin, int &nIdx, std::vector<CFunc_Spec_Item>	&v)
{
	int nSize = v.size();
	
	if (nBegin >= nSize) return false;


	for (nIdx = nBegin; nIdx<nSize; nIdx++)
	{
		if ( ( bPowerOnTestItem == v[nIdx].Spec.Option.isPowerOnTest ) && v[nIdx].Spec.Option.isTest )
			return true;
	}

	return false;
}


bool CFunc_Spec::f_titem_bSearch_PrevItem(bool bPowerOnTestItem, int nBegin, int &nIdx, std::vector<CFunc_Spec_Item>	&v)
{
	int nSize = v.size();

	if (nBegin < 0) return false;

	for (nIdx = nBegin; nIdx >= 0  ; nIdx--)
	{
		if ( ( bPowerOnTestItem == v[nIdx].Spec.Option.isPowerOnTest ) && v[nIdx].Spec.Option.isTest )
			return true;
	}

	return false;
}


bool CFunc_Spec::f_isExist_PowerOnTest_RefTitem(unsigned nRefTitem)
{
	CFunc_Spec_Item *p;

	for (unsigned i=0; i<this->m_stStatus.nTitem; i++)
	{
		p = &this->m_vTitem[i];
		
		if (p->Spec.Option.isTest && p->Spec.Option.isPowerOnTest)
		{
			if (p->Spec.nRefTitem == nRefTitem) return true;
		}
	}

	return false;
}


bool CFunc_Spec::f_isExist_PowerOffTest_RefTitem(unsigned nRefTitem)
{
	CFunc_Spec_Item *p;

	for (unsigned i=0; i<this->m_stStatus.nTitem; i++)
	{
		p = &this->m_vTitem[i];
		
		if (p->Spec.Option.isTest && (!p->Spec.Option.isPowerOnTest) )
		{
			if (p->Spec.nRefTitem == nRefTitem) return true;
		}
	}

	return false;

}


void CFunc_Spec::f_Initialize_SpecInfo()
{
	{
		this->m_stSpecInfo.Hdlr.nProbe = 0;
		this->m_stSpecInfo.Hdlr.fDlyMs_ProbeOn	= 0;
		this->m_stSpecInfo.Hdlr.fDlyMs_ProbeOff = 0;
	}

	{
		TS_CSPEC_SPECINFO_LIN		*pLIN;
		pLIN = &this->m_stSpecInfo.Lin;


		pLIN->sInterface = "";
		pLIN->nBaudrate  = 0;
		pLIN->nChip		 = 0;
		pLIN->nRegulator = 0;


		pLIN->Nvm.Addr00 = 0;
		pLIN->Nvm.Addr01 = 0;
		pLIN->Nvm.Addr02 = 0;
		pLIN->Nvm.Addr03 = 0;
		pLIN->Nvm.Addr04 = 0;
		pLIN->Nvm.Addr05 = 0;
		pLIN->Nvm.Addr06 = 0;
		pLIN->Nvm.Addr07 = 0;
		pLIN->Nvm.Addr08 = 0;

		pLIN->Fid.nRx  = 0;
		pLIN->Fid.nTx1 = 0;
		pLIN->Fid.nTx2 = 0;
		pLIN->Fid.nTx3 = 0;

		pLIN->nWaitTime = 0;
	}
}


void CFunc_Spec::f_initialize_titem_spec (CFunc_Spec_Item &ftest)
{
	{
		ftest.Spec.Option.isTest			= false;
		ftest.Spec.Option.isPowerOnTest		= false;

		ftest.Spec.strTestName				= "n/d";
		ftest.Spec.strTestUnit				= "n/d";
		ftest.Spec.strTestSymbol			= "n/d";

		ftest.Spec.stCal.fMul				= 0.0;
		ftest.Spec.stCal.fSum				= 0.0;

		ftest.Spec.stLimit.HSL_VAR.dblVal	= 0.0;
		ftest.Spec.stLimit.LSL_VAR.dblVal	= 0.0;

		ftest.Spec.stLimit.nMode			= 0;

		ftest.Spec.nRefTitem				= 0;

		ftest.Spec.nPnum					= 0;			
		ftest.Spec.nTnum					= 0;

		ftest.Spec.nPnum_Prev = ftest.Spec.nPnum;
		ftest.Spec.nPnum_Next = ftest.Spec.nPnum;

		ftest.Spec.strDataFormat = "8.3f";

		ftest.Spec.stCal.sRefText = "";
	}

	{
		ftest.Spec.stGroup.bPrevTested		= false;
		ftest.Spec.stGroup.uTestYN.uint32	= 0;
		ftest.Spec.stGroup.nItem_Max		= 0;

		for (unsigned i=0; i<CSPEC_REFFUNC_GROUPTEST_ITEM_MAX; i++)
		{
			ftest.Spec.stGroup.nItem_IdxNo[i] = 0;
		}
	}

	{
		ftest.Lin.SendMsg_bRepeatSend		= 0;
		ftest.Lin.SendMsg_fRepeatSendTime_Ms= 0;
		ftest.Lin.SendMsg_nSel				= 0;

		ftest.Lin.msg_RX.Data.uint64		= 0;
		ftest.Lin.msg_RX.nId				= 0;
		ftest.Lin.msg_RX.nLen				= 0;

		ftest.Lin.meas_NVM_nParam	= 0;
	}

	{	
		ftest.Info.strInfo1 = "";
		ftest.Info.strInfo2 = "";
	}

}


void CFunc_Spec::f_GROUP_PreTested_Item_find_and_flag_set ()
{
	TS_CSPEC_TITEM_SPEC_GROUPITEM *pGroup;
	unsigned pnum;

	unsigned idx = 0;
	unsigned p = 0;
	unsigned nCheck = 0;

	for(p=0; p<this->m_stStatus.nTitem; p++)
	{
		pGroup = &this->m_vTitem[p].Spec.stGroup;
		pGroup->bPrevTested = false;
	}


	for(p=0; p<this->m_stStatus.nTitem; p++)
	{
		pGroup = &this->m_vTitem[p].Spec.stGroup;
	
		if (pGroup->bPrevTested)   continue;
		if (pGroup->nItem_Max < 2) continue;

		for (idx=0; idx <pGroup->nItem_Max; idx++)
		{
			pnum = p + pGroup->nItem_IdxNo[idx];
			
			if (pnum > this->m_stStatus.nTitem)  continue;
			if (pnum == p) continue;

			nCheck = (0x01)<<idx;

			nCheck = pGroup->uTestYN.uint32 & nCheck;

			if ( 0 != nCheck )
				this->m_vTitem[pnum].Spec.stGroup.bPrevTested = true;
		}
	}
	
}


void CFunc_Spec::f_calculate_display_num()
{
	//검사하지 않는 항목은 표시히자 않는다. 
	unsigned pnum_max = this->m_vTitem.size();
	unsigned displaynum_max = pnum_max;

	unsigned p = 0;
	unsigned dispnum = 0;

	for (p = 0; p < pnum_max; p++)
	{
		this->m_vTitem[p].Spec.nDispNum = dispnum;

		if (true == this->m_vTitem[p].Spec.Option.isTest)
		{
			dispnum++;
		}
	}

	this->m_stStatus.nDisplayNum_max = dispnum++;
}
