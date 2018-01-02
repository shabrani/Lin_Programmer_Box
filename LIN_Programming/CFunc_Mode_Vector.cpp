#include "stdafx.h"
#include "CFunc_Mode_Vector.h"


CFunc_Mode_Vector::CFunc_Mode_Vector(void)
{
	this->m_sVectorName = "";

	m_nSize = 0;

	this->f_clear_vec();
}


CFunc_Mode_Vector::~CFunc_Mode_Vector(void)
{
}


unsigned CFunc_Mode_Vector::f_insert_mode(const unsigned nMode, const CString strInfo, const CString strNote)
{
	TS_CFUNC_MODE_VECTOR_MODE_ID_INFO		p;
	
	p.nId	  = nMode;
	p.strInfo = strInfo;
	p.strNote = strNote;
	
	m_vMode.push_back (p);

	m_nSize = m_vMode.size();

	return m_nSize;
}


CString	CFunc_Mode_Vector::f_find_sInfo(unsigned nMode)
{
	int nSize = m_vMode.size ();
	
	for(int idx=0; idx < nSize; idx++)
	{
		if (this->m_vMode[idx].nId == nMode) 
		{
			return m_vMode[idx].strInfo;
		}
	}

	::MessageBox(NULL,  "CFunc_Mode_Vector::f_find_sInfo (int nMode)->오류 : mode가 없습니다.", m_sVectorName, MB_OK);
	
	return "";
}


int	CFunc_Mode_Vector::f_find_idx (unsigned nMode)
{
	int nSize = m_vMode.size ();
	
	for(int idx=0; idx < nSize; idx++)
	{
		if (this->m_vMode[idx].nId == nMode) return idx;
	}

	::MessageBox(NULL,  "CFunc_Mode_Vector::f_find_idx (int nMode)->오류 : mode가 없습니다.", m_sVectorName, MB_OK);
	return 0;
}


int CFunc_Mode_Vector::f_find_mode (unsigned nIdx ) 
{ 
	if ( nIdx <  this->f_get_vec_size() ) 
		return this->m_vMode[nIdx].nId; 
	else
	{
		::MessageBox(NULL,  "CFunc_Mode_Vector::f_find_mode (int nIdx )  ->오류 : 범위를 넘어 섰습니다. ", this->m_sVectorName, MB_OK);
		return 0;
	}
}


void CFunc_Mode_Vector::f_cbox_Initial_Set (CComboBox &cbox, CString sFmt = "%02d. %s")
{
	CString sBuf;

	unsigned nSize = this->f_get_vec_size();

	cbox.ResetContent();

	for (unsigned idx=0; idx < nSize; idx++)
	{
		sBuf.Format (sFmt, m_vMode[idx].nId, m_vMode[idx].strInfo);
		cbox.AddString(sBuf);
	}

	cbox.SetCurSel(0);

}


void CFunc_Mode_Vector::f_cbox_SetCurSel (CComboBox &cbox, unsigned mode)
{
	unsigned idx   = this->f_find_idx(mode);
	unsigned nSize = cbox.GetCount();

	if (0 == nSize)
	{
		CString sMsg;
		sMsg.Format("CFunc_Mode_Vector::f_cbox_SetCurSel->cbox 데이터가 없음, size = %d", nSize);
		::MessageBox(NULL,  sMsg, this->m_sVectorName, MB_OK);

		return;
	}


	if (idx < nSize)
		cbox.SetCurSel ( idx );
	else
	{
		CString sMsg;
		sMsg.Format("CFunc_Mode_Vector::f_cbox_SetCurSel->cbox 데이터보다 큰 수임, idx = %d", idx);
		::MessageBox(NULL,  sMsg, this->m_sVectorName, MB_OK);

		cbox.SetCurSel ( 0 );

	}
}


unsigned CFunc_Mode_Vector::f_cbox_GetCurSel (CComboBox &cbox)
{
	int idx = cbox.GetCurSel();	

	if (idx < 0)
	{
		CString sMsg;
		sMsg.Format("CFunc_Mode_Vector::f_cbox_GetCurSel-> empty selected, idx = %d", idx);
		::MessageBox(NULL,  sMsg, this->m_sVectorName, MB_OK);
		return 0;
	}

	if ((unsigned)idx > this->m_nSize)
	{
		CString sMsg;
		sMsg.Format("CFunc_Mode_Vector::f_cbox_GetCurSel->idx Greater then vec_size, idx = %d", idx);
		::MessageBox(NULL,  sMsg, this->m_sVectorName, MB_OK);
		return 0;
	}

	unsigned mode = m_vMode[idx].nId;

	return mode;
}


void CFunc_Mode_Vector::f_cbox_GetCurSel    (CComboBox &cbox, unsigned &mode)
{
	int idx = cbox.GetCurSel();	
	mode = 0;

	if (idx < 0)
	{
		CString sMsg;
		sMsg.Format("CFunc_Mode_Vector::f_cbox_GetCurSel-> empty selected, idx = %d", idx);
		::MessageBox(NULL,  sMsg, this->m_sVectorName, MB_OK);
		return;
	}

	if ((unsigned)idx > this->m_nSize)
	{
		CString sMsg;
		sMsg.Format("CFunc_Mode_Vector::f_cbox_GetCurSel->idx Greater then vec_size, idx = %d", idx);
		::MessageBox(NULL,  sMsg, this->m_sVectorName, MB_OK);
		return;
	}

	mode = m_vMode[idx].nId;
}
