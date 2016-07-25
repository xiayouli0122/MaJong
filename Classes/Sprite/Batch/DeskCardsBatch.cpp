//
//  DeskCardsBatch.cpp
//  xzdd
//
//  Created by  on 12-3-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.


#include <iostream>
#include "DeskCardsBatch.h"
#include <string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSCommon.h"
#endif


using namespace cocos2d;

//#pragma mark ----------------初始化--------------------
bool DeskCardsBatch::init()
{
	if (CommonFunction::isIpad()) {
		deskCardsBatchNode = CCSpriteBatchNode::create(CONS_DefaultMjFrameImage_Ipad);
	}else {
		deskCardsBatchNode = CCSpriteBatchNode::create(CONS_DefaultMjFrameImage);
	}
	this->addChild(deskCardsBatchNode);

	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptPos = CCDirector::sharedDirector()->getVisibleOrigin();

	//初始化所有数组
	CardsArrayShand = CCArray::create();
	CardsArrayShand->retain();

	CardsArrayXhand = CCArray::create();
	CardsArrayXhand->retain();

	CardsArrayDhand = CCArray::create();
	CardsArrayDhand->retain();

	CardsArraySstand = CCArray::create();
	CardsArraySstand->retain();

	CardsArrayXstand = CCArray::create();
	CardsArrayXstand->retain();

	CardsArrayDstand = CCArray::create();
	CardsArrayDstand->retain();

	CardsArrayPlayerstand = CCArray::create();
	CardsArrayPlayerstand->retain();

	CardsArrayStable = CCArray::create();
	CardsArrayStable->retain();

	CardsArrayXtable = CCArray::create();
	CardsArrayXtable->retain();

	CardsArrayDtable = CCArray::create();
	CardsArrayDtable->retain();

	CardsArrayPlayertable = CCArray::create();
	CardsArrayPlayertable->retain();

	CardsArrayPWall = CCArray::create();
	CardsArrayPWall->retain();

	CardsArraySWall = CCArray::create();
	CardsArraySWall->retain();

	CardsArrayDWall = CCArray::create();
	CardsArrayDWall->retain();

	CardsArrayXWall = CCArray::create();
	CardsArrayXWall->retain();

	CardsArrayOut = CCArray::create();
	CardsArrayOut->retain();

	CardsArrayMo = CCArray::create();
	CardsArrayMo->retain();


	//循环初始化牌墙
	for (int i=0; i<26; i++) {

		Card * myCard;
		CCSize cardSize;
		//玩家
		myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_WALL_P,1));
		cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		if(IOSCommon::IsIpad3())
		{
			myCard->setScale(2.0f);
			cardSize = myCard->boundingBox().size;
		}
#endif
		myCard->setPosition( ccp(ptPos.x + winSize.width * 0.3 + cardSize.width * (i/2),
			winSize.height * 0.2 + cardSize.height*0.3*(i%2)) );
		myCard->setVisible(true);
		deskCardsBatchNode->addChild(myCard);
		CardsArrayPWall->addObject(myCard);

		//上家，牌墙需要倒牌 
		//上家
		myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_WALL_S,1));
		cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		if(IOSCommon::IsIpad3())
		{
			myCard->setScale(2.0f);
			cardSize = myCard->boundingBox().size;
		}
#endif
		myCard->setPosition( ccp(ptPos.x + winSize.width * 0.18,
			winSize.height * 0.78 - cardSize.height *0.7 * (i/2) + cardSize.height*0.4*(i%2)) );
		myCard->setVisible(true);
		deskCardsBatchNode->addChild(myCard);
		CardsArraySWall->addObject(myCard);



		//对家
		myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_WALL_D,1));
		cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		if(IOSCommon::IsIpad3())
		{
			myCard->setScale(2.0f);
			cardSize = myCard->boundingBox().size;
		}
