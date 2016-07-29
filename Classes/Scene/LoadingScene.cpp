//
//  LoadingScene.cpp
//  xzdd
//  Loading...界面
//  Created by  on 12-4-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "LoadingScene.h"

//这里我们看到引入了菜单场景 关卡场景 和 游戏主场景
//主要是会根据不同的情况，加载完毕后跳转到不同的界面
//正常，加载进度完毕之后，直接进入到菜单界面（MenuScene）
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

	//创建一个空的精灵对象
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
		CCLOG("IS_NON_EGAME");
        bjSprite->initWithFile("Image/bg_new/loading.jpg");
#else
        bjSprite->initWithFile("Image/Loading/egamelogo.png");
#endif
        
        bjSprite->setAnchorPoint(ccp(0.5, 0.5));
		bjSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));

        this->addChild(bjSprite,0);

        if (IS_SPRING)
        {
			//春节的时候显示一下广告
            schedule( schedule_selector(LoadingScene::ShowAd));  //增加定时器调用
        }
        else
        {
			//否则。。。
            schedule( schedule_selector(LoadingScene::updateState));  //增加定时器调用
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
    
	//这里没太看明白，调用updateState的时候为什么没有参数，updateState方法是有参数的
    schedule( schedule_selector(LoadingScene::updateState));  //增加定时器调用
	
	return true;
}
void LoadingScene::onExit()
{
    bjSprite->release();
    CCLayer::onExit();
}

void LoadingScene::updateState(float dt)
{
    this->unscheduleAllSelectors();
    switch (targetScene) {
        case TargetSceneMainScene:
			//根据AppDeletgate中初始化的，启动直接进入菜单界面
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
	CCLOG("showAd...");
    this->unscheduleAllSelectors();
    bjSprite->initWithFile("Image/Loading/ad1.jpg");
    bjSprite->setAnchorPoint(ccp(0, 0));
    schedule( schedule_selector(LoadingScene::updateState), 1.5);  //增加定时器调用
}





