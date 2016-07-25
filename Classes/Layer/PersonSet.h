//
//  PersonSet.h
//  xzdd
//
//  Created by  on 12-5-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_PersonSet_h
#define xzdd_PersonSet_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"

#else 

#include "../Common/ConstantDef.h"

#endif

using namespace cocos2d;

class PersonSet: public CCLayer,public CCTextFieldDelegate
{
    PLAYER              user;
    CCSprite *          showImage;
    BYTE                userId;
    BYTE                oldUserId;   //记录刚打开页面时的userId
    char  *             nOldName;    //记录刚打开页面时的用户名
    
    CCLabelTTF *        pLabelName;
    int                 m_nCharLimit;       // the textfield max char limit
    bool                nameInputSelected;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	// implement the "static node()" method manually
	CREATE_FUNC(PersonSet);
    
    virtual void menuLeftCallback(CCObject* pSender);
    virtual void menuRightCallback(CCObject* pSender);
    virtual void menuReturnCallback(CCObject* pSender);
    virtual void menuUpdateCallback(CCObject* pSender);

private:
    void setShow();
    
};



#endif
