//
//  GuanKaScene.cpp
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GuanKaScene.h"
#include "MenuScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSCommon.h"
#endif

using namespace cocos2d;
#define CONVERT_XY(X,Y,W,H) ccp((W)*((X)/1138.0),(H)*((640.0-(Y))/640.0))
cocos2d::CCScene* scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();	
    
	// return the scene
	return scene;
}
// on "init" you need to initialize your instance
bool GuanKaScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    this->setTag(ST_MENU);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrame * spriteFrame;
    CCSprite *bg;
    CCSprite *title;
    
    if (CommonFunction::isIpad()) {
        spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_DefaultGkFrameFile_Ipad);
        if(spriteFrame == NULL){
            //加入图片缓冲
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultGkFrameFile_Ipad);
        }
        bg = CCSprite::create(CONS_Image_GK_BG_Ipad);//关卡屏背景
    }else {
        spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_DefaultGkFrameFile);
        if(spriteFrame == NULL){
            //加入图片缓冲
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultGkFrameFile);
        }
        bg = CCSprite::create(CONS_Image_GK_BG);//关卡屏背景
    }
    
	bg->setPosition( ccp(winSize.width / 2, winSize.height /2) );
	bg->setVisible(true);
	this->addChild(bg, 0,0);
    
//#if IS_NEW_SKIN
//    title = CCSprite::create(CONS_Image_GK_Xz_Text);
//    title->setPosition( ccp(winSize.width*0.5, winSize.height*0.925) );
//	title->setVisible(true);
//	this->addChild(title, 3);
//#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        bg->setAnchorPoint(ccp(0.5f,0.5f));
        bg->setPosition(ccp(winSize.width / 2.0f, winSize.height / 2.0f));
        bg->setScale(2.0f);
    }
#endif
    
    //加入关卡层
	guanKaLayer = GuanKaLayer::create();  
	this->addChild(guanKaLayer,1,1);
    
    //成就说明层
	cjLayer = GameCjLayer::create();
    cjLayer->setTouchEnabled(false);
    cjLayer->setVisible(false);
	this->addChild(cjLayer,1,1);
    
    //关卡说明层
    infoLayer = GkInfoLayer::create();
    infoLayer->setTouchEnabled(false);
    infoLayer->setVisible(false);
	this->addChild(infoLayer,1,1);

    CCSprite *cj = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Cj);//成就按钮
    CCSprite *cj2 = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Cj_2);//成就按钮

	CCMenuItemSprite *pCjItem = CCMenuItemSprite::create(cj, cj2, this,
                                                                       menu_selector(GuanKaScene::menuCjSceneCallback));
	//pCjItem->setPosition( ccp(winSize.width*0.875, winSize.height*0.66) );
	//pCjItem->setAnchorPoint(ccp(0.5, 0.5));
	//CCLog("the guankaKuang->getContentSize() is %d",guankaKuang->getContentSize().width );
	//pCjItem->setPosition( ccp(1210*0.825,  winSize.height*0.66) );
	pCjItem->setPosition( ccp((winSize.width/2 + 480)*0.893, winSize.height*0.66));
	pCjItem->setVisible(true);
    
	CCSprite *gkInfo = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Info);//关卡说明按钮
    CCSprite *gkInfo2 = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Info_2);
    
	CCMenuItemSprite *pGkInfoItem = CCMenuItemSprite::create(gkInfo, gkInfo2, this,
                                                                           menu_selector(GuanKaScene::menuGkInfoSceneCallback));
	//pGkInfoItem->setPosition( ccp(winSize.width*0.875, winSize.height*0.42) );
	//pGkInfoItem->setAnchorPoint(ccp(0.5, 0.5));
	pGkInfoItem->setPosition( ccp((winSize.width/2 + 480)*0.893, winSize.height*0.42) );
	pGkInfoItem->setVisible(true);
    
	CCSprite *ret = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Return);//返回按钮
	CCSprite *retSelected = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Return_2);
    
	CCMenuItemSprite *pItem = CCMenuItemSprite::create(ret, retSelected, this,
                                                                     menu_selector(GuanKaScene::menuBackCallback));
	//pItem->setPosition( ccp(winSize.width*0.875, winSize.height*0.18) ); 
	pItem->setAnchorPoint(ccp(0.5, 0.5));
	pItem->setPosition( ccp((winSize.width/2 + 480)*0.893, winSize.height*0.18) ); 
	pItem->setVisible(true);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        pCjItem->setScale(2.0f);
        pGkInfoItem->setScale(2.0f);
        pItem->setScale(2.0f);
    }
#endif
    
//    //加入message层
//    pGameMessage = GameMessage::create();
//    this->addChild(pGameMessage,4);
    CCSprite *delock1;//按钮
    CCSprite *delock2;//按钮
	CCMenuItemSprite *pDelockItem;
    
    delock1 = CCSprite::createWithSpriteFrameName(CONS_IMG_GK_DELOCK_1);
    delock2 = CCSprite::createWithSpriteFrameName(CONS_IMG_GK_DELOCK_2);
    
    pDelockItem = CCMenuItemSprite::create(delock1, delock2, this,
                                                       menu_selector(GuanKaScene::menuDelockCallback));
    //pDelockItem->setPosition( ccp(winSize.width*0.1065, winSize.height*0.66) );
	//pDelockItem->setAnchorPoint(ccp(0.5, 0.5));
	pDelockItem->setPosition( ccp((winSize.width/2 - 380)*0.996, winSize.height*0.66) );

    if(GetBoolToXML(UD_GUANKA_DELOCK, false))
    {
        pDelockItem->setVisible(false);
    }
    else
    {
        pDelockItem->setVisible(true);
    }
    

