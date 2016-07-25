//
//  ScrollWordAndImage.cpp
//  xzdd
//
//  Created by  on 12-7-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ScrollWordAndImage.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "ConstantDef.h"
#else 
#include "../Common/ConstantDef.h"
#endif

using namespace cocos2d;

//初始化--------------------------------------------------
bool ScrollWordAndImage::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    image = SpriteWordAndImage::Create((char*)"", (char*)"Verdana", CommonFunction::GetValueByDev(10),120,CT_White);
	addChild(image);
    
    return true;
}

void ScrollWordAndImage::visit(void)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    glEnable(GL_SCISSOR_TEST);
    float floatScale = CC_CONTENT_SCALE_FACTOR();
//    CCEGLView::sharedOpenGLView().setScissorInPoints(getPosition().x*floatScale,(getPosition().y+size.height-height)*floatScale,width*floatScale,height*floatScale);
    CCLayer::visit();
    glDisable(GL_SCISSOR_TEST);
}

void ScrollWordAndImage::SetString(char *label)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    image->stopAllActions();
    image->setPosition(ccp(0,size.height));
    image->setString(label);
    CCAction * action = CCDelayTime::create(1.5);
    if (image->countHeight>height) {
        action = CCMoveBy::create(1.5, CCPointMake(0,image->countHeight-height));
    }
    image->runAction(CCSequence::create(CCDelayTime::create(0.2),
                                         action,
                                         CCDelayTime::create(0.2),
                                         //CCCallFuncN::actionWithTarget(this, callfuncN_selector(ScrollWordAndImage::onMoveOver)),
                                         NULL)
                     );
}

void ScrollWordAndImage::SetSize(float width, float height)
{
    this->width = width;
    this->height = height;
    image->setWidth(width);
}




