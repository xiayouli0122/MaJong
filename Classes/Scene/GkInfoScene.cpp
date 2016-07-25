//
//  GameCjScene.cpp
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GkInfoScene.h"

using namespace cocos2d;

// on "init" you need to initialize your instance
bool GkInfoScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}
    this->setTag(ST_MENU);
    
	GkInfoLayer * infoLayer = GkInfoLayer::create();  
	this->addChild(infoLayer);
    
	return true;
}