#endif
		myCard->setPosition( ccp(ptPos.x + winSize.width * 0.7 - cardSize.width * (i/2),
			winSize.height * 0.86 + cardSize.height*0.3*(i%2)) );
		myCard->setVisible(true);
		deskCardsBatchNode->addChild(myCard);
		CardsArrayDWall->addObject(myCard);

		//下家
		myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_WALL_X,1));
		cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		if(IOSCommon::IsIpad3())
		{
			myCard->setScale(2.0f);
			cardSize = myCard->boundingBox().size;
		}
#endif
		myCard->setPosition( ccp(ptPos.x + winSize.width * 0.83,
			winSize.height * 0.78 - cardSize.height *0.7* (i/2) + cardSize.height*0.4*(i%2)) );
		myCard->setVisible(true);
		deskCardsBatchNode->addChild(myCard);
		CardsArrayXWall->addObject(myCard);
	}


	//循环初始化手牌---------------------------------------
	for (int j=0; j<3; j++) {
		Card * myCard;
		CCSize cardSize;       
		for (int i=0; i<13; i++) {

			switch (j) {
			case 0: //上家
				myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_HAND_S,1));
				cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				if(IOSCommon::IsIpad3())
				{
					myCard->setScale(2.0f);
					cardSize = myCard->boundingBox().size;
				}
#endif
				myCard->setPosition( ccp(ptPos.x + winSize.width * 0.13, 
					winSize.height*0.31 + i * cardSize.height*0.60) );
				CardsArrayShand->addObject(myCard); //加入到AI上家手牌数组
				break;
			case 1: //对家
				myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_HAND_D,1));
				cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				if(IOSCommon::IsIpad3())
				{
					myCard->setScale(2.0f);
					cardSize = myCard->boundingBox().size;
				}
#endif
				myCard->setPosition( ccp(ptPos.x + winSize.width *0.36 + i*cardSize.width, 
					winSize.height - cardSize.height*0.6) ); //倒着放
				CardsArrayDhand->addObject(myCard); //加入到AI对家手牌数组
				deskCardsBatchNode->addChild(myCard);
				break;
			case 2: //下家
				myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_HAND_X,1));
				cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				if(IOSCommon::IsIpad3())
				{
					myCard->setScale(2.0f);
					cardSize = myCard->boundingBox().size;
				}
#endif
				myCard->setPosition( ccp(ptPos.x + winSize.width * 0.87, 
					winSize.height*0.80 - i * cardSize.height*0.60) ); //倒着放
				CardsArrayXhand->addObject(myCard); //加入到AI下家手牌数组
				deskCardsBatchNode->addChild(myCard);
				break;
			default:
				break;
			}

		}
		//上家的牌，倒着加入显示。 显示重叠需要
		if (j == 0) {
			for (int i=12; i>=0; i--) {
				deskCardsBatchNode->addChild((Card*)CardsArrayShand->objectAtIndex(i));
			}
		}

		//初始化摸到的牌
		Card * moCard;
		switch (j) {
		case 0://上家
			moCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_MO_S,1));
			cardSize = moCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			if(IOSCommon::IsIpad3())
			{
				moCard->setScale(2.0f);
				cardSize = myCard->boundingBox().size;
			}
#endif
			moCard->setPosition( ccp(ptPos.x + winSize.width * 0.13, 
				winSize.height*0.31 - cardSize.height*1.2) );
			break;
		case 1://对家
			moCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_MO_D,1));
			cardSize = moCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			if(IOSCommon::IsIpad3())
			{
				moCard->setScale(2.0f);
				cardSize = myCard->boundingBox().size;
			}
#endif
			moCard->setPosition( ccp(ptPos.x + winSize.width *0.36 - cardSize.width*1.2, 
				winSize.height - cardSize.height*0.6) );
			break;
		case 2://下家
			moCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_MO_X,1));
			cardSize = moCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			if(IOSCommon::IsIpad3())
			{
				moCard->setScale(2.0f);
				cardSize = myCard->boundingBox().size;
			}
