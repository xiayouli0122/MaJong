//
//  Robot.cpp
//  xzdd
//
//  Created by  on 12-3-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#define COCOS_DEBUG 0
#include "Robot.h"
#include "cocos2d.h"
#include "../../Common/CommonFunction.h"

#define AI_LEVEL_THREE 3
#define AI_LEVEL_FOUR  4
#define AI_LEVEL_FIVE  5
#define AI_LEVEL_SIX  6

//初始化--------------------------------
Robot::Robot()
{
}
void Robot::Init(CGameLogical * g, BYTE c)
{
    CCLOG("Robot init");
    selectedCard = 255;
    selectedCardIndex = 255;
    game = g;
    chair = c;
    AILevel = 4;
	memset(isLocked, 0, sizeof(isLocked));
	memset(outLevel, 0, sizeof(outLevel));
}


//对竞争选择的命令进行选择
BYTE Robot::ChoosingCommon(bool p,bool g,bool h) 
{
	OUTED_CARD m_sOutedCard = game->m_sOutedCard;
	BOOL m_bDingQue = game->m_bDingQue;
	DING_QUE	*dingQue = game->GetDingQue();
	BYTE * huList = game->GetHuList(chair);
    
    if (h) {
        return CLIENT_HU;
    }
    if (g) {		
		if(m_bDingQue){
			PAI_TYPE cardType = game->GetCardType(m_sOutedCard.nCard);
			if(dingQue[chair].nCardType == cardType){//定缺牌，不能杠
				//CCLOG("----------------------fangqi gang");
				return CLIENT_CANCEL;
			}
		}
        return CLIENT_ZHIGANG;
    }
    if (p) {
		if(m_bDingQue){
			PAI_TYPE cardType = game->GetCardType(m_sOutedCard.nCard);
			if(dingQue[chair].nCardType == cardType){
				//CCLOG("----------------------fangqi peng");
				return CLIENT_CANCEL;
			}
		}
		
		if(huList[0] > 0){//如果已经听胡，先简单处理为不碰
			//CCLOG("peng isTingHu----------------------yijing tinghu");
			return CLIENT_CANCEL;
		}
		
        return CLIENT_PENG;
    }
    
    return CLIENT_CANCEL;
}

//AI摸牌后的命令选择
//ag---- 是否能暗杠
//wg---- 是否能弯杠
//h---- 是否能胡
//返回需要执行的命令
BYTE Robot::ChoosingCommonAfterMo(bool ag, bool wg, bool h) 
{
    CCLOG("Rotot ChoosingCommonAfterMo %d,%d,%d",ag?1:0,wg?1:0,h?1:0);
	PLAYER_DATA * playerData = game->GetPlayerData();
    STAND_CARD 	*standCard = game->GetStandCard();   //获取玩家倒牌
	BOOL m_bDingQue = game->m_bDingQue;
	DING_QUE	*dingQue = game->GetDingQue();
    
    if (ag || wg) {        
        BYTE * cards = CommonFunction::GetAGEnableCards(playerData[chair],standCard[chair],wg);
        
        selectedCard = cards[0];
        
        delete [] cards;
        //selectedCardIndex = 1;
		
        if(wg && CommonFunction::IsWangGangCard(selectedCard, standCard[chair]))
        {
            selectedCardIndex = 13;
            return CLIENT_WANGANG;
        }
        
		else if(m_bDingQue){
			PAI_TYPE cardType = game->GetCardType(selectedCard);
			if(dingQue[chair].nCardType == cardType){//定缺牌，不能暗杠，把刚摸到的暗杠牌打掉
				//CCLOG("----------------------fangqi angang");
				selectedCardIndex = 13;
				return CLIENT_OUTCARD;
			}
		}
        return CLIENT_ANGANG;
    }
    if (h) {
        return CLIENT_HU;
    }
    
    return CLIENT_OUTCARD;
}


