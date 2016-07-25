//
//  GameHelp.cpp
//  xzdd
//
//  Created by  on 12-5-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "GameHelp.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "MyTinyXmlParser.h"
#include "CommonFunction.h"

#else 

#include "../Common/MyTinyXmlParser.h"
#include "../Common/CommonFunction.h"

#endif


using namespace cocos2d;

//初始化--------------------------------------------------
bool GameHelp::init()
{
	//super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    int height = CommonFunction::GetValueByDev(900);
    
    if (ISANDROID) {
        height = CommonFunction::GetValueByDev(820);
    }
    
	CCLabelTTF * hLabel = CCLabelTTF::create(MyTinyXmlParser::GetHelp(0).c_str(),"Thonburi",
											CommonFunction::GetValueByDev(11),
											CCSizeMake(CommonFunction::GetValueByDev(480),
                                                    height), 
											kCCTextAlignmentLeft
											);
    hLabel->setAnchorPoint(ccp(0,0.5));
	hLabel->setPosition( ccp(0, size.height - height * 0.5) );
	this->addChild(hLabel, 1,1);
    
    int height1 = CommonFunction::GetValueByDev(600);
    
    if (ISANDROID) {
        height1 = CommonFunction::GetValueByDev(480);//280 lyp
    }
    
	CCLabelTTF * hLabel1 = CCLabelTTF::create(MyTinyXmlParser::GetHelp(1).c_str(),"Thonburi",
											CommonFunction::GetValueByDev(11),
											CCSizeMake(CommonFunction::GetValueByDev(480),
											height), 
											kCCTextAlignmentLeft
											);
    hLabel1->setAnchorPoint(ccp(0,0.5));
	hLabel1->setPosition( ccp(0, size.height - height - height1 * 0.5) );
	this->addChild(hLabel1, 1,1);
    
    
	return true;
}

void GameHelp::onExit()
{
    CCLayer::onExit();
}

