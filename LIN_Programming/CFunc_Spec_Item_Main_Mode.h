#pragma once
#include "CFunc_Mode_Vector.h"


namespace ENUM_CSPEC_LIMIT_MODE
{
	enum Enum
	{
		M0_BOTH_LIMIT		=	0,
		M1_UPPER_LIMIT		=	1,
		M2_LOWER_LIMIT		=	2,
		M3_EQUAL			=	3,
		M4_NOT_EQUAL		=	4,
		M9_ENUM_END			=	9
	};		
};


namespace ENUM_CSPEC_DATA_MODE
{
	enum Enum
	{
		M00_DBL_DEFAULT				=	0,
		M01_DBL_USER_FORMAT			=	1,

		M10_UINT_DEFAULT			=	10,
		//M11_UINT_USER_FORMAT		=	11,

		M21_UINT_HEX_2				=	21,
		M22_UINT_HEX_4				=	22,
		M23_UINT_HEX_6				=	23,
		M24_UINT_HEX_8				=	24,

		M31_UINT_BIN_1				=	31,
		M32_UINT_BIN_2				=	32,
		M33_UINT_BIN_3				=	33,
		M34_UINT_BIN_4				=	34,
		M35_UINT_BIN_5				=	35,
		M36_UINT_BIN_6				=	36,
		M37_UINT_BIM_7				=	37,
		M38_UINT_BIN_8				=	38,
		
		M50_UINT_BOOL				=	50,
		//M50_INT_DEFAULT				=	50,
		//M51_INT_USER_FMT			=	51

		M99_MODE_END				= 99
	};
};


namespace ENUM_CSPEC_ITEM_DATA_DISP_MODE
{
	enum Enum
	{
		M00_NORMAL_DISPLAY_VALUE	= 00,
		M10_BOOL_TRUE_FALSE_TEXT	= 10,		//		
		M21_LIN_PARAM_TEXT			= 21,		//
		M99_ENUM_END				= 99
	};
};


class CFunc_Spec_Item_Main_Mode
{
public:
	CFunc_Spec_Item_Main_Mode(void);
	~CFunc_Spec_Item_Main_Mode(void);


	CFunc_Mode_Vector	stDataDisp;
	CFunc_Mode_Vector	m_DataFormat;
	CFunc_Mode_Vector	m_DataLimitMode;	


};