//AI出牌
void Robot::ChoosingOutCard()
{
    CCLOG("Rotot ChoosingOutCard");
	//CCLOG("------------------Robot::ChoosingOutCard begin--------------------------");
    
	selectedCardIndex = 255;
    
	PLAYER_DATA * playerData = game->GetPlayerData();//获取玩家数据
	STAND_CARD 	*standCard = game->GetStandCard();   //获取玩家倒牌	
	DING_QUE	*dingQue = game->GetDingQue();       //玩家定缺信息	    
	BOOL m_bDingQue = game->m_bDingQue;			     //定缺
    
	//CCLOG("---------player %d --------", chair);
	//CCLOG("---------nCardTakenNow --------%d", playerData[chair].nCardTakenNow);
	//LogCard(playerData[chair].nCardTakenNow);
    
	PAI_TYPE cardType = game->GetCardType(playerData[chair].nCardTakenNow);
	if(PAI_TYPE_INVALID == cardType)
	{
		CCLOG("错误牌类型，发生在robot ChoosingOutCard");
	}
    
	for(int i=WAN; i<=TONG; i++){
		//CCLOG("shou pai lei xing: %d, num: %d", i, playerData[chair].nCard[i][0]);
		for(int j=1; j<=playerData[chair].nCard[i][0];j++){
		    LogCard(playerData[chair].nCard[i][j]);
		}
	}
    
	//for(int i=0; i<standCard[chair].nNum; i++){
	//	CCLOG("########stand type: %d", standCard[chair].nType[i]);
	//	LogCard(standCard[chair].nFirstCard[i]);
        
	//}
    
	game->ListInsert(playerData[chair].nCard[cardType], playerData[chair].nCardTakenNow);
	playerData[chair].nLen++;    
    
	DingQueAI(m_bDingQue, dingQue, chair, playerData, standCard);
    
	if(selectedCardIndex != 255){
		return;
	}
    
	if(AILevel >= AI_LEVEL_THREE){
		TingHuAI(chair, playerData, standCard);
        
		if(selectedCardIndex != 255){
			return;
		}
	}
    
    
	BasicAI(chair, playerData, standCard);
    
	CCLOG("     BasicAI end    selectedCard:%d", selectedCard);
	CCLOG("     BasicAI end    selectedCardIndex:%d", selectedCardIndex);
    
	if(selectedCardIndex != 255){
		return;
	}	
    
	selectedCardIndex = 13;
	
}

void Robot::LogCard(BYTE nCard){
//	PAI_TYPE paiType = game->GetCardType(nCard);
//	if(paiType == WAN){
//		CCLOG("             %d wan", nCard+1);
//	}
//    
//	if(paiType == TIAO){
//		CCLOG("             %d tiao", nCard%9+1);
//	}
//    
//	if(paiType == TONG){
//		CCLOG("             %d tong", nCard%9+1);
//	}	
}

//根据定缺逻辑来出牌	
void Robot::DingQueAI(bool isDingQue, DING_QUE	* dingQue, BYTE nChair, PLAYER_DATA * playerData, STAND_CARD *standCard){
	PAI_TYPE cardType = game->GetCardType(playerData[nChair].nCardTakenNow);
	if(isDingQue){//定缺模式
		if(dingQue[nChair].nCardType == cardType){//判断刚拿到的牌是否是定缺的牌，如果是则直接打掉
			selectedCard = playerData[nChair].nCardTakenNow;
			selectedCardIndex = 13;
            
			game->ListDelete(playerData[nChair].nCard[cardType], playerData[nChair].nCardTakenNow);
	        playerData[nChair].nLen--;
            
			return;
		}else{//从手中牌找定缺牌
			BYTE wantedCard = FindDingQueCard(nChair, playerData, (PAI_TYPE)dingQue[nChair].nCardType);
			if(wantedCard != 255){
				selectedCard = wantedCard;
				BYTE wantedCardIndex = GetOutCardSelectedIndex(wantedCard, nChair, playerData);
				if(wantedCardIndex != 255){
					selectedCardIndex = wantedCardIndex;
					return;
				}
			}else{
				//没找到不用处理
			}
		}
	}else{//非定缺模式
		BYTE cntStandCardType = CountStandCardType(nChair, standCard + nChair);
		BYTE cntShouCardType = CountShouCardType(nChair, playerData);
		if(cntStandCardType == 0){
			if(cntShouCardType == 1 || cntShouCardType == 2){
				//这里不用处理
			}else if(cntShouCardType == 3){
				//找出手牌中数量最少那门，第一张
                BYTE wantedCard = FindLeastShouCard(nChair, playerData);
                selectedCard = wantedCard;
                selectedCardIndex = GetOutCardSelectedIndex(wantedCard, nChair, playerData);
                return;
			}			
		}else if(cntStandCardType == 1){
			if(cntShouCardType == 1){
				//这里不用处理
			}else if(cntShouCardType == 2){
				//如果包含定缺牌，不用处理，不然找出这两种牌中数量最少那门，第一张
				PAI_TYPE standCardType = FindOnlyCardTypeInStand(nChair, standCard + nChair);
				if(playerData[nChair].nCard[standCardType][0] == 0){//不包含
					BYTE wantedCard = FindLessShouCardExcludeStand(nChair, playerData, standCardType);
                    selectedCard = wantedCard;
					selectedCardIndex = GetOutCardSelectedIndex(wantedCard, nChair, playerData);
					return;
				}
			}else if(cntShouCardType == 3){
				//找出另外两种牌中数量最少那门，第一张
				PAI_TYPE excludedCardType = FindOnlyCardTypeInStand(nChair, standCard + nChair);
				BYTE wantedCard = FindLessShouCardExcludeStand(nChair, playerData, excludedCardType);
                selectedCard = wantedCard;
                selectedCardIndex = GetOutCardSelectedIndex(wantedCard, nChair, playerData);
				return;
			}	
            
		}else if(cntStandCardType == 2){
		    //从手牌中找出定缺那门，找到就打掉
			cardType = FindDingQueCardType(nChair, standCard + chair);
			BYTE wantedCard = FindDingQueCard(nChair, playerData, cardType);	
            
			if(255 != wantedCard){//找到
                selectedCard = wantedCard;
				selectedCardIndex = GetOutCardSelectedIndex(wantedCard, nChair, playerData);
				return;
			}
		}
        
	}
}

