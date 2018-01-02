#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <fstream>

#include <string>
#include <iostream>
#include <fstream>

#include <afxdb.h>
#include <odbcinst.h>

#include <vector>
#include <iterator>

#include <functional>
#include <algorithm>


#include "CTest_Main.h"
#include "tmenu_file.h"
#include "CFunc_FilePath.h"

using namespace std;

extern CTest_Main	*pTest;

BOOL f_open_file_dialog (CString &filename, CString path, char *ext)
{
	OPENFILENAME ofn;

	char lpstrFile[MAX_PATH] = "";
	//char oldpath[MAX_PATH];	
	SetCurrentDirectory((LPCSTR)path);
	//GetCurrentDirectory (MAX_PATH, oldpath);	
	strncpy_s (lpstrFile, path, MAX_PATH);

	memset (&ofn, 0, sizeof(OPENFILENAME) );
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = ext;
	ofn.lpstrFile = lpstrFile;
	ofn.nMaxFile = 256;
	ofn.lpstrInitialDir = path;

	BOOL b = GetOpenFileName(&ofn);

	//파일을 열지 못하면 
	if (b != TRUE) return FALSE; 	

	//strncpy_s(filename, strlen(ofn.lpstrFile) + 1, ofn.lpstrFile, strlen(ofn.lpstrFile));
	filename	= ofn.lpstrFile;	
	TRACE("open_file_dialog//filename : %s\r\n",filename);
	return TRUE;
}
