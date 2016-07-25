//
//  GameLogical.cpp
//  xzdd
//
//  Created by  on 12-2-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameLogical.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "GameDesk.h"
#else 
#include "../Layer/GameDesk.h"
#endif

//#include "ini.h"

#define ZERO_TAX

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/************/
/* 胡牌列表 */
/************/

// 初始化胡牌列表
void CGameLogical::InitHuList(BYTE chair)
{
	BYTE n = 0;
	PAI_TYPE CardType = PAI_TYPE_INVALID;
	
	for(BYTE card=0; card<NUM_ALL_TYPE; card++)
	{
		CardType = GetCardType(card);
		if(PAI_TYPE_INVALID == CardType)
		{
			CCLOG("牌类型错误，发生在 InitHuList");
			break;
		}
		ListInsert(m_sPlayer[chair].nCard[CardType], card);
        
		if(JudgeHu(chair))	
		{
			BYTE nFanSum = JudgeFan(chair);
			if(nFanSum >= m_nMinFan) 
			{
				n++;
				m_nHuList[chair][n] = card;
			}
		}
		m_HuCurt[chair].clear();
        ListDelete(m_sPlayer[chair].nCard[CardType], card);
        
	}
	m_nHuList[chair][0] = n;
}

bool CGameLogical::IsInHuList(BYTE chair, BYTE card)				// 判断牌card在不在胡牌列表中
{
//    for (int i = 0; i<30; i++) {
//        CCLOG("card %d, hu list %d,%d",card, i,m_nHuList[chair][i]);
//    }
    
	//DWORD dwUserID = //--m_pSite->GetUserID(chair);
//	char szMsg[512];
    
	for (int i=1; i<=m_nHuList[chair][0]; i++)
	{
		if (card == m_nHuList[chair][i])
		{
//			strcpy(szMsg, "\nin Hu List" );
			//--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szMsg);
			return true;
		}
	}
//	strcpy(szMsg, "\nNot in Hu List" );
	//--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szMsg);
	return false;
}

/**************/
/* 牌链表操作 */
/**************/

// 插入牌
void CGameLogical::ListInsert(BYTE *buf, BYTE card)	
{
	if(!buf[0])
	{
		buf[++buf[0]] = card;
		return;
	}
    int i;
	for(i=1; i<=buf[0]; i++)
	{
		if(buf[i] > card)	break;
	}
	if(i == buf[0] + 1)  //没有比它小的, 插到末尾
	{
		buf[i] = card;
	}
	else if(i <= buf[0] ) //移动
	{
		for(int j = buf[0]; j >= i; j--)
		{
			buf[j+1] = buf[j];
		}
		buf[i] = card;
	}
	else
	{
		CCLOG("Error take place at ListInsert!");
		return;
	}
	
	buf[0]++;
}

// 删除牌
void CGameLogical::ListDelete(BYTE *buf, BYTE card)
{
	bool bHaveFind = 0;
	if (buf[0] == 0)
	{
		CCLOG("buffer len cant be 0");
		return;
	}
    int i;
	for(i=1; i<=buf[0]; i++)
	{
		if(card == buf[i])
		{
			bHaveFind = 1;
			break;
		}
	}
	if(!bHaveFind)	
	{
		CCLOG("Cant fine the card when delete card\n");
		return ;
	}
	for( ; i<=buf[0]; i++)
	{
		buf[i] = buf[i+1];
	}
	buf[0]--;
    
}

// 查找牌，返回个数
BYTE CGameLogical::ListFind(BYTE *buf, BYTE card)
{
	int num = 0;
	for(int i=1; i <= buf[0]; i++)
	{
		if(buf[i] == card) num++;
	}
	return num;
}

//对玩家i手中的牌进行冒泡排序
void CGameLogical::ListSort(BYTE *buf, BYTE n)
{
	int j, k, h, t; 
	
	for (h=n-1; h>0; h=k) //循环到没有比较范围 
	{ 
		for (j=0, k=0; j<h; j++ )
		{ 
			if (*(buf+j) > *(buf+j+1)) //大的放在后面，小的放到前面 
			{ 
				t = *(buf+j); 
				*(buf+j) = *(buf+j+1); 
				*(buf+j+1) = t; //完成交换 
				k = j; //保存最后下沉的位置。这样k后面的都是排序排好了的。 
			} 
		} 
	} 
}

/************
 *判断辅助函数
 ************/

//判断牌列表中是不是只有对
bool CGameLogical::ListJudgeDui(BYTE *s)
{
	BYTE i=1, n=0;
	BYTE len = s[0];
	
	//长度为奇数
	if (len%2 != 0)
	{
		return 0;
	}
	
	while (i<=len)
	{
		n = ListFind(s,	s[i]);
		
		if (n == 2 || n == 4)
		{
			i += n;
		}
		else
		{
			return false;
		}
	}
	return true;
}

//把"刻"从牌列表中分离,判断此牌是全3型(return 1), 3+2型(return 2)或其他(return 0)
BYTE CGameLogical::ListJudgePengPeng(BYTE * s, BYTE &nJiang)	
{
	BYTE CList[17];
	bool tipJiang = false;
	int i, j;
	memcpy(CList,s,s[0]+1);
	while(CList[0])
	{
		i = ListFind(CList,CList[1]);
		if(2 == i && !tipJiang)
		{
			tipJiang = true;
			nJiang = CList[1];
			CList[0] -= 2;
			for(j=1; j<=CList[0]; j++)
			{
				CList[j] = CList[j+2];
			}
			continue;
		}
		else if(3 == i)
		{
			CList[0] -= 3;
			for(j=1; j<=CList[0]; j++)
			{
				CList[j] = CList[j+3];
			}
			continue;
		}
		nJiang = 255;
		return 0;
	}
	return (tipJiang) ? 2 : 1;
}

//判断此牌是全3型(return 1), 3+2型(return 2)或其他(return 0)
BYTE CGameLogical::ListJudgeNormal32(BYTE *s, BYTE &nJiang)
{
	BYTE CList[17],BList[17];
	BYTE temp;
	int i;
	memcpy(CList,s,s[0]+1);							
	if(!CList[0])
	{
		nJiang = 255;                   //全三型无将
		return 1;						//全3型
	}
	if(1 == CList[0])	
	{
		nJiang = 255;
		return 0;					//有单张牌,什么也不是
	}
	if(2 == CList[0])								//两张牌
	{
		if(CList[1] == CList[2])	//3+2型
		{
			nJiang = CList[1];
			return 2;
		}
		nJiang = 255;
		return 0;
	}
	//两张以上
	else if(CList[1] == CList[2])					//前两张相等					
	{
		temp = CList[1];
		if(CList[2] == CList[3])					//分离前三张刻
		{
			memcpy(BList,CList,CList[0]+1);
			BList[0] -= 3;
			for(i=1; i<=BList[0];i++)
			{
				BList[i] = BList[i+3];
			}
			int temp;
			temp = ListJudgeNormal32(BList, nJiang);          //递归
			if(temp)	return temp;
		}
		
		memcpy(BList,CList,CList[0]+1);				//分离前两张将
		BList[0] -= 2;
		for(i=1; i<=BList[0]; i++)
		{
			BList[i] = BList[i+2];
		}
		
		if(1 == ListJudgeNormal32(BList, nJiang))	//3+2型
		{
			nJiang = temp;
			return 2;
		}
		if(ListFind(CList, CList[1]+1) && ListFind(CList, CList[1]+2)) //分离顺
		{
			ListDelete(CList, CList[1]+2);
			ListDelete(CList, CList[1]+1);
			ListDelete(CList, CList[1]);
			return ListJudgeNormal32(CList, nJiang); //递归
		}
		else
		{
			return 0;    //单张牌,什么也不是
		}
	}
	else
	{
		BYTE temp = CList[1]+2;
		if((CList[1]+1 == CList[2]) && ListFind(CList,temp)) //分离顺
		{
			CList[0] -= 2;
			for(i=1; i<=CList[0]; i++)
			{
				CList[i] = CList[i+2];
			}
			for(i=1; i<=CList[0]; i++)
			{
				if(CList[i] == temp) 
				{
					break;
				}
			}
			for( ; i<CList[0]; i++)
			{
				CList[i] = CList[i+1];
			}
			CList[0] --;
			return ListJudgeNormal32(CList, nJiang);
		}
        
		return 0;
	}
}

//判断此牌是幺九
bool CGameLogical::ListJudgeYaoJiu(BYTE *s)
{
	BYTE CList[17],BList[17];
    //	BYTE temp, nJiang;
	int i;
	memcpy(CList,s,s[0]+1);							
	if(0 == CList[0])
	{
		return true;						//全3型
	}
	if(1 == CList[0])	
	{
		return false;					//有单张牌,什么也不是
	}
	if(2 == CList[0])								//两张牌
	{
		if(CList[1] == CList[2] && IsYaoJiu(CList[1]))	//3+2型
		{
			return true;
		}
		return false;
	}
    
	if(3 == CList[0])								//3张牌
	{
		if(IsYaoJiu(CList[1]) && CList[1] == CList[2] && CList[1] == CList[3])
		{
			return true;
		}
        
		if (IsYaoQi(CList[1]) && ListFind(CList, CList[1]+1) && ListFind(CList, CList[1]+2))
		{
			return true;
		}
        
		return false;
	}
    
	if (CList[0] %3 == 0)			//全3型
	{
		if(CList[1] == CList[2])					//前两张相等					
		{
			if(CList[2] == CList[3] && IsYaoJiu(CList[1]))					//分离前三张刻
			{
				memcpy(BList,CList,CList[0]+1);
				BList[0] -= 3;
				for(i=1; i<=BList[0];i++)
				{
					BList[i] = BList[i+3];
				}
				int temp;
				temp = ListJudgeYaoJiu(BList);          //递归
				if(temp)
				{
					return true;
				}
			}
            
			if( IsYaoQi(CList[1]) && ListFind(CList, CList[1]+1) && ListFind(CList, CList[1]+2)) //分离顺
			{
				ListDelete(CList, CList[1]+2);
				ListDelete(CList, CList[1]+1);
				ListDelete(CList, CList[1]);
				int temp;
				temp = ListJudgeYaoJiu(CList);          //递归
				if(temp)
				{
					return true;
				}
			}
		}
		else
		{
			BYTE temp = CList[1]+2;
			if(IsYaoQi(CList[1]) && (CList[1]+1 == CList[2]) && ListFind(CList,temp)) //分离顺
			{
				CList[0] -= 2;
				for(i=1; i<=CList[0]; i++)
				{
					CList[i] = CList[i+2];
				}
				for(i=1; i<=CList[0]; i++)
				{
					if(CList[i] == temp) 
					{
						break;
					}
				}
				for( ; i<CList[0]; i++)
				{
					CList[i] = CList[i+1];
				}
				CList[0] --;
				if (ListJudgeYaoJiu(CList))
				{
					return true;
				}
			}
			
			return false;
		}
	}
	else if (CList[0] %3 == 2)			//全3+2型
	{
		if(CList[1] == CList[2])					//前两张相等					
		{
			if(CList[2] == CList[3] && IsYaoJiu(CList[1]))					//分离前三张刻
			{
				memcpy(BList,CList,CList[0]+1);
				BList[0] -= 3;
				for(i=1; i<=BList[0];i++)
				{
					BList[i] = BList[i+3];
				}
				int temp;
				temp = ListJudgeYaoJiu(BList);          //递归
				if(temp)
				{
					return true;
				}
			}
            
			if( IsYaoJiu(CList[1]) )
			{
				memcpy(BList,CList,CList[0]+1);			//分离前2张将
				BList[0] -= 2;						
				for(i=1; i<=BList[0]; i++)
				{
					BList[i] = BList[i+2];
				}
				int temp;
				temp = ListJudgeYaoJiu(BList);          //递归
				if(temp)
				{
					return true;
				}
			}
			
			if(IsYaoQi(CList[1]) && ListFind(CList, CList[1]+1) && ListFind(CList, CList[1]+2)) //分离顺
			{
				ListDelete(CList, CList[1]+2);
				ListDelete(CList, CList[1]+1);
				ListDelete(CList, CList[1]);
				int temp;
				temp = ListJudgeYaoJiu(CList);          //递归
				if(temp)
				{
					return true;
				}
			}
		}
		else
		{
			BYTE temp = CList[1]+2;
			if( IsYaoQi(CList[1]) && (CList[1]+1 == CList[2]) && ListFind(CList,temp)) //分离顺
			{
				CList[0] -= 2;
				for(i=1; i<=CList[0]; i++)
				{
					CList[i] = CList[i+2];
				}
				for(i=1; i<=CList[0]; i++)
				{
					if(CList[i] == temp) 
					{
						break;
					}
				}
				for( ; i<CList[0]; i++)
				{
					CList[i] = CList[i+1];
				}
				CList[0] --;
				if (ListJudgeYaoJiu(CList))
				{
					return true;
				}
			}
			
			return false;
		}
	}
    
	return false;
}

//判断手持牌能不能构成3 + 2
bool CGameLogical::Judge32(BYTE chair)
{
	BYTE nJiang[35] = {255, 255, 255, 255, 255};
	
	m_nJiang[chair] = 255;
    
	BYTE nRet = 0;
	BYTE nSum = 0;
    int i;
	for(i=WAN; i<=DRAGON; i++)
	{
		if(i <= TONG)
		{
			nRet = ListJudgeNormal32(m_sPlayer[chair].nCard[i], nJiang[i]);
		}
		else
		{
			nRet = ListJudgePengPeng(m_sPlayer[chair].nCard[i], nJiang[i]);
		}
		
		if(nRet)
		{
			nSum += nRet;
		}
		else
		{
			return false;
		}
	}
    
    
	if (nSum == 6) 
	{
		for(i=0; i<5; i++)
		{
			if(255 != nJiang[i])
			{
				m_nJiang[chair] = nJiang[i];
				break;
			}
		}
        
		return true;
	}
    
	m_nJiang[chair] = 255;
	return false;
}

//判断倒牌中有没有顺
bool CGameLogical::IsShunInStandCards(BYTE chair)
{
	for( int i=0; i < m_sStandCard[chair].nNum; i++ )
	{
		if ( m_sStandCard[chair].nType[i] == SHUN)	
		{
			return true;
		}
	}
	return false;
}


/************
 *  判断函数
 ************/
/*///cai<
 //判断有没有吃牌
 bool CGameLogical::FindEat(BYTE chair)
 {
 BYTE nCard = 255, nEatCount=0;
 int nCardValue = -1;
 bool mark[4] = {0,0,0,0};
 PAI_TYPE CardType = PAI_TYPE_INVALID;
 
 nCard = m_sOutedCard.nCard;
 nCardValue = GetCardValue(nCard);
 CardType = GetCardType(nCard);
 
 if(CardType >  TONG || nCardValue == -1)
 {
 //		CCLOG("错误的牌类型，发生在FindEat");
 return false;
 }
 
 if ( nCardValue>2 && ListFind(m_sPlayer[chair].nCard[CardType], nCard-2) )
 {
 mark[0] = true;
 }
 if ( nCardValue>1 && ListFind(m_sPlayer[chair].nCard[CardType], nCard-1) )
 {
 mark[1] = true;
 }
 if ( nCardValue<9 && ListFind(m_sPlayer[chair].nCard[CardType], nCard+1) )
 {
 mark[2] = true;
 }
 if ( nCardValue<8 && ListFind(m_sPlayer[chair].nCard[CardType], nCard+2) )
 {
 mark[3] = true;
 }
 
 if( mark[0] && mark[1] )
 {
 m_sEat.nCard[nEatCount][0] = nCard-2;
 m_sEat.nCard[nEatCount][1] = nCard-1;
 m_sEat.nCard[nEatCount][2] = nCard;
 nEatCount ++;	
 }
 if( mark[1] && mark[2] )
 {
 m_sEat.nCard[nEatCount][0] = nCard-1;
 m_sEat.nCard[nEatCount][1] = nCard;
 m_sEat.nCard[nEatCount][2] = nCard+1;
 nEatCount ++;	
 }
 if( mark[2] && mark[3] )
 {
 m_sEat.nCard[nEatCount][0] = nCard;
 m_sEat.nCard[nEatCount][1] = nCard+1;
 m_sEat.nCard[nEatCount][2] = nCard+2;
 nEatCount ++;	
 }
 
 m_sEat.nNum = nEatCount;
 
 if (nEatCount)
 {
 return true;
 }
 return false;
 }
 *////cai>

//判断有没有碰	cai v2.1
bool CGameLogical::FindPeng(BYTE chair)
{
    //	CCLOG("FindPeng");
	PAI_TYPE CardType = GetCardType(m_sOutedCard.nCard);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在FindPeng");
		return false;
	}
    
    if (m_bDingQue && CardType == m_sDingQue[chair].nCardType)
	{
		return false;
	}
    
	BYTE nCardCount = ListFind(m_sPlayer[chair].nCard[CardType], m_sOutedCard.nCard);
    
	if (  nCardCount == 2 || nCardCount == 3 )
	{
		return true;
	}
    
	return false;
}

//判断有没有暗杠	cai v2.1
bool CGameLogical::FindAnGang(BYTE chair)
{
	BYTE nType = 255;
	bool mark = false;
    
	for (nType = WAN; nType <= DRAGON; nType++)
	{
		for (int i = 1; i <= m_sPlayer[chair].nCard[nType][0]; i ++)
		{
			if ( ListFind(m_sPlayer[chair].nCard[nType], m_sPlayer[chair].nCard[nType][i]) == 4 ) 
			{
                if (m_bDingQue && GetCardType(m_sPlayer[chair].nCard[nType][i]) == m_sDingQue[chair].nCardType)
				{
					continue;
				}
				m_sCanGang.type[m_sCanGang.nNum] = CLIENT_ANGANG;
				m_sCanGang.card[m_sCanGang.nNum] = m_sPlayer[chair].nCard[nType][i];
				mark = true;
				i +=3;
				m_sCanGang.nNum++;
			}
		}
	}
	return mark;
}

// 判断有没有自己摸的明杠
bool CGameLogical::FindWanGang(BYTE chair)
{
	bool mark = false;
	BYTE nTempCard = 255;
	PAI_TYPE CardType = PAI_TYPE_INVALID;
    
	if ( m_sStandCard[chair].nNum == 0 )
	{
        //		CCLOG("没有倒牌， 发生在FindMingGangMine");
		return false;
	}
    
	for (int i = 0; i < m_sStandCard[chair].nNum; i ++)
	{
		// 找到类型为刻的倒牌 
		if ( m_sStandCard[chair].nType[i] == KE )
		{
			nTempCard = m_sStandCard[chair].nFirstCard[i];
			CardType = GetCardType(nTempCard);
            
			if(PAI_TYPE_INVALID == CardType)
			{
				CCLOG("错误的牌类型，发生在FindMingGangCome");
				return false;
			}
            
			if ( ListFind(m_sPlayer[chair].nCard[CardType], nTempCard) )
			{
				m_sCanGang.type[m_sCanGang.nNum] = CLIENT_WANGANG;
				m_sCanGang.card[m_sCanGang.nNum] = nTempCard;
				m_sCanGang.nNum++;
				mark = true;
			}
		}
	}
	return mark;
}

// 判断有没有别人打来的明杠	cai v2.1
bool CGameLogical::FindMingGangCome(BYTE chair)
{
    //	CCLOG("FindMingGangCome");
	PAI_TYPE CardType = GetCardType(m_sOutedCard.nCard);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在FindMingGangCome");
		return false;
	}
    
    if (m_bDingQue && CardType == m_sDingQue[chair].nCardType)
	{
		return false;
	}
    
	BYTE nCardCount = ListFind(m_sPlayer[chair].nCard[CardType], m_sOutedCard.nCard);
	if(nCardCount == 3)
	{
		return true;
	}
	return false;
}

//判断碰碰胡
bool CGameLogical::JudgePengPengHu(BYTE chair)
{
	//m_nJiang[chair] = 255;
	BYTE nJiang = 0;
	//倒牌中有顺
	if(IsShunInStandCards(chair))
	{
		return false;
	}
    
	BYTE nRet = 0;
	BYTE nSum = 0;
	for(int i=WAN; i<=DRAGON; i++)
	{
		BYTE nRet = ListJudgePengPeng(m_sPlayer[chair].nCard[i], nJiang);
		if(nRet)
		{
			nSum += nRet;
		}
		else
		{
			return false;
		}
	}
    
	if (nSum == 6)
	{
		return true;
	}
	//m_nJiang[chair] = 255;	
	return false;
}

//判断清一色
bool CGameLogical::JudgeQingYiSe(BYTE chair)
{
	BYTE len = 0;
	BYTE HaveType = 255;
	PAI_TYPE nCardType = PAI_TYPE_INVALID;
    int i;
	// 判倒牌是不是只有一种色
	for(i=0; i<m_sStandCard[chair].nNum; i++)
	{
		PAI_TYPE CardType = GetCardType(m_sStandCard[chair].nFirstCard[i]);
		if(PAI_TYPE_INVALID == CardType)
		{
			CCLOG("牌类型错误，发生在 JudgeQingYiSe");
			return false;
		}
        
		if(255 == HaveType)
		{
			HaveType = CardType;
		}
		else if(HaveType != CardType)
		{
			return false; //不止一种色
		}
	}
    
	// 判断手持牌中是不是只有一种色
	for(i=WAN; i<=DRAGON; i++)
	{
		if(m_sPlayer[chair].nCard[i][0])
		{
			if(255 == HaveType)
			{
				HaveType = i;
			}
			else if(HaveType != i)
			{
				return false; //不止一种色
			}
		}
        
	}
    
	return true;
}

//判断根	cai v1.1
BYTE CGameLogical::JudgeGen(BYTE chair)
{
	BYTE nCard=255;
	BYTE len = 0;
	BYTE count = 0;
    
	// 判断手持牌中有没有根 
	for(int i=WAN; i<=TONG; i++)
	{
		len = m_sPlayer[chair].nCard[i][0];
		for (int j = 1; j<len-2; ++j)
		{
			nCard = m_sPlayer[chair].nCard[i][j];
			if (j+3 <= len && nCard == m_sPlayer[chair].nCard[i][j+3])
			{
				count++;
				j += 3;
			}
		}
		
	}
	
	return count;
}

//判断七巧对
bool CGameLogical::JudgeQiQiaoDui(BYTE chair)
{
	BYTE nStandCount = m_sStandCard[chair].nNum;
	if(nStandCount)
	{
		return false;
	}
    
	for(int i=WAN; i<=TONG; i++)
	{
		if ( !ListJudgeDui(m_sPlayer[chair].nCard[i]))
		{
			return false;
		}
	}
	return true;
}

//判断胡	cai v2.1
bool CGameLogical::JudgeHu(BYTE chair)
{
    /*
	if (!JudgeQueYimen(chair))  //判断缺一门
	{
		return false;
	}
    
	if (m_bDingQue && JudgeHuaZhu(chair))	//定缺场判断花猪
	{
		return false;
	}
    */
    
    if (JudgeHuaZhu(chair))	//判断花猪
	{
		return false;
	}
    
	BYTE nReturnType = JudgeHuType(chair);
    
	switch(nReturnType)
	{
            //	case OK_CHAOHU:
            //		return true;
        case FALSE_ALL:
            return false;
        case OK_PINGHU:					// 1 平胡
		{
			m_HuCurt[chair].nMethod[0] = PINGHU;
			m_HuCurt[chair].nCount = 1;	
			break;
		}
        case OK_PENGPENGHU:	// 2 碰碰胡
		{
            ///			m_HuCurt[chair].nType = FENGDINGHU;			//碰碰胡
			m_HuCurt[chair].nMethod[0] = PENGPENGHU;
			m_HuCurt[chair].nCount = 1;	
			break;
		}
        case OK_QINGYISE:	// 3 清一色
		{
            ///			m_HuCurt[chair].nType = FENGDINGHU;
			m_HuCurt[chair].nMethod[0] = QINGYISE;
			m_HuCurt[chair].nCount = 1;
			break;
		}
        case OK_YAOJIU:		// 4 幺九
		{
			m_HuCurt[chair].nMethod[0] = YAOJIU;
			m_HuCurt[chair].nCount = 1;
			break;
		}
        case OK_QIDUI:		// 5 七对
		{
			m_HuCurt[chair].nMethod[0] = QIDUI;
			m_HuCurt[chair].nCount = 1;
			break;
		}
        case OK_QING_PENG:	// 6 清碰
		{
			m_HuCurt[chair].nMethod[0] = QING_PENG;
			m_HuCurt[chair].nCount = 1;
			break;
		}
        case OK_JIANG_PENG:	// 7 将碰
		{
			m_HuCurt[chair].nMethod[0] = JIANG_PENG;
			m_HuCurt[chair].nCount = 1;
			break;
		}
        case OK_LONG_QIDUI:	// 8 龙七对
		{
			m_HuCurt[chair].nMethod[0] = LONG_QIDUI;
			m_HuCurt[chair].nCount = 1;
			break;
		}
        case OK_QING_QIDUI:	// 9 清七对
		{
			m_HuCurt[chair].nMethod[0] = QING_QIDUI;
			m_HuCurt[chair].nCount = 1;
			break;
		}
        case OK_QING_YAOJIU:	// 10清幺九
		{
			m_HuCurt[chair].nMethod[0] = QING_YAOJIU;
			m_HuCurt[chair].nCount = 1;
			break;
		}
        case OK_QINGLONG_QIDUI:	// 11青龙七对
		{
			m_HuCurt[chair].nMethod[0] = QINGLONG_QIDUI;
			m_HuCurt[chair].nCount = 1;
			break;
		}
        default:
            return false;
	}
    
	if(m_bTianRenHu)							//天胡，人胡
	{
		//		m_HuCurt[chair].nType = CHAOHU;
		if(chair == m_nChairBanker)
		{
			m_HuCurt[chair].AddHU(TIANHU);
		}
		else
		{
			m_HuCurt[chair].AddHU(DIHU);
		}
	}
	else
	{
		if(m_nDiHu[chair] <= 1 && chair == m_chairCurrentPlayer)
		{
			m_HuCurt[chair].AddHU(DIHU);
		}
	}
    
    
    ///	if (m_nGen[chair]!=0 && !JudgeQiQiaoDui(chair))
    ///	{
    ///		m_HuCurt[chair].AddHU(GEN);
    ///	}
    
    int i;
    
	for (i = 0; i<m_nGen[chair];++i)
	{
		m_HuCurt[chair].AddHU(GEN);
	}
    
    // 	if (!JudgeQiQiaoDui(chair))
    // 	{
    // 		for (i = 0; i<m_nGen[chair];++i)
    // 		{
    // 			m_HuCurt[chair].AddHU(GEN);
    // 		}
    // 	}
    
	for (i=0; i<m_sStandCard[chair].nNum; ++i)
	{
		if (m_sStandCard[chair].nType[i] != KE)
		{
			m_HuCurt[chair].AddHU(GANG);
		}
	}
    
	return true;
}


///<cai
bool CGameLogical::JudgeQueYimen(BYTE chair)
{
	bool bHaveWan = false;
	bool bHaveTiao = false;
	bool bHaveTong = false;
	BYTE nStandCount = m_sStandCard[chair].nNum;
    int i;
	for(i=0; i<nStandCount; i++)
	{
		PAI_TYPE CardType = GetCardType(m_sStandCard[chair].nFirstCard[i]);
		if(PAI_TYPE_INVALID == CardType)
		{
			CCLOG("牌类型错误，发生在 JudgeQueYimen");
			return false;
		}
		switch (CardType)
		{
            case WAN:
                bHaveWan = true;
                break;
            case TIAO:
                bHaveTiao = true;
                break;
            case TONG:
                bHaveTong = true;
                break;
            default:
                CCLOG("cardtype return error");
                return false;
		}
		if (bHaveWan && bHaveTiao && bHaveTong)
		{
			return false;
		}
	}
    
	for(i=WAN; i<=TONG; i++)
	{
		if(m_sPlayer[chair].nCard[i][0]!=0)
		{
			switch (i)
			{
                case WAN:
                    bHaveWan = true;
                    break;
                case TIAO:
                    bHaveTiao = true;
                    break;
                case TONG:
                    bHaveTong = true;
                    break;
                default:
                    CCLOG("cardtype return error");
                    return false;
			}
            
			if (bHaveWan && bHaveTiao && bHaveTong)
			{
				return false;
			}
		}
	}
	return true;
}

//查花猪	cai v2.1
bool CGameLogical::JudgeHuaZhu(BYTE chair)
{
	if (!JudgeQueYimen(chair))
	{
		return true;
	}
	else if (!m_bDingQue)
	{
		return false;
	}
    
    ///	if (m_sPlayer[chair].nCardTakenNow == 255)
    ///	{
    ///		return false;
    ///	}
    
    ///	PAI_TYPE CardType = GetCardType(m_sPlayer[chair].nCardTakenNow);
    
	if (m_sPlayer[chair].nCard[m_sDingQue[chair].nCardType][0] != 0)
	{
		return true;
	}
    ///	else if (PAI_TYPE_INVALID != CardType && CardType == m_sDingQue[chair].nCardType)
    ///	{
    ///		return true;
    ///	}
	else
	{
		return false;
	}
}
///cai>

/*////cai<
//判断混一色
bool CGameLogical::JudgeHunYiSe(BYTE chair)
{
	BYTE HaveType = 255;
	BYTE nStandCount = m_sStandCard[chair].nNum;
	bool bHaveZiPai = false;
    int i;
	for(i=0; i<nStandCount; i++)
	{
		PAI_TYPE CardType = GetCardType(m_sStandCard[chair].nFirstCard[i]);
		if(PAI_TYPE_INVALID == CardType)
		{
			CCLOG("牌类型错误，发生在JudgeHunYiSe");
			return false;
		}
        
		if(CardType == FENG || CardType == DRAGON)
		{
			bHaveZiPai = true;
		}
		else if(CardType >= WAN && CardType <= TONG)
		{
			if(255 == HaveType)
			{
				HaveType = CardType;
			}
			else
			{
				if(CardType != HaveType)
				{
					return false;
				}
			}
		}
	}
    
	for(i=WAN; i<=TONG; i++)
	{
		if(m_sPlayer[chair].nCard[i][0])
		{
			if(255 == HaveType)
			{
				HaveType = i;
			}
			else
			{
				if(i != HaveType)
				{
					return false;
				}
			}
		}
	}
    
	if(m_sPlayer[chair].nCard[FENG][0] || m_sPlayer[chair].nCard[DRAGON][0])
	{
		bHaveZiPai = true;
	}
    
	return bHaveZiPai;
}
*////cai>

