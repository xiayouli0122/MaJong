//
//  ClientMjDefs.h
//  xzdd
//
//  Created by  on 12-6-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_ClientMjDefs_h
#define xzdd_ClientMjDefs_h
#include "TypeDef.h"

#define PLAYER_COUNT		4		// 4个玩家

///cai	#define CARD_NUM			136		// 牌的个数,万条筒共108张 + 字牌 28 共 136
#define CARD_NUM			108		// 牌的个数,万条筒共108张 + 字牌 28 共 136

#define HOLD_CARD_NUM		13      // 开始时手持牌的数量,庄家除外

///cai	#define NUM_ALL_TYPE		34		// 所有类型牌的个数
#define NUM_ALL_TYPE		27		// 所有类型牌的个数
#define MAX_WIN_LOSE_METHOD		16
#define MAX_TIME_OUT_COUNT		1
///cai v2.1
#define CARD_TAKEN_NULL		255

#define CARD_SECRET			27      // 旁观者隐藏牌

///cai v2.1
//const WORD SCORE_BASE = 6;					// 基数分
//const WORD SCORE_FLEE_MUL = 16;	    // 逃跑分

//－－－－－－－－－－－－－状态 －－－－－－－－－－－－－－－－－－－

////阶段状态
//enum SYSTEMPHASE 
//{
//    PhaseWaitingStart       = 1,		// 用户进入而又没开始的状态
//    PhaseThinkingOutCard	= 2,		// 思考打牌阶段
//    PhaseChoosing			= 3, 		// 竞争抉择阶段,有碰,杠,胡时的抉择
//    PhaseSetOver			= 4,		// 结束阶段
//    PhaseInvalid 			= 255,		// 非法阶段，还没有开始
//    ///cai
//    PhaseDingQue			= 5			// 定缺阶段
//};
//
////玩家状态	cai v2.1
//enum PLAYER_STATUS
//{
//    WAITING					= 0,
//    THINK_OUTCARD			= 1,
//    CHOOSING				= 2,
//    BLOOD_HU				= 3,
//    HUAZHU					= 4,
//    DAJIAO					= 5,
//    
//    ///		DAJIAO_HU				= 6,
//    ///		BLOOD_HU_ESCAPE			= 4,
//    
//    PLAYER_STATUS_INVALIDE				= 255
//};
//
//
////胡牌状态
//enum eHUSTATE
//{
//	LOST	= 1,
//	WASTE	= 2,
//	WIN		= 3
//    
//};


//// 结束原因
//enum END_REASON
//{
//    REASON_FLEE			= 1,
//    REASON_HU			= 2,
//    REASON_NOCARD		= 3,
//    REASON_FLEE_BLOOD	= 4,
//    REASON_HU_BLOOD		= 5,
//    REASON_NOCARD_BLOOD = 6
//};
//
////－－－－－－－－－－－－－状态 OVER－－－－－－－－－－－－－－－－－
//
////－－－－－－－－－－－－玩家数据－－－－－－－－－－－－－－－－－－－－－－－－－－
//struct PLAYER_DATA
//{
//	BYTE	nState;			//玩家状态
//	BYTE	nLen;			//手拿多少张牌,不包括nCardTakenNow;
//	BYTE	nCardTakenNow;	//0-27表示拿到那张牌的id，如果吃碰杠了，则是第14张牌
//	BYTE 	nCard[5][15];	//存放4种牌型的数组,cCardes[0][0]:万字牌数,1:条子,2:筒子
//	BYTE    bSeenOutCard; //能否看到出的牌，在竞争选择时候用
//	void clear() 
//	{
//		nState = WAITING;
//		nLen = 0;
//		nCardTakenNow = 255;
//		memset(nCard, -1, sizeof(nCard));
//		nCard[0][0] = 0;
//		nCard[1][0] = 0;
//		nCard[2][0] = 0;
//		nCard[3][0] = 0;
//		nCard[4][0] = 0;
//		bSeenOutCard = 1;
//	}
//};
//－－－－－－－－－－－－玩家数据 OVER－－－－－－－－－－－－－－－－－－－－－－

//－－－－－－－－－－－－－ 消息 －－－－－－－－－－－－－－－－－－－
//客户端发来的命令
#define CLIENT_READY		30		//软开始命令
#define CLIENT_OUTCARD		31		//出牌命令
#define CLIENT_CANCEL		32		//取消命令
//#define CLIENT_EAT		33		//吃命令
#define CLIENT_PENG			34		//碰命令
#define CLIENT_ZHIGANG      35		//不可抢杠的明杠命令
#define CLIENT_ANGANG		36		//暗杠命令
#define CLIENT_WANGANG		37		//可抢杠的明杠命令
#define CLIENT_HU			38		//胡命令
///<cai
#define CLIENT_DINGQUE		39
#define CLIENT_RULE			40
#define CLIENT_TIME_OUT		41
///cai>

