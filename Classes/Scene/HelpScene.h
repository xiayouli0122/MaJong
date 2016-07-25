//
//  HelpScene.h
//  xzdd
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_HelpScene_h
#define xzdd_HelpScene_h

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "GameHelp.h"
#include "CommonFunction.h"

#else 

#include "../Layer/GameHelp.h"
#include "../Common/CommonFunction.h"

#endif

using namespace cocos2d;

class HelpScene : public cocos2d::CCLayer
{
    GameHelp * helpLayer;
    CCSprite * bjSprite;
private:
	float y_begin;//触摸开始时y位置
	float y_batch_location_begin;//触摸开始时成就batch位置
	float y_end;//触摸结束时y位置
    float y_max;
    float y_min;
    
    float moveSpeed;            //移动速度    
    bool enableMove;            //允许自动移动
    float y_last;               //上一帧 y的位置
    
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    virtual void onExit();
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuBackCallback(CCObject* pSender);
    
	// implement the "static node()" method manually
	CREATE_FUNC(HelpScene);
    
    //触摸相关方法---------------------------------------------
    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

	virtual void keyBackClicked();
    
    //定时器，定时调用
    void undateState(float dt);
};


#endif
