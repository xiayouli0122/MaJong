//
//  GuanKaSprite.cpp
//  xzdd
//
//  Created by  on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "GuanKaSprite.h"

using namespace cocos2d;

GuanKaSprite::GuanKaSprite(void)
{
}


GuanKaSprite::~GuanKaSprite(void)
{
}

bool GuanKaSprite::init()
{
    if(!CCSprite::init())
    {
        return false;
    }
	guanKaState = GK_None;    
    
	sNumber = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Num1);
//	sLock = CCSprite::create(CONS_Image_Lock2);
    sLock = CCSprite::createWithSpriteFrameName(CONS_Image_Lock3);
    sStar1 = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Star);
    sStar2 = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Star);
    sStar3 = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Star); 
	sStarDark1 = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Star_Dark); 
	sStarDark2 = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Star_Dark); 
	sStarDark3 = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Star_Dark); 
	sText = CCSprite::createWithSpriteFrameName(CONS_Image_GK_Text1);
    
    sLogoPay = CCSprite::createWithSpriteFrameName(CONS_Image_Lock1);
	
	sNumber->setVisible(false);
	sLock->setVisible(false);
    sStar1->setVisible(false);
    sStar2->setVisible(false);
    sStar3->setVisible(false);
    sStarDark1->setVisible(false);
    sStarDark2->setVisible(false);
    sStarDark3->setVisible(false);
    
    sLogoPay->setVisible(false);
    
    addChild(sNumber, 1);
	addChild(sLock,2);
    addChild(sStar1,3);
    addChild(sStar2,3);
    addChild(sStar3,3);
    addChild(sStarDark1,2);
	addChild(sStarDark2,2);
	addChild(sStarDark3,2);
    addChild(sText,2);
    
    addChild(sLogoPay, 2);
    
	setVisible(true);    //初始化设置对象可见
    return true;
}

//通过图片名创建关卡对象
GuanKaSprite* GuanKaSprite::guanKaWithFrameName(const char *pFrameName)
{
    
	GuanKaSprite* pGuanKaSprite = GuanKaSprite::create();
    pGuanKaSprite->initWithSpriteFrameName(pFrameName);
//	pGuanKaSprite->autorelease();
    
	CCSize pSize = pGuanKaSprite->getContentSize();
	CCSize starSize = pGuanKaSprite->sStar1->getContentSize();
    
	pGuanKaSprite->sNumber->setPosition(ccp(pSize.width*0.5, pSize.height*0.55));
	pGuanKaSprite->sLock->setPosition(ccp(pSize.width*0.5, pSize.height*0.5));
	pGuanKaSprite->sStar1->setPosition(ccp(pSize.width*0.5 - starSize.width *1.25,pSize.height*0.25));
	pGuanKaSprite->sStar2->setPosition(ccp(pSize.width*0.5,pSize.height*0.25));
    pGuanKaSprite->sStar3->setPosition(ccp(pSize.width*0.5 + starSize.width *1.25,pSize.height*0.25));
	pGuanKaSprite->sStarDark1->setPosition(ccp(pSize.width*0.5 - starSize.width *1.25,pSize.height*0.25));
    pGuanKaSprite->sStarDark2->setPosition(ccp(pSize.width*0.5,pSize.height*0.25));
    pGuanKaSprite->sStarDark3->setPosition(ccp(pSize.width*0.5 + starSize.width *1.25,pSize.height*0.25));
	pGuanKaSprite->sText->setPosition(ccp(pSize.width*(0.5), pSize.height*(-0.1)));
    
    pGuanKaSprite->sLogoPay->setPosition(ccp(pSize.width*0.5, pSize.height*0.5));
    
	return pGuanKaSprite;
}


void GuanKaSprite::setDisplayFrameName(GuanKaState state, int guankaIndex)
{
	char guanka[512];
	char guankaNum[512];
	char guankaName[512];
	
	sprintf(guanka,"gk_%d.png", guankaIndex);
	sprintf(guankaNum,"gk_num_%d.png", guankaIndex);
	sprintf(guankaName,"gk_%d_text.png", guankaIndex);
    
    CCSpriteFrame *guankaframe;    
	CCSpriteFrame *darkGuankaframe;
    
	CCSpriteFrame *guankaNumFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(guankaNum);
	this->sNumber->setDisplayFrame(guankaNumFrame);
    
	CCSpriteFrame *guankaNameFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(guankaName);
	this->sText->setDisplayFrame(guankaNameFrame);
    
	switch(state)
	{
		case GK_None:
			guankaframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(guanka);
			this->setDisplayFrame(guankaframe);
			this->sLock->setVisible(false);
			this->sNumber->setVisible(true);
			this->sStar1->setVisible(false);
			this->sStar2->setVisible(false);
			this->sStar3->setVisible(false);
			this->sStarDark1->setVisible(true);
			this->sStarDark2->setVisible(true);
			this->sStarDark3->setVisible(true);
            
            this->sLogoPay->setVisible(false);
			break;
		case GK_Lock:
//			darkGuankaframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_Image_GK_Dark);
            darkGuankaframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_IMAGE_GK_UNPAY);
			this->setDisplayFrame(darkGuankaframe);
			this->sLock->setVisible(true);
			this->sNumber->setVisible(false);
			this->sStar1->setVisible(false);
			this->sStar2->setVisible(false);
			this->sStar3->setVisible(false);
			this->sStarDark1->setVisible(false);
			this->sStarDark2->setVisible(false);
			this->sStarDark3->setVisible(false);
            
            this->sLogoPay->setVisible(false);
			break;
		case GK_Star1:
			guankaframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(guanka);
			this->setDisplayFrame(guankaframe);
			this->sLock->setVisible(false);
			this->sNumber->setVisible(true);
			this->sStar1->setVisible(true);
			this->sStar2->setVisible(false);
			this->sStar3->setVisible(false);
			this->sStarDark1->setVisible(true);
			this->sStarDark2->setVisible(true);
			this->sStarDark3->setVisible(true);
            
            this->sLogoPay->setVisible(false);
			break;
		case GK_Star2:
			guankaframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(guanka);
			this->setDisplayFrame(guankaframe);
			this->sLock->setVisible(false);
			this->sNumber->setVisible(true);
			this->sStar1->setVisible(true);
			this->sStar2->setVisible(true);
			this->sStar3->setVisible(false);
			this->sStarDark1->setVisible(true);
			this->sStarDark2->setVisible(true);
			this->sStarDark3->setVisible(true);
            
            this->sLogoPay->setVisible(false);
			break;
		case GK_Star3:
			guankaframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(guanka);
			this->setDisplayFrame(guankaframe);
			this->sLock->setVisible(false);
			this->sNumber->setVisible(true);
			this->sStar1->setVisible(true);
			this->sStar2->setVisible(true);
			this->sStar3->setVisible(true);
			this->sStarDark1->setVisible(true);
			this->sStarDark2->setVisible(true);
			this->sStarDark3->setVisible(true);
            
            this->sLogoPay->setVisible(false);
			break;
        case GK_UNPAY:
			darkGuankaframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_Image_GK_Dark);
			this->setDisplayFrame(darkGuankaframe);
			this->sLock->setVisible(false);
			this->sNumber->setVisible(false);
			this->sStar1->setVisible(false);
			this->sStar2->setVisible(false);
			this->sStar3->setVisible(false);
			this->sStarDark1->setVisible(false);
			this->sStarDark2->setVisible(false);
			this->sStarDark3->setVisible(false);
            
            this->sLogoPay->setVisible(true);
            
			break;
		default:
			return;
	}
    
    
    this->setVisible(true);
}