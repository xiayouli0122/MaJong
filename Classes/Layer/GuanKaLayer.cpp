//
//  GuanKaLayer.cpp
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GuanKaLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "MyTinyXmlParser.h"
#include "MenuScene.h"
#include "GuanKaScene.h"
#include "IOSCommon.h"

#else 

#include "../Common/MyTinyXmlParser.h"
#include "../Scene/MenuScene.h"
#include "../Scene/GuanKaScene.h"

#endif

using namespace cocos2d;

//初始化--------------------------------------------------
bool GuanKaLayer::init()
{
	//super init first
	if ( !ParentLayer::init() )
	{
		return false;
	}
    
    this->setTouchEnabled(true);

	this->setKeypadEnabled(true);
	isMoveActionRunning = false;
    

    //加入message层
    gameMessage = GameMessage::create();
    this->addChild(gameMessage,5);
    
    guankaNum = MyTinyXmlParser::GetGuanKaCount();
    
    //加入所有关卡	
    guanKaBatch = GuanKaBatch::create();
	guanKaBatch->initArray(guankaNum);
    this->addChild(guanKaBatch, 1);
	guanKaBatch->SetAllGuanKa(guankaNum);
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
	ping1 = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Selected);//关卡屏1，默认在第一屏
	ping1->setPosition( ccp(winSize.width*0.485, winSize.height*0.1016) );
	ping1->setVisible(true);
	this->addChild(ping1, 3);
    
	ping2 = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Unselected);//关卡屏2
	ping2->setPosition( ccp(winSize.width*0.515, winSize.height*0.1016) );
	ping2->setVisible(true);
	this->addChild(ping2, 3);
    
    CCSprite *kuang;// = CCSprite::create(CONS_Image_GK_Kuang);//关卡屏边框
	if (CommonFunction::isIpad()) {
        kuang = CCSprite::create(CONS_Image_GK_Kuang_Ipad);//关卡屏边框
    }
    else{
        kuang = CCSprite::create(CONS_Image_GK_Kuang);//关卡屏边框
    }
	//CCSprite* spriteLeft =  CCSprite::create("Image/GK_new/gk_kuang_left.png");
	//CCSprite* spriteRight =  CCSprite::create("Image/GK_new/gk_kuang_right.png");
	//spriteLeft->setAnchorPoint(ccp(0.0f,0.5f)); 
	//spriteRight->setAnchorPoint(ccp(1.0f,0.5f));

	//float midWidth = (winSize.width - spriteLeft->getContentSize().width - spriteRight->getContentSize().width) ;
	//kuang->setScaleX(midWidth / kuang->getContentSize().width);
	//kuang->setAnchorPoint(ccp(0.0f,0.5f));
	//kuang->setPosition(ccp(spriteLeft->getContentSize().width, winSize.height *0.5f));
	kuang->setPosition( ccp(winSize.width / 2, winSize.height /2) );
	kuang->setVisible(true);
	this->addChild(kuang, 2,2);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        kuang->setAnchorPoint(ccp(0.5f,0.5f));
        kuang->setPosition(ccp(winSize.width / 2.0f, winSize.height / 2.0f));
        kuang->setScale(2.0f);
    }
#endif
    
	return true;
}

void GuanKaLayer::onExit()
{
    ParentLayer::onExit();
}


//触摸相关方法---------------------------------------------
void GuanKaLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GuanKaLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
	if(isMoveActionRunning){//如果移屏动画正在运行，则不响应触屏事件		
		return false;
	}
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    x_begin = touchPoint.x;
    if (CommonFunction::isIpad()) {
        if (x_begin < winSize.width*0.139 || x_begin > winSize.width * 0.78) {
            return false;
        }       
    }else {
        if (x_begin < winSize.width*0.115 || x_begin > winSize.width * 0.8) {
            return false;
        }
    }
	x_batch_location_begin = guanKaBatch->getPosition().x;

	return true;
}

void GuanKaLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
	x_end = touchPoint.x;	
    if (x_end-x_begin > -5 && x_end-x_begin < 5) {
        guanKaBatch->onTouchSelected(touchPoint);
        return;
    }
	CCSpriteFrame *selectedFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_Image_GK_Selected);
	CCSpriteFrame *unSelectedFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_Image_GK_Unselected);
    
	isMoveActionRunning = true;//开始移屏动画
    
	if(x_end - x_begin > 40){//右移
		ping1->setDisplayFrame(selectedFrame);
		ping2->setDisplayFrame(unSelectedFrame);
		CCActionInterval*  actionTo = CCMoveTo::create(0.5, CCPointMake(0, 0));
        
        CCAction *sequneceAction = CCSequence::create(actionTo,//移屏动画                       
                                                       CCCallFunc::create(this, callfunc_selector(GuanKaLayer::moveActionCallback)),//结束动画用的回调                        
                                                       NULL); 
		guanKaBatch->runAction(sequneceAction);
	}else if(x_end - x_begin < -40){//左移
		ping1->setDisplayFrame(unSelectedFrame);
		ping2->setDisplayFrame(selectedFrame);
		CCActionInterval*  actionTo = CCMoveTo::create(0.5, ccp(-CCDirector::sharedDirector()->getWinSize().width*0.6833,0));
        CCAction *sequneceAction = CCSequence::create(actionTo,//移屏动画                       
                                                       CCCallFunc::create(this, callfunc_selector(GuanKaLayer::moveActionCallback)),//结束动画用的回调                        
                                                       NULL); 
		guanKaBatch->runAction(sequneceAction);
	}else{//恢复初始位置
		CCActionInterval*  actionTo = CCMoveTo::create(0.5, ccp(x_batch_location_begin,0));
        CCAction *sequneceAction = CCSequence::create(actionTo,//移屏动画                       
                                                       CCCallFunc::create(this, callfunc_selector(GuanKaLayer::moveActionCallback)),//结束动画用的回调                        
                                                       NULL); 
		guanKaBatch->runAction(sequneceAction);
	}
	
}

void GuanKaLayer::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
//    guanKaBatch->touchCancelled(touch);
}

void GuanKaLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
    
	guanKaBatch->setPosition(ccp(x_batch_location_begin + touchPoint.x - x_begin,0));	
}

void GuanKaLayer::moveActionCallback()
{
	isMoveActionRunning = false;//结束移屏动画
    
}

//#pragma mark -----------------------开始关卡----------------------
void GuanKaLayer::SelectGK(BYTE gk)
{
    //CCLOG("GuanKaLayer::SelectGK");
    //单机游戏币更新
//    long lCoin = GetIntegerToXML(UD_SINGLE_COIN);
    if (!CommonFunction::IsEnoughCoin())
    {
        //paddy test 提示充值
        CCLOG("***** no coin *****");
        
        gameMessage->SetMessageType(MT_NO_COIN);
        
        guanKaBatch->setVisible(false);
        ((GuanKaScene *)this->getParent())->setButtonVisible(false);
        return;
    }

    //如果选择的关卡有分，提示是否继续
    GUANKA_STATS gkStats = CommonFunction::GetGuanKaStats(gk);
    
//    if (ISANDROID)
//    {
//        CommonFunction::sendStatistic(gkStats.nSet, gkStats.guanKa, GetIntegerToXML(UD_SINGLE_COIN));
//        
//    }
    
    if (gkStats.nSet!=0)
    {
        gameMessage->selectedGK = gk;
        
        gameMessage->SetMessageType(MT_ContinueGK);
        
        guanKaBatch->setVisible(false);
        ((GuanKaScene *)this->getParent())->setButtonVisible(false);
    }
    else
    {
        //创建电脑玩家
        CommonFunction::CreatePlayersByGuan(gk);
        SetIntegerToXML(UD_CurrentGuanKa, gk);//从1开始
        CCDirector::sharedDirector()->replaceScene(LoadingScene::scene(TargetSceneGameScene));
    }
}

void GuanKaLayer::onCancel(MessageType type)
{
    if(type == MT_ContinueGK)
    {
        gameMessage->SetMessageType(MT_ReGK);
    }
    else if(type == MT_ReGK)
    {
        gameMessage->selectedGK = 0;
        gameMessage->setVisible(false);
        guanKaBatch->setVisible(true);
        ((GuanKaScene *)this->getParent())->setButtonVisible(true);
    }
    else if (type == MT_NO_COIN)
    {
        gameMessage->setVisible(false);
        guanKaBatch->setVisible(true);
        ((GuanKaScene *)this->getParent())->setButtonVisible(true);
    }
    else if (type == MT_OPEN_GUANKA)
    {
        gameMessage->setVisible(false);
        guanKaBatch->setVisible(true);
        ((GuanKaScene *)this->getParent())->setButtonVisible(true);
    }
}

