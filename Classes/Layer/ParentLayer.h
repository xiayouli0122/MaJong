//
//  ParentLayer.h
//  xzdd
//
//  Created by  on 12-4-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_ParentLayer_h
#define xzdd_ParentLayer_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"

#else 

#include "../Common/ConstantDef.h"

#endif

using namespace cocos2d;
class ParentLayer : public cocos2d::CCLayerColor
{
public:
	//定义了两个纯虚函数，派生类必须重写
    virtual void onCancel(MessageType type) =0;
    virtual void onConfirm(MessageType type) =0;
};

#endif
