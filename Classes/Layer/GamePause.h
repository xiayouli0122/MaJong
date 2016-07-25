//
//  GamePause.h
//  xzdd
//
//  Created by  on 12-4-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GamePause_h
#define xzdd_GamePause_h

#include "cocos2d.h"
using namespace cocos2d;

class GamePause : public cocos2d::CCLayerColor
{
    CCSprite * bjSprite;
    //CCLabelTTF* label;
    CCLabelTTF* pLabel1;
    CCLabelTTF* pLabel2;
    CCLabelTTF* pLabel3;
    long        _lCash;
    bool        _bIsPlaying;
    int         _nStatus;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    virtual void onExit();
	// implement the "static node()" method manually
	CREATE_FUNC(GamePause);
	
	//selector callback
    virtual void menuResumeCallback(CCObject* pSender);
    virtual void menuReGKCallback(CCObject* pSender);
    virtual void menuBackToMainMenuCallback(CCObject* pSender);
    virtual void menuBackToGKMenuCallback(CCObject* pSender);
    
    virtual void menuCommunityCallback(CCObject* pSender);
    virtual void menuFriendsCallback(CCObject* pSender);
    
    void handleBackToMainMenu();
    void handleRestartGuanka();
    void handleBackToGuankaMenu();
    
    void Pause();
    void Renew();
    
    void SetPlaying(bool bPlaying);
    void SetStatus(int nStatus);
};


#endif
