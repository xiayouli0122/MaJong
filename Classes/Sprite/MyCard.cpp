//
//  MyCard.cpp
//  xzdd
//
//  Created by  on 12-2-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MyCard.h"

using namespace cocos2d;

//初始化--------------------------------
MyCard::MyCard(void)
{
}
MyCard::~MyCard(void)
{
}

//通过图片名创建card对象
MyCard* MyCard::MyCardWithFrameName(const char *pFrameName)
{
	MyCard* pMyCard = new MyCard();
    pMyCard->initWithSpriteFrameName(pFrameName);
	pMyCard->autorelease();
	return pMyCard;
}

//更换card的图片
void MyCard::setDisplayFrameName(const char *frameName)
{
    Card::setDisplayFrameName(frameName);
    c_state = cardNone;     //设置初始属性
}

//触摸相关方法---------------------------
//被触摸
void MyCard::onTouched()
{
    if(c_state == cardNone)
    {
        onTouchIn();
    }
    else if(c_state == cardSelected)
    {
        onTouchOut();
    }

}
//焦点移入
void MyCard::onTouchIn()
{
    if (c_state == cardNone) {
        c_initPostion = getPosition();
    }
    setPosition(ccp(c_initPostion.x,c_initPostion.y+10));
    c_state = cardSelected;
}
//焦点移出
void MyCard::onTouchOut()
{
    setPosition(c_initPostion);
    c_state = cardNone;
}