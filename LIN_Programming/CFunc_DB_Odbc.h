#pragma once

#include <afxdb.h>
#include <odbcinst.h>

#include "afxdao.h"
#pragma warning(disable:4995) 

#include "CTest_State.h"



typedef struct
{
	CString sField;
	CString sData;
}TS_CSPEC_FIELD;




class CFunc_DB_Odbc
{
public:
	CFunc_DB_Odbc(void);
	~CFunc_DB_Odbc(void);



	//BOOL  f_field_check_and_create (CDaoTableDef* pTableDef, CString strFieldName, 

	void f_SQL_Update_AddString_CStr	(CString &sSQL, const char *szField, const CString		&sData,		const char charSeperator );
	void f_SQL_Update_AddString_text	(CString &sSQL, const char *szField, const char			*szData,	const char charSeperator );
	void f_SQL_Update_AddString_uint	(CString &sSQL, const char *szField, unsigned			uData,		const char charSeperator );
	//void f_SQL_Update_AddString_ulong	(CString &sSQL, const char *szField, unsigned long long uData,		const char charSeperator );
	void f_SQL_Update_AddString_bool	(CString &sSQL, const char *szField, bool				bData,		const char charSeperator );
	void f_SQL_Update_AddString_double	(CString &sSQL, const char *szField, double				fData,		const char charSeperator );


	bool f_extract_SpecInfo_from_vRecord				(std::vector<TS_CSPEC_FIELD> &vec, char *ref, CString &strBuf);


	bool f_extract_SpecInfo_from_vRecord_u8				(std::vector<TS_CSPEC_FIELD> &vec, char *ref, UINT8   &u8);
	bool f_extract_SpecInfo_from_vRecord_u16			(std::vector<TS_CSPEC_FIELD> &vec, char *ref, UINT16  &u16);
	bool f_extract_SpecInfo_from_vRecord_u32			(std::vector<TS_CSPEC_FIELD> &vec, char *ref, UINT32  &u32);

	bool f_extract_SpecInfo_from_vRecord_hex_to_u8		(std::vector<TS_CSPEC_FIELD> &vec, char *ref, UINT8   &u8);
	bool f_extract_SpecInfo_from_vRecord_hex_to_u16		(std::vector<TS_CSPEC_FIELD> &vec, char *ref, UINT16  &u16);
	bool f_extract_SpecInfo_from_vRecord_hex_to_u32		(std::vector<TS_CSPEC_FIELD> &vec, char *ref, UINT32  &u32);
	

	bool f_extract_SpecInfo_from_vRecord_float		(std::vector<TS_CSPEC_FIELD> &vec, char *ref, float      &fData);
	bool f_extract_SpecInfo_from_vRecord_dbl		(std::vector<TS_CSPEC_FIELD> &vec, char *ref, double     &fData);
	bool f_extract_SpecInfo_from_vRecord_bool		(std::vector<TS_CSPEC_FIELD> &vec, char *ref, bool       &bData);
	bool f_extract_SpecInfo_from_vRecord_CStr	    (std::vector<TS_CSPEC_FIELD> &vec, char *ref, CString    &sBuf);



	bool f_getFieldValue_CStr	(CRecordset &recset, char *field, CString &sData);
	bool f_getFieldValue_uint	(CRecordset &recset, char *field, unsigned &uData);
	bool f_getFieldValue_uint16	(CRecordset &recset, char *field, unsigned short &uData);
	bool f_getFieldValue_ulong	(CRecordset &recset, char *field, unsigned long &uData);
	//bool f_getFieldValue_udlong	(CRecordset &recset, char *field, unsigned long long &uData);
	bool f_getFieldValue_double (CRecordset &recset, char *field, double     &fData);
	bool f_getFieldValue_bool	(CRecordset &recset, char *field, bool        &bData);
	bool f_getFieldValue_byte	(CRecordset &recset, char *field, unsigned char &byteData);



	bool f_SQL_Update_SpecInfo_Record (CDatabase &database, const char *szDBTable, const char *szField, const char *szData );

	//bool f_SQL_Update_SpecInfo_string (CDatabase &database, const char *szDBTable, const char *szField, CString &strData );
	bool f_SQL_Update_SpecInfo_uint	  (CDatabase &database, const char *szDBTable, const char *szField, unsigned uData	 );
		
	bool f_SQL_Update_SpecInfo_u32_to_hex (CDatabase &database, const char *szDBTable, const char *szField, UINT32  uData	 );
	bool f_SQL_Update_SpecInfo_u16_to_hex (CDatabase &database, const char *szDBTable, const char *szField, UINT16  uData	 );
	bool f_SQL_Update_SpecInfo_u08_to_hex (CDatabase &database, const char *szDBTable, const char *szField, UINT8   uData	 );
	bool f_SQL_Update_SpecInfo_u08_to_hex(CDatabase &database, const char *szDBTable, const char *szField,  UINT32  uData);

	//bool f_SQL_Update_SpecInfo_ulong  (CDatabase &database, const char *szDBTable, const char *szField, unsigned long long uData);
	bool f_SQL_Update_SpecInfo_bool	  (CDatabase &database, const char *szDBTable, const char *szField, bool  bData    );
	bool f_SQL_Update_SpecInfo_float  (CDatabase &database, const char *szDBTable, const char *szField, float fData	   );	
	bool f_SQL_Update_SpecInfo_dbl    (CDatabase &database, const char *szDBTable, const char *szField, double fData   );	
	bool f_SQL_Update_SpecInfo_CStr	  (CDatabase &database, const char *szDBTable, const char *szField, CString sData  );
};