#endif
			moCard->setPosition( ccp(ptPos.x + winSize.width * 0.87, 
				winSize.height*0.80 + cardSize.height* 1.2) );
			break;

		default:
			break;
		}
		deskCardsBatchNode->addChild(moCard);
		CardsArrayMo->addObject(moCard);

	}        

	for (int j=0; j<4; j++) {

		//循环初始化倒牌---------------------------------------
		for (int i=0; i<16; i++) {

			Card * myCard;
			CCSize cardSize;
			switch (j) {
			case 0://玩家
				myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_STAND_P,1));
				cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				if(IOSCommon::IsIpad3())
				{
					myCard->setScale(2.0f);
					cardSize = myCard->boundingBox().size;
				}
#endif
				if (i%4 == 3) {
					myCard->setPosition( ccp(ptPos.x + cardSize.width * (i-2+0.5 -i/4), cardSize.height*0.7));
				}
				else
				{
					myCard->setPosition( ccp(ptPos.x + cardSize.width * (i+0.5 - i/4),cardSize.height/2));
				}
				CardsArrayPlayerstand->addObject(myCard); //加入到玩家
				deskCardsBatchNode->addChild(myCard);
				break;
			case 1://上家
				myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_STAND_S,1));
				cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				if(IOSCommon::IsIpad3())
				{
					myCard->setScale(2.0f);
					cardSize = myCard->boundingBox().size;
				}
#endif
				if (i%4 == 3) {
					myCard->setPosition( ccp(ptPos.x + winSize.width * 0.13, 
						winSize.height*0.30 + (12.5-i+2+i/4) * cardSize.height*0.70
						+ cardSize.height *0.3) );                                                
				}
				else
				{
					myCard->setPosition( ccp(ptPos.x + winSize.width * 0.13, 
						winSize.height*0.30 + (12.5-i+i/4) * cardSize.height*0.70) );                        
				}
				CardsArraySstand->addObject(myCard); //加入到AI下家
				deskCardsBatchNode->addChild(myCard);
				break;
			case 2://对家
				myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_STAND_D,1));
				cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				if(IOSCommon::IsIpad3())
				{
					myCard->setScale(2.0f);
					cardSize = myCard->boundingBox().size;
				}
#endif
				if (i%4 == 3) {
					myCard->setPosition( ccp(ptPos.x + winSize.width *0.36 + (12.5-i+2 +i/4)*cardSize.width, 
						winSize.height - cardSize.height*0.4) );                                               
				}
				else
				{
					myCard->setPosition( ccp(ptPos.x + winSize.width *0.36 + (12.5-i + i/4)*cardSize.width, 
						winSize.height - cardSize.height*0.6) );                        
				}
				CardsArrayDstand->addObject(myCard); //加入到AI对家
				deskCardsBatchNode->addChild(myCard);
				break;
			case 3://下家
				myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_STAND_X,1));
				cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				if(IOSCommon::IsIpad3())
				{
					myCard->setScale(2.0f);
					cardSize = myCard->boundingBox().size;
				}
