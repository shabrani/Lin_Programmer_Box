// CDlg_Diag_MCU_ComPort.cpp : implementation file
//

#include "stdafx.h"
#include "LIN_Programming.h"
#include "CDlg_Diag_MCU_ComPort.h"
#include "afxdialogex.h"


// CDlg_Diag_MCU_ComPort dialog

IMPLEMENT_DYNAMIC(CDlg_Diag_MCU_ComPort, CDialogEx)

CDlg_Diag_MCU_ComPort::CDlg_Diag_MCU_ComPort(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg_Diag_MCU_ComPort::IDD, pParent)
{

}

CDlg_Diag_MCU_ComPort::~CDlg_Diag_MCU_ComPort()
{
}

void CDlg_Diag_MCU_ComPort::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CWB_MCU_PORT_CONNECTED, m_nib_Connected);

	DDX_Control(pDX, IDC_LIST_MSG, m_list);
	DDX_Control(pDX, IDC_BTN_CONNECT, m_btn_Connect);


	DDX_Control(pDX, IDC_CWB_PLC_OUT_1, m_nib_Plc_Out1);
	DDX_Control(pDX, IDC_CWB_PLC_OUT_2, m_nib_Plc_Out2);
	DDX_Control(pDX, IDC_CWB_PLC_OUT_3, m_nib_Plc_Out3);
	DDX_Control(pDX, IDC_CWB_PLC_OUT_4, m_nib_Plc_Out4);

	DDX_Control(pDX, IDC_CWB_PLC_IN_1, m_nib_Plc_In1);
	DDX_Control(pDX, IDC_CWB_PLC_IN_2, m_nib_Plc_In2);

	DDX_Control(pDX, IDC_EDIT_SEND, m_edit_Send);
}


BEGIN_MESSAGE_MAP(CDlg_Diag_MCU_ComPort, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlg_Diag_MCU_ComPort::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlg_Diag_MCU_ComPort::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CDlg_Diag_MCU_ComPort::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_CLEAR_LIST, &CDlg_Diag_MCU_ComPort::OnBnClickedBtnClearList)
	ON_BN_CLICKED(IDC_BTN_IDN, &CDlg_Diag_MCU_ComPort::OnBnClickedBtnIdn)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CDlg_Diag_MCU_ComPort::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_SEND, &CDlg_Diag_MCU_ComPort::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CDlg_Diag_MCU_ComPort message handlers
BOOL CDlg_Diag_MCU_ComPort::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pMCU = m_cfg.pTest->m_pMCU;
	
	GetDlgItem(IDC_EDIT_BAUDRATE)->EnableWindow(false);


	if (pMCU->m_pCom->m_bConnected)
	{
		this->m_nib_Connected.SetValue(true);
		f_PrintStr("통신이 연결되어 있습니다.");
		SetDlgItemText(IDC_BTN_CONNECT, "Close");

		GetDlgItem(IDC_EDIT_COM_PORT)->EnableWindow(false);
	}
	else
	{
		this->m_nib_Connected.SetValue(false);
		f_PrintStr("통신이 연결되지 않았습니다.");

		SetDlgItemText(IDC_BTN_CONNECT, "Open");
		GetDlgItem(IDC_EDIT_COM_PORT)->EnableWindow(true);
	}

	CString strComPort, strBaudRate;


	strBaudRate.Format("%d", pMCU->m_cfg.nBaudRate);
	SetDlgItemText(IDC_EDIT_COM_PORT, pMCU->m_cfg.sPort);
	SetDlgItemText(IDC_EDIT_BAUDRATE, strBaudRate);
	//	SetDlgItemText(IDC_BTN_CONNECT, "Connect");

	this->UpdateData(FALSE);


	{
		CString sBuf;

		sBuf.Format("PLC IN ?");
		m_edit_Send.SetWindowTextA(sBuf);

		OnBnClickedBtnSend();

		TU_UINT16 u;

		u.uint16 = atoi(pMCU->m_recv.sRecv);

		this->m_nib_Plc_In1.SetValue(u.bit.b00 ? FALSE : TRUE);
		this->m_nib_Plc_In1.SetValue(u.bit.b01 ? FALSE : TRUE);


		sBuf.Format("PLC OUT ?");
		m_edit_Send.SetWindowTextA(sBuf);

		OnBnClickedBtnSend();

		u.uint16 = atoi(pMCU->m_recv.sRecv);

		this->m_nib_Plc_Out1.SetValue(u.bit.b00 ? TRUE : FALSE);
		this->m_nib_Plc_Out2.SetValue(u.bit.b01 ? TRUE : FALSE);
		this->m_nib_Plc_Out3.SetValue(u.bit.b02 ? TRUE : FALSE);
		this->m_nib_Plc_Out4.SetValue(u.bit.b03 ? TRUE : FALSE);

	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlg_Diag_MCU_ComPort::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CDlg_Diag_MCU_ComPort::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}


