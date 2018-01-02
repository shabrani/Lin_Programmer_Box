// CDlg_Spec.cpp : implementation file
//

#include "stdafx.h"
#include "LIN_Programming.h"
#include "CDlg_Spec.h"
#include "afxdialogex.h"

#include "CTest_Main.h"
#include "CFunc_File.h"
#include "CDlg_Spec_Item.h"

//////////////////////////////////////////////////////////////////////////
extern CTest_Main	*pTest;

//////////////////////////////////////////////////////////////////////////

// CDlg_Spec dialog

IMPLEMENT_DYNAMIC(CDlg_Spec, CDialog)

CDlg_Spec::CDlg_Spec(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Spec::IDD, pParent)
	, m_editbox_SpecName(_T(""))
	, m_editbox_ProgName(_T(""))
	, m_editbox_ProgRev(_T(""))
	, m_editbox_TestItem(_T(""))
	, m_editbox_SpecRevDate(_T(""))
	, m_editbox_SpecRevNo(_T(""))
	, m_editbox_TestDevice(_T(""))
{

}

CDlg_Spec::~CDlg_Spec()
{
}

void CDlg_Spec::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEDIT_LIST, m_list_sedit);

	DDX_Text(pDX, IDC_SPEC_NAME, m_editbox_SpecName);
	DDX_Text(pDX, IDC_PROG_NAME, m_editbox_ProgName);
	DDX_Text(pDX, IDC_PROG_REV,  m_editbox_ProgRev);
	DDX_Text(pDX, IDC_TEST_ITEM, m_editbox_TestItem);
	DDX_Text(pDX, IDC_SPEC_REVDATE, m_editbox_SpecRevDate);
	DDX_Text(pDX, IDC_TEST_REVNO, m_editbox_SpecRevNo);
	DDX_Text(pDX, IDC_SPEC_DEVICE, m_editbox_TestDevice);
}


BEGIN_MESSAGE_MAP(CDlg_Spec, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_SEDIT_LIST, &CDlg_Spec::OnNMDblclkSeditList)
END_MESSAGE_MAP()


// CDlg_Spec message handlers
BOOL CDlg_Spec::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->m_editbox_TestDevice.Format	("%s", m_var.CSpec_Edit.m_stSpecInfo.tspec.strDeviceName.GetString() );
	this->m_editbox_SpecName.Format		("%s", m_var.CSpec_Edit.m_stSpecInfo.tspec.strSpecName.GetString()	);
	this->m_editbox_SpecRevDate.Format	("%s", m_var.CSpec_Edit.m_stSpecInfo.tspec.strSpecRevDate.GetString());
	this->m_editbox_SpecRevNo.Format	("%d", m_var.CSpec_Edit.m_stSpecInfo.tspec.nSpecRevNo);

	this->m_editbox_ProgName.Format		("%s", m_var.CSpec_Edit.m_stSpecInfo.tproc.strProcName.GetString()	);
	this->m_editbox_ProgRev.Format		("%s", m_var.CSpec_Edit.m_stSpecInfo.tproc.strProcRevDate.GetString());

	this->m_editbox_TestItem.Format		("%d", m_var.CSpec_Edit.m_stStatus.nTitem);
	
	// Control List Font Init ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_Font.CreateFont(15,					// nHeight
					  7,					// nWidth 
					  0,					// nEscapement 
					  0,					// nOrientation 
					  FW_DONTCARE,			// FW_BOLD,	nWeight 
					  FALSE,				// bItalic 
					  FALSE,				// bUnderline 
					  0,					// cStrikeOut
					  DEFAULT_CHARSET,		// nCharSet 
					  OUT_DEFAULT_PRECIS,	// nOutPrecision 
					  CLIP_DEFAULT_PRECIS,	// nClipPrecision
					  DEFAULT_QUALITY,		// nQuality 
					  DEFAULT_PITCH,		// nPitchAndFamily 
					  _T("Arial"));			// lpszFacename
	m_list_sedit.SetFont(&m_Font, TRUE);

//	m_var.CSpec_Edit.m_stMode.Spec_vRefModel.f_cbox_Initial_Set(m_comboTestRefModel, "%d. %s");
//	m_var.CSpec_Edit.m_stMode.Spec_vRefModel.f_cbox_SetCurSel(m_comboTestRefModel, m_var.CSpec_Edit.m_stSpecInfo.tspec.nTestRefModel);

	f_EditMode_Change();

	return TRUE;
}

