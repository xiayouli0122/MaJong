
#ifndef xzdd_GameMoreGameScene_h
#define xzdd_GameMoreGameScene_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "GameMGLayer.h"

#else 

#include "../Layer/GameMGLayer.h"

#endif


class GameMoreGameScene :public cocos2d::CCScene
{
public:
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(); 
    
	// implement the "static node()" method manually
	CREATE_FUNC(GameMoreGameScene);
    
	void menuBackCallback(CCObject* pSender);
};


#endif


