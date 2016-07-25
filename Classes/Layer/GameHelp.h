//
//  GameHelp.h
//  xzdd
//
//  Created by  on 12-5-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameHelp_h
#define xzdd_GameHelp_h
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"

#else 

#include "../Common/ConstantDef.h"

#endif

using namespace cocos2d;

class GameHelp : public cocos2d::CCLayer
{
public:
    //初始化--------------------------------------------------
	virtual bool init();  
    virtual void onExit();
    
	// implement the "static node()" method manually
	CREATE_FUNC(GameHelp);
};

#endif

