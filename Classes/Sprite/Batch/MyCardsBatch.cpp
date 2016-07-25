//
//  MyCardsBatch.cpp
//  xzdd
//
//  Created by  on 12-2-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MyCardsBatch.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "GameDesk.h"
#include "IOSCommon.h"
#else 

#include "../../Layer/GameDesk.h"

#endif

#define CONVERT_XY(X,Y,W,H) ccp((W)*((X)/1138.0),(H)*((640.0-(Y))/640.0))

using namespace cocos2d;

//#pragma mark -----------初始化-----------
bool MyCardsBatch::init()
{
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();
    dingQueType = PAI_TYPE_INVALID;     //初始化为没有定缺
    
    //循环初始化每一张牌
//     myCardArray = new CCMutableArray<MyCard*>;
//     enableTouchCardArray = new CCMutableArray<MyCard*>;
	myCardArray = CCArray::create();
	myCardArray->retain();
	enableTouchCardArray = CCArray::create();
	enableTouchCardArray->retain();
    for (int i=0; i<15; i++) {
        MyCard * myCard = MyCard::MyCardWithFrameName(CommonFunction::GetImageByByte(CT_HAND_P,1));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if(IOSCommon::IsIpad3())
        {
            myCard->setScale(2.0f);
        }
#endif
        this->addChild(myCard);
        myCardArray->addObject(myCard); //加入牌到数组
    }
    
    //初始化摸到的牌
    moCard = MyCard::MyCardWithFrameName(CommonFunction::GetImageByByte(CT_MO_P,1));
    CCSize cardSize = moCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        moCard->setScale(2.0f);
        cardSize = moCard->boundingBox().size;
    }
#endif

	if(winSize.width/winSize.height >= 1.775)
	{
		moCard->setPosition(ccp(ptPos.x + winSize.width - cardSize.width*2,cardSize.height/2));
	}
	else
	{
		 moCard->setPosition(ccp(ptPos.x + winSize.width - cardSize.width/2,cardSize.height/2));
	}

    //moCard->setPosition(ccp(winSize.width*0.914 - cardSize.width/2,cardSize.height/2));
    moCard->cardIndex = 13; //摸到的牌的索引 始终是13
    this->addChild(moCard);
    myCardArray->addObject(moCard);
    
    selectedCard = NULL;
    
    shadowCard = MyCard::MyCardWithFrameName(CommonFunction::GetImageByByte(CT_MO_P,1));
    shadowCard->setAnchorPoint(ccp(0.5,0));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        shadowCard->setScale(2.0f);
        shadowCard->setPosition(ccp(shadowCard->boundingBox().size.width / 2, shadowCard->boundingBox().size.height - shadowCard->getContentSize().height));
    }
#endif
    this->addChild(shadowCard);
    shadowCard->setVisible(false);

	return true;
}

void MyCardsBatch::onExit()
{
	myCardArray->removeAllObjects();
    myCardArray->release();   //手牌数组

	enableTouchCardArray->removeAllObjects();
    enableTouchCardArray->release();
    CCNode::onExit();
}

//#pragma mark -----------公用方法-----------
//通过逻辑对象，设置所有手牌
void MyCardsBatch::SetMyCard(PLAYER_DATA *playerData)
{
    mc_state = MC_AfterMo_ChooseOut;
//    CCMutableArray<MyCard*>::CCMutableArrayIterator card;
	CCObject **card;
    int index = 0;
    card = myCardArray->data->arr;
    
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();
    MyCard *cc =(MyCard*)*card;

    CCSize cardSize = cc->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        cardSize = cc->boundingBox().size;
    }
#endif
    //倒着放
    for (int k=2; k>=0; k--) {
        for (int j=playerData[0].nCard[k][0]; j>0; j--) {
            if(playerData[0].nCard[k][j] != 255)
            {
                MyCard *c =(MyCard*)*card;
                c->cardIndex = 12 - index; //计算牌的索引
				CCLog("The winsize is %f ,the winsize.hitht is%f, w/h is%f", winSize.width, winSize.height, winSize.width/winSize.height);
				if(winSize.width/winSize.height >= 1.775)
				{
					c->setPosition( ccp(ptPos.x + winSize.width-(3.2+index++)* cardSize.width, cardSize.height /2));
				}
				else
				{
					c->setPosition( ccp(ptPos.x + winSize.width-(1.9+index++)* cardSize.width, cardSize.height /2));
				}
				//c->setPosition( CONVERT_XY(winSize.width-(1.7 + index++)* cardSize.width, winSize.height*0.916,winSize.width,winSize.height));
				//c->setPosition( ccp(winSize.width*0.034+(1.7 + index++)* cardSize.width, cardSize.height /2));
				
                c->cardContent = playerData[0].nCard[k][j];
                char * fileName = CommonFunction::GetImageByByte(CT_HAND_P,c->cardContent);
                c->setDisplayFrameName(fileName);
                c->setColor( ccc3( 255,255,255));
                card++;
            }
        }
    }
    
    //多余的手牌设置为不可见
    while (index < 15) {
        MyCard *c =(MyCard*)*card;
        c->setVisible(false);
        card++;
        index++;
    }
    moCard->setColor( ccc3( 255,255,255));
}