//从table中找出该牌已出的数量
BYTE Robot::FindCountOfOutCardFromTable(BYTE nCard){
	int count = 0;
	for(int i=0; i<4; i++){
		BYTE * tableCard = game->GetTableCards(i);//第i个玩家的tableCard
		BYTE tableCardNum = game->GetNumTableCards(i);//第i个玩家的tableCard

		for(int j=0;j<tableCardNum;j++){
			if(tableCard[j] == nCard){
				count++;
			}
		}
	}

	return count;
}

//从倒牌中找出该牌已出的数量
BYTE Robot::FindCountOfOutCardFromStand(BYTE nCard, STAND_CARD * standCard){
	int count = 0;
	for(int i=0; i<standCard[chair].nNum; i++){
		if(standCard[chair].nType[i] == SHUN){//SHUN
			PAI_TYPE cardType1 = game->GetCardType(nCard);
			PAI_TYPE cardType2 = game->GetCardType(standCard[chair].nFirstCard[i]);
			if(cardType1 == cardType2 && (nCard == standCard[chair].nFirstCard[i] || nCard == (standCard[chair].nFirstCard[i] + 1)
                                          || (nCard == standCard[chair].nFirstCard[i] + 2))){
				count++;
			}
		}else if(standCard[chair].nType[i] == KE){//KE
			if(nCard == standCard[chair].nFirstCard[i]){
				count += 3;
			}
		}else if(standCard[chair].nType[i] == MGANG_COME || standCard[chair].nType[i] == ANGANG 
                 || standCard[chair].nType[i] == MGANG_MYSELF){//MGANG_COME or ANGANG or MGANG_MYSELF
			if(nCard == standCard[chair].nFirstCard[i]){
				count += 4;
			}
		}
        
	}

	return count;
}

//从牌堆中找出该牌已出的数量
BYTE Robot::FindCountOfOutCardFromLeft(BYTE nCard){
	BYTE *cardBuf = game->GetCardBuf();               //获取牌的缓存区
	BYTE m_nCountAllot  = game->m_nCountAllot;		  // 发到第几张牌
    
	int count=0;
	for(int i=m_nCountAllot+1; i<108; i++){
		if(cardBuf[i] == nCard){
			count++;
		}
	}
    
	return count;
    
}

void Robot::TingHuAI(BYTE nChair, PLAYER_DATA * playerData, STAND_CARD *standCard){
    
	BYTE outCardHuList[14][30];
	BYTE countLeftHuCard[14];//听的牌剩下的数量
	BYTE countLeftHuCardCopy[14];//听的牌剩下的数量
	BYTE wantedCard = 255;
	memset(outCardHuList, 0 ,sizeof(outCardHuList));
	memset(countLeftHuCard, 0 ,sizeof(countLeftHuCard));
	memset(countLeftHuCardCopy, 0 ,sizeof(countLeftHuCardCopy));
    
	int m=0;
	for(int i=WAN; i<=TONG; i++){
		for(int j=1; j<=playerData[nChair].nCard[i][0];j++){
			BYTE card = playerData[nChair].nCard[i][j];
			game->ListDelete(playerData[nChair].nCard[i], card);//假如出了这张牌
			game->InitHuList(chair);
			BYTE * huList = game->GetHuList(nChair);
            
			outCardHuList[m][0] = huList[0];
			if(huList[0]>0){				
				for(int k=1; k<=huList[0]; k++){
					outCardHuList[m][k] = huList[k];
				}				
			}
			m++;
			game->ListInsert(playerData[nChair].nCard[i], card);
		}
	}
    
	//判断打牌后是否听胡
	int outCardTingHuCount = 0;
	for(int i=0;i<m;i++){
		if(outCardHuList[i][0] > 0){
			outCardTingHuCount++;
		}
	}
    
	if(outCardTingHuCount == 0){//还未听胡
		return;
	}
    
	if(AILevel < AI_LEVEL_FOUR){//从桌面看听的牌还剩下多少个
		for(int i=0;i<m;i++){
			for(int j=1; j<=outCardHuList[i][0]; j++){
				countLeftHuCard[i] += (4 - FindCountOfOutCardFromTable(outCardHuList[i][j]) - FindCountOfOutCardFromStand(outCardHuList[i][j], standCard));
			}
		}
	}else{//从牌堆看听的牌还剩下多少个
		for(int i=0;i<m;i++){
			for(int j=1; j<=outCardHuList[i][0]; j++){
				countLeftHuCard[i] += FindCountOfOutCardFromLeft(outCardHuList[i][j]);
			}
		}
	}
    
	for(int i=0;i<m;i++){
		countLeftHuCardCopy[i] = countLeftHuCard[i];
	}
	
	game->ListSort(countLeftHuCardCopy, m);//大的在后面
    
	BYTE maxCountLeftHuCard = countLeftHuCardCopy[m-1];
    
	int cardIndex = 0;
	for(int i=0;i<m;i++){//找出第几张牌
		cardIndex++;
		if(countLeftHuCard[i] == maxCountLeftHuCard){
			break;
		}
	}
    
	int index = 0;
	for(int i=WAN; i<=TONG; i++){
		for(int j=1; j<=playerData[nChair].nCard[i][0];j++){
			index++;
			if(index == cardIndex){
				wantedCard = playerData[nChair].nCard[i][j];
			}
		}
	}
    
    CCLOG("TingHuAI  wantedCard:%d", wantedCard);
	if(wantedCard != 255){
		selectedCard = wantedCard;
	}else{
		return;
	}
    
	BYTE wantedCardIndex = GetOutCardSelectedIndex(wantedCard, nChair, playerData);
	CCLOG("TingHuAI  wantedCardIndex:%d", wantedCardIndex);
	if(wantedCardIndex != 255){
		selectedCardIndex = wantedCardIndex;
	}
    
	return;
    
}