//判断平胡  （只有顺子）
bool CGameLogical::JudgePingHu(BYTE chair)
{
	BYTE nStandCount = m_sStandCard[chair].nNum;
    int i;
	for(i=0; i<nStandCount; i++)
	{
		if(SHUN != m_sStandCard[chair].nType[i])
		{
			return false;
		}
	}
    
	for(i=WAN; i<=TONG; i++)
	{
		BYTE nCardSum = m_sPlayer[chair].nCard[i][0];
		if(nCardSum < 3)
		{
			break;
		}
		for(int j=1; j<nCardSum; j++)
		{
			BYTE nCard = m_sPlayer[chair].nCard[i][j];
			BYTE nNum = ListFind(m_sPlayer[chair].nCard[i], nCard);
			if(3 == nNum && nCard != m_nJiang[chair])
			{
				if(nCardSum < 9)
				{
					return false;
				}
				BYTE nNumMiddle = ListFind(m_sPlayer[chair].nCard[i], nCard+1);
				BYTE nNumTop = ListFind(m_sPlayer[chair].nCard[i], nCard+2);
				if(nNumMiddle <= 3 || nNumTop <= 3)
				{
					return false;
				}
                
				if(nCardSum == 9)
				{
					break;
				}
                
				nCard = m_sPlayer[chair].nCard[i][j+9];
				nNum = ListFind(m_sPlayer[chair].nCard[i], nCard);
				if(3 == nNum)
				{
					return false;
				}
				break;
                
			}
		}
	}
    
	if(m_sPlayer[chair].nCard[FENG][0] > 2 || m_sPlayer[chair].nCard[DRAGON][0] > 2)
	{
		return false;
	}
    
	return true;
}
////判断超胡	cai v1.1
//BYTE CGameLogical::JudgeHuType(BYTE chair)
//{
//	//CCLOG("Judge32: %d,  JudgeQiQiaoDui: %d", JudgeQiQiaoDui(chair), JudgeQingYiSe(chair));
//	
//	m_nGen[chair] = JudgeGen(chair);
//    
//	if(!Judge32(chair))	//该函数会处理好“将”	
//	{
//		if (JudgeQiQiaoDui(chair))				//判断七对
//		{
//			bool bQing = JudgeQingYiSe(chair);
//            
//			if (bQing && m_nGen[chair])
//			{
//				return OK_QINGLONG_QIDUI;	//11 青龙七对
//			}
//			else if (bQing)
//			{
//				return OK_QING_QIDUI;		//9 清七对
//			}
//			else if (m_nGen[chair])
//			{
//				return OK_LONG_QIDUI;		//8 龙七对
//			}
//			else
//			{
//				return OK_QIDUI;			//5 七对
//			}
//		}
//        else
//        {
//            return FALSE_ALL;
//        }
//	}
//    
//	bool bQingYiSe = JudgeQingYiSe(chair);
//	bool bYaoJiu = JudgeHaveYaoJiu(chair);
//    
//	if(bYaoJiu && bQingYiSe)
//	{
//		return OK_QING_YAOJIU;			//10 清幺九
//	}
//	
//	bool bPengPeng = JudgePengPengHu(chair);
//	bool b258 = Judge258(chair);
//    
//	if (bPengPeng && b258)
//	{
//		return OK_JIANG_PENG;				//7 将碰
//	}
//    
//	if(bQingYiSe && bPengPeng)
//	{
//		return OK_QING_PENG;				//6 清碰
//	}
//    
//	if (bYaoJiu)
//	{
//		return OK_YAOJIU;					//4 幺九
//	}
//    
//	if(bQingYiSe)
//	{
//		return OK_QINGYISE;				//3 清一色
//	}
//    
//	if(bPengPeng)
//	{
//		return OK_PENGPENGHU;				//2 碰碰胡
//	}
//    
//	return OK_PINGHU;
//}

//判断超胡	cai v1.1
BYTE CGameLogical::JudgeHuType(BYTE chair)
{	
	m_nGen[chair]	= JudgeGen(chair);
	bool bType32	= Judge32(chair);
	bool bQiDui		= JudgeQiQiaoDui(chair);
	bool bQing		= JudgeQingYiSe(chair);
    
//	if (bType32 || bQiDui)
//	{
//		CCLOG("Judge32: %d,  JudgeQiQiaoDui: %d, JudgeQingYiSe: %d", 
//              bType32, bQiDui, bQing);
//	}
	
	if(!bType32 && !bQiDui)	//不是32牌型也不是7对
	{
		return FALSE_ALL;
	}
	else if (bQiDui)				//判断七对，可能同时是32牌型
	{	
		if (bQing && m_nGen[chair])
		{
			m_nGen[chair]--;
			return OK_QINGLONG_QIDUI;	//11 青龙七对
		}
		else if (bQing)
		{
			return OK_QING_QIDUI;		//9 清七对
		}
		else if (m_nGen[chair])
		{
			m_nGen[chair]--;
			return OK_LONG_QIDUI;		//8 龙七对
		}
		else
		{
			return OK_QIDUI;			//5 七对
		}
	}
	
	bool bYaoJiu = JudgeYaoJiuHu(chair);
//	CCLOG("JudgeYaoJiuHu: %d", bYaoJiu);
	
	if(bYaoJiu && bQing)
	{
		return OK_QING_YAOJIU;			//10 清幺九
	}
	
	bool bPengPeng = JudgePengPengHu(chair);
	bool b258 = Judge258(chair);
	
	if (bPengPeng && b258)
	{
		return OK_JIANG_PENG;				//7 将碰
	}
	
	if(bQing && bPengPeng)
	{
		return OK_QING_PENG;				//6 清碰
	}
	
	if (bYaoJiu)
	{
		return OK_YAOJIU;					//4 幺九
	}
	
	if(bQing)
	{
		return OK_QINGYISE;				//3 清一色
	}
	
	if(bPengPeng)
	{
		return OK_PENGPENGHU;				//2 碰碰胡
	}
	
	return OK_PINGHU;
}

//判断字一色
bool CGameLogical::JudgeZiYiSe(BYTE chair)
{
	BYTE nStandCount = m_sStandCard[chair].nNum;
    int i;
	for(i=0; i<nStandCount; i++)
	{
		bool bZiPai = IsZiPai(m_sStandCard[chair].nFirstCard[i]);
		if(!bZiPai)
		{
			return false;
		}
	}
    
	for(i=WAN; i<=TONG; i++)
	{
		if(m_sPlayer[chair].nCard[i][0])
		{
			return false;
		}
	}
    
	return true;
}

//判断么九  ///cai v1.1
/*///<
BYTE CGameLogical::JudgeYaoJiuHu(BYTE chair, bool bJudgeShiSanYao)
{
	BYTE nStandCount = m_sStandCard[chair].nNum;
	bool bQing = true;
	if(nStandCount)
	{
		if(bJudgeShiSanYao)
		{
			return CHAOHU_TYPE_INVALID;
		}
		
		if(IsShunInStandCards(chair))
		{
			return CHAOHU_TYPE_INVALID;
		}
        
		for(int i=0; i<nStandCount; i++)
		{
			bool bYaoJiu = IsYaoJiu(m_sStandCard[chair].nFirstCard[i]);
			if(!bYaoJiu)
			{
				bool bZiPai = IsZiPai(m_sStandCard[chair].nFirstCard[i]);
				if(!bZiPai)
				{
					return CHAOHU_TYPE_INVALID;
				}
				bQing = false;
			}
		}
	}
	
    bool bHaveJiang = false;  //为判断十三么
	for(int i=WAN; i<=DRAGON; i++)
	{
		for(int j=1; j<=m_sPlayer[chair].nCard[i][0]; j++)
		{
			if(i <= TONG)          //判断普通牌是否么九牌
			{
				bool bYaoJiu = IsYaoJiu(m_sPlayer[chair].nCard[i][j]);
				if(!bYaoJiu)
				{
					return CHAOHU_TYPE_INVALID;
				}
			}
			if(i == FENG || i == DRAGON)         // 如有字牌为混
			{
				if(m_sPlayer[chair].nCard[i][0])   
				{
					bQing = false;
				}
			}
            
			if(bJudgeShiSanYao)  //判断十三么，只能有两张相同
			{
				if(j>1 && m_sPlayer[chair].nCard[i][j] == m_sPlayer[chair].nCard[i][j-1])
				{
					if(bHaveJiang)
					{
						return CHAOHU_TYPE_INVALID;    //如果有将，则不是十三么
					}
					bHaveJiang = true;
				}
			}
		}
	}
    
	if(m_sPlayer[chair].nCard[DRAGON][0])   // 如有字牌为混
	{
		bQing = false;
	}
    
 if(bQing)
 {
 return QINGYAOJIU;
 }
 else
 {
 return HUNYAOJIU;
 }
 }
 *////>

// cai v1.1 判断么九  
bool CGameLogical::JudgeYaoJiuHu( BYTE chair )
{
	BYTE nStandCount = m_sStandCard[chair].nNum;
    ///	bool bQing = true;
	if(nStandCount)
	{
		for( int i=0; i < nStandCount; i++ )
		{
			if ( m_sStandCard[chair].nType[i] == SHUN)	
			{
				bool bYaoQi = IsYaoQi(m_sStandCard[chair].nFirstCard[i]);
				if (!bYaoQi)
				{
					return false;
				}
			}
			else
			{
				bool bYaoJiu = IsYaoJiu(m_sStandCard[chair].nFirstCard[i]);
				if (!bYaoJiu)
				{
					return false;
				}
			}
		}
	}
	
	for(int i=WAN; i<=TONG; i++)
	{
		for (int j = 1; j <= m_sPlayer[chair].nCard[i][0]; ++j)
		{
			if (Is456(m_sPlayer[chair].nCard[i][j]))
			{
				return false;
			}
		}
        
		if (!ListJudgeYaoJiu(m_sPlayer[chair].nCard[i]))	
		{
			return false;
		}
	}	
	return true;
}


// cai v1.1 判断258  
bool CGameLogical::Judge258( BYTE chair )
{
	BYTE nStandCount = m_sStandCard[chair].nNum;
	///	bool bQing = true;
	if(nStandCount)
	{
		if(IsShunInStandCards(chair))
		{
			return false;
		}
		
		for(int i=0; i<nStandCount; i++)
		{
			bool b258 = Is258(m_sStandCard[chair].nFirstCard[i]);
			if(!b258)
			{
				return false;
			}
		}
	}
	
	for(int i=WAN; i<=TONG; i++)
	{
		for(int j=1; j<=m_sPlayer[chair].nCard[i][0]; j++)
		{
			if(i <= TONG)          //判断普通牌是否么九牌
			{
				bool bYaoJiu = Is258(m_sPlayer[chair].nCard[i][j]);
				if(!bYaoJiu)
				{
					return false;
				}
			}
		}
	}
	
	return true;
}

// 命令处理函数
void CGameLogical::HandleChooseEat(BYTE nChair, LPCVOID lpData, int nSize)
{
	BYTE nCardBuf[3] = {255,255,255};
    
	nCardBuf[0] = *((BYTE *)lpData);
	nCardBuf[1] = nCardBuf[0]+1;
	nCardBuf[2] = nCardBuf[0]+2;
    
	BYTE nTempCard = m_sOutedCard.nCard;
	PAI_TYPE CardType = GetCardType(nTempCard);
	
	if (CardType != GetCardType(nCardBuf[0]))
	{
		CCLOG("错误的吃牌类型");
		return;
	}
    int i;
	// 删掉其他两张牌
	for (i = 0; i < 3; i ++)
	{
		if (nCardBuf[i] != nTempCard)
		{
			ListDelete(m_sPlayer[nChair].nCard[CardType],nCardBuf[i]);
		}
	}
	// 设置倒牌
	BYTE nStandCount = m_sStandCard[nChair].nNum;
	m_sStandCard[nChair].nType[nStandCount] = SHUN;
	m_sStandCard[nChair].nFirstCard[nStandCount] = nCardBuf[0];
	m_sStandCard[nChair].nCard[nStandCount] = nTempCard;
	m_sStandCard[nChair].nWhoGiveMe[nStandCount] = m_sOutedCard.nChair;
	m_sStandCard[nChair].nNum ++;
    
	m_sPlayer[nChair].nLen -= 3;
	m_sOutedCard.clear();
	
	// 找出第14张牌
	BYTE nLastType = DRAGON;
	while(!(m_sPlayer[nChair].nCard[nLastType][0]))
	{
		nLastType --;
	}
	if(255 == nLastType)
	{
		CCLOG("竟然没有牌, 发生在HandleChooseEat");
	}
	BYTE nCardCount = m_sPlayer[nChair].nCard[nLastType][0];
	BYTE nFouteenCard = m_sPlayer[nChair].nCard[nLastType][nCardCount];
	ListDelete(m_sPlayer[nChair].nCard[nLastType],nFouteenCard);
    
	m_sPlayer[nChair].nCardTakenNow = nFouteenCard;
	
	for (i = 0; i < PLAYER_COUNT; i ++)
	{
		m_sPlayer[i].nState = WAITING;
	}
	// 改变状态
	m_sysPhase = PhaseThinkingOutCard;
	m_sPlayer[nChair].nState = THINK_OUTCARD;
	m_chairCurrentPlayer = nChair;
    
	//--m_pSite -> NotifySceneChanged();
    
}

void CGameLogical::HandleChoosePeng(BYTE nChair, LPCVOID lpData, int nSize)
{
	BYTE nTempCard = m_sOutedCard.nCard;
	PAI_TYPE CardType = GetCardType(nTempCard);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在HandleChoosePeng");
		return;
	}
	
	ListDelete(m_sPlayer[nChair].nCard[CardType], nTempCard);
	ListDelete(m_sPlayer[nChair].nCard[CardType], nTempCard);
	
	// 设置倒牌
	BYTE nStandCount = m_sStandCard[nChair].nNum;
	m_sStandCard[nChair].nType[nStandCount] = KE;
	m_sStandCard[nChair].nFirstCard[nStandCount] = nTempCard;
	m_sStandCard[nChair].nCard[nStandCount] = nTempCard;
	m_sStandCard[nChair].nWhoGiveMe[nStandCount] = m_sOutedCard.nChair;
	m_sStandCard[nChair].nNum ++;
	
	// 找出第14张牌
	BYTE nLastType = TONG;
	while(!(m_sPlayer[nChair].nCard[nLastType][0]))
	{
		nLastType --;
	}
	if(255 == nLastType)
	{
		CCLOG("竟然没有牌, 发生在HandleChooseEat");
	}
	BYTE nCardCount = m_sPlayer[nChair].nCard[nLastType][0];
	BYTE nFouteenCard = m_sPlayer[nChair].nCard[nLastType][nCardCount];
	ListDelete(m_sPlayer[nChair].nCard[nLastType],nFouteenCard);
    
	m_sPlayer[nChair].nCardTakenNow = nFouteenCard;
    
	m_sPlayer[nChair].nLen -= 3;
	m_sOutedCard.clear();
	
	for (int i = 0; i < PLAYER_COUNT; i ++)
	{
		if (m_sPlayer[i].nState != BLOOD_HU)
		{
			m_sPlayer[i].nState = WAITING;
		}
	}
	
	// 改变状态
	m_sysPhase = PhaseThinkingOutCard;
	m_chairCurrentPlayer = nChair;
	m_sPlayer[nChair].nState = THINK_OUTCARD;
    
	//--m_pSite -> NotifySceneChanged();
    
}

///cai v2.1
void CGameLogical::HandleChooseAnGang(BYTE nChair, LPCVOID lpData, int nSize)
{
	BYTE nTempCard = *((BYTE *)lpData);
	
	PAI_TYPE CardType = GetCardType(m_sPlayer[nChair].nCardTakenNow);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在HandleChooseAnGang1");
		return ;
	}
	ListInsert(m_sPlayer[nChair].nCard[CardType], m_sPlayer[nChair].nCardTakenNow);
	m_sPlayer[nChair].nCardTakenNow = 255;
    
	
	CardType = GetCardType(nTempCard);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在HandleChooseAnGang2");
		return ;
	}
	ListDelete(m_sPlayer[nChair].nCard[CardType], nTempCard);
	ListDelete(m_sPlayer[nChair].nCard[CardType], nTempCard);
	ListDelete(m_sPlayer[nChair].nCard[CardType], nTempCard);
	ListDelete(m_sPlayer[nChair].nCard[CardType], nTempCard);
    
	m_sPlayer[nChair].nLen -= 3;
	
	// 设置倒牌
	BYTE nStandCount = m_sStandCard[nChair].nNum;
	m_sStandCard[nChair].nType[nStandCount] = ANGANG;
	m_sStandCard[nChair].nFirstCard[nStandCount] = nTempCard;
	m_sStandCard[nChair].nCard[nStandCount] = nTempCard;
	m_sStandCard[nChair].nWhoGiveMe[nStandCount] = nChair;
	m_sStandCard[nChair].nNum ++;
    
	m_bHaveGang = true;  //for 杠上花
	
    BYTE nGangScore = 0;
    BYTE nGangPao = 0;
    memset(m_wGFXYScore, 0, sizeof(m_wGFXYScore));
	for (int i=0; i<PLAYER_COUNT; ++i)
	{
		if (i == nChair)
		{
			continue;
		}
		
		if (m_sPlayer[i].nState!=BLOOD_HU)
		{
			nGangScore = 2*SCORE_BASE;
            
			m_wGFXYScore[i] = -nGangScore;			//扣本次刮风下雨分
			m_wGangScore[i][i] -= nGangScore;		//总刮风下雨分
            
			m_wGFXYScore[nChair] += nGangScore;				//赢本次刮风下雨分
			m_wGangScore[nChair][nChair] += nGangScore;		//总刮风下雨分
            
			m_wGangScore[nChair][i] += nGangScore;			//赢对应玩家刮风下雨分
            
			nGangPao += nGangScore;
            
		}
	}
    
	m_sGangPao.InitData(true, m_sOutedCard.nCard, m_sOutedCard.nChair, ANGANG, nGangPao);
    
	// 补发张牌给玩家
	m_sysPhase = PhaseThinkingOutCard;
	m_chairCurrentPlayer = nChair;
	//此刻要更新胡牌列表
	InitHuList(nChair);
	if(!(DealCard(nChair)))
	{
		return;
	}
    
	//暗杠需要记录入命令
	m_chairSendCmd = m_chairCurrentPlayer;
	m_currentCmd = CLIENT_ANGANG;
	m_sOutedCard.clear();
    if(m_nEndReason == REASON_NOCARD)
	{
		CCLog("end reason no card");
		return;
	}
	//--m_pSite -> NotifySceneChanged();
    
}

///	cai v2.1
void CGameLogical::HandleChooseMingGangM(BYTE nChair, LPCVOID lpData, int nSize)
{
	BYTE nTempCard = *((BYTE *)lpData);
	PAI_TYPE CardType = GetCardType(nTempCard);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在HandleChooseMingGangM1");
		return ;
	}
    
	// 初始化杠结构
	m_sQiangGang.InitData(true, nTempCard, nChair); //处理抢杠
	m_bHaveGang = true;					//for 杠上花
    
	BYTE nGangScore = 0;
    BYTE nGangPao = 0;
    memset(m_wGFXYScore, 0, sizeof(m_wGFXYScore));
	for (int i=0; i<PLAYER_COUNT; ++i)
	{
		if (i == nChair)
		{
			continue;
		}
		
		if (m_sPlayer[i].nState!=BLOOD_HU)
		{
			nGangScore = SCORE_BASE;
            
			m_wGFXYScore[i] = -nGangScore;
			m_wGangScore[i][i] -= nGangScore;
            
			m_wGFXYScore[nChair] += nGangScore;
			m_wGangScore[nChair][nChair] += nGangScore;
            
			m_wGangScore[nChair][i] += nGangScore;
            
			nGangPao += nGangScore;
            
		}
	}
    
	m_sGangPao.InitData(true, m_sOutedCard.nCard, m_sOutedCard.nChair, MGANG_MYSELF, nGangPao);
    
	// 改变手持牌，弯杠牌是第14张牌
	if (m_sPlayer[nChair].nCardTakenNow == nTempCard)
	{
		m_sPlayer[nChair].nCardTakenNow = 255;
	}
	else //弯杠牌在手持牌中
	{
		ListDelete(m_sPlayer[nChair].nCard[CardType], nTempCard);
        
		PAI_TYPE nCardType = GetCardType(m_sPlayer[nChair].nCardTakenNow);
		if(PAI_TYPE_INVALID == nCardType)
		{
			CCLOG("错误的牌类型，发生在HandleChooseMingGangM2");
			return ;
		}
		ListInsert(m_sPlayer[nChair].nCard[nCardType], m_sPlayer[nChair].nCardTakenNow);
		m_sPlayer[nChair].nCardTakenNow = 255;
        
	}
    
    int i;
	// 设置倒牌
	for (i = 0; i < m_sStandCard[nChair].nNum; i ++)
	{
		if (m_sStandCard[nChair].nType[i] == KE 
			&& m_sStandCard[nChair].nCard[i] == nTempCard)
		{
			m_sStandCard[nChair].nType[i] = MGANG_MYSELF;
			break;
		}
	}
    
	m_sOutedCard.clear();
    
    //若有人可以胡，抢杠胡
	BYTE chair=nChair, bHaveCmd=0;
	for (i=0; i<3; i++)
	{
        /// cai
		chair = AntiClock(chair);
        ///		CCLOG("HandleOutCard m_sPlayer[%d].nState: %d", chair, m_sPlayer[chair].nState);
		if (m_sPlayer[chair].nState == BLOOD_HU)
		{
			continue;
		}
        
		if (IsInHuList(chair, nTempCard))
		{
			ListInsert(m_sPlayer[chair].nCard[CardType], nTempCard);
			//1,判断胡
			if(JudgeHu(chair))	
			{				
				m_HuCurt[chair].AddHU(QIANGGANG);
				m_HuCurt[m_chairHu[i]].nState = ZI_MO;   //抢杠算作自摸
				//3，判断番数
				if(JudgeFan(chair) >= m_nMinFan) 
				{
					m_bChooseBuf[chair][3] = 1;
					bHaveCmd = 1;
					m_sPlayer[chair].nState = CHOOSING;
				}
			}
			m_HuCurt[chair].clear();
			
			ListDelete(m_sPlayer[chair].nCard[CardType], nTempCard);
		}
        
	}
	if (bHaveCmd) 
	{
		m_sysPhase = PhaseChoosing;
		//--m_pSite->NotifySceneChanged();
	}
	else	// 补发张牌给玩家
	{
        //		m_sGang.clear();  不能清杠，因为可能有杠上花
		m_sysPhase = PhaseThinkingOutCard;
		m_chairCurrentPlayer = nChair;
        
        //paddy add
        InitHuList(nChair); // 此处要更新胡牌列表
        
		if(!DealCard(nChair))
		{
			return;
		}
        
		//摸杠需要记录入命令
		m_chairSendCmd = m_chairCurrentPlayer;
		m_currentCmd = CLIENT_WANGANG;
        if(m_nEndReason == REASON_NOCARD)
		{
			CCLog("end reason no card");
			return;
		}
		//--m_pSite -> NotifySceneChanged();
	}
    
}

///cai v2.1
void CGameLogical::HandleChooseMingGangC(BYTE nChair, LPCVOID lpData, int nSize)	
{
	BYTE nTempCard = m_sOutedCard.nCard;
	PAI_TYPE CardType = GetCardType(nTempCard);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在HandleChooseMingGangC");
		return ;
	}
	
	ListDelete(m_sPlayer[nChair].nCard[CardType], nTempCard);
	ListDelete(m_sPlayer[nChair].nCard[CardType], nTempCard);
	ListDelete(m_sPlayer[nChair].nCard[CardType], nTempCard);
	
	// 设置倒牌
	BYTE nStandCount = m_sStandCard[nChair].nNum;
	m_sStandCard[nChair].nType[nStandCount] = MGANG_COME;
	m_sStandCard[nChair].nFirstCard[nStandCount] = nTempCard;
	m_sStandCard[nChair].nCard[nStandCount] = nTempCard;
	m_sStandCard[nChair].nWhoGiveMe[nStandCount] = m_sOutedCard.nChair;
	m_sStandCard[nChair].nNum ++;
    
	m_sPlayer[nChair].nLen -= 3;
	m_sOutedCard.clear();
    
	m_bHaveGang = true;  //for 杠上花
	
	BYTE nGangScore = 0;
    BYTE nGangPao = 0;
    memset(m_wGFXYScore, 0, sizeof(m_wGFXYScore));
	for (int i=0; i<PLAYER_COUNT; ++i)
	{
		if (i == nChair)
		{
			continue;
		}
        
		if (i == m_sStandCard[nChair].nWhoGiveMe[nStandCount])
		{
			nGangScore = 2*SCORE_BASE;
            
			m_wGFXYScore[i] = -nGangScore;
			m_wGangScore[i][i] -= nGangScore;
            
			m_wGFXYScore[nChair] += nGangScore;
			m_wGangScore[nChair][nChair] += nGangScore;
            
			m_wGangScore[nChair][i] += nGangScore;
            
			nGangPao += nGangScore;
		}
		else if (m_enGFXY == GFXYJiaJiaYou && m_sPlayer[i].nState!=BLOOD_HU)
		{
			nGangScore = SCORE_BASE;
            
			m_wGFXYScore[i] = -nGangScore;
			m_wGangScore[i][i] -= nGangScore;
            
			m_wGFXYScore[nChair] += nGangScore;
			m_wGangScore[nChair][nChair] += nGangScore;
			
			m_wGangScore[nChair][i] += nGangScore;
            
			nGangPao += nGangScore;
            
		}
	}
    
	m_sGangPao.InitData(true, m_sOutedCard.nCard, m_sOutedCard.nChair,MGANG_COME, nGangPao);
	
	// 补发张牌给玩家
    m_sysPhase = PhaseThinkingOutCard;
	m_chairCurrentPlayer = nChair;
	if(!DealCard(nChair))
	{
		return;
	}
    if(m_nEndReason == REASON_NOCARD)
	{
		CCLOG("end reason no card");
		return;
	}
	//--m_pSite -> NotifySceneChanged();
    
}

/// cai v2.1
void CGameLogical::HandleHuZiMo(BYTE nChair, LPCVOID lpData, int nSize)			//处理自摸
{
  	BYTE nTempCard = m_sPlayer[nChair].nCardTakenNow;
	PAI_TYPE CardType = GetCardType(nTempCard);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在HandleHuZiMo");
		return ;
	}
    
	ListInsert(m_sPlayer[nChair].nCard[CardType], nTempCard);
 	bool bHu = JudgeHu(nChair);
	m_HuCurt[nChair].nCard = nTempCard;
	ListDelete(m_sPlayer[nChair].nCard[CardType], nTempCard);
    
	m_HuCurt[nChair].nState = ZI_MO;
    
	if(!bHu) //诈胡
	{
		CCLOG("有人诈胡 at HandleHuZiMo");
		HandleZhaHu(nChair);
		m_HuCurt[nChair].clear();
	}
	else 
	{
        /// cai
        ///		if(m_HuCurt[nChair].nType == FENGDINGHU)   
        ///		{
        ///m_HuCurt[nChair].AddHU(ZIMOFAN);
        
        if (m_bHaveGang)						//杠开
        {
            m_bHaveGang = false;
            m_HuCurt[nChair].AddHU(GANGKAI);
        }
        /*///<
         if(m_nCountAllot >= CARD_NUM)					//海底胡
         {
         m_HuCurt[nChair].AddHU(HAIDIHU);
         }
         *////>
        ///		}
        
		if(ScoreOneHuCal(nChair))
		{
            m_chairSendCmd = m_chairCurrentPlayer;
			m_currentCmd = CLIENT_HU;
			if (!m_bBloodyGame)
			{
				m_nEndReason = REASON_HU;
				HandleSetOver();
				//--m_pSite->SetSceneStatusToFree(CONDITION_STOP_LOGIC);
			}
			else
			{
				m_bChairHu[nChair] = true;
				m_nCountHu++;
				m_sPlayer[nChair].nState = BLOOD_HU;
                
                ///				ListInsert(m_sPlayer[nChair].nCard[CardType], m_sPlayer[nChair].nCardTakenNow); //整理完毕
                ///				m_sPlayer[nChair].nCardTakenNow = 255;
                
				if (m_nCountHu>=3)		//三个玩家胡牌
				{
					m_nEndReason = REASON_HU;
					HandleSetOver();
					//--m_pSite->SetSceneStatusToFree(CONDITION_STOP_LOGIC);
				}
				else					//游戏继续
				{
					BYTE nNextChair = nChair;
					do 
					{
						nNextChair = AntiClock(nNextChair);
					} while (m_bChairHu[nNextChair]);
					
					if (nNextChair == nChair)
					{
						CCLOG("find unHu player error, chair:%d", nChair);
						return;
					}
                    
					m_sysPhase = PhaseThinkingOutCard;
					m_chairCurrentPlayer = nNextChair;
					
					//start the expire timer
					//--m_pSite ->KillTimer(TIME_ID_EXPIRE);
					//--m_pSite ->SetTimer(TIME_ID_EXPIRE, TIME_EXPIRE);
					
					if(!DealCard(nNextChair))
					{
						return;
					}
                    if(m_nEndReason == REASON_NOCARD)
					{
						CCLOG("end reason no card");
						return;
					}
					//--m_pSite -> NotifySceneChanged();
				}
			}
		}
		else	//番数不够，判诈胡
		{
			HandleZhaHu(nChair);
			m_HuCurt[nChair].clear();
            
			m_sysPhase = PhaseThinkingOutCard;
			m_chairCurrentPlayer = nChair;
			m_sPlayer[nChair].nState = THINK_OUTCARD;
			
			//--m_pSite -> NotifySceneChanged();
			
		}
    }
}

