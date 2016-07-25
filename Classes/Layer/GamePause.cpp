//
//  GamePause.cpp
//  xzdd
//
//  Created by  on 12-4-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "GamePause.h"
#include "GameMenu.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "LoadingScene.h"
#include "MenuScene.h"
#include "CommonFunction.h"
#include "IOSCommon.h"
#else 

#include "../Scene/LoadingScene.h"
#include "../Scene/MenuScene.h"
#include "../Common/CommonFunction.h"

#endif


using namespace cocos2d;

bool GamePause::init()
{
	//////////////////////////////
	// 1. super init first
    ccColor4B c = {0,0,0,150};
	if (!CCLayerColor::initWithColor(c) )
	{
		return false;
	}
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //加入背景
    bjSprite = new CCSprite();
    if (CommonFunction::isIpad()) {
        bjSprite->initWithFile(CONS_Image_BG_Pause_Ipad);
    }else {
        bjSprite->initWithFile(CONS_Image_BG_Pause);
    }

    bjSprite->setAnchorPoint(ccp(0.5, 0.5));
    bjSprite->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(bjSprite,0,0);
    
    CCSize bgSize = bjSprite->getContentSize();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        bjSprite->setAnchorPoint(ccp(0.5f,0.5f));
        bjSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
        bjSprite->setScale(2.0f);
        bgSize = bjSprite->boundingBox().size;
    }
#endif
    
    GUAN_KA gk = CommonFunction::GetGuanKa(GetIntegerToXML(UD_CurrentGuanKa));
    
    // 加入一个 label guanka name
    char str[500];
    sprintf(str,CONS_STRING_DJG,gk.nId,gk.nName);
	pLabel1 = CCLabelTTF::create(str, "Verdana-Bold", CommonFunction::GetValueByDev(14));
	pLabel1->setPosition( ccp(size.width / 2, size.height*0.5 + bgSize.height*0.37) );
    pLabel1->setColor(CCPauseTitle);
    
	this->addChild(pLabel1, 2);
    
    GUANKA_STATS gkStats = CommonFunction::GetGuanKaStats(gk.nId);
    
    //guanka conditions
    sprintf(str,CONS_STRING_CGJD,
            gkStats.nSet,
            gkStats.nScore,
            gk.conditionOne.nScore,
            gkStats.nFan,
            gk.conditionOne.nFanNum,
            gkStats.nJiPin,
            gk.conditionOne.nChaoHuNum);
	pLabel2 = CCLabelTTF::create(str, "Verdana", CommonFunction::GetValueByDev(13));
	pLabel2->setPosition( ccp(size.width / 2, size.height*0.5 + bgSize.height*0.15) );
    pLabel2->setColor(CCPauseContent);
	this->addChild(pLabel2, 2);
    
    
    _lCash = GetIntegerToXML(UD_SINGLE_COIN);
    // 加入金币 label
    sprintf(str,CONS_STRING_CASH,_lCash);
	pLabel3 = CCLabelTTF::create(str, "Verdana-Bold", CommonFunction::GetValueByDev(13));
	pLabel3->setPosition( ccp(size.width / 2, size.height*0.5 + bgSize.height*0.30) );
    pLabel3->setColor(CCPauseCash);
	this->addChild(pLabel3, 2);

    
    // 加入菜单    - 继续
    CCSprite * ci1_1 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Continue_1);
    CCSprite * ci1_2 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Continue_2);
    
    CCMenuItemSprite *pItem1 = CCMenuItemSprite::create(ci1_1,ci1_2,NULL,this, 
                                                                      menu_selector(GamePause::menuResumeCallback));
    pItem1->setPosition( ccp(size.width*0.5,size.height*0.5 - bgSize.height*0.05 ) );
//	pItem1->setPosition( ccp(size.width*0.5,size.height*0.5 + bgSize.height*0.02 ) ); 
    
	// 加入菜单    - 重新开始本关
    CCSprite * ci2_1 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_ReGK_1);
    CCSprite * ci2_2 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_ReGK_2);
    
    CCMenuItemSprite *pItem2 = CCMenuItemSprite::create(ci2_1,ci2_2,NULL,this, 
                                                                      menu_selector(GamePause::menuReGKCallback));
    pItem2->setPosition( ccp(size.width*0.5,size.height*0.5 - bgSize.height*0.20) );