void GuanKaLayer::onConfirm(MessageType type)
{
    switch (type) {
        case MT_ContinueGK:
            //继续关卡
            SetIntegerToXML(UD_CurrentGuanKa, gameMessage->selectedGK);
            CCDirector::sharedDirector()->replaceScene(LoadingScene::scene(TargetSceneGameScene));
            break;
            
        case MT_ReGK:
            //创建电脑玩家
            CommonFunction::CreatePlayersByGuan(gameMessage->selectedGK);
            //重新开始关卡
            CommonFunction::ClearGuanKaSaveData(gameMessage->selectedGK);
            SetIntegerToXML(UD_CurrentGuanKa, gameMessage->selectedGK);
            CCDirector::sharedDirector()->replaceScene(LoadingScene::scene(TargetSceneGameScene));
            break;
            
        case MT_NO_COIN:
            gameMessage->setVisible(false);
            guanKaBatch->setVisible(true);
            ((GuanKaScene *)this->getParent())->setButtonVisible(true);
            
            CommonFunction::payfee(1, PAY_ID_COIN);
            SetBoolToXML(CONS_STR_IS_PAY_COIN,true);
            
            schedule(schedule_selector(GuanKaLayer::TimerCheckPay));
 
#if IS_QUICK_PAY
////<for test
            CommonFunction::AddCoin(COIN_NUM_PAY);
            SetBoolToXML("isPayRet", true);
            SetBoolToXML("isPaySucceed", true);
            SetBoolToXML("isPayCancel", false);
////for test>
#endif
            break;
            
        case MT_OPEN_GUANKA:
            gameMessage->setVisible(false);
            
//            CommonFunction::payfee(1, PAY_ID_GUANKA);
//            SetBoolToXML(CONS_STR_IS_PAY_GUANKA,true);
            
//            schedule(schedule_selector(GuanKaLayer::TimerCheckPay));
            
////<for test
			//lyp start
//#if IS_QUICK_PAY
//            CommonFunction::OpenGuanka();
//            SetBoolToXML("isPayRet", true);
//            SetBoolToXML("isPaySucceed", true);
//            SetBoolToXML("isPayCancel", false);
//#endif
			//lyp end

////for test>
            
            gameMessage->setVisible(false);
            
            guanKaBatch->setVisible(true);
            ((GuanKaScene *)this->getParent())->setButtonVisible(true);
            
            //        CCDirector::sharedDirector()->replaceScene(LoadingScene::scene(TargetSceneGuanKaScene));
            break;
            
        case MT_PAY_COIN_MSG:
            gameMessage->setVisible(false);
            gameMessage->setVisibleCancel(true);
            
            guanKaBatch->setVisible(true);
            ((GuanKaScene *)this->getParent())->setButtonVisible(true);
            break;
            
        case MT_PAY_GK_MSG:
            gameMessage->setVisible(false);
            gameMessage->setVisibleCancel(true);
            
            guanKaBatch->setVisible(true);
            ((GuanKaScene *)this->getParent())->setButtonVisible(true);
            CCDirector::sharedDirector()->replaceScene(LoadingScene::scene(TargetSceneGuanKaScene));
            break;
            
        case MT_UNPASS_MSG:
            gameMessage->setVisible(false);
            gameMessage->setVisibleCancel(true);
            
            guanKaBatch->setVisible(true);
            ((GuanKaScene *)this->getParent())->setButtonVisible(true);
            break;
            
        default:
            break;
    }
}

void GuanKaLayer::keyBackClicked(){
	((GuanKaScene *)this->getParent())->onBack();
}

void GuanKaLayer::ShowOpenAllGuanka(int arg)
{
    guanKaBatch->setVisible(false);
    ((GuanKaScene *)this->getParent())->setButtonVisible(false);
    gameMessage->SetMessageType(MT_OPEN_GUANKA, arg);
}

void GuanKaLayer::ShowDelock(int arg)
{
    guanKaBatch->setVisible(false);
    ((GuanKaScene *)this->getParent())->setButtonVisible(false);
    gameMessage->SetMessageType(MT_OPEN_GUANKA, arg);
}

void GuanKaLayer::ShowMsg(int arg)
{
    guanKaBatch->setVisible(false);
    ((GuanKaScene *)this->getParent())->setButtonVisible(false);
    gameMessage->SetMessageType(MT_UNPASS_MSG, arg);
}

