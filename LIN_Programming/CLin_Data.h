#pragma once

#include "KvrLin.h"

#include <string>
#include <functional>
#include <algorithm>

#include "CFunc_Mode_Vector.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Struct
typedef struct 
{
	unsigned nId;
	double	 fVal;
	CString	 sDesc;
}TS_CLIN_REG_DATA_ID_VAL;

 typedef struct
 {
	KVRTYPE_LIN_ARBID	fid;
	KVRTYPE_UINT8		Data[4];

	unsigned nLength;	
 }TS_CLIN_DATA_SEND_MSG;

typedef union 
{
	struct
	{
		KVRTYPE_UINT16 Data1;
		KVRTYPE_UINT16 Data2;
		KVRTYPE_UINT16 Data3;
		KVRTYPE_UINT16 Data4;

		KVRTYPE_UINT16 Data5;
	}u16;

	struct
	{
		unsigned char Data10_L; //NVM_A0
		unsigned char Data11_H;	//NVM_A1
		unsigned char Data20_L;	//NVM_A2
		unsigned char Data21_H;	//NVM_A3
		unsigned char Data30_L;	//NVM_A4
		unsigned char Data31_H;	//NVM_A5
		unsigned char Data40_L;	//NVM_A6
		unsigned char Data41_H;	//NVM_A7
		unsigned char Data50_L;	//NVM_A8
		unsigned char Data51_H;
	}u8;

	struct
	{
		unsigned R10_b2_3_PP			:3;
		unsigned R10_b5_3_VSET			:3;
		unsigned R10_b6_1_ALT			:1;
		unsigned R10_b7_1_CFG			:1;

		unsigned R11_b1_2_LRCFT			:2;
		unsigned R11_b2_1_res_0			:1;
		unsigned R11_b5_3_LRCRT			:3;
		unsigned R11_b7_2_LRCDIS		:2;

		unsigned R20_b0_1_EOFF			:1;
		unsigned R20_b1_1_res_0			:1;
		unsigned R20_b2_1_OTEXC			:1;
		unsigned R20_b3_1_CSHT			:1;
		unsigned R20_b5_2_LEO			:2;
		unsigned R20_b7_2_SSS			:2;

		unsigned R21_b2_3_HTG			:3;
		unsigned R21_b5_3_THT			:3;
		unsigned R21_b7_2_CLIM			:2;

		unsigned R30_b2_3_SUPP			:3;
		unsigned R30_b7_5_CLASS			:5;
		
		unsigned R31_b1_2_EWMA_K		:2;
		unsigned R31_b3_2_EWMA_Mode		:2;
		unsigned R31_b7_4_res_0			:4;

		unsigned R40_b1_2_IEXC			:2;
		unsigned R40_b4_3_PEXCDC		:3;
		unsigned R40_b7_3_CTSADJ		:3;

		unsigned R41_b1_2_T_PSB_ON_MAX	:2;
		unsigned R41_b2_1_SPCHG_EN		:1;
		unsigned R41_b4_2_SPCHG_CFG		:2;
		unsigned R41_b6_2_RPARA_SEL		:2;
		unsigned R41_b7_1_LOCK_EN		:1;


		unsigned R50:					16;
		
	}reg;

	struct
	{
		unsigned	a0				:8;
		unsigned	a1				:8;
		unsigned	a2				:8;
		unsigned	a3				:8;
		unsigned	a4				:8;
		unsigned	a5				:8;
		unsigned	a6				:8;
		unsigned	a7				:8;
		unsigned	a8				:8;
		unsigned	a9				:8;
	}Boach_u8;

}TU_CLIN_DATA_UNION_NVM;

