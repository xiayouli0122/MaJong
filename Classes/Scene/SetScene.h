//
//  SetScene.h
//  xzdd
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_SetScene_h
#define xzdd_SetScene_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "SetProgress.h"
#include "SelectSprite.h"

#else 

#include "../Layer/SetProgress.h"
#include "../Sprite/SelectSprite.h"

#endif
using namespace cocos2d;

class SetScene : public CCLayer
{
    CCSprite * bjSprite;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    virtual void onExit();
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(SetScene);
    
};


#endif