//设置胡牌 亮牌
void MyCardsBatch::SetHU(BYTE huCard)
{
    setMoCard(huCard);
}
void MyCardsBatch::SetLIANG()
{
//    CCMutableArray<MyCard*>::CCMutableArrayIterator card;
	CCObject *item;
	CCARRAY_FOREACH(myCardArray, item)
	{
		Card *c =dynamic_cast<Card *>(item);
        if (c->isVisible()) {
            char * fileName = CommonFunction::GetImageByByte(CT_HU_P,c->cardContent);
            c->setDisplayFrameName(fileName);
        }
    }
    if (moCard->isVisible()) {
        char * fileName = CommonFunction::GetImageByByte(CT_HU_P,moCard->cardContent);
        moCard->setDisplayFrameName(fileName);
    }
}

//摸牌
void MyCardsBatch::MoCardActive(PLAYER_DATA *playerData)
{
    setMoCard(playerData[0].nCardTakenNow);
    setEnableCard();
}

//出牌后
void MyCardsBatch::OutCardActive(PLAYER_DATA *playerData)
{
    SetMyCard(playerData);
    //隐藏摸到的牌
    moCard->setVisible(false);
}

//设置当前状态为  "在动作菜单后 选择牌"
//standCard = 用户桌面牌
//haveWG=是否有弯杠选择
void MyCardsBatch::ChooseCardAfterAction(BYTE * cards)
{
    mc_state = MC_AfterAction_ChooseCard;
    
    //设置 可以被触摸到的牌
//    enableTouchCardArray->release();
//    enableTouchCardArray = new CCMutableArray<MyCard*>;
	enableTouchCardArray->removeAllObjects();
// 	enableTouchCardArray->release();
// 	enableTouchCardArray = CCArray::create();
// 	enableTouchCardArray->retain();
    
    //BYTE * cards = CommonFunction::GetAGEnableCards(playerData[0],standCard,haveWG);
    
//    CCMutableArray<MyCard*>::CCMutableArrayIterator eachCard;
	CCObject *item;
	CCARRAY_FOREACH(myCardArray, item)
	{
		MyCard* c = dynamic_cast<MyCard *>(item);
        if(c->isVisible())
        {
            if (c->cardContent == cards[0]
                || c->cardContent == cards[1]
                || c->cardContent == cards[2]
                || c->cardContent == cards[3])
            {
                c->setColor( ccc3( 255,255,255));
                enableTouchCardArray->addObject(c);
            }
            else
            {
                //标示牌为不可选
                c->setColor(CCDisable);
            }
        }
    }
}

//#pragma mark -----------触摸相关方法-----------
bool MyCardsBatch::touchBegan(CCTouch* touch)
{
    CCPoint touchPoint = touch->getLocationInView();
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
    touchSelectCard(touchPoint);
    return true;
}
void MyCardsBatch::touchEnded(CCTouch* touch)
{
    CCPoint touchPoint = touch->getLocationInView( );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
    
    if(selectedCard != NULL)
    {
        CCRect rect = selectedCard->boundingBox();
        if (touchPoint.y > rect.getMaxY())
        {
            //选择牌  如果有选中的牌，并且触摸点高于牌堆
            GameDesk * desk = (GameDesk *)getParent();
            desk->Action_ChooseCard(0,selectedCard->cardContent,selectedCard->cardIndex);
            selectedCard = NULL;
        }
    }
    shadowCard->setVisible(false);
}

void MyCardsBatch::touchCancelled(CCTouch* touch)
{}

void MyCardsBatch::touchMoved(CCTouch* touch)
{
    CCPoint touchPoint = touch->getLocationInView(  );
    touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );

    //处理影子牌
    if (selectedCard != NULL) {
        if (shadowCard->cardContent != selectedCard->cardContent) {
            shadowCard->cardContent = selectedCard->cardContent;
            char * fileName = CommonFunction::GetImageByByte(CT_HAND_P,selectedCard->cardContent);
            shadowCard->setDisplayFrameName(fileName);
        }
        shadowCard->setOpacity(150);
        shadowCard->setPosition(touchPoint);
        shadowCard->setVisible(true);
    }
    else
    {
        shadowCard->setVisible(false);
    }
    
    if(selectedCard != NULL)
    {
        CCRect rect = selectedCard->boundingBox();
        if (touchPoint.y >rect.getMaxY())
        {
            //如果移动时触摸点被选择的牌，不做处理
            return;
        }
        
        if(!rect.containsPoint(touchPoint))
        { 
            selectedCard->onTouchOut();
            selectedCard = NULL;
        }
        else
        {
            selectedCard->onTouchIn();
            return; //如果在一个已选的牌中移动，则不处理
        }
    }
    touchSelectCard(touchPoint);
}