///cai v2.1
void CGameLogical::HandleOutCard(BYTE nChair, LPCVOID lpData, int nSize)		//处理出牌
{
	BYTE *pBuf = (BYTE*)lpData;
    
    /*///<	
     if(m_bMissHu[nChair])
     {
     m_bMissHu[nChair] = false; //如果出牌了，漏胡就可以继续胡了。
     
     DWORD dwUserID = //--m_pSite->GetUserID(nChair);
     char szMsg[512];
     strcpy(szMsg, "\n系统： 您好！ 您的炮胡禁令已被取消。" );
     //--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szMsg);
     }
     *////>
    
	//一旦有人出牌，表示上一轮竞争已经结束, 可以清CMD
	m_chairSendCmd = 255;							// 当前发命令的玩家
	m_currentCmd = 0;							// 当前的命令
    
	// 更新桌面牌
	if(m_sOutedCard.nCard != 255)
	{
		BYTE oldOutChair = m_sOutedCard.nChair;
		m_nTableCards[oldOutChair][m_nNumTableCards[oldOutChair]++] = m_sOutedCard.nCard;
		m_sOutedCard.clear();
	}
    
	// 清除杠标记
	m_sQiangGang.clear();  
	m_bHaveGang = false;  
    
	//接收数据
	m_sOutedCard.nChair = nChair;
	BYTE pos  = pBuf[0];
	//memcpy(m_nHuList[nChair], &pBuf[1], sizeof(m_nHuList[nChair]));

    
	//若打出的是第14张牌
	if(pos == 13)
	{
		m_sOutedCard.nCard = m_sPlayer[nChair].nCardTakenNow;
		m_sPlayer[nChair].nCardTakenNow = 255;
	}
	else if(pos < 13)	//若打出的是第1-13张牌, 要整理牌列表
	{
		//定位pos在nCard[n][m]中的位置
		BYTE nTypeCount = DRAGON;
		BYTE nCardCount = m_sPlayer[nChair].nCard[nTypeCount][0];
		for(int i=12; ; i--)
		{
			while(!nCardCount && nTypeCount)
			{
				nTypeCount--;
				nCardCount = m_sPlayer[nChair].nCard[nTypeCount][0];
			}
			if(pos == i)
			{
				break;
			}
			nCardCount --;
		}
		
		m_sOutedCard.nCard = m_sPlayer[nChair].nCard[nTypeCount][nCardCount];	
		ListDelete(m_sPlayer[nChair].nCard[nTypeCount],m_sOutedCard.nCard);
        
		PAI_TYPE CardType = GetCardType(m_sPlayer[nChair].nCardTakenNow);
		if(PAI_TYPE_INVALID == CardType)
		{
			CCLOG("错误的牌类型，发生在HandleOutCard");
			return;
		}
		ListInsert(m_sPlayer[nChair].nCard[CardType], m_sPlayer[nChair].nCardTakenNow); //整理完毕
		m_sPlayer[nChair].nCardTakenNow = 255;
	}
        
    SetHuList(nChair);
	
	bool bHaveCmd = 0;
	m_sPlayer[nChair].bSeenOutCard = 1; 
	BYTE chair = nChair;
	for (int i=0; i<4; i++)
	{
        if (m_sPlayer[chair].nState == CHOOSING) {
            m_sPlayer[chair].nState = WAITING; 
        }
    }    
	for (int i=0; i<3; i++)
	{
		chair = AntiClock(chair);
        //CCLOG("HandleOutCard m_sPlayer[%d].nState: %d", chair, m_sPlayer[chair].nState);
		if (m_sPlayer[chair].nState == BLOOD_HU)
		{
			continue;
		}
		m_sPlayer[chair].bSeenOutCard = 0; 
        
		if (FindPeng(chair))
		{
			m_sPlayer[chair].bSeenOutCard = 1; 
			m_bChooseBuf[chair][1] = 1;
			bHaveCmd = 1;
			m_sPlayer[chair].nState = CHOOSING;
		}
		if (FindMingGangCome(chair))
		{
			m_sPlayer[chair].bSeenOutCard = 1; 
			m_bChooseBuf[chair][2] = 1;
			bHaveCmd = 1;
			m_sPlayer[chair].nState = CHOOSING;
		}
		if (IsInHuList(chair, m_sOutedCard.nCard))
		{
            ///			if(false == m_bMissHu[chair]) //只有没有漏胡的时候才可以胡
            ///			{
            BYTE nTempCard = m_sOutedCard.nCard;
            PAI_TYPE CardType = GetCardType(nTempCard);
            if(PAI_TYPE_INVALID == CardType)
            {
                CCLOG("错误的牌类型，发生在HandleOutCard2");
                return;
            }
            ListInsert(m_sPlayer[chair].nCard[CardType], nTempCard);
            //1,判断胡
            if(JudgeHu(chair))	
            {
                //2，加入附加胡
                if (m_sGangPao.mark)
                {
                    m_HuCurt[chair].AddHU(GANGPAO);
                }
                //3，判断番数
                if(JudgeFan(chair) >= m_nMinFan) 
                {
                    m_sPlayer[chair].bSeenOutCard = 1; 
                    m_bChooseBuf[chair][3] = 1;
                    bHaveCmd = 1;
                    m_sPlayer[chair].nState = CHOOSING;
                }
            }
            m_HuCurt[chair].clear();
            
            ListDelete(m_sPlayer[chair].nCard[CardType], nTempCard);
			
            ///			}
		}
	}
	//CCLOG("HandleOutCard, bHaveCmd:%d", bHaveCmd);
	if (bHaveCmd) //若有人可以选择,进入选择状态
	{
		m_sysPhase = PhaseChoosing;
		//--m_pSite->NotifySceneChanged();
 	}
	else	// 发牌给下家
	{	
		chair = nChair;
		do 
		{
			chair = AntiClock(chair);
		} while (m_bChairHu[chair]);
		
		if (chair == nChair)
		{
			CCLOG("find unHu player error, chair:%d", chair);
			return;
		}
		
		m_sysPhase = PhaseThinkingOutCard;
		m_chairCurrentPlayer = chair;
        
        m_sGangPao.clear();
        
		//start the expire timer
		//--m_pSite ->KillTimer(TIME_ID_EXPIRE);
		//--m_pSite ->SetTimer(TIME_ID_EXPIRE, TIME_EXPIRE);
        
        if(!DealCard(chair))
		{
			CCLOG("DealCard return false in HandleOutCard()");
			return;
		}
        if(m_nEndReason == REASON_NOCARD)
		{
			CCLOG("end reason no card");
			return;
		}
		//--m_pSite -> NotifySceneChanged();
	}
}

/// cai v2.1
void CGameLogical::HandleChooseResult()
{
	BYTE nTempCard=255;
	GAME_CMD_DATA cmd;
	PAI_TYPE CardType = PAI_TYPE_INVALID; 
    
    int i;
	//抉择后全部可见
	for(i = 0; i< PLAYER_COUNT; i ++)
	{
		m_sPlayer[i].bSeenOutCard = 1;
	}
    
	if (m_sQiangGang.mark )	// 处理抢杠
	{
		nTempCard = m_sQiangGang.card;
		CardType = GetCardType(nTempCard);
		if(PAI_TYPE_INVALID == CardType)
		{
			CCLOG("错误的牌类型，发生在HandleChooseResult 抢杠");
			return;
		}
        
		bool bHaveHu = false;
		
		if (m_nNumCmdHu)
		{
			for (i=0; i<m_nNumCmdHu; i++)
			{
				ListInsert(m_sPlayer[m_chairHu[i]].nCard[CardType], nTempCard);
				bool bHu = JudgeHu(m_chairHu[i]);
				m_HuCurt[m_chairHu[i]].nCard = nTempCard;
				ListDelete(m_sPlayer[m_chairHu[i]].nCard[CardType], nTempCard);
                
				if(!bHu) 
				{
					CCLOG("有人诈胡 at HandleChooseResult1");
				    HandleZhaHu(m_chairHu[i]);
					m_HuCurt[m_chairHu[i]].clear();
				}
				else
				{
					m_bHaveGang = false;  //杠上花
                    ///cai
                    ///					if (m_HuCurt[m_chairHu[i]].nType == FENGDINGHU)
                    ///					{
                    ///						m_HuCurt[m_chairHu[i]].AddHU(QIANGGANG);
                    ///					}
                    
					m_HuCurt[m_chairHu[i]].AddHU(QIANGGANG);
					m_HuCurt[m_chairHu[i]].nState = ZI_MO;   //抢杠算作自摸，再算包牌
                    
					if(ScoreOneHuCal(m_chairHu[i], m_sQiangGang.chair))
					{
						bHaveHu = true;
						if (m_bBloodyGame)		//血战场
						{
							m_bChairHu[m_chairHu[i]] = true;
							m_nCountHu++;
							m_sPlayer[m_chairHu[i]].nState = BLOOD_HU;
						}
						//ListInsert(m_sPlayer[m_chairHu[i]].nCard[CardType], nTempCard); //整理完毕
						m_sPlayer[m_chairHu[i]].nCardTakenNow = nTempCard;
                        
					}
					else
					{
						bHaveHu = false;
						HandleZhaHu(m_chairHu[i]);
						m_HuCurt[m_chairHu[i]].clear();
					}
				}
			}
		}
		if(bHaveHu) //抢杠胡
		{
			//m_chairSendCmd = m_chairCurrentPlayer;
			m_sOutedCard.nChair = m_sQiangGang.chair;
			m_sOutedCard.nCard	= m_sQiangGang.card;
			m_currentCmd = CLIENT_HU;
            
			// 设置倒牌, 抢杠后杠牌变成刻子
			for (i = 0; i < m_sStandCard[m_sOutedCard.nChair].nNum; i ++)
			{
				if (m_sStandCard[m_sOutedCard.nChair].nType[i] == MGANG_MYSELF 
					&& m_sStandCard[m_sOutedCard.nChair].nCard[i] == m_sOutedCard.nCard)
				{
					m_sStandCard[m_sOutedCard.nChair].nType[i] = KE;
					break;
				}
			}
            
			if (!m_bBloodyGame)	
			{
				m_nEndReason = REASON_HU;
				HandleSetOver();
				//--m_pSite->SetSceneStatusToFree(CONDITION_STOP_LOGIC);
				return;
			}
			else		//血战场
			{
				if (m_nCountHu>=3)		//三个玩家胡牌
				{
                    ///					m_nEndReason = REASON_HU_BLOOD;
					m_nEndReason = REASON_HU;
                    
					HandleSetOver();
					//--m_pSite->SetSceneStatusToFree(CONDITION_STOP_LOGIC);
					return;
				}
				else					//游戏继续
				{
					BYTE nNextChair = m_sOutedCard.nChair;
					do 
					{
						nNextChair = AntiClock(nNextChair);
					} while (m_bChairHu[nNextChair]);
					
					if (nNextChair == m_chairCurrentPlayer)
					{
						CCLOG("find unHu player error, chair:%d", m_chairCurrentPlayer);
						return;
					}
					
					m_sysPhase = PhaseThinkingOutCard;
					m_chairCurrentPlayer = nNextChair;
                    m_sOutedCard.clear();
					
					//start the expire timer
					//--m_pSite ->KillTimer(TIME_ID_EXPIRE);
					//--m_pSite ->SetTimer(TIME_ID_EXPIRE, TIME_EXPIRE);
					
					if(!DealCard(nNextChair))
					{
						return;
					}
                    if(m_nEndReason == REASON_NOCARD)
					{
						CCLOG("end reason no card");
						return;
					}
					//--m_pSite -> NotifySceneChanged();
					return;
				}
			}
		}
		else // 给杠的玩家补张	
		{	
			m_sysPhase = PhaseThinkingOutCard;
			m_chairCurrentPlayer = m_sQiangGang.chair;
			m_sQiangGang.clear();
            
	    	if(!DealCard(m_chairCurrentPlayer))
			{
				return;
			}
            
			//摸杠需要记录入命令
			m_chairSendCmd = m_chairCurrentPlayer;
			m_currentCmd = CLIENT_WANGANG;
            
            if(m_nEndReason == REASON_NOCARD)
			{
				CCLOG("end reason no card");
				return;
			}
            
			//--m_pSite -> NotifySceneChanged();
			return;
		}
	}	
	else	// 不是抢杠拉
	{
		bool bHaveHu = false;
        
		nTempCard = m_sOutedCard.nCard;
		CardType = GetCardType(nTempCard);
		if(PAI_TYPE_INVALID == CardType)
		{
			CCLOG("错误的牌类型，发生在HandleChooseResult 不是抢杠");
			return;
		}
        
        // 一炮双响 BUG修正应该在此处⋯⋯
		if (m_nNumCmdHu)
		{
			for (i=0; i<m_nNumCmdHu; i++)
			{
				ListInsert(m_sPlayer[m_chairHu[i]].nCard[CardType], nTempCard);
				bool bHu  = JudgeHu(m_chairHu[i]);
				m_HuCurt[m_chairHu[i]].nCard = nTempCard;
				ListDelete(m_sPlayer[m_chairHu[i]].nCard[CardType], nTempCard);
                
				if(!bHu) 
				{
					CCLOG("有人诈胡 at HandleChooseResult2");
					HandleZhaHu(m_chairHu[i]);
					m_HuCurt[m_chairHu[i]].clear();
				}
				else
				{
					m_HuCurt[m_chairHu[i]].nState = CHI_PAO;
					//m_HuCurt[m_sOutedCard.nChair].nState = FANG_PAO;
                    m_nChairDianPao = m_sOutedCard.nChair;
                    
					// add by chiyan80
					CCLOG("总共有%d个赢家。现在算第%d个赢家分数， 输家为 %d ", m_nNumCmdHu, i, m_sOutedCard.nChair);
					
	            	if(ScoreOneHuCal(m_chairHu[i], m_sOutedCard.nChair))
					{
						bHaveHu = true;
						if (m_bBloodyGame)		//血战场
						{
							m_bChairHu[m_chairHu[i]] = true;
							m_nCountHu++;
							m_sPlayer[m_chairHu[i]].nState = BLOOD_HU;
						}
						//ListInsert(m_sPlayer[m_chairHu[i]].nCard[CardType], nTempCard); //整理完毕
						m_sPlayer[m_chairHu[i]].nCardTakenNow = nTempCard;
                        
					}
					else
					{
						bHaveHu = false;
						HandleZhaHu(m_chairHu[i]);
						m_HuCurt[m_chairHu[i]].clear();
					}
				}
			}
		}
		if(bHaveHu)
		{
            //m_chairSendCmd = m_chairCurrentPlayer;
			m_currentCmd = CLIENT_HU;
			if (!m_bBloodyGame)	
			{
				m_nEndReason = REASON_HU;
				HandleSetOver();
				//--m_pSite->SetSceneStatusToFree(CONDITION_STOP_LOGIC);
				return;
			}
			else		//血战场
			{
				if (m_nCountHu>=3)		//三个玩家胡牌
				{
                    ///					m_nEndReason = REASON_HU_BLOOD;
					m_nEndReason = REASON_HU;
					HandleSetOver();
					//--m_pSite->SetSceneStatusToFree(CONDITION_STOP_LOGIC);
					return;
				}
				else					//游戏继续
				{
					BYTE nNextChair = m_sOutedCard.nChair;
					do 
					{
						nNextChair = AntiClock(nNextChair);
					} while (m_bChairHu[nNextChair]);
					
					if (nNextChair == m_chairCurrentPlayer)
					{
						CCLOG("find unHu player error, chair:%d", m_chairCurrentPlayer);
						return;
					}
					
					m_sysPhase = PhaseThinkingOutCard;
					m_chairCurrentPlayer = nNextChair;
                    m_sOutedCard.clear();
					
					//start the expire timer
					//--m_pSite ->KillTimer(TIME_ID_EXPIRE);
					//--m_pSite ->SetTimer(TIME_ID_EXPIRE, TIME_EXPIRE);
					
					if(!DealCard(nNextChair))
					{
						return;
					}
                    if(m_nEndReason == REASON_NOCARD)
					{
						CCLOG("end reason no card");
						return;
					}
					//--m_pSite -> NotifySceneChanged();
					return;
				}
			}
			
		}
	    
		//没有胡， 继续处理其他命令
        
		//start the expire timer
		//--m_pSite ->KillTimer(TIME_ID_EXPIRE);
		//--m_pSite ->SetTimer(TIME_ID_EXPIRE, TIME_EXPIRE);
        
		if(m_bTianRenHu)  //判断地胡标志
		{
			m_bTianRenHu = false;
		}
        
		if (m_sGangPao.mark)
		{
			m_sGangPao.clear();
		}

		switch(m_currentCmd) 
		{
                /*///<cai
                 case CLIENT_EAT:	
                 HandleChooseEat(m_chairSendCmd, m_nEatBuf, 3);
                 memset(m_nDiHu, 255, 4);				//关闭地胡标志
                 m_bMenQing[m_chairSendCmd] = false;		//关闭门清
                 break;
                 *////cai>
            case CLIENT_PENG:
                HandleChoosePeng(m_chairSendCmd, NULL, 0);
                memset(m_nDiHu, 255, 4);				//关闭地胡标志
                m_bMenQing[m_chairSendCmd] = false;		//关闭门清
                break;
            case CLIENT_ZHIGANG:
                HandleChooseMingGangC(m_chairSendCmd, NULL, 0);
                memset(m_nDiHu, 255, 4);				//关闭地胡标志
                m_bMenQing[m_chairSendCmd] = false;		//关闭门清
                break;
            case CLIENT_CANCEL:	// 发牌给下家
            default:  //预防有人诈胡后,游戏得以继续
                ///cai
                BYTE nNextChair = m_chairCurrentPlayer;
                do 
                {
                    nNextChair = AntiClock(nNextChair);
                } while (m_bChairHu[nNextChair]);
                
                if (nNextChair == m_chairCurrentPlayer)
                {
                    CCLOG("find unHu player error, chair:%d", m_chairCurrentPlayer);
                    return;
                }
                
                m_sysPhase = PhaseThinkingOutCard;
                m_chairCurrentPlayer = nNextChair;
                
                if(!DealCard(nNextChair))
                {
                    return;
                }
                if(m_nEndReason == REASON_NOCARD)
                {
                    CCLOG("end reason no card");
                    return;
                }
                //m_pSite -> NotifySceneChanged();
                break;
		}
	}
}

/******/
/*其他*/
/******/

//玩家i相对于玩家j的位置,如(0,3),返回1(即下家)
BYTE CGameLogical::ChairTo(BYTE i, BYTE j)	
{
	return (j-i+PLAYER_COUNT)%PLAYER_COUNT;
}

//返回chair逆时针转1的玩家
BYTE CGameLogical::AntiClock(BYTE chair)
{
	return (chair+PLAYER_COUNT-1)%PLAYER_COUNT;
}

//返回牌的类型
PAI_TYPE CGameLogical::GetCardType(BYTE nCard)		
{
	if(nCard < 0 || nCard >= NUM_ALL_TYPE)
	{
		CCLOG("nCard wrong in GetCardType");
		CCLOG("nCard == %d", nCard);
		return PAI_TYPE_INVALID;
	}
	if(nCard < 9)	return WAN;
	if(nCard < 18)	return TIAO;
	if(nCard < 27)  return TONG;
	if(nCard < 31)  return FENG;
	return DRAGON;
}

bool CGameLogical::IsYaoJiu(BYTE card)
{
    PAI_TYPE CardType = GetCardType(card);
    if(PAI_TYPE_INVALID == CardType)
    {
        CCLOG("错误的牌类型，发生在IsYaoJiu");
        return false;
	}
    
    if(CardType >= WAN && CardType <= TONG)
    {
        int nCardValue = GetCardValue(card);
        if(nCardValue == 1 || nCardValue == 9)
        {
            return true;
        }
    }
    return false;
}


bool CGameLogical::IsYaoQi(BYTE card)
{
	PAI_TYPE CardType = GetCardType(card);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在IsYaoJiu");
		return false;
	}
	
	if(CardType >= WAN && CardType <= TONG)
	{
		int nCardValue = GetCardValue(card);
		if(nCardValue == 1 || nCardValue == 7)
		{
			return true;
		}
	}
	return false;
}
bool CGameLogical::Is456(BYTE card)
{
	PAI_TYPE CardType = GetCardType(card);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在Is456()");
		return false;
	}
	
	if(CardType >= WAN && CardType <= TONG)
	{
		int nCardValue = GetCardValue(card);
		if(nCardValue == 4 || nCardValue == 5 || nCardValue == 6)
		{
			return true;
		}
	}
	return false;
}
bool CGameLogical::IsZiPai(BYTE card)
{
	PAI_TYPE CardType = GetCardType(card);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在IsZiPai");
		return false;
	}
    
	if(CardType == FENG || CardType == DRAGON)
	{
		return true;
	}
	return false;
}
bool CGameLogical::IsFeng(BYTE card)
{
	PAI_TYPE CardType = GetCardType(card);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在IsFeng");
		return false;
	}
    
	if(CardType == FENG)
	{
		return true;
	}
	return false;
}

bool CGameLogical::IsDragon(BYTE card)
{
	PAI_TYPE CardType = GetCardType(card);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在IsDragon");
		return false;
	}
    
	if(CardType == DRAGON)
	{
		return true;
	}
	return false;
}


BYTE CGameLogical::GetSanYuanNum(BYTE chair)    // 得到三元的数目
{
	BYTE sum = 0;
	BYTE nCount = m_sStandCard[chair].nNum;
	if(nCount)
	{
		for(int i=0; i<nCount; i++)
		{
			bool bDragon = IsDragon(m_sStandCard[chair].nFirstCard[i]);
			if(bDragon)
			{
				sum ++;
			}
		}
	}
    
	nCount = m_sPlayer[chair].nCard[DRAGON][0];
    
	if(nCount > 2)
	{
		for(int i=1; i<nCount; i++)
		{
			if((m_sPlayer[chair].nCard[DRAGON][i] == m_sPlayer[chair].nCard[DRAGON][i+1])
               && (m_sPlayer[chair].nCard[DRAGON][i+1] == m_sPlayer[chair].nCard[DRAGON][i+2]))
			{
				sum ++;
				i += 2;
			}
            
		}
	}
    
	return sum;
}


BYTE CGameLogical::GetSiXiNum(BYTE chair, BYTE* pCardSiXi)		// 得到四喜的数目
{
	BYTE sum = 0;
	BYTE nCount = m_sStandCard[chair].nNum;
	if(nCount)
	{
		for(int i=0; i<nCount; i++)
		{
			bool bFeng = IsFeng(m_sStandCard[chair].nFirstCard[i]);
			if(bFeng)
			{
				if(NULL != pCardSiXi)
				{
					pCardSiXi[sum] = m_sStandCard[chair].nFirstCard[i];
				}
				sum ++;
			}
		}
	}
    
	nCount = m_sPlayer[chair].nCard[FENG][0];
	
	if(nCount > 2)
	{
		for(int i=1; i<nCount; i++)
		{
			if((m_sPlayer[chair].nCard[FENG][i] == m_sPlayer[chair].nCard[FENG][i+1])
               && (m_sPlayer[chair].nCard[FENG][i+1] == m_sPlayer[chair].nCard[FENG][i+2]))
			{
				if(NULL != pCardSiXi)
				{
					pCardSiXi[sum] = m_sPlayer[chair].nCard[FENG][i];
				}
				sum ++;
				i += 2;
			}
			
		}
	}
	
	return sum;
}


int CGameLogical::GetCardValue(BYTE nCard)
{
	if(nCard > 26) //字牌或者无效牌
	{
		return -1;
	}
	int value;
	value = (nCard+1)%9;
	if (value==0)
		return 9;
	return value;
}

//判断某牌是不是2, 5, 8
bool CGameLogical::Is258(BYTE card)
{
	BYTE nValue = (card+1)%9;
	if (nValue==2 || nValue==5 || nValue==8)
		return 1;
	return 0;
}


CGameLogical::CGameLogical()
{
	InitRawData();
	m_bPreventCheatRoom = FALSE;//add by mxs 
    for(int i=WAN; i<=TONG; ++i)
	{
		for (int j=1; j<=9; ++j)
		{
			CardIndex[i][j] = i*9+j-1;
			//Trace("CardIndex[%d][%d]: %d", i, j, CardIndex[i][j]);
		}
	}
}

CGameLogical::~CGameLogical()
{
    
}

/************/
/* 接口函数 */
/************/

CHECK_START_MODE CGameLogical::OnGetCheckStartMode()
{
	//CCLOG("OnGetCheckStartMode运行了！");// test用
	return START_WHEN_ALL_CHAIR_READY;
}

///cai v2.1
BOOL CGameLogical::OnGetChairScene(unsigned char nChair/*in*/,BOOL bSeenSecretData/*in*/,BOOL bNeedWholeScene/*in*/,int nUserCurrentVersion/*in*/,SCENE * pScene/*out*/,DWORD dwFlag)
{
	//CCLOG("OnGetChairScene()运行了");
	assert(pScene!=NULL);
	if (m_sysPhase == PhaseInvalid)
	{
		CCLOG("sysPhase invalid\n");
		return false;
	}
    
	// 填充pScene
	int i;
	int nCount = sizeof(int);
    
	if(bSeenSecretData)
	{
		m_bSeen = true;
	}
	else
	{
		m_bSeen = false;
	}
	
	BYTE *pBuf = (BYTE*)pScene->lpdata;
	
	pBuf[0] = m_sysPhase;											// 当前的阶段
	pBuf ++;	nCount ++;
    
    ///<cai
	if (m_sysPhase == PhaseDingQue)
	{
		pBuf[0] = m_nChairBanker;									//庄家
        pBuf ++;	nCount ++;
		
        ///cai		pBuf[0] = m_nCountChangeBanker/4;							//圈风
        ///cai		pBuf ++;	nCount ++;
		
		pBuf[0] = m_chairCurrentPlayer;								// 当前出牌者
		pBuf[1] = m_nCountAllot;									// 发到第几张牌
		pBuf += 2;	nCount += 2;
		
		for (i=0; i<4; i++)                                         // 玩家手持牌长度
		{
			pBuf[i] = m_sPlayer[i].nLen;
		}
		pBuf += 4;  nCount += 4;
		
		for (i=0; i<4; i++)											//玩家状态
		{
			pBuf[i] = m_sPlayer[i].nState;
		}
		pBuf += 4;  nCount += 4;
		
		for (i=0; i<4; i++)											//摸到的牌
		{
			pBuf[i] = m_sPlayer[i].nCardTakenNow;
		}
		pBuf += 4;  nCount += 4;
        
		pBuf[0] = m_bSeen;											//是否可见
		pBuf++;	  nCount++;
		
		if (bSeenSecretData)                                        // 私有数据
		{
			memcpy(pBuf, &m_sPlayer[nChair], sizeof(PLAYER_DATA));
			pBuf += sizeof(PLAYER_DATA); 
			nCount += sizeof(PLAYER_DATA);
		}
        
		pScene->cbSize = nCount;
		return TRUE;
	}
    ///cai>
	if (m_sysPhase == PhaseThinkingOutCard)
	{
		pBuf[0] = m_nChairBanker;									//庄家
        pBuf ++;	nCount ++;
        
        ///cai		pBuf[0] = m_nCountChangeBanker/4;							//圈风
        ///cai		pBuf ++;	nCount ++;
		
		pBuf[0] = m_chairCurrentPlayer;								// 当前出牌者
		pBuf[1] = m_nCountAllot;									// 发到第几张牌
		pBuf += 2;	nCount += 2;
        
		memcpy(pBuf, m_bChooseBuf[nChair], 4);                      //命令缓冲
		pBuf += 4;  nCount += 4;
		
		memcpy(pBuf, m_nNumTableCards, sizeof(m_nNumTableCards));   // 玩家桌面牌数量
		pBuf += sizeof(m_nNumTableCards); 
		nCount += sizeof(m_nNumTableCards);
		
		memcpy(pBuf, m_nTableCards, sizeof(m_nTableCards));			// 玩家桌面牌
		pBuf += sizeof(m_nTableCards); 
		nCount += sizeof(m_nTableCards);
		
		memcpy(pBuf, &m_sStandCard, sizeof(m_sStandCard));			// 玩家倒牌
		pBuf += sizeof(m_sStandCard); 
		nCount += sizeof(m_sStandCard);
		
		memcpy(pBuf, &m_sOutedCard, sizeof(m_sOutedCard));			//刚出的牌
		pBuf += sizeof(m_sOutedCard); 
		nCount += sizeof(m_sOutedCard);
		
		for (i=0; i<4; i++)                                         // 玩家手持牌长度
		{
			pBuf[i] = m_sPlayer[i].nLen;
		}
		pBuf += 4;  nCount += 4;
        
		for (i=0; i<4; i++)											//玩家状态
		{
			pBuf[i] = m_sPlayer[i].nState;
		}
		pBuf += 4;  nCount += 4;
        
		for (i=0; i<4; i++)											//摸到的牌
		{
			pBuf[i] = m_sPlayer[i].nCardTakenNow;
		}
		pBuf += 4;  nCount += 4;
        
		pBuf[0] = m_bSeen;											//是否可见
		pBuf++;	  nCount++;
        
		if (bSeenSecretData)                                        // 私有数据
		{
			memcpy(pBuf, &m_sPlayer[nChair], sizeof(PLAYER_DATA));
			pBuf += sizeof(PLAYER_DATA); 
			nCount += sizeof(PLAYER_DATA);
		}
		
		memcpy(pBuf, &m_sCanGang, sizeof(m_sCanGang));              //杠信息
		pBuf += sizeof(m_sCanGang); 
		nCount += sizeof(m_sCanGang);
        
		pBuf[0] = m_chairSendCmd;                                      //选中的命令
        pBuf[1] = m_currentCmd;
		pBuf += 2;
		nCount += 2;
        
		if (m_bBloodyGame)
		{
			for(i=0; i<4; i++)											//胡牌详情
			{
				memcpy(pBuf, &m_HuCurt[i], sizeof(HU_CURT));
				pBuf += sizeof(HU_CURT); 
				nCount += sizeof(HU_CURT);
			}
            
			memcpy(pBuf, m_nNumFan, 4);									// 玩家番数
			pBuf += 4;  nCount += 4;
		}
        
        if (m_currentCmd == CLIENT_HU)
		{
			memcpy(pBuf, m_wHuScore, sizeof(m_wHuScore));			//胡分数
			pBuf += sizeof(m_wHuScore);  nCount += sizeof(m_wHuScore);
            // 			for (i=0; i<PLAYER_COUNT; ++i)
            // 			{
            // 				CCLOG("HU score[%d]: %ld", i, m_wHuScore[i]);
            // 			}
            // 			
            // 			memset(m_wHuScore, 0, sizeof(m_wHuScore));
		}
		else if (m_currentCmd == CLIENT_ZHIGANG
                 || m_currentCmd == CLIENT_WANGANG
                 || m_currentCmd == CLIENT_ANGANG)
		{
			memcpy(pBuf, m_wGFXYScore, sizeof(m_wGFXYScore));			//刮风下雨分数
			pBuf += sizeof(m_wGFXYScore);  nCount += sizeof(m_wGFXYScore);
			
            // 			for (i=0; i<PLAYER_COUNT; ++i)
            // 			{
            // 				CCLOG("Gang score[%d]: %ld", i, m_wGFXYScore[i]);
            // 			}
            // 			
            // 			memset(m_wGFXYScore, 0, sizeof(m_wGFXYScore));
		}
        
		pScene->cbSize = nCount;
		return TRUE;
	}
	if (m_sysPhase == PhaseChoosing)
	{
        
		pBuf[0] = m_nChairBanker;                                   //庄家
        pBuf ++;	nCount ++;
        
		pBuf[0] = m_bSeen;                                          //是否可见
		pBuf += 1;	  nCount += 1;
		
		if (bSeenSecretData)                                        // 私有数据
		{
			memcpy(pBuf, &m_sPlayer[nChair], sizeof(PLAYER_DATA));
			pBuf += sizeof(PLAYER_DATA); 
			nCount += sizeof(PLAYER_DATA);
		}
        
		pBuf[0] = m_chairCurrentPlayer;			                    // 当前出牌者
		pBuf += 1;	  nCount += 1;
        
		memcpy(pBuf, m_bChooseBuf[nChair], 4);                      // 可供选择的命令缓冲
		pBuf += 4;  nCount += 4;
		
		memcpy(pBuf, &m_sEat, sizeof(EAT_SUIT));                    // 吃牌结构
		pBuf += sizeof(EAT_SUIT); 
		nCount += sizeof(EAT_SUIT);
		
		pBuf[0] = m_nCountAllot;									// 发到第几张牌
		pBuf ++;	nCount ++;
		
		memcpy(pBuf, m_nNumTableCards, sizeof(m_nNumTableCards));   // 玩家桌面牌数量
		pBuf += sizeof(m_nNumTableCards); 
		nCount += sizeof(m_nNumTableCards);
		
		memcpy(pBuf, m_nTableCards, sizeof(m_nTableCards));         // 玩家桌面牌
		pBuf += sizeof(m_nTableCards); 
		nCount += sizeof(m_nTableCards);
		
		memcpy(pBuf, &m_sStandCard, sizeof(m_sStandCard));          // 玩家倒牌
		pBuf += sizeof(m_sStandCard); 
		nCount += sizeof(m_sStandCard);
		
		memcpy(pBuf, &m_sOutedCard, sizeof(m_sOutedCard));          // 刚出的牌
		pBuf += sizeof(m_sOutedCard); 
		nCount += sizeof(m_sOutedCard);
		
		for (i=0; i<4; i++)                                         // 玩家手持牌长度
		{
			pBuf[i] = m_sPlayer[i].nLen;
		}
		pBuf += 4;  nCount += 4;  
		
		for (i=0; i<4; i++)											//玩家状态
		{
			pBuf[i] = m_sPlayer[i].nState;
		}
		pBuf += 4;  nCount += 4;
        
		for (i=0; i<4; i++)											//玩家摸到的牌
		{
			pBuf[i] = m_sPlayer[i].nCardTakenNow;
		}
		pBuf += 4;  nCount += 4;
        
		pScene->cbSize = nCount;
		return TRUE;
	}
	if (m_sysPhase == PhaseSetOver)
	{
		pBuf[0] = m_nEndReason;										//结束原因
		pBuf[1] = m_nCardLast;										//海底牌
		pBuf += 2;  nCount += 2;
        
		memcpy(pBuf, m_nNumCheat, 4);								// 玩家i诈胡次数
		pBuf += 4;  nCount += 4;
        
		memcpy(pBuf, m_nNumFan, 4);									// 玩家番数
		pBuf += 4;  nCount += 4;
        
		if (m_bIsCasinoGame)
		{
			memcpy(pBuf, m_wSetGold, sizeof(m_wSetGold));			//金币数
			pBuf += sizeof(m_wSetGold);  
			nCount += sizeof(m_wSetGold);
			memcpy(pBuf, m_wSetTax, sizeof(m_wSetTax));				//税收
			pBuf += sizeof(m_wSetTax);  
			nCount += sizeof(m_wSetTax);
		}
		else
		{
			memcpy(pBuf, m_wSetScore, sizeof(m_wSetScore));			//分数
			pBuf += sizeof(m_wSetScore);  nCount += sizeof(m_wSetScore);
            
			memcpy(pBuf, m_wSetLoseScore, sizeof(m_wSetLoseScore));			//分数
			pBuf += sizeof(m_wSetLoseScore);  nCount += sizeof(m_wSetLoseScore);
            
			memcpy(pBuf, m_wHuaZhuScore, sizeof(m_wHuaZhuScore));			//花猪分数
			pBuf += sizeof(m_wHuaZhuScore);  nCount += sizeof(m_wHuaZhuScore);
            
			memcpy(pBuf, m_wDaJiaoScore, sizeof(m_wDaJiaoScore));			//大叫分数
			pBuf += sizeof(m_wDaJiaoScore);  nCount += sizeof(m_wDaJiaoScore);
            
            // 			memcpy(pBuf, m_wGangScore, sizeof(m_wGangScore));			//刮风下雨分数
            // 			pBuf += sizeof(m_wGangScore);  nCount += sizeof(m_wGangScore);
            
			for(i=0; i<4; i++)
			{
				memcpy(pBuf, &m_wGangScore[i][i], sizeof(long));
				pBuf += sizeof(long); 
				nCount += sizeof(long);
			}
            
			memcpy(pBuf, m_wTotalScore, sizeof(m_wTotalScore));			//分数
			pBuf += sizeof(m_wTotalScore);  nCount += sizeof(m_wTotalScore);
            
            
			if (m_bZimoFan)
			{
				memcpy(pBuf, m_wZimoFanScore, sizeof(m_wZimoFanScore));			//自摸加底分数
				pBuf += sizeof(m_wZimoFanScore);  nCount += sizeof(m_wZimoFanScore);
			}
            
		}		
        
		for(i=0; i<4; i++)											//胡牌详情
		{
			memcpy(pBuf, &m_HuCurt[i], sizeof(HU_CURT));
			pBuf += sizeof(HU_CURT); 
			nCount += sizeof(HU_CURT);
		}
		
		
		memcpy(pBuf, m_nNumTableCards, sizeof(m_nNumTableCards));	// 玩家桌面牌数量
		pBuf += sizeof(m_nNumTableCards); 
		nCount += sizeof(m_nNumTableCards);
		
		memcpy(pBuf, m_nTableCards, sizeof(m_nTableCards));			// 玩家桌面牌
		pBuf += sizeof(m_nTableCards); 
		nCount += sizeof(m_nTableCards);
		
		memcpy(pBuf, &m_sStandCard, sizeof(m_sStandCard));			// 玩家倒牌
		pBuf += sizeof(m_sStandCard); 
		nCount += sizeof(m_sStandCard);
		
		memcpy(pBuf, &m_sOutedCard, sizeof(m_sOutedCard));			// 刚出的牌
		pBuf += sizeof(m_sOutedCard); 
		nCount += sizeof(m_sOutedCard);
		
		for (i=0; i<4; i++)											// 玩家数据
		{
			memcpy(pBuf, &m_sPlayer[i], sizeof(PLAYER_DATA));
			pBuf += sizeof(PLAYER_DATA); 
			nCount += sizeof(PLAYER_DATA);
		}
        
        
		for(i=0; i<4; i++)											//逃跑信息
		{
			pBuf[0] = m_bFlee[i];
			pBuf ++;
			nCount ++;
		}
        
        pBuf[0] = m_nCountDajiao;
		pBuf ++;
		nCount ++;
        
		if (m_bBloodyGame)
		{
			pBuf[0] = m_nCountHu;
			pBuf ++;
			nCount ++;
            
			pBuf[0] = m_nCountFlee;
			pBuf ++;
			nCount ++;
            
		}
        
		pBuf[0] = m_nCountHuaZhu;
		pBuf ++;
		nCount ++;
        
        // 		pBuf[0] = m_nCountAllot;									// 发到第几张牌
        // 		pBuf ++;	nCount ++;
        
		if(m_bIsMatchGame)											//比赛局数
		{
			pBuf[0] = m_nSetCount;
			pBuf ++;
			nCount ++;
		}
        
		pScene->cbSize = nCount;
		return TRUE;
	}	
	return TRUE;
}

