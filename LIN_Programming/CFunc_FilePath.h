#pragma once

#include "CTest_State.h"


class CFunc_FilePath  
{
public:
	CFunc_FilePath();
	virtual ~CFunc_FilePath();

	char m_szDrive		[MAX_PATH];
	char m_szDir		[MAX_PATH];
	char m_szFilename	[MAX_PATH];
	char m_szExt		[MAX_PATH];
	char m_szPullPath	[MAX_PATH];


	void	f_filename_remove_path (char *filename);
	void	f_filename_remove_ext (char *filename );

	void	f_filename_remove_ext   (CString &strFilename);
	void	f_filename_remove_path  (CString &strFilename);
	void	f_filename_extract_path (CString &strFilename);


	void	f_filename_remove_filename (char *filename_dest, const char *filename_src );
	void	f_filename_change_ext (char *filename, char *ext);
	
	//
	bool f_path_Query_isExistFile(char *filename);
	bool f_path_Query_isExistFile(CString &filename);
	bool f_path_Query_isExistFile(std::string &s);


	bool f_path_create_directory_with_full_pathname (char *path);
	void f_path_create_full_pathname (char *path );
	bool f_path_create_directory     (char *path );

	bool f_path_Query_exist_path (char path[]);
	bool f_Query_exist_file      (char filename[]);
};