BEGIN_EVENTSINK_MAP(CDlg_Spec, CDialog)
	ON_EVENT(CDlg_Spec, IDC_CWN_SAVE, DISPID_CLICK, CDlg_Spec::ClickCwnSave, VTS_NONE)
	ON_EVENT(CDlg_Spec, IDC_CWN_EXIT, DISPID_CLICK, CDlg_Spec::ClickCwnExit, VTS_NONE)

	ON_EVENT(CDlg_Spec, IDC_BTN_SORT, -600 /* Click */  , OnClickSeditBtnSort,   VTS_NONE)
	ON_EVENT(CDlg_Spec, IDC_BTN_ADD,  -600 /* Click */  , OnClickSeditBtnAdd,    VTS_NONE)
	ON_EVENT(CDlg_Spec, IDC_BTN_DELETE, -600 /* Click */, OnClickSeditBtnDelete, VTS_NONE)
END_EVENTSINK_MAP()

void CDlg_Spec::ClickCwnSave()
{
	// TODO: Add your message handler code here
	this->UpdateData(TRUE);

	m_var.CSpec_Edit.m_stSpecInfo.tspec.strDeviceName	= this->m_editbox_TestDevice;
	m_var.CSpec_Edit.m_stSpecInfo.tspec.strSpecName		= this->m_editbox_SpecName;
	m_var.CSpec_Edit.m_stSpecInfo.tspec.strSpecRevDate	= this->m_editbox_SpecRevDate;
	m_var.CSpec_Edit.m_stSpecInfo.tspec.nSpecRevNo		= atoi(this->m_editbox_SpecRevNo);


	m_var.CSpec_Edit.f_titem_stable_sort_with_isFuncTest(m_var.CSpec_Edit.m_vTitem);


	CFunc_Spec_File specfile(&m_var.CSpec_Edit);
	if (true == specfile.f_Save_CSpec_to_SFile())
	{
		m_var.CSpec_pOrg->f_CSpec_Copy_from_class(m_var.CSpec_Edit);

		::MessageBox(NULL, "Save Ok", "Information", MB_OK);	
	}
	else
	{
		::MessageBox(NULL, "Save Fail", "Information", MB_OK);
	}

}


void CDlg_Spec::ClickCwnExit()
{
	// TODO: Add your message handler code here
	CDialog::OnOK();
}


void CDlg_Spec::OnNMDblclkSeditList(NMHDR *pNMHDR, LRESULT *pResult)
{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	POSITION pos = m_list_sedit.GetFirstSelectedItemPosition();
	if (pos == NULL)  return;

	//////////////////////////////////////////////////////////////////////////////
	CDlg_Spec_Item	dlg_SpecItem;

	dlg_SpecItem.m_var.pnum_prev = 999;
	dlg_SpecItem.m_var.pnum		 = m_list_sedit.GetNextSelectedItem(pos);

	dlg_SpecItem.m_var.pCSpec	 = &m_var.CSpec_Edit;
	dlg_SpecItem.m_var.pTest	 = m_var.pTest;

	dlg_SpecItem.DoModal();
	///////////////////////////////////////////////////////////////////////////////

	f_ListCtrl_DispalyData();

	*pResult = 0;
}

void CDlg_Spec::OnClickSeditBtnSort ()
{
	m_var.CSpec_Edit.f_titem_stable_sort_with_isFuncTest (m_var.CSpec_Edit.m_vTitem);

	this->f_ListCtrl_DispalyData();	
}

void CDlg_Spec::OnClickSeditBtnAdd ()
{
	m_var.CSpec_Edit.f_titem_add_empty_record_to_final ();

	this->f_ListCtrl_DispalyData();
}

void CDlg_Spec::OnClickSeditBtnDelete ()
{
	POSITION pos = this->m_list_sedit.GetFirstSelectedItemPosition();

	if (pos == NULL)
	{
		display_msg_for_Information ("No items were selected!\n");
		return ;
	}

	int nItem = this->m_list_sedit.GetNextSelectedItem(pos);

	
	CFunc_Spec_Item *pTitem = &m_var.CSpec_Edit.m_vTitem[nItem];

	CString  sMsg;
	CString sBuf;

	sBuf.Format ("Delete item?   \n\n\n");								    	sMsg  = sBuf;	
	sBuf.Format ("Selected Item No (Process No)  = %d \n", nItem);								sMsg += sBuf;		
	sBuf.Format ("Selected Item Name             = '%s' \n\n\n", pTitem->Spec.strTestName.GetString());	sMsg += sBuf;

	int rtn = AfxMessageBox (sMsg, MB_OKCANCEL);
	if ( rtn != IDOK) return;
	
	m_var.CSpec_Edit.f_titem_delete (nItem);
	this->f_ListCtrl_DispalyData();	
}


