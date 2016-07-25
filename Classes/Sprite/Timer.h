//
//  Timer.h
//  xzdd
//
//  Created by  on 12-3-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_Timer_h
#define xzdd_Timer_h
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "ConstantDef.h"
#include "CommonFunction.h"

#else 
#include "../Common/ConstantDef.h"
#include "../Common/CommonFunction.h"

#endif

using namespace cocos2d;

//计时器对象
class Timer : public CCSprite
{
    CCLabelBMFont * numberLabel;    //倒数数字控件
    //箭头
    CCSprite * sArrow;
    CCSprite * xArrow;
    CCSprite * zArrow;
    CCSprite * yArrow;
    
public:
    //初始化--------------------------------
    Timer(void);
	virtual ~Timer(void);
    virtual bool init();
    
    unsigned short  countTime;
    //公有方法------------------------------
    //通过图片名创建对象
    static Timer* timerWithFrameName(const char *pFrameName);

    void SetTime(unsigned short time,BYTE chair);
    void SetTime(unsigned short time);
    void SetChair(BYTE chair);
};

#endif
