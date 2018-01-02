#include "stdafx.h"
#include "CFunc_DelayTime.h"

bool f_delay_ms( double fSetDlyMs )
{
	LARGE_INTEGER freq, start_count, end_count;

	double delay_count, delay_time;

	QueryPerformanceCounter(&start_count);
	QueryPerformanceFrequency(&freq);
	
	if (start_count.QuadPart == 0 ) return false;

	for(double x=0;;x++)
	{
		QueryPerformanceCounter(&end_count);
	    delay_count = double(end_count.QuadPart - start_count.QuadPart);

		delay_time = (delay_count / double(freq.QuadPart)) * 1.0E3;
		
		if (delay_time> fSetDlyMs) return TRUE;	
	}
	
	return true;

}

CFunc_DelayTime::CFunc_DelayTime(void)
{
	QueryPerformanceFrequency(&m_freq);
}


CFunc_DelayTime::~CFunc_DelayTime(void)
{
}

bool CFunc_DelayTime::f_delay_ms ( double fSetDlyMs )
{
	QueryPerformanceCounter(&m_delay_start_count);
	if (m_delay_start_count.QuadPart == 0 ) return FALSE;

	for(double x=0;;x++)
	{
		QueryPerformanceCounter(&m_delay_end_count);

	    m_delay_count = double(m_delay_end_count.QuadPart - m_delay_start_count.QuadPart);
		m_delay_time  = (m_delay_count / double(m_freq.QuadPart))*1000;
		if ( m_delay_time > fSetDlyMs ) return true;	
	}
	
	return false;
}

bool CFunc_DelayTime::f_measTime_setStart ()
{
	QueryPerformanceCounter(&m_meas_start_count);
	if ( 0 == m_meas_start_count.QuadPart ) return false;
	return true;
}

double CFunc_DelayTime::f_measTime ()
{
	QueryPerformanceCounter(&m_meas_end_count);
	if ( 0 == m_meas_start_count.QuadPart ) return 0.0;

	m_meas_count = double(m_meas_end_count.QuadPart - m_meas_start_count.QuadPart);
	m_meas_time  = (m_meas_count / double(m_freq.QuadPart));

	return m_meas_time;
}