#if (IS_COMMUNITY)
    CCSprite *rank1;//按钮
    CCSprite *rank2;//按钮
    CCMenuItemSprite *pRankItem;
    
    rank1 = CCSprite::createWithSpriteFrameName(CONS_IMG_GK_RANK_1);
    rank2 = CCSprite::createWithSpriteFrameName(CONS_IMG_GK_RANK_2);
    
    pRankItem = CCMenuItemSprite::create(rank1, rank2, this,
                                                       menu_selector(GuanKaScene::menuRankCallback));
    pRankItem->setAnchorPoint(ccp(1,1));
    pRankItem->setVisible(true);
    
    if (IS_NEW_SKIN) {
        pRankItem->setPosition( ccp(winSize.width*0.95, winSize.height) );
    }
    else
    {
        pRankItem->setPosition( ccp(winSize.width, winSize.height*0.9) );
    }
    
    pMenu = CCMenu::create(pCjItem,pGkInfoItem,pItem,pRankItem,pDelockItem,NULL);
#else
    pMenu = CCMenu::create(pCjItem,pGkInfoItem,pItem,pDelockItem,NULL);
#endif
	pMenu->setAnchorPoint(ccp(0, 0));
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 3);

//    //加入message层
//    pGuankaMessage = GuanKaMessage::create();
//    this->addChild(pGuankaMessage,4);
    
    if (CommonFunction::isIpad()) {
        pCjItem->setPosition( ccp(winSize.width*0.85, winSize.height*0.58) ); 
        pGkInfoItem->setPosition( ccp(winSize.width*0.85, winSize.height*0.40) ); 
        pItem->setPosition( ccp(winSize.width*0.85, winSize.height*0.22) ); 
    }
    
    bool bGkOpen = GetBoolToXML(UD_GUANKA_OPEN, false);
    bool bPassGk1 = GetBoolToXML(UD_PASS_GUANKA_1, false);
    
#if !IS_NEW_GK_CONDITION
    if (!bGkOpen && bPassGk1)
    {
        guanKaLayer->ShowOpenAllGuanka(1);
    }
#else
    bool bPassGk3 = GetBoolToXML(UD_PASS_GUANKA_3, false);
    if (!bGkOpen && bPassGk3)
    {
        guanKaLayer->ShowOpenAllGuanka(1);
    }
#endif
    
//    bool bGkDelock = GetBoolToXML(UD_GUANKA_DELOCK, false);
//    if (bGkDelock) {
//        pDelockItem->setVisible(false);
//    }

    
	return true;
}

void GuanKaScene::onExit()
{
    CCScene::onExit();
}

void GuanKaScene::onBack(){
    
    if (guanKaLayer->isVisible()) {
        CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
    }
    else
    {
        guanKaLayer->setVisible(true);
        cjLayer->setVisible(false);
        infoLayer->setVisible(false);
        
        guanKaLayer->setTouchEnabled(true);
        cjLayer->setTouchEnabled(false);
        infoLayer->setTouchEnabled(false);
    }
}

void GuanKaScene::menuBackCallback(CCObject* pSender)
{
    onBack();
}

void GuanKaScene::menuCjSceneCallback(CCObject* pSender){
    guanKaLayer->setVisible(false);
    guanKaLayer->setTouchEnabled(false);
    cjLayer->setVisible(true);
    cjLayer->setTouchEnabled(true);
    infoLayer->setVisible(false);
    infoLayer->setTouchEnabled(false);
}

void GuanKaScene::menuGkInfoSceneCallback(CCObject* pSender){
    guanKaLayer->setVisible(false);
    guanKaLayer->setTouchEnabled(false);
    cjLayer->setVisible(false);
    cjLayer->setTouchEnabled(false);
	infoLayer->setVisible(true);
	infoLayer->setTouchEnabled(true);
}

void GuanKaScene::setButtonVisible(bool isVisible)
{
    pMenu->setVisible(isVisible);
}

void GuanKaScene::menuRankCallback(CCObject* pSender)
{
    CommonFunction::callEgameAPI(API_ID_VIEW_RANK, 0);
}

void GuanKaScene::menuDelockCallback(CCObject* pSender)
{
    bool bGkOpen = GetBoolToXML(UD_GUANKA_OPEN, false);
    bool bGkDelock = GetBoolToXML(UD_GUANKA_DELOCK, false);
    if (!bGkOpen)
    {
		guanKaLayer->ShowOpenAllGuanka(2);
       // guanKaLayer->onConfirm(MT_OPEN_GUANKA);
    }
//    else if(!bGkDelock)
    else
    {
        guanKaLayer->onConfirm(MT_OPEN_GUANKA);
		//guanKaLayer->PayDelock();
    }
}
