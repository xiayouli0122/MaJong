//
//  OutCard.cpp
//  xzdd
//
//  Created by  on 12-3-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "OutCard.h"

using namespace cocos2d;

//初始化--------------------------------
OutCard::OutCard(void)
{
}
OutCard::~OutCard(void)
{
}
bool OutCard::init()
{
    if(!CCSprite::init())
    {
        return false;
    }
    //添加背景
    bjSprite = CCSprite::createWithSpriteFrameName(CONS_DefaultMjOutBJImage);
    addChild(bjSprite,-1);
    setVisible(false);
    return true;
}

//通过图片名创建card对象
OutCard* OutCard::outCardWithFrameName(const char *pFrameName)
{
	OutCard* pOutCard = new OutCard();
	pOutCard->init();
    pOutCard->initWithSpriteFrameName(pFrameName);
    //设置背景位置
    pOutCard->bjSprite->setPosition(ccp(pOutCard->getContentSize().width*0.5,pOutCard->getContentSize().height*0.5));
	pOutCard->autorelease();
	return pOutCard;
}