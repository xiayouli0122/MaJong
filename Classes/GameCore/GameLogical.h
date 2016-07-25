//
//  GameLogical.h
//  xzdd
//
//  Created by  on 12-2-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameLogical_h
#define xzdd_GameLogical_h

#include "MjDef.h"
#include "ServerFrameDefs.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "RuleDef.h"

#else 

#include "RuleGen/RuleDef.h"

#endif


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MIN_GOLD_MUTIPLE 128
//海底胡和抢杠胡 12/10分 都是在大胡的基础上加分的。
const WORD SCORE_DADAHU_MORE = 20;           //海底胡多算的分，（共10分，如果是点/吃炮的是庄家，为12分）
const WORD SCORE_DADAHU_BANKER_MORE = 10;
static BYTE CardIndex[3][10];

struct tagServerOption;

class CGameLogical
{	
private:
    ///cai
    BYTE m_nChairTA;
	BYTE m_nChairDianPao;				// 点炮玩家椅子号
	BYTE m_nCountHu;
	BYTE m_nCountFlee;
	BYTE m_nCountHuaZhu;
	BYTE m_nCountDajiao;
	bool m_bChairHu[PLAYER_COUNT];		// 血战已胡玩家
    BYTE m_nGen[PLAYER_COUNT];
    
    bool m_bMaxFan;
    
    //	BYTE m_nDingQue[PLAYER_COUNT];		// 定缺状态
	DING_QUE	m_sDingQue[PLAYER_COUNT];	// 定缺状态
    

	BYTE m_nCountChangeBanker;			// 换庄次数

    
	bool m_bSeen;                        //是否可见
	bool m_bTianRenHu;					// 用以判断地天人胡
	BYTE m_nDiHu[4];					// 判断地胡
	bool m_bMenQing[4];					// 判断门清
	
	BYTE m_nEndReason;					// 游戏结束原因
    
	QIANG_GANG m_sQiangGang;			// 处理抢杠
	GANG_PAO	m_sGangPao;				// 处理杠炮
	bool m_bHaveGang;                   // 处理杠开
    
	long m_wHuaZhuScore[4];				// 分数
	long m_wDaJiaoScore[4];				// 分数
	long m_wZimoFanScore[4];			// 分数
	long m_wGangScore[4][4];			// 分数
    long m_wGangScoreOne[4];			// 分数
	long m_wTotalScore[4];				// 该局的分数
    
    long m_wHuScore[4];					// 分数
	long m_wGFXYScore[4];
    
    // 	DWORD m_dwUserID[4][10];			// 玩家ID, m_dwUserID[i][0] 为玩家 
    // 										// m_dwUserID[i][1]为旁观者数目
    // 										// 其他为旁观者ID，最大有8个旁观者
    
	//数据区
	BYTE 		m_nTableCards[4][32];		// 4个玩家的桌面牌
	STAND_CARD 	m_sStandCard[4];			// 玩家倒牌

	PLAYER_DATA	m_sPlayer[4];				// 玩家私有数据
	BYTE		m_nNumCheat[4];				// 玩家i诈胡次数
	BYTE		m_nNumFan[4];				// 赢家的番数
	long		m_wSetScore[4];				// 该局的牌面分数
	long		m_wSetLoseScore[4];			// 该局的牌面分数
	long		m_wSetGold[4];				// 该局的金币数
	long		m_wSetTax[4];				// 该局的税收
	BYTE		m_nHuTypeCurt[4];			// 简略的胡牌的类型(小胡,大胡,大胡番倍)
	BYTE		m_nHuTypeDetailed[4];		// 详细的胡牌类型(天胡, 地胡, 碰碰胡.......)
	BYTE		m_nCardLast;				// 海底牌
	
	//逃跑
	BYTE        m_bFlee[PLAYER_COUNT];  
    BYTE        m_nSetCount;
    
    BYTE		m_nDajiaoFan[PLAYER_COUNT];
    
	//处理命令
	EAT_SUIT	m_sEat;						// 存放吃牌信息
	GangMine_SUIT	m_sCanGang;				// 存放可以杠的牌的信息
	bool		m_bChooseBuf[4][4];			// 4个玩家的胡,吃,碰,不可胡明杠命令
	BYTE		m_nNumCmdHu;				// 胡命令的个数
	BYTE		m_chairHu[3];				// 发出胡命令的玩家
	BYTE		m_chairSendCmd;				// 当前发命令的玩家

    
	// 接收客户端数据
	BYTE		m_nJiang[4];				// 判断胡牌的将,不能胡时将为255;
	BYTE 		m_nHuList[4][30];			// 胡牌列表, m_nHuCList[4][0]: 可胡牌的个数
	BYTE		m_nHuGiveUp[4][10];			// 该轮放弃胡的牌,m_nHuGiveUp[4][0]: 个数
	BYTE		m_nEatBuf[3];				// 客户端选择吃的三张牌
	