//基本的出牌AI, 比如有三张的保留，成顺子的保留，对子看等级，单独的或者边张的先出
void Robot::BasicAI(BYTE nChair, PLAYER_DATA * playerData, STAND_CARD *standCard){
    
	for(int i=WAN; i<=TONG; i++){//初始化
		isLocked[i][0] = playerData[nChair].nCard[i][0];
		outLevel[i][0] = playerData[nChair].nCard[i][0];
		for(int j=1; j<=playerData[nChair].nCard[i][0];j++){
			isLocked[i][j] = false;//默认的是true,不同平台相应要修改
			outLevel[i][j]= 0;
		}
	}
    
	//第一步：判断是否成顺子，成则锁定
	for(int i=WAN; i<=TONG; i++){
        FindShun(playerData[nChair].nCard[i], isLocked[i]);
	}
    
	//第二步：判断有没有相同的三张
	for(int i=WAN; i<=TONG; i++){
        FindSanZhang(playerData[nChair].nCard[i], isLocked[i]);
	}
    
	//第三步：找对子，有对level=1，不成对level=2
	for(int i=WAN; i<=TONG; i++){
        FindDui(playerData[nChair].nCard[i], isLocked[i], outLevel[i]);
	}
    
	//第四步：找相邻牌和相隔牌
	for(int i=WAN; i<=TONG; i++){
		FindXiangJin(playerData[nChair].nCard[i], isLocked[i], outLevel[i], standCard);
	}
	
	BYTE wantedCardContent = GetOutCardSelectedContent(nChair, playerData);
	if(wantedCardContent != 255){
		selectedCard = wantedCardContent;
	}
    
	BYTE wantedCardIndex = GetOutCardSelectedIndex(wantedCardContent, nChair, playerData);
	if(wantedCardIndex != 255){
		selectedCardIndex = wantedCardIndex;
	}
    
	return;
    
}


//根据相近牌已出多少个来设定level
void Robot::DealWithOutXiangJinLevel(BYTE * outCardLevel, BYTE cardIndex, BYTE outCardCount, bool chengdui){
	
    switch(outCardCount){
        case 0 :
            outCardLevel[cardIndex] = chengdui ? 3 : ((outCardLevel[cardIndex] > 4 || outCardLevel[cardIndex] == 2) ?  4 : outCardLevel[cardIndex]);
            break; 
        case 1 :
            outCardLevel[cardIndex] = chengdui ? 3 : ((outCardLevel[cardIndex] > 5 || outCardLevel[cardIndex] == 2) ?  5 : outCardLevel[cardIndex]);
            break; 
        case 2 :
            outCardLevel[cardIndex] = chengdui? 3 : ((outCardLevel[cardIndex] > 6 || outCardLevel[cardIndex] == 2) ?  6 : outCardLevel[cardIndex]);
            break;
        case 3 :
            outCardLevel[cardIndex] = chengdui? 3 : ((outCardLevel[cardIndex] > 7 || outCardLevel[cardIndex] == 2) ?  7 : outCardLevel[cardIndex]);
            break;
        case 4 :
            outCardLevel[cardIndex] = chengdui? 3 : ((outCardLevel[cardIndex] > 8 || outCardLevel[cardIndex] == 2) ?  8 : outCardLevel[cardIndex]);
            break;
        case 5 :
            outCardLevel[cardIndex] = chengdui? 3 : ((outCardLevel[cardIndex] > 9 || outCardLevel[cardIndex] == 2) ?  9 : outCardLevel[cardIndex]);
            break;
        case 6 :
            outCardLevel[cardIndex] = chengdui? 3 : ((outCardLevel[cardIndex] > 10 || outCardLevel[cardIndex] == 2) ?  10 : outCardLevel[cardIndex]);
            break;
        case 7 :
            outCardLevel[cardIndex] = chengdui? 3 : ((outCardLevel[cardIndex] > 11 || outCardLevel[cardIndex] == 2) ?  11 : outCardLevel[cardIndex]);
            break;
        case 8 :
            outCardLevel[cardIndex] = chengdui? 3 : ((outCardLevel[cardIndex] > 12 || outCardLevel[cardIndex] == 2) ?  12 : outCardLevel[cardIndex]);
            break;
        default:
            return;			
    }
}

