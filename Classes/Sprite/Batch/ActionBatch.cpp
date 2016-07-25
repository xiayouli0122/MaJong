//
//  ActionBatch.cpp
//  xzdd
//
//  Created by  on 12-3-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "ActionBatch.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "GameDesk.h"
#include "IOSCommon.h"
#else 

#include "../../Layer/GameDesk.h"

#endif

using namespace cocos2d;

bool ActionBatch::init()
{
    //加入背景
    CCSprite * sbj = CCSprite::createWithSpriteFrameName(CONS_ActionbjImage);
    
#if IS_NEW_SKIN
    sbj->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.5,
                          CCDirector::sharedDirector()->getWinSize().height*0.3));
#else
    sbj->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.5,
                          CCDirector::sharedDirector()->getWinSize().height*0.315));
#endif
    
    this->addChild(sbj,1);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        sbj->setScale(2.0f);
    }
#endif
    
    m_bPause = false;
    
    markDingQue = CCSprite::createWithSpriteFrameName(CONS_ActionDQImage);
    markDingQue->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.5,
                          CCDirector::sharedDirector()->getWinSize().height*0.315 +
                                  sbj->boundingBox().size.height*0.45));
    markDingQue->setVisible(false);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        markDingQue->setScale(2.0f);
    }
#endif
    this->addChild(markDingQue,2);
    
    //--------加入菜单----------
    //--消--
    CCSprite * sx1 = CCSprite::createWithSpriteFrameName(CONS_ActionxImage1);
    // 获取菜单图片大小，摆位置的时候用
    CCSize itemSize = sx1->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        itemSize.width *= 2.0f;
        itemSize.height *= 2.0f;
    }
#endif
    CCSprite * sx2 = CCSprite::createWithSpriteFrameName(CONS_ActionxImage2);
    CCSprite * sx3 = CCSprite::createWithSpriteFrameName(CONS_ActionxImage3);
    pItemx = CCMenuItemSprite::create(sx1,sx2,sx3,this, menu_selector(ActionBatch::ActionX));
	pItemx->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.5 - itemSize.width * 1.5,
                             CCDirector::sharedDirector()->getWinSize().height*0.3) ); 
    
    //--碰--
    CCSprite * sp1 = CCSprite::createWithSpriteFrameName(CONS_ActionpImage1);
    CCSprite * sp2 = CCSprite::createWithSpriteFrameName(CONS_ActionpImage2);
    CCSprite * sp3 = CCSprite::createWithSpriteFrameName(CONS_ActionpImage3);
    pItemp = CCMenuItemSprite::create(sp1, sp2, sp3, this, menu_selector(ActionBatch::ActionP));
	pItemp->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.5 - itemSize.width * 0.5,
                             CCDirector::sharedDirector()->getWinSize().height*0.3) ); 
    
    //--直杠,弯杠,暗杠--
    CCSprite * sg1 = CCSprite::createWithSpriteFrameName(CONS_ActiongImage1);
    CCSprite * sg2 = CCSprite::createWithSpriteFrameName(CONS_ActiongImage2);
    CCSprite * sg3 = CCSprite::createWithSpriteFrameName(CONS_ActiongImage3);
    pItemg = CCMenuItemSprite::create(sg1, sg2, sg3, this, menu_selector(ActionBatch::ActionG));
	pItemg->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.5 + itemSize.width * 0.5,
                             CCDirector::sharedDirector()->getWinSize().height*0.3) ); 
    
    //--胡--
    CCSprite * sh1 = CCSprite::createWithSpriteFrameName(CONS_ActionhImage1);
    CCSprite * sh2 = CCSprite::createWithSpriteFrameName(CONS_ActionhImage2);
    CCSprite * sh3 = CCSprite::createWithSpriteFrameName(CONS_ActionhImage3);
    pItemh = CCMenuItemSprite::create(sh1, sh2, sh3, this, menu_selector(ActionBatch::ActionH));
	pItemh->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.5 + itemSize.width * 1.5,
                             CCDirector::sharedDirector()->getWinSize().height*0.3) ); 
    
    //--定缺 万--
    CCSprite * dqw1 = CCSprite::createWithSpriteFrameName(CONS_ActionWanImage1);
    CCSprite * dqw2 = CCSprite::createWithSpriteFrameName(CONS_ActionWanImage2);
    CCSprite * dqw3 = CCSprite::createWithSpriteFrameName(CONS_ActionWanImage3);
    pItemdqwan = CCMenuItemSprite::create(dqw1, dqw2, dqw3, this, menu_selector(ActionBatch::ActionDingQueWan));
	pItemdqwan->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.5 - itemSize.width*1.2,
                              CCDirector::sharedDirector()->getWinSize().height*0.3) );
    pItemdqwan->setVisible(false);
    
    //--定缺 条--
    CCSprite * dqt1 = CCSprite::createWithSpriteFrameName(CONS_ActionTiaoImage1);
    CCSprite * dqt2 = CCSprite::createWithSpriteFrameName(CONS_ActionTiaoImage2);
    CCSprite * dqt3 = CCSprite::createWithSpriteFrameName(CONS_ActionTiaoImage3);
    pItemdqtiao = CCMenuItemSprite::create(dqt1, dqt2, dqt3, this, menu_selector(ActionBatch::ActionDingQueTiao));
	pItemdqtiao->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.5,
                                 CCDirector::sharedDirector()->getWinSize().height*0.3) );
    pItemdqtiao->setVisible(false);
    
    //--定缺 筒--
    CCSprite * dqto1 = CCSprite::createWithSpriteFrameName(CONS_ActionTongImage1);
    CCSprite * dqto2 = CCSprite::createWithSpriteFrameName(CONS_ActionTongImage2);
    CCSprite * dqto3 = CCSprite::createWithSpriteFrameName(CONS_ActionTongImage3);
    pItemdqtong = CCMenuItemSprite::create(dqto1, dqto2, dqto3, this, menu_selector(ActionBatch::ActionDingQueTong));
	pItemdqtong->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.5 + itemSize.width*1.2,
                                 CCDirector::sharedDirector()->getWinSize().height*0.3) );
    pItemdqtong->setVisible(false);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        pItemx->setScale(2.0f);
        pItemp->setScale(2.0f);
        pItemg->setScale(2.0f);
        pItemh->setScale(2.0f);
        pItemdqwan->setScale(2.0f);
        pItemdqtiao->setScale(2.0f);
        pItemdqtong->setScale(2.0f);
    }
