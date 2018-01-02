#pragma once


// 
// create auto backup file
//
// rev 0.0 2015.04.14 sjim   자동파일 백업프로그램 클래스 작성
//		class 생성자에서 백업폴더 및 확장자 수정가능
//
// rev 0.1 2015.04.16 sjkim  백업파일을 찾는 오류 발생 => 이부분만 api함수 이용하여 수정함
//
// rev 0.2 2015.08.20 sjkim  백업폴더이름에 백업일자를 넣어서 언제 수정이 되었는지 쉽게 찾을수 있도록 함.
//
// rev 0.3 2015.08.20 sjkim  백업폴더와 백업파일 이름에 백업일자를 추가하여 쉽게 언제 백업이 되었는지 확인이 가능하도록 함.
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