typedef union 
{
	struct
	{
		unsigned char offset0_5;
		unsigned char offset0_6;
		unsigned char offset0_7;
		unsigned char offset0_8;
		unsigned char offset1_5;
		unsigned char offset1_6;
		unsigned char offset1_7;
		unsigned char offset1_8;	
		unsigned char offset2_5;
		unsigned char offset2_6;
		unsigned char offset2_7;
		unsigned char offset2_8;
	}u8;

	struct
	{
		// offset=0 ///////////////////////////////
		unsigned offset0_5_b1_2_PP				:2; 
		unsigned offset0_5_b4_3_VSET			:3; 
		unsigned offset0_5_b6_2_PROTOCOL		:2;
		unsigned offset0_5_b7_1_EN_LRC			:1;

		unsigned offset0_6_b3_4_LIN_CONFIG		:4;
		unsigned offset0_6_b6_3_LRC				:3;
		unsigned offset0_6_b7_1_EN_OV_FLAG		:1;

		unsigned offset0_7_b1_2_NLRC_DISF		:2;
		unsigned offset0_7_b3_2_LRC_RETURN		:2;
		unsigned offset0_7_b4_1_res				:1;
		unsigned offset0_7_b5_1_EN_EX_OFF		:1;
		unsigned offset0_7_b7_2_VLOW			:2;

		unsigned offset0_8_b1_2_NSELFSTART		:2;
		unsigned offset0_8_b4_3_VSET_HT_GRAD	:3;
		unsigned offset0_8_b7_3_VSET_HT_THRES	:3;

		// offset=1 ///////////////////////////////
		unsigned offset1_5_b4_5_ALT_CLASS		:5;
		unsigned offset1_5_b7_3_DC_PREEXC		:3;
		
		unsigned offset1_6_b1_2_BEH_DC_FILT_PSB	:2;
		unsigned offset1_6_b3_2_TFILT_DC_MEAS	:2;
		unsigned offset1_6_b5_2_TFILT_IEXC_MEAS	:2;
		unsigned offset1_6_b5_2_TFILT_VBA_MEAS	:2;

		unsigned offset1_7_b1_2_TONBOOST		:2;
		unsigned offset1_7_b2_1_res				:1;
		unsigned offset1_7_b3_1_TOUT_LIN		:1;
		unsigned offset1_7_b5_2_BZ				:2;
		unsigned offset1_7_b7_2_ISHORT			:2;

		unsigned offset1_8_b3_4_res				:4;
		unsigned offset1_8_b7_4_res				:4;

		// offset=2 ///////////////////////////////
		unsigned offset2_5_b6_7_res				:7;
		unsigned offset2_5_b7_1_EN_BZI			:1;

		unsigned offset2_6_b0_1_BEH_PREEXC		:1;
		unsigned offset2_6_b1_1_EN_SPEC_VERB_ID	:1;
		unsigned offset2_6_b2_1_res				:1;
		unsigned offset2_6_b3_1_BEH_F_MEC		:1;
		unsigned offset2_6_b4_1_BEH_F_EL		:1;
		unsigned offset2_6_b6_2_TFILT_FLAG		:2;
		unsigned offset2_6_b7_1_res				:1;

		unsigned offset2_7_b2_3_ALT_SUPPLIER	:3;
		unsigned offset2_7_b5_3_res				:3;
		unsigned offset2_7_b7_2_res				:2;

		unsigned offset2_8_b3_4_res				:4;
		unsigned offset2_8_b7_4_res				:4;
	
	}reg;

}TU_LIN2112_DATA_UNION_NVM;

namespace ENUM_CLIN_DATA_TLE8881_NVM_PARAM
{
	enum Enum
	{
		R00						=	0,	
		R10_b2_3_PP				= 102,
		R10_b5_3_VSET			= 105,
		R10_b6_1_ALT			= 106,
		R10_b7_1_CFG			= 107,
		R11_b1_2_LRCFT			= 111,
		R11_b2_1_res_0			= 112,
		R11_b5_3_LRCRT			= 115,
		R11_b7_2_LRCDIS			= 117,
		R20_b0_1_EOFF			= 200,
		R20_b1_1_res_0			= 201,
		R20_b2_1_OTEXC			= 202,
		R20_b3_1_CSHT			= 203,
		R20_b5_2_LEO			= 205,
		R20_b7_2_SSS			= 207,
		R21_b2_3_HTG			= 212,
		R21_b5_3_THT			= 215,
		R21_b7_2_CLIM			= 217,
		R30_b2_3_SUPP			= 302,
		R30_b7_5_CLASS			= 307,
		R31_b1_2_EWMA_K			= 311,
		R31_b3_2_EWMA_Mode		= 313,
		R31_b7_4_res_0			= 317,
		R40_b1_2_IEXC			= 401,
		R40_b4_3_PEXCDC			= 404,
		R40_b7_3_CTSADJ			= 407,
		R41_b1_2_T_PSB_ON_MAX	= 411,
		R41_b2_1_SPCHG_EN		= 412,
		R41_b4_2_SPCHG_CFG		= 414,
		R41_b6_2_RPARA_SEL		= 416,
		R41_b7_1_LOCK_EN		= 417,
		R99_enum_end			= 999
	};
};


