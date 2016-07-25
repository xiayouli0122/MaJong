//
//  GameScene.cpp
//  xzdd
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "GameDesk.h"
#include "CommonFunction.h"
#include "IOSCommon.h"
#else 

#include "../Layer/GameDesk.h"
#include "../Common/CommonFunction.h"

#endif
using namespace cocos2d;
using namespace CocosDenshion;

// on "init" you need to initialize your instance
bool GameCScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    this->setTag(ST_GAME);
    
    //加入桌面背景
    bjSprite = new CCSprite();
    if(CommonFunction::isIpad()){
        bjSprite->initWithFile(CONS_Image_BG_Ipad);
    }
    else{
        bjSprite->initWithFile(CONS_Image_BG);
    }
	cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    bjSprite->setAnchorPoint(ccp(0.5, 0.5));
    bjSprite->setPosition( ccp(winSize.width / 2, winSize.height /2));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        
        bjSprite->setAnchorPoint(ccp(0.5f,0.5f));
        bjSprite->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f));
        bjSprite->setScale(2.0f);
    }
#endif
    
    this->addChild(bjSprite,1);
    
#if (IS_NEW_SKIN && IS_LOCAL)
    int nGK = GetIntegerToXML(UD_CurrentGuanKa,1);
    char path[128];
    sprintf(path, CONS_IMG_BG_GK_NAME, nGK);
    bgGkName = new CCSprite();
    bgGkName->initWithFile(path);
    
    bgGkName->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.425f));
    this->addChild(bgGkName,1);
#endif
    
    //加入游戏桌面
    GameDesk * deskLayer = GameDesk::create();
    this->addChild(deskLayer,2,1);
    
	return true;
}

void GameCScene::onExit()
{
    bjSprite->release();
#if (IS_NEW_SKIN && IS_LOCAL)
    bgGkName->release();
#endif
    CCScene::onExit();
}
void GameCScene::onEnter()
{
    CCScene::onEnter();
}

void GameCScene::onSystemResume()
{
    GameDesk * deskLayer = (GameDesk *)getChildByTag(1);
    deskLayer->onSystemResume();
}