#endif
				if (i%4 == 3) {
					myCard->setPosition( ccp(ptPos.x + winSize.width * 0.87, 
						winSize.height*0.80 - (12.5-i+2+i/4) * cardSize.height*0.70
						+ cardSize.height *0.3) );                        
				}
				else
				{
					myCard->setPosition( ccp(ptPos.x + winSize.width * 0.87, 
						winSize.height*0.80 - (12.5-i+i/4) * cardSize.height*0.70) );
				}
				CardsArrayXstand->addObject(myCard); //加入到AI上家
				break;
			default:
				break;
			} 
		}
		//下家的牌，倒着加入显示。 显示重叠需要
		if (j==3) {
			for (int i = 4; i>0; i--) {
				deskCardsBatchNode->addChild((Card*)CardsArrayXstand->objectAtIndex(i*4-2));
				deskCardsBatchNode->addChild((Card*)CardsArrayXstand->objectAtIndex(i*4-3));
				deskCardsBatchNode->addChild((Card*)CardsArrayXstand->objectAtIndex(i*4-4));
				deskCardsBatchNode->addChild((Card*)CardsArrayXstand->objectAtIndex(i*4-1));
			}
		}


		//循环初始化桌面牌-------------------------------------

		for (int i=0; i<MAX_Card_Table; i++) {

			Card * myCard;
			CCSize cardSize;

			switch (j) {
			case 0://玩家 倒排
				myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_TABLE_P,1));
				cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				if(IOSCommon::IsIpad3())
				{
					myCard->setScale(2.0f);
					cardSize = myCard->boundingBox().size;
				}
#endif
				myCard->setPosition( ccp(ptPos.x + winSize.width*0.78 - cardSize.width * 0.95 * ((MAX_Card_Table-1-i)%14),
					winSize.height*0.3 + cardSize.height *0.8* ((MAX_Card_Table-1-i)/14)) );
				CardsArrayPlayertable->addObject(myCard); //加入到玩家
				break;
			case 1://上家 倒排
				myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_TABLE_S,1));
				cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				if(IOSCommon::IsIpad3())
				{
					myCard->setScale(2.0f);
					cardSize = myCard->boundingBox().size;
				}
#endif
				myCard->setPosition( ccp(ptPos.x + winSize.width * 0.23 + cardSize.width * ((MAX_Card_Table-1-i)/9),
					winSize.height*0.3 + cardSize.height*0.7 * ((MAX_Card_Table-1-i)%9)) );
				CardsArrayStable->addObject(myCard); //加入到AI下家
				break;
			case 2://对家
				myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_TABLE_D,1));
				cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				if(IOSCommon::IsIpad3())
				{
					myCard->setScale(2.0f);
					cardSize = myCard->boundingBox().size;
				}
#endif
				myCard->setPosition( ccp(ptPos.x + winSize.width *0.23 + cardSize.width * 0.95 * (i%14), 
					winSize.height * 0.77- cardSize.height *0.8* (i/14)) );
				CardsArrayDtable->addObject(myCard); //加入到AI对家
				break;
			case 3://下家
				myCard = Card::cardWithFrameName(CommonFunction::GetImageByByte(CT_TABLE_X,1));
				cardSize = myCard->getContentSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				if(IOSCommon::IsIpad3())
				{
					myCard->setScale(2.0f);
					cardSize = myCard->boundingBox().size;
				}
#endif
				myCard->setPosition( ccp(ptPos.x + winSize.width * 0.78 - cardSize.width * (i/9), 
					winSize.height*0.77 - cardSize.height*0.7 * (i%9)) );
				CardsArrayXtable->addObject(myCard); //加入到AI上家
				break;
			default:
				break;
			} 
			deskCardsBatchNode->addChild(myCard);
		}
	}

	//循环初始化当前打出的牌-------------------------------------
	for(int i=0;i<4;i++)
	{
		OutCard * outCard = OutCard::outCardWithFrameName(CommonFunction::GetImageByByte(CT_OUT,1));
		switch (i) {
		case 0://玩家
			outCard->setPosition( ccp(ptPos.x + winSize.width/2, winSize.height * 0.25) );
			break;
		case 1://上家
			outCard->setPosition( ccp(ptPos.x + winSize.width * 0.18, winSize.height * 0.55) );
			break;
		case 2://对家
			outCard->setPosition( ccp(ptPos.x + winSize.width/2, winSize.height * 0.82) );
			break;
		case 3://下家
			outCard->setPosition( ccp(ptPos.x + winSize.width * 0.82, winSize.height * 0.5) );
			break;

		default:
			break;
		}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		if(IOSCommon::IsIpad3())
		{
			outCard->setScale(2.0f);
		}
#endif
		deskCardsBatchNode->addChild(outCard);

		CardsArrayOut->addObject(outCard);
	}

	return true;
}