//	pItem2->setPosition( ccp(size.width*0.5,size.height*0.5 - bgSize.height*0.11) );
    
    
    // 加入菜单    - quit game
    CCSprite * ci3_1 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_GK_1);
    CCSprite * ci3_2 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_GK_2);
    
    CCMenuItemSprite *pItem3 = CCMenuItemSprite::create(ci3_1,ci3_2,NULL,this, 
                                                                      menu_selector(GamePause::menuBackToGKMenuCallback));
    pItem3->setPosition( ccp(size.width*0.5,size.height*0.5 - bgSize.height*0.35) );
//	pItem3->setPosition( ccp(size.width*0.5,size.height*0.5 - bgSize.height*0.24) );
    
//    // 加入菜单    - 主菜单
//    CCSprite * ci4_1 = CCSprite::create(CONS_Image_Menu_Menu_1);
//    CCSprite * ci4_2 = CCSprite::create(CONS_Image_Menu_Menu_2);
//    
//    CCMenuItemSprite *pItem4 = CCMenuItemSprite::create(ci4_1,ci4_2,NULL,this, 
//                                                                      menu_selector(GamePause::menuBackToMainMenuCallback));
//	pItem4->setPosition( ccp(size.width*0.5,size.height*0.5 - bgSize.height*0.37) ); 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        pItem1->setScale(2.0f);
        pItem2->setScale(2.0f);
        pItem3->setScale(2.0f);
//        pItem4->setScale(2.0f);
    }
#endif
    
    CCSprite * sprBtnCommunity1;
    CCSprite * sprBtnCommunity2;
    CCMenuItemSprite *pItemCommunity;
    
    CCSprite * sprBtnRank1;
    CCSprite * sprBtnRank2;
    CCMenuItemSprite *pItemRank;
    
    // create menu, it's an autorelease object
    CCMenu* pMenu;
    
#if (IS_COMMUNITY)
    {
        sprBtnRank1 = CCSprite::createWithSpriteFrameName(CONS_IMG_PAUSE_RANK_1);
        sprBtnRank2 = CCSprite::createWithSpriteFrameName(CONS_IMG_PAUSE_RANK_2);
        pItemRank = CCMenuItemSprite::create(sprBtnRank1,sprBtnRank2,NULL,this,
                                                           menu_selector(GamePause::menuFriendsCallback));
        
        sprBtnCommunity1 = CCSprite::createWithSpriteFrameName(CONS_IMG_PAUSE_COMMUNITY_1);
        sprBtnCommunity2 = CCSprite::createWithSpriteFrameName(CONS_IMG_PAUSE_COMMUNITY_2);
        pItemCommunity = CCMenuItemSprite::create(sprBtnCommunity1,sprBtnCommunity2,NULL,this,
                                                                menu_selector(GamePause::menuCommunityCallback));
        
        if (IS_NEW_SKIN) {
            pItemRank->setAnchorPoint(ccp(0, 1));
            pItemRank->setPosition( ccp(size.width*0.5-bgSize.width*0.5, size.height*0.5 + bgSize.height*0.25) );
            
            pItemCommunity->setAnchorPoint(ccp(0, 1));
            pItemCommunity->setPosition( ccp(size.width*0.5-bgSize.width*0.5, size.height*0.5 + bgSize.height*0.43) );
        }
        else
        {
            pItemRank->setAnchorPoint(ccp(1, 1));
            pItemRank->setPosition( ccp(size.width*0.5+bgSize.width*0.52, size.height*0.5 + bgSize.height*0.49) );
            
            pItemCommunity->setAnchorPoint(ccp(0, 1));
            pItemCommunity->setPosition( ccp(size.width*0.5-bgSize.width*0.52, size.height*0.5 + bgSize.height*0.49) );
        }
        
        pMenu = CCMenu::create(pItem1,pItem2,pItem3, pItemCommunity, pItemRank, NULL);
    }
#else
    {
        pMenu = CCMenu::create(pItem1,pItem2,pItem3,NULL);
    }
#endif
    
    
//	CCMenu* pMenu = CCMenu::create(pItem1,pItem2,pItem3,pItem4,NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 3);
    
    this->setVisible(false);
    
	return true;
}

void GamePause::onExit()
{
    bjSprite->release();
    CCLayerColor::onExit();
}

void GamePause::Pause()
{
    cocos2d::CCDirector::sharedDirector()->pause();
    ((GameMenu *)this->getParent())->onPause();
    Renew();
    this->setVisible(true);
}

