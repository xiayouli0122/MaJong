//
//  GuanKaBatch.cpp
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameCjBatch.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "CommonFunction.h"
#include "IOSCommon.h"
#else 
#include "../../Common/CommonFunction.h"
#endif

using namespace cocos2d;

//初始化--------------------------------------------------
bool GameCjBatch::init()
{
	return true;
}

//设置所有成就--------------------------------------------------
bool GameCjBatch::SetAllCj(CHENGJIU * cj, int cjNum, CCSize itemSize)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float heightX = 0.91;
    if (CommonFunction::isIpad()) {
        heightX = 0.85;
    }
    for (int i=0; i<cjNum; i++) {
        GameCjSprite * cjSprite = GameCjSprite::cjWithFrameName(cj, i,itemSize);
#if IS_NEW_SKIN
		cjSprite->setPosition(ccp(winSize.width*0.49,winSize.height*heightX - itemSize.height*(i+1)));
#else
        cjSprite->setPosition(ccp(winSize.width*0.465,winSize.height*heightX - itemSize.height*(i+1)));
#endif
		this->addChild(cjSprite, 2);

    }
	return true;
}

void GameCjBatch::onExit()
{
    CCNode::onExit();
}