//服务器发来的消息
#define SEV_ZHA_HU			50		//诈胡信号
#define SEV_READY			51		//服务器发给客户端的开始信号
#define SEV_CASINOINFO		52		//金币信息
#define SEV_CASINONUM		53		//金币数目
#define SEV_NOTENOUGH_GOLD  54      //金币不足
#define SEV_ISMATCH         55     //是否比赛
#define SEV_ISMATCH_OVER    56     //是否比赛结束
#define SEV_ISMATCH_NOSTART 57     //比赛时间到，有人没有开始
#define SEV_MIN_FAN			58	   //起胡番数
#define SEV_PREVENT_CHEAT	59		//是否防作弊房间	add by mxs
///<cai
#define SEV_DINGQUE			60
#define SEV_RULE			61
#define SEV_TIME_OUT		62
#define SEV_DINGQUE_INFO	63
///cai>

//－－－－－－－－－－－－－－消息 OVER －－－－－－－－－－－－－－－－－－－－


//－－－－－－－－－－－－－－胡牌－－－－－－－－－－－－－－－－－－－－－－－

////判断胡的返回类型	cai v1.1
//enum HU_RETURN_TYPE
//{
//    OK_PINGHU			= 1,	// 1 平胡
//    
//    OK_PENGPENGHU		= 2,	// 2 碰碰胡
//    
//    OK_QINGYISE			= 3,	// 3 清一色
//    OK_YAOJIU			= 4,	// 4 幺九
//    OK_QIDUI				= 5,	// 5 七对
//    
//    OK_QING_PENG			= 6,	// 6 清碰
//    OK_JIANG_PENG		= 7,	// 7 将碰
//    OK_LONG_QIDUI		= 8,	// 8 龙七对
//    
//    OK_QING_QIDUI		= 9,	// 9 清七对
//    OK_QING_YAOJIU		= 10,	// 10清幺九
//    
//    OK_QINGLONG_QIDUI	= 11,	// 11青龙七对
//    
//    FALSE_ALL            = 0		 //FALSE, 什么都不是
//};
//
//
/////cai v1.1
//enum HU_TYPE
//{
//    PINGHU			= 21,	// 1 平胡		1番
//    
//    PENGPENGHU		= 22,	// 2 碰碰胡		2番
//    
//    QINGYISE		= 23,	// 3 清一色		3番
//    YAOJIU			= 24,	// 4 幺九		3番
//    QIDUI			= 25,	// 5 七对		3番
//    
//    QING_PENG		= 26,	// 6 清碰		4番
//    JIANG_PENG		= 27,	// 7 将碰		4番
//    LONG_QIDUI		= 28,	// 8 龙七对		4番
//    
//    QING_QIDUI		= 29,	// 9 清七对		5番
//    QING_YAOJIU		= 30,	// 10清幺九		5番
//    
//    QINGLONG_QIDUI	= 31,	// 11青龙七对	6番
//    
//    FENGDING_TYPE_INVALID   = 20	//错误
//};