//找出要出的牌的content
BYTE Robot::GetOutCardSelectedContent(BYTE nChair, PLAYER_DATA * playerData)
{
	BYTE tempArr[3][15];
	BYTE outCard[14];//最大优先级出的牌
    
	for(int i=WAN; i<=TONG; i++){//复制，因为排序会改变原数组
		tempArr[i][0] = playerData[nChair].nCard[i][0];
		for(int j=1; j<=playerData[nChair].nCard[i][0];j++){
			tempArr[i][j] = outLevel[i][j];
		}
	}
	
	for(int i=WAN; i<=TONG; i++){//对三种类型的牌的outLevel进行排序
		game->ListSort(&tempArr[i][1], playerData[nChair].nCard[i][0]);//最大的排到后面
	}
	
	BYTE maxOutCardLevel = FindMax(tempArr[WAN][playerData[nChair].nCard[WAN][0]],
		                           tempArr[TIAO][playerData[nChair].nCard[TIAO][0]]);
    
	maxOutCardLevel = FindMax(maxOutCardLevel,
                              tempArr[TONG][playerData[nChair].nCard[TONG][0]]);
    
	int index=0;
	for(int i=WAN; i<=TONG; i++){//找出原来outLevel数组中所有最高优先级要出的牌
		for(int j=1; j<=playerData[nChair].nCard[i][0];j++){
			if(maxOutCardLevel == outLevel[i][j]){
				outCard[index++] = playerData[nChair].nCard[i][j];
			}
		}
	}
    
	//如果有多张最高优先级一样，则选择边张先出，如无边张或者多个边张，都选第一张
	BYTE wantedCard = 255;
	for(int i=0; i<index;i++){
		if(outCard[i]%9 == 0 || outCard[i]%9 == 8){
			wantedCard = outCard[i];
			break;
		}
	}
	if(wantedCard != 255){//有边张
		return wantedCard;
	}else{
		return outCard[0];
	}
	
}

//找出要出的牌的index,在原来的手牌中找
BYTE Robot::GetOutCardSelectedIndex(BYTE wantedCard, BYTE nChair, PLAYER_DATA * playerData)
{
	PAI_TYPE cardType = game->GetCardType(playerData[nChair].nCardTakenNow);
	game->ListDelete(playerData[nChair].nCard[cardType], playerData[nChair].nCardTakenNow);
	playerData[nChair].nLen--;
    
	
	if(playerData[nChair].nCardTakenNow == wantedCard){
	    return 13;
	}
    
	PAI_TYPE wantedCardType = game->GetCardType(wantedCard);
    
	int index = 0;
	//根据要出的牌找出它的index
	for(int j=1; j<=playerData[nChair].nCard[wantedCardType][0];j++){	
		if(wantedCard == playerData[nChair].nCard[wantedCardType][j]){
			break;
		}
		index++;
	}
    
	BYTE selectedCardIndex = 13;
	for(int i = TONG; i >= wantedCardType; i--){		
		selectedCardIndex = selectedCardIndex - playerData[nChair].nCard[i][0];
	}
    
	return selectedCardIndex + index;
    
}

//找顺子,找到则锁定
void Robot::FindShun(BYTE *buf, bool * isLocked){
	bool isHaveSecond = false;//顺子的第二张
	bool isHaveThree = false;//顺子的第三张
	int secondIndex = 0;//顺子的第二张的数组下标
	int threeIndex = 0;//顺子的第三张的数组下标
    
	if(buf[0] < 3){
		return;
	}
    
	for(int i=1; i<=buf[0];i++){//该张牌作为顺子的第一张,如123的1
		isHaveSecond = false;
		isHaveThree = false;
		if(!isLocked[i]){//已经被锁，不找
			for(int j=i+1; j<=buf[0];j++){
                
				if(!isLocked[j]){//从余下没被锁的牌中找
					if(buf[j] == buf[i]+1){//找到第二张
						isHaveSecond = true;
						secondIndex = j;
						break;
					}
				}	
                
			}	
            
			for(int j=i+1; j<=buf[0];j++){
                
				if(!isLocked[j]){//从余下没被锁的牌中找
					if(buf[j] == buf[i]+2 && isHaveSecond && j > secondIndex){//找到第三张
						isHaveThree = true;
						threeIndex = j;
						break;
					}
				}	
                
			}	
		}
        
		if(isHaveSecond && isHaveThree){//找到顺子
			isLocked[i] = true;
			isLocked[secondIndex] = true;
			isLocked[threeIndex] = true;
		}
		
	}
	
}

