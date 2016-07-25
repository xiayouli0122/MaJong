//
//  LoadingScene.cpp
//  xzdd
//
//  Created by  on 12-4-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "LoadingScene.h"
#include "GameScene.h"
#include "GuanKaScene.h"
#include "MenuScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSCommon.h"
#endif

using namespace cocos2d;

CCScene* LoadingScene::scene(TargetScene target)
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	LoadingScene *layer = LoadingScene::create();
    layer->targetScene = target;
    
	// add layer as a child to scene
	scene->addChild(layer);
    scene->setTag(ST_MENU);
    
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}  
    
    bjSprite = new CCSprite();
    
    static bool bFirstCall = true;
    cocos2d::CCSize size = cocos2d::CCDirector::sharedDirector()->getWinSize();

    if(bFirstCall)
    {
        bFirstCall = false;
        
#if IS_EGAME_LOGO
        bjSprite->initWithFile("Image/Loading/egamelogo.png");
#elif IS_CXWX
        if (IS_NEW_SKIN) {
            bjSprite->initWithFile("Image/bg_new/loading.jpg");
        }
        else
        {
            bjSprite->initWithFile("Image/Loading/cgclogo.png");
        }
#elif IS_NON_EGAME
        bjSprite->initWithFile("Image/bg_new/loading.jpg");
#else
        bjSprite->initWithFile("Image/Loading/egamelogo.png");
#endif
        
        bjSprite->setAnchorPoint(ccp(0.5, 0.5));
		bjSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));

        this->addChild(bjSprite,0);

        if (IS_SPRING)
        {
            schedule( schedule_selector(LoadingScene::ShowAd));  //增加定时器调用
        }
        else
        {
            schedule( schedule_selector(LoadingScene::undateState));  //增加定时器调用
        }
        
        return true;
    }
        
    //加入桌面背景
    //bjSprite = new CCSprite();
    if (CommonFunction::isIpad()) {
        bjSprite->initWithFile(CONS_Image_Loading_Ipad);
    }
    else{
        bjSprite->initWithFile(CONS_Image_Loading);
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        bjSprite->setAnchorPoint(ccp(0.5f,0.5f));
        bjSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
        bjSprite->setScale(2.0f);
    }
#endif

    bjSprite->setAnchorPoint(ccp(0.5, 0.5));
	bjSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));

    this->addChild(bjSprite,0);
    
    schedule( schedule_selector(LoadingScene::undateState));  //增加定时器调用
	
	return true;
}
void LoadingScene::onExit()
{
    bjSprite->release();
    CCLayer::onExit();
}

void LoadingScene::undateState(float dt)
{
    this->unscheduleAllSelectors();
    switch (targetScene) {
        case TargetSceneMainScene:
            CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
            break;
        case TargetSceneGameScene:
            CCDirector::sharedDirector()->replaceScene(GameCScene::create());
            break;
        case TargetSceneGuanKaScene:
            CCDirector::sharedDirector()->replaceScene(GuanKaScene::create());
            break;
            
           
        default:
            break;
    }
}

void LoadingScene::ShowAd(float dt)
{
    this->unscheduleAllSelectors();
    bjSprite->initWithFile("Image/Loading/ad1.jpg");
    bjSprite->setAnchorPoint(ccp(0, 0));
    schedule( schedule_selector(LoadingScene::undateState), 1.5);  //增加定时器调用
}





