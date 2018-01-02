#include "stdafx.h"
#include "CLin_Data.h"


CLin_Data::CLin_Data(void)
{
}


CLin_Data::~CLin_Data(void)
{
}


void CLin_Data::f_param_RMC_initial_set()
{
	int nRtn = 0;

	CFunc_Mode_Vector	*pV;
	{
		pV = &this->m_cvt.RMC;

	//	pV->f_set_vec_name ("CLIN_DATA_TLE8881B::m_cvt.RMC");
	//	pV->f_clear_vec();

	//	nRtn = this->m_cvt.RMC.f_insert_mode ( 0x00, "13.2");
	//	nRtn = this->m_cvt.RMC.f_insert_mode ( 0x01, "13.3");
	//	nRtn = this->m_cvt.RMC.f_insert_mode ( 0x02, "13.4");
	//	nRtn = this->m_cvt.RMC.f_insert_mode ( 0x03, "13.5");
	//	nRtn = this->m_cvt.RMC.f_insert_mode ( 0x04, "13.6");
	//	nRtn = this->m_cvt.RMC.f_insert_mode ( 0x05, "13.7");
	}

}


void CLin_Data::f_mode_initialize()
{

	CFunc_Mode_Vector *pVec;

	
	{

		pVec = &this->m_mode.meas_TX_vParam;

		pVec->f_set_vec_name ("CLIN_Data_TLE8881::m_mode.meas_TX_vParam");
		pVec->f_clear_vec();

		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M00_NONE,					"--"				);

		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M10,							""					);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M11_TX2_BYTE1,				"TX2_Byte1"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M12_TX2_BYTE2,				"TX2_Byte2"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M13_TX2_UINT16,				"TX2_U16"			);	

		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M20,							""					);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M21_TX2_TH_RSUPP,			"TX2_TH_RSUPP"		);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M22_TX2_TI_RCLASS,			"TX2_TI_RCLASS"		);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M23_TX2_TJ_MFG,				"TX2_TJ_MFG"		);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M24_TX2_TJ_ASIC,				"TX2_TJ_ASIC"		);	



		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M30,							""					);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M31_TX3_BYTE1,				"TX3_Byte1"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M32_TX3_BYTE2,				"TX3_Byte2"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M33_TX3_BYTE3,				"TX3_Byte3"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M34_TX3_BYTE4,				"TX3_Byte4"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M35_TX3_UINT32,				"TX3_U32"			);	


		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M40,							""					);
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M41_TX3_TK_B1_FHT,			"TX3_TK_B1_FHT"		);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M42_TX3_TL_B1_FROT,			"TX3_TL_B1_FROT"	);
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M43_TX3_TM_B1_FEL,			"TX3_TM_B1_FEL"		);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M44_TX3_TN_B5_RDC,			"TX3_TN_B5_RDC"		);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M45_TX3_TO_B8_RMC,			"TX3_TO_B8_RMC"		);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M46_TX3_TP_B3_RDI,			"TX3_TP_B3_RDI"		);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M47_TX3_TQ_B1_FECF,			"TX3_TQ_B1_FECF"	);
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M48_TX3_TR_B1_FCTO,			"TX3_TR_B1_FCTO"	);
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M49_TX3_TS_B8_MEAS,			"TX3_TS_B8_MEAS"	);
		
	}


	{

		pVec = &this->m_mode.meas_NVM_vParam;

		pVec->f_set_vec_name ("CLIN_Data_TLE8881::m_mode.meas_NVM_vParam");
		pVec->f_clear_vec();

		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R00							,"--"				);

		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R10_b2_3_PP					,"b3_PP"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R10_b5_3_VSET				,"b3_VSET"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R10_b6_1_ALT					,"b1_ALT"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R10_b7_1_CFG					,"b1_CFG"			);		
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R11_b1_2_LRCFT				,"b2_LRCFT"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R11_b2_1_res_0				,"b1_res_0"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R11_b5_3_LRCRT				,"b3_LRCRT"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R11_b7_2_LRCDIS				,"b2_LRCDIS"		);	

		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R20_b0_1_EOFF				,"b1_EOFF"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R20_b1_1_res_0				,"b1_res_0"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R20_b2_1_OTEXC				,"b1_OTEXC"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R20_b3_1_CSHT				,"b1_CSHT"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R20_b5_2_LEO					,"b2_LEO"			);
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R20_b7_2_SSS					,"b2_SSS"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R21_b2_3_HTG					,"b3_HTG"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R21_b5_3_THT					,"b3_THT"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R21_b7_2_CLIM				,"b2_CLIM"			);	

		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R30_b2_3_SUPP				,"b3_SUPP"			);
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R30_b7_5_CLASS				,"b5_CLASS"			);

		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R31_b1_2_EWMA_K				,"b2_EWMA_K"		);
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R31_b3_2_EWMA_Mode			,"b2_EWMA_Mode"		);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R31_b7_4_res_0				,"b4_res_0"			);


		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R40_b1_2_IEXC				,"b2_IEXC"			);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R40_b4_3_PEXCDC				,"b3_PEXCDC"		);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R40_b7_3_CTSADJ				,"b3_CTSADJ"		);	

		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R41_b1_2_T_PSB_ON_MAX		,"b2_T_PSB_ON_MAX"	);
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R41_b2_1_SPCHG_EN			,"b1_SPCHG_EN"		);
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R41_b4_2_SPCHG_CFG			,"b2_SPCHG_CFG"		);
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R41_b6_2_RPARA_SEL			,"b2_RPARA_SEL"		);	
		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R41_b7_1_LOCK_EN				,"b1_LOCK_EN"		);

		pVec->f_insert_mode (ENUM_CLIN_DATA_TLE8881_NVM_PARAM::R99_enum_end					,"-"				);	
	}




}

