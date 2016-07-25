#include "GameCjSprite.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSCommon.h"
#endif

using namespace cocos2d;

GameCjSprite::GameCjSprite(void)
{
}


GameCjSprite::~GameCjSprite(void)
{
}

bool GameCjSprite::init()
{
    if(!CCSprite::init())
    {
        return false;
    }
    
    return true;
}

//通过图片名创建关卡对象
GameCjSprite* GameCjSprite::cjWithFrameName(CHENGJIU * cj, int cjIndex, CCSize itemSize)
{
	GameCjSprite* pGameCjSprite = new GameCjSprite();
     pGameCjSprite->initWithSpriteFrameName(CONS_Image_Cj_Light);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        //pGameCjSprite->init();
        cocos2d::CCSprite* bgSp = cocos2d::CCSprite::createWithSpriteFrameName(CONS_Image_Cj_Light);
        cocos2d::CCSize cjSize = pGameCjSprite->getContentSize();
        bgSp->setPosition(ccp(cjSize.width / 2,cjSize.height/2));
        pGameCjSprite->addChild(bgSp,0);
        bgSp->setScale(2.0f);
    }
#endif
    
  pGameCjSprite->autorelease();
    
	if(!GetBoolToXML(cj[cjIndex].key,false)){
		pGameCjSprite->initWithSpriteFrameName(CONS_Image_Cj_Dark);
	}

	// 加入一个 label
	CCLabelTTF* pLabeTitle1 = CCLabelTTF::create(CONS_STRING_CJ,"Verdana-Bold", CommonFunction::GetValueByDev(12));
	pLabeTitle1->setPosition( ccp(itemSize.width*0.3, itemSize.height*0.7) );
	pLabeTitle1->setColor(CCPauseTitle);
	pGameCjSprite->addChild(pLabeTitle1, 2);
    
	// 加入一个 label
	CCLabelTTF* pLabeTitle2 = CCLabelTTF::create(cj[cjIndex].name,"Verdana-Bold", CommonFunction::GetValueByDev(12));
	pLabeTitle2->setPosition( ccp(itemSize.width*0.5, itemSize.height*0.7) );
	pLabeTitle2->setColor(CCPauseContent);
	pGameCjSprite->addChild(pLabeTitle2, 2);
    
    // 加入一个 label
	char str[100];
	sprintf(str,"(%s)",cj[cjIndex].info);
	CCLabelTTF* pLabelContent = CCLabelTTF::create(str, "Verdana", CommonFunction::GetValueByDev(10));
    pLabelContent->setAnchorPoint(ccp(0,0.5));
	pLabelContent->setPosition( ccp(itemSize.width*0.2, itemSize.height*0.35) );
	pGameCjSprite->addChild(pLabelContent, 2);
    
    pGameCjSprite->setVisible(true);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        pLabeTitle1->setPosition(ccpSub(pLabeTitle1->getPosition(), ccp(0,30)));
        pLabeTitle2->setPosition(ccpSub(pLabeTitle2->getPosition(), ccp(0,30)));
        pLabelContent->setPosition(ccpSub(pLabelContent->getPosition(), ccp(0,30)));
    }
#endif
    
	return pGameCjSprite;
}