// CDlg_Spec_Item.cpp : implementation file
//

#include "stdafx.h"
#include "LIN_Programming.h"
#include "CDlg_Spec_Item.h"
#include "afxdialogex.h"


// CDlg_Spec_Item dialog

IMPLEMENT_DYNAMIC(CDlg_Spec_Item, CDialog)

CDlg_Spec_Item::CDlg_Spec_Item(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Spec_Item::IDD, pParent)

	, m_edit_TestName(_T(""))
	, m_edit_DataFormat(_T(""))
	, m_edit_Symbol(_T(""))
	, m_edit_Unit(_T(""))
{

}

CDlg_Spec_Item::~CDlg_Spec_Item()
{
}

void CDlg_Spec_Item::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CWN_PNUM,			m_cwn_nPnum);
	DDX_Control(pDX, IDC_CWN_TNUM,			m_cwn_nTnum);
	DDX_Control(pDX, IDC_COMBO_REFTITEM,	m_combo_RefTitem);
	DDX_Control(pDX, IDC_COMBO_DATA_TYPE,	m_combo_DataType);
	DDX_Control(pDX, IDC_CWN_BAUDRATE,		m_edit_Baudrate);
	DDX_Control(pDX, IDC_CWN_HSL,			m_cwn_HSL);
	DDX_Control(pDX, IDC_CWN_LSL,			m_cwn_LSL);

	DDX_Text(pDX, IDC_EDIT_TEST_NAME,		m_edit_TestName);
	DDX_Text(pDX, IDC_EDIT_DATA_FORMAT,		m_edit_DataFormat);
	DDX_Text(pDX, IDC_EDIT_SYMBOL,			m_edit_Symbol);
	DDX_Text(pDX, IDC_EDIT_UNIT,			m_edit_Unit);
	DDX_Control(pDX, IDC_COMBO_LIMIT_MODE, m_combo_LimitMode);
}


BEGIN_MESSAGE_MAP(CDlg_Spec_Item, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA_TYPE, &CDlg_Spec_Item::OnCbnSelchangeComboDataType)
	ON_CBN_SELCHANGE(IDC_COMBO_LIMIT_MODE, &CDlg_Spec_Item::OnCbnSelchangeComboLimitMode)
END_MESSAGE_MAP()


// CDlg_Spec_Item message handlers
void CDlg_Spec_Item::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_var.pPropertySheet)	
		delete m_var.pPropertySheet;
}

BOOL CDlg_Spec_Item::OnInitDialog()
{
	CDialog::OnInitDialog();

	unsigned temp;

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &m_var.pCSpec->m_stSpecInfo.Lin;
	temp = pLin->nChip;

	this->m_cwn_nPnum.SetValue (m_var.pnum);

	// LIN Information Initialize ////////////////////////////////////////////
	this->m_edit_Baudrate.SetValue (pLin->nBaudrate);

	// Ref Titem Initialize //////////////////////////////////////////////////
	f_ComboBox_Initialize ();
	f_Page_Initialize	  ();

	pLin->nChip = temp;
	//////////////////////////////////////////////////////////////////////////
	this->m_cwn_nPnum.SetMinMax		   (0, m_var.pCSpec->m_stStatus.nTitem);
	this->m_cwn_nPnum.SetRangeChecking (true);


	this->f_spec_load_from_CSpec(m_var.pnum);

	this->m_cwn_nPnum.SetValue  (m_var.pnum);

	this->UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control

}



void CDlg_Spec_Item::f_ComboBox_Initialize (void)
{
	CString sBuf;
	int nIdx, nSize;
	

	TS_CSPEC_REFFUNC *pRef;

	nSize = m_var.pCSpec->m_stMode.vInfoRefFuncTitem.size();
	for (nIdx=0; nIdx < nSize; nIdx++)
	{
		pRef = &m_var.pCSpec->m_stMode.vInfoRefFuncTitem[nIdx];
		sBuf.Format ("%03d. %s", pRef->nId,  pRef->sInfo.GetString() );
		this->m_combo_RefTitem.AddString(sBuf);
	}

	m_var.pCSpec->m_stMode.ItemMode.m_DataFormat.f_cbox_Initial_Set(this->m_combo_DataType, "%02d. %s");
	m_var.pCSpec->m_stMode.ItemMode.m_DataLimitMode.f_cbox_Initial_Set(this->m_combo_LimitMode, "%02d. %s");
}

