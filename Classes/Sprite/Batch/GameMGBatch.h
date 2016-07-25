#pragma once

#ifndef xzdd_GameMGBatch_h
#define xzdd_GameMGBatch_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "GameMGSprite.h"

#else 

#include "../GameMGSprite.h"

#endif


using namespace cocos2d;

class GameMGBatch : public cocos2d::CCNode
{
    
protected:
//    CCMutableArray<GameMGSprite*> *cjArray;   //成就数组
	CCArray *cjArray;   //成就数组
    
public:
	//初始化--------------------------------------------------
	virtual bool init();
	virtual bool SetAllMg(MOREGAME * mg, int cjNum);
    virtual void onExit();
	// implement the "static node()" method manually
	CREATE_FUNC(GameMGBatch);  
    
	float totalHeight;
};

#endif