void CGameLogical::OnGetServerVersionScope(VERSION_STRUCT * version/*out*/)
{
    //	CCLOG("OnGetServerVersionScope运行了！");// test用
	version->dwMainVersion = 2;
	version->dwSubVersion = 2;
	return;
}

LOOKON_OPTION CGameLogical::OnGetLookOnOption()
{
    //	CCLOG("OnGetLookOnOption运行了！");// test用
	return LO_NO_HIDDEN_DATA;
}
BOOL CGameLogical::OnInit(tagServerOption * pServerOption)
{
    //	CCLOG("OnInit()运行了");
    
	//--m_pSite = pServerFrame;	//框架指针
	m_pServerOption = pServerOption;
    
	//初始化比赛和金币使能
//	if ( pServerOption->dwMatchType > 0 )	//如果是比赛服务器，则禁止金币功能
//	{
//		m_bIsCasinoGame = false;
//		m_bIsMatchGame = true;
//	}
//	else
//	{
//    	m_bIsCasinoGame = pServerOption->bCasinoGame;
//		m_bIsMatchGame = false;
//        
//	}
    
	DWORD dwRule = //--m_pSite->GetGameOption();
	
    //--Todo
	m_bBloodyGame			= GET_GAME_MODE(dwRule);
	m_enGFXY				= GET_GFXY(dwRule);
	m_bFast					= GET_FAST(dwRule);
	m_b3Fan					= GET_MUL3(dwRule);
	m_bDingQue				= GET_BID(dwRule);
	m_bZimoFan				= GET_ZIMO(dwRule);
    
	static bool bCCLOGd = false;
	if (!bCCLOGd)
	{
		CCLOG("游戏场：%s, 快牌：%s, 三番起胡：%s, 定缺：%s, 自摸加底：%s, 刮风下雨：%s", 
              m_bBloodyGame? "血战场": "普通场",
              m_bFast?"yes":"no", 
              m_b3Fan?"yes":"no",
              m_bDingQue?"yes":"no",
              m_bZimoFan?"yes":"no",
              m_enGFXY == GFXYJiaJiaYou? "家家有": "承包制");
		bCCLOGd = true;
	}
    
	if (m_b3Fan)
	{
		m_nMinFan = 3;
	}
	else
	{
		m_nMinFan = 1;
	}
	
	return TRUE;
}

BOOL CGameLogical::OnSceneStatusToPlaying(int iNomi, int iDeNomi)			//游戏开始
{
	CCLOG("OnSceneStatusToPlaying()运行了");
	
	//初始化数据
    InitData(); 
	//发牌
    //DealAllCard();
    DealAllCardEx(iNomi, iDeNomi);
//    DealAllCardBySet(1, 16);
	//DealAllCardTest(1, 16);
	
    for (BYTE i = 0; i<200; i++) {
        CCLOG("%d--%d",i,m_nCardBuf[i]);
    }
    
    //m_nChairBanker = 0; //测试设置庄家
    
	if (m_bDingQue)
	{
		m_sysPhase = PhaseDingQue;
		//for (i = 0; i < PLAYER_COUNT; ++i)
		//{
        //m_sPlayer[i].nState = CHOOSING;
		//}
		return TRUE;
	}
    
	SceneStatusToPhasePlaying();
    
    /* 输出测试手牌
    for (int m = 0; m<PLAYER_COUNT; m++) {
        int p = 0;
        for (int n=0; n<3; n++) {
            for (int o=1; o<14; o++) {
                if (m_sPlayer[m].nCard[n][o] != 255) {
                    p++;
                    CCLOG("player--%d , type %d,%d", m,n,m_sPlayer[m].nCard[n][o]);
                }
            }
        }
        CCLOG("player--%d count %d,", m,p);
    }
    */
	return TRUE;
}

///<cai
void CGameLogical::SceneStatusToPhasePlaying()
{
	//状态设定
	m_sysPhase = PhaseThinkingOutCard;	
    m_sPlayer[m_nChairBanker].nState = THINK_OUTCARD;
    
	m_chairCurrentPlayer = m_nChairBanker;
    
    //开始expire时钟
	//--m_pSite ->KillTimer(TIME_ID_EXPIRE);
	//--m_pSite ->SetTimer(TIME_ID_EXPIRE, TIME_EXPIRE);
    
	for(int i = 0; i < PLAYER_COUNT; i ++)
	{
        /*		if(i == m_nChairBanker)
         {
         continue;
         }
         */
		InitHuList(i);
	}
    
	BYTE nTempCard = m_sPlayer[m_nChairBanker].nCardTakenNow;
	PAI_TYPE CardType = GetCardType(nTempCard);
	if(PAI_TYPE_INVALID != CardType)
	{
		ListInsert(m_sPlayer[m_nChairBanker].nCard[CardType], nTempCard);
	}
	else
	{
		CCLOG("错误牌类型，发生在OnSceneStatusToPlaying");
	}
    
	m_sCanGang.clear();
	if(FindAnGang(m_nChairBanker))
	{
		m_sPlayer[m_nChairBanker].nState = CHOOSING;
        m_bChooseBuf[m_nChairBanker][1] = true;//yaoh 测试用
	}
	ListDelete(m_sPlayer[m_nChairBanker].nCard[CardType], nTempCard);
    
	if(IsInHuList(m_nChairBanker, nTempCard))	
	{
		bool bHaveCmd = 0;
		ListInsert(m_sPlayer[m_nChairBanker].nCard[CardType], nTempCard);
		if(JudgeHu(m_nChairBanker))	
		{
			//2，加入附加胡
			//3，判断番数
			if(JudgeFan(m_nChairBanker) >= m_nMinFan) 
			{
                //				m_sPlayer[chair].bSeenOutCard = 1; 
				m_bChooseBuf[m_nChairBanker][3] = 1;		//庄家可胡牌
				bHaveCmd = 1;
				m_sPlayer[m_nChairBanker].nState = CHOOSING;
			}
		}
		m_HuCurt[m_nChairBanker].clear();
		
		ListDelete(m_sPlayer[m_nChairBanker].nCard[CardType], nTempCard);
		
		if (bHaveCmd) //若有人可以选择,进入选择状态
		{
			m_sysPhase = PhaseThinkingOutCard;
			//--m_pSite->NotifySceneChanged();
		}
	}
}
///cai>

///cai v2.1
void CGameLogical::OnSceneStatusToFree(BOOL bFled[MAX_CHAIR],int nCondition,DWORD dwReserved)
{
    
	CCLOG("OnSceneStatusToFree");
    // 	if(m_nEndReason == REASON_FLEE || m_nEndReason == REASON_HU)
    // 	{
    // 		if(m_pSite->WriteScore(m_Score,sizeof(m_Score)*PLAYER_COUNT))
    // 		{
    // 			if(IsYBGame())
    // 			{
    // 				for(int i = 0; i < PLAYER_COUNT; i++)
    // 					m_wSetGold[i] = m_Score[i].lCash;	
    // 				
    // 				// 通过判断状态来确定赢家不能为负分－－add by chiyan80 修改一炮双响赢家得负分的BUG
    // 				for(int j = 0; j < PLAYER_COUNT; j++)
    // 				{
    // 					// 假如是赢家，但是分数小于零，改之
    // 					if(m_sPlayer[j].nState == CHI_PAO && m_wSetScore[j] < 0)
    // 					{
    // 						m_wSetScore[j] = -m_wSetScore[j];
    // 						for(int k = 0; k < PLAYER_COUNT; k++)
    // 						{
    // 							if(m_sPlayer[k].nState == FANG_PAO)
    // 							{
    // 								m_wSetScore[k] -= m_wSetScore[j];
    // 							}
    // 						}
    // 					}
    // 				}
    // 			}
    // 			else
    // 			{
    // 				for(int i = 0; i < PLAYER_COUNT; i++)
    // 				{
    // 					m_wTotalScore[i] = m_Score[i].lScore;
    // ///					Trace("m_wSetScore[%d]: %ld", i, m_wSetScore[i]);
    // 					Trace("m_wTotalScore[%d]: %ld", i, m_wTotalScore[i]);
    // ///					Trace("m_Score[%d]: %ld", i, m_Score[i].lScore);
    // 				}
    // 			}
    // 			m_pSite->NotifySceneChanged();
    // 		}
    // 	}
    
//	for(int i = 0; i < PLAYER_COUNT; i++)
//	{
//		m_wTotalScore[i] = m_Score[i].lScore;
//	}
	
    //todo yaoh
//	if(m_pSite->WriteScore(m_Score,sizeof(m_Score)*PLAYER_COUNT))
//	{
//		if(IsYBGame())
//		{
//			for(int i = 0; i < PLAYER_COUNT; i++)
//				m_wSetGold[i] = m_Score[i].lCash;	
//			
//			// 通过判断状态来确定赢家不能为负分－－add by chiyan80 修改一炮双响赢家得负分的BUG
//			for(int j = 0; j < PLAYER_COUNT; j++)
//			{
//				// 假如是赢家，但是分数小于零，改之
//				if(m_sPlayer[j].nState == CHI_PAO && m_wSetScore[j] < 0)
//				{
//					m_wSetScore[j] = -m_wSetScore[j];
//					for(int k = 0; k < PLAYER_COUNT; k++)
//					{
//						if(m_sPlayer[k].nState == FANG_PAO)
//						{
//							m_wSetScore[k] -= m_wSetScore[j];
//						}
//					}
//				}
//			}
//		}
//		else
//		{
//			for(int i = 0; i < PLAYER_COUNT; i++)
//			{
//                //				m_wTotalScore[i] = m_Score[i].lScore;
//				///					Trace("m_wSetScore[%d]: %ld", i, m_wSetScore[i]);
//				Trace("m_wTotalScore[%d]: %ld -> %ld", i, m_wTotalScore[i], m_Score[i].lScore);
//				Trace("m_wHuazhuScore[%d]: %ld", i, m_wHuaZhuScore[i]);
//				Trace("m_wDajiaoScore[%d]: %ld", i, m_wDaJiaoScore[i]);
//				///					Trace("m_Score[%d]: %ld", i, m_Score[i].lScore);
//			}
//		}
//		m_pSite->NotifySceneChanged();
//	}
    
	return;
}

//处理来自客户端的命令
void CGameLogical::OnGameMessage(unsigned char nChair/*in*/, int nCmdID/*in*/, LPCVOID lpData/*in*/, int nSize/*in*/)
{
	//CCLOG("OnGameMessage()运行了");
    
//	CFrameUserInfoHelper player;
//	BOOL bAtThisTable = FALSE;
//	DWORD dwMyUserID = 0;
//    
//	//非合法玩家发的消息
//	if(!(//--m_pSite->GetUser(dwUserID, &player.pUser,bAtThisTable)) || !bAtThisTable)
//	{
//		CCLOG("OnGameOperation the %d player is not found!", dwUserID);
//		return;
//	}
//	if(player.pUser->GetUserStatus() >= STATUS_LOOKON)
//	{
//		CCLOG("踢这个人断线");
//		//--m_pSite->KickUserOff(dwUserID);	// 踢其断线
//		return;
//	}
	///<cai
	if (m_sysPhase == PhaseDingQue)
	{
		if(nCmdID == CLIENT_DINGQUE)
		{
			PAI_TYPE cardType =  (PAI_TYPE)((BYTE*)lpData)[0];
			if (m_sDingQue[nChair].bRecv)
			{
				CCLOG("chair[%d] Ding Que recved\n", nChair);
				return;
			}
			if (PAI_TYPE_INVALID == cardType)
			{
				CCLOG("chair[%d] Ding Que card type error", nChair);
				return;
			}
			HandleDingQue(nChair, cardType);
		}
		return;
	}
    ///cai>
  	if (m_sysPhase == PhaseThinkingOutCard)
	{
		if (nChair != m_chairCurrentPlayer )
		{
			CCLOG("非当前玩家发出命令， 发生在 PhaseThinkingOutCard");
			CCLOG("命令码为： %d", nCmdID);
			//错误命令，踢掉他
            //			//--m_pSite->KickUserOff(dwUserID);	// 踢其断线
			return;
		}
		switch(nCmdID) 
		{
            case CLIENT_HU:
                if(m_bChooseBuf[nChair][3] == 0)	// 诈胡
                {	
                    CCLOG("有人诈胡 at OnGameMessage PhaseThinkingOutCard");
                    HandleZhaHu(nChair);
                    return;	
                }
                HandleHuZiMo(nChair, lpData, nSize);
                ClearChooseBuf(nChair);	  //自摸不可能抢杠胡
                break;
            case CLIENT_ANGANG:
                ClearChooseBuf(nChair);
                HandleChooseAnGang(nChair, lpData, nSize);
                break;
            case CLIENT_WANGANG:
                ClearChooseBuf(nChair, false);
                HandleChooseMingGangM(nChair, lpData, nSize);
                break;
            case CLIENT_OUTCARD:
                ClearChooseBuf(nChair);
                //Todo
                HandleOutCard(nChair, lpData, nSize);
                break;
            case CLIENT_CANCEL: // 只有取消杠
                m_sPlayer[nChair].nState = THINK_OUTCARD;
                ClearChooseBuf(nChair);
                break;
            default:
                CCLOG("Invaild cmd int the state PhaseThinkingOutCard");
                CCLOG("the nCmdID == %d", nCmdID);
                return;
		}
        ((GameDesk *)UIDelegate)->OnLogicOver();
		return;
	}
	if (m_sysPhase == PhaseChoosing)
	{
		if(nChair == m_chairCurrentPlayer)
		{
			CCLOG("CurrentPlayer cant send cmd in the state PhaseChoosing\n");
			CCLOG("the nCmdID == %d", nCmdID);
			//错误命令，踢掉他
            //			//--m_pSite->KickUserOff(dwUserID);	// 踢其断线
			return;
		}
		
		switch(nCmdID)
		{
                /*///<cai
                 case CLIENT_EAT:	// 吃
                 if ((nChair != AntiClock(m_sOutedCard.nChair)) || (m_bChooseBuf[nChair][0] == 0))
                 {	
                 CCLOG("Error take place in eating\n");
                 return;
                 }
                 memcpy(m_nEatBuf, lpData,sizeof(m_nEatBuf)); //把吃的三张牌保存起来
                 ClearChooseBuf(nChair);
                 break;
                 *////cai>
            case CLIENT_PENG:
                if(m_bChooseBuf[nChair][1] == 0)
                {	CCLOG("Error take place in peng\n"); return;}
                ClearChooseBuf(nChair);
                break;
                
            case CLIENT_ZHIGANG:
                if(m_bChooseBuf[nChair][2] == 0)
                {	
                    CCLOG("Error take place in ming gang\n"); 
                    return;
                }
                ClearChooseBuf(nChair);
                break;
                
            case CLIENT_HU:
                if(m_bChooseBuf[nChair][3] == 0)	// 诈胡
                {	
                    CCLOG("有人诈胡 at OnGameMessage PhaseChoosing");
                    HandleZhaHu(nChair);
                    return;	
                }
                ClearChooseBuf(nChair, false); //可能抢杠胡
                break;
                
            case CLIENT_CANCEL:	//吃,碰,杠的放弃命令
                if(!(m_bChooseBuf[nChair][0] + m_bChooseBuf[nChair][1] + m_bChooseBuf[nChair][2] + m_bChooseBuf[nChair][3]))
                {	
                    CCLOG("Error take place in cancel\n");
                    return;
                }
                /*///<
                 if(m_bChooseBuf[nChair][3])  //如果不胡，本轮不得炮胡
                 {
                 m_bMissHu[nChair] = true;
                 
                 DWORD dwUserID = //--m_pSite->GetUserID(nChair);
                 char szMsg[512];
                 strcpy(szMsg, "\n系统： 您好！由于您错过了本次炮胡，在您打出下张牌前将禁止您的炮胡。" );
                 //--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szMsg);
                 }
                 *////>
                ClearChooseBuf(nChair, false); //有可能取消的是抢杠胡，这是需要后面判断来补张
                m_sPlayer[nChair].nState = WAITING;
                break;
                
            default: //无效命令
                CCLOG("Invaild cmd int the state PhaseThinkingOutCard");
                CCLOG("the nCmdID == %d", nCmdID);
                return;
		}
        
		if(nCmdID > m_currentCmd && nCmdID >= CLIENT_CANCEL)	//吃, 碰, 明杠竞争
		{
			m_chairSendCmd	= nChair;
			m_currentCmd	= nCmdID;
		}
		if(nCmdID == CLIENT_HU)
		{
			assert(m_nNumCmdHu < PLAYER_COUNT - 1);
			m_chairHu[m_nNumCmdHu ++] = nChair;
		}
		int sum = 0;
     	for(int i=0; i<4; i++)
		{
			if(i == m_chairCurrentPlayer || m_sPlayer[i].nState == BLOOD_HU)
			{
                continue;
			}
			sum += m_bChooseBuf[i][0] + m_bChooseBuf[i][1] + m_bChooseBuf[i][2] + m_bChooseBuf[i][3];
		}
        
		if(!sum)
		{
			HandleChooseResult();						// 处理玩家选择的结果
			m_nNumCmdHu = 0;							// 胡命令的个数
			memset(m_chairHu, -1, sizeof(m_chairHu));	// 发出胡命令的玩家
			memset(&m_sEat, 0, sizeof(m_sEat));         //抉择完以后再清空吃牌结构，为掉线
            ((GameDesk *)UIDelegate)->OnLogicOver();
		}
		return;
	}
	if (m_sysPhase == PhaseSetOver)
	{
		if(nCmdID == CLIENT_READY)
		{
			GAME_CMD_DATA cmd;
			cmd.InitData(-1,SEV_READY);
			cmd.AddData(&nChair,sizeof(nChair));
			//--m_pSite->SendGameCmd(SCO_ALL_USER,0,cmd.GetBuf(),cmd.GetDataLen());
			//--m_pSite->SetChairStatusToReady(nChair);
		}
	}
	return;
}

///<cai
void CGameLogical::HandleDingQue(BYTE nChair, BYTE nCardType)
{
	m_sDingQue[nChair].bRecv = true;
	m_sDingQue[nChair].nCardType = nCardType;
	CCLOG("OnGameMessage(), recv CLIENT_DINGQUE, chair[%d]: %d", nChair, m_sDingQue[nChair].nCardType);
	GAME_CMD_DATA cmd;
	cmd.InitData(-1,SEV_DINGQUE);
	cmd.AddData(&nChair,sizeof(nChair));
	cmd.AddData(&nCardType, sizeof(BYTE));
	//--m_pSite->SendGameCmd(SCO_ALL_USER,0,cmd.GetBuf(),cmd.GetDataLen());
    
	int i;
	for (i = 0; i<PLAYER_COUNT; ++i)
	{
		if (!m_sDingQue[i].bRecv)
		{
			break;
		}
	}
	if (PLAYER_COUNT == i)
	{
		SceneStatusToPhasePlaying();
		//--m_pSite->NotifySceneChanged();
	}
}
///cai>

void CGameLogical::OnTimer(DWORD dwEventID)
{
//	switch(dwEventID) {
//        case TIME_ID_EXPIRE:
//		{
//			//--m_pSite->KillTimer(TIME_ID_EXPIRE);
//			BYTE expirer = m_chairCurrentPlayer; 
//			for(int i=0; i<4; i++)
//			{
//				if(i == m_chairCurrentPlayer)
//				{
//					continue;
//				}
//				int sum = m_bChooseBuf[i][0] + m_bChooseBuf[i][1] + m_bChooseBuf[i][2] + m_bChooseBuf[i][3];
//				if(sum)
//				{
//					expirer = i;
//					break;
//				}
//			}
//            //  someone flee
//			if((m_sysPhase==PhaseThinkingOutCard||m_sysPhase==PhaseChoosing) 
//               && (//--m_pSite->GetSceneStatus() == SCENE_STATUS_PLAYING))
//			{
//				m_bFlee[expirer] = true;
//				
//				//--m_pSite->NotifyChairFlee(expirer);
//				m_nEndReason = REASON_FLEE;
//				HandleSetOver();
//				//--m_pSite->SetSceneStatusToFree(CONDITION_STOP_PLAYER_LEAVE, TRUE);
//				
//				return;
//			}
//            
//            break;
//		}
//            
//        default:
//            break;
//	}
	return;
}
void CGameLogical::OnTableStatusToPlaying()
{
    ///cai	m_nChairBanker = //--m_pSite->GetTableOP();
    ///cai	掷骰定庄家
	//--m_pSite->SRand(GetTickCount());
	//m_nChairBanker = //--m_pSite->Rand()%PLAYER_COUNT;
    
    m_nChairBanker = rand()%PLAYER_COUNT;
    //Todo
    //m_nChairBanker = 1;
    
	return;
}

BOOL CGameLogical::OnGetOldScoreBuffer(LPSTR lpszBuffer,int& nSize)
{
    //	CCLOG("OnGetOldScoreBuffer运行了！");// test用
	return FALSE;
}


void CGameLogical::OnUserEnter(int nChair,DWORD dwUserID,BOOL bIsPlayer)
{
//    //发送是否比赛信息
//	SendOneByteMsg(SEV_ISMATCH, m_bIsMatchGame, dwUserID);
//	//发送起胡番数
//	SendOneByteMsg(SEV_MIN_FAN, m_nMinFan, dwUserID);
//    
//	DWORD dwRule = m_pSite->GetGameOption();
//	BYTE nRule = LOBYTE(LOWORD(dwRule));
//	SendOneByteMsg(SEV_RULE, nRule, dwUserID);
//    
//	//发送金币信息
//    
//	if (m_bPreventCheatRoom)	//发是否是防作弊房间		//add by mxs			
//	{
//		GAME_CMD_DATA data;									//add by mxs
//		data.cChair = nChair;								//add by mxs
//		data.cCmdID = SEV_PREVENT_CHEAT;					//add by mxs
//		m_pSite->SendGameCmd(SCO_SINGLE_PLAYER, dwUserID, data.GetBuf(),data.GetDataLen());	//add by mxs
//	}
//    
//	GAME_CMD_DATA cmdCasinoInfo;
//	cmdCasinoInfo.InitData(-1, SEV_CASINOINFO);
//	BYTE nBChair = (BYTE)nChair;
//	cmdCasinoInfo.AddData(&nBChair, sizeof(nBChair));
//	cmdCasinoInfo.AddData(&m_bIsCasinoGame, sizeof(m_bIsCasinoGame));
//	cmdCasinoInfo.AddData(&m_bSupportNego, sizeof(m_bSupportNego));
//	cmdCasinoInfo.AddData(&m_nAnte, sizeof(m_nAnte));
//	int nTemp = MIN_GOLD_MUTIPLE;
//	cmdCasinoInfo.AddData(&nTemp, sizeof(nTemp));
//	m_pSite->SendGameCmd(SCO_SINGLE_PLAYER, dwUserID, cmdCasinoInfo.GetBuf(), cmdCasinoInfo.GetDataLen());
//    
//	if (m_bPreventCheatRoom)	//add by mxs
//	{							//add by mxs
//		InformCoinChairToChair(nChair,nChair);//add by mxs 把我的金币发给我
//	}							//add by mxs
//	else 
//	{	
//		if(bIsPlayer)
//		{
//			for(int i = 0; i < PLAYER_COUNT; i++)
//			{
//				InformCoinChairToChair(nChair, i);
//				if(i != nChair)
//				{
//					InformCoinChairToID(i, dwUserID);
//				}
//			}
//		}
//		else	//旁观者只把别人的金币通知给自己
//		{
//			for(int i=0; i<PLAYER_COUNT; i++)
//			{
//				InformCoinChairToID(i, dwUserID);
//			}
//		}
//	}
//	
//	//比赛信息
//	if ( IsMatchServer() )
//	{
//		SendOneByteMsg(SEV_ISMATCH_OVER, false, dwUserID);	//可以坐进来的话，一定是要开始比赛了或比赛正在进行，不要送m_bIsMatchOver，因为它这时可能为true，但比赛确实要开始了
//	}
//	else
//	{
//		SendOneByteMsg(SEV_ISMATCH_OVER, true, dwUserID);
//	}
//    
//	//有番起胡提示
//	if(m_nMinFan>1)
//	{
//		char szZhahu[512];
//		sprintf(szZhahu,"系统提示：您好！本服务器为%d番起胡，如果您的牌型番数不足，您将无法胡牌。", m_nMinFan); 
//		m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szZhahu);
//	}
//	char szPrompt[512];
//	//strcpy(szPrompt,"系统提示：您好！如果要开启或关闭音效，请点击上面的游戏设置按钮。"); 
//	strcpy(szPrompt,"\n0620v3\n"); 
//	m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szPrompt);
    
	return;
}
void CGameLogical::OnPlayerOffline(int nChair,DWORD dwUserID)
{
    //	CCLOG("OnPlayerOffline运行了！");// test用
	return;
}

