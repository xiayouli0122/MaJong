//
//  SelectSprite.h
//  xzdd
//
//  Created by  on 12-4-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_SelectSprite_h
#define xzdd_SelectSprite_h
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"

#else 

#include "../Common/ConstantDef.h"

#endif

using namespace cocos2d;

typedef enum 
{
    ST_Select,
    ST_Unselect
} SelectState; 

class SelectSprite : public CCSprite
{
	CCSprite * gou;     //勾
    
public:
    
	SelectState state;
    
	SelectSprite(void);
	~SelectSprite(void);
    
    virtual bool init();
    
    //公有方法------------------------------
	static SelectSprite* selectWithFrameName(const char *pFrameName);
    virtual void setSelectDisplay(SelectState s);
};

#endif