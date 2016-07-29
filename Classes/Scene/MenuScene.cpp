//
//  MenuScene.cpp
//  xzdd
//
//  Created by  on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "LoadingScene.h"
#include "SetScene.h"
#include "HelpScene.h"
#include "PersonSetScene.h"
#include "GameMoreGameScene.h"
#include "StoreLayer.h"
//#include <pthread.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "ConstantDef.h"
#include "CommonFunction.h"
//#include "SceneNetRoom.h"
#include "IOSCommon.h"

#else 
#include "../Common/ConstantDef.h"
#include "../Common/CommonFunction.h"
//#include "Net/SceneNetRoom.h"
#endif

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MenuScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	MenuScene *layer = MenuScene::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    scene->setTag(ST_MENU);
    
	// return the scene
	return scene;
}
void * threadFunction(void * arg)
{
//    CommonFunction::sendRequest();
	return NULL;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	this->setKeypadEnabled(true);

	if(CommonFunction::isIpad()){
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultMenuFrameFile_Ipad); 
	}else {
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultMenuFrameFile);
	}

	gameMessage = GameMessage::create();
	this->addChild(gameMessage,6);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float ratioX = 1.0f;
    float ratioY = 1.0f;
    CCLOG("WinSize:%f,%f",size.width,size.height);
    //加入图片缓冲
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultMenuFrameFile); 
    
    //加入桌面背景
    bjSprite = CCSprite::create(CONS_Image_BG_MainMenu);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bjSprite->setAnchorPoint(ccp(0, 0));
#else
	bjSprite->setAnchorPoint(ccp(0.5,0.5));
    bjSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
   // float design,device;

	//design=bjSprite->getContentSize().width/ bjSprite->getContentSize().height;

	//device=size.width/size.height;

	//if(design==device){
	//	CCLog("1111111111111111111111111");
		//按高度宽度适配均可
	//	 ratioX = size.width / bjSprite->getContentSize().width;
	//	 ratioY = size.height / bjSprite->getContentSize().height;
    //     bjSprite->setScaleX(ratioX);
    //     bjSprite->setScaleY(ratioY);
        
	//}
	//else if(design>device){
		//按高度适配
	//	CCLog("222222222222222222222222");
	//	 ratioY = size.height / bjSprite->getContentSize().height;
	//	 bjSprite->setScaleX(ratioY);
    //     bjSprite->setScaleY(ratioY);
	//}
	//else if(design<device){
		//按宽度适配
	//	CCLog("3333333333333333333333333");
	//	 ratioX = size.width / bjSprite->getContentSize().width;
	//	 bjSprite->setScaleX(ratioX);
    //     bjSprite->setScaleY(ratioX);
	//}
#endif
    
    this->addChild(bjSprite,0);
    
	// 加入菜单    - 单机闯关
    CCSprite * ci1_1 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_DJCG_1);
    CCSprite * ci1_2 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_DJCG_2);
    
    CCMenuItemSprite *pItemStartSingle = CCMenuItemSprite::create(ci1_1,ci1_2,NULL,this, 
                                                                      menu_selector(MenuScene::menuSingleSceneCallback));
	pItemStartSingle->setPosition( ccp(size.width*0.69,
                             size.height*0.68) );

    
	// 加入菜单    - 联网模式(登录账号)
    CCSprite * ci2_1 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Net_1);
    CCSprite * ci2_2 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Net_2);
    
    CCMenuItemSprite *pItemNetLogin = CCMenuItemSprite::create(ci2_1,ci2_2,NULL,this, 
                                                                      menu_selector(MenuScene::menuNetSceneCallback));
	pItemNetLogin->setPosition( ccp(size.width*0.69,
                             size.height*0.53) );

    // 加入菜单    - 游戏设置
    CCSprite * ci3_1 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Set_1);
    CCSprite * ci3_2 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Set_2);
    
    CCMenuItemSprite *pItemSetting = CCMenuItemSprite::create(ci3_1,ci3_2,NULL,this, 
                                                                      menu_selector(MenuScene::menuSetSceneCallback));
	pItemSetting->setPosition( ccp(size.width*0.69,
                             size.height*0.38) );

    // 加入菜单    - 帮助
    CCSprite * ci4 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Help);
    CCSprite * ci4_2 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Help_2);
    
    CCMenuItemSprite *pItemHelp = CCMenuItemSprite::create(ci4,ci4_2,NULL,this, 
                                                                      menu_selector(MenuScene::menuHelpSceneCallback));
	pItemHelp->setPosition( ccp(size.width*0.62,
                             size.height*0.15) );

    
    // 加入菜单    - 更多游戏
    CCSprite * ci5 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_MoreGames);
    CCSprite * ci5_2 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_MoreGames_2);
    
    CCMenuItemSprite *pItemMore = CCMenuItemSprite::create(ci5,ci5_2,NULL,this, 
                                                                      menu_selector(MenuScene::menuMoreGameCallback));
	pItemMore->setPosition( ccp(size.width*0.75,
                             size.height*0.15) );

    