	// 与客户端无关
	BYTE		m_nCardBuf[140];			// 牌的缓冲区
    
	// 金币游戏
	BYTE m_bIsCasinoGame;	// 是不是金币游戏
	BYTE m_bSupportNego;		// 是否支持协商
	int  m_nMinGold;		// 进入游戏所需的最小金币
	int  m_nAnte;			// 赌注
	int	 m_nDefAnte;        //备份默认赌注
    
	//比赛相关
	BYTE m_bIsMatchGame;
	BYTE m_bIsMatchOver;
    
	//胡牌
    HU_CURT m_HuCurt[4];
    ///cai	bool m_bMissHu[4];      //处理如果该轮错
    
	///cai 规则号相关
	BOOL m_bBloodyGame;		//游戏模式
	GuaFengXiaYu m_enGFXY;	//刮风下雨
	BOOL m_bFast;			//快牌
	BOOL m_bZimoFan;		//自摸加番
	BOOL m_b3Fan;			//三番起胡
    
	//分数
	Score_Struct m_Score[PLAYER_COUNT];
    
	BOOL m_bPreventCheatRoom;	//add by mxs 
    
private:	
	//--IServerFrame * m_pSite; 
	tagServerOption * m_pServerOption;
    
    /************************************************************************/
    /*                               函数区                                 */
    /************************************************************************/
    
public:
    
    //初始化和发牌
	void InitData();
	void InitRawData();
	void DealAllCard();
	bool DealCard(BYTE nChair);
	
    //胡牌列表
	void InitHuList(BYTE chair);						// 初始化胡牌列表
	bool IsInHuList(BYTE chair, BYTE card);				// 判断牌card在不在胡牌列表中
    
    //牌链表操作
	void ListInsert(BYTE *buf, BYTE card);	// 插入牌
	void ListDelete(BYTE *buf, BYTE card);		// 删除牌
	BYTE ListFind(BYTE *buf, BYTE card);		// 查找牌，返回个数
	void ListSort(BYTE *buf, BYTE n);
    
	BYTE ListJudgePengPeng(BYTE * s, BYTE &nJiang);		//把"刻"从牌列表中分离,判断此牌是全3型(return 1), 3+2型(return 2)或其他(return 0)
	BYTE ListJudgeNormal32(BYTE *s, BYTE &nJiang);		//判断此牌是全3型(return 1), 3+2型(return 2)或其他(return 0)
	bool ListJudgeDui(BYTE *s);						//判断牌列表中是不是只有对
    bool ListJudgeYaoJiu(BYTE *s);					//判断列表中幺九牌
    //判断辅助函数
	bool Judge32(BYTE chair);					//判断手持牌能不能构成3 + 2
	bool IsShunInStandCards(BYTE chair);		//判断倒牌中有没有顺
    
    //判断操作函数
    ///cai	bool FindEat(BYTE chair);			//判断有没有吃牌
	bool FindPeng(BYTE chair);			//判断有没有碰
	bool FindAnGang(BYTE chair);		//判断有没有暗杠
	bool FindWanGang(BYTE chair);	//判断有没有别人打来的明杠
	bool FindMingGangCome(BYTE chair);	//判断有没有自己摸的明杠
	
    //判断胡牌函数	
    ///cai
	bool JudgeQueYimen(BYTE nChair);
	bool JudgeHuaZhu(BYTE chair);
	void SceneStatusToPhasePlaying();
	void HandleDingQue(BYTE nChair, BYTE nCardType);
    
	bool JudgeHu(BYTE chair);
	BYTE JudgeFan(BYTE chair);
    
	BYTE JudgeHuType(BYTE chair);       //判断超胡
//	BYTE JudgeYaoJiuHu(BYTE chair, bool bJudgeShiSanYao = false); //判断么九 包括十三么，清么九，混么九 
	
	bool JudgePingHu(BYTE chair);		//判断平  胡	1
	bool JudgePengPengHu(BYTE chair);   //判断碰碰胡	3
///cai	bool JudgeHunYiSe(BYTE chair);		//判断混一色	3
	bool JudgeQingYiSe(BYTE chair);		//判断清一色	5
	bool JudgeZiYiSe(BYTE chair);		//判断字一色	8
	
