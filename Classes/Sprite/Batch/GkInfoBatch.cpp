//
//  GuanKaBatch.cpp
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GkInfoBatch.h"

using namespace cocos2d;

//初始化--------------------------------------------------
bool GkInfoBatch::init()
{	
	return true;
}

//设置所有关卡--------------------------------------------------
bool GkInfoBatch::SetAllGk(GUAN_KA * gk, int gkNum)
{
	totalHeight = 0;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float heightX = 0.81f;
    if (CommonFunction::isIpad()) {
        heightX = 0.78f;
    }
    for (int i=0; i<gkNum; i++) {		
        GkInfoDetailLayer * infoLayer = GkInfoDetailLayer::infoWithGk(gk, i, i==gkNum-1);
		CCSize infoSize = infoLayer->getContentSize();
		totalHeight += infoSize.height;
		infoLayer->setPosition(ccp(winSize.width*0.35, winSize.height*heightX - totalHeight));
		this->addChild(infoLayer, 2);		
    }
    
	return true;
}

void GkInfoBatch::onExit()
{
    CCNode::onExit();
}


