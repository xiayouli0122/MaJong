//
//  ShowCJ.h
//  xzdd
//
//  Created by  on 12-4-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_ShowCJ_h
#define xzdd_ShowCJ_h
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"

#else 

#include "../Common/ConstantDef.h"

#endif

using namespace cocos2d;

class ShowCJ : public CCSprite
{
    CCLabelTTF* label;
    CCLabelTTF* l_cj;
public:
    //初始化--------------------------------
    ShowCJ(void);
	virtual ~ShowCJ(void);
    virtual bool init();
    
    //公有方法------------------------------
    static ShowCJ* creatShowCJ();
    void show(CHENGJIU * cj);
};


#endif
