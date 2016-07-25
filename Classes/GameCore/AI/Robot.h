//
//  Robot.h
//  xzdd
//
//  Created by  on 12-3-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_Robot_h
#define xzdd_Robot_h

#include "../TypeDef.h"
#include "../GameLogical.h"

using namespace cocos2d;

//AI 机器人
class Robot
{
    CGameLogical * game;
    BYTE    chair;
    BYTE    AILevel;                //AI级别
public:
    Robot();
    void Init(CGameLogical * g, BYTE c);
    
    //主要公用方法
    
    BYTE    selectedCard;           //选中牌的内容
    BYTE    selectedCardIndex;      //选中牌的序号
    
	
	
	bool isLocked[3][15];//是否锁定，锁定就表示不能出
	BYTE outLevel[3][15]; //出牌等级，等级越高，就越应该出
    
    BYTE ChoosingCommon(bool p, bool g, bool h);   //对竞争选择的命令进行选择
    
    BYTE ChoosingCommonAfterMo(bool ag, bool wg, bool h);    //AI摸牌后的命令选择
    
    void ChoosingOutCard(); //AI出牌
    void SetAILevel(BYTE l);
    
	PAI_TYPE DingQue();
    
	void LogCard(BYTE nCard);
    
private:
	void DingQueAI(bool isDingQue, DING_QUE	* dingQue, BYTE nChair, PLAYER_DATA * playerData, STAND_CARD *standCard);//根据定缺逻辑来出牌	
    BYTE CountStandCardType(BYTE nChair, STAND_CARD * standCard);//计算玩家不同的倒牌种类数
	PAI_TYPE FindDingQueCardType(BYTE nChair, STAND_CARD *standCard); //找出缺的那门	
    BYTE FindDingQueCard(BYTE nChair, PLAYER_DATA * playerData, PAI_TYPE cardType);//从手牌中找出已经定缺的那种牌
    BYTE CountShouCardType(BYTE nChair, PLAYER_DATA * playerData);//计算玩家手牌种类数   	
    BYTE FindLeastShouCard(BYTE nChair, PLAYER_DATA * playerData);//找出玩家手牌中数量最少的那门的第一张，前提时候手中有三门
	PAI_TYPE FindLeastShouCardType(BYTE nChair, PLAYER_DATA * playerData);//找出玩家手牌中数量最少的那门,定缺模式中用
    BYTE FindLessShouCardExcludeStand(BYTE nChair, PLAYER_DATA * playerData, PAI_TYPE excludedCardType);//找出玩家手牌中数量较少的那门的第一张,前提是倒牌中有一门，手中有另外两门	
    PAI_TYPE FindOnlyCardTypeInStand(BYTE nChair, STAND_CARD *standCard);//找出倒牌中的唯一牌型，前提是只有一种
	BYTE FindMin(BYTE b1, BYTE b2);//计算较小值 
	BYTE FindMax(BYTE b1, BYTE b2);//计算较大值 
    
	//基本的出牌AI, 比如有三张的保留，成顺子的保留，对子保留，单独的或者边张的先出
    void BasicAI(BYTE nChair, PLAYER_DATA * playerData, STAND_CARD *standCard);	
	void FindShun(BYTE *buf, bool * isLocked);//找顺子,找到则锁定
	void FindSanZhang(BYTE *buf, bool * isLocked);//找相同三张,找到则锁定
	void FindDui(BYTE *buf, bool * isLocked, BYTE * outLevel);//找对子,然后设相应等级
	void FindXiangJin(BYTE *buf, bool * isLocked, BYTE * outLevel, STAND_CARD *standCard);//找相近牌,包括相邻和相隔，然后设相应出牌等级   
    BYTE GetOutCardSelectedIndex(BYTE wantedCard, BYTE nChair, PLAYER_DATA * playerData);//找出要出的牌的index
	BYTE GetOutCardSelectedContent(BYTE nChair, PLAYER_DATA * playerData);//找出要出的牌的content
	BYTE FindCountOfOutCardFromTable(BYTE nCard);//从table找出该牌已出的数量
	BYTE FindCountOfOutCardFromStand(BYTE nCard, STAND_CARD * standCard);//从倒牌中找出该牌已出的数量
	BYTE FindCountOfOutCardFromLeft(BYTE nCard);//从牌堆中找出该牌已出的数量
    void DealWithOutXiangJinLevel(BYTE * outCardLevel, BYTE cardIndex, BYTE outCardCount, bool chengdui);//根据相近牌已出多少个来设定level	
    
	void TingHuAI(BYTE nChair, PLAYER_DATA * playerData, STAND_CARD *standCard);//根据听牌逻辑来出牌	
    
    
};

#endif
