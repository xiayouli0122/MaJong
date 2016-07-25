//
//  GuanKaBatch.h
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GuanKaBatch_h
#define xzdd_GuanKaBatch_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"
#include "CommonFunction.h"
#include "GuanKaSprite.h"
#include "LoadingScene.h"

#else 

#include "../../Common/ConstantDef.h"
#include "../../Common/CommonFunction.h"
#include "../GuanKaSprite.h"
#include "../../Scene/LoadingScene.h"

#endif

using namespace cocos2d;

class GuanKaBatch : public cocos2d::CCNode
{
    
protected:
//    CCMutableArray<GuanKaSprite*> *guanKaArray;   //关卡数组
	CCArray *guanKaArray;   //关卡数组
	int guankaNum; //关卡数量
    
public:
	//初始化--------------------------------------------------
	virtual bool init();
	virtual bool initArray(int guankaNum);
    virtual void onExit();
	// implement the "static node()" method manually
	CREATE_FUNC(GuanKaBatch);
    
    //公有方法------------------------------------------------
    //设置所有关卡
    void SetAllGuanKa(int guankaNum);
    
    void onTouchSelected(CCPoint touchPoint);
    
//    //触摸相关方法---------------------------------------------
//    virtual bool touchBegan(CCTouch* touch);
//	virtual void touchEnded(CCTouch* touch);
//	virtual void touchCancelled(CCTouch* touch);
//	virtual void touchMoved(CCTouch* touch);
    
	virtual void menuCallback(CCObject* pSender);
};

#endif