//     // 加入头像菜单    - 用户设置
    CCSprite * ci6 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Ico);
//     
//     CCMenuItemSprite *pItemFace = CCMenuItemSprite::create(ci6,NULL,NULL,this,
//                                                                       menu_selector(MenuScene::menuPersonSetCallback));
// 	pItemFace->setPosition( ccp(size.width*0.28,
//                              size.height*0.57) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        pItemStartSingle->setScale(2.0f);
        pItemNetLogin->setScale(2.0f);
        pItemSetting->setScale(2.0f);
        pItemHelp->setScale(2.0f);
        pItemMore->setScale(2.0f);
        pItemFace->setScale(2.0f);
    }
#endif

	CCSprite* ci7 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Store1);
	CCSprite* ci8 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Store2);
    
    CCSprite * sprBtnCommunity1;
    CCSprite * sprBtnCommunity2;
    CCMenuItemSprite *pItemCommunity;

	CCMenuItemSprite *pStore;
    
    CCSprite * sprBtnRank1;
    CCSprite * sprBtnRank2;
    CCMenuItemSprite *pItemRank;
    
    // create menu, it's an autorelease object
    CCMenu* pMenu;
	    
    if (IS_LOCAL)  //if单机版
    {
        pItemNetLogin->setVisible(false);
        if (IS_COMMUNITY || IS_NON_EGAME)        //if单机-if社区||外部渠道
        {
#if IS_SPRING      //if单机-if社区||外部渠道-if春节活动
            CCSprite * sprBtnSpring1;
            CCSprite * sprBtnSpring2;
            CCMenuItemSprite *pItemSpring;
            
            sprBtnRank1 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_RANK_1);
            sprBtnRank2 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_RANK_2);
            pItemRank = CCMenuItemSprite::create(sprBtnRank1,sprBtnRank2,NULL,this,
                                                               menu_selector(MenuScene::menuFriendsCallback));
            pItemRank->setAnchorPoint(ccp(1, 1));
            pItemRank->setPosition( ccp(size.width*0.95,
                                        size.height*0.92) );
            
            sprBtnSpring1 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_SPRING_1);
            sprBtnSpring2 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_SPRING_2);
            pItemSpring = CCMenuItemSprite::create(sprBtnSpring1,sprBtnSpring2,NULL,this,
                                                                 menu_selector(MenuScene::menuSpringCallback));
            pItemSpring->setPosition( ccp(size.width*0.69,
                                          size.height*0.31) );

			pStore = CCMenuItemSprite::create( ci7, ci8, NULL, this, menu_selector( MenuScene::menuStoreCallback ) );
			pStore->setPosition( ccp( size.width*0.69,
				size.height*0.21) );

            sprBtnCommunity1 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_COMMUNITY_1);
            sprBtnCommunity2 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_COMMUNITY_2);
            pItemCommunity = CCMenuItemSprite::create(sprBtnCommunity1,sprBtnCommunity2,NULL,this,
                                                                    menu_selector(MenuScene::menuCommunityCallback));
            pItemCommunity->setPosition( ccp(size.width*0.69,
                                             size.height*0.44) );
            
            pMenu = CCMenu::create(pItemStartSingle, pItemSetting, pItemHelp, pItemMore, pItemFace, pItemSpring, pItemCommunity, pItemRank, NULL);
            
            pItemStartSingle->setPosition( ccp(size.width*0.69,
                                          size.height*0.70) );
            
            pItemSetting->setPosition( ccp(size.width*0.69,
                                     size.height*0.57) );
