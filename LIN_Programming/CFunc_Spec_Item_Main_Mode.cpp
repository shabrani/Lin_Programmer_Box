#include "stdafx.h"
#include "CFunc_Spec_Item_Main_Mode.h"


CFunc_Spec_Item_Main_Mode::CFunc_Spec_Item_Main_Mode(void)
{

	CFunc_Mode_Vector *pVec;


	{
		pVec = &this->stDataDisp;

		pVec->f_set_vec_name ("CFunc_Spec_Item_Mode::DataDispMode");
		pVec->f_clear_vec();

		pVec->f_insert_mode (ENUM_CSPEC_ITEM_DATA_DISP_MODE::M00_NORMAL_DISPLAY_VALUE,	"Default :: Value Type"				);
		pVec->f_insert_mode (ENUM_CSPEC_ITEM_DATA_DISP_MODE::M10_BOOL_TRUE_FALSE_TEXT,	"Convert Value to True/False Text"	);
//		pVec->f_insert_mode (ENUM_CSPEC_ITEM_DATA_DISP_MODE::M21_LIN_PARAM_TEXT,			"LIN Param Convert Meas to "		);
	}

	{
		pVec = &this->m_DataFormat;

		pVec->f_set_vec_name ("CSpec::Spec_vDataFmt");
		pVec->f_clear_vec();

		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M00_DBL_DEFAULT,			"DBL"		);
	//	pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M01_DBL_USER_FORMAT,		"DBL_fmt"	);
		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M10_UINT_DEFAULT,		"UINT"		);
	//	pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M11_UINT_USER_FORMAT,	"UINT_fmt"	);

		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M21_UINT_HEX_2,			"UINT_HEX_2"	);
		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M22_UINT_HEX_4,			"UINT_HEX_4"	);
		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M23_UINT_HEX_6,			"UINT_HEX_6"	);
		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M24_UINT_HEX_8,			"UINT_HEX_8"	);

		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M31_UINT_BIN_1,			"UINT_BIN_1"	);
		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M32_UINT_BIN_2,			"UINT_BIN_2"	);
		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M33_UINT_BIN_3,			"UINT_BIN_3"	);
		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M34_UINT_BIN_4,			"UINT_BIN_4"	);
		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M35_UINT_BIN_5,			"UINT_BIN_5"	);
		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M36_UINT_BIN_6,			"UINT_BIN_6"	);
		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M37_UINT_BIM_7,			"UINT_BIM_7"	);
		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M38_UINT_BIN_8,			"UINT_BIN_8"	);

		pVec->f_insert_mode (ENUM_CSPEC_DATA_MODE::M50_UINT_BOOL,			"UINT_BOOL"		);

	}


	{

		pVec = &this->m_DataLimitMode;

		pVec->f_set_vec_name ("CSpec::Spec_vLimitMode");
		pVec->f_clear_vec();


		 pVec->f_insert_mode (ENUM_CSPEC_LIMIT_MODE::M0_BOTH_LIMIT	,	"BOTH Limit" 	);
		 pVec->f_insert_mode (ENUM_CSPEC_LIMIT_MODE::M1_UPPER_LIMIT,	"UPPER Limit"	);
		 pVec->f_insert_mode (ENUM_CSPEC_LIMIT_MODE::M2_LOWER_LIMIT,	"LOWER Limit"	);
		 pVec->f_insert_mode (ENUM_CSPEC_LIMIT_MODE::M3_EQUAL		,	"EQUAL"			);
		 pVec->f_insert_mode (ENUM_CSPEC_LIMIT_MODE::M4_NOT_EQUAL	,	"Not EQUAL"		);
	}



}

CFunc_Spec_Item_Main_Mode::~CFunc_Spec_Item_Main_Mode(void)
{
}