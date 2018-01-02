#include "stdafx.h"
#include "LIN_Programming.h"

#include "CTest_Main.h"
#include "CFunc_File.h"



CFunc_File::CFunc_File(void)
{
	this->m_var.bSaveComplete	= true;

	this->m_var.nAr				= 0;
	this->m_var.nTitem			= 0;
}


CFunc_File::~CFunc_File(void)
{
}


void CFunc_File::f_Open_File (void)
{
	CStdioFile		file;
	CFileException	ex;
	CString			filename;
	CString			msg;

	filename.Format("TEST.txt"); 

	if (!file.Open(filename, CFile::modeCreate | CFile::modeRead | CFile::modeWrite, &ex))
	{
		TCHAR szError[1024] = {0, };

		ex.GetErrorMessage(szError, 1024);
		msg.Format("File Open Fail.\r\n\r\n%s", szError);

		return ;
	}

	file.Write("12345678910", 11); 

	file.Close();

	return ;
}