#elif IS_NEW_SKIN      //if单机-if社区||外部渠道-if换肤
            if(IS_COMMUNITY)       //if单机-if社区-if换肤
            {
                sprBtnRank1 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_RANK_1);
                sprBtnRank2 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_RANK_2);
                pItemRank = CCMenuItemSprite::create(sprBtnRank1,sprBtnRank2,NULL,this,
                                                                   menu_selector(MenuScene::menuFriendsCallback));
                
                sprBtnCommunity1 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_COMMUNITY_1);
                sprBtnCommunity2 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_COMMUNITY_2);
                pItemCommunity = CCMenuItemSprite::create(sprBtnCommunity1,sprBtnCommunity2,NULL,this,
                                                                        menu_selector(MenuScene::menuCommunityCallback));

				pStore = CCMenuItemSprite::create( ci7, ci8, NULL, this, menu_selector( MenuScene::menuStoreCallback ) );

                
                pItemStartSingle->setAnchorPoint(ccp(0.5, 0));
                pItemSetting->setAnchorPoint(ccp(0.5, 0));
                pItemRank->setAnchorPoint(ccp(0.5, 0));
                pItemCommunity->setAnchorPoint(ccp(0.5, 0));
                pItemHelp->setAnchorPoint(ccp(0.5, 0));
				pStore->setAnchorPoint(ccp(0.5f,0));
                
                pItemMore->setAnchorPoint(ccp(1, 1));
                
                
                pItemStartSingle->setPosition( ccp(size.width*0.5,
                                                   size.height*0.025) );
                
                pItemSetting->setPosition( ccp(size.width*0.325,
                                               size.height*0.1) );
                pItemRank->setPosition( ccp(size.width*0.675,
                                            size.height*0.1) );
                
                pItemCommunity->setPosition( ccp(size.width*0.15,
                                                 size.height*0.175) );
                pItemHelp->setPosition( ccp(size.width*0.85,
                                            size.height*0.175) );
                
                pItemMore->setPosition( ccp(size.width*0.96,
                                            size.height) );

				pStore->setPosition( ccp( size.width*0.5,
					size.height*0.21) );
                
                pMenu = CCMenu::create(pItemStartSingle, pItemSetting, pItemHelp, pItemMore, pItemCommunity, pItemRank, pStore, NULL);
            }
            else        //if单机-if非社区&&外部渠道-if换肤
            {
				pStore = CCMenuItemSprite::create( ci7, ci8, NULL, this, menu_selector( MenuScene::menuStoreCallback ) );
                pItemStartSingle->setAnchorPoint(ccp(0.5, 0));
                pItemSetting->setAnchorPoint(ccp(0.5, 0));
                pItemHelp->setAnchorPoint(ccp(0.5, 0));
				pStore->setAnchorPoint(ccp(0.5,0));
                
                pItemStartSingle->setPosition( ccp(size.width*0.5,
                                                   size.height*0.3) );
                
                pItemSetting->setPosition( ccp(size.width*0.25,
                                               size.height*0.15) );

				
				pStore->setPosition( ccp( size.width*0.5,
					size.height*0.05) );
                
                pItemHelp->setPosition( ccp(size.width*0.75,
                                            size.height*0.15) );
                
                if (IS_SHOW_MOREGAME) {
                    pItemMore->setAnchorPoint(ccp(1, 1));
                    pItemMore->setPosition( ccp(size.width*0.96,
                                                size.height) );
                    pMenu = CCMenu::create(pItemStartSingle, pItemSetting, pItemHelp, pItemMore, pStore, NULL);
                }
                else{
                    pMenu = CCMenu::create(pItemStartSingle, pItemSetting, pItemHelp, pStore, NULL);
                }
            }
