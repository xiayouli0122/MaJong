//
//  GuanKaBatch.cpp
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GuanKaBatch.h"
#include <string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "GuanKaLayer.h"
#include "IOSCommon.h"
#else 

#include "../../Layer/GuanKaLayer.h"

#endif


using namespace cocos2d;

//初始化--------------------------------------------------
bool GuanKaBatch::init()
{	
	return true;
}

//初始化--------------------------------------------------
bool GuanKaBatch::initArray(int guankaNum)
{
    //循环初始化每一个关卡
//    guanKaArray = new CCMutableArray<GuanKaSprite*>;
	guanKaArray = CCArray::create();
	guanKaArray->retain();
    for (int i=0; i<guankaNum; i++) {
        GuanKaSprite * guanKaSprite = GuanKaSprite::guanKaWithFrameName(CONS_Image_GK_Dark);
        guanKaArray->addObject(guanKaSprite); //加入关卡到数组
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if(IOSCommon::IsIpad3())
        {
            guanKaSprite->setScale(2.0f);
        }
#endif

    }
    
	return true;
}

void GuanKaBatch::onExit()
{
	guanKaArray->removeAllObjects();
    guanKaArray->release();   //关卡数组 
    CCNode::onExit();
}

void GuanKaBatch::SetAllGuanKa(int guankaNum)
{
//	CCMutableArray<GuanKaSprite*>::CCMutableArrayIterator ite;
	CCObject ** ite;
    
    ite = guanKaArray->data->arr;   
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	GuanKaSprite *myGuanKa = (GuanKaSprite*)* ite;
	CCSize guanKaSize = myGuanKa->getContentSize();
	float ge_x = (winSize.width* 0.6833 - 4*guanKaSize.width)/5;
	float ge_y = (winSize.height*0.7031 - 3*guanKaSize.height)/4;
    float baseHeight = winSize.height*0.8344;
    if (CommonFunction::isIpad()) {
        ge_y = (winSize.height*0.6031 - 3*guanKaSize.height)/4;
        baseHeight = winSize.height*0.8;
    }
    for (int j=0; j<guankaNum; j++) {
		GuanKaSprite * guanKa = (GuanKaSprite*)* ite;
		guanKa->setVisible(true);
#if IS_NEW_SKIN
		float position_x = winSize.width* 0.15 + j/12*winSize.width*0.6833 + ge_x*(j%4+1) + guanKaSize.width*(j%4+j%4+1)/2;
#else
        float position_x = winSize.width* 0.1229 + j/12*winSize.width*0.6833 + ge_x*(j%4+1) + guanKaSize.width*(j%4+j%4+1)/2;
#endif
		float position_y = 0;
		if(j%12>=0 && j%12<4){
			position_y = baseHeight - ge_y - guanKaSize.height/2;
		}else if(j%12>=4 && j%12<8){
			position_y = baseHeight - ge_y*2 - guanKaSize.height*1.5;
		}else if(j%12>=8 && j%12<12){
			position_y = baseHeight - ge_y*3 - guanKaSize.height*2.5;
		}
        
        GUANKA_STATS gkStats = CommonFunction::GetGuanKaStats(j+1);
        GuanKaState gState;
  
        bool bGkOpened  = GetBoolToXML(UD_GUANKA_OPEN, false);
        bool bGkPassed1 = GetBoolToXML(UD_PASS_GUANKA_1, false);
        
        bool bGkPassed3 = GetBoolToXML(UD_PASS_GUANKA_3, false);
        
        if(!gkStats.isLock && gkStats.passStar == 0)
        {
#if IS_NEW_GK_CONDITION
            if (j==3 && bGkPassed3 && !bGkOpened)
            {
                gState = GK_UNPAY;
            }
            else
            {
                gState = GK_None;
            }
#else
            if (j==1 && bGkPassed1 && !bGkOpened)
            {
                gState = GK_UNPAY;
            }
            else
            {
                gState = GK_None;
            }
#endif
        }
        else if(gkStats.isLock)
        {
#if IS_NEW_GK_CONDITION
            if (bGkOpened)
            {
                gState = GK_Lock;
            }
            else if(j==1 || j==2)
            {
                gState = GK_Lock;
            }
            else
            {
                gState = GK_UNPAY;
            }
#else
            if (bGkOpened)
            {
                gState = GK_Lock;
            }
            else
            {
                gState = GK_UNPAY;
            }
#endif
        }
        else if(!gkStats.isLock && gkStats.passStar == 1)
        {
            gState = GK_Star1;
        }
        else if(!gkStats.isLock && gkStats.passStar == 2)
        {
            gState = GK_Star2;
        }
        else if(!gkStats.isLock && gkStats.passStar == 3)
        {
            gState = GK_Star3;
        }
        else
        {
            //ERROR
        }
        
        guanKa->setDisplayFrameName(gState, j+1);

        guanKa->setPosition( ccp(position_x, position_y) );
        if (!gkStats.isLock)
        {
#if IS_NEW_GK_CONDITION
            if (j==3 && bGkPassed3 && !bGkOpened)
            {
                guanKa->setTag(0);
            }
#else
            if (j==1 && bGkPassed1 && !bGkOpened)
            {
                guanKa->setTag(0);
            }
#endif
            else
            {
                guanKa->setTag(j+1);
            }
        }
        else
        {
#if IS_NEW_GK_CONDITION
            if (j==1 || j==2)
            {
                guanKa->setTag(j+1);
            }
            else
            {
                guanKa->setTag(0);
            }
#else
            guanKa->setTag(0);
#endif
        }
        this->addChild(guanKa, 2);
        
		ite++;
    }
}