typedef union
{
	KVRTYPE_UINT32 u32;

	struct
	{
		KVRTYPE_UINT8 Data1;
		KVRTYPE_UINT8 Data2;
		KVRTYPE_UINT8 Data3;
		KVRTYPE_UINT8 Data4;
	}u8;

	struct
	{
		unsigned R10_6_RA_RVSET_7_2		:6; //RA[1:0] = 00;
		unsigned R16_2_00				:2;
		unsigned R20_4_RB_RLRCRT		:4;
		unsigned R24_4_RC_RLRCDIS		:4;
		unsigned R20_5_RD_RCLIM		    :5;	//RD[6:5] = 00;
		unsigned R26_2_RD_00		    :5;	
		unsigned R27_1_x				:1;
		unsigned R40_3_RE_RDI			:3;
		unsigned R43_1_RF_RLRCBZ		:1;
		unsigned R44_3_RG_RHT			:3;
		unsigned R47_1_RH_RPARA		:1;
	}reg_VersionA;

	struct
	{
		unsigned R10_8_RA_RVSET			:8;
		unsigned R20_4_RB_RLRCRT		:4;
		unsigned R24_4_RC_RLRCDIS		:4;
		unsigned R40_0_x				:1;
		unsigned R41_7_RD_RCLIM			:7;
		unsigned R40_3_RE_RDI			:3;
		unsigned R43_1_RF_RLRCBZ		:1;
		unsigned R44_3_RG_RHT			:3;
		unsigned R47_1_RH_RPARA			:1;
	}reg_VersionB;

}TU_CLIN_DATA_UNION_RX;


typedef union		//information filed;
{
	KVRTYPE_UINT16	u16;

	struct
	{
		KVRTYPE_UINT8 Data1;
		KVRTYPE_UINT8 Data2;
	}u8;

	struct
	{
		unsigned b10_1_TA_F_HT	:1; //high temperature indication flag
		unsigned b11_1_TB_F_ROT	:1;	//mechanical abnormality flag 
		unsigned b12_1_TC_F_ELL	:1;	//electrical abnormality flag
		unsigned b13_5_TD_RDC	:5;	//Duty cycle value of the excitation PWM (field monitoring)
		unsigned b20_6_TE_RMC	:6;	//Measured Excitation Current 
		unsigned b26_1_TF_F_CEF	:1;	//LIN Communication Error Falg
		unsigned b27_1_TG_F_CTO	:1;	//LIN Communication Timeout Flag
	}reg;

}TU_CLIN_DATA_UNION_TX1;


typedef union		//information filed;
{
	KVRTYPE_UINT16	u16;

	struct
	{
		KVRTYPE_UINT8 Data1;
		KVRTYPE_UINT8 Data2;
	}u8;

	struct
	{
		unsigned b10_3_ALT_SUPPLIER	:3; //Alternator supplier identification
		unsigned b13_5_ALT_CLASS	:5;	//Alternator class identification
		unsigned b20_3_AIC_MFG_ID	:3;	//Manufacturer ID: Infineon: 100b
		unsigned b23_5_ASIC_ID		:5;	//ASIC ID: A11 = 0001b;
	}reg;

}TU_CLIN_DATA_UNION_TX2;





