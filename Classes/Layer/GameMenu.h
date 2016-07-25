//
//  GameMenu.h
//  xzdd
//
//  Created by  on 12-4-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameMenu_h
#define xzdd_GameMenu_h

#include "cocos2d.h"
#include "GamePause.h"
#include "GameResult.h"
#include "GameMessage.h"
#include "GameSet.h"
#include "GameShowCJ.h"
#include "ParentLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ServerFrameDefs.h"
//#include "LayerNetChat.h"

#else 

#include "../GameCore/ServerFrameDefs.h"
//#include "Net/LayerNetChat.h"

#endif

using namespace cocos2d;

//桌面状态定义
typedef enum 
{
    M_None,
    M_Pause,
    M_Result,
    M_ERROR
    
} MenuState;

class GameMenu : public ParentLayer
{
    GamePause *     gamePause;
    GameResult *    gameResult;
    GameMessage *   gameMessage;
    GameShowCJ *    gameShowCJ;
    GameSet *       gameSet;
//    LayerNetChat *  layerNetChat;
    
    MenuState   mState; //菜单状态
    GameType    mType;  //菜单类型
    bool        mAuto; //是否是托管模式
    CCMenuItemSprite *  pItemPause;
    CCMenuItemSprite *  pItemExit;
    CCMenuItemSprite *  pItemSet;
    CCMenuItemSprite *  readyMenu;
    CCMenuItemSprite *  changeTableMenu;
    CCMenuItemSprite *  pItemCardstart;
    CCMenuItemSprite *  pItemAuto;
    CCMenuItemSprite *  pItemUnAuto;
    CCSprite *          sAuto;
    CCMenu* pMenu;
    
    CCSprite * infoBg;
    CCLabelTTF * infoLabel;
    
    bool    bNoCoinInMenu;
    bool    _bIsPlaying;
    int     _nTarget;
    int     _nStatus;
    bool    bTargetToRestart;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    void initWithGameType(GameType type);
	// implement the "static node()" method manually
	CREATE_FUNC(GameMenu);
    
    bool _isPassGuan;
    bool _isLook;
    
    bool IsPlaying();
    void SetPlaying(bool bPlaying);
	
    virtual void keyBackClicked();
    virtual void onCancel(MessageType type);
    virtual void onConfirm(MessageType type);
    
	// a selector callback
    virtual void menuReadyCallback(CCObject* pSender);
    virtual void menuChangeTableCallback(CCObject* pSender);
    virtual void menuCardStartCallback(CCObject* pSender);
    virtual void menuPauseCallback(CCObject* pSender);
    virtual void menuSetCallback(CCObject* pSender);
    virtual void menuExitCallback(CCObject* pSender);
    virtual void menuChatCallback(CCObject* pSender);
    virtual void menuAutoCallback(CCObject* pSender);
    void ShowReady();
    void ShowResult(Score_Struct * score, HU_CURT * huCurt, BYTE * numFan, 
                    long * gangScore,long * huazhuScore, long * dajiaoScore,PLAYER_DATA * m_sPlayer,BYTE endReason, long* setFanScore);
    void ShowNetResult(HU_CURT * huCurt, PLAYER_DATA * m_sPlayer,BYTE endReason,BYTE * numFan, long *totalScore,
                       long * setScore, long *setLostScore, long * gangScore,long * huazhuScore, long * dajiaoScore);
//    void ShowResult();
    void showCJ(CHENGJIU * cj,BYTE & count);
    void SetAuto(bool isAuto);
    
    void Pause();
    void onPause();
    void onResume();
    void onResultHide();
    void onSetEnableLookOn(bool isEnable);
    
    void onExitNetGame();
    
    void SendChatMsg(string msg);
    void AddChatRecord(char* msg);
    
    void ShowReGKMessage();
    void ShowNoCoinMessage(bool bIsInMenu = false);
    void ShowFleeMessage(int nTarget = -1);
    void ShowNoCoinByRestart();
    void ShowAddCoinMessage();
    
    void SetStatus(int nStatus);
    
    void ReStartGuanka();
    
    void TimerCheckPay(float dt);
    void HandlePaySuccess(int nItem = PAY_ID_COIN);
    void HandlePayFailed(int nItem = PAY_ID_COIN);
    
    void ShowPaySuccess(int nItem = PAY_ID_COIN);
    void ShowPayFailed(int nItem = PAY_ID_COIN);
    
    void ShowInfoMsg(InfoMsgType enType, int arg);
    //void ShowHuMyInfoMsg(int n);
    //void ShowRecInfoMsg(int n);
    void ShowInfoMsgTimeOver(CCNode* sender);
    void HideInfoMsg();
    
    void PayCard();
};


#endif
