//
//  GameCjSprite.h
//  xzdd
//
//  Created by  on 12-4-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameCjSprite_h
#define xzdd_GameCjSprite_h

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "CommonFunction.h"
#else 
#include "../Common/CommonFunction.h"
#endif

using namespace cocos2d;

class GameCjSprite : public CCSprite
{
    CCLabelTTF * title; //标题
    CCLabelTTF * content;//内容
    
public:
    
	GameCjSprite(void);
	~GameCjSprite(void);
    
	virtual bool init();
    
    //公有方法------------------------------
    //通过图片名创建成就对象
    static GameCjSprite* cjWithFrameName(CHENGJIU * cj, int cjIndex, CCSize itemSize);
    
};

#endif

