//
//  SetProgress.h
//  xzdd
//
//  Created by  on 12-4-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_SetProgress_h
#define xzdd_SetProgress_h

#include "cocos2d.h"
using namespace cocos2d;

//桌面状态定义
typedef enum 
{
    PT_None,
    PT_Music,
    PT_Effect
} ProgressType; 

class SetProgress : public CCLayer
{
    CCSprite * bjSprite;
    CCProgressTimer *progressTimer;
    CCSprite * buttonSprite;
    ProgressType mType;
    int value;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	// implement the "static node()" method manually
	CREATE_FUNC(SetProgress);
    
    void SetProgressType(ProgressType type);
    void SetProgressValue(int value);
    void SetProgressShow(int value);
	
    //触摸相关方法---------------------------------------------
    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
};


#endif
