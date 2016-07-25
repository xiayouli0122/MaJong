//
//  MyTinyXmlParser.h
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_MyTinyXmlParser_h
#define xzdd_MyTinyXmlParser_h

#include "ConstantDef.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "tinyxml.h"

#else 

#include "../tinyxml/tinyxml.h"

#endif

using namespace cocos2d;

class MyTinyXmlParser
{
public:
    
    static int GetGuanKaCount();
	static GUAN_KA * GetGuanKa();
	static void loadCondition(TiXmlElement* conditionElement, GUAN_KA * pGuanKa, int guankaIndex, int conditionIndex, int conDetailIndex);
    
    //获取成就
    static CHENGJIU * GetChengJiu();
    //获取更多游戏
    static MOREGAME * GetMoreGame();
    
    //获取Help页面内容
    static std::string GetHelp(BYTE index);
};

#endif