void CDlg_Spec_Item::f_Page_Initialize (void)
{

	m_var.pPropertySheet = new CPropertySheet;

	//////////////////////////////////////////////////////////////////////
	// CR665
	m_page.CR665.m_var.pParentDlg = this;
	m_page.CR665.m_var.pTest	  = m_var.pTest;
	m_page.CR665.m_var.pCSpec	  = m_var.pCSpec;
	
	m_var.pPropertySheet->AddPage(&m_page.CR665);

	//////////////////////////////////////////////////////////////////////
	// TLE8880
	m_page.TLE8880.m_var.pParentDlg = this;
	m_page.TLE8880.m_var.pTest	  = m_var.pTest;
	m_page.TLE8880.m_var.pCSpec	  = m_var.pCSpec;
	
	m_var.pPropertySheet->AddPage(&m_page.TLE8880);

	//////////////////////////////////////////////////////////////////////
	// TLE8881
	m_page.TLE8881.m_var.pParentDlg = this;
	m_page.TLE8881.m_var.pTest	  = m_var.pTest;
	m_page.TLE8881.m_var.pCSpec	  = m_var.pCSpec;
	
	m_var.pPropertySheet->AddPage(&m_page.TLE8881);

	//////////////////////////////////////////////////////////////////////
	// L9916
	m_page.L9916.m_var.pParentDlg = this;
	m_page.L9916.m_var.pTest	  = m_var.pTest;
	m_page.L9916.m_var.pCSpec	  = m_var.pCSpec;
	
	m_var.pPropertySheet->AddPage(&m_page.L9916);

	//////////////////////////////////////////////////////////////////////
	// LIN2112
	m_page.LIN2112.m_var.pParentDlg = this;
	m_page.LIN2112.m_var.pTest	  = m_var.pTest;
	m_page.LIN2112.m_var.pCSpec	  = m_var.pCSpec;
	
	m_var.pPropertySheet->AddPage(&m_page.LIN2112);

	//////////////////////////////////////////////////////////////////////
	// SetEtc
	m_page.SetEtc.m_var.pParentDlg = this;
	m_page.SetEtc.m_var.pTest	  = m_var.pTest;
	m_page.SetEtc.m_var.pCSpec	  = m_var.pCSpec;
	
	m_var.pPropertySheet->AddPage(&m_page.SetEtc);

	//////////////////////////////////////////////////////////////////////
	// Create PropertySheet
	m_var.pPropertySheet->Create        (this, WS_CHILD | WS_VISIBLE, 0); 
	m_var.pPropertySheet->ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	m_var.pPropertySheet->ModifyStyle   (0, WS_TABSTOP);

	//////////////////////////////////////////////////////////////////////
	// Active PropertySheet
	m_var.pPropertySheet->SetActivePage(&m_page.LIN2112);
	m_var.pPropertySheet->SetActivePage(&m_page.L9916);
	m_var.pPropertySheet->SetActivePage(&m_page.TLE8880);
	m_var.pPropertySheet->SetActivePage(&m_page.TLE8881);
	m_var.pPropertySheet->SetActivePage(&m_page.CR665);
	m_var.pPropertySheet->SetActivePage(&m_page.SetEtc);

    CRect rcSheet;
    this->GetWindowRect( &rcSheet );
    ScreenToClient( &rcSheet );
	m_var.pPropertySheet->MoveWindow(4,150,1000,650);
}

