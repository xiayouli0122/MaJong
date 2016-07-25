#include "StoreLayer.h"
#include "Common/ConstantDef.h"
#include "AppDelegate.h"
#include "CallJni.h"

#define TOWRMBTAG 52014
#define FOURRMBTAG 52015
#define SIXRMBTAG 52016
#define CANLETAG 52017

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h> 
#include "platform/android/jni/JniHelper.h" 
#include <android/log.h>

#endif

CStoreLayer::CStoreLayer(void)
	:
	m_pMessage( NULL )
{
}

CStoreLayer::~CStoreLayer(void)
{
}

bool CStoreLayer::init()
{
	if ( !CCLayer::init() )
		return false;

	CCLayerColor*	player = CCLayerColor::create(ccc4( 0, 0, 0, 50));
	this->addChild(player);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCTextureCache::sharedTextureCache()->addImage(CONS_DefaultStoreBackGround);

 	CCSprite* pSprite = CCSprite::create( CONS_DefaultStoreBackGround );
 	pSprite->setPosition( ccp( size.width/2, size.height/2 ) );
 	this->addChild( pSprite );

	CCSize sPSize = this->getContentSize();

	CCSprite * ci1 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Cancel);
	CCSprite * ci12 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Cancel_2);

	CCMenuItemSprite* pCancel = CCMenuItemSprite::create(ci1,ci12,NULL,this,
		menu_selector(CStoreLayer::CanleCallback));
	pCancel->setPosition( ccp(size.width*0.9,size.height*0.1) ); 
	pCancel->setTag( CANLETAG );

	CCSprite* ci3 = CCSprite::create( "Image/Menu_new/TowRMB.png" );
	CCSprite* ci4 = CCSprite::create( "Image/Menu_new/FourRMB.png" );
	CCSprite* ci5 = CCSprite::create( "Image/Menu_new/SixRMB.png" );

	CCMenuItemSprite* pTow = CCMenuItemSprite::create(ci3,ci3,NULL,this,
		menu_selector(CStoreLayer::CanleCallback));
	pTow->setPosition( ccp(sPSize.width / 2, sPSize.height * 0.7 ) ); 
	pTow->setTag( TOWRMBTAG );

	CCMenuItemSprite* pFour = CCMenuItemSprite::create(ci4,ci4,NULL,this,
		menu_selector(CStoreLayer::CanleCallback));
	pFour->setPosition( ccp(sPSize.width/ 2, sPSize.height * 0.5 ) ); 
	pFour->setTag( FOURRMBTAG );

	CCMenuItemSprite* pSix = CCMenuItemSprite::create(ci5,ci5,NULL,this,
		menu_selector(CStoreLayer::CanleCallback));
	pSix->setPosition( ccp(sPSize.width / 2, sPSize.height * 0.3) ); 
	pSix->setTag( SIXRMBTAG );

	CCMenu* pMenu = CCMenu::create( pCancel, pTow, pFour, pSix, NULL );
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 999);		

	this->setTouchEnabled( true );

	AppDelegate::cur_scene_flag = shop_layer;
	AppDelegate::g_pLayer = this;

	return true;
}

void CStoreLayer::CanleCallback( CCObject* pSender )
{
	CCMenuItemSprite* pItem = ( CCMenuItemSprite* )pSender;

	switch ( pItem->getTag() )
	{
	case TOWRMBTAG:
		{
			CallJni::forGet1Goal();
		}
		break;
	case FOURRMBTAG:
		{
			CallJni::forGet5Goal();
		}
		break;
	case SIXRMBTAG:
		{
			CallJni::forGet10Goal();
		}
		break;
	case CANLETAG:
		this->removeFromParent();
		break;
	default:
		break;
	}
}

void CStoreLayer::billCallbackFor1Goal()
{
	int num = GetIntegerToXML( UD_SINGLE_COIN );
	num += 10000;
	SetIntegerToXML(UD_SINGLE_COIN, num);

	m_pMessage = GameMessage::create();
	this->addChild( m_pMessage, 1000 );
	m_pMessage->SetMessageType( MT_BUY_TOW_COIN );
}

void CStoreLayer::billCallbackFor5Goal()
{
	int num = GetIntegerToXML( UD_SINGLE_COIN );
	num += 50000;
	SetIntegerToXML(UD_SINGLE_COIN, num);

	m_pMessage = GameMessage::create();
	this->addChild( m_pMessage, 1000 );
	m_pMessage->SetMessageType( MT_BUY_FOUR_COIN );
}

void CStoreLayer::billCallbackFor10Goal()
{
	int num = GetIntegerToXML( UD_SINGLE_COIN );
	num += 100000;
	SetIntegerToXML(UD_SINGLE_COIN, num);

	m_pMessage = GameMessage::create();
	this->addChild( m_pMessage, 1000 );
	m_pMessage->SetMessageType( MT_BUY_SIX_COIN );
}
