//
//  SplashLayer.h
//  xzdd
//
//  Created by Paddy on 12-12-7.
//
//

#ifndef __xzdd__SplashLayer__
#define __xzdd__SplashLayer__

#include <iostream>

#include "cocos2d.h"

//#include "GameMessage.h"


#include "../Common/ConstantDef.h"
#include "../Sprite/Batch/SplashBatch.h"


using namespace cocos2d;

class SplashLayer : public CCLayer
{
	SplashBatch    * splashBatch;
    CCMenu         * pMenu;
    
    bool m_bTouchedSplash;
    bool bTouchFlag;
    
private:
	float x_begin;//触摸开始时x位置
	float x_batch_location_begin;//触摸开始时关卡batch位置
	float x_end;//触摸结束时x位置
//	CCSprite *ping1;//屏1
//	CCSprite *ping2;//屏2
//    CCSprite *ping3;//屏3
//    CCSprite *ping4;//屏4
    
//    CCMutableArray<CCSprite*> *_pIndexArray;   //selectindex数组
	CCArray *_pIndexArray;   //selectindex数组
    
	bool isMoveActionRunning;
    int  nPage;
    
public:
    //初始化--------------------------------------------------
	virtual bool init();
    
    //    void onEnter();
    void onExit();
    
    
    //    void show();
    //    void hide();
    //    virtual void menuCloseCallback(CCObject* pSender);
    
	// implement the "static node()" method manually
	CREATE_FUNC(SplashLayer);
    
	void moveActionCallback();
    
    virtual void keyBackClicked();
    virtual void onEntrance();
    
    //触摸相关方法---------------------------------------------
    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
//    virtual void menuCallback(CCObject* pSender);
    
};

#endif /* defined(__xzdd__SplashLayer__) */