////附加	cai v2.1
//enum ATTACHED_HU
//{		
//	TIANHU					= 41,	 //1 天胡		6番
//    DIHU					= 42,	 //2 地胡		6番
//    RENHU					= 43,	 //3 人和		6番
//    ZIMOFAN					= 44,	 //4 自摸加番	1番
//    
//    GANGKAI					= 45,	 //5 杠开		1番
//    GANGPAO					= 46,	 //6 杠炮		1番
//    QIANGGANG				= 47,	 //7 抢杠		1番
//    GEN						= 48,	 //8 根（杠）	1番
//    GANG					= 49	//9 杠加番
//};
//
//
/////	cai v2.1
//struct HU_CURT
//{
//    BYTE nState;
//	BYTE nCard;
//	BYTE nType;
//	BYTE nCount;
//	BYTE nMethod[10];
//    
//	BYTE nGainChair[4];
//	
//    ///	BYTE nLoseMethod[MAX_WIN_LOSE_METHOD+1];
//	
//	/// cai add
//	///	bool bHu;
//	
//	void clear()
//	{
//		nState = 0;					//事不关己状态
//		nCard = 255;
//		nType = 255;
//		nCount = 0;
//        memset(nMethod, 0, sizeof(nMethod));
//		memset(nGainChair, 0, sizeof(nGainChair));
//        ///		memset(nLoseMethod, 0, sizeof(nLoseMethod));
//	}
//	
//	void AddHU(BYTE _nMethod)
//	{
//		nMethod[nCount] = _nMethod;
//		nCount++;
//	}
//    /*	
//     void AddLose(BYTE _nMethod)
//     {
//     nLoseMethod[0]++;
//     if (nLoseMethod[0]>MAX_WIN_LOSE_METHOD)
//     {
//     Trace("数组越界, in HU_CURT::AddLose");
//     return;
//     }
//     nLoseMethod[nLoseMethod[0]] = _nMethod;
//     }
//     */
//};
//
////玩家终局时输赢状态
/////cai v2.1
//enum WIN_STATUS
//{
//    NOTHING				= 0,	//事不关己
//    ZI_MO				= 1,	//自摸
//    CHI_PAO				= 2,	//吃炮
//    HU_DA_JIAO			= 3
//    
//    ///		HUA_ZHU				= 3,
//    ///		DA_JIAO				= 4,	//大叫
//    ///		HU_DA_JIAO			= 5
//    
//	/*
//     NOTHING				= 0,	//事不关己
//     ZI_MO				= 1,	//自摸
//     CHI_PAO				= 2,	//吃炮
//     FANG_PAO			= 3,	//放炮
//     BAOPAI_QIANGGANG	= 4,	//抢杠包牌
//     HUA_ZHU				= 5,	//花猪
//     DA_JIAO_HU			= 6,	//大叫
//     DA_JIAO_LOSE		= 7		//大叫输
//     */
//};
//
////玩家终局时输赢状态
/////cai v2.1
//enum LOSE_STATUS
//{
//    FANG_PAO			= 6,	//放炮
//    BAOPAI_QIANGGANG	= 7,	//抢杠包牌
//    ///		HUA_ZHU				= 8,	//花猪
//    ///		DA_JIAO_LOSE		= 9		//大叫输
//};
//
//－－－－－－－－－－－－－－－－胡牌 OVER －－－－－－－－－－－－－－－－－－－


//－－－－－－－－－－－ －－－－－牌的类型－－－－－－－－－－－－－－－－－－－－
//牌
#define CARD_TYPE_NUM		3		// 类型的个数	
//enum PAI_TYPE
//{
//    WAN		= 0,
//    TIAO	= 1,
//    TONG	= 2,
//    FENG	= 3,
//    DRAGON	= 4,
//    PAI_TYPE_INVALID = 255
//};	

// 牌墙结构
struct WALL
{
	BYTE len;
	BYTE state[13];
};

//倒牌的类型
#define		SHUN			 0 	//顺子
#define		KE				 1 	//刻
#define		MGANG_COME		 2 	//别人打给我地明杠
#define		ANGANG			 3 	//暗杠
#define		MGANG_MYSELF	 4	//先碰再自己摸到第二种明杠

#define		SELECT_PENG		1
#define		SELECT_GANG		2
#define		SELECT_HU		3

////桌面牌
//struct STAND_CARD	
//{
//	BYTE nNum;						// 倒牌数
//	BYTE nType[5];					// 顺，刻，明杠，暗杠 //类型
//	BYTE nWhoGiveMe[5];				// 谁打给我上的
//	BYTE nCard[5];					// 被上的牌
//	BYTE nFirstCard[5];				// 牌型的第一张牌
//	void clear()
//	{
//		memset(this, 0, sizeof(STAND_CARD));
//		memset(this->nCard, -1, 5);
//		memset(this->nFirstCard, -1, 5);
//	}
//};
//
////出牌
//struct OUTED_CARD
//{
//	BYTE nChair;	//谁打出的
//	BYTE nCard;		//是什么牌
//	
//	void clear()
//	{
//		nChair = 255;
//		nCard  =  255;
//	}
//};
//
//
////杠
//struct GangMine_SUIT
//{
//	BYTE nNum;		// 有几个杠
//	BYTE card[5];		// 杠的牌
//	BYTE type[5];	// 是暗杠,还是可胡明杠
//	void clear()
//	{
//		nNum = 0;
//		memset(card, -1, 5);
//		memset(type, 0, 5);
//	}
//};
//
////吃牌的结构
//struct EAT_SUIT
//{
//	BYTE nNum;		// 有几种吃法
//	BYTE nCard[3][3];	// 第i种吃法3张牌
//	EAT_SUIT() 
//	{
//		nNum = 0;
//		memset(nCard, -1, sizeof(EAT_SUIT));
//	}
//};
//
/////<cai
////定缺结构
//struct DING_QUE
//{
//	bool bRecv;			// 是否收到客户端定缺消息
//	BYTE nCardType;		// 定缺牌型
//	void Clear() 
//	{
//		bRecv = false;
//		nCardType = 255;
//	}
//};
///cai>

