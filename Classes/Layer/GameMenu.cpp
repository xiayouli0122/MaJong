//
//  GameMenu.cpp
//  xzdd
//
//  Created by  on 12-4-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "GameMenu.h"
#include "GameDesk.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "CommonFunction.h"
#include "LoadingScene.h"
#include "MenuScene.h"
#include "GameScene.h"
//#include "LayerNetGameDesk.h"
#include "IOSCommon.h"
#else 
#include "../Common/CommonFunction.h"
#include "../Scene/LoadingScene.h"
#include "../Scene/MenuScene.h"
#include "../Scene/GameScene.h"
//#include "Net/LayerNetGameDesk.h"
#endif

using namespace cocos2d;

bool GameMenu::init()
{
	//////////////////////////////
	// 1. super init first
    ccColor4B c = {0,0,0,0};
	if (!CCLayerColor::initWithColor(c) )
	{
		return false;
	}
    
    this->setKeypadEnabled(true);
    
    mState = M_None;
    _isPassGuan = false;
	return true;
}

void GameMenu::initWithGameType(GameType type)
{
    mType = type;
    mAuto = false;
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //加入游戏结算层
    gameResult = GameResult::create();
    gameResult->initWithGameType(type);
    this->addChild(gameResult,4);
    
    //加入gameSet层
    gameSet = GameSet::create();
    gameSet->initWithGameType(type);
    this->addChild(gameSet,5);
    
    //加入message层
    gameMessage = GameMessage::create();
    this->addChild(gameMessage,6);
    
    //准备开始按钮菜单
    CCSprite * sx1 = CCSprite::createWithSpriteFrameName(CONS_ActionStart);
    CCSprite * sx2 = CCSprite::createWithSpriteFrameName(CONS_ActionStart2);
//	if (IS_LOCAL)
//    {
//        readyMenu->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.5,
//                                    CCDirector::sharedDirector()->getWinSize().height*0.5) );
//    }
//    else
//    {
//        readyMenu->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.38,
//                                    CCDirector::sharedDirector()->getWinSize().height*0.5) );
//    }
    
    CCSprite * sc1 = CCSprite::createWithSpriteFrameName(CONS_ActionChangeTable);
    changeTableMenu = CCMenuItemSprite::create(sc1,NULL,NULL,this, menu_selector(GameMenu::menuChangeTableCallback));
    
    changeTableMenu->setScale(2.1f);
	changeTableMenu->setPosition( ccp(ptPos.x + winSize.width*0.62,winSize.height*0.5) );

#if IS_NEW_SKIN
    CCSprite * card1 = CCSprite::createWithSpriteFrameName(CONS_IMG_START_CARD_1);
    CCSprite * card2 = CCSprite::createWithSpriteFrameName(CONS_IMG_START_CARD_2);
    pItemCardstart = CCMenuItemSprite::create(card1,card2,NULL,this, menu_selector(GameMenu::menuCardStartCallback));
    
    pItemCardstart->setAnchorPoint(ccp(0, 0.5));
    pItemCardstart->setScale(1.2);
	pItemCardstart->setPosition( ccp(ptPos.x + winSize.width*0.55, winSize.height*0.5) );
    
    readyMenu = CCMenuItemSprite::create(sx2,sx1,NULL,this, menu_selector(GameMenu::menuReadyCallback));
    readyMenu->setAnchorPoint(ccp(1, 0.5));
    readyMenu->setScale(1.2);
    readyMenu->setPosition( ccp(ptPos.x + winSize.width*0.45,winSize.height*0.5) );
    
    CCMenu *prMenu = CCMenu::create(readyMenu,changeTableMenu,pItemCardstart,NULL);
    pItemCardstart->setVisible(false);
#else
    readyMenu = CCMenuItemSprite::create(sx1,sx2,NULL,this, menu_selector(GameMenu::menuReadyCallback));
    readyMenu->setPosition( ccp(ptPos.x + winSize.width*0.38,winSize.height*0.5) );
    
    CCMenu *prMenu = CCMenu::create(readyMenu,changeTableMenu,NULL);
#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        readyMenu->setScale(2.0f);
        changeTableMenu->setScale(2.0f);
    }
