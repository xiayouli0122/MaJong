//
//  GameMessage.h
//  xzdd
//
//  Created by  on 12-4-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameMessage_h
#define xzdd_GameMessage_h

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"

#else 

#include "../Common/ConstantDef.h"

#endif

using namespace cocos2d;

class GameMessage : public cocos2d::CCLayerColor
{
    CCSprite * bjSprite;
    CCMenuItemSprite * pConfirm;
    CCMenuItemSprite * pCancel;
    
    CCLabelTTF* label;
    MessageType type;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    virtual void onExit();
	// implement the "static node()" method manually
	CREATE_FUNC(GameMessage);
	
    void SetMessageType(MessageType mType, int nStatus=-1);
    void setVisibleCancel(bool bVisible);
	//selector callback
    //selector callback
    virtual void menuCancelCallback(CCObject* pSender);
    virtual void menuConfirmCallback(CCObject* pSender);
    
    //virtual void registerWithTouchDispatcher();
    
    int selectedGK;
};


#endif
