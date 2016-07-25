//
//  DeskCardsBatch.h
//  xzdd
//
//  Created by  on 12-3-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_DeskCardsBatch_h
#define xzdd_DeskCardsBatch_h

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "ConstantDef.h"
#include "CommonFunction.h"
#include "Card.h"
#include "OutCard.h"
#include "GameLogical.h"

#else 

#include "../../Common/ConstantDef.h"
#include "../../Common/CommonFunction.h"
#include "../Card.h"
#include "../OutCard.h"
#include "../../GameCore/GameLogical.h"

#endif


using namespace cocos2d;

//桌面牌缓存
class DeskCardsBatch : public CCNode
{
    
private:
    //显示出牌
    void ShowOutCard(OUTED_CARD outCard);
    //把牌放到桌面上
//    void SetArrayTableByImage(CCArray *tableArray,char *image);//正排
//    void SetArrayTableByImage_Reverse(CCArray *tableArray,char *image);//倒排
//     void SetArrayTableByImage(CCArray *tableArray,BYTE count,BYTE * tableCard,CARDTYPE type);//正排
//     void SetArrayTableByImage_Reverse(CCArray *tableArray,BYTE count,BYTE * tableCard,CARDTYPE type);//倒排
	void SetArrayTableByImage(CCArray *tableArray,BYTE count,BYTE * tableCard,CARDTYPE type);//正排
	void SetArrayTableByImage_Reverse(CCArray *tableArray,BYTE count,BYTE * tableCard,CARDTYPE type);//倒排
    
    
protected:
    CCSpriteBatchNode * deskCardsBatchNode;
	//Card*
    CCArray *CardsArrayPWall;
    CCArray *CardsArraySWall;
    CCArray *CardsArrayXWall;
    CCArray *CardsArrayDWall;
    
    //AI 手牌 （上，下，对）
    CCArray *CardsArrayShand;
    CCArray *CardsArrayXhand;
    CCArray *CardsArrayDhand;
    
    //倒牌 （上，下，对）
    CCArray *CardsArraySstand;
    CCArray *CardsArrayXstand;
    CCArray *CardsArrayDstand;
    CCArray *CardsArrayPlayerstand;
    
    //桌面牌 （上，下，对）
    CCArray *CardsArrayStable;
    CCArray *CardsArrayXtable;
    CCArray *CardsArrayDtable;
    CCArray *CardsArrayPlayertable;
    
    //打出的牌
	//OutCard*
    CCArray *CardsArrayOut;
    
	//摸到的牌
	//card*
    CCArray *CardsArrayMo;
    
    BYTE m_nChairBanker;				// 庄家的位置，
public:
	//初始化--------------------------------------------------
	virtual bool init();
    virtual void onExit();
	// implement the "static node()" method manually
	CREATE_FUNC(DeskCardsBatch);
    
    BYTE    m_Chair;    //玩家座位
    //公有方法------------------------------------------------
    //设置AI手牌
    void SetCardHand(PLAYER_DATA * playerData);
    //设置倒下的牌
    void SetCardStand(STAND_CARD *standCard);
    //设置桌面的牌
    void SetCardTable(BYTE chair,BYTE count,BYTE * tableCard);
    //设置牌墙
    void SetCardWall(BYTE countAllot);
    
    //出牌
    void OutCardAction(PLAYER_DATA * playerData,OUTED_CARD outCard);
    //摸牌
    void MoCardActive(BYTE activityPlayer,BYTE cardTakenNow);
    
    //隐藏所有出牌
    void SetAllOutCardHide();
    //发牌后初始化牌墙
    void InitWall(BYTE banker);
    
    //设置胡牌
    void SetHU(BYTE playIndex,BYTE huCard);
    //设置亮牌
    void SetLIANG(PLAYER_DATA * playerData);
    
private:
    //私有辅助方法
    //根据牌的位置，判断牌所在的牌堆
    BYTE GetWallByCard(BYTE card);
    //获取牌在牌堆中的位置
    BYTE GetIndexInWallByCard(BYTE card);
    
};

#endif
