#pragma once
class CFunc_DelayTime
{
public:
	CFunc_DelayTime(void);
	~CFunc_DelayTime(void);

	bool f_delay_ms ( double fSetDlyMs );

	bool f_measTime_setStart();
	double f_measTime();

	LARGE_INTEGER	m_freq;
	LARGE_INTEGER	m_meas_start_count;
	LARGE_INTEGER	m_meas_end_count;
	LARGE_INTEGER	m_delay_start_count;
	LARGE_INTEGER	m_delay_end_count;

	double m_delay_count;
	double m_delay_time;

	double m_meas_count;
	double m_meas_time;
};

bool f_delay_ms (double   fSetDlyMs);
