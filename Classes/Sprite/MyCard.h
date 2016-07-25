//
//  MyCard.h
//  xzdd
//
//  Created by  on 12-2-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_MyCard_h
#define xzdd_MyCard_h

#include "cocos2d.h"
#include "Card.h"
using namespace cocos2d;

//手牌状态定义，触摸用
typedef enum 
{
    cardNone,       //初始状态
	cardSelected    //被选择状态
} CardState; 

//sprite对象，玩家手牌，可接受触摸
class MyCard : public Card
{

    CCPoint         c_initPostion;  //初始位置
    
public:
    //初始化--------------------------------
    MyCard(void);
	virtual ~MyCard(void);
    
    BYTE cardIndex;   //牌的索引
    CardState		c_state;        //状态
    
    //公有方法------------------------------
    //通过图片名创建card对象
    static MyCard* MyCardWithFrameName(const char *pFrameName);

    //更换card的图片
    virtual void setDisplayFrameName(const char *frameName);

    
    //触摸相关方法---------------------------
    virtual void onTouched();   //被触摸
    virtual void onTouchIn();   //焦点移入
    virtual void onTouchOut();  //焦点移出
    
};

#endif
