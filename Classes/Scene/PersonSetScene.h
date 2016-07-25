//
//  PersonSetScene.h
//  xzdd
//
//  Created by  on 12-5-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_PersonSetScene_h
#define xzdd_PersonSetScene_h
#include "cocos2d.h"

class PersonSetScene : public cocos2d::CCScene
{
    cocos2d::CCSprite * bjSprite;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    virtual void onExit();
    virtual void onEnter();
    
	// implement the "static node()" method manually
	CREATE_FUNC(PersonSetScene);
    
};

#endif
