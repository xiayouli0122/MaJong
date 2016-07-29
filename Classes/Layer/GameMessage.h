//
//  GameMessage.h
//  xzdd
//
//  Created by  on 12-4-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameMessage_h
#define xzdd_GameMessage_h

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"

#else 

#include "../Common/ConstantDef.h"

#endif

using namespace cocos2d;

//CCLayerColor：一个可以有背景颜色的Layer
//这个GameMessage应该就像是Android中的一个自定义的公用Dialog
class GameMessage : public cocos2d::CCLayerColor
{
	//Dialog的背景层
    CCSprite * bjSprite;
	//确定按钮
    CCMenuItemSprite * pConfirm;
	//取消按钮
    CCMenuItemSprite * pCancel;
    
	//显示的Message内容
    CCLabelTTF* label;
	//根据类型不同，Dialog内容略有变化
    MessageType type;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    virtual void onExit();
	// implement the "static node()" method manually
	CREATE_FUNC(GameMessage);
	
    void SetMessageType(MessageType mType, int nStatus=-1);
	//设置取消按钮是否可见，也就是有的Dialog展示的时候只需要一个确定按钮就可以了
    void setVisibleCancel(bool bVisible);
	//selector callback
    //selector callback
	//确定和取消按钮的点击回调
    virtual void menuCancelCallback(CCObject* pSender);
    virtual void menuConfirmCallback(CCObject* pSender);
    
    /*virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch * touch, CCEvent * event);*/
    
	//定义了一个变量，暂时不知道什么卵用
    int selectedGK;
};


#endif
