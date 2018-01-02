#pragma once


//이전의 검사 결과를 효과적으로 보관하기 위한 방법을 구현한다. 

typedef struct
{
	unsigned	nDnum;
	unsigned	nJig;
	bool		isPass;
	bool		isTested;
	bool		isStop;

	unsigned	nPass_add;
	unsigned	nFail_add;
}TS_CTRESULT_RESULT;


typedef struct
{
	unsigned	nPass;			
	unsigned	nFail;
}TS_CTRESULT_QUANTITY;




class CTest_Status_Test_Result
{
public:
	CTest_Status_Test_Result ();
	~CTest_Status_Test_Result(void);

	unsigned	m_nChannelCount;

	struct
	{
		TS_CTRESULT_QUANTITY Curr;	//현재 로트의 작업수량
		TS_CTRESULT_QUANTITY Acc;	//누적작업수량
	}m_Qty;		

	struct
	{
		TS_CTRESULT_RESULT	CH;		//개별 채널의 결과를 저장한다. 
		TS_CTRESULT_RESULT	*pCh;	//전체 불량을 판단할때 사용한다. 

		bool bAllPass;
	}m_Result, m_Prev;


	void f_clear_Qty_Acc  ();
	void f_clear_Qty_Curr ();

	void f_Result_Backup ()			{m_Prev = m_Result;}
	void f_Result_Reset_for_Test ();

	bool f_check_All_CH_Pass();

	void f_adjust_retest_qty (unsigned nCh, unsigned &nDnum_PRev);

};