void CGameLogical::OnPlayerReplay(int nChair,DWORD dwUserID)
{
//    //	CCLOG("OnPlayerReplay运行了！");// test用
//    
//	//发送是否比赛信息
//	SendOneByteMsg(SEV_ISMATCH, m_bIsMatchGame, dwUserID);
//	//发送起胡番数
//	SendOneByteMsg(SEV_MIN_FAN, m_nMinFan, dwUserID);
//	//发送金币信息
//	GAME_CMD_DATA cmdCasinoInfo;
//	cmdCasinoInfo.InitData(-1, SEV_CASINOINFO);
//	BYTE nBChair = (BYTE)nChair;
//	cmdCasinoInfo.AddData(&nBChair, sizeof(nBChair));
//	cmdCasinoInfo.AddData(&m_bIsCasinoGame, sizeof(m_bIsCasinoGame));
//	cmdCasinoInfo.AddData(&m_bSupportNego, sizeof(m_bSupportNego));
//	cmdCasinoInfo.AddData(&m_nAnte, sizeof(m_nAnte));
//	int nTemp = MIN_GOLD_MUTIPLE;
//	cmdCasinoInfo.AddData(&nTemp, sizeof(nTemp));
//	//--m_pSite->SendGameCmd(SCO_SINGLE_PLAYER, dwUserID, cmdCasinoInfo.GetBuf(), cmdCasinoInfo.GetDataLen());
//	
//    //	for(int i = 0; i < PLAYER_COUNT; i++)
//    //	{
//    //		InforCoinNum(nChair, i);
//    //		if(i != nChair)
//    //		{
//    //			InforCoinNum(i, nChair);
//    //		}
//    //	}
//    ///////////////////////////////////////////////////////////
//    
//	if (m_bPreventCheatRoom)	//add by mxs
//	{							//add by mxs
//		InformCoinChairToChair(nChair,nChair);//add by mxs 把我的金币发给我
//	}							//add by mxs
//	else
//	{
//		for(int i = 0; i < PLAYER_COUNT; i++)
//		{
//			InformCoinChairToChair(nChair, i);
//			if(i != nChair)
//			{
//				InformCoinChairToID(i, dwUserID);
//			}
//		}
//	}
//    
//    
//    ///////////////////////////////////////////////////////////
//	
//	//比赛信息
//	if ( IsMatchServer() )
//	{
//		SendOneByteMsg(SEV_ISMATCH_OVER, false, dwUserID);	//可以坐进来的话，一定是要开始比赛了或比赛正在进行，不要送m_bIsMatchOver，因为它这时可能为true，但比赛确实要开始了
//	}
//	else
//	{
//		SendOneByteMsg(SEV_ISMATCH_OVER, true, dwUserID);
//	}
//	
//	//有番起胡提示
//	if(m_nMinFan>1)
//	{
//		char szZhahu[512];
//		sprintf(szZhahu,"系统提示：您好！本服务器为%d番起胡，如果您的牌型番数不足，您将无法胡牌。", m_nMinFan); 
//		//--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szZhahu);
//	}
//    
//	char szPrompt[512];
//	strcpy(szPrompt,"系统提示：您好！如果要开启或关闭音效，请点击上面的游戏设置按钮。"); 
//	//--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szPrompt);
	
	return;
}
bool CGameLogical::OnPlayerReady(int nChair,DWORD dwUserID)
{
	return true;
}

void CGameLogical::OnSentence(int nWinIndex,DWORD dwReserved)
{
	return;
}
BOOL CGameLogical::OnIsCasinoGame(DWORD& dwMinCashNeeded)
{
	return m_bIsCasinoGame;
}


BOOL CGameLogical::OnIsOneScoreInOneSet()
{
    //	CCLOG("OnIsOneScoreInOneSet运行了！");// test用
	return FALSE;
}


void CGameLogical::Release()
{
	return;
}

BOOL CGameLogical::OnIsSupportGameConcept()
{
    //	CCLOG("OnIsSupportGameConcept运行了！");// test用
	return FALSE;
}

BOOL CGameLogical::OnGameStatusToFree()
{
    //	CCLOG("OnGameStatusToFree运行了！");// test用
	return FALSE;
}

BOOL CGameLogical::OnGameStatusToPlaying()
{
    //	CCLOG("OnGameStatusToPlaying运行了！");// test用
    
	return FALSE;
}

//int CGameLogical::OnGetClientScoreType()
//{
//	return enClientType_Majiang;
//}

BOOL CGameLogical::OnIsSupportNegotiateDismiss(DWORD& dwLeastAdvocater/*out*/)
{
	return FALSE;
}

BOOL CGameLogical::OnGetMatchSetContext(LPSTR lpszBuffer/*out*/,int& nDataLen/*in/out*/)
{
	nDataLen = 0;
	return true;
}
int	CGameLogical::OnGetTableOpChair()
{
	return 0;
}

//BOOL CGameLogical::OnGetDefaultGameRule(LPVOID lpGameRule/*out*/,UINT& nDataLen/*in/out*/)
//{
//	m_nAnte = m_nDefAnte;
//	memcpy(lpGameRule, &m_nAnte, 4);
//	nDataLen = 4;
//    //	CCLOG("OnGetDefaultGameRule运行，lpGameRule == %d", m_nAnte);
//	return TRUE;
//}
//
//BOOL CGameLogical::OnGetGameRule(LPVOID lpGameRule/*out*/,UINT& nDataLen/*in/out*/)
//{
//	memcpy(lpGameRule, &m_nAnte, 4);
//	nDataLen = 4;
//	return TRUE;
//}
//
//void CGameLogical::OnGameRuleChanged(LPCVOID lpGameRule,UINT nLen)
//{
//	if(m_bSupportNego == 0)
//	{
//		return;
//	}
//	UINT nPer = ((UINT*)lpGameRule)[0];
//	m_nAnte = nPer;
//    
//	DWORD dwUid = //--m_pSite->GetUserID(0); 
//	Score_Struct score;
//	if( INVALID_FRAME_USER_ID != dwUid)
//	{
//		//--m_pSite->GetUserScore(dwUid,&score);
//	}
//	if(score.lCash < m_nMinGold)
//	{
//		m_nAnte = m_nDefAnte;
//	}
//    
//	m_nMinGold = m_nAnte * MIN_GOLD_MUTIPLE ;
//	//--m_pSite->NotifyMinGoldChanged();
//	return;
//}

void CGameLogical::OnSetGameRuleCanceled()
{
	m_nMinGold = m_nAnte * MIN_GOLD_MUTIPLE ;
	return;
}


BOOL CGameLogical::OnGetCreateClientMethod(DWORD& dwMethodID,LPSTR lpszFileName)
{
	return FALSE;
}

BOOL CGameLogical::OnPlayerLookonStateChanged(int nChair,DWORD dwDestID,BOOL bEnable)
{
	return FALSE;
}

void CGameLogical::ScoreFleeMatchCal(Score_Struct scores[PLAYER_COUNT])
{
    int i;
	for (i=0; i< PLAYER_COUNT; i++)
	{
		scores[i].lScore = 0; 
	}
    
	for ( i=0; i< PLAYER_COUNT; i++)
	{
		if ( m_bFlee[i] )
		{
			scores[i].lScore -=  MATCH_FLEE_BASE_PUNISH_SCORE;
			scores[i].lFleeCount = 1;
			scores[(i+1)%4].lScore += MATCH_FLEE_BASE_PUNISH_SCORE/(PLAYER_COUNT-1);
			scores[(i+2)%4].lScore += MATCH_FLEE_BASE_PUNISH_SCORE/(PLAYER_COUNT-1);
			scores[(i+3)%4].lScore += MATCH_FLEE_BASE_PUNISH_SCORE/(PLAYER_COUNT-1);
		}
        
		scores[i].lSetCount = 1;
	}
	for (i=0; i< PLAYER_COUNT; i++)
	{
		m_wSetScore[i] = scores[i].lScore; //记录在案，供客户端显示
	}
    
}

bool CGameLogical::IsTooManyFlee(Score_Struct *pScore[PLAYER_COUNT],int nSetCount,long lFleeCounts[PLAYER_COUNT])
{
	int i, j;
	
	bool bTooManyFlee = false;
	
	for (i=0; i<PLAYER_COUNT; i++)
	{
		lFleeCounts[i] = 0;
		for (j=0; j<nSetCount; j++)
		{
			lFleeCounts[i] += pScore[i][j].lFleeCount;
		}
		if (lFleeCounts[i] >= MAX_MATCH_FLEE_COUNT)
			bTooManyFlee = true;
	}
	
	return bTooManyFlee;
}

///cai v2.1
void CGameLogical::CalcFleeScore()
{
    //	Score_Struct score[PLAYER_COUNT];
	for(int i=0; i<PLAYER_COUNT; i++)
	{
		//m_Score[i].clear();
		memset(&m_Score[i],0,sizeof(Score_Struct));
	}
    
//	if ( m_bIsCasinoGame )	//from 旧金币代码：HRESULT IGameLogicalImpl::Stop(UINT uflags)
//	{
//		if (!ScoreFleeYBCal(m_Score) )
//			return ;
//	}
//	else	
//	{
////		if ( IsMatchServer() )
////		{
////            
////			ScoreFleeMatchCal(m_Score);
////		}
////		else
////		{
//        if (!m_bBloodyGame)
//        {
//            ScoreFleeNormalCal();
//        }
//        else
//        {
//            ScoreFleeBloodCal();
//        }
////		}
//	}
    
    if (!m_bBloodyGame)
    {
        ScoreFleeNormalCal();
    }
    else
    {
        ScoreFleeBloodCal();
    }
    
    //	//--m_pSite->WriteScore(m_Score,sizeof(m_Score)*PLAYER_COUNT);
	/////////////////////////////////////////////////////////////////////////////////
    //	AddSetScoreToPlayerScore();
}

///paddy//  void CGameLogical::ScoreNormalCalAndWrite ()
void CGameLogical::CalcHuScore()
{
	int cash = 0;
    //	Score_Struct score[PLAYER_COUNT];
    int i;
	for(i=0; i<PLAYER_COUNT; i++)
	{
		//m_Score[i].clear();
		memset(&m_Score[i],0,sizeof(Score_Struct));
	}
	for(i=0; i<PLAYER_COUNT; i++)
	{
		m_Score[i].lScore = m_wSetScore[i] + m_wSetLoseScore[i] + m_wZimoFanScore[i] + m_wGangScore[i][i];
		m_Score[i].lSetCount = 1;
		if (m_Score[i].lScore>0)
		{
			m_Score[i].lWinCount = 1;
		}
		else if (m_Score[i].lScore<0)
		{
			m_Score[i].lLoseCount = 1;
		}
		else
		{
			m_Score[i].lDrawCount = 1;
		}
	}
    
    
    // 一炮双响问题应该处在此处⋯⋯ add by chiyan80
    
//	// 金币游戏
//	if (m_bIsCasinoGame)
//	{
//        /*		// 通过判断状态来确定赢家不能为负分－－add by chiyan80 修改一炮双响赢家得负分的BUG
//         for(int j = 0; j < PLAYER_COUNT; j++)
//         {
//         // 假如是赢家，但是分数小于零，改之
//         if(m_sPlayer[j].nState == CHI_PAO && m_Score[j].lScore < 0)
//         m_Score[j].lScore = -m_Score[j].lScore;
//         }
//         */		
//		if(!CalSetCoinScore())
//		{
//			return;
//		}
//		
//		// 通过判断状态来确定赢家不能为负分－－add by chiyan80 修改一炮双响赢家得负分的BUG
//		for(int j = 0; j < PLAYER_COUNT; j++)
//		{
//			// 假如是赢家，但是分数小于零，改之
//			if(m_sPlayer[j].nState == CHI_PAO && m_wSetScore[j] < 0)
//				m_wSetScore[j] = -m_wSetScore[j];
//		}
//        
//		for(int i=0; i<PLAYER_COUNT; i++)
//		{
//			cash = m_wSetScore[i];
//#ifndef ZERO_TAX
//			if (cash>100)							//100起税
//			{
//				m_Score[i].lTax = cash/50;			//税率2％
//				m_Score[i].lCash = cash - m_Score[i].lTax;
//			}
//			else
//#endif
//			{
//				m_Score[i].lCash = cash;
//			}
//			
//			m_wSetGold[i] = m_Score[i].lCash;	
//			m_wSetTax[i]  = m_Score[i].lTax;
//			
//			// add by chiyan80
//			CCLOG("%d 号玩家得分：%d", i, m_wSetGold[i]);
//		}
//	}	
}

/// cai v2.1
void CGameLogical::ScoreFleeNormalCal()
{
	BYTE nFleeChair = 255;
	int i;
	
	for(i=0; i<PLAYER_COUNT; ++i)
	{
		m_nDajiaoFan[i] = 0;
		
		if (m_bFlee[i])
		{
			nFleeChair = i;
            if (m_nCountAllot > CARD_NUM-4)
			{
				m_sPlayer[i].nState = DAJIAO;
				m_nCountDajiao++;
			}
			continue;
		}
        
        m_HuCurt[i].nState = NOTHING;
		
		if (m_nCountAllot > CARD_NUM-4)	//查大叫
		{
			m_nDajiaoFan[i] = JudgeDajiao(i);
			if (m_nDajiaoFan[i]>0)
			{
                ///				m_sPlayer[i].nState = DAJIAO_HU;
				m_HuCurt[i].nState = HU_DA_JIAO;
				m_nNumFan[i] = m_nDajiaoFan[i];
			}
            else
			{
				m_HuCurt[i].nState = NOTHING;
				m_nCountDajiao++;
			}
		}
	}
	
	if (nFleeChair == 255)
	{
		CCLOG("flee chair error");
		return;
	}
	
	for(i=0; i<4; i++)
	{
        ///		if(!m_bFlee[i] && m_sPlayer[i].nState==DAJIAO_HU)
		if(!m_bFlee[i])
		{
			if (m_HuCurt[i].nState == HU_DA_JIAO)
			{
				//m_wDaJiaoScore[i] += SCORE_BASE*m_nDajiaoFan[i];		
				//m_wDaJiaoScore[nFleeChair] -= SCORE_BASE*m_nDajiaoFan[i];
                
				long lScore = SCORE_BASE*(1<<(m_nDajiaoFan[i]-1));
				m_wDaJiaoScore[i] += lScore;		
				m_wDaJiaoScore[nFleeChair] -= lScore;
			}
            
			if (m_wGangScore[nFleeChair][i] > 0)		//退回刮风下雨分
			{
				m_wGangScore[nFleeChair][nFleeChair] -= m_wGangScore[nFleeChair][i];
				m_wGangScore[i][i] += m_wGangScore[nFleeChair][i];
                
				m_wGangScore[nFleeChair][i] = 0;
			}
            
			m_Score[i].lScore = m_wDaJiaoScore[i] + m_wSetScore[i] + m_wSetLoseScore[i]
            + m_wGangScore[i][i] + m_wHuaZhuScore[i];
		}
	}
	
	m_Score[nFleeChair].lScore = m_wDaJiaoScore[nFleeChair] - SCORE_FLEE_MUL*SCORE_BASE*3
    + m_wSetScore[nFleeChair] + m_wSetLoseScore[nFleeChair] + m_wGangScore[nFleeChair][nFleeChair] + m_wHuaZhuScore[nFleeChair];
	m_Score[nFleeChair].lSetCount = 1;
	m_Score[nFleeChair].lFleeCount = 1;
    
	m_Score[nFleeChair].lLoseCount = 1;
    
    /*
     for(int i=0; i<4; i++)
     {
     if(m_bFlee[i])
     {
     m_wSetScore[i] -= SCORE_FLEE*SCORE_BASE;
     score[i].lFleeCount = 1;
     score[i].lSetCount = 1;
     }
     score[i].lScore = m_wSetScore[i];
     }
     */
    
}

bool CGameLogical::ScoreFleeYBCal(Score_Struct score[PLAYER_COUNT])
{
    
	for(int i = 0; i < PLAYER_COUNT; i++)
	{
		if(m_bFlee[i])
		{
			m_wSetScore[i] -= (SCORE_FLEE*SCORE_BASE);
		}
		else
		{
			m_wSetScore[i] += ((SCORE_FLEE*SCORE_BASE)/3);	
		}
        //		score[i].lScore = m_wSetScore[i];
		score[i].lSetCount = 1;
        
		int cash = (m_wSetScore[i]/SCORE_BASE)*m_nAnte;
#ifndef ZERO_TAX
		if (cash>100)						//100起税
		{
			score[i].lTax = cash/50;		//税率2％
			score[i].lCash = cash - score[i].lTax;
		}
		else
#endif
		{
			score[i].lCash = cash;
		}
		m_wSetGold[i] = score[i].lCash;	
		m_wSetTax[i] = score[i].lTax;	
	}
    
//	if(!CalSetCoinScore()) //检查是否有足够金币
//	{
//		return false ;	
//	}
    
	return true;
}

void CGameLogical::SendOneByteMsg(char cmd ,BYTE data,DWORD dwUserID )
{
	GAME_CMD_DATA buf;
	buf.InitData(-1, cmd);
	buf.AddData(&data,1);
	
	if (INVALID_FRAME_USER_ID == dwUserID)
	{
		//--m_pSite->SendGameCmd(SCO_ALL_PLAYER,0,buf.GetBuf(), buf.GetDataLen());
	}
	else
	{
		//--m_pSite->SendGameCmd(SCO_SINGLE_PLAYER,dwUserID,buf.GetBuf(), buf.GetDataLen());
	}
	return;
}

void CGameLogical::HandleZhaHu(BYTE nChair)
{
	m_wSetScore[nChair] -= SCORE_ZHA_HU;
	if(m_bIsCasinoGame)
	{
		for(int i=0; i<4; i++)
		{
			if(i==nChair)
			{
				continue;
			}
			m_wSetScore[nChair] += SCORE_ZHA_HU/3;
		}
	}
	m_nNumCheat[nChair]++;
	GAME_CMD_DATA cmd;
	cmd.InitData(-1, SEV_ZHA_HU);
	cmd.AddData(&nChair, 1);
	//DWORD dwUserID = //--m_pSite->GetUserID(nChair);
	//--m_pSite->SendGameCmd(SCO_SINGLE_PLAYER, dwUserID, cmd.GetBuf(), cmd.GetDataLen());
    
    /* Todo
	IFrameUserInfo *pPlayer = NULL;
	//--m_pSite->GetPlayerByChair(nChair,&pPlayer);
	char szName[64];
	memset(szName, 0, 64);
	if (pPlayer && pPlayer->GetUserName())
	{
		lstrcpyn(szName, pPlayer->GetUserName(), 64);
	}
	if (pPlayer)
	{
		pPlayer->Release();
	}
     */
	char szZhahu[512];
	//sprintf(szZhahu,"系统：玩家 %s 因诈胡被扣除%d分，诈胡原因可能为番数不足.", szName, SCORE_ZHA_HU); 
	//--m_pSite->SendSysMsgToClient(SCO_ALL_USER,0,szZhahu);
    
	m_bChooseBuf[nChair][3] = 0; //clear the hu signal
}

/// cai v2.1
void CGameLogical::InitData()
{
	int i,j,k;
    
	m_bIsMatchOver = false; //比赛开始
	m_bSeen = false;
	m_bTianRenHu = true;
	m_bHaveGang = false;
    
	m_chairCurrentPlayer = 255;
    m_nChairDianPao = 255;
	m_nCountAllot = 0;			//还没发牌
	m_nNumCmdHu = 0;			// 胡命令的个数
	m_chairSendCmd = 255;			// 当前发命令的玩家
	m_currentCmd = 0;			// 当前的命令
	m_nEndReason = 0;
	m_nCardLast = 255;
	m_nSetCount = 0;
    
    m_bMaxFan = false;
	
	//初始化数据区
	memset(m_nNumCheat, 0, sizeof(m_nNumCheat));
	memset(m_nNumTableCards, 0, sizeof(m_nNumTableCards));
	memset(m_nTableCards, 0, sizeof(m_nTableCards));
	memset(m_wSetScore, 0, sizeof(m_wSetScore));
	memset(m_wSetGold, 0, sizeof(m_wSetGold));
	memset(m_wSetTax, 0, sizeof(m_wSetTax));
	memset(m_nHuTypeCurt, 0, sizeof(m_nHuTypeCurt));
	memset(m_nHuTypeDetailed, 0, sizeof(m_nHuTypeDetailed));
	memset(m_nHuList, 0, sizeof(m_nHuList));
	memset(&m_sEat, 0, sizeof(m_sEat));
	memset(m_nHuGiveUp, 0, sizeof(m_nHuGiveUp));
	memset(m_nCardBuf, 0, sizeof(m_nCardBuf));
	memset(m_bChooseBuf, 0, sizeof(m_bChooseBuf));
	memset(m_nJiang, -1, sizeof(m_nJiang));
	memset(m_chairHu, -1, sizeof(m_chairHu));		// 发出胡命令的玩家
	memset(m_bFlee, 0, sizeof(m_bFlee));		//逃跑
	memset(m_nNumFan, 0, sizeof(m_nNumFan));		//番数
	memset(m_nDajiaoFan, 0, sizeof(m_nDajiaoFan));		//番数
    ///	memset(m_bMissHu, 0, 4);
	memset(m_nDiHu, 0, 4);
	memset(m_bMenQing, 1, 4);
	memset(m_szTALevel, 0, sizeof(m_szTALevel));
    
	memset(m_wZimoFanScore, 0, sizeof(m_wZimoFanScore));
	memset(m_wGangScore, 0, sizeof(m_wGangScore));
	memset(m_wHuaZhuScore, 0, sizeof(m_wHuaZhuScore));
	memset(m_wDaJiaoScore, 0, sizeof(m_wDaJiaoScore));
	memset(m_wTotalScore, 0, sizeof(m_wTotalScore));
	memset(m_wSetLoseScore, 0, sizeof(m_wSetLoseScore));
    
    memset(m_wHuScore, 0, sizeof(m_wHuScore));
	memset(m_wGFXYScore, 0, sizeof(m_wGFXYScore));
    
	sprintf(m_szTALevel, "默认");
	
	m_sCanGang.clear();
	m_sOutedCard.clear();
	m_sQiangGang.clear();
    
    m_sGangPao.clear();
    
	for (i=0; i<4; i++)
	{
		m_sStandCard[i].clear();
	}
    
	for (i=0; i<4; i++)
	{
		m_sPlayer[i].clear();
		m_sDingQue[i].Clear();
	}
    
	for(i=0; i<4; i++)
	{
		m_HuCurt[i].clear();
	}
	//初始化牌缓冲区
	for(j=0, k=0; k<4; k++)
	{
		for(i=0; i<NUM_ALL_TYPE; i++)
		{
			m_nCardBuf[j++] = i;
		}
	}
	//最后四张剩余
	m_nCardBuf[136] = 255;
	m_nCardBuf[137] = 255;
	m_nCardBuf[138] = 255;
	m_nCardBuf[139] = 255;
    
	///cai
	for (i = 0; i<PLAYER_COUNT; ++i)
	{
		m_bChairHu[i] = false;
		///cai
		m_nGen[i] = 0;
	}
    
    m_nCountHu = 0;
	m_nCountFlee = 0;
	m_nCountHuaZhu = 0;
	m_nCountDajiao = 0;
}

///cai v1.1
void CGameLogical::InitRawData()
{
    // 	for(int i=0; i<4; i++)
    // 	{
    // 		m_dwUserID[i][0] = INVALID_FRAME_USER_ID;
    // 		m_dwUserID[i][1] = 0;
    // 		for(int j=2; j<10; j++)
    // 		{
    // 			m_dwUserID[i][j] = INVALID_FRAME_USER_ID;
    // 		}
    // 	}	
    
    ///cai	m_nCountChangeBanker = 0;
	
	//调试函数数组
	m_iTAFuncCount = 0;
	for(int i=0; i<MAX_TA_BULID_FUNC; i++)
	{
		BuildTA[i] = 0;
	}
    
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAQingYiSe;			//1 清一色
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAYaoJiu;			//2 幺九
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAQiDui;				//3 七对
    
    BuildTA[m_iTAFuncCount++] = &CGameLogical::TAQingYiSe;			//1 清一色
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAYaoJiu;			//2 幺九
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAQiDui;				//3 七对
    
    BuildTA[m_iTAFuncCount++] = &CGameLogical::TAQingYiSe;			//1 清一色
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAYaoJiu;			//2 幺九
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAQiDui;				//3 七对
	
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAQingPeng;			//4 清碰
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAJiangPeng;			//5 将碰
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TALongQiDui;			//6 龙七对
    
    BuildTA[m_iTAFuncCount++] = &CGameLogical::TAQingPeng;			//4 清碰
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAJiangPeng;			//5 将碰
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TALongQiDui;			//6 龙七对
	
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAQingQiDui;			//7 清七对
	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAQingYaJiu;			//8 清幺九
    
    //	BuildTA[m_iTAFuncCount++] = &CGameLogical::TAQingLongQiDui;			//test    
}

/*///<cai
 void CGameLogical::DealAllCard()
 {
 const int nTransferCount = 300;   //发牌随机时转换的次数
 int i=0, j=0, k= 0;
 BYTE temp = 255, nTempCard = 255;
 
 //洗牌
 //--m_pSite->SRand(GetTickCount());
 for(i = 0; i < nTransferCount; i ++)
 {
 j = //--m_pSite->Rand() % CARD_NUM;
 k = //--m_pSite->Rand() % CARD_NUM;
 temp = m_nCardBuf[j];
 m_nCardBuf[j] = m_nCardBuf[k];
 m_nCardBuf[k] = temp;
 }
 
 //给每人发13张牌
 for(i=0; i<PLAYER_COUNT; i++)
 {
 for(k=0; k<HOLD_CARD_NUM; k++)
 {
 nTempCard = m_nCardBuf[m_nCountAllot++];	//从牌缓冲区里那张牌
 PAI_TYPE CardType = GetCardType(nTempCard);
 if(PAI_TYPE_INVALID != CardType)
 {
 m_sPlayer[i].nCard[CardType][0] ++;
 m_sPlayer[i].nCard[CardType][m_sPlayer[i].nCard[CardType][0]] = nTempCard;
 }
 else
 {
 CCLOG("发牌错误，出现未定义类型的牌");
 }
 }
 m_sPlayer[i].nLen = 13;
 
 //对玩家i手中的牌进行排序
 for(k=WAN; k<=DRAGON; k++)
 {
 ListSort(&m_sPlayer[i].nCard[k][1], m_sPlayer[i].nCard[k][0]);
 }
 }
 
 //给庄家发第14张牌
 m_sPlayer[m_nChairBanker].nCardTakenNow = m_nCardBuf[m_nCountAllot++];	
 
 }
 *////cai>

///cai v2.1
bool CGameLogical::ScoreOneHuCal(BYTE nWinChair, BYTE nLostChair)
{
	if(!IsValidChair(nWinChair))
	{
		CCLOG("错误椅子号");
		return false;
	}
    
    if (m_HuCurt[nWinChair].nState == CHI_PAO && m_sGangPao.mark && m_sGangPao.chair != nWinChair)
	{
		m_HuCurt[nWinChair].AddHU(GANGPAO);
	}
    
	BYTE nFanSum = JudgeFan(nWinChair);
	if(nFanSum < m_nMinFan)
	{
		m_HuCurt[nWinChair].clear();
		return false;
	}
	m_nNumFan[nWinChair] = nFanSum;
    
	int nPerWinScore = 1;
	for(int i=1; i<nFanSum; i++)
	{
		nPerWinScore *= 2;
	}
	long wWinScore = 0;
    
    memset(m_wHuScore, 0, sizeof(m_wHuScore));
    
	if(m_HuCurt[nWinChair].nState == ZI_MO)
	{
		BYTE nChairBaoPai = 255;
		//包牌情况, 只有自摸时处理包牌
		if(m_sQiangGang.mark)						//抢杠包牌
		{
			if(m_sQiangGang.chair != nWinChair)
			{
				nChairBaoPai = m_sQiangGang.chair;
                ///				m_HuCurt[nChairBaoPai].nState = BAOPAI_QIANGGANG;
                ///				m_HuCurt[nChairBaoPai].AddLose(BAOPAI_QIANGGANG);
				
				for (int i=0; i<PLAYER_COUNT; ++i)
				{
					if (i == nChairBaoPai)
					{
						continue;
					}
					
					if (m_sPlayer[i].nState!=BLOOD_HU)
					{
						m_wGangScore[nChairBaoPai][nChairBaoPai] -= SCORE_BASE;
						m_wGangScore[nWinChair][nWinChair] += SCORE_BASE;
                        
						m_wGangScore[nWinChair][nChairBaoPai] += SCORE_BASE;
                        
					}
				}
			}
		}
        
		for(int i = 0; i < PLAYER_COUNT; i++)
		{
			if(i == nWinChair)
			{
				continue;
			}
            
			if (m_bBloodyGame && m_sPlayer[i].nState == BLOOD_HU)
			{
				continue;
			}
            
			if(nChairBaoPai != 255)
			{
				nLostChair = nChairBaoPai;
			}
			else
			{
				nLostChair = i;
			}
            
			wWinScore = 0;
			wWinScore += SCORE_BASE * nPerWinScore;
            
			m_wHuScore[nLostChair] -= wWinScore;
			m_wHuScore[nWinChair] += wWinScore;
            
			m_wSetLoseScore[nLostChair] -= wWinScore;
			m_wSetScore[nWinChair] += wWinScore;
            
			m_HuCurt[nWinChair].nGainChair[0]++;
			m_HuCurt[nWinChair].nGainChair[m_HuCurt[nWinChair].nGainChair[0]]=nLostChair;
            
			if (m_bZimoFan)
			{
				m_wZimoFanScore[nLostChair] -= SCORE_BASE;
				m_wZimoFanScore[nWinChair] += SCORE_BASE;
			}
		}
        
		for (int i=0; i<PLAYER_COUNT; ++i)
		{
			CCLOG("---HU score[%d]: %ld---", i, m_wHuScore[i]);
		}
		return true;
	}
    
	// 吃炮者算分在此处！！
	if(m_HuCurt[nWinChair].nState == CHI_PAO)
	{
		BYTE nChairBaoPai = 255;
		//杠炮
		if(m_sGangPao.mark)					
		{
			if(m_sGangPao.chair != nWinChair)
			{
				//退回刮风下雨
				m_wGangScore[nWinChair][nWinChair] += m_sGangPao.score;
				m_wGangScore[nLostChair][nLostChair] -= m_sGangPao.score;
                
				m_wGangScore[nLostChair][nWinChair] -= m_sGangPao.score;
                
			}
		}
		wWinScore = 0;
		wWinScore += SCORE_BASE * nPerWinScore;
        
		m_wHuScore[nLostChair] -= wWinScore;
		m_wHuScore[nWinChair] += wWinScore;
        
		m_wSetLoseScore[nLostChair] -= wWinScore;
		m_wSetScore[nWinChair] += wWinScore;
        
		m_HuCurt[nWinChair].nGainChair[0] = 1;
		m_HuCurt[nWinChair].nGainChair[1]=nLostChair;
        
		CCLOG("%d 号赢家分数为%d", nWinChair, wWinScore);
		CCLOG("%d 号输家分数为－%d", nLostChair, wWinScore);
		for (int i=0; i<PLAYER_COUNT; ++i)
		{
			CCLOG("---HU score[%d]: %ld---", i, m_wHuScore[i]);
		}
		return true;
	}
	
    CCLOG("此人没有胡");
	CCLOG("m_HuCurt[nWinChair].nState == %d", m_HuCurt[nWinChair].nState);
	return false;
	
}

