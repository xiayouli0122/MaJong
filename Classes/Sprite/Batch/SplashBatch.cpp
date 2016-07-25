//
//  SplashBatch.cpp
//  xzdd
//
//  Created by Paddy on 12-12-7.
//
//

#include "SplashBatch.h"
#include <string>


#include "../../Layer/SplashLayer.h"
#include "../../Scene/MenuScene.h"

//static const char* CONS_Image_SPLASH_PAGE = "Image/splash/splash%d.jpg";
//static const char* CONS_IMG_BTN_SPLASH_ENTRANCE_1 = "Image/splash/enternormal.png";
//static const char* CONS_IMG_BTN_SPLASH_ENTRANCE_2 = "Image/splash/enterselect.png";

using namespace cocos2d;

//初始化--------------------------------------------------
bool SplashBatch::init()
{
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //循环初始化
//    pSpPageArray = new CCMutableArray<CCSprite*>;
	pSpPageArray = CCArray::create();
	pSpPageArray->retain();
    CCSprite * pSprite;
    char path[128];
    for (int i=0; i<PAGE_NUM; i++)
    {
        sprintf(path, CONS_Image_SPLASH_PAGE, i+1);
        pSprite = CCSprite::create(path);
        pSpPageArray->addObject(pSprite); //加入到数组
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        if(IOSCommon::IsIpad3())
//        {
//            pSprite->setScale(2.0f);
//        }
#endif
		float ratioX = 1.0f;
		float ratioY = 1.0f;
		float design,device;

		design=pSprite->getContentSize().width/ pSprite->getContentSize().height;

		device=winSize.width/winSize.height;
		ratioX = winSize.width / pSprite->getContentSize().width;
		ratioY = winSize.height / pSprite->getContentSize().height;
		pSprite->setScaleX(ratioX);
		pSprite->setScaleY(ratioY);
		//if(design==device)
		//{
		//	CCLog("1111111111111111111111111");
			//按高度宽度适配均可
		//	 ratioX = winSize.width / pSprite->getContentSize().width;
		//	 ratioY = winSize.height / pSprite->getContentSize().height;
		//	 pSprite->setScaleX(ratioX);
		//	 pSprite->setScaleY(ratioY);
		//}
		//else if(design>device)
		//{
			//按高度适配
		///	 CCLog("222222222222222222222222");
		//	 ratioY = winSize.height / pSprite->getContentSize().height;
		//	 pSprite->setScaleX(ratioY);
		//	 pSprite->setScaleY(ratioY);
		//}
		//else if(design<device)
		//{
			//按宽度适配
		//	 CCLog("3333333333333333333333333");
		//	 ratioX = winSize.width / pSprite->getContentSize().width;
		//	 pSprite->setScaleX(ratioX);
		//	 pSprite->setScaleY(ratioX);
		//}

		pSprite->setAnchorPoint(ccp(0.5, 0.5));
        pSprite->setPosition( ccp(ptPos.x + winSize.width/2 + winSize.width*i, winSize.height/2) );
        pSprite->setVisible(true);
        this->addChild(pSprite, 0);
    }
    
    CCTexture2D* texSplashSel = CCTextureCache::sharedTextureCache()->addImage(CONS_IMG_BTN_SPLASH_ENTRANCE_1);
    CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texSplashSel,CCRectMake(0,0,texSplashSel->getContentSize().width,texSplashSel->getContentSize().height));
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, CONS_IMG_BTN_SPLASH_ENTRANCE_1);
    
    texSplashSel = CCTextureCache::sharedTextureCache()->addImage(CONS_IMG_BTN_SPLASH_ENTRANCE_2);
    frame = CCSpriteFrame::createWithTexture(texSplashSel,CCRectMake(0,0,texSplashSel->getContentSize().width,texSplashSel->getContentSize().height));
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, CONS_IMG_BTN_SPLASH_ENTRANCE_2);
    
    
    
    // 加入菜单
    CCSprite * btn_entrance_1 = CCSprite::createWithSpriteFrameName(CONS_IMG_BTN_SPLASH_ENTRANCE_1);
    CCSprite * btn_entrance_2 = CCSprite::createWithSpriteFrameName(CONS_IMG_BTN_SPLASH_ENTRANCE_2);
    

    
    pItemEntrance = CCMenuItemSprite::create(btn_entrance_1,btn_entrance_2,NULL,this,menu_selector(SplashBatch::menuCallback));
   
    pItemEntrance->setAnchorPoint(ccp(1, 0));
	pItemEntrance->setPosition( ccp(ptPos.x + winSize.width*0.98, winSize.height*0.02) );

    CCMenu* pMenu = CCMenu::create(pItemEntrance,0);
    pMenu->setPosition(ccp(0,0));
    
   ((CCSprite*)pSpPageArray->lastObject())->addChild(pMenu, 1);

	return true;
}


void SplashBatch::onExit()
{
	pSpPageArray->removeAllObjects();
    pSpPageArray->release();
    CCLayer::onExit();
//    CCNode::onExit();
}

bool SplashBatch::onTouchSelected(CCPoint touchPoint)
{
    CCMenuItemSprite *p = pItemEntrance;
    
    CCRect rect = p->boundingBox();
    rect.origin = ccpAdd(getPosition(), rect.origin);
    if(rect.containsPoint(touchPoint))
    {
        CCLOG("splash entrance detect");
        ((SplashLayer *)this->getParent())->onEntrance();
        return true;
    }

    return false;
}


void SplashBatch::menuCallback(CCObject* pSender)
{
    CCLOG("splash entrance");
    //((SplashLayer *)this->getParent())->onEntrance();
    this->getParent()->removeFromParentAndCleanup(true);
}

