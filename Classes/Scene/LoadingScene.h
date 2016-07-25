//
//  LoadingScene.h
//  xzdd
//
//  Created by  on 12-4-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_LoadingScene_h
#define xzdd_LoadingScene_h

#include "cocos2d.h"
using namespace cocos2d;

typedef enum 
{
	TargetSceneINVALID = 0,
	TargetSceneMainScene,
	TargetSceneGameScene,
    TargetSceneGuanKaScene,
	TargetSceneOverScene,

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
    void undateState(float dt);
    void ShowAd(float dt);
};


#endif
