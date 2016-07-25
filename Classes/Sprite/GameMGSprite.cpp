#include "GameMGSprite.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "MenuScene.h"
#include "CommonFunction.h"

#else 

#include "../Scene/MenuScene.h"
#include "../Common/CommonFunction.h"

#endif

using namespace cocos2d;

GameMGSprite::GameMGSprite(void)
{
}


GameMGSprite::~GameMGSprite(void)
{
}

bool GameMGSprite::init()
{
    if(!CCSprite::init())
    {
        return false;
    }
    
    return true;
}

//通过图片名创建关卡对象
GameMGSprite* GameMGSprite::mgWithFrameName(MOREGAME * mg)
{
	GameMGSprite* pGameMGSprite = new GameMGSprite();
	pGameMGSprite->initWithSpriteFrameName(CONS_Image_MG_List);
	pGameMGSprite->autorelease();
    
	CCSize cjSize = pGameMGSprite->getContentSize();
    
	/////////////////////////////
	//加入按钮
	CCSprite* retSprite = CCSprite::createWithSpriteFrameName(mg->ico);
    
    CCMenuItemSprite *pItem0 = CCMenuItemSprite::create(retSprite,NULL,NULL,pGameMGSprite, 
                                                                      menu_selector(GameMGSprite::menuBackCallback));
	pItem0->setPosition( ccp(cjSize.width*0.15, cjSize.height*0.5) ); 
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pItem0, NULL);
	pMenu->setPosition( CCPointZero );
	pGameMGSprite->addChild(pMenu, 1);
    
	// 加入一个 label
	CCLabelTTF* pLabeTitle2 = CCLabelTTF::create(mg->name, "Verdana-Bold", CommonFunction::GetValueByDev(12));
	pLabeTitle2->setPosition( ccp(cjSize.width*0.55, cjSize.height*0.5) );
	pLabeTitle2->setColor(CCPauseContent);
	pGameMGSprite->addChild(pLabeTitle2, 2);
	pGameMGSprite->moreGame = mg;
    
	return pGameMGSprite;
}


void GameMGSprite::menuBackCallback(CCObject* pSender)
{
    CommonFunction::openURL(moreGame->url);
}