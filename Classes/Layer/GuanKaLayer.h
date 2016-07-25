//
//  GuanKaLayer.h
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GuanKaLayer_h
#define xzdd_GuanKaLayer_h

#include "cocos2d.h"
#include "ParentLayer.h"
#include "GameMessage.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"
#include "GuanKaBatch.h"

#else 

#include "../Common/ConstantDef.h"
#include "../Sprite/Batch/GuanKaBatch.h"

#endif

using namespace cocos2d;

class GuanKaLayer : public ParentLayer
{
	GuanKaBatch    * guanKaBatch;     //关卡缓存
    GameMessage    * gameMessage;

private:
	float x_begin;//触摸开始时x位置
	float x_batch_location_begin;//触摸开始时关卡batch位置
	float x_end;//触摸结束时x位置
	CCSprite *ping1;//关卡屏1
	CCSprite *ping2;//关卡屏2
	bool isMoveActionRunning;
    
public:
    //初始化--------------------------------------------------
	virtual bool init();  
    virtual void onExit();
    
	//GUAN_KA m_GuanKa[20];
	int guankaNum;
    
	// implement the "static node()" method manually
	CREATE_FUNC(GuanKaLayer);
    void SelectGK(BYTE gk);
    virtual void onCancel(MessageType type);
    virtual void onConfirm(MessageType type);
    
	void moveActionCallback();
    virtual void keyBackClicked();
    
    //触摸相关方法---------------------------------------------
    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
    void ShowOpenAllGuanka(int arg = 0);
    void ShowPaySuccess(int nItem);
    void ShowPayFailed(int nItem);
    void ShowDelock(int arg = 0);
    
    void ShowMsg(int arg = 0);
    
    void TimerCheckPay(float dt);
    
    void HandlePaySuccess(int nItem);
    void HandlePayFailed(int nItem);
    
    void PayDelock(int arg = 0);
};

#endif