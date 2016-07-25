//
//  HelpScene.cpp
//  xzdd
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "HelpScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSCommon.h"
#endif

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelpScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	HelpScene *layer = HelpScene::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    scene->setTag(ST_MENU);
    
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelpScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();

	this->setKeypadEnabled(true);
    
	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();    
    //加入背景
    bjSprite = new CCSprite();
    if(CommonFunction::isIpad()){
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
        bjSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
        bjSprite->setScale(2.0f);
    }
#endif
    this->addChild(bjSprite,1);
    
	/////////////////////////////
	// 加入菜单    
    CCMenuItemImage *pItem1;
    
    if (CommonFunction::isIpad()) {
        pItem1 = CCMenuItemImage::create(CONS_PATH_PNG_MENU_CONFIRM_IPAD, CONS_PATH_PNG_MENU_CONFIRM_IPAD,this,menu_selector(HelpScene::menuBackCallback));
    }else {
        pItem1 = CCMenuItemImage::create(CONS_PATH_PNG_MENU_CONFIRM, CONS_PATH_PNG_MENU_CONFIRM,this,
                                                      menu_selector(HelpScene::menuBackCallback));
    }
	pItem1->setPosition( ccp(size.width*0.9,size.height*0.1) ); 
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        pItem1->setScale(2.0f);
    }
#endif
    
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pItem1, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 2,2);
    
    
	// 加入一个 label
    helpLayer = GameHelp::create();
	this->addChild(helpLayer, 1,1);
    
    int height = CommonFunction::GetValueByDev(1200);
    
    if (ISANDROID) {
        height = CommonFunction::GetValueByDev(1100);
    }
    
    y_min = 0; //size.height - height * 0.5;
    y_max = height - size.height;// height* 0.5;
    
    this->setTouchEnabled(true);
    enableMove = false;
    
    schedule( schedule_selector(HelpScene::undateState));  //增加定时器调用

	return true;
}
void HelpScene::onExit()
{
    bjSprite->release();
    CCLayer::onExit();
}
void HelpScene::menuBackCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}

//触摸相关方法---------------------------------------------
void HelpScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool HelpScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
	y_begin = touchPoint.y;
	y_batch_location_begin = helpLayer->getPosition().y;
    enableMove = false;
	return true;
}

void HelpScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
	y_end = touchPoint.y;
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	CCActionInterval*  actionTo;
	if(y_batch_location_begin + y_end - y_begin < y_min){//拉到最上面了
		actionTo = CCMoveTo::create(0, CCPointMake(0, y_min));
        helpLayer->runAction(actionTo);	
	}else if(y_batch_location_begin + y_end - y_begin > y_max){//拉到最下面了
		actionTo = CCMoveTo::create(0, CCPointMake(0, y_max));
        helpLayer->runAction(actionTo);	
	}else{//中间
        enableMove = true;
	}
}

void HelpScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
    
	helpLayer->setPosition(ccp(0,y_batch_location_begin + touchPoint.y - y_begin));	
}

//定时器，定时调用
void HelpScene::undateState(float dt)
{ 
    if(!enableMove)
    {
        moveSpeed = helpLayer->getPosition().y - y_last;
        y_last = helpLayer->getPosition().y;        
    }
    else
    {
        moveSpeed = moveSpeed * 9 / 10;
        if (moveSpeed > 2 || moveSpeed < -2) {
            helpLayer->setPosition(ccpAdd(helpLayer->getPosition(), ccp(0,moveSpeed)));
            if (helpLayer->getPosition().y < y_min ) {
                CCActionInterval*  actionTo = CCMoveTo::create(0, CCPointMake(0, y_min));
                helpLayer->runAction(actionTo);
                enableMove = false;
            }
            else if(helpLayer->getPosition().y > y_max)
            {
                CCActionInterval*  actionTo = CCMoveTo::create(0, CCPointMake(0, y_max));
                helpLayer->runAction(actionTo);
                enableMove = false;
            }
        }
    }
}

void HelpScene::keyBackClicked(){

	CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}
