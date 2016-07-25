//
//  GameSet.cpp
//  xzdd
//
//  Created by  on 12-4-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameSet.h"
#include "GameMenu.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "MenuScene.h"
#include "IOSCommon.h"
#else 
#include "../Scene/MenuScene.h"
#endif


using namespace cocos2d;

bool GameSet::init()
{
	//////////////////////////////
	// 1. super init first
    ccColor4B c = {0,0,0,150};
	if (!CCLayerColor::initWithColor(c) )
	{
		return false;
	}

    return true;
}
void GameSet::onExit()
{
    kuangSprite->release();
    CCLayerColor::onExit();
}
void GameSet::initWithGameType(GameType type)
{
    mType = type;
    m_gameSetType = GST_MainMenu;
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //加入游戏设置边框
    kuangSprite = new CCSprite();
    if (CommonFunction::isIpad()) {
        kuangSprite->initWithFile(CONS_Image_BG_Set_Ipad);
    }else {
        kuangSprite->initWithFile(CONS_Image_BG_Set);
    }

	kuangSprite->setPosition( ccp(winSize.width/2, winSize.height/2) );
    this->addChild(kuangSprite,1);
    
    CCSize kuangSize = kuangSprite->getContentSize();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        kuangSprite->setAnchorPoint(ccp(0.5f,0.5f));
        kuangSprite->setPosition(ccp(winSize.width / 2.0f, winSize.height / 2.0f));
        kuangSprite->setScale(2.0f);
        kuangSize = kuangSprite->boundingBox().size;
    }
#endif
    
	//加入返回按钮
	CCSprite* retSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_return);
    CCSprite* retSprite2 = CCSprite::createWithSpriteFrameName(CONS_Image_Set_return_2);
    
    CCMenuItemSprite *pItemReturn = CCMenuItemSprite::create(retSprite,retSprite2,NULL,this, 
                                                                      menu_selector(GameSet::menuBackCallback));
	pItemReturn->setPosition( ccp(winSize.width*0.81, winSize.height*0.17) ); 
    
	//音乐文字
	CCSprite* yySprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Yy_Text);    
	yySprite->setPosition( ccp(winSize.width*0.3, winSize.height*0.5 + kuangSize.height*0.3) );
	this->addChild(yySprite,2);
    
	//音效文字
	CCSprite* yxSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Yx_Text);
	yxSprite->setPosition( ccp(winSize.width*0.30, winSize.height*0.5 + kuangSize.height*0.2) );
	this->addChild(yxSprite,2); 
    
    yyProgress = SetProgress::create();
    yyProgress->SetProgressType(PT_Music);
    this->addChild(yyProgress,1,4);
    yyProgress->setPosition(ccp(winSize.width*0.52, winSize.height*0.5 + kuangSize.height*0.3));  
    
    yxProgress = SetProgress::create();
    yxProgress->SetProgressType(PT_Effect);
    this->addChild(yxProgress,1,4);
    yxProgress->setPosition(ccp(winSize.width*0.52, winSize.height*0.5 + kuangSize.height*0.2));  
    
	//---省电模式
	CCSprite* sdmsSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Sdms_Text);
	sdmsSprite->setPosition( ccp(winSize.width*0.5875, winSize.height*0.5 + kuangSize.height*0.07) );
	this->addChild(sdmsSprite,2);
    
	//省电模式选择
	sdmsSelectSprite = SelectSprite::selectWithFrameName(CONS_Image_BG_Set_Checkbox);
	if(GetBoolToXML(UD_Set_Sdms,false)){
		sdmsSelectSprite->setSelectDisplay(ST_Select);
	}else{
		sdmsSelectSprite->setSelectDisplay(ST_Unselect);
	}
    
    CCMenuItemSprite *pItemSdms = CCMenuItemSprite::create(sdmsSelectSprite,NULL,NULL,this, 
                                                                      menu_selector(GameSet::menuSetSdmsCallback));
	pItemSdms->setPosition( ccp(winSize.width*0.6937, winSize.height*0.5 + kuangSize.height*0.07) ); 
    
    if (type == GT_SingleGame) {
        //---自动登陆文字
        CCSprite* zddlSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Zddl_Text);
        zddlSprite->setPosition( ccp(winSize.width*0.325, winSize.height*0.5 + kuangSize.height*0.07) );
        if (IS_LOCAL) {
            zddlSprite->setVisible(false);
        }
        
        this->addChild(zddlSprite,2);
        
        //自动登陆
        zddlSelectSprite = SelectSprite::selectWithFrameName(CONS_Image_BG_Set_Checkbox);
        if(GetBoolToXML(UD_Set_Zddl,false)){
            zddlSelectSprite->setSelectDisplay(ST_Select);
        }else{
            zddlSelectSprite->setSelectDisplay(ST_Unselect);
        }
        CCMenuItemSprite *pItemZddl = CCMenuItemSprite::create(zddlSelectSprite,NULL,NULL,this, 
                                                                             menu_selector(GameSet::menuSetZddlCallback));
        if (IS_LOCAL) {
            pItemZddl->setVisible(false);
        }
        
        pItemZddl->setPosition( ccp(winSize.width*0.4312, winSize.height*0.5 + kuangSize.height*0.07) ); 
        