#endif
    
    
	prMenu->setPosition( CCPointZero );
	this->addChild(prMenu, 1);
    readyMenu->setVisible(false);
    changeTableMenu->setVisible(false);

	//菜单项初始化
    //暂停
    CCSprite * ccPause = CCSprite::createWithSpriteFrameName(CONS_Image_Game_Pause);
    CCSprite * ccPause1 = CCSprite::createWithSpriteFrameName(CONS_Image_Game_Pause_1);
    pItemPause = CCMenuItemSprite::create(ccPause,ccPause1, NULL,this, 
                                                                      menu_selector(GameMenu::menuPauseCallback));
//    pItemPause->setScale(1.05);
    pItemPause->setAnchorPoint(ccp(1, 1));
	pItemPause->setPosition( ccp(ptPos.x + winSize.width,winSize.height) );
    
    //退出
    CCSprite * ccExit = CCSprite::createWithSpriteFrameName(CONS_Image_Game_Quit);
    pItemExit = CCMenuItemSprite::create(ccExit,NULL,NULL,this, 
                                                                      menu_selector(GameMenu::menuExitCallback));
	pItemExit->setAnchorPoint(ccp(1,1));
    pItemExit->setPosition( ccp(ptPos.x + winSize.width,winSize.height) );
    
    //设置
    CCSprite * ccSet = CCSprite::createWithSpriteFrameName(CONS_Image_Game_Set);
    CCSprite * ccSet1 = CCSprite::createWithSpriteFrameName(CONS_Image_Game_Set_1);
    pItemSet = CCMenuItemSprite::create(ccSet,ccSet1,NULL,this, 
                                                                      menu_selector(GameMenu::menuSetCallback));
//    pItemSet->setScale(1.05);
    pItemSet->setAnchorPoint(ccp(1, 1));
    CCSize itemSize = pItemPause->boundingBox().size;
	pItemSet->setPosition( ccp(ptPos.x + winSize.width*0.97 - itemSize.width, winSize.height) );
    
    //聊天
    CCSprite * ccChat = CCSprite::createWithSpriteFrameName(CONS_Image_Chat_Button);
    CCMenuItemSprite *pItemChat = CCMenuItemSprite::create(ccChat,NULL,NULL,this, 
                                                                      menu_selector(GameMenu::menuChatCallback));
	pItemChat->setPosition( ccp(ptPos.x + winSize.width*0.06,winSize.height*0.34) ); 
    //托管
    CCSprite * ccAuto = CCSprite::createWithSpriteFrameName(CONS_Image_Delegate);
    pItemAuto = CCMenuItemSprite::create(ccAuto,NULL,NULL,this, 
                                                       menu_selector(GameMenu::menuAutoCallback));
	pItemAuto->setPosition( ccp(ptPos.x + winSize.width*0.06,winSize.height*0.25) );
    pItemAuto->setVisible(false);
    
    //取消托管
    CCSprite * ccUnAuto = CCSprite::createWithSpriteFrameName(CONS_Image_Delegate_Cancel);
    pItemUnAuto = CCMenuItemSprite::create(ccUnAuto,NULL,NULL,this, 
                                                       menu_selector(GameMenu::menuAutoCallback));
	pItemUnAuto->setPosition( ccp(ptPos.x + winSize.width*0.06,winSize.height*0.25) );
    pItemUnAuto->setVisible(false);
    
    //托管图标
    sAuto = CCSprite::createWithSpriteFrameName(CONS_Image_Delegate_Robot);
    sAuto->setPosition( ccp(ptPos.x + winSize.width*0.02,winSize.height*0.03) );
    sAuto->setVisible(false);
    
    if (type == GT_SingleGame) {
        //加入暂停层
        gamePause = GamePause::create();
        this->addChild(gamePause,3);
        
        //加入成就显示层
        gameShowCJ = GameShowCJ::create();
        this->addChild(gameShowCJ,7);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if(IOSCommon::IsIpad3())
        {
            pItemPause->setScale(2.0f);
            pItemSet->setScale(2.0f);
        }
#endif
        //加入菜单
        pMenu = CCMenu::create(pItemPause,pItemSet, NULL);
        pMenu->setPosition( CCPointZero );
        this->addChild(pMenu, 2);
        
        infoBg = CCSprite::createWithSpriteFrameName(CONS_IMG_INFO_BG);
        infoBg->setPosition( ccp(ptPos.x + winSize.width*0.5, winSize.height*0.5) );
        infoBg->setVisible(false);
        this->addChild(infoBg,4);
        
        infoLabel = CCLabelTTF::create("", "Thonburi", CommonFunction::GetValueByDev(12));
        //infoLabel->setColor(CC_Yellow);
        infoLabel->setPosition( ccp(ptPos.x + winSize.width*0.5, winSize.height*0.5) );
        infoLabel->setVisible(false);
        this->addChild(infoLabel,5);
    }
    else
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if(IOSCommon::IsIpad3())
        {
            pItemExit->setScale(2.0f);
            pItemSet->setScale(2.0f);
            pItemChat->setScale(2.0f);
            pItemAuto->setScale(2.0f);
            pItemUnAuto->setScale(2.0f);
        }
