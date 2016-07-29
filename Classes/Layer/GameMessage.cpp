//
//  GameMessage.cpp
//  xzdd
//
//  Created by  on 12-4-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameMessage.h"
#include "ParentLayer.h"
#include <limits>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CommonFunction.h"
#include "IOSCommon.h"

#else
#include "../Common/CommonFunction.h"
#endif

using namespace cocos2d;

bool GameMessage::init()
{
	//////////////////////////////
	// 1. super init first
	//Dialog的背景设置成一个黑色半透明
	ccColor4B c = {0,0,0,150};
	if (!CCLayerColor::initWithColor(c) )
	{
		return false;
	}
	selectedGK = 0;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCLOG("Message.size:%f x %f ", size.width, size.height);

	//加入背景
	bjSprite = new CCSprite();
	if (CommonFunction::isIpad()) {
		bjSprite->initWithFile(CONS_Image_BG_Message_Ipad);
	}else {
		bjSprite->initWithFile(CONS_Image_BG_Message);
	}
	//背景居中
	bjSprite->setAnchorPoint(ccp(0.5, 0.5));
	bjSprite->setPosition(ccp(size.width * 0.5, size.height * 0.5));

	//第二个参数1：表示加载顺序，这里为什么不是0呢？背景层不是应该直接优先加载的吗？
	//第三个参数1：标记，后面可以通过getChildByTag取回该对象
	//CCSprite *sp1 = (CCSprite*)this->getChildByTag(tag)
	this->addChild(bjSprite,1,1);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	if(IOSCommon::IsIpad3())
	{
		bjSprite->setAnchorPoint(ccp(0.5f,0.5f));
		bjSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
		bjSprite->setScale(2.0f);
	}
#endif


	// 加入一个文本框，显示Dialog的消息内容，居中显示
	label = CCLabelTTF::create(CONS_MESSAGE_ReGK,"Thonburi", CommonFunction::GetValueByDev(13));
	label->setPosition( ccp(size.width*0.5,size.height*0.55) );
	this->addChild(label, 2,2);

	// 加入菜单    - 取消
	CCSprite * ci1 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Cancel);
	CCSprite * ci12 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Cancel_2);

	pCancel = CCMenuItemSprite::create(ci1,ci12,NULL,this,
		menu_selector(GameMessage::menuCancelCallback));
	//这里为什么还要获取一次WinSzie呢？前面不是已经获取过一次了吗？HAO蠢
	//我来改掉
	//0.62  0.31 好吧
	pCancel->setPosition(ccp(size.width*0.62, size.height*0.31));
	/*pCancel->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.62,
		CCDirector::sharedDirector()->getWinSize().height*0.31) ); */

	// 加入菜单    - 确认
	CCSprite * ci2 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Confirm);
	CCSprite * ci22 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Confirm_2);

	pConfirm = CCMenuItemSprite::create(ci2,ci22,NULL,this,
		menu_selector(GameMessage::menuConfirmCallback));
	pConfirm->setPosition(ccp(size.width*0.75, size.height*0.31));
	/*pConfirm->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.75,
		CCDirector::sharedDirector()->getWinSize().height*0.31) ); */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	if(IOSCommon::IsIpad3())
	{
		pConfirm->setScale(2.0f);
		pCancel->setScale(2.0f);
	}
#endif

	//确定和取消两个按钮都创建完了，然后是组成菜单
	CCMenu* pMenu = CCMenu::create(pCancel,pConfirm,NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 3,3);
	//默认Dialog是不显示的
	this->setVisible(false);

	return true;
}
void GameMessage::onExit()
{
	bjSprite->release();
	CCLayerColor::onExit();
}