//        //todo netgame
//        pItemZddl->setVisible(false);
//        zddlSprite->setVisible(false);
        
        //---血战定缺
        CCSprite* xzdqSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Xzdq_Text);
        xzdqSprite->setPosition( ccp(winSize.width*0.325, winSize.height*0.5 - kuangSize.height*0.08) );
        this->addChild(xzdqSprite,2);
        
        //血战定缺选择
        xzdqSelectSprite = SelectSprite::selectWithFrameName(CONS_Image_BG_Set_Checkbox);
        if(GetBoolToXML(UD_Set_Xzdq,true)){
            xzdqSelectSprite->setSelectDisplay(ST_Select);
        }else{
            xzdqSelectSprite->setSelectDisplay(ST_Unselect);
        }
        CCMenuItemSprite *pItemXzdq = CCMenuItemSprite::create(xzdqSelectSprite,NULL,NULL,this,
                                                                             menu_selector(GameSet::menuSetXzdqCallback));
        pItemXzdq->setPosition( ccp(winSize.width*0.4312, winSize.height*0.5 - kuangSize.height*0.08) ); 
        
        //---普通血战
        CCSprite* ptxzSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Ptxz_Text);
        ptxzSprite->setPosition( ccp(winSize.width*0.5875, winSize.height*0.5 - kuangSize.height*0.08) );
        this->addChild(ptxzSprite,2);
        
        //普通血战选择
        ptxzSelectSprite = SelectSprite::selectWithFrameName(CONS_Image_BG_Set_Checkbox);
        if(GetBoolToXML(UD_Set_Ptxz,false)){
            ptxzSelectSprite->setSelectDisplay(ST_Select);
        }else{
            ptxzSelectSprite->setSelectDisplay(ST_Unselect);
        }
        
        CCMenuItemSprite *pItemPtxz = CCMenuItemSprite::create(ptxzSelectSprite,NULL,NULL,this, 
                                                                             menu_selector(GameSet::menuSetPtxzCallback));
        pItemPtxz->setPosition( ccp(winSize.width*0.6937, winSize.height*0.5 - kuangSize.height*0.08) ); 
        
        //---承包制
        CCSprite* cbzSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Cbz_Text);
        cbzSprite->setPosition( ccp(winSize.width*0.335, winSize.height*0.5 - kuangSize.height*0.19) );
        this->addChild(cbzSprite,2);
        
        //承包制选择
        cbzSelectSprite = SelectSprite::selectWithFrameName(CONS_Image_BG_Set_Checkbox);
        if(GetBoolToXML(UD_Set_Cbz,false)){
            cbzSelectSprite->setSelectDisplay(ST_Select);
        }else{
            cbzSelectSprite->setSelectDisplay(ST_Unselect);
        }
        
        CCMenuItemSprite *pItemCbz = CCMenuItemSprite::create(cbzSelectSprite,NULL,NULL,this, 
                                                                            menu_selector(GameSet::menuSetCbzCallback));
        pItemCbz->setPosition( ccp(winSize.width*0.4312, winSize.height*0.5 - kuangSize.height*0.19) ); 
        
        //---家家有
        CCSprite* jjySprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Jjy_Text);
        jjySprite->setPosition( ccp(winSize.width*0.5975, winSize.height*0.5 - kuangSize.height*0.19) );
        this->addChild(jjySprite,2);
        
        //家家有选择
        jjySelectSprite = SelectSprite::selectWithFrameName(CONS_Image_BG_Set_Checkbox);
        if(GetBoolToXML(UD_Set_Jjy,true)){
            jjySelectSprite->setSelectDisplay(ST_Select);
        }else{
            jjySelectSprite->setSelectDisplay(ST_Unselect);
        }
        
        CCMenuItemSprite *pItemJjy = CCMenuItemSprite::create(jjySelectSprite,NULL,NULL,this, 
                                                                            menu_selector(GameSet::menuSetJjyCallback));
        pItemJjy->setPosition( ccp(winSize.width*0.6937, winSize.height*0.5 - kuangSize.height*0.19) ); 
        
        //---三番起和
        CCSprite* sfqhSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Sfqh_Text);
        sfqhSprite->setPosition( ccp(winSize.width*0.325, winSize.height*0.5 - kuangSize.height*0.3) );
        this->addChild(sfqhSprite,2);
        
        //三番起和选择
        sfqhSelectSprite = SelectSprite::selectWithFrameName(CONS_Image_BG_Set_Checkbox);
        if(GetBoolToXML(UD_Set_Sfqh,false)){
            sfqhSelectSprite->setSelectDisplay(ST_Select);
        }else{
            sfqhSelectSprite->setSelectDisplay(ST_Unselect);
        }
        
        CCMenuItemSprite *pItemSfqh = CCMenuItemSprite::create(sfqhSelectSprite,NULL,NULL,this, 
                                                                             menu_selector(GameSet::menuSetSfqhCallback));
        pItemSfqh->setPosition( ccp(winSize.width*0.4312, winSize.height*0.5 - kuangSize.height*0.3) );
        
        //---自摸加底
        CCSprite* zmjdSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Zmjd_Text);
        zmjdSprite->setPosition( ccp(winSize.width*0.5875, winSize.height*0.5 - kuangSize.height*0.3) );
        this->addChild(zmjdSprite,2);
        
        //自摸加底选择
        zmjdSelectSprite = SelectSprite::selectWithFrameName(CONS_Image_BG_Set_Checkbox);
        if(GetBoolToXML(UD_Set_Zmjd,true)){
            zmjdSelectSprite->setSelectDisplay(ST_Select);
        }else{
            zmjdSelectSprite->setSelectDisplay(ST_Unselect);
        }
        
        CCMenuItemSprite *pItemZmjd = CCMenuItemSprite::create(zmjdSelectSprite,NULL,NULL,this, 
                                                                             menu_selector(GameSet::menuSetZmjdCallback));
        pItemZmjd->setPosition( ccp(winSize.width*0.6937, winSize.height*0.5 - kuangSize.height*0.3) );
        
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if(IOSCommon::IsIpad3())
        {
            /*yyProgress->setScale(2.0f);
            yxProgress->setScale(2.0f);*/
            pItemReturn->setScale(2.0f);
            pItemZddl->setScale(2.0f);
            pItemSdms->setScale(2.0f);
            pItemXzdq->setScale(2.0f);
            pItemPtxz->setScale(2.0f);
            pItemCbz->setScale(2.0f);
            pItemJjy->setScale(2.0f);
            pItemSfqh->setScale(2.0f);
            pItemZmjd->setScale(2.0f);
            
            yySprite->setScale(2.0f);
            yxSprite->setScale(2.0f);
            sdmsSprite->setScale(2.0f);
            zddlSprite->setScale(2.0f);
            xzdqSprite->setScale(2.0f);
            ptxzSprite->setScale(2.0f);
            cbzSprite->setScale(2.0f);
            jjySprite->setScale(2.0f);
            
            sfqhSprite->setScale(2.0f);
            zmjdSprite->setScale(2.0f);

        }