void CDlg_Spec::f_EditMode_Change ()
{
	this->m_list_sedit.EnableScrollBar (SB_BOTH, ESB_DISABLE_BOTH);

	f_ListCtrl_Initialize_funcTest ();

	f_ListCtrl_DispalyData ();

	this->UpdateData (FALSE);

	this->m_list_sedit.EnableScrollBar (SB_BOTH, ESB_ENABLE_BOTH);
}

void CDlg_Spec::f_ListCtrl_Initialize_funcTest (void)
{

	while (this->m_list_sedit.DeleteColumn(0) );
	
	m_list_sedit.SetExtendedStyle(LVS_EX_SUBITEMIMAGES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rect;
	m_list_sedit.GetClientRect(&rect);

	LVCOLUMN lv;
	lv.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;

	f_InsertCol (lv, 0,		40,  "PNo",		    LVCFMT_CENTER);
	f_InsertCol (lv, 1,		40,  "TNo",		    LVCFMT_CENTER);
	f_InsertCol (lv, 2,		70,  "Symbol",		LVCFMT_LEFT);
	f_InsertCol (lv, 3,		300, "Test Name",	LVCFMT_LEFT);	
	f_InsertCol (lv, 4,		70,	 "Unit",		LVCFMT_CENTER);
	f_InsertCol (lv, 5,		85,  "LSL",			LVCFMT_CENTER);
	f_InsertCol (lv, 6,		85,  "HSL",			LVCFMT_CENTER);
	f_InsertCol (lv, 7,		100, "Format",		LVCFMT_LEFT);

}

void CDlg_Spec::f_ListCtrl_DispalyData ()
{
	f_ListCtrl_DisplayData_funcTest();

//	this->m_Edit_sTestNum.Format ("%d", m_var.CSpec_Edit.m_stSpecInfo.nTitem);
//	this->m_cniToPNum.SetMinMax  (0,		m_var.CSpec_Edit.m_stSpecInfo.nTitem);

	this->UpdateData (FALSE);
}


void CDlg_Spec::f_ListCtrl_DisplayData_funcTest()
{
	m_list_sedit.DeleteAllItems();

	if( false == m_var.CSpec_Edit.m_stStatus.isLoading_spec ) return;

	LV_ITEM lvItem;
	CString strTemp;
	unsigned pnum;

	CFunc_Spec_Item	*p;

	for(pnum = 0; pnum < m_var.CSpec_Edit.m_stStatus.nTitem; pnum++)
	{
		p = &m_var.CSpec_Edit.m_vTitem[pnum];

		int nItemNum = m_list_sedit.GetItemCount();

		lvItem.iItem = nItemNum;
		lvItem.iSubItem = 0;
		lvItem.mask = LVIF_PARAM | LVIF_TEXT;
		lvItem.cchTextMax = 0;
		lvItem.pszText = "";
		
		m_list_sedit.LockWindowUpdate();
		m_list_sedit.InsertItem(&lvItem);

		strTemp.Empty();

		this->f_InsertLVItem_uint	(lvItem,  0, pnum,				   "%d");

		this->f_InsertLVItem_uint	(lvItem,  1, p->Spec.nTnum,		   "%d");

		this->f_InsertLVItem_Text	(lvItem,  2, p->Spec.strTestSymbol);

		this->f_InsertLVItem_Text	(lvItem,  3, p->Spec.strTestName);

		this->f_InsertLVItem_Text	(lvItem,  4, p->Spec.strTestUnit);

		switch (p->Spec.stDataFmt.nMode)
		{
			case ENUM_CSPEC_DATA_MODE::M00_DBL_DEFAULT:			strTemp.Format("%8.3f",  p->Spec.stLimit.LSL_VAR.dblVal); break;
			case ENUM_CSPEC_DATA_MODE::M10_UINT_DEFAULT:		strTemp.Format("%d",	 p->Spec.stLimit.LSL_VAR.ulVal); break;
	
			case ENUM_CSPEC_DATA_MODE::M21_UINT_HEX_2:			strTemp.Format("0x%02x", p->Spec.stLimit.LSL_VAR.ulVal); break;	
			case ENUM_CSPEC_DATA_MODE::M22_UINT_HEX_4:			strTemp.Format("0x%04x", p->Spec.stLimit.LSL_VAR.ulVal); break;		
			case ENUM_CSPEC_DATA_MODE::M23_UINT_HEX_6:			strTemp.Format("0x%06x", p->Spec.stLimit.LSL_VAR.ulVal); break;	
			case ENUM_CSPEC_DATA_MODE::M24_UINT_HEX_8:			strTemp.Format("0x%08x", p->Spec.stLimit.LSL_VAR.ulVal); break;		

			case ENUM_CSPEC_DATA_MODE::M31_UINT_BIN_1:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.LSL_VAR.ulVal, 1); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M32_UINT_BIN_2:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.LSL_VAR.ulVal, 2); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M33_UINT_BIN_3:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.LSL_VAR.ulVal, 3); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M34_UINT_BIN_4:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.LSL_VAR.ulVal, 4); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M35_UINT_BIN_5:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.LSL_VAR.ulVal, 5); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M36_UINT_BIN_6:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.LSL_VAR.ulVal, 6); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M37_UINT_BIM_7:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.LSL_VAR.ulVal, 7); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M38_UINT_BIN_8:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.LSL_VAR.ulVal, 8); break;		// $ 2013.11.19 Add

			default:
				break;
		}	
		this->f_InsertLVItem_CStr	(lvItem,  5, strTemp);

		switch (p->Spec.stDataFmt.nMode)
		{
			case ENUM_CSPEC_DATA_MODE::M00_DBL_DEFAULT:			strTemp.Format("%8.3f",  p->Spec.stLimit.HSL_VAR.dblVal); break;
			case ENUM_CSPEC_DATA_MODE::M10_UINT_DEFAULT:		strTemp.Format("%d",	 p->Spec.stLimit.HSL_VAR.ulVal); break;
	
			case ENUM_CSPEC_DATA_MODE::M21_UINT_HEX_2:			strTemp.Format("0x%02x", p->Spec.stLimit.HSL_VAR.ulVal); break;	
			case ENUM_CSPEC_DATA_MODE::M22_UINT_HEX_4:			strTemp.Format("0x%04x", p->Spec.stLimit.HSL_VAR.ulVal); break;		
			case ENUM_CSPEC_DATA_MODE::M23_UINT_HEX_6:			strTemp.Format("0x%06x", p->Spec.stLimit.HSL_VAR.ulVal); break;	
			case ENUM_CSPEC_DATA_MODE::M24_UINT_HEX_8:			strTemp.Format("0x%08x", p->Spec.stLimit.HSL_VAR.ulVal); break;		

			case ENUM_CSPEC_DATA_MODE::M31_UINT_BIN_1:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.HSL_VAR.ulVal, 1); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M32_UINT_BIN_2:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.HSL_VAR.ulVal, 2); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M33_UINT_BIN_3:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.HSL_VAR.ulVal, 3); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M34_UINT_BIN_4:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.HSL_VAR.ulVal, 4); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M35_UINT_BIN_5:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.HSL_VAR.ulVal, 5); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M36_UINT_BIN_6:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.HSL_VAR.ulVal, 6); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M37_UINT_BIM_7:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.HSL_VAR.ulVal, 7); break;		// $ 2013.11.19 Add
			case ENUM_CSPEC_DATA_MODE::M38_UINT_BIN_8:			strTemp = m_var.pTest->f_testdata_conv_to_Binary  (pnum, p->Spec.stLimit.HSL_VAR.ulVal, 8); break;		// $ 2013.11.19 Add

			default:
				break;
		}
		this->f_InsertLVItem_CStr	(lvItem,  6, strTemp);

		
		CString sBuf;
		sBuf.Format("%s", p->Spec.strDataFormat.GetString());
		m_list_sedit.SetItemText(lvItem.iItem, 7, sBuf);	



		m_list_sedit.UnlockWindowUpdate();

	}

}


