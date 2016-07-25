//
//  PersonSet.cpp
//  xzdd
//
//  Created by  on 12-5-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PersonSet.h"
#include "text_input_node/CCTextFieldTTF.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "MenuScene.h"
#include "CommonFunction.h"
#include "IOSCommon.h"
#else 

#include "../Scene/MenuScene.h"
#include "../Common/CommonFunction.h"
#endif

using namespace cocos2d;

//初始化--------------------------------------------------
bool PersonSet::init()
{
	//super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    nameInputSelected = false;
    m_nCharLimit = 8; //最大长度
    
    if (CommonFunction::isIpad()) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultPersonSetFrameFile_Ipad); 
    }else {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CONS_DefaultPersonSetFrameFile); 
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    // 加入菜单    - left
    CCSprite * ci1_1 = CCSprite::createWithSpriteFrameName(CONS_Image_PSet_Left);
    
    CCMenuItemSprite *pItem1 = CCMenuItemSprite::create(ci1_1,NULL,NULL,this, 
                                                                      menu_selector(PersonSet::menuLeftCallback));
	pItem1->setPosition( ccp(winSize.width*0.155,winSize.height*0.54) );

    
	// 加入菜单    - right
    CCSprite * ci2_1 = CCSprite::createWithSpriteFrameName(CONS_Image_PSet_Right);
    
    CCMenuItemSprite *pItem2 = CCMenuItemSprite::create(ci2_1,NULL,NULL,this, 
                                                                      menu_selector(PersonSet::menuRightCallback));
	pItem2->setPosition( ccp(winSize.width*0.41,winSize.height*0.54) ); 
    
    
    // 加入菜单    - return
    CCSprite * ci3_1 = CCSprite::createWithSpriteFrameName(CONS_Image_PSet_Return);
    
    CCMenuItemSprite *pItem3 = CCMenuItemSprite::create(ci3_1,NULL,NULL,this, 
                                                                      menu_selector(PersonSet::menuReturnCallback));
	pItem3->setPosition( ccp(winSize.width*0.85,winSize.height*0.1) ); 
    
    // 加入菜单    - update
    CCSprite * ci4_1 = CCSprite::createWithSpriteFrameName(CONS_Image_PSet_Update);
    
    CCMenuItemSprite *pItem4 = CCMenuItemSprite::create(ci4_1,NULL,NULL,this, 
                                                                      menu_selector(PersonSet::menuUpdateCallback));
	pItem4->setPosition( ccp(winSize.width*0.7,winSize.height*0.1) ); 
    
	CCMenu* pMenu = CCMenu::create(pItem1,pItem2,pItem3,pItem4,NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu);
    
    // 加入用户show
    user = CommonFunction::GetUser();
    userId = (user.nId == 0) ? 1 : user.nId;
    oldUserId = user.nId;
    nOldName = user.nName;
    showImage = CCSprite::createWithSpriteFrameName(user.nShowImage);
    showImage->setPosition( ccp(winSize.width*0.283,winSize.height*0.54) ); 
    this->addChild(showImage);
    
    pLabelName = CCLabelTTF::create("?", "Arial", CommonFunction::GetValueByDev(12));
    CCLOG("----USER NAME=%s", user.nName);
    pLabelName->setString(user.nName);
    pLabelName->setPosition( ccp(winSize.width*0.58,winSize.height*0.688) );
    pLabelName->setVisible(true);
    this->addChild(pLabelName);
    
    if(CommonFunction::isIpad()){
        pItem1->setPosition( ccp(winSize.width*0.175,winSize.height*0.54) );
        pItem2->setPosition( ccp(winSize.width*0.415, winSize.height*0.54) ); 
        pItem3->setPosition( ccp(winSize.width*0.828,winSize.height*0.167) ); 
        pItem4->setPosition( ccp(winSize.width*0.687,winSize.height*0.167) );
        showImage->setPosition( ccp(winSize.width*0.297, winSize.height*0.54) ); 
        pLabelName->setPosition( ccp(winSize.width*0.575,winSize.height*0.657) );
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        pItem1->setScale(2.0f);
        pItem2->setScale(2.0f);
        pItem3->setScale(2.0f);
        pItem4->setScale(2.0f);
        showImage->setScale(2.0f);
    }
#endif
    
    return true;
}

void PersonSet::setShow()
{
    char str[20];
    sprintf(str, "%s%d%s","show_",userId,".png");
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
    showImage->setDisplayFrame(frame);
    
    user = CommonFunction::GetUser();
    pLabelName->setString(user.nName);

}

//#pragma mark ----- 菜单回发 -----
void PersonSet::menuLeftCallback(CCObject* pSender)
{
    userId--;
    if (userId == 0) {
        userId = ICO_COUNT;
    }
    
    SetIntegerToXML(UD_User_Id,userId);
    
    setShow();
}


void PersonSet::menuRightCallback(CCObject* pSender)
{
    userId++;
    if (userId == ICO_COUNT+1) {
        userId = 1;
    }
    
    SetIntegerToXML(UD_User_Id,userId);
    
    setShow();
}

void PersonSet::menuReturnCallback(CCObject* pSender)
{
    SetIntegerToXML(UD_User_Id, oldUserId);
    SetStringToXML(UD_User_Name, nOldName);
    CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}
void PersonSet::menuUpdateCallback(CCObject* pSender)
{
    //PLAYER user = CommonFunction::GetUser();
    user.nId = userId;
    sprintf(user.nName,"%s",pLabelName->getString());

    CommonFunction::SetUser(user);
    CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}