#endif
        
        
        // create menu, it's an autorelease object
        CCMenu* pMenu = CCMenu::create(pItemReturn,
                                              pItemZddl,
                                              pItemSdms,
                                              pItemXzdq,
                                              pItemPtxz,
                                              pItemCbz,
                                              pItemJjy,
                                              pItemSfqh,
                                              pItemZmjd, 
                                              NULL);
        pMenu->setPosition( CCPointZero );
        this->addChild(pMenu, 1);
    }
    else{
        //---允许旁观文字
        CCSprite* yxpgSprite = CCSprite::createWithSpriteFrameName(CONS_Image_Set_Yxpg_Text);
        yxpgSprite->setPosition( ccp(winSize.width*0.325, winSize.height*0.5 + kuangSize.height*0.07) );
        this->addChild(yxpgSprite,2);
        
        //允许旁观
        yxpgSelectSprite = SelectSprite::selectWithFrameName(CONS_Image_BG_Set_Checkbox);
        if(GetBoolToXML(UD_Set_Yxpg,false)){
            yxpgSelectSprite->setSelectDisplay(ST_Select);
        }else{
            yxpgSelectSprite->setSelectDisplay(ST_Unselect);
        }
        
        CCMenuItemSprite *pItemYxpg = CCMenuItemSprite::create(yxpgSelectSprite,NULL,NULL,this, 
                                                                             menu_selector(GameSet::menuSetYxpgCallback));
        pItemYxpg->setPosition( ccp(winSize.width*0.4312, winSize.height*0.5 + kuangSize.height*0.07) ); 
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if(IOSCommon::IsIpad3())
        {
            yxpgSprite->setScale(2.0f);
            pItemYxpg->setScale(2.0f);
            pItemReturn->setScale(2.0f);
            pItemSdms->setScale(2.0f);
            
            yySprite->setScale(2.0f);
            yxSprite->setScale(2.0f);
            sdmsSprite->setScale(2.0f);
        }
#endif
        
        // create menu, it's an autorelease object
        CCMenu* pMenu = CCMenu::create(pItemReturn, 
                                              pItemYxpg,
                                              pItemSdms,
                                              NULL);
        pMenu->setPosition( CCPointZero );
        this->addChild(pMenu, 1);
    }
	
    this->setVisible(false);
    
    //	//新手提示
    //	CCSprite* xstsSprite = CCSprite::create(CONS_Image_Set_Xsts_Text);
    //	xstsSprite->setPosition( ccp(winSize.width*0.325, winSize.height*0.5 + kuangSize.height*0.07) );
    //	this->addChild(xstsSprite,2);
    //    
    //	//新手提示选择
    //	xstsSelectSprite = SelectSprite::selectWithFrameName(CONS_Image_BG_Set_Checkbox);
    //	if(GetBoolToXML(UD_Set_Xsts,true)){
    //		xstsSelectSprite->setSelectDisplay(ST_Select);
    //	}else{
    //		xstsSelectSprite->setSelectDisplay(ST_Unselect);
    //	}
    //    
    //    CCMenuItemSprite *pItem1 = CCMenuItemSprite::create(xstsSelectSprite,NULL,NULL,this, 
    //                                                                      menu_selector(GameSet::menuSetXstsCallback));
    //	pItem1->setPosition( ccp(winSize.width*0.4312, winSize.height*0.5 + kuangSize.height*0.07) ); 
    //    
    //    //todo 暂不显示
    //    xstsSprite->setVisible(false); 
    //    pItem1->setVisible(false);
}
void GameSet::ShowGameSet(GameSetType gameSetType)
{
    this->setVisible(true);
    m_gameSetType = gameSetType;
}