void CDlg_Spec::f_InsertCol(LVCOLUMN &lv, int nCol, int nWidth, LPTSTR szHeader, int iFmt )
{
	lv.iSubItem			= nCol; 
	lv.cx				= nWidth; 
	lv.pszText			= szHeader;
	lv.fmt				= iFmt;	

	m_list_sedit.InsertColumn(nCol, &lv);
}

void CDlg_Spec::f_InsertLVItem_CStr   (LV_ITEM &lvItem, int nCol, CString	&str	)
{
	m_list_sedit.SetItemText(lvItem.iItem, nCol , str.operator LPCTSTR());
}

void CDlg_Spec::f_InsertLVItem_Text(LV_ITEM &lvItem, int nCol, const char * szText)
{  
	m_list_sedit.SetItemText(lvItem.iItem, nCol , szText);
}

void CDlg_Spec::f_InsertLVItem_uint  (LV_ITEM &lvItem, int nCol, unsigned	uData		, const char *szFmt)
{
	CString sBuf;		
	sBuf.Format(szFmt, uData);
	m_list_sedit.SetItemText(lvItem.iItem, nCol , sBuf.operator LPCTSTR());
}

void CDlg_Spec::f_InsertLVItem_float (LV_ITEM &lvItem, int nCol, double	fData		, const char *szFmt)
{
	CString sBuf;		
	sBuf.Format(szFmt, fData);
	m_list_sedit.SetItemText(lvItem.iItem, nCol , sBuf.operator LPCTSTR());
}