#else   //if单机-if社区||外部渠道-if非春节&&非换肤
            sprBtnRank1 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_RANK_1);
            sprBtnRank2 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_RANK_2);
            pItemRank = CCMenuItemSprite::create(sprBtnRank1,sprBtnRank2,NULL,this,
                                                               menu_selector(MenuScene::menuFriendsCallback));
            pItemRank->setAnchorPoint(ccp(1, 1));
            pItemRank->setPosition( ccp(size.width*0.95,
                                        size.height*0.92) );
            
//            sprBtnSpring1 = CCSprite::create(CONS_IMG_MENU_SPRING_1);
//            sprBtnSpring2 = CCSprite::create(CONS_IMG_MENU_SPRING_2);
//            pItemSpring = CCMenuItemSprite::create(sprBtnSpring1,sprBtnSpring2,NULL,this,
//                                                                 menu_selector(MenuScene::menuSpringCallback));
//            pItemSpring->setPosition( ccp(size.width*0.69,
//                                          size.height*0.31) );
            
            sprBtnCommunity1 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_COMMUNITY_1);
            sprBtnCommunity2 = CCSprite::createWithSpriteFrameName(CONS_IMG_MENU_COMMUNITY_2);
            pItemCommunity = CCMenuItemSprite::create(sprBtnCommunity1,sprBtnCommunity2,NULL,this,
                                                                    menu_selector(MenuScene::menuCommunityCallback));
            pItemCommunity->setPosition( ccp(size.width*0.69,
                                             size.height*0.44) );
            
            pMenu = CCMenu::create(pItemStartSingle, pItemSetting, pItemHelp, pItemMore, pItemFace, pItemCommunity, pItemRank, NULL);
            
            pItemStartSingle->setPosition( ccp(size.width*0.69,
                                     size.height*0.70) );
            
            pItemSetting->setPosition( ccp(size.width*0.69,
                                     size.height*0.57) );
#endif
        }
        else        //if单机-if非社区&&非外部渠道
        {
            if (IS_NEW_SKIN)       //if单机-if非社区&&非外部渠道-if换肤
            {
                pItemStartSingle->setAnchorPoint(ccp(0.5, 0));
                pItemSetting->setAnchorPoint(ccp(0.5, 0));
                pItemHelp->setAnchorPoint(ccp(0.5, 0));
                
                pItemStartSingle->setPosition( ccp(size.width*0.5,
                                                   size.height*0.3) );
                
                pItemSetting->setPosition( ccp(size.width*0.25,
                                               size.height*0.15) );
                
                pItemHelp->setPosition( ccp(size.width*0.75,
                                            size.height*0.15) );
                
                
                if (IS_SHOW_MOREGAME) {
                    pItemMore->setAnchorPoint(ccp(1, 1));
                    pItemMore->setPosition( ccp(size.width*0.96,
                                                size.height) );
                    pMenu = CCMenu::create(pItemStartSingle, pItemSetting, pItemHelp, pItemMore, NULL);
                }
                else{
                    pMenu = CCMenu::create(pItemStartSingle, pItemSetting, pItemHelp, NULL);
                }
            }
            else           //if单机-if非社区&&非外部渠道-if非换肤
            {
                pMenu = CCMenu::create(pItemStartSingle,pItemNetLogin,pItemSetting,pItemHelp,pItemMore, NULL);
                
                pItemStartSingle->setPosition( ccp(size.width*0.69,
                                                   size.height*0.6) );
                pItemSetting->setPosition( ccp(size.width*0.69,
                                               size.height*0.4) );
            }
        }
        
#if !IS_NEW_SKIN
        CCSprite * infoTitle = CCSprite::createWithSpriteFrameName(CONS_IMG_INFO_TITLE_SINGLE);
        infoTitle->setPosition( ccp(size.width*0.22,
                              size.height*0.34) );
        this->addChild(infoTitle,3);
