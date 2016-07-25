//
//  GameSet.h
//  xzdd
//
//  Created by  on 12-4-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameSet_h
#define xzdd_GameSet_h

#include "cocos2d.h"
#include "SetProgress.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "SelectSprite.h"

#else 

#include "../Sprite/SelectSprite.h"

#endif

using namespace cocos2d;

typedef enum 
{
    GST_MainMenu,
    GST_GameMenu
} GameSetType; 

class GameSet : public cocos2d::CCLayerColor
{
    SetProgress* yyProgress;
	SetProgress* yxProgress;
	SelectSprite* xstsSelectSprite;
    SelectSprite* zddlSelectSprite;
	SelectSprite* sdmsSelectSprite;
	SelectSprite* xzdqSelectSprite;
	SelectSprite* ptxzSelectSprite;
	SelectSprite* cbzSelectSprite;
	SelectSprite* jjySelectSprite;
	SelectSprite* sfqhSelectSprite;
	SelectSprite* zmjdSelectSprite;
    SelectSprite* yxpgSelectSprite;
    GameSetType m_gameSetType;
    GameType    mType;
    CCSprite * kuangSprite;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    virtual void onExit();
    void initWithGameType(GameType type);
	// implement the "static node()" method manually
	CREATE_FUNC(GameSet);
    
    void ShowGameSet(GameSetType gameSetType);
	
    virtual void menuBackCallback(CCObject* pSender);
	virtual void menuSetXstsCallback(CCObject* pSender);
	virtual void menuSetZddlCallback(CCObject* pSender);
	virtual void menuSetSdmsCallback(CCObject* pSender);
	virtual void menuSetXzdqCallback(CCObject* pSender);
	virtual void menuSetPtxzCallback(CCObject* pSender);
	virtual void menuSetCbzCallback(CCObject* pSender);
	virtual void menuSetJjyCallback(CCObject* pSender);
	virtual void menuSetSfqhCallback(CCObject* pSender);
	virtual void menuSetZmjdCallback(CCObject* pSender);
    virtual void menuSetYxpgCallback(CCObject* pSender);
    
};


#endif