#endif
    
	// create menu, it's an autorelease object
	CCMenu *pMenu = CCMenu::create(pItemx,pItemp,pItemg,pItemh,pItemdqwan,pItemdqtiao,pItemdqtong,NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 2);
    
    this->setVisible(false);
    
    return true;
}

//最后参数isMo，判断是否时摸牌模式，从而显示不同的菜单
void ActionBatch::show(bool showP,bool showAG, bool showG, bool showH, bool isMo)
{
    isMoAction = isMo;

    showType(MenuType_ChooseAction);
    
    pItemp->setEnabled(showP);
    pItemg->setEnabled(showG || showAG);
    pItemh->setEnabled(showH);
    
    if (pItemp->isEnabled()||pItemg->isEnabled()||pItemg->isEnabled()||pItemh->isEnabled()) {
        this->setVisible(true);
    }
}

void ActionBatch::showDingQue()
{
    showType(MenuType_DingQue);
    this->setVisible(true);
}

void ActionBatch::showType(ActionMenuType type)
{
    markDingQue->setVisible(type == MenuType_DingQue);
    pItemdqwan->setVisible(type == MenuType_DingQue);
    pItemdqtiao->setVisible(type == MenuType_DingQue);
    pItemdqtong->setVisible(type == MenuType_DingQue);
    
    pItemp->setVisible(type != MenuType_DingQue);
    pItemx->setVisible(type != MenuType_DingQue);
    pItemg->setVisible(type != MenuType_DingQue);
    pItemh->setVisible(type != MenuType_DingQue);
}

//Action菜单
void ActionBatch::ActionX(CCObject* pSender)
{
    this->setVisible(false);
    GameDesk * desk = (GameDesk *)getParent();
    desk->ActionX();
}

void ActionBatch::ActionP(CCObject* pSender)
{
    this->setVisible(false);
    GameDesk * desk = (GameDesk *)getParent();
    desk->ActionP();
}

void ActionBatch::ActionG(CCObject* pSender)
{
    this->setVisible(false);
    GameDesk * desk = (GameDesk *)getParent();
    if (isMoAction) {
        desk->ActionMoG();
    }
    else {
        desk->ActionZG();
    }
}

void ActionBatch::ActionH(CCObject* pSender)
{
    this->setVisible(false);
    GameDesk * desk = (GameDesk *)getParent();
    desk->ActionH();
}

void ActionBatch::ActionDingQueWan(CCObject* pSender)
{
    ActionDingQue(WAN);
}
void ActionBatch::ActionDingQueTiao(CCObject* pSender)
{
    ActionDingQue(TIAO);
}
void ActionBatch::ActionDingQueTong(CCObject* pSender)
{
    ActionDingQue(TONG);
}

void ActionBatch::ActionDingQue(PAI_TYPE type)
{
    this->setVisible(false);
    GameDesk * desk = (GameDesk *)getParent();
    desk->ActionDingQue(0, type);
}

//#pragma mark -----------------------暂停和恢复----------------------
void ActionBatch::onPause()
{
    if (!m_bPause) {
        isShowBeforePause = this->isVisible();
        this->setVisible(false);
        m_bPause = true;
    }
}
void ActionBatch::onResume()
{
    m_bPause = false;
    this->setVisible(isShowBeforePause);
}