void DeskCardsBatch::onExit()
{
	CardsArrayPWall->removeAllObjects();
	CardsArrayPWall->release();

	CardsArraySWall->removeAllObjects();
	CardsArraySWall->release();

	CardsArrayDWall->removeAllObjects();
	CardsArrayDWall->release();

	CardsArrayXWall->removeAllObjects();
	CardsArrayXWall->release();

	//AI 手牌 （上，下，对）
	CardsArrayShand->removeAllObjects();
	CardsArrayShand->release();

	CardsArrayXhand->removeAllObjects();
	CardsArrayXhand->release();

	CardsArrayDhand->removeAllObjects();
	CardsArrayDhand->release();

	//倒牌 （上，下，对）
	CardsArraySstand->removeAllObjects();
	CardsArraySstand->release();

	CardsArrayXstand->removeAllObjects();
	CardsArrayXstand->release();

	CardsArrayDstand->removeAllObjects();
	CardsArrayDstand->release();

	CardsArrayPlayerstand->removeAllObjects();
	CardsArrayPlayerstand->release();

	//桌面牌 （上，下，对）
	CardsArrayStable->removeAllObjects();
	CardsArrayStable->release();

	CardsArrayXtable->removeAllObjects();
	CardsArrayXtable->release();

	CardsArrayDtable->removeAllObjects();
	CardsArrayDtable->release();

	CardsArrayPlayertable->removeAllObjects();
	CardsArrayPlayertable->release();

	//打出的牌
	CardsArrayOut->removeAllObjects();
	CardsArrayOut->release();
	//摸到的牌
	CardsArrayMo->removeAllObjects();
	CardsArrayMo->release();

	CCNode::onExit();
}

//#pragma mark -----------------设置牌------------------
//#pragma mark设置所有AI手牌
void DeskCardsBatch::SetCardHand(PLAYER_DATA *playerData)
{
//	CCMutableArray<Card*>::CCMutableArrayIterator card;
	CCObject** card;

	for (int i=0; i<4; i++) {
		//已经胡牌的玩家不处理
		if (playerData[i].nState == BLOOD_HU) {
			continue;
		}
		BYTE chair = CommonFunction::GetChair(m_Chair, i);
		if (chair == 0) {
			//如果是玩家，则跳过
			continue;
		}
		int count = 0;
		switch (chair) {
		case 1:
			card = CardsArrayShand->data->arr;
			break;
		case 2:
			card = CardsArrayDhand->data->arr;
			break;
		case 3:
			card = CardsArrayXhand->data->arr;
			break;

		default:
			break;
		}
		for (int k=2; k>=0; k--) {
			for (int j=playerData[i].nCard[k][0]; j>0; j--) {
				if(playerData[i].nCard[k][j] != 255)
				{
					Card *c =(Card*)*card;
					c->cardContent = playerData[i].nCard[k][j];
					char * fileName = CommonFunction::GetImageByByte(CT_HAND_S,c->cardContent);

					switch (chair) {
					case 1:
						fileName = CommonFunction::GetImageByByte(CT_HAND_S,c->cardContent);
						break;
					case 2:
						fileName = CommonFunction::GetImageByByte(CT_HAND_D,c->cardContent);
						break;
					case 3:
						fileName = CommonFunction::GetImageByByte(CT_HAND_X,c->cardContent);
						break;

					default:
						break;
					}

					c->setDisplayFrameName(fileName);

					card++;
					count++;
				}
			}
		}
		//多余的手牌设置为不可见
		while (count < 13) {
			Card *c =(Card*)*card;
			c->setVisible(false);
			card++;
			count++;
		}
	}
}