#endif

    }
    else
    {
        CCSprite * sprBtnStart1;
        CCSprite * sprBtnStart2;
        CCMenuItemSprite *pItemStart;
        
        sprBtnStart1 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_DJCG_1);
        sprBtnStart2 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_DJCG_2);
        pItemStart = CCMenuItemSprite::create(sprBtnStart1,sprBtnStart2,NULL,this,
                                                            menu_selector(MenuScene::menuQuickStartCallback));
        pMenu = CCMenu::create(pItemNetLogin,pItemStart,pItemHelp,pItemMore, NULL);
        //        pMenu = CCMenu::create(pItemNetLogin,pItemSetting,pItemHelp,pItemMore,pItemFace, NULL);
        
        pItemStart->setPosition( ccp(size.width*0.69,
                                     size.height*0.6) );
        pItemNetLogin->setPosition( ccp(size.width*0.69,
                                        size.height*0.4) );
        
        CCSprite * infoTitle = CCSprite::createWithSpriteFrameName(CONS_IMG_INFO_TITLE_NEWWORK);
        infoTitle->setPosition( ccp(size.width*0.20,
                                    size.height*0.34) );
        this->addChild(infoTitle,3);
    }
    
    pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

    
    //加入个人信息
	PLAYER user = CommonFunction::GetUser();
    if(user.nId != 0)
    {
        CCSprite * ico = CCSprite::createWithSpriteFrameName(user.nIco);
        ico->setPosition( ccp(size.width*0.28,
                              size.height*0.57) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if(IOSCommon::IsIpad3())
        {
            ico->setScale(2.0f);
        }
#endif

        if (CommonFunction::isIpad()) {
            ico->setPosition( ccp(size.width*0.29,
                                  size.height*0.57) );
        }
        this->addChild(ico,2,2);
    }
    else{
//         CCAction * m_flash = CCRepeatForever::create(
//                                                                (CCActionInterval*)CCSequence::create(
//                                                                                                       CCFadeOut::create(0.5),
//                                                                                                       CCFadeIn::create(1),
//                                                                                                       0
//                                                                                                       ));
//         ci6->runAction(m_flash);
    }
    CCLabelTTF* nameLabel = CCLabelTTF::create((user.nId != 0) ? user.nName : "?", "Arial", CommonFunction::GetValueByDev(13));
    nameLabel->setPosition( ccp(size.width*0.32,
                                size.height*0.40) ); 
    
    
    //加入积分信息
    CCLabelTTF* sourceLabel = CCLabelTTF::create("", "Arial", CommonFunction::GetValueByDev(13));
    
    if (IS_LOCAL)
    {
		int	day = GetIntegerToXML( UD_SINGLE_TIMER );
		//判断日期来领取当日奖励
		if ( day != CurrentTimeNow() )
		{
			gameMessage->SetMessageType( MT_RECEIVE_COIN );
			SetIntegerToXML( UD_SINGLE_TIMER, CurrentTimeNow() );
			CommonFunction::AddCoin( 2000 );
		}
		//yuri test
		gameMessage->SetMessageType( MT_RECEIVE_COIN );

        long score = GetIntegerToXML(UD_SINGLE_COIN, COIN_NUM_GIVEN);
        char temp[20];
        sprintf(temp, "%ld", score);
        sourceLabel->setString(temp);
        sourceLabel->setPosition( ccp(size.width*0.32,
                                      size.height*0.28) );

		
    }
    else{
        if (GetBoolToXML(UD_User_Room_Logoned, false)) {
            sourceLabel->setString(GetStringToXML(UD_User_Last_Score, "").c_str());
        }else {
            sourceLabel->setString(CONS_STRING_NetTemp);
        }
        sourceLabel->setPosition( ccp(size.width*0.32,
                                      size.height*0.34) );
    }
    
    
    //显示玩家级别
    CCLabelTTF* djLabel;
    if (IS_LOCAL) {
        string gkName = CommonFunction::GetGkNameByIndex(GetIntegerToXML(UD_CurrentGuanKa,1));
        djLabel = CCLabelTTF::create(gkName.c_str(), "Verdana", CommonFunction::GetValueByDev(13));
        djLabel->setPosition( ccp(size.width*0.32,
                                  size.height*0.34) );
                
        if (CommonFunction::isIpad()) {
            djLabel->setPosition( ccp(size.width*0.33,
                                      size.height*0.33) );
        }
    }else{
        char * dengji = CommonFunction::GetMaxFanCJName();
        if (dengji != NULL) {
            djLabel = CCLabelTTF::create(dengji, "Verdana", CommonFunction::GetValueByDev(13));
            djLabel->setPosition( ccp(size.width*0.32,
                                      size.height*0.28) );
            
            if (CommonFunction::isIpad()) {
                djLabel->setPosition( ccp(size.width*0.33,
                                          size.height*0.33) );
            }
        }
    }
    
    if (!IS_NEW_SKIN) {
        this->addChild(nameLabel);
        this->addChild(sourceLabel);
        this->addChild(djLabel);

    }
    
    if(CommonFunction::isIpad()){
        nameLabel->setPosition( ccp(size.width*0.33,
                                    size.height*0.44) ); 
        sourceLabel->setPosition( ccp(size.width*0.33,
                                      size.height*0.385) ); 
        
        pItemStartSingle->setPosition( ccp(size.width*0.68,
                                 size.height*0.66) ); 
        pItemNetLogin->setPosition( ccp(size.width*0.68,
                                 size.height*0.53) ); 
        pItemSetting->setPosition( ccp(size.width*0.68,
                                 size.height*0.40) ); 
        pItemHelp->setPosition( ccp(size.width*0.61,
                                 size.height*0.22) ); 
        pItemMore->setPosition( ccp(size.width*0.74,
                                 size.height*0.22) ); 
//         pItemFace->setPosition( ccp(size.width*0.29,
//                                  size.height*0.57) ); 
    }
    
    if (ISANDROID)
    {
        if (!CommonFunction::isValidAndroidSysVer()) {
//             gameMessage = LayerNetGameMessage::create();
//             gameMessage->SetMessageType(NMT_LowAndroidVer, "本游戏要求Android系统版本不低于2.2,请先升级");
//             gameMessage->SetStatus(UI_Menu);
//             addChild(gameMessage,8);
        }
    }

	static bool bAppIsRun = false;
	if (!bAppIsRun)
	{
		CommonFunction::addMarketLog();
		bAppIsRun = true;
	}
    
//    //如果已经记录的版本和当前版本不一致
//     if (strcmp(GetStringToXML(UD_RecordVersion,"").c_str(),CONS_Version) != 0){
//         if (ISANDROID){
//             CommonFunction::sendRequest();
//         }else{
//             if(pthread_kill(pthId, 0) != 0){
//                 pthread_create(&pthId, NULL, threadFunction, NULL);
//             }
//         }
//     }
//    
	//lyp 注释
//	if (ISANDROID && (PLAT_ID == 92)) {
//		//如果已经记录的版本和当前版本不一致 FOR ANDROID 畅想无限
//		if (strcmp(GetStringToXML(UD_RecordVersion_CXWX,"").c_str(),CONS_Version) != 0){
//			CommonFunction::sendAndroidRequestCXWX();
//		}
//	}
    
    if (GetBoolToXML(UD_IsFirstRun, true))
    {
        CCLOG("*****App First Run*****");
        SetBoolToXML(UD_IsFirstRun,false);
        SetIntegerToXML(UD_SINGLE_COIN, COIN_NUM_GIVEN + 2000);
        
//         //加入splash层
//         splashLayer = SplashLayer::create();
//         this->addChild(splashLayer,11);
// //        bIsInSplash = true;
    }
    
#if IS_FREE_ACTIVATE
    if (!GetBoolToXML(UD_GUANKA_OPEN, false)) {
        SetBoolToXML(UD_GUANKA_OPEN, true);
    }
#endif
    
//    //加入splash层
//    splashLayer = SplashLayer::create();
//    this->addChild(splashLayer,11);
////    bIsInSplash = false;
    
    return true;
}

