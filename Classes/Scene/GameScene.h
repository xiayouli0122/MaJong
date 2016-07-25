//
//  GameScene.h
//  xzdd
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameScene_h
#define xzdd_GameScene_h

#include "cocos2d.h"

class GameCScene : public cocos2d::CCScene
{
    cocos2d::CCSprite * bjSprite;
    cocos2d::CCSprite * bgGkName;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    virtual void onExit();
    virtual void onEnter();
	//static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(GameCScene);
    
    void onSystemResume();
};

#endif