//#pragma mark设置胡牌
void DeskCardsBatch::SetHU(BYTE playIndex,BYTE huCard)
{

//	CCMutableArray<Card*>::CCMutableArrayIterator card;
	CCObject* item;
	char * fileName;
	CARDTYPE type;
	CARDTYPE huType;
	switch (playIndex) {
	case 1:
		{
			CCARRAY_FOREACH(CardsArrayShand, item)
			{
				Card *c =dynamic_cast<Card *>(item);
				if (c->isVisible()) {
					type = CT_HU_S;
					huType = CT_TABLE_S;
					fileName = CommonFunction::GetImageByByte(type,c->cardContent);
					c->setDisplayFrameName(fileName);
				}
			}
			break;
		}
	case 2:
		{
			CCARRAY_FOREACH(CardsArrayDhand, item)
			{
				Card *c =dynamic_cast<Card *>(item);
				if (c->isVisible()) {
					type = CT_HU_D;
					huType = CT_TABLE_D;
					fileName = CommonFunction::GetImageByByte(type,c->cardContent);
					c->setDisplayFrameName(fileName);
				}
			}
			break;
		}
	case 3:
		{
			CCARRAY_FOREACH(CardsArrayXhand, item)
			{
				Card *c =dynamic_cast<Card *>(item);
				if (c->isVisible()) {
					type = CT_HU_X;
					huType = CT_TABLE_X;
					fileName = CommonFunction::GetImageByByte(type,c->cardContent);
					c->setDisplayFrameName(fileName);
				}
			}
			break;
		}
	default:
		break;
	}

	//设置胡的那张牌
	Card *c = (Card *)CardsArrayMo->objectAtIndex(playIndex-1);
	c->cardContent = huCard;
	fileName = CommonFunction::GetImageByByte(huType,huCard);
	c->setDisplayFrameName(fileName);
	c->setVisible(true);
}
//#pragma mark设置亮牌
void DeskCardsBatch::SetLIANG(PLAYER_DATA * playerData)
{
//	CCMutableArray<Card*>::CCMutableArrayIterator card;
	CCObject* item;
	char * fileName;
	CARDTYPE type;
	for (int playIndex=1; playIndex<4; playIndex++) {
		switch (playIndex) {
		case 1:
			{
				CCARRAY_FOREACH(CardsArrayShand, item)
				{
					Card *c = dynamic_cast<Card *>(item);
					if (c->isVisible()) {
						type = CT_TABLE_S;
						fileName = CommonFunction::GetImageByByte(type,c->cardContent);
						c->setDisplayFrameName(fileName);
					}
				}
				break;
			}
		case 2:
			{
				CCARRAY_FOREACH(CardsArrayDhand, item)
				{
					Card *c = dynamic_cast<Card *>(item);
					if (c->isVisible()) {
						type = CT_TABLE_D;
						fileName = CommonFunction::GetImageByByte(type,c->cardContent);
						c->setDisplayFrameName(fileName);
					}
				}
				break;
			}
		case 3:
			{
				CCARRAY_FOREACH(CardsArrayXhand, item)
				{
					Card *c = dynamic_cast<Card *>(item);
					if (c->isVisible()) {
						type = CT_TABLE_X;
						fileName = CommonFunction::GetImageByByte(type,c->cardContent);
						c->setDisplayFrameName(fileName);
					}
				}
				break;
			}
		default:
			break;
		}

		//设置自摸的牌
		Card *c = (Card *)CardsArrayMo->objectAtIndex(playIndex-1);
		if (playerData[playIndex].nCardTakenNow == 255) {
			c->setVisible(false);
		}
		if (c->isVisible()) {
			fileName = CommonFunction::GetImageByByte(type,c->cardContent);
			c->setDisplayFrameName(fileName);
		}
	}
}

