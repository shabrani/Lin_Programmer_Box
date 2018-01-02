#pragma once

#include "linlib.h"

typedef  char                       KVRTYPE_INT8;
typedef  short                      KVRTYPE_INT16;
typedef  long                       KVRTYPE_INT32;
typedef  unsigned char              KVRTYPE_UINT8;
typedef  unsigned short             KVRTYPE_UINT16;
typedef  unsigned long              KVRTYPE_UINT32;
typedef  float                      KVRTYPE_REAL;
typedef  double                     KVRTYPE_LREAL;

typedef	 KVRTYPE_UINT32				KVRTYPE_LIN_ARBID;

typedef  struct {
   unsigned int			LowPart;
   unsigned int			HighPart;
} KVRTYPE_UINT64;

typedef struct{
   unsigned int			ArbitrationId;
   unsigned char		DataLength;
   unsigned char		Data[8];
} KVRTYPE_LIN_FRAME;

typedef struct{
	KVRTYPE_UINT64		Timestamp;
	unsigned int		ArbitrationId;
	unsigned int		DataLength;
	unsigned char		Data[8];
	unsigned int		Flags;
	LinMessageInfo		msgInfo;
}KVR_LIN_STRUCT;

typedef struct{
	unsigned long		timeOffset;
}KVR_LIN_TIME;
