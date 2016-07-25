//
//  GuanKaSprite.h
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GuanKaSprite_h
#define xzdd_GuanKaSprite_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"

#else 

#include "../Common/ConstantDef.h"

#endif

using namespace cocos2d;

typedef enum 
{
    GK_None,
    GK_Lock,
	GK_Star1,
	GK_Star2,
	GK_Star3,
    GK_Hide,
    GK_UNPAY
} GuanKaState; 

class GuanKaSprite : public CCSprite
{
	CCSprite * sNumber;//关号
    CCSprite * sLock;
    CCSprite * sStar1;
    CCSprite * sStar2;
    CCSprite * sStar3;
	CCSprite * sStarDark1;//灰色的星1
	CCSprite * sStarDark2;//灰色的星2
	CCSprite * sStarDark3;//灰色的星3
	CCSprite * sText;//关卡名字
    
//    CCSprite * sBgPay;
    CCSprite * sLogoPay;
    
public:
	GuanKaState guanKaState;
    
	GuanKaSprite(void);
	~GuanKaSprite(void);
    
	virtual bool init();
    
    //公有方法------------------------------
    //通过图片名创建card对象
    static GuanKaSprite* guanKaWithFrameName(const char *pFrameName);
    
    //更换card的图片
    virtual void setDisplayFrameName(GuanKaState state, int guankaIndex);
    
	BYTE guanKaContent;   //关卡的内容

	CREATE_FUNC(GuanKaSprite);
};

#endif