bool CGameLogical::DealCard(BYTE nChair)
{
	if (m_bBloodyGame && m_bChairHu[nChair])	//血战场找未胡玩家发牌
	{
		if (m_nCountHu >=3)
		{
			return false;
		}
		m_chairCurrentPlayer = AntiClock(nChair);
		DealCard(m_chairCurrentPlayer);
	}
    
	CCLOG("DealCard chair %d", m_chairCurrentPlayer);
    
	if(m_bTianRenHu)						//判断天人胡标志
	{
		m_bTianRenHu = false;
	}
	if(m_nDiHu[nChair] <= 1)
	{
		m_nDiHu[nChair] ++;
	}
    
	for(int i=0; i<4; i++)
	{
		if (m_sPlayer[i].nState != BLOOD_HU)
		{
			m_sPlayer[i].bSeenOutCard = 1;		//如无人吃碰杠，则全部可见
			m_sPlayer[i].nState = WAITING;
			m_sPlayer[i].nCardTakenNow = 255;
		}
	}
    
	if(m_nCountAllot >= CARD_NUM)					//没牌啦
	{
		CCLOG("没牌啦, m_nCountAllot: %d", m_nCountAllot);
        
		m_nEndReason = REASON_NOCARD;
		HandleSetOver();
		//m_pSite->SetSceneStatusToFree(CONDITION_STOP_LOGIC, TRUE);
		return true;
        
        // 		if (!m_bBloodyGame)
        // 		{
        // 			m_nEndReason = REASON_NOCARD;
        // 			HandleSetOver();
        // 			m_pSite->SetSceneStatusToFree(CONDITION_STOP_LOGIC, TRUE);
        // 			return true;
        // 		}
        // 		else
        // 		{
        // 			m_nEndReason = REASON_NOCARD;
        // 			HandleSetOver();
        // 			m_pSite->SetSceneStatusToFree(CONDITION_STOP_LOGIC, TRUE);
        // 			return true;
        // 		}
        
	}
	//	m_sOutedCard.clear();
	BYTE nTheCard = m_nCardBuf[m_nCountAllot];
	m_nCountAllot++;
    
	m_sPlayer[nChair].nCardTakenNow	= nTheCard;
	
	PAI_TYPE CardType = GetCardType(nTheCard);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在DealCard");
		return false;
	}
	ListInsert(m_sPlayer[nChair].nCard[CardType], nTheCard);
    
	m_sPlayer[nChair].nState = THINK_OUTCARD;
	m_sCanGang.clear();
	if(FindAnGang(nChair))							//判断有没有暗杠
	{
		m_sPlayer[nChair].nState = CHOOSING;
        m_bChooseBuf[nChair][1] = true;//yaoh 测试用
	}
	if(FindWanGang(nChair))
	{
		m_sPlayer[nChair].nState = CHOOSING;
        m_bChooseBuf[nChair][2] = true;//yaoh 测试用
	}
	ListDelete(m_sPlayer[nChair].nCard[CardType], nTheCard);
    
	if(IsInHuList(nChair, nTheCard))	
	{
		BYTE nTempCard = nTheCard;
		ListInsert(m_sPlayer[nChair].nCard[CardType], nTempCard);
		//1,判断胡
		if(JudgeHu(nChair))	
		{
            ///			//2，加入附加胡
            ///			m_HuCurt[nChair].AddHU(ZIMOFAN);
            ///			m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, "judge hu true in dealcard");
			//3，判断番数
			if(JudgeFan(nChair) >= m_nMinFan) 
			{
				m_bChooseBuf[nChair][3] = 1;
				m_sPlayer[nChair].nState = CHOOSING;
                ///				m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, "judge fan true dealcard");
			}
            
		}
		m_HuCurt[nChair].clear();
		
		ListDelete(m_sPlayer[nChair].nCard[CardType], nTempCard);
		
	}
    
	return true;
}

void CGameLogical::ClearChooseBuf(BYTE nChair, bool bClearGang)
{
 	if(bClearGang)
	{
		m_sQiangGang.clear();
	}
	memset(m_bChooseBuf[nChair], 0, 4);
}

/// cai v2.1
BYTE CGameLogical::JudgeFan(BYTE nChair)
{
	BYTE nFanSum = 0;		
	BYTE nWinChair = nChair; 
	
    ///	if(m_HuCurt[nWinChair].nType == FENGDINGHU)
	switch(m_HuCurt[nWinChair].nMethod[0]) 
	{
        case PINGHU:				//1 平  胡
            nFanSum = 1;
            break;
        case PENGPENGHU:	// 2 碰碰胡
            nFanSum = 2;
            break;
        case QINGYISE:		// 3 清一色
        case YAOJIU:		// 4 幺九
        case QIDUI:			// 5 七对
            nFanSum = 3;
            break;
        case QING_PENG:		// 6 清碰
        case JIANG_PENG:	// 7 将碰
        case LONG_QIDUI:	// 8 龙七对
            nFanSum = 4;
            break;
        case QING_QIDUI:	// 9 清七对
        case QING_YAOJIU:	// 10清幺九
            nFanSum = 5;
            break;
        case QINGLONG_QIDUI:	// 11青龙七对
            nFanSum = 6;
            break;
        default:
            CCLOG("未知的胡类型 发生在ScoreOneHuCal");
            CCLOG("m_HuCurt[nWinChair].nMethod[0] == %d", m_HuCurt[nWinChair].nMethod[0]);
            return false;
	}
    ///	CCLOG("m_HuCurt[nWinChair].nMethod[0] == %d", m_HuCurt[nWinChair].nMethod[0]);
    
	for(int i=1; i<m_HuCurt[nWinChair].nCount; i++)
	{
		switch(m_HuCurt[nWinChair].nMethod[i]) 
		{
            case TIANHU:				//1天胡
            case DIHU:					//2地胡
            case RENHU:					//3人胡
                nFanSum += 6;
                break;
                ///		case ZIMOFAN:				//4自摸
                ///			if (m_bZimoFan)
                ///			{
                ///				nFanSum += 1;
                ///			}
                ///			break;
            case GANGKAI:				//5杠开
            case GANGPAO:				//6杠炮
            case QIANGGANG:				//7抢杠
            case GEN:					//8根
            case GANG:
                nFanSum += 1;
                break;
            default:
                CCLOG("未知的附加胡类型%d, 发生在ScoreOneHuCal", m_HuCurt[nWinChair].nMethod[i]);
                return false;
		}
        ///		CCLOG("附加胡类型%d",m_HuCurt[nWinChair].nMethod[i]);
	}
    
    if (nFanSum > MAX_FAN)
    {
        nFanSum = MAX_FAN;
        m_bMaxFan = true;
    }
    
	return nFanSum;
}


BOOL CGameLogical::IsValidChair(BYTE nChair)
{
	if(nChair >= 0 && nChair <= PLAYER_COUNT)
	{
		return TRUE;
	}
	return FALSE;
}

//void CGameLogical::TianDiRenHuQiangGang()
//{
//	int i = 0;
//	BYTE nChair = AntiClock(m_nChairBanker);
//	m_sPlayer[nChair].nCard[WAN][0] = 13;
//	m_sPlayer[nChair].nCard[TIAO][0] = 0;
//	m_sPlayer[nChair].nCard[TONG][0] = 0;
//	m_sPlayer[nChair].nCard[FENG][0] = 0;
//	m_sPlayer[nChair].nCard[DRAGON][0] = 0;
//	
//	for(i=1; i<= 11; i++)
//	{
//		m_sPlayer[nChair].nCard[WAN][i] = (i-1)/3;
//	}
//	m_sPlayer[nChair].nCard[WAN][12] = 5;
//	m_sPlayer[nChair].nCard[WAN][13] = 6;
//	
//	nChair = AntiClock(nChair);
//	int nWan = m_sPlayer[nChair].nCard[WAN][0];
//	if(nWan < 2)
//	{
//		for(i=TIAO; i<=DRAGON; i++)
//		{
//			if(m_sPlayer[nChair].nCard[i][0] >= 3)
//			{
//				m_sPlayer[nChair].nCard[i][0] -= (2-nWan);
//				m_sPlayer[nChair].nCard[WAN][0] = 2;
//			}
//		}
//	}
//	m_sPlayer[nChair].nCard[WAN][1] = 7;
//	m_sPlayer[nChair].nCard[WAN][2] = 7;
//	m_nCardBuf[m_nCountAllot + 4] = 7;
//	m_nCardBuf[m_nCountAllot] = 7;
//	



BYTE CGameLogical::TAHunYaoJiu()
{
	//清空特征库
	memset(m_TArray, 255, sizeof(m_TArray));
    
	//--m_pSite->SRand(GetTickCount());
	const int iBaseCount = 52;
	//填充特征等级
	int iLevel = 1;//--m_pSite->Rand()%3;
	switch(iLevel) {
        case 0:
            sprintf(m_szTALevel, "么九－");
            break;
        case 1:
            sprintf(m_szTALevel, "么九");
            break;
        case 2:
            sprintf(m_szTALevel, "么九＋");
            break;
        default:
            sprintf(m_szTALevel, "默认");
            break;
	}
    
	const BYTE nTACount = 11 + iLevel;
	//创建序列库
	BYTE ArrayBase[iBaseCount];
	memset(ArrayBase, 0, sizeof(ArrayBase));
    int i;
	for(i=0; i<iBaseCount/4; i++)
	{
		BYTE nCard = 255;
		if(i < 6)
		{
			nCard = (i+1)/2 * 9 - (i%2);
		}
		else
		{
			nCard = 21 + i;
		}
		for(int j=0; j<4; j++)
		{
			ArrayBase[i*4+j] = nCard; 
		}
	}
    
	//打散序列库
	const int nTransferCount = 50;   //发牌随机时转换的次数
	int j=0, k= 0;
	BYTE temp = 255, nTempCard = 255;
	
	for(i = 0; i < nTransferCount; i ++)
	{
		j = //--m_pSite->Rand() % iBaseCount;
		k = //--m_pSite->Rand() % iBaseCount;
		temp = ArrayBase[j];
		ArrayBase[j] = ArrayBase[k];
		ArrayBase[k] = temp;
	}
    
	//选取特征库
	for(i=0; i<nTACount; i++)
	{
		m_TArray[i] = ArrayBase[i];
	}
    
	return nTACount;
}

BYTE CGameLogical::TASanYuan()
{
	//清空特征库
	memset(m_TArray, 255, sizeof(m_TArray));
	
	const int iBaseCount = 12;
	//--m_pSite->SRand(GetTickCount());
    
	//填充特征等级
	int iLevel = 1;//--m_pSite->Rand()%3;
	switch(iLevel) {
        case 0:
            sprintf(m_szTALevel, "三元－");
            break;
        case 1:
            sprintf(m_szTALevel, "三元");
            break;
        case 2:
            sprintf(m_szTALevel, "三元＋");
            break;
        default:
            sprintf(m_szTALevel, "默认");
            break;
	}
	const BYTE nTACount = 7 + iLevel;
    
	//创建序列库
	BYTE ArrayBase[iBaseCount];
	memset(ArrayBase, 0, sizeof(ArrayBase));
    int i;
	for(i=0; i<iBaseCount/4; i++)
	{
		BYTE nCard = 255;
		nCard = i + 31;
		for(int j=0; j<4; j++)
		{
			ArrayBase[i*4+j] = nCard; 
		}
	}
	
	//打散序列库
	const int nTransferCount = 50;   //发牌随机时转换的次数
	int j=0, k= 0;
	BYTE temp = 255, nTempCard = 255;
	
	for(i = 0; i < nTransferCount; i ++)
	{
		j = //--m_pSite->Rand() % iBaseCount;
		k = //--m_pSite->Rand() % iBaseCount;
		temp = ArrayBase[j];
		ArrayBase[j] = ArrayBase[k];
		ArrayBase[k] = temp;
	}
	
	//选取特征库
	for(i=0; i<nTACount; i++)
	{
		m_TArray[i] = ArrayBase[i];
	}
	return nTACount;
}

BYTE CGameLogical::TASiXi()
{
	//清空特征库
	memset(m_TArray, 255, sizeof(m_TArray));
	
	const int iBaseCount = 16;
	//--m_pSite->SRand(GetTickCount());
    
	//填充特征等级
	int iLevel = 1;//--m_pSite->Rand()%3;
	switch(iLevel) {
        case 0:
            sprintf(m_szTALevel, "四喜－");
            break;
        case 1:
            sprintf(m_szTALevel, "四喜");
            break;
        case 2:
            sprintf(m_szTALevel, "四喜＋");
            break;
        default:
            sprintf(m_szTALevel, "默认");
            break;
	}
	const BYTE nTACount = 10 + iLevel;
	
	//创建序列库
	BYTE ArrayBase[iBaseCount];
	memset(ArrayBase, 0, sizeof(ArrayBase));
    int i;
	for(i=0; i<iBaseCount/4; i++)
	{
		BYTE nCard = 255;
		nCard = i + 27;
		for(int j=0; j<4; j++)
		{
			ArrayBase[i*4+j] = nCard; 
		}
	}
	
	//打散序列库
	const int nTransferCount = 50;   //发牌随机时转换的次数
	int j=0, k= 0;
	BYTE temp = 255, nTempCard = 255;
	
	for(i = 0; i < nTransferCount; i ++)
	{
		j = //--m_pSite->Rand() % iBaseCount;
		k = //--m_pSite->Rand() % iBaseCount;
		temp = ArrayBase[j];
		ArrayBase[j] = ArrayBase[k];
		ArrayBase[k] = temp;
	}
	
	//选取特征库
	for(i=0; i<nTACount; i++)
	{
		m_TArray[i] = ArrayBase[i];
	}
	return nTACount;
}

BYTE  CGameLogical:: TAQingYiSe()
{
	//清空特征库
	memset(m_TArray, 255, sizeof(m_TArray));
	
	const int iBaseCount = 36;
    
	//--m_pSite->SRand(GetTickCount());
	//填充特征等级
	int iLevel;
    if (m_nChairTA != 0) {
        iLevel = rand()%3; //m_pSite->Rand()%3;
    }
    else{
        iLevel = 0;
    }
	switch(iLevel) {
        case 0:
            sprintf(m_szTALevel, "清一色－");
            break;
        case 1:
            sprintf(m_szTALevel, "清一色");
            break;
        case 2:
            sprintf(m_szTALevel, "清一色＋");
            break;
        default:
            sprintf(m_szTALevel, "默认");
            break;
	}
	const BYTE nTACount = 11 + iLevel;
    
	//创建序列库
	BYTE ArrayBase[iBaseCount];
	//--m_pSite->SRand(GetTickCount());
	BYTE nLevyType = rand()%3; //m_pSite->Rand() % 3;
    
	memset(ArrayBase, 0, sizeof(ArrayBase));
	for(int i=0; i<iBaseCount/4; i++)
	{
		BYTE nCard = nLevyType*9 + i;
		for(int j=0; j<4; j++)
		{
			ArrayBase[i*4+j] = nCard; 
		}
	}
	
	//打散序列库
	const int nTransferCount = 50;   //发牌随机时转换的次数
	int j=0, k= 0;
	BYTE temp = 255, nTempCard = 255;
	//--m_pSite->SRand(GetTickCount());
	for(int i = 0; i < nTransferCount; i ++)
	{
		j = rand()%iBaseCount; //m_pSite->Rand() % iBaseCount;
		k = rand()%iBaseCount; //m_pSite->Rand() % iBaseCount;
		temp = ArrayBase[j];
		ArrayBase[j] = ArrayBase[k];
		ArrayBase[k] = temp;
	}
	
	//选取特征库
	for(int i=0; i<nTACount; i++)
	{
		m_TArray[i] = ArrayBase[i];
	}
	return nTACount;
}


BYTE CGameLogical::TAYaoJiu()
{
	//清空特征库
	memset(m_TArray, 255, sizeof(m_TArray));
	
	//--m_pSite->SRand(GetTickCount());
	
	const int iBaseYaoJiuCount	= 12;		//2*3*2: 幺九2种牌3张刻字2个花色
	const int iBaseOtherCount	= 12;		//2*3*2: 幺九2种牌3张顺子2个花色
	
	const int iBaseCount = iBaseYaoJiuCount+iBaseOtherCount;	//24, 幺九2种牌2个花色各4张全部进入特征库，二三七八4种牌2个花色各1张进入特征库
	
	
	//填充特征等级
	int iLevel;
    if (m_nChairTA != 0) {
        iLevel = rand()%3; //m_pSite->Rand()%3;
    }
    else{
        iLevel = rand()%2;
    }

	switch(iLevel) {
        case 0:
            sprintf(m_szTALevel, "么九－");
            break;
        case 1:
            sprintf(m_szTALevel, "么九");
            break;
        case 2:
            sprintf(m_szTALevel, "么九＋");
            break;
        default:
            sprintf(m_szTALevel, "默认");
            break;
	}
	
	const BYTE nTACount = 11 + iLevel;
	
	//创建序列库
	BYTE ArrayBase[iBaseCount];
	memset(ArrayBase, 0, sizeof(ArrayBase));
	
	//--m_pSite->SRand(GetTickCount());
	BYTE nLevyType = rand() % 3;
    
	int nCount = 0;
	for(int i=0; i<6; i++)
	{
		if (i/2 == nLevyType)
		{
			continue;
		}
        
		BYTE nCard = (i+1)/2 * 9 - (i%2);
		for(int j=0; j<3; j++)
		{
			ArrayBase[nCount*3+j] = nCard;
		}
		BYTE nCard1 = ((i%2)==0? nCard+1: nCard-1);
		BYTE nCard2 = ((i%2)==0? nCard+2: nCard-2);
		ArrayBase[iBaseYaoJiuCount+3*nCount] = nCard;
		ArrayBase[iBaseYaoJiuCount+3*nCount+1] = nCard1;
		ArrayBase[iBaseYaoJiuCount+3*nCount+2] = nCard2;
		nCount++;
	}
	
	if (!CheckTACard(ArrayBase, iBaseCount))
	{
		CCLOG("TA error, in TAYaoJiu");
		return 0;
	}
	
	//打散序列库
	const int nTransferCount = 50;   //发牌随机时转换的次数
	int j=0, k= 0;
	BYTE temp1 = 255, temp2 = 255;
	
	for(int i = 0; i < nTransferCount; i ++)
	{
		j = rand() % (iBaseCount/3);
		k = rand() % (iBaseCount/3);
		if (j==k)
		{
			continue;
		}
		temp1 = ArrayBase[3*j+1];
		temp2 = ArrayBase[3*j+2];
		ArrayBase[3*j+1] = ArrayBase[3*k+1];
		ArrayBase[3*j+2] = ArrayBase[3*k+2];
		ArrayBase[3*k+1] = temp1;
		ArrayBase[3*k+2] = temp2;
	}
	
	//选取特征库
	for(int i=0; i<nTACount; i++)
	{
		m_TArray[i] = ArrayBase[i];
	}
    
	if (!CheckTACard(m_TArray, nTACount))
	{
		CCLOG("TA error, in TAYaoJiu2");
		return 0;
        
	}
	
	return nTACount;
}


BYTE CGameLogical::TAQiDui()			//3 七对特征牌
{
	//清空特征库
	memset(m_TArray, 255, sizeof(m_TArray));
	
	//--m_pSite->SRand(GetTickCount());
	
	const int iBaseCount = CARD_NUM;	
	
	//填充特征等级
	int iLevel;
    if (m_nChairTA != 0) {
        iLevel = rand()%3; //m_pSite->Rand()%3;
    }
    else{
        iLevel = rand()%2;
    }

	switch(iLevel) {
        case 0:
            sprintf(m_szTALevel, "七对－");
            break;
        case 1:
            sprintf(m_szTALevel, "七对");
            break;
        case 2:
            sprintf(m_szTALevel, "七对＋");
            break;
        default:
            sprintf(m_szTALevel, "默认");
            break;
	}
	
	const BYTE nTACount = 11 + iLevel;
	
	//创建序列库
	BYTE ArrayBase[iBaseCount];
	memset(ArrayBase, 0, sizeof(ArrayBase));
	
	for(int i=0; i<iBaseCount/4; i++)
	{
		BYTE nCard = i;
		for(int j=0; j<4; j++)
		{
			ArrayBase[i*4+j] = nCard;
		}
	}
    
	if (!CheckTACard(ArrayBase, iBaseCount))
	{
		CCLOG("TA error, in TAQiDui");
		return 0;
	}
	
	//打散对子序列库
	const int nTransferCount = 200;   //发牌随机时转换的次数
	int j=0, k= 0;
	BYTE temp1 = 255, temp2 = 255;
	
	for(int i = 0; i < nTransferCount; i ++)
	{
		j = rand() % (iBaseCount/2);
		k = rand() % (iBaseCount/2);
        
		if (j==k)
		{
			continue;
		}
        
		if (ArrayBase[2*j]!=ArrayBase[2*j+1])
		{
			CCLOG("特征库初始化错误，发生在TAQiDui: %d - %d", 2*j, 2*j+1);
			return 0;
		}
        
		if (ArrayBase[2*k]!=ArrayBase[2*k+1])
		{
			CCLOG("特征库初始化错误，发生在TAQiDui: %d - %d", 2*k, 2*k+1);
			return 0;
		}
        
		temp1 = ArrayBase[2*j];
		temp2 = ArrayBase[2*j+1];
		ArrayBase[2*j] = ArrayBase[2*k];
		ArrayBase[2*j+1] = ArrayBase[2*k+1];
		ArrayBase[2*k] = temp1;
		ArrayBase[2*k+1] = temp2;
	}
	
	//选取特征库
	for(int i=0; i<nTACount; i++)
	{
		m_TArray[i] = ArrayBase[i];
	}
	
	return nTACount;
}

BYTE CGameLogical::TAQingPeng()			//4 清碰特征牌
{
	//清空特征库
	memset(m_TArray, 255, sizeof(m_TArray));
	
	//每种花色9张牌的刻字共27张
	const int iBaseCount = 9*3;
	
	//--m_pSite->SRand(GetTickCount());
	//填充特征等级
	int iLevel;
    if (m_nChairTA != 0) {
        iLevel = rand()%3; //m_pSite->Rand()%3;
    }
    else{
        iLevel = 0;
    }

	switch(iLevel) {
        case 0:
            sprintf(m_szTALevel, "清碰－");
            break;
        case 1:
            sprintf(m_szTALevel, "清碰");
            break;
        case 2:
            sprintf(m_szTALevel, "清碰＋");
            break;
        default:
            sprintf(m_szTALevel, "默认");
            break;
	}
	const BYTE nTACount = 11 + iLevel;
	
	//创建序列库
	BYTE ArrayBase[iBaseCount];
	memset(ArrayBase, 0, sizeof(ArrayBase));
    
	//--m_pSite->SRand(GetTickCount());
	BYTE nLevyType = rand() % 3;
    
	for(int i=0; i<iBaseCount/3; i++)
	{
		BYTE nCard = nLevyType*9 + i;
		for(int j=0; j<3; j++)
		{
			ArrayBase[i*3+j] = nCard; 
		}
	}
	
	//打散序列库
	const int nTransferCount = 50;   //发牌随机时转换的次数
	int j=0, k= 0;
	BYTE temp = 255, nTempCard = 255;
	//--m_pSite->SRand(GetTickCount());
	for(int i = 0; i < nTransferCount; i ++)
	{
		j = rand() % (iBaseCount/3);
		k = rand() % (iBaseCount/3);
        
		if (j==k)
		{
			continue;
		}
        
		if (ArrayBase[3*j]!=ArrayBase[3*j+1] || ArrayBase[3*j]!=ArrayBase[3*j+2])
		{
			CCLOG("特征库初始化错误，发生在TAQingPeng: %d - %d - %d", 3*j, 3*j+1, 3*j+2);
			return 0;
		}
		
		if (ArrayBase[3*k]!=ArrayBase[3*k+1] || ArrayBase[3*k]!=ArrayBase[3*k+2])
		{
			CCLOG("特征库初始化错误，发生在TAQingPeng: %d - %d - %d", 3*k, 3*k+1, 3*k+2);
			return 0;
		}
        
		temp = ArrayBase[3*j];
		ArrayBase[3*j] = ArrayBase[3*k];
		ArrayBase[3*j+1] = ArrayBase[3*k];
		ArrayBase[3*j+2] = ArrayBase[3*k];
		ArrayBase[3*k] = temp;
		ArrayBase[3*k+1] = temp;
		ArrayBase[3*k+2] = temp;
	}
	
	//选取特征库
	for(int i=0; i<nTACount; i++)
	{
		m_TArray[i] = ArrayBase[i];
	}
	return nTACount;
}

BYTE CGameLogical::TAJiangPeng()		//5 将碰特征牌
{
	//清空特征库
	memset(m_TArray, 255, sizeof(m_TArray));
	
	//3种花色二五八3种将牌的3张刻字共3*3*3张
	const int iBaseCount = 27;
	
	//--m_pSite->SRand(GetTickCount());
	//填充特征等级
	int iLevel;
    if (m_nChairTA != 0) {
        iLevel = rand()%3; //m_pSite->Rand()%3;
    }
    else{
        iLevel = rand()%2;
    }

	switch(iLevel) {
        case 0:
            sprintf(m_szTALevel, "将碰－");
            break;
        case 1:
            sprintf(m_szTALevel, "将碰");
            break;
        case 2:
            sprintf(m_szTALevel, "将碰＋");
            break;
        default:
            sprintf(m_szTALevel, "默认");
            break;
	}
	const BYTE nTACount = 11 + iLevel;
	
	//创建序列库
	BYTE ArrayBase[iBaseCount];
	memset(ArrayBase, 0, sizeof(ArrayBase));
    
	for(int i=0; i<iBaseCount/3; i++)
	{
		BYTE nCard = (i/3)*9 + (i%3)*3+1;
		for(int j=0; j<3; j++)
		{
			ArrayBase[i*3+j] = nCard; 
		}
	}
    
	if (!CheckTACard(ArrayBase, iBaseCount))
	{
		CCLOG("TA error, in TAJiangPeng");
		return 0;
	}
	
	//打散序列库
	const int nTransferCount = 50;   //发牌随机时转换的次数
	int j=0, k= 0;
	BYTE temp = 255, nTempCard = 255;
	//--m_pSite->SRand(GetTickCount());
	for(int i = 0; i < nTransferCount; i ++)
	{
		j = rand() % (iBaseCount/3);
		k = rand() % (iBaseCount/3);
		
		if (j==k)
		{
			continue;
		}
		
		if (!Is258(ArrayBase[3*j]) || ArrayBase[3*j]!=ArrayBase[3*j+1] || ArrayBase[3*j]!=ArrayBase[3*j+2])
		{
			CCLOG("特征库初始化错误，发生在TAJiangPeng: %d - %d - %d, %d", 3*j, 3*j+1, 3*j+2, ArrayBase[3*j]);
			return 0;
		}
		
		if (!Is258(ArrayBase[3*k]) || ArrayBase[3*k]!=ArrayBase[3*k+1] || ArrayBase[3*k]!=ArrayBase[3*k+2])
		{
			CCLOG("特征库初始化错误，发生在TAJiangPeng: %d - %d - %d, %d", 3*k, 3*k+1, 3*k+2, ArrayBase[3*k]);
			return 0;
		}
		
		temp = ArrayBase[3*j];
		ArrayBase[3*j] = ArrayBase[3*k];
		ArrayBase[3*j+1] = ArrayBase[3*k];
		ArrayBase[3*j+2] = ArrayBase[3*k];
		ArrayBase[3*k] = temp;
		ArrayBase[3*k+1] = temp;
		ArrayBase[3*k+2] = temp;
	}
	
	//选取特征库
	for(int i=0; i<nTACount; i++)
	{
		m_TArray[i] = ArrayBase[i];
	}
	return nTACount;
}

BYTE CGameLogical::TALongQiDui()		//6 龙七对特征牌
{
	//清空特征库
	memset(m_TArray, 255, sizeof(m_TArray));
	
	//--m_pSite->SRand(GetTickCount());
	
	const int iBaseCount = CARD_NUM;	
	
	//填充特征等级
	int iLevel;
    if (m_nChairTA != 0) {
        iLevel = rand()%3; //m_pSite->Rand()%3;
    }
    else{
        iLevel = 0;
    }

	switch(iLevel) {
        case 0:
            sprintf(m_szTALevel, "龙七对－");
            break;
        case 1:
            sprintf(m_szTALevel, "龙七对");
            break;
        case 2:
            sprintf(m_szTALevel, "龙七对＋");
            break;
        default:
            sprintf(m_szTALevel, "默认");
            break;
	}
	
	const BYTE nTACount = 11 + iLevel;
	
	//创建序列库
	BYTE ArrayBase[iBaseCount];
	memset(ArrayBase, 0, sizeof(ArrayBase));
	
	for(int i=0; i<iBaseCount/4; i++)
	{
		BYTE nCard = i;
		for(int j=0; j<4; j++)
		{
			ArrayBase[i*4+j] = nCard;
		}
	}
	
	if (!CheckTACard(ArrayBase, iBaseCount))
	{
		CCLOG("TA error, in TALongQiDui");
		return 0;
	}
	
	//打散对子序列库
	const int nTransferCount = 200;   //发牌随机时转换的次数
	int j=0, k= 0;
	BYTE temp1 = 255, temp2 = 255;
	
	for(int i = 0; i < nTransferCount; i ++)
	{
		j = rand() % (iBaseCount/2);
		k = rand() % (iBaseCount/2);
        
		if (j==k)
		{
			continue;
		}
		
		if (ArrayBase[2*j]!=ArrayBase[2*j+1])
		{
			CCLOG("特征库初始化错误，发生在TALongQiDui: %d - %d", 2*j, 2*j+1);
			return 0;
		}
		
		if (ArrayBase[2*k]!=ArrayBase[2*k+1])
		{
			CCLOG("特征库初始化错误，发生在TALongQiDui: %d - %d", 2*k, 2*k+1);
			return 0;
		}
		
		temp1 = ArrayBase[2*j];
		temp2 = ArrayBase[2*j+1];
		ArrayBase[2*j] = ArrayBase[2*k];
		ArrayBase[2*j+1] = ArrayBase[2*k+1];
		ArrayBase[2*k] = temp1;
		ArrayBase[2*k+1] = temp2;
	}
    
	for (int i=0; i<iBaseCount/2; ++i)
	{
		if (i!=0 && ArrayBase[2*i]==ArrayBase[0])
		{
			ArrayBase[2*i] = ArrayBase[2*i+1] = ArrayBase[2];
			ArrayBase[2] = ArrayBase[3] = ArrayBase[0];
			break;
		}
	}
	
	//选取特征库
	for(int i=0; i<nTACount; i++)
	{
		m_TArray[i] = ArrayBase[i];
	}
	
	return nTACount;
}