void GuanKaBatch::onTouchSelected(CCPoint touchPoint)
{
    //CCLOG("GuanKaBatch::onTouchSelected");
//    CCMutableArray<GuanKaSprite*>::CCMutableArrayIterator gk;
    CCRect ir;
    
    bool bGuankaOpened = GetBoolToXML(UD_GUANKA_OPEN, false);
    bool bPassedGk1     = GetBoolToXML(UD_PASS_GUANKA_1, false);
    bool bGuankaDelock = GetBoolToXML(UD_GUANKA_DELOCK, false);
    
    bool bPassedGk3     = GetBoolToXML(UD_PASS_GUANKA_3, false);
    
	CCObject *gk;
	CCARRAY_FOREACH(guanKaArray, gk)
	{
        GuanKaSprite *g =dynamic_cast<GuanKaSprite *>(gk);
        CCLOG("onTouchSelected %d", g->getTag());
        if (g->getTag() == 0)
        {
            if (!bGuankaOpened)
            {
                ir = g->boundingBox();
                ir.origin = ccpAdd(getPosition(), ir.origin);
                if(ir.containsPoint(touchPoint))
                {
                    ((GuanKaLayer *)this->getParent())->ShowOpenAllGuanka(0);
                    return;
                }
            }
            else if(!bGuankaDelock)
            {
                ir = g->boundingBox();
                ir.origin = ccpAdd(getPosition(), ir.origin);
                if(ir.containsPoint(touchPoint))
                {
                    ((GuanKaLayer *)this->getParent())->PayDelock(1);
                    return;
                }
            }
            continue;
        }
#if IS_NEW_GK_CONDITION
        int nGK = g->getTag();
        if (nGK ==2 || nGK ==3)
        {
            GUANKA_STATS gkStats = CommonFunction::GetGuanKaStats(nGK);
            if (gkStats.isLock) {
                ir = g->boundingBox();
                ir.origin = ccpAdd(getPosition(), ir.origin);
                if(CCRect::CCRectContainsPoint(ir, touchPoint))
                {
                    if (!bGuankaOpened) {// 游戏未激活
                        ((GuanKaLayer *)this->getParent())->ShowMsg();
                    }
                    else{
                        ((GuanKaLayer *)this->getParent())->PayDelock(1);
                    }
                    return;
                }
            }
        }
#endif
        
//        if (g->getTag() == 1 && !bGuankaOpened && bPassedGk1)
//        {
//            ir = g->boundingBox();
//            ir.origin = ccpAdd(getPosition(), ir.origin);
//            if(CCRect::CCRectContainsPoint(ir, touchPoint))
//            {
//                ((GuanKaLayer *)this->getParent())->ShowOpenAllGuanka(1);
//                return;
//            }
//        }
        
        ir = g->boundingBox();
        ir.origin = ccpAdd(getPosition(), ir.origin);
        if(ir.containsPoint(touchPoint))
        {
            ((GuanKaLayer *)this->getParent())->SelectGK(g->getTag());
            return;
        }
    }
}

////触摸相关方法---------------------------------------------
//bool GuanKaBatch::touchBegan(CCTouch* touch)
//{
//	//CCLOG("==========GuanKaBatch::touchBegan===================");
//    CCPoint touchPoint = touch->getLocationInView( );
//    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
//    return true;
//}
//void GuanKaBatch::touchEnded(CCTouch* touch)
//{
//	//CCLOG("==========GuanKaBatch::touchEnded===================");
//    CCPoint touchPoint = touch->getLocationInView( );
//    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
//    
//    
//}
//
//void GuanKaBatch::touchCancelled(CCTouch* touch)
//{
//}
//
//void GuanKaBatch::touchMoved(CCTouch* touch)
//{
//	//CCLOG("==========GuanKaBatch::touchMoved===================");
//    CCPoint touchPoint = touch->getLocationInView( );
//    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
//    
//}

void GuanKaBatch::menuCallback(CCObject* pSender)
{
	int selectedGuanKa = ((CCMenuItemSprite *)pSender)->getTag();
    ((GuanKaLayer *)this->getParent())->SelectGK(selectedGuanKa);
    CCLOG("GuanKaBatch::menuCallback %d", selectedGuanKa);
}


