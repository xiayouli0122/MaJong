//
//  ShowCJ.cpp
//  xzdd
//
//  Created by  on 12-4-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "ShowCJ.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "CommonFunction.h"

#else 

#include "../Common/CommonFunction.h"

#endif

using namespace cocos2d;

ShowCJ::ShowCJ(void)
{
}


ShowCJ::~ShowCJ(void)
{
}

bool ShowCJ::init()
{
    if(!CCSprite::init())
    {
        return false;
    }
    
    l_cj = CCLabelTTF::create(CONS_STRING_CJ, "Thonburi", CommonFunction::GetValueByDev(12));
    l_cj->setColor(CC_Red);
    addChild(l_cj);
    
    label = CCLabelTTF::create("", "Thonburi", CommonFunction::GetValueByDev(12));
    label->setColor(CC_Yellow);
    addChild(label);
    
    return true;
}

ShowCJ* ShowCJ::creatShowCJ()
{
	ShowCJ* pShowCJ = new ShowCJ();
	pShowCJ->init();
    pShowCJ->initWithSpriteFrameName(CONS_Image_Game_CJ);
	pShowCJ->autorelease();

    CCSize pSize = pShowCJ->getContentSize();
    
    pShowCJ->l_cj->setPosition(ccp(pSize.width*0.25, pSize.height*0.5));
    pShowCJ->label->setPosition(ccp(pSize.width*0.6, pSize.height*0.5));
    
	return pShowCJ;
}

void ShowCJ::show(CHENGJIU * cj)
{
    if (cj->id == 250) { //发到大牌
        l_cj->setVisible(false);
        label->setScale(0.8);
    }
    else{
        l_cj->setVisible(true);
        label->setScale(1);
    }
    label->setString(cj->name);
}