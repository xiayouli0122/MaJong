//
//  GuanKaLayer.cpp
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameCjLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "MyTinyXmlParser.h"
#include "GuanKaScene.h"
#include "MenuScene.h"
#include "IOSCommon.h"
#else 

#include "../Common/MyTinyXmlParser.h"
#include "../Scene/GuanKaScene.h"
#include "../Scene/MenuScene.h"

#endif

using namespace cocos2d;

//初始化--------------------------------------------------
bool GameCjLayer::init()
{
	//super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    this->setTouchEnabled(true);
	cjNum = 0;
    enableMove = false;
    
	GameCjSprite* cjSprite = new GameCjSprite();//为了算出每个成就的高度
    cjSprite->initWithSpriteFrameName(CONS_Image_Cj_Light);
	cjSprite->autorelease();
	cjSize = cjSprite->getContentSize();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        cjSprite->setScale(2.0f);
        cjSize.width *= 2;
        cjSize.height *= 2;
    }
#endif

    
    //加入所有成就
	CHENGJIU * cj = MyTinyXmlParser::GetChengJiu();
	CHENGJIU * cjOriginal = cj;
    
    while (cj->isUsed) {
        cjNum++;
		cj++;//cj到了最后
    }
    
    cjBatch = GameCjBatch::create();
	cjBatch->SetAllCj(cjOriginal, cjNum, cjSize);
	this->addChild(cjBatch, 1);
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    y_max = cjNum*(cjSize.height) - winSize.height*0.69;
    if (CommonFunction::isIpad()) {
        y_max = cjNum*(cjSize.height) - winSize.height*0.58;
    }
    
	CCSprite *pText = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Cj_Text);//成就文字图片    
	pText->setPosition( ccp(winSize.width*0.5, winSize.height*0.925) ); 
    if (CommonFunction::isIpad()) {
        pText->setPosition( ccp(winSize.width*0.4645, winSize.height*0.818) );
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        pText->setScale(2.0f);
    }
#endif
	pText->setVisible(true);
	this->addChild(pText, 3);


    
    
    CCSprite *kuang;// = CCSprite::create(CONS_Image_GK_Kuang);//关卡屏边框
	if (CommonFunction::isIpad()) {
        kuang = CCSprite::create(CONS_Image_GK_Kuang_Ipad);//关卡屏边框
    }
    else{
        kuang = CCSprite::create(CONS_Image_GK_Kuang);//关卡屏边框
    }
    kuang->setPosition( ccp(winSize.width / 2, winSize.height /2) );
	kuang->setVisible(true);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        kuang->setScale(2.0f);
    }
#endif
	this->addChild(kuang, 2,2);
    
    schedule( schedule_selector(GameCjLayer::undateState));  //增加定时器调用
    
	return true;
}

void GameCjLayer::onExit()
{
    CCLayer::onExit();
}


//触摸相关方法---------------------------------------------
void GameCjLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameCjLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView();
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
	y_begin = touchPoint.y;
	y_batch_location_begin = cjBatch->getPosition().y;
    enableMove = false;
	return true;
}

void GameCjLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
	y_end = touchPoint.y;
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	CCActionInterval*  actionTo;
	if(y_batch_location_begin + y_end - y_begin < 0){//拉到最上面了
		actionTo = CCMoveTo::create(0.5, CCPointMake(0, 0));
        cjBatch->runAction(actionTo);	
	}else if(y_batch_location_begin + y_end - y_begin > y_max){//拉到最下面了
		actionTo = CCMoveTo::create(0.5, CCPointMake(0, y_max));
        cjBatch->runAction(actionTo);	
	}else{//中间
		//actionTo = CCMoveTo::create(0.5, CCPointMake(0, y_batch_location_begin + y_end - y_begin));
        enableMove = true;
	}
}

void GameCjLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
    
	cjBatch->setPosition(ccp(0,y_batch_location_begin + touchPoint.y - y_begin));	
}

//定时器，定时调用
void GameCjLayer::undateState(float dt)
{ 
    if(!enableMove)
    {
        moveSpeed = cjBatch->getPosition().y - y_last;
        y_last = cjBatch->getPosition().y;        
    }
    else
    {
        moveSpeed = moveSpeed * 9 / 10;
        if (moveSpeed > 2 || moveSpeed < -2) {
            cjBatch->setPosition(ccpAdd(cjBatch->getPosition(), ccp(0,moveSpeed)));
            if (cjBatch->getPosition().y < 0 ) {
                CCActionInterval*  actionTo = CCMoveTo::create(0.5, CCPointMake(0, 0));
                cjBatch->runAction(actionTo);
                enableMove = false;
            }
            else if(cjBatch->getPosition().y > y_max)
            {
                CCActionInterval*  actionTo = CCMoveTo::create(0.5, CCPointMake(0, y_max));
                cjBatch->runAction(actionTo);
                enableMove = false;
            }
        }
    }
}