//找相同三张,找到则锁定
void Robot::FindSanZhang(BYTE *buf, bool * isLocked){
	bool isHaveSecond = false;//相同三张的第二张
	bool isHaveThree = false;//相同三张的第三张
	int secondIndex = 0;//相同三张的第二张的数组下标
	int threeIndex = 0;//相同三张的第三张的数组下标
    
	if(buf[0] < 3){
		return;
	}
    
	for(int i=1; i<=buf[0];i++){//该张牌作为相同三张的第一张,如111
		isHaveSecond = false;
		isHaveThree = false;
		if(!isLocked[i]){//已经被锁，不找
			for(int j=i+1; j<=buf[0];j++){
                
				if(!isLocked[j]){//从余下没被锁的牌中找
					if(buf[j] == buf[i]){//找到第二张
						isHaveSecond = true;
						secondIndex = j;
						break;
					}
				}	
                
			}	
            
			for(int j=i+1; j<=buf[0];j++){
                
				if(!isLocked[j]){//从余下没被锁的牌中找
					if(buf[j] == buf[i] && isHaveSecond && j > secondIndex){//找到第三张
						isHaveThree = true;
						threeIndex = j;
						break;
					}
				}	
			}	
		}
        
		if(isHaveSecond && isHaveThree){//找到顺子
			isLocked[i] = true;
			isLocked[secondIndex] = true;
			isLocked[threeIndex] = true;
		}
	}
	
}

//找对子,然后设相应等级
void Robot::FindDui(BYTE *buf, bool * isLocked, BYTE * outLevel){
	bool isHaveSecond = false;//对子的第二张
	int secondIndex = 0;//对子的第二张的数组下标
    
	if(buf[0] == 0){
		return;
	}
    
	for(int i=1; i<=buf[0];i++){//该张牌作为对子的第一张,如66
		isHaveSecond = false;
		if(!isLocked[i]){//已经被锁，不找
			for(int j=i+1; j<=buf[0];j++){
                
				if(!isLocked[j]){//从余下没被锁的牌中找
					if(buf[j] == buf[i]){//找到第二张
						isHaveSecond = true;
						secondIndex = j;
					}
				}	
                
			}	
            
			if(isHaveSecond){//找到对子
				outLevel[i] = 1;
				outLevel[secondIndex] = 1;
			}else{
				outLevel[i] = outLevel[i] != 1 ? 2 : outLevel[i];
			}
            
		}
	}
}