void GamePause::Renew()
{
    char str[512];
    
    GUAN_KA gk = CommonFunction::GetGuanKa(GetIntegerToXML(UD_CurrentGuanKa));
    
    
    sprintf(str,CONS_STRING_DJG,gk.nId,gk.nName);
    pLabel1->setString(str);
    
    
    GUANKA_STATS gkStats = CommonFunction::GetGuanKaStats(gk.nId);
    
    sprintf(str,CONS_STRING_CGJD,
            gkStats.nSet,
            gkStats.nScore,
            gk.conditionOne.nScore,
            gkStats.nFan,
            gk.conditionOne.nFanNum,
            gkStats.nJiPin,
            gk.conditionOne.nChaoHuNum);
    pLabel2->setString(str);
    
    _lCash = GetIntegerToXML(UD_SINGLE_COIN);
    sprintf(str,CONS_STRING_CASH,_lCash);
    pLabel3->setString(str);
}

//#pragma mark -----------------------菜单动作----------------------

void GamePause::menuResumeCallback(CCObject* pSender)
{
    this->setVisible(false);
    cocos2d::CCDirector::sharedDirector()->resume();
    ((GameMenu *)this->getParent())->onResume();
}

void GamePause::menuReGKCallback(CCObject* pSender)
{

    //单机游戏币更新
//    long lCoin = GetIntegerToXML(UD_SINGLE_COIN);
    if (!CommonFunction::IsEnoughCoin())
    {
        //paddy test 提示充值
        CCLOG("***** no coin *****");
        this->setVisible(false);
        ((GameMenu *)this->getParent())->ShowNoCoinMessage(true);
        return;
    }
    
    this->setVisible(false);
    ((GameMenu *)this->getParent())->ShowReGKMessage();
}

void GamePause::menuBackToGKMenuCallback(CCObject* pSender)
{
//    handleBackToGuankaMenu();
    
    if (!_bIsPlaying || _nStatus == StatusPlayerHu)
    {
        handleBackToGuankaMenu();
    }
    else
    {
        this->setVisible(false);
        ((GameMenu *)this->getParent())->ShowFleeMessage(TargetGuankaMenu);
    }

}

void GamePause::menuBackToMainMenuCallback(CCObject* pSender)
{
//    handleBackToMainMenu();
    
    if (!_bIsPlaying || _nStatus == StatusPlayerHu)
    {
        handleBackToMainMenu();
    }
    else
    {
        this->setVisible(false);
        ((GameMenu *)this->getParent())->ShowFleeMessage(TargetMainMenu);
    }
}

void GamePause::handleBackToMainMenu()
{
    cocos2d::CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}

void GamePause::handleBackToGuankaMenu()
{
    cocos2d::CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->replaceScene(LoadingScene::scene(TargetSceneGuanKaScene));

}

void GamePause::handleRestartGuanka()
{
    CCLOG("handleRestartGuanka()");
    
    //单机游戏币更新
//    long lCoin = GetIntegerToXML(UD_SINGLE_COIN);
    if (!CommonFunction::IsEnoughCoin())
    {
        //paddy test 提示充值
        CCLOG("***** no coin *****");
        this->setVisible(false);
        //重新开始关卡前，清除游戏进度数据
        CommonFunction::ClearGuanKaSaveData(GetIntegerToXML(UD_CurrentGuanKa,0));
        handleBackToGuankaMenu();
    }
    else
    {
        cocos2d::CCDirector::sharedDirector()->resume();
        //重新创建电脑玩家
        CommonFunction::CreatePlayersByGuan(GetIntegerToXML(UD_CurrentGuanKa,0));
        //重新开始关卡前，清除游戏进度数据
        CommonFunction::ClearGuanKaSaveData(GetIntegerToXML(UD_CurrentGuanKa,0));
        CCDirector::sharedDirector()->replaceScene(LoadingScene::scene(TargetSceneGameScene));
    }
}


void GamePause::SetPlaying(bool bPlaying)
{
    _bIsPlaying = bPlaying;
}

void GamePause::SetStatus(int nStatus)
{
    _nStatus = nStatus;
}

void GamePause::menuCommunityCallback(CCObject* pSender)
{
	CommonFunction::callEgameAPI(API_ID_START_EGAME, 0);
}

void GamePause::menuFriendsCallback(CCObject* pSender)
{
    
	CommonFunction::callEgameAPI(API_ID_VIEW_RANK, 0);
}