#endif
        //加入菜单
        pMenu = CCMenu::create(pItemExit,pItemSet,pItemChat,pItemAuto,pItemUnAuto,NULL);
        pMenu->setPosition( CCPointZero );
        this->addChild(pMenu, 2);
        
        this->addChild(sAuto);        
        //加入聊天层
//         layerNetChat = LayerNetChat::create();
//         layerNetChat->calListHeight();
//         layerNetChat->checkGun();
//         layerNetChat->setVisible(false);
//         layerNetChat->setTouchEnabled(false);
//        this->addChild(layerNetChat,7);
    }

}

void GameMenu::ShowResult(Score_Struct * score, HU_CURT * huCurt, BYTE * numFan, 
                          long * gangScore,long * huazhuScore, long * dajiaoScore,PLAYER_DATA * m_sPlayer,BYTE endReason, long* setFanScore)
{
    //pMenu->setVisible(false);
    SetBoolToXML(UD_IsRegularSet,true);
    pItemPause->setVisible(false);
    pItemSet->setVisible(false);
    gameResult->ShowLocalResult(score, huCurt, numFan, gangScore,huazhuScore,dajiaoScore,m_sPlayer, endReason, setFanScore);
    mState = M_Result;
}
void GameMenu::ShowNetResult(HU_CURT * huCurt, PLAYER_DATA * m_sPlayer,BYTE endReason,BYTE * numFan, long *totalScore,
                   long * setScore, long *setLostScore, long * gangScore,long * huazhuScore, long * dajiaoScore)
{
    //pMenu->setVisible(false);
    pItemUnAuto->setVisible(false);
    pItemAuto->setVisible(false);
    sAuto->setVisible(false);
    gameResult->ShowNetResult(huCurt, m_sPlayer,endReason,numFan, totalScore,
                           setScore, setLostScore, gangScore,huazhuScore, dajiaoScore);
    mState = M_Result;
}
//void GameMenu::ShowResult()
//{
//    readyMenu->setVisible(false);
//    gameResult->setVisible(true);
//}
void GameMenu::ShowReady()
{
    readyMenu->setVisible(!_isLook);
    //changeTableMenu->setVisible(true);
    changeTableMenu->setVisible(!_isLook);
    
    pItemAuto->setVisible(false);
    pItemUnAuto->setVisible(false);
    sAuto->setVisible(false);
}

void GameMenu::showCJ(CHENGJIU * cj,BYTE & count)
{
    gameShowCJ->showCJ(cj,count);
}

void GameMenu::menuReadyCallback(CCObject* pSender)
{
    if (mType == GT_NetGame) {
//         if (((LayerNetGameDesk *)getParent())->onReadyCall()) {
//             readyMenu->setVisible(false);
//             changeTableMenu->setVisible(false);
//         }
    }
    else{
        //单机游戏币更新
        if (!CommonFunction::IsEnoughCoin())
        {
            //paddy test 提示充值
            CCLOG("***** no coin *****");
            ShowNoCoinMessage();
            return;
        }

        readyMenu->setVisible(false);
#if IS_NEW_SKIN
        pItemCardstart->setVisible(false);
#endif

        if (_isPassGuan) {
            CCDirector::sharedDirector()->replaceScene(LoadingScene::scene(TargetSceneGuanKaScene));
        }
        else {
//            SetBoolToXML(UD_IsContinueSet,true);
            CCDirector::sharedDirector()->replaceScene(GameCScene::create());
        }
    }
}
void GameMenu::menuChangeTableCallback(CCObject* pSender)
{
//    ((LayerNetGameDesk *)getParent())->onChangeTable();
}

void GameMenu::menuCardStartCallback(CCObject* pSender)
{
    ((GameDesk *)getParent())->BuyCard();
}


void GameMenu::menuPauseCallback(CCObject* pSender)
{
    Pause();
}