BYTE CGameLogical::TAQingQiDui()		//7 清七对特征牌
{
	//清空特征库
	memset(m_TArray, 255, sizeof(m_TArray));
	
	//--m_pSite->SRand(GetTickCount());
	
	const int iBaseCount = 9*4;	
	
	//填充特征等级
	int iLevel;
    if (m_nChairTA != 0) {
        iLevel = rand()%3; //m_pSite->Rand()%3;
    }
    else{
        iLevel = 0;
    }

	switch(iLevel) {
        case 0:
            sprintf(m_szTALevel, "清七对－");
            break;
        case 1:
            sprintf(m_szTALevel, "清七对");
            break;
        case 2:
            sprintf(m_szTALevel, "清七对＋");
            break;
        default:
            sprintf(m_szTALevel, "默认");
            break;
	}
	
	const BYTE nTACount = 11 + iLevel;
	
	//创建序列库
	BYTE ArrayBase[iBaseCount];
	memset(ArrayBase, 0, sizeof(ArrayBase));
	
	//--m_pSite->SRand(GetTickCount());
	BYTE nLevyType = rand() % 3;
	
	for(int i=0; i<iBaseCount/4; i++)
	{
		BYTE nCard = nLevyType*9 + i;;
		for(int j=0; j<4; j++)
		{
			ArrayBase[i*4+j] = nCard;
		}
	}
	
	if (!CheckTACard(ArrayBase, iBaseCount))
	{
		CCLOG("TA error, in TAQingQiDui");
		return 0;
	}
	
	//打散对子序列库
	const int nTransferCount = 50;   //发牌随机时转换的次数
	int j=0, k= 0;
	BYTE temp1 = 255, temp2 = 255;
	
	for(int i = 0; i < nTransferCount; i ++)
	{
		j = rand() % (iBaseCount/2);
		k = rand() % (iBaseCount/2);
		
		if (j==k)
		{
			continue;
		}
		
		if (ArrayBase[2*j]!=ArrayBase[2*j+1])
		{
			CCLOG("特征库初始化错误，发生在TAQingQiDui: %d - %d", 2*j, 2*j+1);
			return 0;
		}
		
		if (ArrayBase[2*k]!=ArrayBase[2*k+1])
		{
			CCLOG("特征库初始化错误，发生在TAQingQiDui: %d - %d", 2*k, 2*k+1);
			return 0;
		}
		
		temp1 = ArrayBase[2*j];
		temp2 = ArrayBase[2*j+1];
		ArrayBase[2*j] = ArrayBase[2*k];
		ArrayBase[2*j+1] = ArrayBase[2*k+1];
		ArrayBase[2*k] = temp1;
		ArrayBase[2*k+1] = temp2;
	}
	
	//选取特征库
	for(int i=0; i<nTACount; i++)
	{
		m_TArray[i] = ArrayBase[i];
	}
	
	return nTACount;
}

BYTE CGameLogical::TAQingYaJiu()		//8 清幺九特征牌
{
	//清空特征库
	memset(m_TArray, 255, sizeof(m_TArray));
	
	//--m_pSite->SRand(GetTickCount());
	
	const int iBaseYaoJiuCount	= 6;		//3*2*1: 幺九2种牌3张刻子1个花色
	const int iBaseYaoJiuShunCount	= 6;		//3*2*1: 幺九2种牌3张顺子1个花色
	const int iBaseOtherCount = 4;
	
	//12, 幺九2种牌1个花色各4张全部进入特征库，二三七八4种牌1个花色各1张进入特征库
	const int iBaseCount = iBaseYaoJiuCount+iBaseYaoJiuShunCount+iBaseOtherCount;
    //	const int iBaseCount = iBaseYaoJiuCount+iBaseYaoJiuShunCount;
	
	//填充特征等级
	int iLevel;
    if (m_nChairTA != 0) {
        iLevel = rand()%3; //m_pSite->Rand()%3;
    }
    else{
        iLevel = 0;
    }

	switch(iLevel) {
        case 0:
            sprintf(m_szTALevel, "清么九－");
            break;
        case 1:
            sprintf(m_szTALevel, "清么九");
            break;
        case 2:
            sprintf(m_szTALevel, "清么九＋");
            break;
        default:
            sprintf(m_szTALevel, "默认");
            break;
	}
	
	const BYTE nTACount = 11 + iLevel;
	
	//创建序列库
	BYTE ArrayBase[iBaseCount];
	memset(ArrayBase, 0, sizeof(ArrayBase));
	
	//--m_pSite->SRand(GetTickCount());
	BYTE nLevyType = rand() % 3;
	
	for(int i=0; i<2; i++)
	{
		BYTE nCard = (i+1)/2 * 9 - (i%2) + nLevyType*9;
		for(int j=0; j<3; j++)
		{
			ArrayBase[i*3+j] = nCard;
		}
		BYTE nCard1 = ((i%2)==0? nCard+1: nCard-1);
		BYTE nCard2 = ((i%2)==0? nCard+2: nCard-2);
		ArrayBase[iBaseYaoJiuCount+3*i] = nCard;
		ArrayBase[iBaseYaoJiuCount+3*i+1] = nCard1;
		ArrayBase[iBaseYaoJiuCount+3*i+2] = nCard2;
	}
	
	ArrayBase[iBaseYaoJiuCount+iBaseYaoJiuShunCount] = nLevyType*9+1;
	ArrayBase[iBaseYaoJiuCount+iBaseYaoJiuShunCount+1] = nLevyType*9+2;
	ArrayBase[iBaseYaoJiuCount+iBaseYaoJiuShunCount+2] = nLevyType*9+6;
	ArrayBase[iBaseYaoJiuCount+iBaseYaoJiuShunCount+3] = nLevyType*9+7;
	
	if (!CheckTACard(ArrayBase, iBaseCount))
	{
		CCLOG("TA error, in TAQingYaJiu");
		return 0;
	}
	
	//打散序列库
	const int nTransferCount = 50;   //发牌随机时转换的次数
	int j=0, k= 0;
	BYTE temp1 = 255, temp2 = 255;
	int m = 0, n = 0;
	
	for(int i = 0; i < nTransferCount; i ++)
	{
		j = rand() % (iBaseCount/3);
		k = rand() % (iBaseCount/3);
        
		m = rand() % (iBaseCount-iBaseOtherCount);
		n = rand() % iBaseOtherCount;
		temp1 = ArrayBase[m];
		ArrayBase[m] = ArrayBase[iBaseCount - iBaseOtherCount + n];
		ArrayBase[iBaseCount - iBaseOtherCount + n] = temp1;
        
		if (j==k)
		{
			continue;
		}
		temp1 = ArrayBase[3*j+1];
		temp2 = ArrayBase[3*j+2];
		ArrayBase[3*j+1] = ArrayBase[3*k+1];
		ArrayBase[3*j+2] = ArrayBase[3*k+2];
		ArrayBase[3*k+1] = temp1;
		ArrayBase[3*k+2] = temp2;
	}
	
	//选取特征库
	for(int i=0; i<nTACount; i++)
	{
		m_TArray[i] = ArrayBase[i];
	}
	
	if (!CheckTACard(m_TArray, nTACount))
	{
		CCLOG("TA error, in TAYaoJiu2");
		return 0;
	}
	
	return nTACount;
}


BYTE CGameLogical::TAQingLongQiDui()	//9 清龙七对特征牌
{
	//清空特征库
	memset(m_TArray, 255, sizeof(m_TArray));
	
	//--m_pSite->SRand(GetTickCount());
	
	const int iBaseCount = 13;
	
	const BYTE nTACount = 11;
	
	//创建序列库
	BYTE ArrayBase[iBaseCount];
	memset(ArrayBase, 0, sizeof(ArrayBase));
    
	ArrayBase[0] = 8;
	ArrayBase[1] = ArrayBase[2] = ArrayBase[3] = ArrayBase[4] = 0;
	ArrayBase[5] = ArrayBase[6] = ArrayBase[7] = ArrayBase[8] = 1;
	ArrayBase[9] = ArrayBase[10] = ArrayBase[11] = ArrayBase[12] = 2;
    
	for(int i=0; i<4; i++)
	{
		if (!ReplaceCardFromBuf(&(m_nCardBuf[0]), 9, 0, m_nCardBuf[9+i]))
		{
			ReplaceCardFromBuf(&(m_nCardBuf[13]), CARD_NUM-13, 0, m_nCardBuf[9+i]);
		}
		m_nCardBuf[9+i] = 0;
	}
    
	for (int i = 0; i<NUM_ALL_TYPE; ++i)
	{
		int nCount = 1;
		for (int j=0; j<CARD_NUM; ++j)
		{
			if (m_nCardBuf[j]==i)
			{
				nCount++;
				CCLOG("%d - %d : buf[%d]", i, nCount, j);
			}
		}
	}
    
	for(int i=0; i<13; ++i)
	{
		CCLOG("m_nCardBuf[%d]: %d - ArrayBase[%d]: %d", i, m_nCardBuf[i], i, ArrayBase[i]);
	}
	
	
	//选取特征库
	for(int i=0; i<nTACount; i++)
	{
		m_TArray[i] = ArrayBase[i];
	}
	
	if (!CheckTACard(m_TArray, nTACount))
	{
		CCLOG("TA error, in TAQingLongQiDui2");
		return 0;
	}
	
	return nTACount;
    
}

bool CGameLogical::CheckTACard(BYTE ArrayBase[], const int iBaseCount)
{
	for (int i=0; i<iBaseCount; ++i)
	{
		int nMax = 1;
		for (int j=0; j<iBaseCount; ++j)
		{
			if(i==0 && PAI_TYPE_INVALID == GetCardType(ArrayBase[j]))
			{
				CCLOG("错误的牌类型，发生在CheckTACard");
				return false;
			}
			
			if (i == j)
			{
				continue;
			}
			else if (ArrayBase[i]==ArrayBase[j])
			{
				nMax++;
			}
		}
		
		if (nMax>4)
		{
			CCLOG("特征库初始化错误，发生在CheckTACard");
			return false;
		}
	}
    
	return true;
}

void CGameLogical::ResetTACardBuf(BYTE nTACount)
{
	for(int i=0; i<nTACount; i++)
	{
		ReplaceCardFromBuf(&(m_nCardBuf[i]), CARD_NUM-i, m_TArray[i], m_nCardBuf[i]);
		m_nCardBuf[i] = m_TArray[i];
	}
}
BOOL CGameLogical::ReplaceCardFromBuf(BYTE* pBuf, int nLength, BYTE nPreCard, BYTE nByCard, BOOL bOnlyOnce)
{
	BOOL bFind = FALSE;
	for(int i=0; i<nLength; i++)
	{
		if(pBuf[i] == nPreCard)
		{
			pBuf[i] = nByCard;
			bFind = TRUE;
			if(bOnlyOnce)
			{
				break;
			}
		}
	}
    
	return bFind;
}

void CGameLogical::WashCard(BYTE nTACount, BYTE nTAChair)
{
	const int nTransferCount = 400;   //发牌随机时转换的次数
	int i=0, j=0, k= 0;
	BYTE temp = 255, nTempCard = 255;
    
	//洗牌
	//--m_pSite->SRand(GetTickCount());
    srand(time(NULL));
    
	if(nTAChair == 255 || nTACount == 0)
	{
		for(i = 0; i < nTransferCount; i ++)
		{
			j = rand() % CARD_NUM;//--m_pSite->Rand() % CARD_NUM;
			k = rand() % CARD_NUM;//--m_pSite->Rand() % CARD_NUM;
			temp = m_nCardBuf[j];
			m_nCardBuf[j] = m_nCardBuf[k];
			m_nCardBuf[k] = temp;
		}
	}
	else
	{
		for(i = 0; i < nTransferCount; i ++)
		{
			j = rand() % (CARD_NUM-nTACount);//--m_pSite->Rand() % (CARD_NUM-nTACount);
			k = rand() % (CARD_NUM-nTACount);//--m_pSite->Rand() % (CARD_NUM-nTACount);
			j += nTACount;
			k += nTACount;
			temp = m_nCardBuf[j];
			m_nCardBuf[j] = m_nCardBuf[k];
			m_nCardBuf[k] = temp;
		}
		if(nTAChair != 0)
		{
			for(i=0; i<HOLD_CARD_NUM; i++)
			{
				temp = m_nCardBuf[i];
				m_nCardBuf[i] = m_nCardBuf[nTAChair*HOLD_CARD_NUM+i];
				m_nCardBuf[nTAChair*HOLD_CARD_NUM+i] = temp;
			}
		}
	}
}

///<cai
void CGameLogical::DealAllCardBySet(int iNomi, int iDeNomi)  // 发特定牌
{
    BYTE nChairTA = 255;
    BYTE nTempCard = 255;
    //提供1/4特征牌的概率
    //--m_pSite->SRand(GetTickCount());
    int iResidue = rand() % iDeNomi; //--m_pSite->Rand() % iDeNomi;
    if(iResidue < iNomi)
    {
        nChairTA = rand() % 4;//--m_pSite->Rand() % 4;
        //创建并置入特征库
        int nLevyFuncPos = rand() % m_iTAFuncCount;//--m_pSite->Rand() % m_iTAFuncCount;
        BYTE nTACount = (this->*BuildTA[nLevyFuncPos])();
        ResetTACardBuf(nTACount);
        
        //洗牌
        WashCard(nTACount, nChairTA);
        
        //发送提示消息
        //DWORD dwUserID = //--m_pSite->GetUserID(nChairTA);
        //char szPrompt[256];
        //memset(szPrompt, 0, sizeof(szPrompt));
        //sprintf(szPrompt, "系统提示：您有幸发到“%s”特征牌，努力做一把大胡吧！", m_szTALevel);
        //--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER,dwUserID,szPrompt);
        // 		//随机选择提示语
        // 		char* pTemp = NULL;
        // 		CIni Ini("Prompt.ini");
        // 		int iPromtCount = 0;
        // 		if (Ini.ReadInt("FriendPrompt", "Count", iPromtCount))
        // 		{
        // 			int iPromptPos = //--m_pSite->Rand() % iPromtCount;
        // 			char szItem[32];
        // 			memset(szItem, 0, sizeof(szItem));
        // 			sprintf(szItem, "Phase%d", iPromptPos+1);
        // 			pTemp = Ini.ReadText("FriendPrompt", szItem);
        // 		}
        // 		if(pTemp != NULL)
        // 		{
        // 			memset(szPrompt, 0, sizeof(szPrompt));
        // 			sprintf(szPrompt, "友情留言：%s", pTemp);
        // 			//--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER,dwUserID,szPrompt);
        // 		}
    }
    else
    {
        WashCard();
    }
    
    //发牌
    //给每人发13张特定牌
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    m_sPlayer[3].nCard[TIAO][0]++;
    m_sPlayer[3].nCard[TIAO][m_sPlayer[3].nCard[TIAO][0]]  = 9;	
    m_sPlayer[3].nCard[TIAO][0]++;
    m_sPlayer[3].nCard[TIAO][m_sPlayer[3].nCard[TIAO][0]]  = 9;
    m_sPlayer[3].nCard[TIAO][0]++;
    m_sPlayer[3].nCard[TIAO][m_sPlayer[3].nCard[TIAO][0]]  = 9;	
    m_sPlayer[3].nCard[TIAO][0]++;
    m_sPlayer[3].nCard[TIAO][m_sPlayer[3].nCard[TIAO][0]]  = 10;	
    m_sPlayer[3].nCard[TIAO][0]++;
    m_sPlayer[3].nCard[TIAO][m_sPlayer[3].nCard[TIAO][0]]  = 10;	
    m_sPlayer[3].nCard[TIAO][0]++;
    m_sPlayer[3].nCard[TIAO][m_sPlayer[3].nCard[TIAO][0]]  = 10;	
    m_sPlayer[3].nCard[TIAO][0]++;
    m_sPlayer[3].nCard[TIAO][m_sPlayer[3].nCard[TIAO][0]]  = 11;	
    m_sPlayer[3].nCard[TIAO][0]++;
    m_sPlayer[3].nCard[TIAO][m_sPlayer[3].nCard[TIAO][0]]  = 11;
    m_sPlayer[3].nCard[TIAO][0]++;
    m_sPlayer[3].nCard[TIAO][m_sPlayer[3].nCard[TIAO][0]]  = 11;	
    m_sPlayer[3].nCard[TIAO][0]++;
    m_sPlayer[3].nCard[TIAO][m_sPlayer[3].nCard[TIAO][0]]  = 12;	
    m_sPlayer[3].nCard[TIAO][0]++;
    m_sPlayer[3].nCard[TIAO][m_sPlayer[3].nCard[TIAO][0]]  = 12;	
    m_sPlayer[3].nCard[WAN][0]++;
    m_sPlayer[3].nCard[WAN][m_sPlayer[3].nCard[WAN][0]]  = 0;	
    m_sPlayer[3].nCard[WAN][0]++;
    m_sPlayer[3].nCard[WAN][m_sPlayer[3].nCard[WAN][0]]  = 4;
    
    // m_sPlayer[3].nCard[FENG][0]++;
    // m_sPlayer[3].nCard[FENG][m_sPlayer[3].nCard[FENG][0]]  = 27;	
    // m_sPlayer[3].nCard[FENG][0]++;
    // m_sPlayer[3].nCard[FENG][m_sPlayer[3].nCard[FENG][0]]  = 30;	
    // m_sPlayer[3].nCard[FENG][0]++;
    // m_sPlayer[3].nCard[FENG][m_sPlayer[3].nCard[FENG][0]]  = 30;
    // 
    // m_sPlayer[3].nCard[DRAGON][0]++;
    // m_sPlayer[3].nCard[DRAGON][m_sPlayer[3].nCard[DRAGON][0]]  = 33;	
    // m_sPlayer[3].nCard[DRAGON][0]++;
    // m_sPlayer[3].nCard[DRAGON][m_sPlayer[3].nCard[DRAGON][0]]  = 33;
    
    m_sPlayer[3].nLen = 13;
    //对玩家i手中的牌进行排序
    int k1;
    for(k1=WAN; k1<=DRAGON; k1++)
    {
        ListSort(&m_sPlayer[3].nCard[k1][1], m_sPlayer[3].nCard[k1][0]);
    }
    
    
    
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 14;
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 14;
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 14;
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 15;
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 15;
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 15; 
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 16;
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 16;
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 16;
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 17;
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 17;
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 17;
    m_sPlayer[2].nCard[TIAO][0]++;
    m_sPlayer[2].nCard[TIAO][m_sPlayer[2].nCard[TIAO][0]]  = 13;
    
    
    m_sPlayer[2].nLen = 13;
    //对玩家i手中的牌进行排序
    for(k1=WAN; k1<=DRAGON; k1++)
    {
        ListSort(&m_sPlayer[2].nCard[k1][1], m_sPlayer[2].nCard[k1][0]);
    }
    //	m_sPlayer[0].nCard[WAN][13] = 8;
    
    
    m_sPlayer[1].nCard[WAN][0]++;
    m_sPlayer[1].nCard[WAN][m_sPlayer[1].nCard[WAN][0]]  = 0;
    m_sPlayer[1].nCard[WAN][0]++;
    m_sPlayer[1].nCard[WAN][m_sPlayer[1].nCard[WAN][0]]  = 1; 
    m_sPlayer[1].nCard[WAN][0]++;
    m_sPlayer[1].nCard[WAN][m_sPlayer[1].nCard[WAN][0]]  = 2;
    m_sPlayer[1].nCard[WAN][0]++;
    m_sPlayer[1].nCard[WAN][m_sPlayer[1].nCard[WAN][0]]  = 3;
    m_sPlayer[1].nCard[WAN][0]++;
    m_sPlayer[1].nCard[WAN][m_sPlayer[1].nCard[WAN][0]]  = 4;
    m_sPlayer[1].nCard[WAN][0]++;
    m_sPlayer[1].nCard[WAN][m_sPlayer[1].nCard[WAN][0]]  = 5;
    
    m_sPlayer[1].nCard[TONG][0]++;
    m_sPlayer[1].nCard[TONG][m_sPlayer[1].nCard[TONG][0]]  = 22;
    m_sPlayer[1].nCard[TONG][0]++;
    m_sPlayer[1].nCard[TONG][m_sPlayer[1].nCard[TONG][0]]  = 22;
    m_sPlayer[1].nCard[TONG][0]++;
    m_sPlayer[1].nCard[TONG][m_sPlayer[1].nCard[TONG][0]]  = 24;
    m_sPlayer[1].nCard[TONG][0]++;
    m_sPlayer[1].nCard[TONG][m_sPlayer[1].nCard[TONG][0]]  = 25;
    m_sPlayer[1].nCard[TONG][0]++;
    m_sPlayer[1].nCard[TONG][m_sPlayer[1].nCard[TONG][0]]  = 25;
    m_sPlayer[1].nCard[TONG][0]++;
    m_sPlayer[1].nCard[TONG][m_sPlayer[1].nCard[TONG][0]]  = 25;
    m_sPlayer[1].nCard[TONG][0]++;
    m_sPlayer[1].nCard[TONG][m_sPlayer[1].nCard[TONG][0]]  = 26;
    
    
    
    
    m_sPlayer[1].nLen = 13;
    //对玩家i手中的牌进行排序
    for(k1=WAN; k1<=DRAGON; k1++)
    {
        ListSort(&m_sPlayer[1].nCard[k1][1], m_sPlayer[1].nCard[k1][0]);
    }
    //	m_sPlayer[1].nCard[DRAGON][13] = 0;
    
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]]  = 18;
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]]  = 18;
    
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]] = 26;
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]] = 19;	
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]] = 19;
    
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]] = 20;	
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]] = 20;
    
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]] = 21;
    
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]]  = 21;
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]]  = 22;
    
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]] = 22;
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]] = 23;
    m_sPlayer[0].nCard[TONG][0]++;
    m_sPlayer[0].nCard[TONG][m_sPlayer[0].nCard[TONG][0]] = 23;
    
    m_sPlayer[0].nLen = 13;
    //对玩家i手中的牌进行排序
    for(k1=WAN; k1<=DRAGON; k1++)
    {
        ListSort(&m_sPlayer[0].nCard[k1][1], m_sPlayer[0].nCard[k1][0]);
    }
    
    //重新调整牌堆-------------------------------------------------
    //------------------------------------------------------------
    BYTE p=0;
    for (int m = 0; m<PLAYER_COUNT; m++) {
        for (int n=0; n<3; n++) {
            for (int o=1; o<14; o++) {
                if (m_sPlayer[m].nCard[n][o] != 255) {
                    
                    if (m_sPlayer[m].nCard[n][o] != m_nCardBuf[p++]) {
                        
                        for (int q = p; q<108; q++) {
                            if (m_sPlayer[m].nCard[n][o] == m_nCardBuf[q]) {
                                
                                m_nCardBuf[q] = m_nCardBuf[p-1];
                                m_nCardBuf[p-1] = m_sPlayer[m].nCard[n][o];
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    
    //发测试牌  为 摸牌
    BYTE cc = 26, index=52;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    }
   
    cc = 19, index=53;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    }

    cc = 1, index=54;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    }
    cc = 1, index=55;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    }
    cc = 21, index=56;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    }
    cc = 18, index=57;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    } 
    cc = 2, index=58;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    } 
    
    m_nCountAllot = 52;
    
    //给庄家发第14张牌
    DealCard(m_nChairBanker);
    //m_sPlayer[m_nChairBanker].nCardTakenNow = m_nCardBuf[m_nCountAllot++];	
}
///cai>

void CGameLogical::DealAllCardEx(int iNomi, int iDeNomi)
{
    // 	BYTE nTempCard = 255;
    // 	WashCard();
    bool    bTAGuanka1 = false;
    int     nCurGuanka = GetIntegerToXML(UD_CurrentGuanKa);
    bool    bPassedGk1 = GetBoolToXML(UD_PASS_GUANKA_1, false);
    
    bool    bUsingTACard = GetBoolToXML(UD_SINGLE_TACARD, false);
    if (bUsingTACard) {
        iNomi = iDeNomi = 1;
    }
    
    if (nCurGuanka==1 && !bPassedGk1 && iNomi!=0)
    {
        bTAGuanka1 = true;
    }
    ///*///<cai
	//BYTE nChairTA = 255;
    m_nChairTA = 255;
	BYTE nTempCard = 255;
	//提供iNomi/iDeNomi特征牌的概率
	//m_pSite->SRand(GetTickCount());
	int iResidue = rand()% iDeNomi; //m_pSite->Rand() % iDeNomi;
	if(iResidue < iNomi)
	{
        if (bUsingTACard) {
            m_nChairTA = 0;
            SetBoolToXML(UD_SINGLE_TACARD, false);
        }
        else if (bTAGuanka1)
        {
            m_nChairTA = rand()%2;
            if (m_nChairTA < 1)
            {
                m_nChairTA = 0;
            }
            else
            {
                m_nChairTA = rand()%3+1;
            }
        }
        else
        {
            m_nChairTA = rand()%10;
            if (m_nChairTA < 1)
            {
                m_nChairTA = 0;
            }
            else
            {
                m_nChairTA = rand()%3+1;
            }

        }
        
#if IS_TEST_CARD
        m_nChairTA = 0;
#endif
        
//        nChairTA = rand()%4;
        
//        int nRand = rand()%7;
//        nChairTA = (nRand+1)/2;
//        if (nChairTA>=4) {
//            CCLOG("TA chair error");
//            return;
//        }
		//创建并置入特征库
		int nLevyFuncPos = rand()%m_iTAFuncCount; //m_pSite->Rand() % m_iTAFuncCount;
		BYTE nTACount = (this->*BuildTA[nLevyFuncPos])();
		ResetTACardBuf(nTACount);
        
        CCLOG("p:%d/%d, TAChair:%d", iNomi, iDeNomi, m_nChairTA);
        
		//洗牌
		WashCard(nTACount, m_nChairTA);
		
		//发送提示消息
        if (m_nChairTA == 0)
        {
            ((GameDesk *)UIDelegate)->OnGetExCard();
        }
        
//		DWORD dwUserID = m_pSite->GetUserID(nChairTA);
//		char szPrompt[256];
//		memset(szPrompt, 0, sizeof(szPrompt));
//		sprintf(szPrompt, "系统提示：您有幸发到“%s”特征牌，努力做一把大胡吧！", m_szTALevel);
        
		//--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER,dwUserID,szPrompt);
        // 		//随机选择提示语
        // 		char* pTemp = NULL;
        // 		CIni Ini("Prompt.ini");
        // 		int iPromtCount = 0;
        // 		if (Ini.ReadInt("FriendPrompt", "Count", iPromtCount))
        // 		{
        // 			int iPromptPos = m_pSite->Rand() % iPromtCount;
        // 			char szItem[32];
        // 			memset(szItem, 0, sizeof(szItem));
        // 			sprintf(szItem, "Phase%d", iPromptPos+1);
        // 			pTemp = Ini.ReadText("FriendPrompt", szItem);
        // 		}
        // 		if(pTemp != NULL)
        // 		{
        // 			memset(szPrompt, 0, sizeof(szPrompt));
        // 			sprintf(szPrompt, "友情留言：%s", pTemp);
        // 			m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER,dwUserID,szPrompt);
        // 		}
	}
	else
	{
		WashCard();
	}
    //*////cai>
    
	//发牌
	//给每人发13张牌
	for(int i=0; i<PLAYER_COUNT; i++)
	{
		for(int k=0; k<HOLD_CARD_NUM; k++)
		{
			nTempCard = m_nCardBuf[m_nCountAllot++];	//从牌缓冲区里那张牌
			PAI_TYPE CardType = GetCardType(nTempCard);
			if(PAI_TYPE_INVALID != CardType)
			{
				m_sPlayer[i].nCard[CardType][0] ++;
				m_sPlayer[i].nCard[CardType][m_sPlayer[i].nCard[CardType][0]] = nTempCard;
			}
			else
			{
				CCLOG("发牌错误，出现未定义类型的牌");
			}
		}
		m_sPlayer[i].nLen = 13;
		
		//对玩家i手中的牌进行排序
		for(int k=WAN; k<=DRAGON; k++)
		{
			ListSort(&m_sPlayer[i].nCard[k][1], m_sPlayer[i].nCard[k][0]);
		}
	}
	
	//给庄家发第14张牌
	m_sPlayer[m_nChairBanker].nCardTakenNow = m_nCardBuf[m_nCountAllot++];
    
    CCLOG("DealAllCardEx done");
    
}