void CDlg_Diag_MCU_ComPort::OnBnClickedBtnConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->UpdateData(TRUE);

	if (pMCU->m_pCom->m_bConnected)
	{
		pMCU->m_pCom->ClosePort();

		if (pMCU->m_pCom->m_bConnected)
		{
			f_PrintStr("통신연결이 Close 되지 않았습니다.");
		}
		else
		{
			f_PrintStr("통신연결이 Close 되었습니다.");
		}

	}
	else
	{
		CString strPort;
		CString strBaudrate;

		GetDlgItemText(IDC_EDIT_COM_PORT, strPort);
		GetDlgItemText(IDC_EDIT_BAUDRATE, strBaudrate);

		int nBaudrate = atoi(strBaudrate.GetString());

		pMCU->f_Open((LPSTR)(LPCSTR)strPort, nBaudrate);


		if (pMCU->m_pCom->m_bConnected)
		{
			f_PrintStr("통신연결이 되었습니다. ");
		}
		else
		{
			f_PrintStr("통신연결이 되지 않았습니다.");
		}
	}

	m_btn_Connect.SetWindowText(pMCU->m_pCom->m_bConnected ? "Close" : "Open");
	GetDlgItem(IDC_EDIT_COM_PORT)->EnableWindow(pMCU->m_pCom->m_bConnected ? FALSE : TRUE);
	this->m_nib_Connected.SetValue(pMCU->m_pCom->m_bConnected ? TRUE : FALSE);


	//this->UpdateData(FALSE);

}


void CDlg_Diag_MCU_ComPort::OnBnClickedBtnClearList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	while (m_list.GetCount() > 0)
		m_list.DeleteString(0);

}


void CDlg_Diag_MCU_ComPort::OnBnClickedBtnIdn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetDlgItemText(IDC_EDIT_SEND, "*IDN?");
	OnBnClickedBtnSend();
}


void CDlg_Diag_MCU_ComPort::OnBnClickedBtnExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CDlg_Diag_MCU_ComPort::OnBnClickedBtnSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pMCU->m_pCom->m_bConnected)
	{
		CString strBuf;
		this->GetDlgItemTextA(IDC_EDIT_SEND, strBuf);

		f_PrintStr("Send => " + strBuf);
		pMCU->f_cmd((char*)(LPCSTR)strBuf);

		f_PrintStr("Recv <= " + pMCU->m_recv.sRecv);
	}
	else
	{
		f_PrintStr("통신이 연결되지 않았습니다");
	}
}



void CDlg_Diag_MCU_ComPort::f_PrintStr(CString &str)
{
	if (m_list.GetCount() > 10) m_list.DeleteString(0);
	m_list.SetCurSel(m_list.GetCount());
	m_list.AddString(str);
}

void CDlg_Diag_MCU_ComPort::f_PrintStr(char *szString)
{
	if (m_list.GetCount() > 10) m_list.DeleteString(0);
	m_list.SetCurSel(m_list.GetCount());
	m_list.AddString(szString);
}

BEGIN_EVENTSINK_MAP(CDlg_Diag_MCU_ComPort, CDialogEx)
	ON_EVENT(CDlg_Diag_MCU_ComPort, IDC_CWB_PLC_OUT_1, DISPID_CLICK, CDlg_Diag_MCU_ComPort::ClickCwbPlcOut1, VTS_NONE)
	ON_EVENT(CDlg_Diag_MCU_ComPort, IDC_CWB_PLC_OUT_2, DISPID_CLICK, CDlg_Diag_MCU_ComPort::ClickCwbPlcOut2, VTS_NONE)
	ON_EVENT(CDlg_Diag_MCU_ComPort, IDC_CWB_PLC_OUT_3, DISPID_CLICK, CDlg_Diag_MCU_ComPort::ClickCwbPlcOut3, VTS_NONE)
	ON_EVENT(CDlg_Diag_MCU_ComPort, IDC_CWB_PLC_OUT_4, DISPID_CLICK, CDlg_Diag_MCU_ComPort::ClickCwbPlcOut4, VTS_NONE)
	ON_EVENT(CDlg_Diag_MCU_ComPort, IDC_CWB_PLC_IN_1, DISPID_CLICK, CDlg_Diag_MCU_ComPort::ClickCwbPlcIn1, VTS_NONE)
	ON_EVENT(CDlg_Diag_MCU_ComPort, IDC_CWB_PLC_IN_2, DISPID_CLICK, CDlg_Diag_MCU_ComPort::ClickCwbPlcIn2, VTS_NONE)
