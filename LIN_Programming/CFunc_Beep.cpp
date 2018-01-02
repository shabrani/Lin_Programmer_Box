#include "stdafx.h"
#include "CFunc_Beep.h"
#include "resource.h"

CFunc_Beep::CFunc_Beep(void)
{
}


CFunc_Beep::~CFunc_Beep(void)
{
}


void CFunc_Beep::Play(void)
{
	PlaySound((LPCSTR)MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
}


void CFunc_Beep::Stop(void)
{
	PlaySound((LPCSTR)MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC | SND_PURGE);
}