void CGameLogical::DealAllCardTest(int iNomi, int iDeNomi)
{
	BYTE nTempCard = 255;
	WashCard();
    
    //发特定牌 测试抢杠
    
    DealTestCard(0, CardIndex[TIAO][5]);		//1
	DealTestCard(0, CardIndex[TIAO][5]);		//2
	DealTestCard(0, CardIndex[TIAO][5]);		//3
	DealTestCard(0, CardIndex[TIAO][6]);		//4
	DealTestCard(0, CardIndex[TIAO][6]);		//5
	DealTestCard(0, CardIndex[TIAO][6]);		//6
	DealTestCard(0, CardIndex[TIAO][7]);		//7
	DealTestCard(0, CardIndex[TIAO][7]);		//8
	DealTestCard(0, CardIndex[TONG][1]);		//9
	DealTestCard(0, CardIndex[TONG][2]);		//10
	DealTestCard(0, CardIndex[TONG][3]);		//11
	DealTestCard(0, CardIndex[TONG][5]);		//12
	DealTestCard(0, CardIndex[TONG][5]);		//13
    
    ResetCardBuf();
    
    m_sPlayer[0].nLen = 13;
    if (m_nCountAllot != 13)
    {
		CCLOG("DealAllCardTest error, chair[0], len:%d, allot:%d", m_sPlayer[0].nLen, m_nCountAllot);
    }   

    DealTestCard(1, CardIndex[WAN][1]);		//1
	DealTestCard(1, CardIndex[WAN][1]);		//2
	DealTestCard(1, CardIndex[WAN][2]);		//3
	DealTestCard(1, CardIndex[WAN][2]);		//4
	DealTestCard(1, CardIndex[WAN][3]);		//5
	DealTestCard(1, CardIndex[WAN][3]);		//6
	DealTestCard(1, CardIndex[WAN][4]);		//7
	DealTestCard(1, CardIndex[WAN][4]);		//8
	DealTestCard(1, CardIndex[WAN][4]);		//9
	DealTestCard(1, CardIndex[WAN][6]);		//10
	DealTestCard(1, CardIndex[WAN][7]);		//11
	DealTestCard(1, CardIndex[WAN][9]);		//12
	DealTestCard(1, CardIndex[WAN][1]);		//13
	ResetCardBuf();
    
	m_sPlayer[1].nLen = 13;
    if (m_nCountAllot != 26)
    {
		CCLOG("DealAllCardTest error, chair[1], len:%d, allot:%d", m_sPlayer[1].nLen, m_nCountAllot);
    }
    
	DealTestCard(2, CardIndex[TONG][1]);		//1
	DealTestCard(2, CardIndex[TONG][2]);		//2
	DealTestCard(2, CardIndex[TONG][3]);		//3
	DealTestCard(2, CardIndex[TONG][4]);		//4
	DealTestCard(2, CardIndex[TONG][5]);		//5
	DealTestCard(2, CardIndex[TONG][6]);		//6
	DealTestCard(2, CardIndex[TONG][7]);		//7
	DealTestCard(2, CardIndex[TONG][7]);		//8
	DealTestCard(2, CardIndex[TIAO][1]);		//9
	DealTestCard(2, CardIndex[TIAO][2]);		//10
	DealTestCard(2, CardIndex[TIAO][8]);		//11
	DealTestCard(2, CardIndex[TIAO][9]);		//12
	DealTestCard(2, CardIndex[WAN][9]);		//13
	ResetCardBuf();
    
	m_sPlayer[2].nLen = 13;
    if (m_nCountAllot != 39)
    {
		CCLOG("DealAllCardTest error, chair[1], len:%d, allot:%d", m_sPlayer[1].nLen, m_nCountAllot);
    }

    DealTestCard(3, CardIndex[WAN][1]);		//1
	DealTestCard(3, CardIndex[WAN][2]);		//2
	DealTestCard(3, CardIndex[WAN][5]);		//3
	DealTestCard(3, CardIndex[WAN][5]);		//4
	DealTestCard(3, CardIndex[WAN][7]);		//5
	DealTestCard(3, CardIndex[WAN][8]);		//6
	DealTestCard(3, CardIndex[WAN][9]);		//7
	DealTestCard(3, CardIndex[TIAO][2]);		//8
	DealTestCard(3, CardIndex[TIAO][2]);		//9
	DealTestCard(3, CardIndex[TIAO][2]);		//10
	DealTestCard(3, CardIndex[TIAO][3]);		//11
	DealTestCard(3, CardIndex[TIAO][3]);		//12
	DealTestCard(3, CardIndex[TIAO][9]);		//13
	ResetCardBuf();
    
	m_sPlayer[3].nLen = 13;
    if (m_nCountAllot != 52)
    {
		CCLOG("DealAllCardTest error, chair[1], len:%d, allot:%d", m_sPlayer[1].nLen, m_nCountAllot);
    }
    
    
//	for (int i=0; i<HOLD_CARD_NUM; ++i)
//	{
//		DealTestCard(1, m_nCardBuf[m_nCountAllot]);
//	}
//    
//    m_sPlayer[1].nLen = 13;
//    if (m_nCountAllot != 26)
//    {
//		CCLOG("DealAllCardTest error, chair[2], len:%d, allot:%d", m_sPlayer[2].nLen, m_nCountAllot);
//    }
//    
//    for (int i=0; i<HOLD_CARD_NUM; ++i)
//	{
//		DealTestCard(2, m_nCardBuf[m_nCountAllot]);
//	}
//    
//    m_sPlayer[2].nLen = 13;
//    if (m_nCountAllot != 39)
//    {
//		CCLOG("DealAllCardTest error, chair[3], len:%d, allot:%d", m_sPlayer[3].nLen, m_nCountAllot);
//    }
//    
//    
//	for (int i=0; i<HOLD_CARD_NUM; ++i)
//	{
//		DealTestCard(3, m_nCardBuf[m_nCountAllot]);
//	}
//    
//    m_sPlayer[3].nLen = 13;
//    if (m_nCountAllot != 52)
//    {
//		CCLOG("DealAllCardTest error, chair[2], len:%d, allot:%d", m_sPlayer[2].nLen, m_nCountAllot);
//    }
    
    
    BYTE cc = 15, index=52;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    }
    
    cc = 18, index=53;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    }
    cc = 11, index=54;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    }
    cc = 18, index=55;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    }
    cc = 15, index=56;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    }
    cc = 25, index=57;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    }
    cc = 4, index=58;
    if (m_nCardBuf[index] != cc ) {
        for (int q = index; q<108; q++) {
            if (m_nCardBuf[q] == cc) {
                m_nCardBuf[q] = m_nCardBuf[index];
                m_nCardBuf[index] = cc;
                break;
            }
        }
    }
    
	//给庄家发第14张牌
    
	m_sPlayer[m_nChairBanker].nCardTakenNow = m_nCardBuf[m_nCountAllot++];	
}
bool CGameLogical::DealTestCard(BYTE nChair, BYTE nCard)
{
	PAI_TYPE CardType = GetCardType(nCard);
	if(PAI_TYPE_INVALID == CardType)
	{
		CCLOG("错误的牌类型，发生在DealTestCard");
		return false;
	}
	ListInsert(m_sPlayer[nChair].nCard[CardType], nCard);
	m_nCountAllot++;
	return true;
}
void CGameLogical::ResetCardBuf()
{
	//重新调整牌堆
    BYTE p=0;
    for (int n = 0; n<PLAYER_COUNT; n++) 
	{
        for (int i=WAN; i<=TONG; i++) 
		{
            for (int j=1; j<=m_sPlayer[n].nCard[i][0]; j++) 
			{
                if (m_sPlayer[n].nCard[i][j] != 255) 
				{
					if (m_sPlayer[n].nCard[i][j] != m_nCardBuf[p++]) 
					{
						for (int q = p; q<CARD_NUM; q++) 
						{
                            if (m_sPlayer[n].nCard[i][j] == m_nCardBuf[q]) 
							{
                                m_nCardBuf[q] = m_nCardBuf[p-1];
                                m_nCardBuf[p-1] = m_sPlayer[n].nCard[i][j];
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}
bool CGameLogical::DealAllotCard(BYTE nCard, BYTE index)
{
	if (index>=CARD_NUM)
	{
		CCLOG("index overlap, %d", index);
		return false;
	}
	//发测试牌摸牌
    if (m_nCardBuf[index] != nCard ) 
	{
        for (int i = m_nCountAllot; i<CARD_NUM; i++) {
            if (m_nCardBuf[i] == nCard) 
			{
                m_nCardBuf[i] = m_nCardBuf[index];
                m_nCardBuf[index] = nCard;
                return true;
            }
        }
    }
	return false;
}

void CGameLogical::InformResultMsg()
{
	return;
//	char szMsg[512];
//	DWORD dwUserID = -1;
//    
//	for(UINT i=0; i<PLAYER_COUNT; i++)
//	{
//		switch(m_HuCurt[i].nState) {
//            case ZI_MO:					//自摸
//			{
//				if(IsYBGame())
//				{
//					sprintf(szMsg,"恭喜，您自摸了，共赢得金币%d", m_wSetGold[i]); 
//				}
//				else
//				{
//					sprintf(szMsg,"恭喜，您自摸了，共赢得分数%d", m_wSetScore[i]); 
//				}
//                //				dwUserID = //--m_pSite->GetUserID(i);
//                //				//--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szMsg);
//				SendSysMsgToUser(i, szMsg);
//                
//				BOOL bHaveBaoPai = FALSE;
//				for(UINT j=0; j<PLAYER_COUNT; j++)
//				{
//					if(j == i)
//					{
//						continue;
//					}
//					if(m_HuCurt[j].nState != NOTHING)
//					{
//						bHaveBaoPai = TRUE;
//						break;
//					}
//				}
//				if(bHaveBaoPai == FALSE)
//				{
//					for(UINT j=0; j<PLAYER_COUNT; j++)
//					{
//						if(j == i)
//						{
//							continue;
//						}
//						if(IsYBGame())
//						{
//							sprintf(szMsg,"很不幸，您被自摸了，共输金币%d", 0-m_wSetGold[j]); 
//						}
//						else
//						{
//							sprintf(szMsg,"很不幸，您被自摸了，共输分数%d", 0-m_wSetScore[j]); 
//						}
//                        //						dwUserID = //--m_pSite->GetUserID(j);
//                        //						//--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szMsg);
//						SendSysMsgToUser(j, szMsg);
//                        
//					}
//				}
//				break;
//			}
//            case CHI_PAO:				//吃炮
//			{
//				if(IsYBGame())
//				{
//					sprintf(szMsg,"恭喜，您吃炮了，共赢得金币%d", m_wSetGold[i]); 
//				}
//				else
//				{
//					sprintf(szMsg,"恭喜，您吃炮了，共赢得分数%d", m_wSetScore[i]); 
//				}
//                //				dwUserID = //--m_pSite->GetUserID(i);
//                //				//--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szMsg);
//				SendSysMsgToUser(i, szMsg);
//                
//				break;
//			}
//            case FANG_PAO:				//放炮
//			{
//				if(IsYBGame())
//				{
//					sprintf(szMsg,"很不幸，您放炮了，共输金币%d", 0-m_wSetGold[i]); 
//				}
//				else
//				{
//					sprintf(szMsg,"很不幸，您放炮了，共输分数%d", 0-m_wSetScore[i]); 
//				}
//                //				dwUserID = //--m_pSite->GetUserID(i);
//                //				//--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szMsg);
//				SendSysMsgToUser(i, szMsg);
//                
//				break;
//			}
//            case BAOPAI_QIANGGANG:		//抢杠包牌
//            //case BAOPAI_SHIER:			//十二张包牌
//            //case BAOPAI_JIU:			//九张包牌
//			{
//				if(IsYBGame())
//				{
//					sprintf(szMsg,"很不幸，您包牌了，共输金币%d", 0-m_wSetGold[i]); 
//				}
//				else
//				{
//					sprintf(szMsg,"很不幸，您包牌了，共输分数%d", 0-m_wSetScore[i]); 
//				}
//                //				dwUserID = //--m_pSite->GetUserID(i);
//                //				//--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, dwUserID, szMsg);
//				SendSysMsgToUser(i, szMsg);
//                
//				break;
//			}
//                
//		}
//	}
    
}

BOOL CGameLogical::SendSysMsgToUser(BYTE nChair, LPCSTR lpszMsg)
{
//	CFrameUserInfoHelper user;
//	if(!//--m_pSite->GetPlayerByChair(nChair,&user.pUser))
//	{
//		return FALSE;
//	}
//	//--m_pSite->SendSysMsgToClient(SCO_SINGLE_PLAYER, user.pUser->GetUserID(), lpszMsg);
//	//--m_pSite->SendSysMsgToClient(SCO_ALL_MY_LOOKON, user.pUser->GetUserID(), lpszMsg);
	
	return TRUE;
}

///cai v3.1
void CGameLogical::HandleSetOver()
{
	m_sysPhase = PhaseSetOver;
	//m_sOutedCard.clear();
	
	//Close the expire timer
	//m_pSite ->KillTimer(TIME_ID_EXPIRE);
	
	if (m_nEndReason == REASON_HU)
	{
///paddy//		ScoreNormalCalAndWrite(); //正常算分，此时无逃跑得失相等
        CalcHuScore(); //正常算分，此时无逃跑得失相等
		InformResultMsg();		  //通知输赢消息
	}
	else if (m_nEndReason==REASON_NOCARD)
	{
		m_nCardLast = m_nCardBuf[CARD_NUM-1];
		CalcNoCardScore();
        
	}
	else if(m_nEndReason == REASON_FLEE)		//逃跑结算游戏
	{
		CalcFleeScore();
	}
	else
	{
		CCLOG("Unknow end reason: %d", m_nEndReason);
	}
    
    
    // 	if (m_bBloodyGame || m_nChairDianPao >= PLAYER_COUNT)	//血战模式或无点炮者，庄家随机掷骰
    // 	{
    // 		m_pSite->SRand(GetTickCount());
    // 		m_nChairBanker = m_pSite->Rand()%PLAYER_COUNT;
    // 	}
    // 	else							//普通场点炮玩家坐庄
    // 	{
    // 		m_nChairBanker = m_nChairDianPao;
    // 	}
    
	m_nChairBanker = m_nChairDianPao;
    
//	//需处理比赛的逃跑
//	if ( IsMatchServer() )	// 这里判断是否结束
//	{
//		CalIsMatchStop();
//	}
    
	// 通过判断状态来确定赢家不能为负分－－add by chiyan80 修改一炮双响赢家得负分的BUG
	for(int j = 0; j < PLAYER_COUNT; j++)
	{
		// 假如是赢家，但是分数小于零，改之
		if(m_sPlayer[j].nState == CHI_PAO && m_wSetScore[j] < 0)
		{
			m_wSetScore[j] = -m_wSetScore[j];
			for(int k = 0; k < PLAYER_COUNT; k++)
			{
				if(m_sPlayer[k].nState == FANG_PAO)
				{
					m_wSetScore[k] -= m_wSetScore[j];
				}
			}
		}
	}
	
    WriteScore();
	//--m_pSite->NotifySceneChanged();
}

void CGameLogical::WriteScore()
{
    for(int i = 0; i < PLAYER_COUNT; i++)
	{
		m_wTotalScore[i] = m_Score[i].lScore;
	}
}

bool CGameLogical::OnIsNetChessAcademy()
{
	return false;
}
bool CGameLogical::OnGetAcademyLevelScoreBuf(LPSTR lpszScoreBuf/*out*/,DWORD dwMaxLen)
{
	return false;
}
bool CGameLogical::OnGetAcademyLevelDesc(LPSTR lpszDescBuf/*out*/,DWORD dwMaxLen)
{
	return false;
}

void CGameLogical::OnWriteUBReturn(DWORD dwSequenceID,BOOL bSucceeded)
{
    
}

BOOL CGameLogical::OnMatchCheckStart()
{
	return FALSE;
}

BOOL CGameLogical::OnInit(bool is_DingQue, bool is_3Fan, bool is_ZimoFan, GuaFengXiaYu is_enGFXY)
{
    CCLOG("OnInit()运行了");
    
	//--DWORD dwRule = //--m_pSite->GetGameOption();
	
    //--Todo
	m_bBloodyGame			= true;
	m_enGFXY				= is_enGFXY;
	m_bFast					= true;
	m_b3Fan					= is_3Fan;
	m_bDingQue				= is_DingQue;
	m_bZimoFan				= is_ZimoFan;
    
	static bool bCCLOGd = false;
	if (!bCCLOGd)
	{
		CCLOG("游戏场：%s, 快牌：%s, 三番起胡：%s, 定缺：%s, 自摸加底：%s, 刮风下雨：%s", 
              m_bBloodyGame? "血战场": "普通场",
              m_bFast?"yes":"no", 
              m_b3Fan?"yes":"no",
              m_bDingQue?"yes":"no",
              m_bZimoFan?"yes":"no",
              m_enGFXY == GFXYJiaJiaYou? "家家有": "承包制");
		bCCLOGd = true;
	}
    
	if (m_b3Fan)
	{
		m_nMinFan = 3;
	}
	else
	{
		m_nMinFan = 1;
	}
	
	return TRUE;
}

void CGameLogical::SetHuList(BYTE chair)
{
	BYTE n = 0;
	PAI_TYPE nCardType = PAI_TYPE_INVALID;
	
	memset(m_nHuList[chair], 0, sizeof(m_nHuList[chair]));
	for(BYTE card=0; card<NUM_ALL_TYPE; card++)
	{
		nCardType = GetCardType(card);
		if(PAI_TYPE_INVALID == nCardType)
		{
			CCLOG("card error in SetHulist" );
			return;
		}
		ListInsert(m_sPlayer[chair].nCard[nCardType], card);
		
		BOOL bCanHu = FALSE;
//		if(!Judge32(chair))	//该函数会处理好“将”	
//		{
//			if(JudgeQiQiaoDui(chair))  //判断七巧对
//			{
//				bCanHu = TRUE;
//			}
//		}
//		else
//		{
//			bCanHu = TRUE;
//		}
        if (JudgeHu(chair)) {
            bCanHu = TRUE;
        }
		if(bCanHu)
		{
			n++;
			m_nHuList[chair][n] = card;
		}
		
		m_HuCurt[chair].clear();
		
		ListDelete(m_sPlayer[chair].nCard[nCardType], card);
	}
	m_nHuList[chair][0] = n;
}

/// cai v2.1
BYTE CGameLogical::JudgeDajiao( BYTE chair )
{
	PLAYER_DATA tmpPlayer;
	memcpy(&tmpPlayer, &m_sPlayer[chair], sizeof(PLAYER_DATA));
	BYTE nMaxFan = 0;
    
	if (m_sPlayer[chair].nCardTakenNow != 255)
	{
		PAI_TYPE CardType = GetCardType(m_sPlayer[chair].nCardTakenNow);
		if(PAI_TYPE_INVALID == CardType)
		{
			CCLOG("错误的牌类型，发生在JudgeDajiao1");
			return 0;
		}
		ListInsert(m_sPlayer[chair].nCard[CardType], m_sPlayer[chair].nCardTakenNow); //整理完毕
        ///		m_sPlayer[chair].nCardTakenNow = 255;
        
		for (int i = WAN; i<=TONG; ++i)
		{
			for (int j = 1; j <= m_sPlayer[chair].nCard[i][0]; ++j)
			{	
				if (j>1 && m_sPlayer[chair].nCard[i][j] == m_sPlayer[chair].nCard[i][j-1])
				{
					continue;
				}
                
				BYTE tmpCard = m_sPlayer[chair].nCard[i][j];
				ListDelete(m_sPlayer[chair].nCard[i],m_sPlayer[chair].nCard[i][j]);
                
				SetHuList(chair);
				BYTE nHuCount = m_nHuList[chair][0];
                
				if (nHuCount == 0 )
				{
					ListInsert(m_sPlayer[chair].nCard[i], tmpCard);
					continue;
				}
                
				for (int k = 1; k<=nHuCount; ++k)
				{
					BYTE nTempCard = m_nHuList[chair][k];
					PAI_TYPE CardType = GetCardType(nTempCard);
					if(PAI_TYPE_INVALID == CardType)
					{
						CCLOG("错误的牌类型，发生在JudgeDajiao2");
						return 0;
					}
					ListInsert(m_sPlayer[chair].nCard[CardType], nTempCard);
					//1,判断胡
					if(JudgeHu(chair))	
					{
						BYTE nFan = JudgeFan(chair);
						nMaxFan = nFan>nMaxFan? nFan: nMaxFan;
					}
					ListDelete(m_sPlayer[chair].nCard[CardType], nTempCard);
				}
				ListInsert(m_sPlayer[chair].nCard[i], tmpCard);
			}
		}
        
		ListDelete(m_sPlayer[chair].nCard[CardType], m_sPlayer[chair].nCardTakenNow);
	}
	else
	{
		SetHuList(chair);
		BYTE nHuCount = m_nHuList[chair][0];
		if (nHuCount == 0)
		{
			return 0;
		}
		
		for (int i = 1; i<=nHuCount; ++i)
		{
			BYTE nTempCard = m_nHuList[chair][i];
			PAI_TYPE CardType = GetCardType(nTempCard);
			if(PAI_TYPE_INVALID == CardType)
			{
				CCLOG("错误的牌类型，发生在JudgeDajiao3");
				return 0;
			}
			ListInsert(m_sPlayer[chair].nCard[CardType], nTempCard);
			//1,判断胡
			if(JudgeHu(chair))	
			{
				BYTE nFan = JudgeFan(chair);
				nMaxFan = nFan>nMaxFan? nFan: nMaxFan;
			}
            m_HuCurt[chair].clear();
			ListDelete(m_sPlayer[chair].nCard[CardType], nTempCard);
		}
	}
	
	return nMaxFan;
}


/// cai v2.1
void CGameLogical::ScoreFleeBloodCal()
{
	BYTE nFleeChair = 255;
	int i;
    
	for(i=0; i<PLAYER_COUNT; ++i)
	{
		m_nDajiaoFan[i] = 0;
        
		if (m_bFlee[i] && m_sPlayer[i].nState != BLOOD_HU)      //paddy add
		{
			nFleeChair = i;
			if (m_nCountAllot > CARD_NUM-4)
			{
				m_sPlayer[i].nState = DAJIAO;
				m_nCountDajiao++;
			}
			continue;
		}
        
		if (m_sPlayer[i].nState != BLOOD_HU)
		{
			m_HuCurt[i].nState = NOTHING;
            
		}
		
		if (m_nCountAllot > CARD_NUM-4 )	//查大叫
		{
			if (m_sPlayer[i].nState != BLOOD_HU)
			{
				m_nDajiaoFan[i] = JudgeDajiao(i);
				if (m_nDajiaoFan[i]>0)
				{
                    ///					m_sPlayer[i].nState = DAJIAO_HU;
					m_HuCurt[i].nState = HU_DA_JIAO;
					m_nNumFan[i] = m_nDajiaoFan[i];
				}
				else
				{
					m_HuCurt[i].nState = NOTHING;
					m_nCountDajiao++;
				}
			}
		}
	}
	
	if (nFleeChair == 255)
	{
		CCLOG("flee chair error");
		return;
	}
	CCLOG("flee chair: %d", nFleeChair);
    
    //paddy add 刮风下雨退分结算修改
    
	for(i=0; i<4; i++)
	{
        ///		if(!m_bFlee[i] && m_sPlayer[i].nState==DAJIAO_HU)
		if(!m_bFlee[i])
		{
			if (m_HuCurt[i].nState == HU_DA_JIAO)
			{
                // 				m_wDaJiaoScore[i] += SCORE_BASE*m_nDajiaoFan[i];		
                // 				m_wDaJiaoScore[nFleeChair] -= m_wDaJiaoScore[i];
                
				long lScore = SCORE_BASE*(1<<(m_nDajiaoFan[i]-1));
				m_wDaJiaoScore[i] += lScore;		
				m_wDaJiaoScore[nFleeChair] -= lScore;
			}
            
			if (!m_bFlee[i] || m_sPlayer[i].nState == BLOOD_HU)
            {
                if (m_wGangScore[nFleeChair][i] > 0)		//退回刮风下雨分
                {
                    m_wGangScore[nFleeChair][nFleeChair] -= m_wGangScore[nFleeChair][i];
                    m_wGangScore[i][i] += m_wGangScore[nFleeChair][i];
                    
                    m_wGangScore[nFleeChair][i] = 0;
                }
            }
		}
		m_Score[i].lScore = m_wDaJiaoScore[i] + m_wSetScore[i] + m_wSetLoseScore[i]
        + m_wGangScore[i][i] + m_wHuaZhuScore[i];
	}
    
	m_Score[nFleeChair].lScore = m_wDaJiaoScore[nFleeChair] - SCORE_FLEE_MUL*SCORE_BASE*3
    + m_wSetScore[nFleeChair] + m_wSetLoseScore[nFleeChair] + m_wGangScore[nFleeChair][nFleeChair] + m_wHuaZhuScore[nFleeChair];
	m_Score[nFleeChair].lSetCount = 1;
	m_Score[nFleeChair].lFleeCount = 1;
    
	m_Score[nFleeChair].lLoseCount = 1;
}


///cai v2.1	流局结算，查花猪查大叫
void CGameLogical::CalcNoCardScore()
{
	//	Score_Struct score[PLAYER_COUNT];
    int i;
	for(i=0; i<PLAYER_COUNT; i++)
	{
		//m_Score[i].clear();
		memset(&m_Score[i],0,sizeof(Score_Struct));
	}
	
	if (!m_bBloodyGame)
	{
		ScoreNoCardNormalCal();
	}
	else
	{
		ScoreNoCardBloodCal();
	}
    
	for(i=0; i<PLAYER_COUNT; i++)
	{
		m_Score[i].lScore = m_wSetScore[i] + m_wSetLoseScore[i] + m_wHuaZhuScore[i] + m_wDaJiaoScore[i] + m_wZimoFanScore[i] + m_wGangScore[i][i];
		m_Score[i].lSetCount = 1;
        
        if (m_Score[i].lScore>0)
		{
			m_Score[i].lWinCount = 1;
		}
		else if (m_Score[i].lScore<0)
		{
			m_Score[i].lLoseCount = 1;
		}
		else
		{
			m_Score[i].lDrawCount = 1;
		}
	}
}


/// cai v2.1
void CGameLogical::ScoreNoCardNormalCal()
{
    ///	BYTE nCountHuaZhu = 0;
    ///	BYTE nCountDaJiao = 0;
    
	int i, j;
	for (i=0; i<PLAYER_COUNT; ++i)
	{
		if (JudgeHuaZhu(i))
		{
			m_sPlayer[i].nState = HUAZHU;
			m_nCountHuaZhu++;
		}
		else
		{
			m_nDajiaoFan[i] = JudgeDajiao(i);
			if (m_nDajiaoFan[i] ==0)
			{
				m_sPlayer[i].nState = DAJIAO;
				m_nCountDajiao++;
			}
			else
			{
                ///				m_sPlayer[i].nState = DAJIAO_HU;
				m_HuCurt[i].nState = HU_DA_JIAO;
			}
		}
	}
	
	if (m_nCountHuaZhu == PLAYER_COUNT)
	{
		for (i=0; i<PLAYER_COUNT; ++i)
		{
			m_HuCurt[i].nState = NOTHING;
		}
		return;
	}
    
	for (i=0; i<PLAYER_COUNT; ++i)
	{
		if (m_nCountHuaZhu>0)
		{
			if (m_sPlayer[i].nState == HUAZHU)
			{
				m_wHuaZhuScore[i] -= SCORE_BASE*16*(PLAYER_COUNT-m_nCountHuaZhu);
			}
			else
			{
				m_wHuaZhuScore[i] += SCORE_BASE*16*m_nCountHuaZhu;
			}
		}
		
		if (m_nCountDajiao!=0 && m_nCountDajiao!=PLAYER_COUNT-m_nCountHuaZhu)
		{
            ///			if (m_sPlayer[i].nState == DAJIAO_HU )
			if(m_HuCurt[i].nState == HU_DA_JIAO)
			{
                // 				m_nNumFan[i] = m_nDajiaoFan[i];
                // 				m_wDaJiaoScore[i] += SCORE_BASE*m_nDajiaoFan[i]*m_nCountDajiao;
                
				m_nNumFan[i] = m_nDajiaoFan[i];
				long lScore = SCORE_BASE*(1<<(m_nDajiaoFan[i]-1));
				m_wDaJiaoScore[i] += lScore*m_nCountDajiao;
                
				for (j=0; j<PLAYER_COUNT; ++j)
				{
					if (m_sPlayer[j].nState == DAJIAO)
					{
						//m_wDaJiaoScore[j] -= SCORE_BASE*m_nDajiaoFan[i];
						m_wDaJiaoScore[j] -= lScore;
					}
				}
			}
            
            if (m_sPlayer[i].nState == DAJIAO)		//paddy add 退回刮风下雨分
			{
				for (j = 0; j<PLAYER_COUNT; ++j)
				{
					//退回刮风下雨
					if (j!=i && m_wGangScore[i][j] > 0)		//退回大叫玩家i赢玩家j的刮风下雨分
					{
						m_wGangScore[i][i] -= m_wGangScore[i][j];
						m_wGangScore[j][j] += m_wGangScore[i][j];
						
						m_wGangScore[i][j] = 0;
					}
				}
			}
		}
	}
}


/// cai v2.1
void CGameLogical::ScoreNoCardBloodCal()
{
    ///	BYTE nCountHuaZhu = 0;
    ///	BYTE nCountDaJiao = 0;
    ///	BYTE nCountHu = 0;
    ///	BYTE nCountFlee = 0;
    
	int i, j;
	for (i=0; i<PLAYER_COUNT; ++i)
	{
		if (m_sPlayer[i].nState == BLOOD_HU)
		{
            ///			nCountHu++;
			if (m_bFlee[i])
			{
				m_nCountFlee++;
			}
		}
		else if (JudgeHuaZhu(i))
		{
			m_sPlayer[i].nState = HUAZHU;
			m_nCountHuaZhu++;
		}
		else
		{
			m_nDajiaoFan[i] = JudgeDajiao(i);
			if (m_nDajiaoFan[i] ==0)
			{
				m_sPlayer[i].nState = DAJIAO;
				m_nCountDajiao++;
			}
			else
			{
                ///				m_sPlayer[i].nState = DAJIAO_HU;
				m_HuCurt[i].nState = HU_DA_JIAO;
			}
		}
	}
	
	if (m_nCountHuaZhu == PLAYER_COUNT)
	{
		for (i=0; i<PLAYER_COUNT; ++i)
		{
			m_HuCurt[i].nState = NOTHING;
		}
		return;
	}
	
	for (i=0; i<PLAYER_COUNT; ++i)
	{
		if (m_nCountHuaZhu>0)
		{
			if (m_sPlayer[i].nState == HUAZHU)
			{
				m_wHuaZhuScore[i] -= SCORE_BASE*16*(PLAYER_COUNT-m_nCountHuaZhu-m_nCountFlee);
			}
			else if(!m_bFlee[i])
			{
				m_wHuaZhuScore[i] += SCORE_BASE*16*m_nCountHuaZhu;
			}
		}
		
		if (m_nCountDajiao!=0 && m_nCountDajiao!=PLAYER_COUNT-m_nCountHuaZhu-m_nCountHu)
		{
			if (m_HuCurt[i].nState == HU_DA_JIAO)
			{
                // 				m_nNumFan[i] = m_nDajiaoFan[i];
                // 				m_wDaJiaoScore[i] += SCORE_BASE*m_nDajiaoFan[i]*m_nCountDajiao;
                
				m_nNumFan[i] = m_nDajiaoFan[i];
				long lScore = SCORE_BASE*(1<<(m_nDajiaoFan[i]-1));
				m_wDaJiaoScore[i] += lScore*m_nCountDajiao;
                
				for (j=0; j<PLAYER_COUNT; ++j)
				{
					if (m_sPlayer[j].nState == DAJIAO)
					{
						//m_wDaJiaoScore[j] -= SCORE_BASE*m_nDajiaoFan[i];
						m_wDaJiaoScore[j] -= lScore;
					}
				}
			}
            
            if (m_sPlayer[i].nState == DAJIAO)		//paddy add 退回刮风下雨分
			{
				for (j = 0; j<PLAYER_COUNT; ++j)
				{
					//退回刮风下雨
					if (j!=i && m_wGangScore[i][j] > 0)		//退回大叫玩家i赢玩家j的刮风下雨分
					{
						m_wGangScore[i][i] -= m_wGangScore[i][j];
						m_wGangScore[j][j] += m_wGangScore[i][j];
						
						m_wGangScore[i][j] = 0;
					}
				}
			}
		}
	}
}


//返回玩家数据
PLAYER_DATA *   CGameLogical::GetPlayerData()
{
    return m_sPlayer;
}

//返回牌堆
BYTE        *   CGameLogical::GetCardBuf()
{
    return m_nCardBuf;
}

//返回玩家倒牌
STAND_CARD 	*   CGameLogical::GetStandCard()
{
    return m_sStandCard;
}

//返回指定玩家命令缓存
bool        *   CGameLogical::GetChooseBuf(BYTE chair)
{
    return m_bChooseBuf[chair];
}

// 返回玩家定缺信息
DING_QUE    * CGameLogical::GetDingQue(){
	return m_sDingQue;
}

//获取玩家的桌面牌
BYTE * CGameLogical::GetTableCards(BYTE chair){
    return m_nTableCards[chair];
}

//获取玩家的桌面牌数量
BYTE CGameLogical::GetNumTableCards(BYTE chair){
    return m_nNumTableCards[chair];
}

//获取玩家的桌面牌
BYTE * CGameLogical::GetHuList(BYTE chair){
	return m_nHuList[chair];	
}

//获取该局的分数
Score_Struct * CGameLogical::GetScore(){
    return m_Score;
}

//获取胡牌状态
HU_CURT * CGameLogical::GetHuCurt(){
    return m_HuCurt;
}

//获取番数
BYTE * CGameLogical::GetNumFan(){
    return m_nNumFan;
}
// 刮风下雨分数
long * CGameLogical::GetGangScore(){
    for (int i=0; i<4; i++) {
        m_wGangScoreOne[i]= m_wGangScore[i][i];
    }
	return m_wGangScoreOne;
}
long * CGameLogical::GetHuaZhuScore(){ 
	return m_wHuaZhuScore;
}
long * CGameLogical::GetDaJiaoScore(){ 
	return m_wDaJiaoScore;
}
long * CGameLogical::GetSetWinScore(){
	return m_wSetScore;
}

// 游戏结束原因
BYTE CGameLogical::GetEndReason(){
    return m_nEndReason;
}









