//
//  OutCard.h
//  xzdd
//
//  Created by  on 12-3-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_OutCard_h
#define xzdd_OutCard_h

#include "cocos2d.h"
#include "Card.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"

#else 

#include "../Common/ConstantDef.h"

#endif

using namespace cocos2d;

//sprite对象，刚打出的牌
class OutCard : public Card
{
    CCSprite * bjSprite;    //背景图片
public:
    //初始化--------------------------------
    OutCard(void);
	virtual ~OutCard(void);
    virtual bool init();

    //公有方法------------------------------
    //通过图片名创建card对象
    static OutCard* outCardWithFrameName(const char *pFrameName);

    
};

#endif
