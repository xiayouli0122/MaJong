//
//  GuanKaBatch.cpp
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameMGBatch.h"
#include <string>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "CommonFunction.h"
#include "IOSCommon.h"
#else 

#include "../../Common/CommonFunction.h"

#endif



using namespace cocos2d;

//初始化--------------------------------------------------
bool GameMGBatch::init()
{	
	return true;
}

//设置所有成就--------------------------------------------------
bool GameMGBatch::SetAllMg(MOREGAME * mg, int cjNum)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float heightX = 0.91;
    if (CommonFunction::isIpad()) {
        heightX = 0.85;
    }
    for (int i=0; i<cjNum; i++) {
        GameMGSprite * cjSprite = GameMGSprite::mgWithFrameName(mg++);
		CCSize cjSize = cjSprite->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if(IOSCommon::IsIpad3())
        {
            cjSprite->setScale(2.0f);
            cjSize = cjSprite->boundingBox().size;
        }
#endif
        
		cjSprite->setPosition(ccp(winSize.width*0.465,winSize.height*heightX - cjSize.height*(i+1)));
		this->addChild(cjSprite, 2);
    }
	return true;
}

void GameMGBatch::onExit()
{
    CCNode::onExit();
}
