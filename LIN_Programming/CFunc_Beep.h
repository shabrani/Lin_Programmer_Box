#pragma once
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>

class CFunc_Beep
{
public:
	CFunc_Beep(void);
	~CFunc_Beep(void);

	void Play();
	void Stop();
};

