#pragma once

#include <vector>

using namespace std;

typedef struct
{
//	double			fData;		
//	unsigned		nData;		// 32비트 데이터

	VARIANT			varData;	// 복합형식
	CString			strData;

	bool			bPass;
	bool			bTested;

	unsigned		nFailCount;

}ST_CFUNCDATA_ITEMDATA;


typedef struct
{	
	bool	 bFistFail;
	bool	 b2ndFial;

	unsigned nPnum;
	unsigned nTnum;
	unsigned nPnum_prev;
	unsigned nTnum_prev;

}TS_CTESTDATA_DEVICEDATA_FIRST_FAIL;

typedef struct
{
	struct
	{
		unsigned	nDnum;
		bool		bTested;	
		bool		bPass;			// $ 2014.05.11 Add for .for Critial Bug Fix
		CString		sSerialNo;
		unsigned	nJig;			// $ Add 2013-0911
		unsigned	nBin;
		unsigned	nFailFirst;		// $ Add 2013-0911 첫번째 불량 항목

		CTime		tTime;			// 검사한 시간
		double		fElapsedtime;	// 검사소요시간

		unsigned	nRetestCount;						// $ Add 2015-03-05 sjkim

		TS_CTESTDATA_DEVICEDATA_FIRST_FAIL  st1stFail;	// $ Add 2015-03-05 sjkim
	}Var;

	std::vector < vector <ST_CFUNCDATA_ITEMDATA> >	vData;

}TS_CTESTDATA_DEVICEDATA;


class CFunc_TestData
{
public:
	CFunc_TestData(void);
	~CFunc_TestData(void);

	struct 
	{
		unsigned	nArray;		//Array number
		unsigned	nTitem;		//test item
	}m_const;

	
	TS_CTESTDATA_DEVICEDATA	m_testData;
	TS_CTESTDATA_DEVICEDATA	m_saveData;


	void f_create_data_vector           ( unsigned nTitem, unsigned nAr );				//vData[ar][p];

	void f_copy_CTestData_to_Class      ( CFunc_TestData *pCTestData);

	void f_reset_CTestData_for_Test_Ready  (unsigned nTestCh, unsigned nDnum);

	void f_data_clear (TS_CTESTDATA_DEVICEDATA *pData);
	void f_data_copy  (TS_CTESTDATA_DEVICEDATA *pSrc, TS_CTESTDATA_DEVICEDATA *pDest);

	void f_clear_CTestData_FailCount ();

};