void MenuScene::onExit()
{
//    bjSprite->release();
    CCLayer::onExit();
}

void MenuScene::menuSingleSceneCallback(CCObject* pSender)
{
//    if (bIsInSplash)
//    {
//        return;
//    }
	CCDirector::sharedDirector()->replaceScene(LoadingScene::scene(TargetSceneGuanKaScene));
}
void MenuScene::menuNetSceneCallback(CCObject* pSender)
{
//    if (bIsInSplash)
//    {
//        return;
//    }
//	CCDirector::sharedDirector()->replaceScene(SceneNetRoom::scene());
}
void MenuScene::menuSetSceneCallback(CCObject* pSender)
{
//    if (bIsInSplash)
//    {
//        return;
//    }
	CCDirector::sharedDirector()->replaceScene(SetScene::scene());
}
void MenuScene::menuHelpSceneCallback(CCObject* pSender)
{
//    if (bIsInSplash)
//    {
//        return;
//    }
	CCDirector::sharedDirector()->replaceScene(HelpScene::scene());
}
void MenuScene::menuPersonSetCallback(CCObject* pSender)
{
//    if (bIsInSplash)
//    {
//        return;
//    }
	CCDirector::sharedDirector()->replaceScene(PersonSetScene::create());
}

// void MenuScene::menuSplashEntranceCallback(CCObject* pSender)
// {
// //	CCDirector::sharedDirector()->replaceScene(PersonSetScene::create());
//     splashLayer->setVisible(false);
//     this->removeChild(splashLayer, true);
//     CCLOG("enter game menu");
// //    bIsInSplash = false;
// }