void GameMenu::menuSetCallback(CCObject* pSender)
{
    gameSet->ShowGameSet(GST_GameMenu);
    if(mType == GT_SingleGame){
        cocos2d::CCDirector::sharedDirector()->pause();
        this->onPause();
    }
    else if(mType == GT_NetGame){
//        layerNetChat->onClose();
    }
}
void GameMenu::menuExitCallback(CCObject* pSender)
{
    if (mType == GT_SingleGame) {
        CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
    }
    else
    {
//         if (((LayerNetGameDesk *)getParent())->isLook || !((LayerNetGameDesk *)getParent())->isPlaying) {
//             //如果是旁观状态，或不是游戏状态，则立即推出
//             onExitNetGame();
//         }
//         else
        {
            //提示扣分
            gameMessage->SetMessageType(MT_RunAway);
        }
    }
}
void GameMenu::menuChatCallback(CCObject* pSender)
{
    gameSet->setVisible(false);
//    layerNetChat->onShow();
}
void GameMenu::menuAutoCallback(CCObject* pSender)
{
//     ((LayerNetGameDesk *)getParent())->SetAutoPlay(!((LayerNetGameDesk *)getParent())->GetAutoPlay());
//     SetAuto(((LayerNetGameDesk *)getParent())->GetAutoPlay());
}
//设置托管的显示
void GameMenu::SetAuto(bool isAuto)
{
    mAuto = isAuto;
    pItemAuto->setVisible(!mAuto);
    pItemUnAuto->setVisible(mAuto);
    sAuto->setVisible(mAuto);
}

void GameMenu::keyBackClicked(){
    
    if (mType == GT_SingleGame) {
        
        if (gameSet->isVisible()) {
            gameSet->setVisible(false);
            CCDirector::sharedDirector()->resume();
            this->onResume();
            return;
        }
        
        if (gamePause->isVisible()&&!gameMessage->isVisible())
        {
            gamePause->setVisible(false);
            CCDirector::sharedDirector()->resume();
            this->onResume();
            return;
        }
        
        if (mState == M_Result) {
            gameResult->setVisible(false);
            onResultHide();
        }else if(mState == M_None){
            Pause();
        }
    }
    else
    {
//         if (layerNetChat->isVisible()) {
//             layerNetChat->onClose();
//             return;
//         }
        
        if(gameResult->isVisible()){
            gameResult->setVisible(false);
            onResultHide();
            return;
        }
        
        if (gameSet->isVisible()) {
            gameSet->setVisible(false);
            return;
        }
        
//         if (((LayerNetGameDesk *)getParent())->isLook || !((LayerNetGameDesk *)getParent())->isPlaying) {
//             //如果是旁观状态，或不是游戏状态，则立即推出
//             onExitNetGame();
//         }
//         else
        {
            //提示扣分
            gameMessage->SetMessageType(MT_RunAway);
        }
    }
}

//#pragma mark -----------------------暂停和恢复----------------------
void GameMenu::Pause()
{
    //在页面状态允许暂停的时候暂停
    if (mState == M_None) {
        gamePause->Pause();
    }
}
void GameMenu::onPause()
{
    CCLOG("GameMenu::onPause");
    ((GameDesk *)this->getParent())->onPause();
    pMenu->setVisible(false);
    mState = M_Result;
//    TimerCheckPay();
}
void GameMenu::onResume()
{
    CCLOG("GameMenu::onResume");
    ((GameDesk *)this->getParent())->onResume();
     SOUND->setBackgroundMusicVolume(GetIntegerToXML(UD_Set_Music,100)*0.01);
     SOUND->setEffectsVolume(GetIntegerToXML(UD_Set_Effect,100)*0.01);
    pMenu->setVisible(true);
    mState = M_None;
}
void GameMenu::onResultHide()
{
    readyMenu->setVisible(true);
    if (mType == GT_SingleGame){
        pItemPause->setVisible(true);
        mState = M_None;
        ((GameDesk *)this->getParent())->UpdateCoinLabel();
#if IS_NEW_SKIN
        pItemCardstart->setVisible(true);
#endif
    }
    else{
        changeTableMenu->setVisible(true);
        //Truman add
        {
            changeTableMenu->setVisible(!_isLook);
        }
    }
}

//#pragma mark -----------------------重新开始关卡----------------------
void GameMenu::ShowReGKMessage()
{
    gameMessage->SetMessageType(MT_ReGK);
}