//找相近牌,包括相邻和相隔，然后设相应等级
void Robot::FindXiangJin(BYTE *buf, bool * isLocked, BYTE * outLevel, STAND_CARD *standCard){
	bool isHaveLinSecond = false;//相邻牌的第二张
	int secondLinIndex = 0;//相邻牌的第二张的数组下标
    
	bool isHaveGeSecond = false;//相隔牌的第二张
	int secondGeIndex = 0;//相隔牌的第二张的数组下标
    
	if(buf[0] == 0){
		return;
	}
    
	if(buf[0] == 1){
		outLevel[1] = 13;
		return;
	}
    
	for(int i=1; i<=buf[0];i++){//该张牌作为相邻牌的第一张,如67
		isHaveLinSecond = false;//重置 
		if(isLocked[i]){//已经被锁，不找
			continue;
		}
        
		for(int j=i+1; j<=buf[0];j++){
            
			if(!isLocked[j]){//从余下没被锁的牌中找
				if(buf[j] == buf[i]+1){//找到第二张
					isHaveLinSecond = true;
					secondLinIndex = j;
					break;
				}
			}	
            
		}	
		
        
		if(isHaveLinSecond){//找到相邻
			BYTE outCardCount = 0;
            
			if(AILevel < AI_LEVEL_FOUR){//从table和stand中找
				if(buf[i]%9 == 0){//边张1
					outCardCount = 4 + FindCountOfOutCardFromTable(buf[i] + 2) + FindCountOfOutCardFromStand(buf[i] + 2, standCard);
				}
                
				if(buf[i]%9 == 7){//边张8
					outCardCount = 4 + FindCountOfOutCardFromTable(buf[i] - 1) + FindCountOfOutCardFromStand(buf[i] - 1, standCard);
				}
                
				if(buf[i]%9 > 0 && buf[i]%9 < 7){//牌2-7
					outCardCount = FindCountOfOutCardFromTable(buf[i] - 1) + FindCountOfOutCardFromTable(buf[i] + 2)
                    + FindCountOfOutCardFromStand(buf[i] - 1, standCard)
                    + FindCountOfOutCardFromStand(buf[i] + 2, standCard);
				}
			}else{//从牌堆中找
				if(buf[i]%9 == 0){//边张1
					outCardCount = 4 + (4 - FindCountOfOutCardFromLeft(buf[i] + 2));
				}
                
				if(buf[i]%9 == 7){//边张8
					outCardCount = 4 + (4 - FindCountOfOutCardFromLeft(buf[i] - 1));
				}
                
				if(buf[i]%9 > 0 && buf[i]%9 < 7){//牌2-7
					outCardCount = 4 - FindCountOfOutCardFromLeft(buf[i] - 1) + 4 - FindCountOfOutCardFromLeft(buf[i] + 2);
				}
			}
            
            
			if(outLevel[i] == 1 || outLevel[i] == 3){
				DealWithOutXiangJinLevel(outLevel, i, outCardCount, true);
			}else{
				DealWithOutXiangJinLevel(outLevel, i, outCardCount, false);
			}
            
			if(outLevel[secondLinIndex] == 1 || outLevel[secondLinIndex] == 3){
				DealWithOutXiangJinLevel(outLevel, secondLinIndex, outCardCount, true);
			}else{
				DealWithOutXiangJinLevel(outLevel, secondLinIndex, outCardCount, false);
			}
            
		}else{//没找到，找相隔的			
			isHaveGeSecond = false;
			if(!isLocked[i]){//已经被锁，不找
				for(int k=i+1; k<=buf[0];k++){
                    
					if(!isLocked[k]){//从余下没被锁的牌中找
						if(buf[k] == buf[i]+2){//找到第二张
							isHaveGeSecond = true;
							secondGeIndex = k;
							break;
						}
					}	
				}	
			}
            
            if(isHaveGeSecond){//找到
				BYTE outCardZhongCount = 0;
                
				outCardZhongCount = 4 + FindCountOfOutCardFromTable(buf[i]+1);
                
				if(outLevel[i] == 1 || outLevel[i] == 3){
					DealWithOutXiangJinLevel(outLevel, i, outCardZhongCount, true);
				}else{
					DealWithOutXiangJinLevel(outLevel, i, outCardZhongCount, false);
				}
                
				if(outLevel[secondGeIndex] == 1 || outLevel[secondGeIndex] == 3){
					DealWithOutXiangJinLevel(outLevel, secondGeIndex, outCardZhongCount, true);
				}else{
					DealWithOutXiangJinLevel(outLevel, secondGeIndex, outCardZhongCount, false);
				}				
                
			}else{
                
				if(outLevel[i] == 1){//对子中的一个
					outLevel[i] = 3;
				}else if(outLevel[i] == 2 ){//该牌是孤零零一张牌
					outLevel[i] = 13;
				}else{//和左边的牌成相邻或者相隔, 看左边的牌设了什么值
					//保持原值
				}
                
			}
            
		}
        
    }
}

//从手牌中找出已经定缺的那种牌，返回找到的第一个
BYTE Robot::FindDingQueCard(BYTE nChair, PLAYER_DATA * playerData, PAI_TYPE cardType){
    
	if(playerData[nChair].nCard[cardType][0] == 0){//找不到定缺牌
		CCLOG("手牌中找不到定缺牌");
		return 255;
	}else{//找第一个
		return playerData[nChair].nCard[cardType][1];
	}	
}


//找出缺的那门，非定缺模式下使用
PAI_TYPE Robot::FindDingQueCardType(BYTE nChair, STAND_CARD *standCard){
	PAI_TYPE queType;
	if(standCard->nNum < 2){
		CCLOG("倒牌的牌类型不能小于2");
	}
	
	BYTE wanCount = 0;
	BYTE tiaoCount = 0;
	BYTE tongCount = 0;
	for(int i= 0; i< standCard->nNum; i++){
		PAI_TYPE paiType = game->GetCardType(standCard->nFirstCard[i]);
		if(WAN == paiType && wanCount == 0){
			wanCount++;
		}else if(TIAO == paiType && tiaoCount == 0){
			tiaoCount++;
		}else if(TONG == paiType && tongCount == 0){
			tongCount++;
		}
	}
    
	if(wanCount == 0){
		queType = WAN;
	}
    
	if(tiaoCount == 0){
		queType = TIAO;
	}
    
	if(tongCount == 0){
		queType = TONG;
	}
    
	return queType;
}

