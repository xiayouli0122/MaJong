//
//  SetScene.cpp
//  xzdd
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "SetScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "GameSet.h"
#include "ConstantDef.h"
#include "CommonFunction.h"
#include "IOSCommon.h"
#else 

#include "../Layer/GameSet.h"
#include "../Common/ConstantDef.h"
#include "../Common/CommonFunction.h"

#endif

using namespace cocos2d;

CCScene* SetScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	SetScene *layer = SetScene::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    scene->setTag(ST_MENU);
    
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SetScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    
    if (CommonFunction::isIpad()) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultMenuFrameFile_Ipad);
    }else {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultMenuFrameFile);
    }

    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //加入桌面背景
    bjSprite = new CCSprite();
    if (CommonFunction::isIpad()) {
        bjSprite->initWithFile(CONS_Image_BG_Ipad);
    }
    else{
        bjSprite->initWithFile(CONS_Image_BG);
    }
    bjSprite->setAnchorPoint(ccp(0, 0));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        bjSprite->setAnchorPoint(ccp(0.5f,0.5f));
        bjSprite->setPosition(ccp(winSize.width / 2.0f, winSize.height / 2.0f));
        bjSprite->setScale(2.0f);
    }
#endif
    
    this->addChild(bjSprite,0);
    
    //加入设置层
    GameSet * setLayer = GameSet::create();
    setLayer->initWithGameType(GT_SingleGame);
    this->addChild(setLayer,1);
	setLayer->ShowGameSet(GST_MainMenu);
    

    
	return true;
}
void SetScene::onExit()
{
    bjSprite->release();
    CCLayer::onExit();
}


