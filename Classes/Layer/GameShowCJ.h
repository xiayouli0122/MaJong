//
//  GameShowCJ.h
//  xzdd
//
//  Created by  on 12-4-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameShowCJ_h
#define xzdd_GameShowCJ_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"
#include "ShowCJ.h"

#else 

#include "../Common/ConstantDef.h"
#include "../Sprite/ShowCJ.h"

#endif

using namespace cocos2d;

class GameShowCJ: public CCLayer
{
    ShowCJ * cc_showCJ;
    CHENGJIU m_cj[20];
    BYTE cjIndex;   //播放列表的位置
    BYTE playIndex; //播放到的位置
    bool showing;   //是否正在运行动画
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	// implement the "static node()" method manually
	CREATE_FUNC(GameShowCJ);
    
    //外部调用方法
    void showCJ(CHENGJIU * cj,BYTE & count);
    
private:
    //播放动画
    void showNextCJ();
    //动画播放玩
    void showEnd();
    //处理状态定时器，定时调用
    void checkCJ(float dt);
};



#endif