void GameMessage::SetMessageType(MessageType mType, int nStatus)
{
	type = mType;
	char str[128];
	switch (type) {
	case MT_ReGK://重新开始Dialog
		label->setString(UTEXT(CONS_MESSAGE_ReGK));
		break;
	case MT_ContinueGK:
		{
			GUANKA_STATS gkStats = CommonFunction::GetGuanKaStats(selectedGK);
			char str[500];
			sprintf(str,CONS_STRING_DQJD,
				gkStats.nSet,
				gkStats.nScore,
				gkStats.nFan,
				gkStats.nJiPin);
			label->setString(UTEXT(str));
			break;
		}
	case MT_RunAway:
		{
			label->setString(UTEXT(CONS_MESSAGE_RunAway));
		}
		break;
	case MT_NO_COIN:
		{
			sprintf(str, CONS_MESSAGE_NO_COIN, COIN_NUM_PAY);

			label->setString(UTEXT(str));
		}
		break;
	case MT_SINGLE_FLEE:
		{
			if (nStatus == StatusJipinHu)
			{
				sprintf(str, CONS_MESSAGE_SINGLE_FLEE_JIPIN, COIN_NUM_FLEE_JIPIN);
			}
			else
			{
				sprintf(str, CONS_MESSAGE_SINGLE_FLEE, COIN_NUM_FLEE);
			}
			label->setString(UTEXT(str));
		}
		break;
	case MT_ADD_COIN:
		{
			sprintf(str, CONS_MESSAGE_ADD_COIN, COIN_NUM_PAY);
			label->setString(UTEXT(str));
		}
		break;
	case MT_OPEN_GUANKA:
		{
			if (nStatus == 0)
			{
				sprintf(str, CONS_MESSAGE_OPEN_GUANKA);
			}
			else if (nStatus == 1)
			{
				sprintf(str, CONS_MESSAGE_OPEN_GUANKA_PASS);
			}
			else if(nStatus == 2)
			{
				sprintf(str,CONS_MSG_DELOCK_OPEN_GK);
			}
			label->setString(UTEXT(str));
		}
		break;
	case MT_PAY_COIN_MSG:
		{
			if (nStatus == 1)
			{
				int nCoin = GetIntegerToXML(UD_SINGLE_COIN);

				setVisibleCancel(false);
				sprintf(str, CONS_MESSAGE_PAY_COIN_OK, nCoin);
				label->setString(UTEXT(str));

				CommonFunction::SubmitCoin(nCoin);
			}
		}
		break;
	case MT_PAY_GK_MSG:
		{
			if (nStatus == 1)
			{
				setVisibleCancel(false);
				sprintf(str, CONS_MESSAGE_PAY_GK_OK);
				label->setString(UTEXT(str));
			}
		}
		break;

	case MT_UNPASS_MSG:
		{
			setVisibleCancel(false);
			sprintf(str, CONS_MESSAGE_UNPASS);
			label->setString(UTEXT(str));
		}
		break;
	case MT_RECEIVE_COIN:
		{
			setVisibleCancel(false);
			sprintf(str, CONS_MESSAGE_RECEIVE);
			label->setString(UTEXT(str));
		}
		break;
	case MT_BUY_TOW_COIN:
		{
			setVisibleCancel(false);
			sprintf(str, CONS_MESSAGE_TOW);
			label->setString(UTEXT(str));
		}
		break;
	case MT_BUY_FOUR_COIN:
		{
			setVisibleCancel(false);
			sprintf(str, CONS_MESSAGE_FOUR);
			label->setString(UTEXT(str));
		}
		break;
	case MT_BUY_SIX_COIN:
		{
			setVisibleCancel(false);
			sprintf(str, CONS_MESSAGE_SIX);
			label->setString(UTEXT(str));
		}
		break;
	default:
		break;
	}
	this->setVisible(true);
}

//#pragma mark -----------------------菜单动作----------------------

void GameMessage::menuCancelCallback(CCObject* pSender)
{
	CCLOG("click cancel btn");
	((ParentLayer *) this->getParent())->onCancel(type);
}

void GameMessage::menuConfirmCallback(CCObject* pSender)
{
	if ( MT_RECEIVE_COIN == type || MT_BUY_TOW_COIN == type || MT_BUY_FOUR_COIN == type || MT_BUY_SIX_COIN == type)
		this->removeFromParent();
	else
		((ParentLayer *) this->getParent())->onConfirm(type);
}

void GameMessage::setVisibleCancel(bool bVisible)
{
	pCancel->setVisible(bVisible);
}

//void GameMessage::registerWithTouchDispatcher()
//{
//	CCLOG("registerWithTouchDispatcher:%d", (numeric_limits<int>::min)());
//	CCDirector * directory = CCDirector::sharedDirector();
//
//	directory->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
//	//cctouchdispatcher *dispatcher = ccdirector::shareddirector()->gettouchdispatcher();
//	//dispatcher->addtargeteddelegate(this, (numeric_limits<int>::min)(), true);
//	//CCLayer::registerWithTouchDispatcher();
//}
//
//bool GameMessage::ccTouchBegan(CCTouch * touch,CCEvent * pevent)
//{
//	return true;
//}