void MenuScene::keyBackClicked(){
	CCDirector::sharedDirector()->end();
}

void MenuScene::onConfirm(NetMessageType mType){
    if (mType == NMT_LowAndroidVer) {
        CCDirector::sharedDirector()->end();
    }
}

void MenuScene::menuMoreGameCallback(CCObject* pSender)
{
//    if (bIsInSplash)
//    {
//        return;
//    }
	if (!ISANDROID) {
		CCDirector::sharedDirector()->replaceScene(GameMoreGameScene::create());
    }
    else
    {
        if (IS_COMMUNITY)
        {
            CommonFunction::callEgameAPI(API_ID_VIEW_MORE, 1);
        }
        else
        {
            //CCDirector::sharedDirector()->replaceScene(NewLoadingScene::scene(kSceneMoreGame));
            if (IS_PLUGIN) {
                char a[100]="http://game.189.cn";
                CommonFunction::openURL(a, 1);
            }else{
                CommonFunction::openHall();
            }

        }
    }
}

void MenuScene::menuSpringCallback(CCObject* pSender)
{
    char a[100]="http://game.189.cn/hd/2013dl";
    CommonFunction::openURL(a, 2);
}

void MenuScene::menuCommunityCallback(CCObject* pSender)
{
	CommonFunction::callEgameAPI(API_ID_START_EGAME, 0);
}

void MenuScene::menuFriendsCallback(CCObject* pSender)
{
    
	CommonFunction::callEgameAPI(API_ID_VIEW_RANK, 0);
}

void MenuScene::menuQuickStartCallback(CCObject* pSender)
{
	
}

int MenuScene::CurrentTimeNow()
{
	struct tm *tm;
	time_t timep;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	time(&timep);
#else
	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	timep = now.tv_sec;
#endif


	tm = localtime(&timep);
	int year = tm->tm_year + 1900;
	int month = tm->tm_mon + 1;
	int day = tm->tm_mday;
	int hour=tm->tm_hour;
	int min=tm->tm_min;
	int second=tm->tm_sec;

	CCLOG( "%d年，%d月，%d日，%d时，%d分，%d秒", year, month, day, hour, min, second );

	return day;
}

void MenuScene::menuStoreCallback( CCObject* pSender )
{
	CStoreLayer* pLayer = CStoreLayer::create();
	this->addChild( pLayer, 999 );
}