void GameMenu::onCancel(MessageType type)
{
    if(type == MT_ReGK)
    {
        gameMessage->setVisible(false);
        gamePause->Renew();
        gamePause->setVisible(true);
        ((GameDesk *)this->getParent())->UpdateCoinLabel();
    }
    else if(type == MT_RunAway)
    {
        gameMessage->setVisible(false);
    }
    else if(type == MT_NO_COIN)
    {
        gameMessage->setVisible(false);
        if (bNoCoinInMenu)
        {
            gamePause->Renew();
            gamePause->setVisible(true);
            ((GameDesk *)this->getParent())->UpdateCoinLabel();
        }
//        cocos2d::CCDirector::sharedDirector()->resume();
//        CCDirector::sharedDirector()->replaceScene(LoadingScene::scene(TargetSceneGuanKaScene));

    }
    else if(type == MT_SINGLE_FLEE)
    {
        gameMessage->setVisible(false);
        gamePause->Renew();
        gamePause->setVisible(true);
        ((GameDesk *)this->getParent())->UpdateCoinLabel();
    }
    else if(type == MT_ADD_COIN)
    {
        gameMessage->setVisible(false);
    }
}

void GameMenu::onConfirm(MessageType type)
{
    if (type == MT_ReGK)
    {
        if (!_bIsPlaying)
        {
            ReStartGuanka();
        }
        else
        {
//            ShowFleeMessage(enTargetRestart);
            switch (_nStatus)
            {
                case StatusPlayerHu:
                    ReStartGuanka();
                    break;
                case StatusJipinHu:
                    ShowFleeMessage(TargetRestart);
                    break;
                case StatusPlayerNoHu:
                    ShowFleeMessage(TargetRestart);
                    break;
                    
                default:
                    break;
            }

        }
    }
    else if(type == MT_RunAway)
    {
        onExitNetGame();
    }
    else if(type == MT_NO_COIN)
    {
        CommonFunction::payfee(1,PAY_ID_COIN);
        SetBoolToXML(CONS_STR_IS_PAY_COIN,true);
        
        schedule(schedule_selector(GameMenu::TimerCheckPay));

////<for test
#if IS_QUICK_PAY
        CommonFunction::AddCoin(COIN_NUM_PAY);
        SetBoolToXML("isPayRet", true);
        SetBoolToXML("isPaySucceed", true);
        SetBoolToXML("isPayCancel", false);
#endif
////for test>
        
        gameMessage->setVisible(false);
        if (bNoCoinInMenu)
        {
            gamePause->Renew();
            gamePause->setVisible(true);
            ((GameDesk *)this->getParent())->UpdateCoinLabel();
        }
    }
    else if(type == MT_SINGLE_FLEE)
    {
        //单机游戏金币更新
        int nCoin;
        if (_nStatus == StatusJipinHu)
        {
            nCoin= CommonFunction::SubCoin(COIN_NUM_FLEE_JIPIN);
        }
        else
        {
            nCoin= CommonFunction::SubCoin(COIN_NUM_FLEE);
        }
        CCAssert(nCoin>=0, "");
        
        switch (_nTarget)
        {
            case TargetGuankaMenu:
                gamePause->handleBackToGuankaMenu();
                break;
            case TargetMainMenu:
                gamePause->handleBackToMainMenu();
                break;
            case TargetRestart:
                gamePause->handleRestartGuanka();
                break;
            default:
                break;
        }
    }
    else if(type == MT_ADD_COIN)
    {
        ((GameDesk *)this->getParent())->onPause();
        gameMessage->setVisible(false);
        gamePause->setVisible(true);
        
        CommonFunction::payfee(1,PAY_ID_COIN);
        SetBoolToXML(CONS_STR_IS_PAY_COIN,true);
        
        schedule(schedule_selector(GameMenu::TimerCheckPay));
        
////<for test
//        CommonFunction::AddCoin(COIN_NUM_PAY);
//        SetBoolToXML("isPayRet", true);
//        SetBoolToXML("isPaySucceed", true);
//        SetBoolToXML("isPayCancel", false);
////for test>
    }
    else if(type == MT_PAY_COIN_MSG)
    {
        gamePause->Renew();
        
        gameMessage->setVisible(false);
        gameMessage->setVisibleCancel(true);
        ((GameDesk *)this->getParent())->UpdateCoinLabel();
    }
}

