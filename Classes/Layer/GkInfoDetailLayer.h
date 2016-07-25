//
//  GkInfoDetailLayer.h
//  xzdd
//
//  Created by  on 12-4-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GkInfoDetailLayer_h
#define xzdd_GkInfoDetailLayer_h
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "CommonFunction.h"

#else 

#include "../Common/CommonFunction.h"

#endif
using namespace cocos2d;

class GkInfoDetailLayer : public CCLayer
{
    CCLabelTTF * title; //标题
    CCLabelTTF * fast;  //快牌
    CCLabelTTF * star1; //星1过关说明
    CCLabelTTF * star2; //星2过关说明
    CCLabelTTF * star3; //星3过关说明
    
public:
    
	GkInfoDetailLayer(void);
	~GkInfoDetailLayer(void);
    
	virtual bool init();
    
    //公有方法------------------------------
    //创建关卡说明对象
    static GkInfoDetailLayer* infoWithGk(GUAN_KA * gk, int gkIndex, bool isLast);    
    
};

#endif