#pragma once

#include "afxwin.h"

typedef struct 
{
	unsigned nId;
	CString strInfo;
	CString strNote;
}TS_CFUNC_MODE_VECTOR_MODE_ID_INFO;

class CFunc_Mode_Vector
{
public:
	CFunc_Mode_Vector();
	~CFunc_Mode_Vector(void);

	unsigned	m_nSize;
	CString		m_sVectorName;

	std::vector<TS_CFUNC_MODE_VECTOR_MODE_ID_INFO> m_vMode;


	unsigned	f_insert_mode(const unsigned nMode, const CString strInfo, const CString strNote = "");
	int			f_find_idx	  (unsigned nMode);
	int			f_find_mode	  (unsigned nIdx );
	CString		f_find_sInfo  (unsigned nMode);

	void		f_clear_vec    () {m_vMode.clear(); 	m_nSize = m_vMode.size();}
	unsigned	f_get_vec_size () {return m_vMode.size();}

	void		f_set_vec_name (CString sName) {m_sVectorName = sName;}



	void		f_cbox_Initial_Set	(CComboBox &cbox, CString sFmt  );
	void		f_cbox_SetCurSel	(CComboBox &cbox, unsigned mode );
	void		f_cbox_GetCurSel	(CComboBox &cbox, unsigned &mode);
	unsigned    f_cbox_GetCurSel	(CComboBox &cbox);

};