void GameMenu::onSetEnableLookOn(bool isEnable)
{
//    ((LayerNetGameDesk *)getParent())->onSetEnableLookOn(isEnable);
}
void GameMenu::onExitNetGame()
{
//    ((LayerNetGameDesk *)getParent())->onUserExit();
}

//#pragma mark -----------------------发送聊天消息----------------------

void GameMenu::SendChatMsg(string msg){
//    ((LayerNetGameDesk*)this->getParent())->SendChatMsg(msg);
}

void GameMenu::AddChatRecord(char* msg){
//    layerNetChat->AddChatRecord(msg);
}


void GameMenu::ShowNoCoinMessage(bool bIsInMenu)
{
    bNoCoinInMenu = bIsInMenu;
    bTargetToRestart = false;
    gameMessage->SetMessageType(MT_NO_COIN);
}

void GameMenu::ShowAddCoinMessage()
{
    gameMessage->SetMessageType(MT_ADD_COIN);
}

void GameMenu::ShowFleeMessage(int nTarget)
{
    _nTarget = nTarget;
    gameMessage->SetMessageType(MT_SINGLE_FLEE, _nStatus);
    CCLog("***nStatus: %d***", _nStatus);
}

bool GameMenu::IsPlaying()
{
    return _bIsPlaying;
}

void GameMenu::SetPlaying(bool bPlaying)
{
    _bIsPlaying = bPlaying;
    gamePause->SetPlaying(bPlaying);
    if (bPlaying)
    {
        _nStatus = StatusPlayerNoHu;
    }
}

void GameMenu::ShowNoCoinByRestart()
{
    bNoCoinInMenu = true;
    bTargetToRestart = true;
    gameMessage->SetMessageType(MT_NO_COIN);
}

void GameMenu::SetStatus(int nStatus)
{
    if (_nStatus == StatusJipinHu)
    {
        return;
    }
    _nStatus = nStatus;
    gamePause->SetStatus(nStatus);
}

void GameMenu::ReStartGuanka()
{
    cocos2d::CCDirector::sharedDirector()->resume();
    //重新创建电脑玩家
    CommonFunction::CreatePlayersByGuan(GetIntegerToXML(UD_CurrentGuanKa,0));
    //重新开始关卡前，清除游戏进度数据
    CommonFunction::ClearGuanKaSaveData(GetIntegerToXML(UD_CurrentGuanKa,0));
    CCDirector::sharedDirector()->replaceScene(LoadingScene::scene(TargetSceneGameScene));
}

void GameMenu::TimerCheckPay(float dt)
{
    //如果充值返回
    if(GetBoolToXML("isPayRet",false))
    {
        
        if(GetBoolToXML(CONS_STR_IS_PAY_COIN,false))
        {
            CCLOG("TimerCheckPay, coin charge");
            
            //充值成功
            if(GetBoolToXML("isPaySucceed",false))
            {
                //提示消息
                HandlePaySuccess(PAY_ID_COIN);
            }
            else
            {
                //失败
                if(GetBoolToXML("isPayCancel",false))
                {
                    //取消
                    unschedule( schedule_selector(GameMenu::TimerCheckPay));
                }
                else
                {
                    //扣费失败结果
                    //HandlePayFailed(PAY_RMB_COIN);
                    unschedule( schedule_selector(GameMenu::TimerCheckPay));
                }
            }
            
            SetBoolToXML(CONS_STR_IS_PAY_COIN,false);
            SetBoolToXML("isPayRet",false);
            SetBoolToXML("isPayCancel",false);
        }
        
        if(GetBoolToXML(CONS_STR_IS_PAY_CARD,false))
        {
            CCLOG("TimerCheckPay, card charge");
            
            //充值成功
            if(GetBoolToXML("isPaySucceed",false))
            {
                //提示消息
                HandlePaySuccess(PAY_ID_CARD);
            }
            else
            {
                //失败
                if(GetBoolToXML("isPayCancel",false))
                {
                    //取消
                    unschedule( schedule_selector(GameMenu::TimerCheckPay));
                }
                else
                {
                    //扣费失败结果
                    //HandlePayFailed(PAY_RMB_COIN);
                    unschedule( schedule_selector(GameMenu::TimerCheckPay));
                }
            }
            
            SetBoolToXML(CONS_STR_IS_PAY_CARD,false);
            SetBoolToXML("isPayRet",false);
            SetBoolToXML("isPayCancel",false);
        }
    }
}

