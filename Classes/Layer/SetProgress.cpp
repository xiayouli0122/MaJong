//
//  SetProgress.cpp
//  xzdd
//
//  Created by  on 12-4-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "SetProgress.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "CommonFunction.h"
#include "IOSCommon.h"
#else 

#include "../Common/CommonFunction.h"

#endif

using namespace cocos2d;

bool SetProgress::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    this->setTouchEnabled(true);
    
    //加入图片缓冲
    if(CommonFunction::isIpad()){
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultMenuFrameFile_Ipad); 
    }else {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultMenuFrameFile); 
    }
    
    //加入背景
    bjSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Progress_bg);
    this->addChild(bjSprite,0,0);
    
    //加入progress
    if (CommonFunction::isIpad()) {
//        progressTimer = CCProgressTimer::progressWithFile(CONS_Image_Set_Progress_Ipad);
    }else {
        progressTimer = CCProgressTimer::create(CCSprite::create(CONS_Image_Set_Progress));
    }
	
	progressTimer->setType( kCCProgressTimerTypeBar );
	addChild(progressTimer,0,1);
    
    //加入progress 按钮
    buttonSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Progress_button);
    this->addChild(buttonSprite,0,2);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        bjSprite->setScale(2.0f);
        progressTimer->setScale(2.0f);
        buttonSprite->setScale(2.0f);
    }
#endif

    return true;
}

void SetProgress::SetProgressType(ProgressType type)
{
    mType = type;
    CCSize size = bjSprite->boundingBox().size;
    int value = 0;
    switch (mType) {
        case PT_Music:
            value = GetIntegerToXML(UD_Set_Music,100);
            //SOUND->setBackgroundMusicVolume(value*0.01);
            break;
        case PT_Effect:
            value = GetIntegerToXML(UD_Set_Effect,100);
            //SOUND->setEffectsVolume(value*0.01);
            break;
        default:
            break;
    }
    progressTimer->setPercentage(value);
    buttonSprite->setPosition(ccp((value-50)*size.width*0.01,0));
}

void SetProgress::SetProgressValue(int value)
{
    
    switch (mType) {
        case PT_Music:
            SetIntegerToXML(UD_Set_Music,value);
            SOUND->setBackgroundMusicVolume(value*0.01);
            break;
        case PT_Effect:
            SetIntegerToXML(UD_Set_Effect,value);
            SOUND->setEffectsVolume(value*0.01);
            break;
        default:
            break;
    }
}
void SetProgress::SetProgressShow(int value)
{
    CCSize size = bjSprite->boundingBox().size;
    progressTimer->setPercentage(value);
    buttonSprite->setPosition(ccp((value-50)*size.width*0.01,0));
    SetProgressValue(value);
}

//#pragma mark -----------------------触摸相关方法----------------------
void SetProgress::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool SetProgress::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
    CCSize s = buttonSprite->boundingBox().size;
    if (CCRectMake(getPosition().x + buttonSprite->getPosition().x - s.width*0.5,
                                               getPosition().y - s.height*0.5,
                                               s.width, s.height).containsPoint(touchPoint)) {
        return true;
    }
    return false;
}

void SetProgress::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    SetProgressValue(value);
}

void SetProgress::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{

}

void SetProgress::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );

    CCSize allSize = bjSprite->boundingBox().size;
    float x = touchPoint.x;
    float minX = this->getPosition().x - allSize.width*0.5;
    float maxX = this->getPosition().x + allSize.width*0.5;
    if (x <minX) {
        x = minX;
    }
    if (x > maxX) {
        x = maxX;
    }
    
    //if (touchPoint.x > minX && touchPoint.x <maxX) {
        //buttonSprite->setPosition(ccp(touchPoint.x-this->getPosition().x,buttonSprite->getPosition().y));
        value = (x - minX)/allSize.width * 100;
        progressTimer->setPercentage(value);
        buttonSprite->setPosition(ccp((value-50)*allSize.width*0.01,0));

    //}
}
