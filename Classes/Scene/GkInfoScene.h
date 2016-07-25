//
//  GameCjScene.h
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GkInfoScene_h
#define xzdd_GkInfoScene_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "GkInfoLayer.h"

#else 

#include "../Layer/GkInfoLayer.h"

#endif

class GkInfoScene : public cocos2d::CCScene
{
    
public:
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(); 
    
	// implement the "static node()" method manually
	CREATE_FUNC(GkInfoScene);
    
};


#endif