void GameMenu::HandlePaySuccess(int nItem)
{
    CCLOG("HandlePaySuccess: %d", nItem);
    unschedule( schedule_selector(GameMenu::TimerCheckPay));
    
    ShowPaySuccess(nItem);
    
//    gamePause->setVisible(false);
//    CCDirector::sharedDirector()->resume();
//    this->onResume();
    
//    if (nItem == PAY_ID_COIN)
//    {
//        
//    }
//    else if (nItem == PAY_ID_CARD)
//    {
//        
//    }
}

void GameMenu::HandlePayFailed(int nItem)
{
    unschedule( schedule_selector(GameMenu::TimerCheckPay));
}

void GameMenu::ShowPayFailed(int nItem)
{
    
}

void GameMenu::ShowPaySuccess(int nItem)
{
    if (nItem == PAY_ID_COIN)
    {
        gameMessage->SetMessageType(MT_PAY_COIN_MSG, 1);
        if (IS_COMMUNITY && GetBoolToXML(UD_IS_MAX_COIN_REC, false))
        {
            //        ShowRecInfoMsg(GetIntegerToXML(UD_SINGLE_COIN));
            ShowInfoMsg(INFO_NEW_RECORD, GetIntegerToXML(UD_SINGLE_COIN));
        }
    }
    else if(nItem == PAY_ID_CARD)
    {
        ShowInfoMsg(INFO_PROP_CARD_INUSE, 0);
    }
}


void GameMenu::ShowInfoMsg(InfoMsgType enType, int arg)
{
    char str[128];
    float fDuration;
    switch (enType)
    {
        case INFO_BLOOD_TIPS:
            if (arg ==0 )
            {
                sprintf(str, "您先胡了！\n牌局继续，剩余玩家血战到底！");
            }
            else
            {
                sprintf(str, "有%d家先胡了！\n牌局继续，血战到底！", arg);
            }
            infoBg->setScaleX(0.9f);
            infoBg->setScaleY(0.6f);
            fDuration = 3.0;
            break;
            
        case INFO_NEW_RECORD:
            infoBg->setScaleX(1.0f);
            infoBg->setScaleY(0.5f);
            sprintf(str, "已刷新您的游戏币最高记录%d！", arg);
            fDuration = 4.5;
            break;
            
        case INFO_PROP_CARD_INUSE:
            infoBg->setScaleX(0.9f);
            infoBg->setScaleY(0.6f);
            fDuration = 3.0;
            sprintf(str, "好牌道具已使用!\n下一局您将获得一手好牌！");
            break;
        default:
            return;
    }
    infoLabel->setString(str);
    infoLabel->setVisible(true);
    infoBg->setVisible(true);
    infoBg->runAction(CCSequence::create(CCDelayTime::create(fDuration),
                                          CCCallFuncN::create(this, callfuncN_selector(GameMenu::ShowInfoMsgTimeOver)),
                                          NULL)
                      );
    
//    schedule( schedule_selector(GameMenu::ShowInfoMsgTimeOver), fDuration);
}

//void GameMenu::ShowRecInfoMsg(int n)
//{
//    char str[128];
//    sprintf(str, "已刷新您的游戏币最高记录%d！", n);
//    infoLabel->setString(str);
//    infoLabel->setVisible(true);
//    infoBg->setVisible(true);
//    infoBg->setScaleX(0.9f);
//    infoBg->setScaleY(0.6f);
//    infoBg->runAction(CCSequence::actions(CCDelayTime::create(5),
//                                          CCCallFuncN::actionWithTarget(this, callfuncN_selector(GameMenu::ShowInfoMsgTimeOver)),
//                                          NULL));
//}

void GameMenu::ShowInfoMsgTimeOver(CCNode* sender)
{
//    unschedule( schedule_selector(GameMenu::ShowInfoMsg));
    HideInfoMsg();
}

void GameMenu::HideInfoMsg()
{
    infoLabel->setVisible(false);
    infoBg->setVisible(false);
    infoBg->setScaleX(1.0f);
    infoBg->setScaleY(1.0f);
}

void GameMenu::PayCard()
{
    ((GameDesk *)this->getParent())->onPause();
    //gameMessage->setVisible(false);
    gamePause->setVisible(true);
    
    CommonFunction::payfee(1, PAY_ID_CARD);
    SetBoolToXML(CONS_STR_IS_PAY_CARD,true);
    
    schedule(schedule_selector(GameMenu::TimerCheckPay));
}