void CDlg_Spec_Item::f_spec_load_from_CSpec (unsigned pnum)
{

	this->m_var.pTitem	= &m_var.pCSpec->m_vTitem[pnum];
		
	CFunc_Spec_Item_Main			*pItemSpec;
	pItemSpec = &m_var.pCSpec->m_vTitem[pnum].Spec;

	
	this->m_cwn_nTnum.SetValue (pItemSpec->nTnum);

	this->m_edit_Unit			= pItemSpec->strTestUnit;
	this->m_edit_Symbol			= pItemSpec->strTestSymbol;
	this->m_edit_TestName		= pItemSpec->strTestName;
	this->m_edit_DataFormat		= pItemSpec->strDataFormat;

	///////////////////////////////////////////////////////////////////////////////////////////////
	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_var.pCSpec->m_stSpecInfo.Lin;

	this->m_edit_Baudrate.SetValue(pLin->nBaudrate);

	///////////////////////////////////////////////////////////////////////////////////////////////
	

	int nIndex	 = m_var.pCSpec->f_modeTable_find_vec_record (pItemSpec->nRefTitem, m_var.pCSpec->m_stMode.vInfoRefFuncTitem );	
	this->m_combo_RefTitem.SetCurSel	 (nIndex);

	unsigned idx = m_var.pCSpec->m_stMode.ItemMode.m_DataFormat.f_find_idx(pItemSpec->stDataFmt.nMode);
	this->m_combo_DataType.SetCurSel (idx);

	this->m_combo_LimitMode.SetCurSel (pItemSpec->stLimit.nMode);
	

	f_SPEC_LIMIT_View_Select_with_Mode();
	f_SPEC_LIMIT_Format_Change_with_Mode();

	switch(pItemSpec->stDataFmt.nMode )
	{
	case ENUM_CSPEC_DATA_MODE::M00_DBL_DEFAULT:
		this->m_cwn_LSL.SetValue	 	(m_var.pTitem->Spec.stLimit.LSL_VAR.dblVal);
		this->m_cwn_HSL.SetValue		(m_var.pTitem->Spec.stLimit.HSL_VAR.dblVal);
		break;

	default:
		this->m_cwn_LSL.SetValue	 	(pItemSpec->stLimit.LSL_VAR.ulVal);
		this->m_cwn_HSL.SetValue		(pItemSpec->stLimit.HSL_VAR.ulVal);	

		break;	
	}

	this->f_page_load_from_CSpec(pnum);

	this->UpdateData (FALSE);

}

void CDlg_Spec_Item::f_spec_save_to_CSpec (unsigned pnum)
{
	this->UpdateData (TRUE);
	
	this->m_var.pTitem = &m_var.pCSpec->m_vTitem[pnum];
	
	CFunc_Spec_Item_Main			*pItemSpec;
	pItemSpec = &m_var.pCSpec->m_vTitem[pnum].Spec;

	///////////////////////////////////////////////////////////////////////////////////////////////
	pItemSpec->nTnum	= (unsigned) this->m_cwn_nTnum.GetValue ();

	
	pItemSpec->strTestUnit	= this->m_edit_Unit;
	pItemSpec->strTestSymbol= this->m_edit_Symbol;
	pItemSpec->strTestName	= this->m_edit_TestName;
	pItemSpec->strDataFormat= this->m_edit_DataFormat;

	///////////////////////////////////////////////////////////////////////////////////////////////
	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_var.pCSpec->m_stSpecInfo.Lin;

	pLin->nBaudrate = (unsigned)this->m_edit_Baudrate.GetValue();

	///////////////////////////////////////////////////////////////////////////////////////////////

	int nIndex;	
	nIndex = this->m_combo_RefTitem.GetCurSel ();
	pItemSpec->nRefTitem = m_var.pCSpec->m_stMode.vInfoRefFuncTitem[nIndex].nId;	
	
	pItemSpec->stLimit.nMode = m_var.pCSpec->m_stMode.ItemMode.m_DataLimitMode.f_cbox_GetCurSel(m_combo_LimitMode);
	pItemSpec->stDataFmt.nMode = m_var.pCSpec->m_stMode.ItemMode.m_DataFormat.f_cbox_GetCurSel(m_combo_DataType);


	switch(m_var.pTitem->Spec.stDataFmt.nMode )
	{
	case ENUM_CSPEC_DATA_MODE::M00_DBL_DEFAULT:
		m_var.pTitem->Spec.stLimit.HSL_VAR.dblVal	= this->m_cwn_HSL.GetValue	();
		m_var.pTitem->Spec.stLimit.LSL_VAR.dblVal	= this->m_cwn_LSL.GetValue	();	
		break;

	default:
		m_var.pTitem->Spec.stLimit.HSL_VAR.ulVal	= (unsigned)this->m_cwn_HSL.GetValue	();
		m_var.pTitem->Spec.stLimit.LSL_VAR.ulVal	= (unsigned)this->m_cwn_LSL.GetValue	();	
		break;		
	}
			

	pItemSpec->strTestSymbol= this->m_edit_Symbol;
	pItemSpec->strTestName	= this->m_edit_TestName;


	///////////////////////////////////////////////////////////////////////////////////////////////

	this->f_page_save_to_CSepc(pnum);

	this->UpdateData (FALSE);

}