//#pragma mark设置所有AI倒牌
void DeskCardsBatch::SetCardStand(STAND_CARD *standCard)
{
//	CCMutableArray<Card*>::CCMutableArrayIterator card;
	CCObject **card;

	for (int i=0; i<4; i++) {
		CARDTYPE type = CT_STAND_P;
		CARDTYPE bType = CT_STAND_B_P;
		BYTE chair = CommonFunction::GetChair(m_Chair, i);
		switch (chair) {
		case 0:
			card = CardsArrayPlayerstand->data->arr;
			type = CT_STAND_P;
			bType = CT_STAND_B_P;
			break;
		case 1:
			card = CardsArraySstand->data->arr;
			type = CT_STAND_S;
			bType = CT_STAND_B_S;
			break;
		case 2:
			card = CardsArrayDstand->data->arr;
			type = CT_STAND_D;
			bType = CT_STAND_B_D;
			break;
		case 3:
			card = CardsArrayXstand->data->arr;
			type = CT_STAND_X;
			bType = CT_STAND_B_X;
			break;

		default:
			break;
		}
		for (int j=0; j<standCard[i].nNum; j++) {

			for (int l=0; l<4; l++) {
				//不是杠牌，显示3张
				if(standCard[i].nType[j] < 2 && l == 3){
					card++;
					break;
				}
				Card *c =(Card*)*card;
				char * fileName = CommonFunction::GetImageByByte(type,standCard[i].nFirstCard[j]);
				if (standCard[i].nType[j] == ANGANG && l<3) {
					fileName = CommonFunction::GetImageByByte(bType,standCard[i].nFirstCard[j]);
				}
				c->setDisplayFrameName(fileName);

				card++;
			}
		}
	}
}
//#pragma mark设置桌面的牌
void DeskCardsBatch::SetCardTable(BYTE chair,BYTE count,BYTE * tableCard)
{
	switch (chair) {
	case 0:
		SetArrayTableByImage_Reverse(CardsArrayPlayertable,count,tableCard,CT_TABLE_P);
		break;
	case 1:
		SetArrayTableByImage_Reverse(CardsArrayStable,count,tableCard,CT_TABLE_S);
		break;
	case 2:
		SetArrayTableByImage(CardsArrayDtable,count,tableCard,CT_TABLE_D);
		break;
	case 3:
		SetArrayTableByImage(CardsArrayXtable,count,tableCard,CT_TABLE_X);
		break;

	default:
		break;
	}

}
//#pragma mark显示出牌
void DeskCardsBatch::ShowOutCard(OUTED_CARD outCard)
{
	SetAllOutCardHide();

	OutCard * o = (OutCard*)CardsArrayOut->objectAtIndex(CommonFunction::GetChair(m_Chair,outCard.nChair));
	o->cardContent = outCard.nCard;

	char * fileName = CommonFunction::GetImageByByte(CT_OUT,outCard.nCard);
	o->setDisplayFrameName(fileName);
	o->setVisible(true);
}
//#pragma mark出牌
void DeskCardsBatch::OutCardAction(PLAYER_DATA * playerData,OUTED_CARD outCard)
{
	BYTE chair = outCard.nChair;
	if (chair != 0) {
		SetCardHand(playerData);
		//设置起到的牌不可见
		((Card *)CardsArrayMo->objectAtIndex(chair-1))->setVisible(false);
	}
	ShowOutCard(outCard);    
}
//#pragma mark摸牌
void DeskCardsBatch::MoCardActive(BYTE activityPlayer,BYTE cardTakenNow)
{
	BYTE chair = activityPlayer;
	Card * c = (Card*)CardsArrayMo->objectAtIndex(chair -1);
	c->setVisible(true);
	c->cardContent= cardTakenNow;

	char * fileName;
	switch (chair) {
	case 1:
		fileName = CommonFunction::GetImageByByte(CT_MO_S,cardTakenNow);
		break;
	case 2:
		fileName = CommonFunction::GetImageByByte(CT_MO_D,cardTakenNow);
		break;
	case 3:
		fileName = CommonFunction::GetImageByByte(CT_MO_X,cardTakenNow);
		break;

	default:
		break;
	}
	c->setDisplayFrameName(fileName);
}

