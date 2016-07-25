//
//  PersonSetScene.cpp
//  xzdd
//
//  Created by  on 12-5-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "PersonSetScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "PersonSet.h"
#include "ConstantDef.h"
#include "CommonFunction.h"

#else 

#include "../Layer/PersonSet.h"
#include "../Common/ConstantDef.h"
#include "../Common/CommonFunction.h"

#endif

using namespace cocos2d;

// on "init" you need to initialize your instance
bool PersonSetScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    this->setTag(ST_MENU);
    
 
    //加入桌面背景
    bjSprite = new CCSprite();
    if (CommonFunction::isIpad()) {
        bjSprite->initWithFile(CONS_Image_BG_PersonSet_Ipad);
    }
    else{
        bjSprite->initWithFile(CONS_Image_BG_PersonSet);
    }
    bjSprite->setAnchorPoint(ccp(0, 0));
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float ratioX = 1.0f;
    float ratioY = 1.0f;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bjSprite->setAnchorPoint(ccp(0.5f, 0.5f));
    ratioX = size.width / bjSprite->getContentSize().width;
    ratioY = size.height / bjSprite->getContentSize().height;
    bjSprite->setScaleX(ratioX);
    bjSprite->setScaleY(ratioY);
    bjSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
    
#endif
    
    
    
    this->addChild(bjSprite,1);
    
    //加入游戏桌面
    PersonSet * setLayer = PersonSet::create();
    this->addChild(setLayer,2,1);
    
	return true;
}

void PersonSetScene::onExit()
{
    bjSprite->release();
    CCScene::onExit();
}
void PersonSetScene::onEnter()
{
    CCScene::onEnter();
}