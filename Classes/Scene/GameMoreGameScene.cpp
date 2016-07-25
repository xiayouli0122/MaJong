//
//  GamMoreGameScene.cpp
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameMoreGameScene.h"
#include "MenuScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "CommonFunction.h"
#include "IOSCommon.h"
#else 

#include "../Common/CommonFunction.h"

#endif

using namespace cocos2d;

// on "init" you need to initialize your instance
bool GameMoreGameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}
    this->setTag(ST_MENU);
    
    CCSpriteFrame * spriteFrame;
    
    if (CommonFunction::isIpad()) {
        spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_DefaultGkFrameFile_Ipad);
        if(spriteFrame == NULL){
            //加入图片缓冲
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultGkFrameFile_Ipad);
        }
    }else {
        spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_DefaultGkFrameFile);
        if(spriteFrame == NULL){
            //加入图片缓冲
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultGkFrameFile);
        }
    }
    
    
	GameMGLayer * cjLayer = GameMGLayer::create();  
	this->addChild(cjLayer);
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	/////////////////////////////
	//加入返回按钮
	CCSprite* retSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_return);
    
    CCMenuItemSprite *pItem0 = CCMenuItemSprite::create(retSprite,NULL,NULL,this, 
                                                                      menu_selector(GameMoreGameScene::menuBackCallback));
	pItem0->setPosition( ccp(winSize.width*0.875, winSize.height*0.18) );
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        pItem0->setScale(2.0f);
    }
#endif
    
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pItem0, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);
    
	return true;
}


void GameMoreGameScene::menuBackCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}