//#pragma mark隐藏所有出牌
void DeskCardsBatch::SetAllOutCardHide()
{
//	CCMutableArray<OutCard*>::CCMutableArrayIterator eachCard;
	CCObject* item;
	CCARRAY_FOREACH(CardsArrayOut, item)
	{
		OutCard* c = dynamic_cast<OutCard *>(item);
		c->setVisible(false);
	}
}

//#pragma mark把牌放到桌面上
void DeskCardsBatch::SetArrayTableByImage(CCArray *tableArray,BYTE count,BYTE * tableCard,CARDTYPE type)
{
	for (int i=0; i<count; i++) {
		Card* c = (Card*)tableArray->objectAtIndex(i);
		if(!c->isVisible())
		{
			c->setDisplayFrameName(CommonFunction::GetImageByByte(type,tableCard[i]));
			c->setVisible(true);
			return;
		}
	}
}
//#pragma mark把牌放到桌面上 倒排
void DeskCardsBatch::SetArrayTableByImage_Reverse(CCArray *tableArray,BYTE count,BYTE * tableCard,CARDTYPE type)
{
	for (int i = MAX_Card_Table -1; i>=MAX_Card_Table-count; i--) {
		Card* c = (Card*)tableArray->objectAtIndex(i);
		if(!c->isVisible())
		{
			c->setDisplayFrameName(CommonFunction::GetImageByByte(type,tableCard[MAX_Card_Table-1-i]));
			c->setVisible(true);
			return;
		}
	}
}

//#pragma mark通过逻辑对象，设置牌墙
void DeskCardsBatch::SetCardWall(BYTE countAllot)
{
	CCLOG("发第 %d 张牌", countAllot);
	Card* myCard;
	BYTE cardIndex = GetIndexInWallByCard(countAllot);
	switch (CommonFunction::GetChair(m_Chair, GetWallByCard(countAllot)) ) {
	case 0:
		myCard = (Card*)CardsArrayPWall->objectAtIndex(cardIndex);
		break;
	case 1:
		myCard = (Card*)CardsArraySWall->objectAtIndex(cardIndex);
		break;
	case 2:
		myCard = (Card*)CardsArrayDWall->objectAtIndex(cardIndex);
		break;
	case 3:
		//下家的牌墙，拿牌顺序相反
		cardIndex = 25 - cardIndex;
		if(cardIndex%2 == 0)
		{
			cardIndex++;
		}
		else{
			cardIndex--;
		}
		myCard = (Card*)CardsArrayXWall->objectAtIndex(cardIndex);
		break;
	default:
		break;
	}
	myCard->setVisible(false);
}

//#pragma mark发牌后初始化牌墙
void DeskCardsBatch::InitWall(BYTE banker)
{
	m_nChairBanker = banker;
	for (BYTE i =1; i<53; i++) {
		SetCardWall(i);
	}
}

//#pragma mark -----------------私有辅助方法------------------
//#pragma mark根据牌的位置，判断牌所在的牌堆
BYTE DeskCardsBatch::GetWallByCard(BYTE card)
{
	card--;
	if (card<30) {//前0~29张在庄家
		return m_nChairBanker;
	}
	else if(card<56){//30~55张在庄家的上家
		return (m_nChairBanker + 1)%4;
	}
	else if(card<82){//56~81张在庄家的对家
		return (m_nChairBanker + 2)%4;
	}
	else {//82~108张在庄家的下家
		return (m_nChairBanker + 3)%4;
	}
}
//#pragma mark获取牌在牌堆中的位置
BYTE DeskCardsBatch::GetIndexInWallByCard(BYTE card)
{
	card--;
	if (card < 4) {
		return 25;
	}
	else
	{
		return 25 - (card-4)%26;
	}
}