//#pragma mark -----------私有方法-----------
//touch事件中，循环处理被选中的手牌
void MyCardsBatch::touchSelectCard(CCPoint touchLocation)
{
//    CCMutableArray<MyCard*>::CCMutableArrayIterator eachCard;
	CCArray* cardArray;
    
    //普通摸牌状态可以选所有的牌，选牌状态只能选指定牌
//     CCMutableArray<MyCard*>::CCMutableArrayIterator eachCardBegin;
//     CCMutableArray<MyCard*>::CCMutableArrayIterator eachCardEnd;
	CCObject ** eachCardBegin;
	CCObject ** eachCardEnd;
    if (mc_state == MC_AfterMo_ChooseOut) {
//         eachCardBegin   = myCardArray->data->arr;
//         eachCardEnd     = eachCardBegin + myCardArray->data->num -1;
		cardArray = myCardArray;
    }
    else if(mc_state == MC_AfterAction_ChooseCard 
            || mc_state == MC_DingQue_ChooseOut)
    {
//         eachCardBegin   = enableTouchCardArray->data->arr;
//         eachCardEnd     = eachCardBegin + myCardArray->data->num -1;
		cardArray = enableTouchCardArray;
    }
    
//    for (eachCard = eachCardBegin; eachCard != eachCardEnd; eachCard++)
	CCObject *item;
	CCARRAY_FOREACH(cardArray, item)
    {
        MyCard* c = dynamic_cast<MyCard *>(item);
        if(c->boundingBox().containsPoint(touchLocation))
        {
            if(selectedCard != NULL && selectedCard != c)
            {
                selectedCard->onTouchOut();
            }
            selectedCard = c;
            c->onTouched();
            
            if (c->c_state == cardNone) {
                selectedCard = NULL;
            }

            break;
        }
    }
}

//根据定缺类型，设置牌能否被选择，及牌的颜色
void MyCardsBatch::setEnableCard()
{
    if (dingQueType != PAI_TYPE_INVALID) {
        mc_state = MC_DingQue_ChooseOut;
        
        //设置 可以被触摸到的牌
//        enableTouchCardArray->release();
//        enableTouchCardArray = new CCMutableArray<MyCard*>;
		enableTouchCardArray->removeAllObjects();
// 		enableTouchCardArray->release();
// 		enableTouchCardArray = CCArray::create();
// 		enableTouchCardArray->retain();
        bool haveMustOutCard = false;
        
//        CCMutableArray<MyCard*>::CCMutableArrayIterator eachCard;
		CCObject *item;
		CCARRAY_FOREACH(myCardArray, item)
		{
			MyCard* c = dynamic_cast<MyCard *>(item);
            if(c->isVisible())
            {
                if (CommonFunction::GetCardTypeByContent(c->cardContent) == dingQueType) {
                    haveMustOutCard = true;
                    break;
                }
            }
        }
        
		CCARRAY_FOREACH(myCardArray, item)
		{
			MyCard* c = dynamic_cast<MyCard *>(item);
            if(c->isVisible())
            {
                if (haveMustOutCard) {
                    if (CommonFunction::GetCardTypeByContent(c->cardContent) == dingQueType) {
                        enableTouchCardArray->addObject(c);
                    }
                    else
                    {
                        c->setColor(CCDisable);//标示牌为不可选
                    }
                }
                else
                {
                    enableTouchCardArray->addObject(c);
                }
            }
        }
    }
}

//获取需要强制出牌的索引 定缺时使用
MyCard * MyCardsBatch::GetForceOutCard()
{
//    CCMutableArray<MyCard*>::CCMutableArrayIterator eachCard;
    MyCard* c;
    if (dingQueType != PAI_TYPE_INVALID) {
		CCObject *item;
		CCARRAY_FOREACH(enableTouchCardArray, item)
		{
			c = dynamic_cast<MyCard *>(item);
            //优先打第十三张牌
            if(c->cardIndex == 13)
            {
                return c;
            }
        }
    }
    else
    {
		CCObject *item;
		CCARRAY_FOREACH(myCardArray, item)
		{
			c = dynamic_cast<MyCard *>(item);
            //优先打第十三张牌
            if(c->cardIndex == 13)
            {
                return c;
            }
        }
    }
    return c;
}

//设置摸牌
void MyCardsBatch::setMoCard(BYTE card)
{
    moCard->setVisible(true);
    moCard->cardContent= card;
    moCard->setPosition(ccp(moCard->getPosition().x,moCard->getContentSize().height/2));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IOSCommon::IsIpad3())
    {
        moCard->setScale(2.0f);
        moCard->setPosition(ccp(moCard->getPosition().x,moCard->boundingBox().size.height/2));
    }
#endif
    char * fileName = CommonFunction::GetImageByByte(CT_MO_P,card);
    moCard->setDisplayFrameName(fileName);
}

