//
//  GkInfoBatch.h
//  xzdd
//
//  Created by  on 12-4-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GkInfoBatch_h
#define xzdd_GkInfoBatch_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "GkInfoDetailLayer.h"

#else 

#include "../../Layer/GkInfoDetailLayer.h"

#endif

using namespace cocos2d;

class GkInfoBatch : public cocos2d::CCNode
{
    
protected:
//    CCMutableArray<GkInfoDetailLayer*> *infoArray;   //成就数组
	CCArray *infoArray;   //成就数组
    
public:
	//初始化--------------------------------------------------
	virtual bool init();
	virtual bool SetAllGk(GUAN_KA * gk, int gkNum);
    virtual void onExit();
	// implement the "static node()" method manually
	CREATE_FUNC(GkInfoBatch);  
    
	float totalHeight;
    
};

#endif
