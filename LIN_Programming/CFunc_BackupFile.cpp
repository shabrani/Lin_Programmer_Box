#include "stdafx.h"
#include "CFunc_BackupFile.h"
#include <Windows.h>
#include <tchar.h>


CFunc_BackupFile::CFunc_BackupFile(int nCopyWait_ms, CString strBackupDir)
{
	m_var.strBackupDir = strBackupDir;
	m_var.nCopyWait_ms = nCopyWait_ms;

}


CFunc_BackupFile::~CFunc_BackupFile(void)
{

}


BOOL CFunc_BackupFile::f_create_backupfile (CString strFullPathName)
{

	m_var.strFullPathName = strFullPathName;

	int nLen	= m_var.strFullPathName.GetLength();
	int nPath	= m_var.strFullPathName.ReverseFind('\\');
	int nExt	= m_var.strFullPathName.ReverseFind('.');

	//오늘의 날자를 가져온다.
	//오늘의 날자로 폴더이름을 구성한다. 
	//Backup_2015_0820

	CTime tmBackupDate = CTime::GetCurrentTime();							// $ Add 2015.08.20 
	CString strBackupDate = tmBackupDate.Format("backup_%Y_%m%d");			// $ Add 2015.08.20 
	CString strNewFileExt = tmBackupDate.Format(".~%Y%m%d_%H%M%S");

	m_var.strExt			= m_var.strFullPathName.Right (nLen - nExt  - 1);
	m_var.strFilename		= m_var.strFullPathName.Right (nLen - nPath - 1);
	m_var.strPath			= m_var.strFullPathName.Left  (nPath);

	m_var.strBackupPath		= m_var.strPath  + "\\" + m_var.strBackupDir;		

	f_create_path(m_var.strBackupPath);					// $ Add 2015.08.20 

	m_var.strBackupPath += "\\" + strBackupDate;		// $ Add 2015.08.20 
	f_create_path(m_var.strBackupPath);					// $ Add 2015.08.20 


	CString strNewFilename = m_var.strBackupPath + "\\" + m_var.strFilename + strNewFileExt;

	BOOL bRtn = CopyFile(m_var.strFullPathName, strNewFilename, FALSE);
	
	if (0 != bRtn)
	{
		Sleep(m_var.nCopyWait_ms);
		return true;
	}
	else
	{
		return false;
	}



	return TRUE;
}

bool	CFunc_BackupFile::f_create_path(CString strPath)
{

	CFileFind finder;
	BOOL bResult = finder.FindFile(strPath);

	if (FALSE == bResult)
	{
		finder.Close();

		CreateDirectory(strPath, NULL);			// 디렉토리 생성
		return false;											// 파일이 없음으로 0을 리턴한다.
	}

	return true;
}

