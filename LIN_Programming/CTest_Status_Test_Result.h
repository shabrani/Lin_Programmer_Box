#pragma once


//������ �˻� ����� ȿ�������� �����ϱ� ���� ����� �����Ѵ�. 

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
		TS_CTRESULT_QUANTITY Curr;	//���� ��Ʈ�� �۾�����
		TS_CTRESULT_QUANTITY Acc;	//�����۾�����
	}m_Qty;		

	struct
	{
		TS_CTRESULT_RESULT	CH;		//���� ä���� ����� �����Ѵ�. 
		TS_CTRESULT_RESULT	*pCh;	//��ü �ҷ��� �Ǵ��Ҷ� ����Ѵ�. 

		bool bAllPass;
	}m_Result, m_Prev;


	void f_clear_Qty_Acc  ();
	void f_clear_Qty_Curr ();

	void f_Result_Backup ()			{m_Prev = m_Result;}
	void f_Result_Reset_for_Test ();

	bool f_check_All_CH_Pass();

	void f_adjust_retest_qty (unsigned nCh, unsigned &nDnum_PRev);

};
