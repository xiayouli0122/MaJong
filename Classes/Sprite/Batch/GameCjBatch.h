//
//  GameCjBatch.h
//  xzdd
//
//  Created by  on 12-4-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameCjBatch_h
#define xzdd_GameCjBatch_h
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "GameCjSprite.h"
#else 
#include "../GameCjSprite.h"
#endif

using namespace cocos2d;

class GameCjBatch : public cocos2d::CCNode
{
    
protected:
//    CCSpriteBatchNode * cjBatchNode;
//    CCMutableArray<GameCjSprite*> *cjArray;   //成就数组
	CCArray *cjArray;   //成就数组
    
public:
	//初始化--------------------------------------------------
	virtual bool init();
	virtual bool SetAllCj(CHENGJIU * cj, int cjNum, CCSize itemSize);
    virtual void onExit();
	// implement the "static node()" method manually
	CREATE_FUNC(GameCjBatch);  
    
	float totalHeight;
};

#endif