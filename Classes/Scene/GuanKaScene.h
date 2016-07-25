//
//  GuanKaScene.h
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012Äê __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GuanKaScene_h
#define xzdd_GuanKaScene_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "GuanKaLayer.h"
#include "GameCjLayer.h"
#include "GkInfoLayer.h"

#else 

#include "../Layer/GuanKaLayer.h"
#include "../Layer/GameCjLayer.h"
#include "../Layer/GkInfoLayer.h"

#endif

class GuanKaScene : public cocos2d::CCScene
{
	
    //GuanKaLayer * guanKaLayer;
    GuanKaLayer * guanKaLayer;
    GameCjLayer * cjLayer;
    GkInfoLayer * infoLayer;
    
    CCMenu* pMenu;
public:
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    virtual void onExit();
    virtual void onBack();
    
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(GuanKaScene);
    
    void menuBackCallback(CCObject* pSender);
    void menuCjSceneCallback(CCObject* pSender);
	void menuGkInfoSceneCallback(CCObject* pSender);
    
    void menuRankCallback(CCObject* pSender);
    
    void menuDelockCallback(CCObject* pSender);
    
    void setButtonVisible(bool isVisible);
};


#endif

