//
//  ActionBatch.h
//  xzdd
//
//  Created by  on 12-3-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_ActionBatch_h
#define xzdd_ActionBatch_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"
#include "MjDef.h"
#include "CommonFunction.h"

#else 

#include "../../Common/ConstantDef.h"
#include "../../GameCore/MjDef.h"
#include "../../Common/CommonFunction.h"

#endif


using namespace cocos2d;

//Acion菜单缓存
class ActionBatch : public cocos2d::CCNode
{

    CCMenuItemSprite *pItemx;
    CCMenuItemSprite *pItemp;
    CCMenuItemSprite *pItemg;
    CCMenuItemSprite *pItemh;
    
    CCMenuItemSprite *pItemdqwan;
    CCMenuItemSprite *pItemdqtiao;
    CCMenuItemSprite *pItemdqtong;
    
    CCSprite        *markDingQue;
    bool isMoAction;
    bool m_bPause;

protected:
    
    
public:
	//初始化--------------------------------------------------
	virtual bool init();
	// implement the "static node()" method manually
	CREATE_FUNC(ActionBatch);
    
    void show(bool showP, bool showAG, bool showG, bool showH, bool isMo);
    void showDingQue();
    
    void onPause();
    void onResume();
    
private:
    void showType(ActionMenuType type);
    bool isShowBeforePause;
    
    //Action菜单
    void ActionX(CCObject* pSender);
    void ActionP(CCObject* pSender);
    void ActionG(CCObject* pSender);
    void ActionAG(CCObject* pSender);
    void ActionH(CCObject* pSender);
    
    void ActionDingQueWan(CCObject* pSender);
    void ActionDingQueTiao(CCObject* pSender);
    void ActionDingQueTong(CCObject* pSender);
    
    void ActionDingQue(PAI_TYPE type);
};



#endif
