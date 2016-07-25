//
//  GkInfoLayer.h
//  xzdd
//
//  Created by  on 12-4-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GkInfoLayer_h
#define xzdd_GkInfoLayer_h
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"
#include "GkInfoBatch.h"

#else 

#include "../Common/ConstantDef.h"
#include "../Sprite/Batch/GkInfoBatch.h"

#endif

using namespace cocos2d;

class GkInfoLayer : public cocos2d::CCLayer
{
	GkInfoBatch    * infoBatch;     //成就缓存
    
private:
	float y_begin;//触摸开始时y位置
	float y_batch_location_begin;//触摸开始时成就batch位置
	float y_end;//触摸结束时y位置
    float moveSpeed;    //移动速度
    float y_max;
    float y_last;               //上一帧 y的位置
	int gkNum;
    bool enableMove;            //允许自动移动
    
public:
    //初始化--------------------------------------------------
	virtual bool init();  
    virtual void onExit();
    
	// implement the "static node()" method manually
	CREATE_FUNC(GkInfoLayer)
    
    //触摸相关方法---------------------------------------------
    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
    //定时器，定时调用
    void undateState(float dt);
};

#endif