void GuanKaLayer::TimerCheckPay(float dt)
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
                    unschedule( schedule_selector(GuanKaLayer::TimerCheckPay));
                }
                else
                {
                    //扣费失败结果
                    HandlePayFailed(PAY_ID_COIN);
                }
            }
            
            SetBoolToXML(CONS_STR_IS_PAY_COIN,false);
            SetBoolToXML("isPayRet",false);
            SetBoolToXML("isPayCancel",false);
        }
        
        if(GetBoolToXML(CONS_STR_IS_PAY_GUANKA,false))
        {
            CCLOG("TimerCheckPay, guanka charge");
            
            //充值成功
            if(GetBoolToXML("isPaySucceed",false))
            {
                CCLOG("isPaySucceed");
                //提示消息
                HandlePaySuccess(PAY_ID_GUANKA);
            }
            else
            {
                //失败
                if(GetBoolToXML("isPayCancel",false))
                {
                    //取消
                    CCLOG("isPayCancel");
                    unschedule( schedule_selector(GuanKaLayer::TimerCheckPay));
                }
                else
                {
                    CCLOG("isPayFailed");
                    //扣费失败结果
                    HandlePayFailed(PAY_ID_GUANKA);
                }
            }
            
            SetBoolToXML(CONS_STR_IS_PAY_GUANKA,false);
            SetBoolToXML("isPayRet",false);
            SetBoolToXML("isPayCancel",false);
        }
        
        if(GetBoolToXML(CONS_STR_IS_PAY_DELOCK,false))
        {
            CCLOG("TimerCheckPay, delock charge");
            
            //充值成功
            if(GetBoolToXML("isPaySucceed",false))
            {
                CCLOG("isPaySucceed");
                //提示消息
                HandlePaySuccess(PAY_ID_DELOCK);
            }
            else
            {
                //失败
                if(GetBoolToXML("isPayCancel",false))
                {
                    //取消
                    CCLOG("isPayCancel");
                    unschedule( schedule_selector(GuanKaLayer::TimerCheckPay));
                }
                else
                {
                    CCLOG("isPayFailed");
                    //扣费失败结果
                    HandlePayFailed(PAY_ID_DELOCK);
                }
            }
            
            SetBoolToXML(CONS_STR_IS_PAY_DELOCK,false);
            SetBoolToXML("isPayRet",false);
            SetBoolToXML("isPayCancel",false);
        }
    }

}

void GuanKaLayer::HandlePaySuccess(int nItem)
{
    CCLOG("HandlePaySuccess: %d", nItem);
    unschedule( schedule_selector(GuanKaLayer::TimerCheckPay));
    ShowPaySuccess(nItem);
//    if (nItem == PAY_ID_COIN)
//    {
//        ShowPaySuccess(PAY_ID_COIN);
//    }
//    else if(nItem == PAY_ID_GUANKA)
//    {
//        ShowPaySuccess(PAY_ID_GUANKA);
//    }
//    else if (nItem == PAY_ID_DELOCK)
//    {
//        ShowPaySuccess(PAY_ID_DELOCK);
//    }
}

void GuanKaLayer::HandlePayFailed(int nItem)
{
    unschedule( schedule_selector(GuanKaLayer::TimerCheckPay));
//    if (nItem == PAY_RMB_COIN)
//    {
//        ;
//    }
//    else if(nItem == PAY_RMB_GUANKA)
//    {
//        ;
//    }
}

void GuanKaLayer::ShowPayFailed(int nItem)
{
    
}

void GuanKaLayer::ShowPaySuccess(int nItem)
{
    guanKaBatch->setVisible(false);
    ((GuanKaScene *)this->getParent())->setButtonVisible(false);
    
    if (nItem == PAY_ID_COIN)
    {
        gameMessage->SetMessageType(MT_PAY_COIN_MSG, 1);
    }
    else if(nItem == PAY_ID_GUANKA)
    {
        gameMessage->SetMessageType(MT_PAY_GK_MSG, 1);
    }
    else if(nItem == PAY_ID_DELOCK || nItem == PAY_ID_DELOCK_TOUCH)
    {
//        guanKaBatch->setVisible(true);
//        ((GuanKaScene *)this->getParent())->setButtonVisible(true);
        CCDirector::sharedDirector()->replaceScene(LoadingScene::scene(TargetSceneGuanKaScene));
    }
}

void GuanKaLayer::PayDelock(int arg)
{
    if(GetBoolToXML(UD_GUANKA_DELOCK, false))
    {
        return;
    }
    
    switch (arg) {
        case 0:
            CommonFunction::payfee(1, PAY_ID_DELOCK);
            break;
            
        default:
            CommonFunction::payfee(1, PAY_ID_DELOCK_TOUCH);
            break;
    }
    SetBoolToXML(CONS_STR_IS_PAY_DELOCK,true);
    schedule(schedule_selector(GuanKaLayer::TimerCheckPay));
}