bool CLin_Data::f_check_TX2_param (unsigned select_param )	// Parameter가 TX2인지 확인한다.
{
	switch( select_param )
	{
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M21_TX2_TH_RSUPP	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M22_TX2_TI_RCLASS:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M23_TX2_TJ_MFG	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M24_TX2_TJ_ASIC	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M11_TX2_BYTE1	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M12_TX2_BYTE2	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M13_TX2_UINT16	:	return true; 
	default:
		return false;
	}

	return false;	// nParam값이 TX2이면 true를 반환한다.

}

bool CLin_Data::f_check_TX3_param (unsigned select_param )	// Parameter가 TX3인지 확인한다.
{

	switch( select_param )
	{
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M41_TX3_TK_B1_FHT	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M42_TX3_TL_B1_FROT	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M43_TX3_TM_B1_FEL	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M44_TX3_TN_B5_RDC	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M45_TX3_TO_B8_RMC	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M46_TX3_TP_B3_RDI	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M47_TX3_TQ_B1_FECF	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M48_TX3_TR_B1_FCTO	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M49_TX3_TS_B8_MEAS	:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M31_TX3_BYTE1		:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M32_TX3_BYTE2		:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M33_TX3_BYTE3		:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M34_TX3_BYTE4		:	return true; 
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M35_TX3_UINT32		:	return true; 

	default:
		return false;
	}

	return false;	// return값이 nParam값이 false이면
}


bool CLin_Data::f_extract_TX_param_from_recv_union (unsigned select_param, unsigned &extract_val)
{

	extract_val = 0;

	switch( select_param )
	{
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M21_TX2_TH_RSUPP	:
		extract_val = this->m_recv.uTX2.reg.b10_3_ALT_SUPPLIER;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;


	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M22_TX2_TI_RCLASS	:
		extract_val = this->m_recv.uTX2.reg.b13_5_ALT_CLASS;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;


	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M23_TX2_TJ_MFG	:
		extract_val = this->m_recv.uTX2.reg.b20_3_AIC_MFG_ID;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;


	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M24_TX2_TJ_ASIC	:
		extract_val = this->m_recv.uTX2.reg.b23_5_ASIC_ID;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;


	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M11_TX2_BYTE1	:
		extract_val = this->m_recv.uTX2.u8.Data1;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;

	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M12_TX2_BYTE2	:
		extract_val = this->m_recv.uTX2.u8.Data2;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;

	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M13_TX2_UINT16	:
		extract_val = this->m_recv.uTX2.u16;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;



	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M31_TX3_BYTE1	:
		extract_val = this->m_recv.uTX3.u8.Data1;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;


	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M32_TX3_BYTE2	:
		extract_val = this->m_recv.uTX3.u8.Data2;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;


	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M33_TX3_BYTE3	:
		extract_val = this->m_recv.uTX3.u8.Data3;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;

	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M34_TX3_BYTE4	:
		extract_val = this->m_recv.uTX3.u8.Data4;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;


	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M35_TX3_UINT32	:
		extract_val = this->m_recv.uTX3.u32;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;



	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M41_TX3_TK_B1_FHT	:
		extract_val = this->m_recv.uTX3.reg.b10_1_TK_F_HT;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;



	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M42_TX3_TL_B1_FROT:
		extract_val = this->m_recv.uTX3.reg.b11_1_TL_F_ROT;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;


	
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M43_TX3_TM_B1_FEL	:
		extract_val = this->m_recv.uTX3.reg.b12_1_TM_F_EL;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;


	
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M44_TX3_TN_B5_RDC	:
		extract_val =this->m_recv.uTX3.reg.b13_5_TN_RDC;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;


	
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M45_TX3_TO_B8_RMC	:
		extract_val = this->m_recv.uTX3.reg.b20_8_TO_RMC;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;



	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M46_TX3_TP_B3_RDI	:
		extract_val = this->m_recv.uTX3.reg.b30_3_TP_RDI;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;


	
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M47_TX3_TQ_B1_FECF:
		extract_val = this->m_recv.uTX3.reg.b36_1_TQ_F_CEF;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;

	
	
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M48_TX3_TR_B1_FCTO:
		extract_val = this->m_recv.uTX3.reg.b37_1_TR_F_CTO;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;


	
	case ENUM_CLIN_DATA_TLE8881_MEAS_TX_PARAM::M49_TX3_TS_B8_MEAS:
		extract_val = this->m_recv.uTX3.reg.b40_8_TS_R;
		{
			if (m_recv.bValidTX2) 
				return true; 
			else 
				return false;
		}
		break;



	default:
		extract_val = 0;
		return false;

	}

	return false;	// nParam값이 TX2이면 true를 반환한다.
}



double CLin_Data::f_conv_Val_from_TX3_RDC ( unsigned nRDC )
{

	double fLow = 3.125 * nRDC;
	double fHi  = 3.125 * (nRDC + 1);
	double fCen = (fLow + fHi)/2.0;

	return fCen; // Percent 
}