//－－－－－－－－－－－ 牌的类型 OVER－－－－－－－－－－－－－－－－－－－－－－－－－


// －－－－－－－－－－－－－时钟－－－－－－－－－－－－－－－－－－－－－－－－－



#define TIME_ID_OUT_CARD		22				// 出牌时钟
const DWORD TIME_OUT_CARD		=	25000;

#define TIME_ID_CHOOSE			24				// 命令选择时钟
const DWORD TIME_CHOOSE			=	15000;		

#define TIME_ID_TIMER			25				// 显示计时时钟
const DWORD TIME_TIMER			=	1000;

#define TIME_ID_AUTO			26				// 代打时钟
const DWORD TIME_AUTO			=	1000;

#define TIME_ID_NEXT            27				//开始下一局的时钟
const DWORD TIME_NEXT           =    20000;		

#define TIME_ID_DING_QUE		28				// 命令选择时钟
const DWORD TIME_DING_QUE		=	10000;	

#define TIME_ID_READY			29				// 命令选择时钟
const DWORD TIME_READY			=	30000;			

#define TIME_ID_WAITING_OUT_CARD		30				// 出牌时钟

#define TIME_ID_ANI_EXCELLENT_MINE		40
#define TIME_ID_ANI_EXCELLENT_RIGHT		41
#define TIME_ID_ANI_EXCELLENT_TOP		42
#define TIME_ID_ANI_EXCELLENT_LEFT		43
const DWORD TIME_ANI_EXCELLENT			=	80;

#define TIME_ID_ANI_ZIMO_MINE			44
#define TIME_ID_ANI_ZIMO_RIGHT			45
#define TIME_ID_ANI_ZIMO_TOP			46
#define TIME_ID_ANI_ZIMO_LEFT			47
const DWORD TIME_ANI_ZIMO			=	200;

enum TIMER_PLACE	
{
    TIMER_PLACE_INVALID		= 0,
    TIMER_PLACE_OUTCARD		= 1,
    TIMER_PLACE_CHOOSE      = 2,
    TIMER_PLACE_OVER        = 3,
    TIMER_PLACE_DINGQUE		= 4,
    TIMER_PLACE_NEXT		= 5,
    TIMER_PLACE_READY		= 6
};

// －－－－－－－－－－－－－时钟 OVER－－－－－－－－－－－－－－－－－－－－－－－－－


// －－－－－－－－－－－－－ 控件－－－－－－－－－－－－－－－－－－－－－－－－－

enum BUTTON
{
	BUTTON_START            = 1,
	BUTTON_DAIDA_QUANHU     = 2,
	BUTTON_DAIDA_MOHU       = 3,
	BUTTON_SETCASINO        = 4,
	BUTTON_CHOOSE_CANCEL    = 5,
	BUTTON_CHOOSE_HU        = 6,
	BUTTON_INVALID          = 255
    ///<cai
	,
	BUTTON_QUE_WAN			= 7,
	BUTTON_QUE_TIAO			= 8,
	BUTTON_QUE_TONG			= 9,
	BUTTON_GANG_OK			= 10,
	BUTTON_HU_OK			= 11,
	BUTTON_AUTO				= 12,
	BUTTON_AUTO_CANCEL		= 13
    ///cai>
};
//选择框 
struct SSelectTable
{
	BYTE num;
	BYTE type[7];
	BYTE cardFirst[7];
	char name[7][3];
	
	void clear()
	{
		num = 0;
		memset(type, 0, 7);
		memset(cardFirst, -1, sizeof(cardFirst));
		memset(name, 0, sizeof(name));
	}
};

/*
 相对我的位置，以逆时针旋转
 */
enum RELATIVEPOSITION
{
    Myself	= 0,		// 我自己
    Right	= 1,		// 右手
    Up		= 2,		// 上面
    Left	= 3			// 左手
};
// －－－－－－－－－－－－－控件 OVER－－－－－－－－－－－－－－－－－－－－－－－－－


// －－－－－－－－－－－－－Game.h－－－－－－－－－－－－－－－－－－－－－－－－－
// 用户状态码
typedef enum tagGAME_PLAYER_STATE
{
	PlayerFree = 0,	// 玩家坐在桌子上
	PlayerReady,	// 玩家已经宣布开始，正等待其它人开始
	PlayerPlaying,	// 玩家已经开局
	PlayerOffLine,	// 玩家已经断线，正待他断线续玩，这时其它玩家不能离局，否则扣分
	PlayerLookOn	// 玩家正在旁观某人
}GAME_PLAYER_STATE;




#endif
