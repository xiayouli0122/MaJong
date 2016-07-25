#ifndef RULE_DEF_H 
#define RULE_DEF_H 

#include <math.h>

#define MODE_BIT		0x00000001
#define FAST_BIT		0x00000002
#define MULT3_BIT		0x00000004
#define BID_BIT			0x00000010
#define ZIMO_BIT		0x00000020
#define GFXY_BIT		0x00000040

#define GET_GAME_MODE(n)	(((n)&MODE_BIT))
#define GET_FAST(n)			((n)&FAST_BIT)
#define GET_MUL3(n)			((n)&MULT3_BIT)
#define GET_BID(n)			((n)&BID_BIT)
#define GET_ZIMO(n)			((n)&ZIMO_BIT)
#define GET_GFXY(n)			(((n)&GFXY_BIT)? GFXYJiaJiaYou: GFXYChengbao)


enum GAME_MODE
{
	GameModeNormal	= 0,
	GameModeBlood	= 1
};

enum GuaFengXiaYu
{
	GFXYChengbao	= 0,
	GFXYJiaJiaYou	= 1
};

#define MAX_BEANS_BIT	0x00000100
#define FEE_BEANS_BIT	0x00010000
#define MUL_ID_BIT		0x04000000


#define GET_MIN_BEANS(n)	((n)&0x000000ff)
#define GET_MAX_BEANS(n)	(((n)&0x0000ff00)/(MAX_BEANS_BIT))
#define GET_FEE_BEANS(n)	(((n)&0x03ff0000)/(FEE_BEANS_BIT))

#define GET_MUL_ID(n)		(((n)&0x3c000000)/(MUL_ID_BIT))
#define GET_BID(n)			((n)&BID_BIT)
#define GET_FAST(n)			((n)&FAST_BIT)

#endif