	bool JudgeQiQiaoDui(BYTE chair);	//判断七巧对   保留
	BYTE JudgeGen(BYTE chair);			//判断根
	bool JudgeYaoJiuHu(BYTE chair);		 //判断么九
	bool Judge258(BYTE chair);		 //判断将258
    
    BYTE JudgeDajiao(BYTE chair);
    
	void SetHuList(BYTE chair);    
    
    //命令处理函数
	void HandleChooseEat(BYTE nChair, LPCVOID lpData, int nSize);
	void HandleChoosePeng(BYTE nChair, LPCVOID lpData, int nSize);
	void HandleChooseAnGang(BYTE nChair, LPCVOID lpData, int nSize);
	void HandleChooseMingGangM(BYTE nChair, LPCVOID lpData, int nSize);
	void HandleChooseMingGangC(BYTE nChair, LPCVOID lpData, int nSize);	
    
	void HandleChooseResult();										 // 处理玩家选择的结果
    
	void HandleHuZiMo(BYTE nChair, LPCVOID lpData, int nSize);		 //处理自摸
	void HandleZhaHu(BYTE nChair);                                     //处理诈胡
	
	void HandleOutCard(BYTE nChair, LPCVOID lpData, int nSize);		 //处理出牌
    void HandleOutCard(BYTE nChair, BYTE pos);                      //处理出牌
    
	void HandleMatchNoStart();			//处理比赛时间到没有开始
    
    //其他
	BYTE ChairTo(BYTE i, BYTE j);		// 玩家i相对于玩家j的位置,如(0,3),返回1(即下家)
	BYTE AntiClock(BYTE chair);			// 返回chair逆时针转1的玩家
    
	PAI_TYPE GetCardType(BYTE nCard);	// 返回牌的类型
	int GetCardValue(BYTE nCard);		// 返回牌地值
	BYTE GetSanYuanNum(BYTE chair);     // 得到三元的数目
	BYTE GetSiXiNum(BYTE chair, BYTE* pCardSiXi = NULL);		// 得到四喜的数目
    
	bool Is258(BYTE card);				// 判断card的value是不是2,5,8之一
	bool IsYaoJiu(BYTE card);			// 是否么九牌
	bool IsYaoQi(BYTE card);			// 是否么7牌    
    bool IsZiPai(BYTE card);			//是否字牌
    bool IsFeng(BYTE card);				//是否风牌
	bool IsDragon(BYTE card);			//是否龙牌
	bool Is456(BYTE card);
	void ClearChooseBuf(BYTE nChair, bool bClearGang = true); //清除命令缓冲区
    
	BOOL IsValidChair(BYTE nChair);
    
	void HandleSetOver();
    
    void WriteScore();
    
    //算分以及写分
///paddy//	void ScoreNormalCalAndWrite(); //正常胡写分
    void CalcHuScore(); //正常胡算分
	void CalcFleeScore(); //逃跑算分
    void CalcNoCardScore(); //流局算分
    
	void ScoreFleeNormalCal(); //普通逃跑算分
	void ScoreFleeBloodCal(); //血战逃跑算分
    
	bool ScoreFleeYBCal(Score_Struct score[PLAYER_COUNT]);//金币逃跑算分
	void ScoreFleeMatchCal(Score_Struct scores[PLAYER_COUNT]); //比赛逃跑算分
    
    void ScoreNoCardNormalCal(); //普通流局算分
	void ScoreNoCardBloodCal(); //血战流局算分
    
	bool ScoreOneHuCal(BYTE nWinChair, BYTE nLostChair = 255);
    
	void InformResultMsg();
	BOOL SendSysMsgToUser(BYTE nChair, LPCSTR lpszMsg);
    
    //金币相关
//	BOOL CalSetCoinScore();
//	__inline bool IsYBGame()
//	{	
//		if ( m_pServerOption->dwMatchType > 0 )	//如果是比赛服务器，则禁止金币功能
//			return FALSE;
//		return TRUE == m_pServerOption->bCasinoGame;
//	}
//	BOOL InforCoinNum(BYTE nSrcChair, BYTE nDestChair);
    
//	BOOL InformCoinChairToID(BYTE nSrcChair, DWORD dwUserID);
//	BOOL InformCoinChairToChair(BYTE nSrcChair, BYTE nDestChair, BOOL bIncludeLooker=TRUE);
    
