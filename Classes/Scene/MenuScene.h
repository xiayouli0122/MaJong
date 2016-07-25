//
//  MenuScene.h
//  xzdd
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_MenuScene_h
#define xzdd_MenuScene_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
//#include "LayerNetGameMessage.h"
#include "SplashLayer.h"
#include "GameMessage.h"
#else 
//#include "../Layer/Net/LayerNetGameMessage.h"
#include "../Layer/SplashLayer.h"
#include "../Layer/GameMessage.h"
#endif


class MenuScene : public cocos2d::CCLayer
{
    cocos2d::CCSprite * bjSprite;
	GameMessage *   gameMessage;
    SplashLayer * splashLayer;
//    LayerNetGameMessage *gameMessage;
//    bool bIsInSplash;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
    virtual void onExit();
	static cocos2d::CCScene* scene();
	
    virtual void keyBackClicked();
    virtual void onConfirm(NetMessageType mType);
    
	// a selector callback
    virtual void menuSingleSceneCallback(CCObject* pSender);
    virtual void menuNetSceneCallback(CCObject* pSender);
    virtual void menuSetSceneCallback(CCObject* pSender);
    virtual void menuHelpSceneCallback(CCObject* pSender);
    virtual void menuPersonSetCallback(CCObject* pSender);
    virtual void menuMoreGameCallback(CCObject* pSender);

	int			 CurrentTimeNow();
    
    virtual void menuSpringCallback(CCObject* pSender);
    virtual void menuCommunityCallback(CCObject* pSender);
    virtual void menuFriendsCallback(CCObject* pSender);
	virtual void menuStoreCallback( CCObject* pSender );
    
//    virtual void menuSplashEntranceCallback(CCObject* pSender);
    
    virtual void menuQuickStartCallback(CCObject* pSender);
    
	// implement the "static node()" method manually
	CREATE_FUNC(MenuScene);
    
//    void TimerLogoEnd(float t);
};


#endif