typedef union		//information filed;
{
	KVRTYPE_UINT32	u32;

	struct
	{
		KVRTYPE_UINT8 Data1;
		KVRTYPE_UINT8 Data2;
		KVRTYPE_UINT8 Data3;
		KVRTYPE_UINT8 Data4;
	}u8;

	struct
	{
		unsigned b10_1_TK_F_HT	:1; //high temperature indication flag
		unsigned b11_1_TL_F_ROT	:1;	//mechanical abnormality flag
		unsigned b12_1_TM_F_EL	:1;	//electrical abnormality flag
		unsigned b13_5_TN_RDC	:5;	//Duty cycle value of the excitation PWM (field monitoring)
		unsigned b20_8_TO_RMC	:8; //Measured excitation current
		unsigned b30_3_TP_RDI	:3;	//Data Indicator for TX3 frame Byte 4 RDI[
		unsigned b03_3_000		:3;	//Data Indicator -> Select TS[RMV, RMT, RVSET]
		unsigned b36_1_TQ_F_CEF	:1;	//LIN communication error flag
		unsigned b37_1_TR_F_CTO	:1;	//Lin Comunication Time Out Flag
		unsigned b40_8_TS_R		:8; //RMV, RMT, RVSET with RDI
	}reg;

}TU_CLIN_DATA_UNION_TX3;



// $ 2014.06.10 Move from CFunc_Spec.h

namespace ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM
{
	enum Enum
	{

		M00_NONE					=	0,			

		M10							=	10,		//5,				//24
		M11_TX2_BYTE1				=	11,		//5,				//24
		M12_TX2_BYTE2				=	12,		//5,				//24
		M13_TX2_UINT16				=	13,		//5,				//24


		M20							=	20,
		M21_TX2_TH_RSUPP			=	21,		//1,				//20
		M22_TX2_TI_RCLASS			=	22,		//2,				//21
		M23_TX2_TJ_MFG				=	23,		//3,				//22
		M24_TX2_TJ_ASIC				=	24,		//4,				//23


		M30							=	30,
		M31_TX3_BYTE1				=	31,
		M32_TX3_BYTE2				=	32,
		M33_TX3_BYTE3				=	33,
		M34_TX3_BYTE4				=	34,
		M35_TX3_UINT32				=	35,



		M40							=   40,
		M41_TX3_TK_B1_FHT			=	41,				//6
		M42_TX3_TL_B1_FROT			=	42,				//7
		M43_TX3_TM_B1_FEL			=	43,				//8
		M44_TX3_TN_B5_RDC			=	44,				//9
		M45_TX3_TO_B8_RMC			=	45,				//10
		M46_TX3_TP_B3_RDI			=	46,				//11
		M47_TX3_TQ_B1_FECF			=	47,				//12
		M48_TX3_TR_B1_FCTO			=	48,				//13
		M49_TX3_TS_B8_MEAS			=	49,				//14


		//M301_TX3_BYTE0								= 301,
		//M302_TX3_BYTE1								= 302,
		//M303_TX3_BYTE2								= 303,
		//M302_TX3_BYTE3								= 302,
		//M303_TX3										= 304,
		M99_enum_end				=   99
	};
};

class CLin_Data
{
public:
	CLin_Data(void);
	~CLin_Data(void);

	TU_CLIN_DATA_UNION_NVM		m_uNVM;
	TU_CLIN_DATA_UNION_RX		m_uRX;


	struct
	{
		bool bValidTX2;
		bool bValidTX3;

		TU_CLIN_DATA_UNION_TX1		uTX1;
		TU_CLIN_DATA_UNION_TX2		uTX2;
		TU_CLIN_DATA_UNION_TX3		uTX3;
	}m_recv;

	struct
	{
		CFunc_Mode_Vector	meas_TX_vParam;
		CFunc_Mode_Vector	meas_NVM_vParam;
	}m_mode;


	struct
	{
		CFunc_Mode_Vector	RMC;

		//vector ...
		//vector ...curr
		//vector ...meas duty
		//vector ...
	}m_cvt;

	struct
	{
		TS_CLIN_DATA_SEND_MSG	Sleep;
		TS_CLIN_DATA_SEND_MSG	Wakeup;
		TS_CLIN_DATA_SEND_MSG	TestMode;
	}m_msg;

	unsigned m_nVersion;									//0-versionA, 1-VersionB;

	double f_conv_Val_from_TX3_RDC ( unsigned nRDC );

	void f_mode_initialize();
	
	bool f_extract_TX_param_from_recv_union (unsigned select_param, unsigned &extract_val);	// Parameter가 TX3인지 확인 및 추출하는 기능을 한다.

	bool f_check_TX2_param (unsigned select_param );	// Parameter가 TX2인지 확인한다.
	bool f_check_TX3_param (unsigned select_param );	// Parameter가 TX3인지 확인한다.

	void f_param_RMC_initial_set();


};