    //比赛相关
    void CalIsMatchStop();
	bool IsTooManyFlee(Score_Struct *pScore[PLAYER_COUNT],int nSetCount,long lFleeCounts[PLAYER_COUNT]);
    void BroadcastMatchScores(int nSetCount,Score_Struct *pScore[PLAYER_COUNT]);
//	__inline bool IsMatchServer()	{	return m_pServerOption->dwMatchType > 0;	}
    void SendOneByteMsg(char cmd ,BYTE data,DWORD dwUserID = INVALID_FRAME_USER_ID);
	
	
    //接口函数	
public:
	CGameLogical();
	virtual ~CGameLogical();
    
    // IGameLogicalSink
public:	
	virtual CHECK_START_MODE  OnGetCheckStartMode();
	virtual BOOL  OnGetChairScene(unsigned char nChair/*in*/,BOOL bSeenSecretData/*in*/,
                                         BOOL bNeedWholeScene/*in*/,int nUserCurrentVersion/*in*/,SCENE * pScene/*out*/,DWORD dwFlag = 0);
	virtual void  OnGetServerVersionScope(VERSION_STRUCT * version/*out*/);
	virtual LOOKON_OPTION  OnGetLookOnOption();
	virtual BOOL  OnInit(tagServerOption * pServerOption);
	virtual BOOL  OnSceneStatusToPlaying(int iNomi, int iDeNomi);
	virtual void  OnSceneStatusToFree(BOOL bFled[MAX_CHAIR],int nCondition = 0,DWORD dwReserved = 0);
	virtual void  OnGameMessage(unsigned char nChair/*in*/, 
                                       int nCmdID/*in*/, LPCVOID lpData/*in*/, int nSize/*in*/);
	virtual void  OnTimer(DWORD dwEventID);
	virtual void  OnTableStatusToPlaying();
//	virtual void  OnUserExit(int nChair,DWORD dwUserID,BOOL bIsPlayer,BOOL bLeftAtPlaying = FALSE);
	virtual void  OnUserEnter(int nChair,DWORD dwUserID,BOOL bIsPlayer);
	virtual void  OnPlayerOffline(int nChair,DWORD dwUserID);
	virtual void  OnPlayerReplay(int nChair,DWORD dwUserID);
	virtual bool  OnPlayerReady(int nChair,DWORD dwUserID);
	virtual void  OnSentence(int nWinIndex,DWORD dwReserved);
	virtual BOOL  OnIsCasinoGame(DWORD& dwMinCashNeeded);
//	virtual HRESULT  OnmeMatchStop(UINT uStopReason);
	virtual BOOL  OnIsOneScoreInOneSet();
//  virtual BOOL  OnIsPlayerNotEnoughGold(DWORD dwUserID,long lGold,BOOL& bNeedKick,BOOL & bCancelDefMsgBox);
	virtual BOOL  OnIsSupportGameConcept();
	virtual BOOL  OnGameStatusToPlaying();
	virtual BOOL  OnGameStatusToFree();
	virtual BOOL  OnGetOldScoreBuffer(LPSTR lpszBuffer,int& nSize);
	virtual void  Release();
//	virtual int  OnGetClientScoreType();
	virtual BOOL  OnIsSupportNegotiateDismiss(DWORD& dwLeastAdvocater/*out*/);
	virtual BOOL  OnGetMatchSetContext(LPSTR lpszBuffer/*out*/,int& nDataLen/*in/out*/);
	virtual int	 OnGetTableOpChair();
//	virtual BOOL  OnGetDefaultGameRule(LPVOID lpGameRule/*out*/,UINT& nDataLen/*in/out*/);
//    virtual BOOL  OnGetGameRule(LPVOID lpGameRule/*out*/,UINT& nDataLen/*in/out*/);
//    virtual void  OnGameRuleChanged(LPCVOID lpGameRule,UINT nLen);
    virtual void  OnSetGameRuleCanceled();
//  virtual void  OnClientVersion(DWORD dwUserID,int nChair,BOOL bIsPlayer,DWORD dwMainVersion,DWORD dwSubVersion) ;	
	virtual BOOL  OnGetCreateClientMethod(DWORD& dwMethodID,LPSTR lpszFileName);
//	virtual BOOL  OnCheckClientVersion(GameLogic_DownloadInfo & downloadInfo,DWORD dwMainVersion,DWORD dwSubVersion,LPCVOID lpExtInfo,UINT uLen);
    virtual BOOL  OnPlayerLookonStateChanged(int nChair,DWORD dwDestID,BOOL bEnable);
    
    
	virtual bool  OnIsNetChessAcademy();
	virtual bool  OnGetAcademyLevelScoreBuf(LPSTR lpszScoreBuf/*out*/,DWORD dwMaxLen);
	virtual bool  OnGetAcademyLevelDesc(LPSTR lpszDescBuf/*out*/,DWORD dwMaxLen);
	virtual void  OnWriteUBReturn(DWORD dwSequenceID,BOOL bSucceeded);
	virtual BOOL  OnMatchCheckStart();
//	virtual UINT  OnDispatch(DWORD dwReserved1 = 0,DWORD dwReserved2 = 0,DWORD dwReserved3 = 0);
    
    
    //调试使用
	typedef BYTE (CGameLogical::*TABuidFuc)();
#define MAX_TA_BULID_FUNC 20
	TABuidFuc BuildTA[MAX_TA_BULID_FUNC];
	int m_iTAFuncCount;
	BYTE	m_TArray[HOLD_CARD_NUM];
	char	m_szTALevel[16];
    
