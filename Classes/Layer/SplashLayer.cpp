//
//  SplashLayer.cpp
//  xzdd
//
//  Created by Paddy on 12-12-7.
//
//

#include "SplashLayer.h"


//#include "../Common/MyTinyXmlParser.h"
#include "../Scene/MenuScene.h"


//const static char* CONS_Image_SPLASH_Selected = "Image/splash/pointselect.png";
//const static char* CONS_Image_SPLASH_Unselected = "Image/splash/poinback.png";
//
//static const char* CONS_IMG_BTN_SPLASH_ENTRANCE_1 = "Image/splash/enternormal.png";
//static const char* CONS_IMG_BTN_SPLASH_ENTRANCE_2 = "Image/splash/enterselect.png";

using namespace cocos2d;

//初始化--------------------------------------------------
bool SplashLayer::init()
{
	//super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    CCLOG("SplashLayer::init()");
    this->setTouchEnabled(true);
    
	isMoveActionRunning = false;
    bTouchFlag = false;
    
    //加入所有
    splashBatch = SplashBatch::create();
    this->addChild(splashBatch, 1);
    
    nPage = 0;
    
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCTexture2D* texSplashSel = CCTextureCache::sharedTextureCache()->addImage(CONS_Image_SPLASH_Selected);
    CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texSplashSel,CCRectMake(0,0,texSplashSel->getContentSize().width,texSplashSel->getContentSize().height));
                                                           
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, CONS_Image_SPLASH_Selected);
    
    texSplashSel = CCTextureCache::sharedTextureCache()->addImage(CONS_Image_SPLASH_Unselected);
    frame = CCSpriteFrame::createWithTexture(texSplashSel,CCRectMake(0,0,texSplashSel->getContentSize().width,texSplashSel->getContentSize().height));
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, CONS_Image_SPLASH_Unselected);
    
    
//	ping1 = CCSprite::create(CONS_Image_SPLASH_Selected);//splash屏1
//	ping1->setPosition( ccp(winSize.width*0.45, winSize.height*0.1) );
//	ping1->setVisible(true);
//	this->addChild(ping1, 3);
//    
//	ping2 = CCSprite::create(CONS_Image_SPLASH_Unselected);//splash屏2
//	ping2->setPosition( ccp(winSize.width*0.5, winSize.height*0.1) );
//	ping2->setVisible(true);
//	this->addChild(ping2, 3);
//    
//    ping3 = CCSprite::create(CONS_Image_SPLASH_Unselected);//splash屏3
//	ping3->setPosition( ccp(winSize.width*0.55, winSize.height*0.1) );
//	ping3->setVisible(true);
//	this->addChild(ping3, 3);
//    
//    ping4 = CCSprite::create(CONS_Image_SPLASH_Unselected);//splash屏3
//	ping4->setPosition( ccp(winSize.width*0.60, winSize.height*0.1) );
//	ping4->setVisible(true);
//	this->addChild(ping4, 3);
    
//    _pIndexArray = new CCMutableArray<CCSprite*>;
	_pIndexArray = CCArray::create();
	_pIndexArray->retain();
    
    CCSprite * pSprite;
    float fSpace = 0.05;
    for (int i=0; i<PAGE_NUM; i++)
    {
//        pSprite = CCSprite::create();
        if (i==0) {
            pSprite = CCSprite::create(CONS_Image_SPLASH_Selected);
        }
        else{
            pSprite = CCSprite::create(CONS_Image_SPLASH_Unselected);
        }
        _pIndexArray->addObject(pSprite); //加入到数组
        float fPos = 0.5-(PAGE_NUM-1)*fSpace/2+i*fSpace;
        pSprite->setPosition( ccp(ptPos.x + winSize.width*fPos, winSize.height*0.1) );
        pSprite->setVisible(true);
        this->addChild(pSprite, 3);
    }
        
	return true;
}

void SplashLayer::onExit()
{
	_pIndexArray->removeAllObjects();
	_pIndexArray->release();
    CCLayer::onExit();
}


//触摸相关方法---------------------------------------------
void SplashLayer::registerWithTouchDispatcher()
{
//    CCLOG("SplashLayer::registerWithTouchDispatcher()");
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
   // CCLayer::registerWithTouchDispatcher();
}

bool SplashLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
	if(isMoveActionRunning)
    {//如果移屏动画正在运行，则不响应触屏事件
        bTouchFlag = false;
		return true;
	}
    
    bTouchFlag = true;
    
    x_begin = touchPoint.x;
	x_batch_location_begin = splashBatch->getPosition().x;
    
    //    CCLOG("nPage: %d, xbegin:%f, xbatch:%f", nPage, x_begin, x_batch_location_begin);
    
	return true;
}

void SplashLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    if (!bTouchFlag)
    {//如果移屏动画正在运行，则不响应触屏事件
		return;
	}
    CCPoint touchPoint = touch->getLocationInView(  );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
	x_end = touchPoint.x;
//    if (x_end-x_begin > -5 && x_end-x_begin < 5)
//    {
//        if(splashBatch->onTouchSelected(touchPoint))
//        {
//            return;
//        }
//    }
	CCSpriteFrame *selectedFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_Image_SPLASH_Selected);
	CCSpriteFrame *unSelectedFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CONS_Image_SPLASH_Unselected);
    
	isMoveActionRunning = true;//开始移屏动画
    //    CCLOG("nPage: %d", nPage);
    
    int i;
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    
	if(x_end - x_begin > 50)
    {//右移
        if (nPage == 0)
        {
            isMoveActionRunning = false;
            return;
        }
        
        for (i=0; i<PAGE_NUM; ++i) {
            if (i == nPage-1) {
                ((CCSprite*)_pIndexArray->objectAtIndex(i))->setDisplayFrame(selectedFrame);
            }
            else
            {
                ((CCSprite*)_pIndexArray->objectAtIndex(i))->setDisplayFrame(unSelectedFrame);
            }
        }
        
        CCActionInterval*  actionTo = CCMoveTo::create(0.5, CCPointMake(-winSize.width*(nPage-1), 0));
        
        CCAction *sequneceAction = CCSequence::create(actionTo,//移屏动画
                                                       CCCallFunc::create(this, callfunc_selector(SplashLayer::moveActionCallback)),//结束动画用的回调
                                                       NULL);
        splashBatch->runAction(sequneceAction);
        nPage--;
        
	}
    else if(x_end - x_begin < -50)
    {//左移
        if (nPage == PAGE_NUM-1)
        {
            isMoveActionRunning = false;
            return;
        }
        
        for (i=0; i<PAGE_NUM; ++i) {
            if (i == nPage +1) {
                ((CCSprite*)_pIndexArray->objectAtIndex(i))->setDisplayFrame(selectedFrame);
            }
            else
            {
                ((CCSprite*)_pIndexArray->objectAtIndex(i))->setDisplayFrame(unSelectedFrame);
            }
        }
        
        CCActionInterval*  actionTo = CCMoveTo::create(0.5, ccp(-winSize.width*(nPage+1),0));
        CCAction *sequneceAction = CCSequence::create(actionTo,//移屏动画
                                                       CCCallFunc::create(this, callfunc_selector(SplashLayer::moveActionCallback)),//结束动画用的回调
                                                       NULL);
        splashBatch->runAction(sequneceAction);
        nPage++;
        
	}
    else{//恢复初始位置
		CCActionInterval*  actionTo = CCMoveTo::create(0.5, ccp(x_batch_location_begin,0));
        CCAction *sequneceAction = CCSequence::create(actionTo,//移屏动画
                                                       CCCallFunc::create(this, callfunc_selector(SplashLayer::moveActionCallback)),//结束动画用的回调
                                                       NULL);
		splashBatch->runAction(sequneceAction);
	}
	
}

void SplashLayer::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
    CCLOG("ccTouchCancelled");
}

void SplashLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    if (!bTouchFlag)
    {//如果移屏动画正在运行，则不响应触屏事件
		return;
	}
    CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
    
    if (touchPoint.x > x_begin && nPage == 0)
    {
        isMoveActionRunning = false;
        return;
    }
    
    if (touchPoint.x < x_begin && nPage == PAGE_NUM-1)
    {
        isMoveActionRunning = false;
        //        splashBatch->onTouchMove(touchPoint);
        return;
    }
    
    splashBatch->setPosition(ccp(x_batch_location_begin + touchPoint.x - x_begin,0));
}

void SplashLayer::moveActionCallback()
{
	isMoveActionRunning = false;//结束移屏动画
    
}


void SplashLayer::keyBackClicked()
{
    //	((GuanKaScene *)this->getParent())->onBack();
}

void SplashLayer::onEntrance()
{
    //((MenuScene *)this->getParent())->menuSplashEntranceCallback(splashBatch);
}

// void SplashLayer::menuCallback(CCObject* pSender)
// {
//     CCLOG("splash entrance");
//     //((SplashLayer *)this->getParent())->onEntrance();
//     this->removeFromParentAndCleanup(true);
// }

