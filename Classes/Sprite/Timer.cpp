//
//  Timer.cpp
//  xzdd
//
//  Created by  on 12-3-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Timer.h"

using namespace cocos2d;

//初始化--------------------------------
Timer::Timer(void)
{
}
Timer::~Timer(void)
{
}
bool Timer::init()
{
    if(!CCSprite::init())
    {
        return false;
    }
    //添加时间数字Label对象
    if (CommonFunction::isIpad()) {
//        numberLabel = CCLabelBMFont::create("0", CONS_PATH_FONT_NUM_IPAD);
    }else{
//        numberLabel = CCLabelBMFont::create("0", CONS_PATH_FONT_NUM);
		numberLabel = CCLabelBMFont::create("0", CONS_PATH_FONT_NUM);
    }

    addChild(numberLabel);
//    setVisible(false);
	setVisible(false);
    
    //添加箭头
//     sArrow = CCSprite::create(CONS_TIMER_SImage);
//     xArrow = CCSprite::create(CONS_TIMER_XImage);
//     zArrow = CCSprite::create(CONS_TIMER_ZImage);
//     yArrow = CCSprite::create(CONS_TIMER_YImage);
//     
//     sArrow->setVisible(false);
//     xArrow->setVisible(false);
//     zArrow->setVisible(false);
//     yArrow->setVisible(false);
	sArrow = CCSprite::createWithSpriteFrameName(CONS_TIMER_SImage);
	xArrow = CCSprite::createWithSpriteFrameName(CONS_TIMER_XImage);
	zArrow = CCSprite::createWithSpriteFrameName(CONS_TIMER_ZImage);
	yArrow = CCSprite::createWithSpriteFrameName(CONS_TIMER_YImage);

	sArrow->setVisible(false);
	xArrow->setVisible(false);
	zArrow->setVisible(false);
	yArrow->setVisible(false);
    
    addChild(sArrow);
    addChild(xArrow);
    addChild(zArrow);
    addChild(yArrow);
    
    return true;
}

Timer* Timer::timerWithFrameName(const char *pFrameName)
{
	Timer* pTimer = new Timer();
	pTimer->init();
    //pTimer->initWithSpriteFrameName(pFrameName);
    pTimer->initWithSpriteFrameName(pFrameName);
	pTimer->autorelease();
    
    //设置位置 屏幕中心
    pTimer->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5,
                            CCDirector::sharedDirector()->getWinSize().height*0.5) );
    //数字位置设置为背景图片中心
    pTimer->numberLabel->setPosition(ccp(pTimer->getContentSize().width*0.5,pTimer->getContentSize().height*0.5));
      
    CCSize pSize = pTimer->getContentSize();
    pTimer->sArrow->setPosition(ccp(pSize.width*0.5, pSize.height*1.3));
    pTimer->xArrow->setPosition(ccp(pSize.width*0.5, pSize.height*(-0.3)));
    pTimer->zArrow->setPosition(ccp(pSize.width*(-0.3), pSize.height*0.5));
    pTimer->yArrow->setPosition(ccp(pSize.width*1.3, pSize.height*0.5));
    
	return pTimer;
}

void Timer::SetTime(unsigned short time,BYTE chair)
{
    SetTime(time);
    SetChair(chair);
}
void Timer::SetTime(unsigned short time)
{
    countTime = time;
    char timeStr[20];
    sprintf(timeStr,"%d",time);
    //CCLOG("-----timer number=%s-----------", timeStr);
    numberLabel->setString(timeStr);
}
void Timer::SetChair(BYTE chair)
{
    sArrow->setVisible(false);
    xArrow->setVisible(false);
    zArrow->setVisible(false);
    yArrow->setVisible(false);
    switch (chair) {
        case 0:
            xArrow->setVisible(true);
            break;
        case 1:
            zArrow->setVisible(true);
            break;
        case 2:
            sArrow->setVisible(true);
            break;
        case 3:
            yArrow->setVisible(true);
            break;
        default:
            break;
    }
}

