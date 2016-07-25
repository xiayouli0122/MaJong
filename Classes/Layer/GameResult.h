//
//  GameResult.h
//  xzdd
//
//  Created by  on 12-4-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameResult_h
#define xzdd_GameResult_h

#include "cocos2d.h"
#include "GameMessage.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "MjDef.h"
#include "ServerFrameDefs.h"
#include "CommonFunction.h"

#else 
#include "../GameCore/MjDef.h"
#include "../GameCore/ServerFrameDefs.h"
#include "../Common/CommonFunction.h"
#endif

using namespace cocos2d;

class GameResult : public cocos2d::CCLayerColor
{
    bool _isPassGuan;
    CCSprite * bjSprite;
    GameType mType;
    GameMessage * pGameMessage;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    void initWithGameType(GameType type);
	// implement the "static node()" method manually
	CREATE_FUNC(GameResult);
	
	// a selector callback
    virtual void menuHideCallback(CCObject* pSender);
    
    // 该局的分数,胡牌状态,获取番数

    void ShowLocalResult(Score_Struct * sScore, HU_CURT * huCurt, BYTE * numFan,
                    long * gangScore, long * huazhuScore, long * dajiaoScore,
                    PLAYER_DATA * m_sPlayer,BYTE endReason, long* setFanScore);
    void ShowNetResult(HU_CURT * huCurt, PLAYER_DATA * m_sPlayer,BYTE endReason,BYTE * numFan, long *totalScore,
                       long * setScore, long *setLostScore, long * gangScore,long * huazhuScore, long * dajiaoScore);
    
private:
    void initForSet();
    void ShowResult(BYTE * numFan,HU_CURT * huCurt,long * gangScore,long * huazhuScore, long * dajiaoScore,PLAYER_DATA * m_sPlayer);
    void PassGuan(GUANKA_STATS gk);
    char * GetUserName(BYTE index);
};


#endif