	BYTE	TAHunYaoJiu();		
	BYTE	TASanYuan();
	BYTE	TASiXi();
    
    BYTE    TAQingYiSe();		//1 清一色特征牌
    
	BYTE	TAYaoJiu();			//2 幺九特征牌
	BYTE	TAQiDui();			//3 七对特征牌
    
	BYTE	TAQingPeng();		//4 清碰特征牌
	BYTE	TAJiangPeng();		//5 将碰特征牌
	BYTE	TALongQiDui();		//6 龙七对特征牌
    
	BYTE	TAQingQiDui();		//7 清七对特征牌
	BYTE	TAQingYaJiu();		//8 清幺九特征牌
    
	BYTE	TAQingLongQiDui();	//9 清龙七对特征牌
    
    bool	CheckTACard(BYTE ArrayBase[], const int iBaseCount);
    
	void ResetTACardBuf(BYTE nTACount);
	BOOL ReplaceCardFromBuf(BYTE* pBuf, int nLength, BYTE nPreCard, 
                            BYTE nByCard, BOOL bOnlyOnce = TRUE);
	void WashCard(BYTE nTACount = 0, BYTE nTAChair = 255);
	void DealAllCardEx(int iNomi, int iDeNomi);
    
	void DealAllCardBySet(int iNomi, int iDeNomi);  // 发特定牌
    void DealAllCardTest(int iNomi, int iDeNomi);
    bool DealTestCard(BYTE nChair, BYTE nCard);
    void ResetCardBuf();
    bool DealAllotCard(BYTE nCard, BYTE nIndex);
    
    
    /************************************************************************/
    /*                               新加及修改For Mobile                     */
    /************************************************************************/
    
    
public:
    void *  UIDelegate;
    //获取数据
    PLAYER_DATA *   GetPlayerData();
    BYTE        *   GetCardBuf();       //获取牌的缓存区
    STAND_CARD 	*   GetStandCard();		//获取玩家倒牌
    bool        *   GetChooseBuf(BYTE chair);     //获取指定玩家命令缓存
    BYTE        *   GetTableCards(BYTE chair);    //获取4个玩家的桌面牌
    BYTE            m_nNumTableCards[4];		// 4个玩家的桌面牌的数量

    
    //结算数据
    Score_Struct *  GetScore();   // 该局的分数
    HU_CURT     *   GetHuCurt();  //获取胡牌状态
    BYTE        *   GetNumFan();  //获取番数 
    long        *   GetGangScore(); // 刮风下雨分数
    long        *   GetHuaZhuScore();
    long        *   GetDaJiaoScore();
    BYTE            GetEndReason();					// 游戏结束原因
    long        *   GetSetWinScore();
    
    
    BOOL m_bDingQue;                //定缺
	DING_QUE	*   GetDingQue();	// 定缺状态
    
    //private to public
    BYTE m_nChairBanker;				// 庄家的位置，
	BYTE m_nCountAllot;					// 发到第几张牌
	OUTED_CARD	m_sOutedCard;			// 刚打出的牌	
    SYSTEMPHASE m_sysPhase;				// 当前阶段状态
    BYTE m_chairCurrentPlayer;			// 当前出牌者
    BYTE		m_currentCmd;			// 当前的命令
    BYTE m_nMinFan;                     //起胡番数
    
    BOOL OnInit(bool is_DingQue, bool is_3Fan, bool is_ZimoFan, GuaFengXiaYu is_enGFXY);
    
    BYTE            GetNumTableCards(BYTE chair);   //获取玩家的桌面牌数量
	BYTE        *   GetHuList(BYTE chair);          //获取玩家的桌面牌
	
};

#endif