void CDlg_Spec_Item::f_page_load_from_CSpec(unsigned pnum)
{

	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_var.pCSpec->m_stSpecInfo.Lin;

	unsigned nPrev	= m_var.pTitem->Spec.nPnum_Prev;

	
	switch(pLin->nChip)
	{
	case SELECT_CR665:
		this->m_page.CR665.m_combo_regulator.SetCurSel(pLin->nRegulator);
		this->m_page.CR665.m_combo_version.SetCurSel(pLin->nChip);
		this->m_page.SetEtc.f_Dlg_Set  (pnum);
		this->m_page.CR665.f_Dlg_Set   (pnum);
		break;

	case SELECT_TLE8880:
		this->m_page.TLE8880.m_combo_regulator.SetCurSel(pLin->nRegulator);
		this->m_page.TLE8880.m_combo_version.SetCurSel(pLin->nChip);
		this->m_page.SetEtc.f_Dlg_Set  (pnum);
		this->m_page.TLE8880.f_Dlg_Set (pnum);
		break;

	case SELECT_TLE8881:
		this->m_page.TLE8881.m_combo_regulator.SetCurSel(pLin->nRegulator);
		this->m_page.TLE8881.m_combo_version.SetCurSel(pLin->nChip);
		this->m_page.SetEtc.f_Dlg_Set  (pnum);
		this->m_page.TLE8881.f_Dlg_Set (pnum);
		break;

	case SELECT_L9916:
		this->m_page.SetEtc.f_Dlg_Set  (pnum);
		this->m_page.L9916.f_Dlg_Set (pnum);
		break;

	case SELECT_LIN2112:
		this->m_page.SetEtc.f_Dlg_Set  (pnum);
		this->m_page.LIN2112.f_Dlg_Set (pnum);
		break;

	default:
		break;
	}


	this->UpdateData (FALSE);
}

void CDlg_Spec_Item::f_page_save_to_CSepc  (unsigned pnum)
{
	TS_CSPEC_SPECINFO_LIN	*pLin;
	pLin = &this->m_var.pCSpec->m_stSpecInfo.Lin;

	this->UpdateData (TRUE);

	switch(pLin->nChip)
	{
	case SELECT_CR665:
		this->m_page.SetEtc.f_Dlg_Read  (pnum);
		this->m_page.CR665.f_Dlg_Read   (pnum);
		break;

	case SELECT_TLE8880:
		this->m_page.SetEtc.f_Dlg_Read  (pnum);
		this->m_page.TLE8880.f_Dlg_Read (pnum);
		break;

	case SELECT_TLE8881:
		this->m_page.SetEtc.f_Dlg_Read  (pnum);
		this->m_page.TLE8881.f_Dlg_Read (pnum);
		break;

	case SELECT_L9916:
		this->m_page.SetEtc.f_Dlg_Read  (pnum);
		this->m_page.L9916.f_Dlg_Read (pnum);
		break;

	case SELECT_LIN2112:
		this->m_page.SetEtc.f_Dlg_Read  (pnum);
		this->m_page.LIN2112.f_Dlg_Read (pnum);
		break;

	default:
		break;
	}

}