void GameSet::menuBackCallback(CCObject* pSender)
{
    if (mType == GT_NetGame) {
        this->setVisible(false);
    }
    else{
        if (m_gameSetType == GST_MainMenu) {
            CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
        }
        else if (m_gameSetType == GST_GameMenu)
        {
            this->setVisible(false);
            cocos2d::CCDirector::sharedDirector()->resume();
            ((GameMenu *)this->getParent())->onResume();
        }
    }
}

//XSTS
void GameSet::menuSetXstsCallback(CCObject* pSender)
{
	if(xstsSelectSprite->state == ST_Select){
		xstsSelectSprite->setSelectDisplay(ST_Unselect);
		SetBoolToXML(UD_Set_Xsts,false);
	}else{
		xstsSelectSprite->setSelectDisplay(ST_Select);
		SetBoolToXML(UD_Set_Xsts,true);
	}	
}

//ZDDL
void GameSet::menuSetZddlCallback(CCObject* pSender)
{
	if(zddlSelectSprite->state == ST_Select){
		zddlSelectSprite->setSelectDisplay(ST_Unselect);
		SetBoolToXML(UD_Set_Zddl,false);
	}else{
		zddlSelectSprite->setSelectDisplay(ST_Select);
		SetBoolToXML(UD_Set_Zddl,true);
        SetBoolToXML(UD_Set_Jzmm,true);
	}	
}

//SDMS
void GameSet::menuSetSdmsCallback(CCObject* pSender)
{
	if(sdmsSelectSprite->state == ST_Select){
		sdmsSelectSprite->setSelectDisplay(ST_Unselect);
		SetBoolToXML(UD_Set_Sdms,false);
		SetIntegerToXML(UD_Set_Music,100);
		SetIntegerToXML(UD_Set_Effect,100);
		yyProgress->SetProgressShow(100);
		yxProgress->SetProgressShow(100);
	}else{
		sdmsSelectSprite->setSelectDisplay(ST_Select);
		SetBoolToXML(UD_Set_Sdms,true);
		SetIntegerToXML(UD_Set_Music,0);
		SetIntegerToXML(UD_Set_Effect,0);
		yyProgress->SetProgressShow(0);
		yxProgress->SetProgressShow(0);
	}
}

