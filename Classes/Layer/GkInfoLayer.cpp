//
//  GuanKaLayer.cpp
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GkInfoLayer.h"

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
bool GkInfoLayer::init()
{
	//super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    this->setTouchEnabled(true);
	gkNum = 0;
    enableMove = false;

    //取得所有关卡
	GUAN_KA * gk = MyTinyXmlParser::GetGuanKa();
	GUAN_KA * gkOriginal = gk;
    
    while (gk->isUsed) {
        gkNum++;
		gk++;//gk到了最后
    }
    
    infoBatch = GkInfoBatch::create();
	infoBatch->SetAllGk(gkOriginal, gkNum);
	this->addChild(infoBatch, 1);
    
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    y_max = infoBatch->totalHeight - winSize.height*0.69;
    if (CommonFunction::isIpad()) {
        y_max = infoBatch->totalHeight - winSize.height*0.58;
    }
    
	CCSprite *pText = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Info_Text);//关卡说明文字图片    
	pText->setPosition( ccp(winSize.width*0.5, winSize.height*0.925) ); 
    if (CommonFunction::isIpad()) {
        pText->setPosition( ccp(winSize.width*0.4645, winSize.height*0.818) );
    }
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
	this->addChild(kuang, 2,2);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        pText->setScale(2.0f);
        kuang->setScale(2.0f);
    }
#endif
    
    schedule( schedule_selector(GkInfoLayer::undateState));  //增加定时器调用
    
	return true;
}

void GkInfoLayer::onExit()
{
    CCLayer::onExit();
}


//触摸相关方法---------------------------------------------
void GkInfoLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GkInfoLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
	y_begin = touchPoint.y;
	y_batch_location_begin = infoBatch->getPosition().y;
    
    enableMove = false;
    
	return true;
}

void GkInfoLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
	y_end = touchPoint.y;
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	CCActionInterval*  actionTo;
	if(y_batch_location_begin + y_end - y_begin < 0){//拉到最上面了
		actionTo = CCMoveTo::create(0.5, CCPointMake(0, 0));
        infoBatch->runAction(actionTo);	
	}else if(y_batch_location_begin + y_end - y_begin > y_max){//拉到最下面了
		actionTo = CCMoveTo::create(0.5, CCPointMake(0, y_max));
        infoBatch->runAction(actionTo);	
	}else{//中间

        enableMove = true;
	}	
    
}

void GkInfoLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
    
	infoBatch->setPosition(ccp(0,y_batch_location_begin + touchPoint.y - y_begin));	
}

//定时器，定时调用
void GkInfoLayer::undateState(float dt)
{ 
    if(!enableMove)
    {
        moveSpeed = infoBatch->getPosition().y - y_last;
        y_last = infoBatch->getPosition().y;        
    }
    else
    {
        moveSpeed = moveSpeed * 9 / 10;
        if (moveSpeed > 2 || moveSpeed < -2) {
            infoBatch->setPosition(ccpAdd(infoBatch->getPosition(), ccp(0,moveSpeed)));
            if (infoBatch->getPosition().y < 0 ) {
                CCActionInterval*  actionTo = CCMoveTo::create(0.5, CCPointMake(0, 0));
                infoBatch->runAction(actionTo);
                enableMove = false;
            }
            else if(infoBatch->getPosition().y > y_max)
            {
                CCActionInterval*  actionTo = CCMoveTo::create(0.5, CCPointMake(0, y_max));
                infoBatch->runAction(actionTo);
                enableMove = false;
            }
        }
    }
}