void CDlg_Spec_Item::f_SPEC_LIMIT_View_Select_with_Mode()
{

	unsigned nLimitMode	= this->m_combo_LimitMode.GetCurSel  ();

	switch(nLimitMode)
	{
		case ENUM_CSPEC_LIMIT_MODE::M0_BOTH_LIMIT	: 
			GetDlgItem (IDC_CWN_HSL)->ShowWindow (SW_SHOW);
			GetDlgItem (IDC_CWN_LSL)->ShowWindow (SW_SHOW);
			GetDlgItem (IDC_STATIC_HSL)->ShowWindow (SW_SHOW);
			GetDlgItem (IDC_STATIC_LSL)->ShowWindow (SW_SHOW);
			break;

		case ENUM_CSPEC_LIMIT_MODE::M1_UPPER_LIMIT	:
			GetDlgItem (IDC_CWN_HSL)->ShowWindow (SW_SHOW);
			GetDlgItem (IDC_CWN_LSL)->ShowWindow (SW_HIDE);
			GetDlgItem (IDC_STATIC_HSL)->ShowWindow (SW_SHOW);
			GetDlgItem (IDC_STATIC_LSL)->ShowWindow (SW_HIDE);
			break;

		case ENUM_CSPEC_LIMIT_MODE::M2_LOWER_LIMIT	: 
			GetDlgItem (IDC_CWN_HSL)->ShowWindow (SW_HIDE);
			GetDlgItem (IDC_CWN_LSL)->ShowWindow (SW_SHOW);
			GetDlgItem (IDC_STATIC_HSL)->ShowWindow (SW_HIDE);
			GetDlgItem (IDC_STATIC_LSL)->ShowWindow (SW_SHOW);
			break;

		case ENUM_CSPEC_LIMIT_MODE::M3_EQUAL		: 
			GetDlgItem (IDC_CWN_HSL)->ShowWindow (SW_HIDE);
			GetDlgItem (IDC_CWN_LSL)->ShowWindow (SW_SHOW);
			GetDlgItem (IDC_STATIC_HSL)->ShowWindow (SW_HIDE);
			GetDlgItem (IDC_STATIC_LSL)->ShowWindow (SW_SHOW);
			break;

		case ENUM_CSPEC_LIMIT_MODE::M4_NOT_EQUAL	: 
			GetDlgItem (IDC_CWN_HSL)->ShowWindow (SW_HIDE);
			GetDlgItem (IDC_CWN_LSL)->ShowWindow (SW_SHOW);
			GetDlgItem (IDC_STATIC_HSL)->ShowWindow (SW_HIDE);
			GetDlgItem (IDC_STATIC_LSL)->ShowWindow (SW_SHOW);
			break;

		default: 
			break;
	}

}

