#pragma once

#ifndef xzdd_GameMGLayer_h
#define xzdd_GameMGLayer_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"
#include "GameMGBatch.h"

#else 

#include "../Common/ConstantDef.h"
#include "../Sprite/Batch/GameMGBatch.h"

#endif

using namespace cocos2d;

class GameMGLayer : public cocos2d::CCLayer
{
	GameMGBatch    * cjBatch;     //成就缓存
    
private:
	float y_begin;//触摸开始时y位置
	float y_batch_location_begin;//触摸开始时成就batch位置
	float y_end;//触摸结束时y位置
	float y_max;
    
    float moveSpeed;            //移动速度    
    bool enableMove;            //允许自动移动
    float y_last;               //上一帧 y的位置
    
    CCSize cjSize;
	int cjNum;
    
public:
    //初始化--------------------------------------------------
	virtual bool init();  
    virtual void onExit();
    
	// implement the "static node()" method manually
	CREATE_FUNC(GameMGLayer);
	
    virtual void keyBackClicked();
    
    //触摸相关方法---------------------------------------------
    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
    //定时器，定时调用
    void undateState(float dt);
    
};

#endif

