#pragma once


// 
// create auto backup file
//
// rev 0.0 2015.04.14 sjim   �ڵ����� ������α׷� Ŭ���� �ۼ�
//		class �����ڿ��� ������� �� Ȯ���� ��������
//
// rev 0.1 2015.04.16 sjkim  ��������� ã�� ���� �߻� => �̺κи� api�Լ� �̿��Ͽ� ������
//
// rev 0.2 2015.08.20 sjkim  ��������̸��� ������ڸ� �־ ���� ������ �Ǿ����� ���� ã���� �ֵ��� ��.
//
// rev 0.3 2015.08.20 sjkim  ��������� ������� �̸��� ������ڸ� �߰��Ͽ� ���� ���� ����� �Ǿ����� Ȯ���� �����ϵ��� ��.
//


class CFunc_BackupFile
{
public:
	CFunc_BackupFile (int nCopyWait_ms = 1000, CString strBackupDir = _T("auto_backup_specfiles"));
	~CFunc_BackupFile(void);


	BOOL	f_create_backupfile (CString strFullPathName);

private:

	//bool    f_copy_file (int backup_number);
	//int		f_find_backupfile_number ();
	//int     f_find_backupfile_number (CString strFindFIle);
	//int		f_find_backupfile_final_number ();

	bool	f_create_path(CString strPath);


	struct
	{
		CString strFullPathName;
		CString strFileTitle;
		CString strPath;
		CString strExt;
		CString strFilename;

		//int		nbackup_number;
		CString strFindName;

		CString strBackupExt;
		CString strBackupDir;
		int nCopyWait_ms;
		CString strBackupPath;


		int file_count;

	}m_var;

};