void CDlg_Spec_Item::f_SPEC_LIMIT_Format_Change_with_Mode()
{

	unsigned idx			= this->m_combo_DataType.GetCurSel    ();
	unsigned nDataMode		= m_var.pCSpec->m_stMode.ItemMode.m_DataFormat.f_find_mode(idx);


	CString sBuf = "";
	CString sFmt = "";


	switch(nDataMode)
	{
	case	ENUM_CSPEC_DATA_MODE::M00_DBL_DEFAULT			:	sBuf.Format("####.##0");			sFmt = "%8.3f";	break;	
	case	ENUM_CSPEC_DATA_MODE::M10_UINT_DEFAULT		    :	sBuf.Format(".");					sFmt = "%d";	break;

	case	ENUM_CSPEC_DATA_MODE::M21_UINT_HEX_2			:	sBuf.Format("%c0x%c2X",'"', '"');	sFmt = "%02X";	break;	// $ 2013.11.19 Add 							
	case	ENUM_CSPEC_DATA_MODE::M22_UINT_HEX_4			:	sBuf.Format("%c0x%c4X",'"', '"');	sFmt = "%04X";	break;		
	case 	ENUM_CSPEC_DATA_MODE::M23_UINT_HEX_6			:	sBuf.Format("%c0x%c6X",'"', '"');	sFmt = "%06X";	break;					
	case  	ENUM_CSPEC_DATA_MODE::M24_UINT_HEX_8			:	sBuf.Format("%c0x%c8X",'"', '"');	sFmt = "%08X";	break;					

	case  	ENUM_CSPEC_DATA_MODE::M31_UINT_BIN_1			:	sBuf.Format("%cb%c1b",'"', '"');	sFmt = "%01b";	break;					
	case  	ENUM_CSPEC_DATA_MODE::M32_UINT_BIN_2			:	sBuf.Format("%cb%c2b",'"', '"');	sFmt = "%02b";	break;						
	case  	ENUM_CSPEC_DATA_MODE::M33_UINT_BIN_3			:	sBuf.Format("%cb%c3b",'"', '"');	sFmt = "%03b";	break;						
	case  	ENUM_CSPEC_DATA_MODE::M34_UINT_BIN_4			:	sBuf.Format("%cb%c4b",'"', '"');	sFmt = "%04b";	break;						
	case	ENUM_CSPEC_DATA_MODE::M35_UINT_BIN_5			:	sBuf.Format("%cb%c5b",'"', '"');	sFmt = "%05b";	break;		
	case 	ENUM_CSPEC_DATA_MODE::M36_UINT_BIN_6			:	sBuf.Format("%cb%c6b",'"', '"');	sFmt = "%06b";	break;					
	case  	ENUM_CSPEC_DATA_MODE::M37_UINT_BIM_7			:	sBuf.Format("%cb%c7b",'"', '"');	sFmt = "%07b";	break;					
	case  	ENUM_CSPEC_DATA_MODE::M38_UINT_BIN_8			:	sBuf.Format("%cb%c8b",'"', '"');	sFmt = "%08b";	break;					
	}

	this->m_cwn_LSL.SetFormatString(sBuf);
	this->m_cwn_HSL.SetFormatString(sBuf);

	this->m_edit_DataFormat = sFmt;
	this->UpdateData(FALSE);
}

BEGIN_EVENTSINK_MAP(CDlg_Spec_Item, CDialog)
	ON_EVENT(CDlg_Spec_Item, IDC_BTN_EDIT, DISPID_CLICK, CDlg_Spec_Item::ClickBtnEdit, VTS_NONE)
	ON_EVENT(CDlg_Spec_Item, IDC_CWN_PNUM, 1, CDlg_Spec_Item::ValueChangedCwnPnum, VTS_PVARIANT VTS_PVARIANT VTS_BOOL)
END_EVENTSINK_MAP()


void CDlg_Spec_Item::ClickBtnEdit()
{
	// TODO: Add your message handler code here
	f_spec_save_to_CSpec(m_var.pnum);

	CDialog::OnOK();
}


void CDlg_Spec_Item::ValueChangedCwnPnum(VARIANT* Value, VARIANT* PreviousValue, BOOL OutOfRange)
{
	// TODO: Add your message handler code here
	unsigned pnum = unsigned(this->m_cwn_nPnum.GetValue ());

	if (m_var.pnum == pnum) return;							//윈도우 처음 시작시 저장하는것을 방지한다.


	if (pnum <0)
	{
		pnum = m_var.pnum;
		this->m_cwn_nPnum.SetValue (m_var.pnum);			//이전상태 유지
		return;
	}

	if ( pnum >=  m_var.pCSpec->m_stStatus.nTitem) 
	{
		pnum = m_var.pnum;
		this->m_cwn_nPnum.SetValue (m_var.pnum);			//이전상태유지
		return;
	}
	




	this->f_spec_save_to_CSpec  (m_var.pnum);
	
	m_var.pnum	= pnum;
	
	this->f_spec_load_from_CSpec(pnum);	
}


void CDlg_Spec_Item::OnCbnSelchangeComboDataType()
{
	// TODO: Add your control notification handler code here
	f_SPEC_LIMIT_View_Select_with_Mode();
	f_SPEC_LIMIT_Format_Change_with_Mode();
}


void CDlg_Spec_Item::OnCbnSelchangeComboLimitMode()
{
	// TODO: Add your control notification handler code here
	f_SPEC_LIMIT_View_Select_with_Mode();
}