//XZDQ
void GameSet::menuSetXzdqCallback(CCObject* pSender)
{
	if(xzdqSelectSprite->state == ST_Select){
		xzdqSelectSprite->setSelectDisplay(ST_Unselect);
		ptxzSelectSprite->setSelectDisplay(ST_Select);
		SetBoolToXML(UD_Set_Xzdq,false);
		SetBoolToXML(UD_Set_Ptxz,true);
	}else{
		xzdqSelectSprite->setSelectDisplay(ST_Select);
		ptxzSelectSprite->setSelectDisplay(ST_Unselect);
		SetBoolToXML(UD_Set_Xzdq,true);
		SetBoolToXML(UD_Set_Ptxz,false);
	}
}
//PTXZ
void GameSet::menuSetPtxzCallback(CCObject* pSender)
{
	if(ptxzSelectSprite->state == ST_Select){
		ptxzSelectSprite->setSelectDisplay(ST_Unselect);
		xzdqSelectSprite->setSelectDisplay(ST_Select);
		SetBoolToXML(UD_Set_Ptxz,false);
		SetBoolToXML(UD_Set_Xzdq,true);
	}else{
		ptxzSelectSprite->setSelectDisplay(ST_Select);
		xzdqSelectSprite->setSelectDisplay(ST_Unselect);
		SetBoolToXML(UD_Set_Ptxz,true);
		SetBoolToXML(UD_Set_Xzdq,false);
	}
}
//CBZ
void GameSet::menuSetCbzCallback(CCObject* pSender)
{
	if(cbzSelectSprite->state == ST_Select){
		cbzSelectSprite->setSelectDisplay(ST_Unselect);
		jjySelectSprite->setSelectDisplay(ST_Select);
		SetBoolToXML(UD_Set_Cbz,false);
		SetBoolToXML(UD_Set_Jjy,true);
	}else{
		cbzSelectSprite->setSelectDisplay(ST_Select);
		jjySelectSprite->setSelectDisplay(ST_Unselect);
		SetBoolToXML(UD_Set_Cbz,true);
		SetBoolToXML(UD_Set_Jjy,false);
	}
}
//JJY
void GameSet::menuSetJjyCallback(CCObject* pSender)
{
	if(jjySelectSprite->state == ST_Select){		
		jjySelectSprite->setSelectDisplay(ST_Unselect);
		cbzSelectSprite->setSelectDisplay(ST_Select);
		SetBoolToXML(UD_Set_Jjy,false);
		SetBoolToXML(UD_Set_Cbz,true);
	}else{
		jjySelectSprite->setSelectDisplay(ST_Select);
		cbzSelectSprite->setSelectDisplay(ST_Unselect);
		SetBoolToXML(UD_Set_Jjy,true);
		SetBoolToXML(UD_Set_Cbz,false);
	}
}
//SFQH
void GameSet::menuSetSfqhCallback(CCObject* pSender)
{
	if(sfqhSelectSprite->state == ST_Select){
		sfqhSelectSprite->setSelectDisplay(ST_Unselect);
		SetBoolToXML(UD_Set_Sfqh,false);
	}else{
		sfqhSelectSprite->setSelectDisplay(ST_Select);
		SetBoolToXML(UD_Set_Sfqh,true);
	}
}
//ZMJD
void GameSet::menuSetZmjdCallback(CCObject* pSender)
{
	if(zmjdSelectSprite->state == ST_Select){
		zmjdSelectSprite->setSelectDisplay(ST_Unselect);
		SetBoolToXML(UD_Set_Zmjd,false);
	}else{
		zmjdSelectSprite->setSelectDisplay(ST_Select);
		SetBoolToXML(UD_Set_Zmjd,true);
	}
}
//YXPG
void GameSet::menuSetYxpgCallback(CCObject* pSender)
{
	if(yxpgSelectSprite->state == ST_Select){
		yxpgSelectSprite->setSelectDisplay(ST_Unselect);
		SetBoolToXML(UD_Set_Yxpg,false);
	}else{
		yxpgSelectSprite->setSelectDisplay(ST_Select);
		SetBoolToXML(UD_Set_Yxpg,true);
	}
    ((GameMenu *)this->getParent())->onSetEnableLookOn(yxpgSelectSprite->state == ST_Select);
}