//找出倒牌中的唯一牌型，前提是只有一种
PAI_TYPE Robot::FindOnlyCardTypeInStand(BYTE nChair, STAND_CARD *standCard){
	PAI_TYPE standType;
	
	BYTE wanCount = 0;
	BYTE tiaoCount = 0;
	BYTE tongCount = 0;
	for(int i= 0; i< standCard->nNum; i++){
		PAI_TYPE paiType = game->GetCardType(standCard->nFirstCard[i]);
		if(WAN == paiType && wanCount == 0){
			wanCount++;
		}else if(TIAO == paiType && tiaoCount == 0){
			tiaoCount++;
		}else if(TONG == paiType && tongCount == 0){
			tongCount++;
		}
	}
    
	if(wanCount != 0){
		standType = WAN;
	}
    
	if(tiaoCount != 0){
		standType = TIAO;
	}
    
	if(tongCount != 0){
		standType = TONG;
	}
    
	return standType;
}

//倒牌数>=2情况下，计算玩家不同的倒牌种类数
BYTE Robot::CountStandCardType(BYTE nChair, STAND_CARD * standCard){
	BYTE wanCount = 0;
	BYTE tiaoCount = 0;
	BYTE tongCount = 0;
	for(int i= 0; i< standCard->nNum; i++){
		PAI_TYPE paiType = game->GetCardType(standCard->nFirstCard[i]);
		if(WAN == paiType && wanCount == 0){
			wanCount++;
		}else if(TIAO == paiType && tiaoCount == 0){
			tiaoCount++;
		}else if(TONG == paiType && tongCount == 0){
			tongCount++;
		}
	}
	return wanCount + tiaoCount + tongCount;
}

//计算玩家手牌种类数
BYTE Robot::CountShouCardType(BYTE nChair, PLAYER_DATA * playerData){
	BYTE count = 0;
	for(int i =WAN; i<=TONG; i++){
		if(playerData[nChair].nCard[i][0] > 0){
			count++;
		}
        
	}
	return count;
}

//找出玩家手牌中数量最少的那门的第一张,前提是三门都有
BYTE Robot::FindLeastShouCard(BYTE nChair, PLAYER_DATA * playerData){
	PAI_TYPE wantedCardType;
	
	for(int i =WAN; i<=TONG; i++){
		if(playerData[nChair].nCard[i][0] == 0){
			CCLOG("错误发生在countLeastShouCard， 必须三门都有");
		}
	}	
    
	wantedCardType = playerData[nChair].nCard[WAN][0] > playerData[nChair].nCard[TIAO][0] ? TIAO : WAN;
	wantedCardType = playerData[nChair].nCard[TONG][0] > playerData[nChair].nCard[wantedCardType][0] ? wantedCardType : TONG;
    
	return playerData[nChair].nCard[wantedCardType][1];
}

//找出玩家手牌中数量较少的那门的第一张,前提是倒牌中有一门，手中有另外两门
BYTE Robot::FindLessShouCardExcludeStand(BYTE nChair, PLAYER_DATA * playerData, PAI_TYPE excludedCardType){
	BYTE wantedCount = 0;
	//BYTE wantedCardIndex = 13;
	int wantedCardType;
	BYTE temp[2];
	memset(temp, 0, sizeof(temp));
    
	int index = 0;
	for(int i =WAN; i<=TONG; i++){//找出另外两门
		if(excludedCardType != i){
			temp[index++] = i;
		}
	}
    
	wantedCount = FindMin(playerData[nChair].nCard[temp[0]][0], playerData[nChair].nCard[temp[1]][0]);//找出较少那门的数量
    
	for(int i =WAN; i<=TONG; i++){//找出较少那门
		if(playerData[nChair].nCard[i][0] == wantedCount){
			wantedCardType = i;
		}
	}
    
	return playerData[nChair].nCard[wantedCardType][1];
}

//找出玩家手牌中数量最少的那门，定缺模式中用
PAI_TYPE Robot::FindLeastShouCardType(BYTE nChair, PLAYER_DATA * playerData){
    
	PAI_TYPE wantedCardType;
    
	wantedCardType = playerData[nChair].nCard[WAN][0] > playerData[nChair].nCard[TIAO][0] ? TIAO : WAN;
	wantedCardType = playerData[nChair].nCard[TONG][0] >= playerData[nChair].nCard[wantedCardType][0] ? wantedCardType : TONG;
    
	return wantedCardType;
}

BYTE Robot::FindMin(BYTE b1, BYTE b2){
	return b1 < b2 ? b1 : b2;
}

BYTE Robot::FindMax(BYTE b1, BYTE b2){
	return b1 > b2 ? b1 : b2;
}

//AI定缺
PAI_TYPE Robot::DingQue()
{
	PLAYER_DATA * playerData = game->GetPlayerData();
    
	PAI_TYPE dingQueType = FindLeastShouCardType(chair, playerData);
    
    return dingQueType;
}

void Robot::SetAILevel(BYTE l){
    this->AILevel = l;
}
