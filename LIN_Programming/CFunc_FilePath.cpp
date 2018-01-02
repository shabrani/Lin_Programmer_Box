#include "stdafx.h"

#include <string>

#include "CFunc_FilePath.h"
#include "CTest_Main.h"
#include "My_String.h"


extern CTest_Main	*pTest;

using namespace std;


CFunc_FilePath::CFunc_FilePath()
{

}

CFunc_FilePath::~CFunc_FilePath()
{

}


void CFunc_FilePath::f_filename_remove_path (char *filename)
{
	_splitpath_s (filename, m_szDrive, m_szDir,  m_szFilename, m_szExt);
	_makepath_s  (filename, MAX_PATH, NULL,  NULL, m_szFilename, m_szExt);
}


void CFunc_FilePath::f_filename_remove_ext (char *filename )
{	
	_splitpath_s (filename, m_szDrive, m_szDir,  m_szFilename, m_szExt);
	_makepath_s  (filename, MAX_PATH, m_szDrive, m_szDir,  m_szFilename, NULL);
}

void	CFunc_FilePath::f_filename_remove_ext ( CString &strFilename)
{
	int n = strFilename.Find('.');
	if ( n < 0 ) return;

	strFilename = strFilename.Left ( n );
}

void	CFunc_FilePath::f_filename_remove_path (CString &strFilename)
{
	int nSize = strFilename.GetLength();
	
	int n1 = strFilename.ReverseFind('/');
	int n2 = strFilename.ReverseFind('\\');

	int n = ( n1 > n2 ) ? n1 : n2 ;

	if ( n < 0 ) return;

	strFilename = strFilename.Right ( nSize - n - 1);
}

void	CFunc_FilePath::f_filename_extract_path (CString &strFilename)
{
	int nSize = strFilename.GetLength();
	
	int n1 = strFilename.ReverseFind('/');
	int n2 = strFilename.ReverseFind('\\');

	int n = ( n1 > n2 ) ? n1 : n2 ;

	if ( n < 0 ) return;

	strFilename = strFilename.Left ( n );
}




void CFunc_FilePath::f_filename_remove_filename (char *filename_dest, const char *filename_src )
{	
	_splitpath_s (filename_src, m_szDrive, m_szDir,  m_szFilename, m_szExt);
	_makepath_s  (filename_dest, MAX_PATH, m_szDrive, m_szDir,  "*", m_szExt);
}

void CFunc_FilePath::f_filename_change_ext (char *filename, char *ext)
{
	_splitpath_s (filename, m_szDrive, m_szDir,  m_szFilename, m_szExt);
	_makepath_s  (filename, MAX_PATH, m_szDrive, m_szDir,  m_szFilename, ext);
}



bool CFunc_FilePath::f_path_create_directory_with_full_pathname (char *path)
{
	unsigned Ans;
	unsigned n;
	unsigned i;

	char token[128];
	char new_path [MAX_PATH] = "";
	char old_path [MAX_PATH];

	::GetCurrentDirectory (MAX_PATH, old_path);
	n = ::str_count_token_with_BrokenChar(path, '\\');

	for ( i=0; i < n ; i++ )
	{
	    ::str_extract_token_with_BrokenChar(path, token, 128, i + 1, '\\');
		strcat_s (new_path, token);
		strcat_s (new_path, "\\");

		::CreateDirectory (new_path, NULL);		// 디렉토리 생성 
	}

	Ans = ::SetCurrentDirectory (path);		// 디렉토리로 이동이 되는지 확인 

	if ( Ans == 0 )					   		    // 디렉토리 이동이 되지 않으면 
	{											// 디렉토리 생성이 실패임 					
		::SetCurrentDirectory (old_path);		// 원래의 디렉토리로 이동  	
		return false;		
	}


	::SetCurrentDirectory (old_path);

	return true;
}

void CFunc_FilePath::f_path_create_full_pathname (char *path)
{
	char drive [MAX_PATH];
	char dir [MAX_PATH];
	
	char curr_path   [MAX_PATH];
	char curr_drive [MAX_PATH];
	char curr_dir   [MAX_PATH];

	::GetCurrentDirectory (MAX_PATH,  curr_path);

	_splitpath_s (path,      drive,    MAX_PATH,  dir,  MAX_PATH,    NULL, MAX_PATH,  NULL, MAX_PATH);
	_splitpath_s (curr_path, curr_drive, MAX_PATH, curr_dir, MAX_PATH, NULL, MAX_PATH, NULL, MAX_PATH);

	if ( strlen (drive) == 0 ) strcpy_s (drive, curr_drive); 
	if ( strlen (dir) == 0   ) 
	{
		strcpy_s (dir,   curr_dir  );
	}
	else
	{
		if (dir[0] != '\\') 
		{
			strcat_s (curr_dir, dir);
			strcpy_s (dir, curr_dir);
		}
	}
 
	_makepath_s( path, MAX_PATH, drive, dir, NULL, NULL);
}

bool CFunc_FilePath::f_path_create_directory (char *path )
{
	this->f_path_create_full_pathname( path );

	if ( f_path_Query_exist_path (path) )
	{
		return TRUE;
	} else
	{
		return this->f_path_create_directory_with_full_pathname (path);
	}
}

bool CFunc_FilePath::f_path_Query_exist_path (char path[])
{
	char org_path[MAX_PATH];
	
	BOOL b; 

	::GetCurrentDirectory (MAX_PATH, org_path);
	
	//디렉토리가 있는지 확인 합니다.
	b = ::SetCurrentDirectory (path);
	::SetCurrentDirectory ( org_path );

	if (b == TRUE)
		return true;
	else 
		return false;
}



bool CFunc_FilePath::f_path_Query_isExistFile(CString &filename)
{
	char path[MAX_PATH];
	strncpy_s (path, filename, MAX_PATH);

	return f_path_Query_isExistFile (path);
}

bool CFunc_FilePath::f_path_Query_isExistFile(std::string &s)
{
	char path[MAX_PATH];
	strncpy_s (path, s.c_str(), MAX_PATH);

	return f_path_Query_isExistFile (path);
}



bool CFunc_FilePath::f_path_Query_isExistFile(char filename[])
{
	CString fname = filename;
	if(0 == fname.GetLength() ) return false;
	
	std::fstream file;
	
//	file.open (filename, ios::in);

	if ( file.fail () )	//Returns a nonzero value if any I/O error (not end of file) has occurred
	{
		file.close ();
		file.clear ();
		return false;
	}
	else 
	{
		file.close();
		file.clear();
		return true;
	}
}