END_EVENTSINK_MAP()


void CDlg_Diag_MCU_ComPort::ClickCwbPlcOut1()
{

	bool bBtn = m_nib_Plc_Out1.GetValue();
	m_nib_Plc_Out1.SetValue(!bBtn);


	TU_UINT16 u;
	u.uint16 = 0;

	u.bit.b00 = (m_nib_Plc_Out1.GetValue() ? 1 : 0);
	u.bit.b01 = (m_nib_Plc_Out2.GetValue() ? 1 : 0);
	u.bit.b02 = (m_nib_Plc_Out3.GetValue() ? 1 : 0);
	u.bit.b03 = (m_nib_Plc_Out4.GetValue() ? 1 : 0);


	CString sBuf;

	sBuf.Format("PORT PLC %d", u.uint16);
	m_edit_Send.SetWindowTextA(sBuf);

	OnBnClickedBtnSend();
}


void CDlg_Diag_MCU_ComPort::ClickCwbPlcOut2()
{
	bool bBtn = m_nib_Plc_Out2.GetValue();
	m_nib_Plc_Out2.SetValue(!bBtn);


	TU_UINT16 u;
	u.uint16 = 0;

	u.bit.b00 = (m_nib_Plc_Out1.GetValue() ? 1 : 0);
	u.bit.b01 = (m_nib_Plc_Out2.GetValue() ? 1 : 0);
	u.bit.b02 = (m_nib_Plc_Out3.GetValue() ? 1 : 0);
	u.bit.b03 = (m_nib_Plc_Out4.GetValue() ? 1 : 0);


	CString sBuf;

	sBuf.Format("PORT PLC %d", u.uint16);
	m_edit_Send.SetWindowTextA(sBuf);

	OnBnClickedBtnSend();
}


void CDlg_Diag_MCU_ComPort::ClickCwbPlcOut3()
{
	bool bBtn = m_nib_Plc_Out3.GetValue();
	m_nib_Plc_Out3.SetValue(!bBtn);


	TU_UINT16 u;
	u.uint16 = 0;

	u.bit.b00 = (m_nib_Plc_Out1.GetValue() ? 1 : 0);
	u.bit.b01 = (m_nib_Plc_Out2.GetValue() ? 1 : 0);
	u.bit.b02 = (m_nib_Plc_Out3.GetValue() ? 1 : 0);
	u.bit.b03 = (m_nib_Plc_Out4.GetValue() ? 1 : 0);


	CString sBuf;

	sBuf.Format("PORT PLC %d", u.uint16);
	m_edit_Send.SetWindowTextA(sBuf);

	OnBnClickedBtnSend();
}


void CDlg_Diag_MCU_ComPort::ClickCwbPlcOut4()
{
	bool bBtn = m_nib_Plc_Out4.GetValue();
	m_nib_Plc_Out4.SetValue(!bBtn);


	TU_UINT16 u;
	u.uint16 = 0;

	u.bit.b00 = (m_nib_Plc_Out1.GetValue() ? 1 : 0);
	u.bit.b01 = (m_nib_Plc_Out2.GetValue() ? 1 : 0);
	u.bit.b02 = (m_nib_Plc_Out3.GetValue() ? 1 : 0);
	u.bit.b03 = (m_nib_Plc_Out4.GetValue() ? 1 : 0);


	CString sBuf;

	sBuf.Format("PORT PLC %d", u.uint16);
	m_edit_Send.SetWindowTextA(sBuf);

	OnBnClickedBtnSend();
}


void CDlg_Diag_MCU_ComPort::ClickCwbPlcIn1()
{
	CString sBuf;

	sBuf.Format("PLC IN ?");
	m_edit_Send.SetWindowTextA(sBuf);

	OnBnClickedBtnSend();

	TU_UINT16 u;

	u.uint16 = atoi(pMCU->m_recv.sRecv);

	this->m_nib_Plc_In1.SetValue(u.bit.b00 ? FALSE : TRUE);
	this->m_nib_Plc_In1.SetValue(u.bit.b01 ? FALSE : TRUE);
}


void CDlg_Diag_MCU_ComPort::ClickCwbPlcIn2()
{
	CString sBuf;

	sBuf.Format("PLC IN ?");
	m_edit_Send.SetWindowTextA(sBuf);

	OnBnClickedBtnSend();

	TU_UINT16 u;

	u.uint16 = atoi(pMCU->m_recv.sRecv);

	this->m_nib_Plc_In1.SetValue(u.bit.b00 ? FALSE : TRUE);
	this->m_nib_Plc_In1.SetValue(u.bit.b01 ? FALSE : TRUE);

}
