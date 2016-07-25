//
//  Card.cpp
//  xzdd
//
//  Created by  on 12-3-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "Card.h"

using namespace cocos2d;

//初始化--------------------------------
Card::Card(void)
{
}
Card::~Card(void)
{
}
bool Card::init()
{
    if(!CCSprite::init())
    {
        return false;
    }
    setVisible(false);    //初始化设置对象不可见
    return true;
}

//通过图片名创建card对象
Card* Card::cardWithFrameName(const char *pFrameName)
{
	Card* pCard = new Card();
	pCard->init();
    pCard->initWithSpriteFrameName(pFrameName);
	pCard->autorelease();
    
	return pCard;
}


void Card::setDisplayFrameName(const char *frameName)
{
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
    this->setDisplayFrame(frame);
    this->setVisible(true);
}