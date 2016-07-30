//
//  LoadingScene.h
//  xzdd
//
//  启动界面
//  Created by  on 12-4-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_LoadingScene_h
#define xzdd_LoadingScene_h

#include "cocos2d.h"
using namespace cocos2d;

//定义了一个TargetScene的枚举
typedef enum 
{
	TargetSceneINVALID = 0,
	TargetSceneMainScene,
	TargetSceneGameScene,
    TargetSceneGuanKaScene,
	TargetSceneOverScene,
	TargetSceneLoginScene,

	TargetSceneMAX,
} TargetScene;

class LoadingScene : public CCLayer
{
    CCSprite * bjSprite;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
    virtual void onExit();
	static cocos2d::CCScene* scene(TargetScene target);
    
    TargetScene targetScene;
	
	// implement the "static node()" method manually
	CREATE_FUNC(LoadingScene);
private:
    
    //处理状态定时器，定时调用
    void updateState(float dt);
    //显示广告？
	void ShowAd(float dt);
};


#endif
