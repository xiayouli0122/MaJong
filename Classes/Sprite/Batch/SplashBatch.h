//
//  SplashBatch.h
//  xzdd
//
//  Created by Paddy on 12-12-7.
//
//

#ifndef __xzdd__SplashBatch__
#define __xzdd__SplashBatch__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CommonFunction.h"

#else
#include "../../Common/CommonFunction.h"

#endif

#define PAGE_NUM  3

using namespace cocos2d;

class SplashBatch : public cocos2d::CCLayer
{
    
//protected:
//    CCMutableArray<GuanKaSprite*> *guanKaArray;   //page数组
//	int guankaNum; //page数量

//    CCMutableArray<CCSprite*> *pSpPageArray;   //page数组
	CCArray	*pSpPageArray;   //page数组
    CCMenuItemSprite *pItemEntrance;
    
public:
	//初始化--------------------------------------------------
	virtual bool init();
    virtual void onExit();

	// implement the "static node()" method manually
	CREATE_FUNC(SplashBatch);
    
    //公有方法------------------------------------------------
    bool onTouchSelected(CCPoint touchPoint);
    
//    void onTouchMove(CCPoint toucPoint);
//
    //触摸相关方法---------------------------------------------

    
//
	virtual void menuCallback(CCObject* pSender);
};

#endif /* defined(__xzdd__SplashBatch__) */
