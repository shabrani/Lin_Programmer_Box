#pragma once

///////////////////////////////////////////////////////////
#define         K0      		1
#define         K1      		2
#define         K2      		4
#define         K3      		8
#define         K4      		16
#define         K5      		32
#define         K6     	 		64
#define         K7      		128

#define         K8              256
#define         K9              512
#define         K10             1024
#define         K11             2048
#define         K12             4096
#define         K13             8192
#define         K14             16384
#define         K15             32768

#define         K16             65536
#define         K17             131072
#define         K18             262144
#define         K19             524288
#define         K20             1048576
#define         K21             2097152
#define         K22             4194304
#define         K23             8388608

#define			K24				16777216	
#define			K25				33554432
#define			K26				67108864
#define			K27				134217728
#define			K28				268435456
#define			K29				536870912
#define			K30				1073741824
#define			K31				2147483648

///////////////////////////////////////////////////////////
#define			UINT08	unsigned char
#define			UINT16	unsigned short
#define			UINT32	unsigned int
#define			UINT64	unsigned long long

///////////////////////////////////////////////////////////
typedef union
{
   UINT08	byte;

   struct {
	unsigned int b0  :1;
	unsigned int b1  :1;
	unsigned int b2  :1;
	unsigned int b3  :1;
	unsigned int b4  :1;
	unsigned int b5  :1;
	unsigned int b6  :1;
	unsigned int b7  :1;
   }bit;
}TU_UINT8;

typedef union
{
	UINT16 uint16;

	struct {
		unsigned char b0;
		unsigned char b1;
	}byte;

   struct {
	unsigned int b00  :1;
	unsigned int b01  :1;
	unsigned int b02  :1;
	unsigned int b03  :1;
	unsigned int b04  :1;
	unsigned int b05  :1;
	unsigned int b06  :1;
	unsigned int b07  :1;

	unsigned int b10  :1;
	unsigned int b11  :1;
	unsigned int b12  :1;
	unsigned int b13  :1;
	unsigned int b14  :1;
	unsigned int b15  :1;
	unsigned int b16  :1;
	unsigned int b17  :1;
   }bit;

}TU_UINT16;

typedef union
{
	UINT32 uint32;

	struct {
		unsigned char b0;
		unsigned char b1;
		unsigned char b2;
		unsigned char b3;
	}byte;

	struct {
		unsigned short s0;
		unsigned short s1;
	}U16;

	struct {
		unsigned int b00  :1;
		unsigned int b01  :1;
		unsigned int b02  :1;
		unsigned int b03  :1;
		unsigned int b04  :1;
		unsigned int b05  :1;
		unsigned int b06  :1;
		unsigned int b07  :1;
		unsigned int b08  :1;
		unsigned int b09  :1;
		unsigned int b10  :1;
		unsigned int b11  :1;
		unsigned int b12  :1;
		unsigned int b13  :1;
		unsigned int b14  :1;
		unsigned int b15  :1;
		unsigned int b16  :1;
		unsigned int b17  :1;
		unsigned int b18  :1;
		unsigned int b19  :1;
		unsigned int b20  :1;
		unsigned int b21  :1;
		unsigned int b22  :1;
		unsigned int b23  :1;
		unsigned int b24  :1;
		unsigned int b25  :1;
		unsigned int b26  :1;
		unsigned int b27  :1;
		unsigned int b28  :1;
		unsigned int b29  :1;
		unsigned int b30  :1;
		unsigned int b31  :1;
	}bit;

	struct {
		unsigned int P00  :1;
		unsigned int P01  :1;
		unsigned int P02  :1;
		unsigned int P03  :1;
		unsigned int P04  :1;
		unsigned int P05  :1;
		unsigned int P06  :1;
		unsigned int P07  :1;

		unsigned int P10  :1;
		unsigned int P11  :1;
		unsigned int P12  :1;
		unsigned int P13  :1;
		unsigned int P14  :1;
		unsigned int P15  :1;
		unsigned int P16  :1;
		unsigned int P17  :1;

		unsigned int P20  :1;
		unsigned int P21  :1;
		unsigned int P22  :1;
		unsigned int P23  :1;
		unsigned int P24  :1;
		unsigned int P25  :1;
		unsigned int P26  :1;
		unsigned int P27  :1;

		unsigned int P30  :1;
		unsigned int P31  :1;
		unsigned int P32  :1;
		unsigned int P33  :1;
		unsigned int P34  :1;
		unsigned int P35  :1;
		unsigned int P36  :1;
		unsigned int P37  :1;
	}PBit;
}TU_UINT32;



typedef union
{
	UINT64 uint64;
	
	struct 
	{
		unsigned long L0;
		unsigned long L1;
	}U32;

	struct 
	{
		unsigned short S0;
		unsigned short S1;
		unsigned short S2;
		unsigned short S3;
	}U16;


	struct 
	{
		unsigned char C0;
		unsigned char C1;
		unsigned char C2;
		unsigned char C3;
		unsigned char C4;
		unsigned char C5;
		unsigned char C6;
		unsigned char C7;
	}U8;

	struct {
		unsigned int b00  :1;
		unsigned int b01  :1;
		unsigned int b02  :1;
		unsigned int b03  :1;
		unsigned int b04  :1;
		unsigned int b05  :1;
		unsigned int b06  :1;
		unsigned int b07  :1;
		unsigned int b08  :1;
		unsigned int b09  :1;
		unsigned int b10  :1;
		unsigned int b11  :1;
		unsigned int b12  :1;
		unsigned int b13  :1;
		unsigned int b14  :1;
		unsigned int b15  :1;
		unsigned int b16  :1;
		unsigned int b17  :1;
		unsigned int b18  :1;
		unsigned int b19  :1;
		unsigned int b20  :1;
		unsigned int b21  :1;
		unsigned int b22  :1;
		unsigned int b23  :1;
		unsigned int b24  :1;
		unsigned int b25  :1;
		unsigned int b26  :1;
		unsigned int b27  :1;
		unsigned int b28  :1;
		unsigned int b29  :1;
		unsigned int b30  :1;
		unsigned int b31  :1;
		unsigned int b32  :1;
		unsigned int b33  :1;
		unsigned int b34  :1;
		unsigned int b35  :1;
		unsigned int b36  :1;
		unsigned int b37  :1;
		unsigned int b38  :1;
		unsigned int b39  :1;
		unsigned int b40  :1;
		unsigned int b41  :1;
		unsigned int b42  :1;
		unsigned int b43  :1;
		unsigned int b44  :1;
		unsigned int b45  :1;
		unsigned int b46  :1;
		unsigned int b47  :1;
		unsigned int b48  :1;
		unsigned int b49  :1;
		unsigned int b50  :1;
		unsigned int b51  :1;
		unsigned int b52  :1;
		unsigned int b53  :1;
		unsigned int b54  :1;
		unsigned int b55  :1;
		unsigned int b56  :1;
		unsigned int b57  :1;
		unsigned int b58  :1;
		unsigned int b59  :1;
		unsigned int b60  :1;
		unsigned int b61  :1;
		unsigned int b62  :1;
		unsigned int b63  :1;
	}bit;

}TU_UINT64;
