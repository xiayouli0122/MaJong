//
//  Card.h
//  xzdd
//
//  Created by  on 12-3-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_Card_h
#define xzdd_Card_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "TypeDef.h"

#else 

#include "../GameCore/TypeDef.h"

#endif

using namespace cocos2d;

//sprite对象，桌面上的一张牌
class Card : public CCSprite
{
public:
    //初始化--------------------------------
    Card(void);
	virtual ~Card(void);
    virtual bool init();
    
    //公有方法------------------------------
    //通过图片名创建card对象
    static Card* cardWithFrameName(const char *pFrameName);
    
    //更换card的图片
    virtual void setDisplayFrameName(const char *frameName);
    
	BYTE        cardContent;    //牌的内容
};

#endif
