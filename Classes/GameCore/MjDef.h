#ifndef xzdd_MjDef_h
#define xzdd_MjDef_h

#include "TypeDef.h"
#include "cocos2d.h"

#define PLAYER_COUNT		4		// 4个玩家

///cai	#define CARD_NUM			136		// 牌的个数,万条筒共108张 + 字牌 28张
#define CARD_NUM			108		// 牌的个数,万条筒共108张

#define HOLD_CARD_NUM		13      // 开始时手持牌的数量,庄家除外

///cai	#define NUM_ALL_TYPE		34		// 所有类型牌的个数
#define NUM_ALL_TYPE		27		// 所有类型牌的个数

#define MAX_MATCH_FLEE_COUNT	3

#define MAX_WIN_LOSE_METHOD		16

#define MAX_TIME_OUT_COUNT		1

///cai v2.1
const WORD SCORE_BASE = 6;					// 基数分
const WORD SCORE_FLEE_MUL = 16;	    // 逃跑分

const WORD SCORE_ZHA_HU = 96;	// 诈胡分
const WORD SCORE_FLEE = 96;	    // 逃跑分
const WORD MATCH_FLEE_BASE_PUNISH_SCORE = 60; //比赛逃跑局分

const BYTE MAX_FAN  = 9;
const long COIN_MUL = 1000; // const long COIN_MUL = 1   lyp


//－－－－－－－－－－－－－状态 －－－－－－－－－－－－－－－－－－－

//阶段状态
enum SYSTEMPHASE 
{
    PhaseWaitingStart       = 1,		// 用户进入而又没开始的状态
    PhaseThinkingOutCard	= 2,		// 思考打牌阶段
    PhaseChoosing			= 3, 		// 竞争抉择阶段,有碰,杠,胡时的抉择
    PhaseSetOver			= 4,		// 结束阶段
    PhaseInvalid 			= 255,		// 非法阶段，还没有开始
    ///cai
    PhaseDingQue			= 5			// 定缺阶段
};


//玩家状态	cai v2.1
enum PLAYER_STATUS
{
    WAITING					= 0,
    THINK_OUTCARD			= 1,
    CHOOSING				= 2,
    BLOOD_HU				= 3,
    HUAZHU					= 4,
    DAJIAO					= 5,
    
    ///		DAJIAO_HU				= 6,
    ///		BLOOD_HU_ESCAPE			= 4,
    
    PLAYER_STATUS_INVALIDE				= 255
};


// 结束原因	cai v3.1
enum END_REASON
{
    REASON_FLEE			= 1,
    REASON_HU			= 2,
    REASON_NOCARD		= 3
    ///		REASON_FLEE_BLOOD	= 4,
    ///		REASON_HU_BLOOD		= 5,
    ///		REASON_NOCARD_BLOOD = 6
};


//－－－－－－－－－－－－－状态 OVER－－－－－－－－－－－－－－－－－


//－－－－－－－－－－－－玩家数据－－－－－－－－－－－－－－－－－－－－－－－－－－
struct PLAYER_DATA
{
	BYTE	nState;			//玩家状态
	BYTE	nLen;			//手拿多少张牌,不包括nCardTakenNow;
	BYTE	nCardTakenNow;	//0-27表示拿到那张牌的id，如果吃碰杠了，则是第14张牌
	BYTE 	nCard[5][15];	//存放4种牌型的数组,cCardes[0][0]:万字牌数,1:条子,2:筒子
	BYTE    bSeenOutCard; //能否看到出的牌，在竞争选择时候用
	void clear() 
	{
		nState = WAITING;
		nLen = 0;
		nCardTakenNow = 255;
		memset(nCard, -1, sizeof(nCard));
		nCard[0][0] = 0;
		nCard[1][0] = 0;
		nCard[2][0] = 0;
		nCard[3][0] = 0;
		nCard[4][0] = 0;
        
		bSeenOutCard = 1;
	}
};

//－－－－－－－－－－－－玩家数据 OVER－－－－－－－－－－－－－－－－－－－－－－


//－－－－－－－－－－－－－ 消息 －－－－－－－－－－－－－－－－－－－

//客户端发来的消息
#define CLIENT_READY		30		//软开始命令
#define CLIENT_OUTCARD		31		//出牌命令
#define CLIENT_CANCEL		32		//取消命令
//#define CLIENT_EAT			33		//吃命令
#define CLIENT_PENG			34		//碰命令
#define CLIENT_ZHIGANG	35		//不可抢杠的明杠命令
#define CLIENT_ANGANG		36		//暗杠命令
#define CLIENT_WANGANG		37		//可抢杠的明杠命令
#define CLIENT_HU			38		//胡命令

#define CLIENT_DINGQUE		39
#define CLIENT_RULE         40      //从服务器获取Rule
#define CLIENT_TIME_OUT		41


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

#define SEV_DINGQUE			60

#define SEV_RULE			61
#define SEV_TIME_OUT		62
#define SEV_DINGQUE_INFO	63

#define SEV_CASINO_OPT      64
#define SEV_NORMAL_OPT      65


//－－－－－－－－－－－－－－消息 OVER －－－－－－－－－－－－－－－－－－－－


//－－－－－－－－－－－－－－胡牌－－－－－－－－－－－－－－－－－－－－－－－

//判断胡的返回类型	cai v1.1
enum HU_RETURN_TYPE
{
    OK_PINGHU			= 1,	// 1 平胡
    
    OK_PENGPENGHU		= 2,	// 2 碰碰胡
    
    OK_QINGYISE			= 3,	// 3 清一色
    OK_YAOJIU			= 4,	// 4 幺九
    OK_QIDUI				= 5,	// 5 七对
    
    OK_QING_PENG			= 6,	// 6 清碰
    OK_JIANG_PENG		= 7,	// 7 将碰
    OK_LONG_QIDUI		= 8,	// 8 龙七对
    
    OK_QING_QIDUI		= 9,	// 9 清七对
    OK_QING_YAOJIU		= 10,	// 10清幺九
    
    OK_QINGLONG_QIDUI	= 11,	// 11青龙七对
    
    FALSE_ALL            = 0		 //FALSE, 什么都不是
};


///cai v1.1
enum HU_TYPE
{
    PINGHU			= 21,	// 1 平胡		1番
    
    PENGPENGHU		= 22,	// 2 碰碰胡		2番
    
    QINGYISE		= 23,	// 3 清一色		3番
    YAOJIU			= 24,	// 4 幺九		3番
    QIDUI			= 25,	// 5 七对		3番
    
    QING_PENG		= 26,	// 6 清碰		4番
    JIANG_PENG		= 27,	// 7 将碰		4番
    LONG_QIDUI		= 28,	// 8 龙七对		4番
    
    QING_QIDUI		= 29,	// 9 清七对		5番
    QING_YAOJIU		= 30,	// 10清幺九		5番
    
    QINGLONG_QIDUI	= 31,	// 11青龙七对	6番
    
    FENGDING_TYPE_INVALID   = 20	//错误
};

//附加	cai v2.1
enum ATTACHED_HU
{		
    TIANHU					= 41,	 //1 天胡		6番
    DIHU					= 42,	 //2 地胡		6番
    RENHU					= 43,	 //3 人和		6番
    ZIMOFAN					= 44,	 //4 自摸加番	1番
    
    GANGKAI					= 45,	 //5 杠开		1番
    GANGPAO					= 46,	 //6 杠炮		1番
    QIANGGANG				= 47,	 //7 抢杠		1番
    GEN						= 48,	 //8 根（杠）	1番
    GANG					= 49	//9 杠加番
};

///	cai v2.1
struct HU_CURT
{
    BYTE nState;
	BYTE nCard;
	BYTE nType;
	BYTE nCount;
	BYTE nMethod[10];
	
	BYTE nGainChair[4];
	
    ///	BYTE nLoseMethod[MAX_WIN_LOSE_METHOD+1];
    
    /// cai add
    ///	bool bHu;
	
	void clear()
	{
		nState = 0;					//事不关己状态
		nCard = 255;
		nType = 255;
		nCount = 0;
        memset(nMethod, 0, sizeof(nMethod));
		memset(nGainChair, 0, sizeof(nGainChair));
        ///		memset(nLoseMethod, 0, sizeof(nLoseMethod));
	}
    
	void AddHU(BYTE _nMethod)
	{
		nMethod[nCount] = _nMethod;
		nCount++;
	}
    /*
     void AddLose(BYTE _nMethod)
     {
     nLoseMethod[0]++;
     if (nLoseMethod[0]>MAX_WIN_LOSE_METHOD)
     {
     Trace("数组越界, in HU_CURT::AddLose");
     return;
     }
     nLoseMethod[nLoseMethod[0]] = _nMethod;
     }
     */
};

//玩家终局时输赢状态
///cai v2.1
enum WIN_STATUS
{
    NOTHING				= 0,	//事不关己
    ZI_MO				= 1,	//自摸
    CHI_PAO				= 2,	//吃炮
    HU_DA_JIAO			= 3     //胡大叫
};

//玩家终局时输赢状态
///cai v2.1
enum LOSE_STATUS
{
    FANG_PAO			= 6,	//放炮
    BAOPAI_QIANGGANG	= 7,	//抢杠包牌
    ///		HUA_ZHU				= 8,	//花猪
    ///		DA_JIAO_LOSE		= 9		//大叫输
};


//－－－－－－－－－－－－－－－－胡牌 OVER －－－－－－－－－－－－－－－－－－－


//－－－－－－－－－－－ 牌的类型－－－－－－－－－－－－－－－－－－－－－－－－－

//牌
#define CARD_TYPE_NUM		3		// 类型的个数	
enum PAI_TYPE
{
    WAN		= 0,
    TIAO	= 1,
    TONG	= 2,
    FENG	= 3,
    DRAGON	= 4,
    PAI_TYPE_INVALID = 255
};	

//倒牌的类型	cai v1.1
#define		SHUN			 0 	//顺子
#define		KE				 1 	//刻
#define		MGANG_COME		 2 	//别人打给我地明杠
#define		ANGANG			 3 	//暗杠
#define		MGANG_MYSELF	 4	//先碰再自己摸到第二种明杠


//桌面牌
struct STAND_CARD	
{
	BYTE nNum;						// 倒牌数
	BYTE nType[5];					// 顺，刻，明杠，暗杠 //类型
	BYTE nWhoGiveMe[5];				// 谁打给我上的
	BYTE nCard[5];					// 被上的牌
	BYTE nFirstCard[5];				// 牌型的第一张牌
	void clear()
	{
		memset(this, 0, sizeof(STAND_CARD));
		memset(this->nCard, -1, 5);
		memset(this->nFirstCard, -1, 5);
	}
};

//出牌
struct OUTED_CARD
{
	BYTE nChair;	//谁打出的
	BYTE nCard;		//是什么牌
	
	void clear()
	{
		nChair = 255;
		nCard  =  255;
	}
};

//杠
struct QIANG_GANG
{
	bool mark;
	BYTE card;
	BYTE chair;
	
	void InitData(bool _mark, BYTE _card, BYTE _chair)
	{
		mark = _mark;
		card = _card;
		chair = _chair;
	}
	void clear()
	{
		mark = false;
		card = 255;
		chair = 255;
	}
};


//杠炮 cai v2.1
struct GANG_PAO
{
	bool mark;
	BYTE card;
	BYTE chair;
	BYTE type;
	BYTE score;
	
	void InitData(bool _mark, BYTE _card, BYTE _chair, BYTE _type, BYTE _score)
	{
		mark = _mark;
		card = _card;
		chair = _chair;
		type = _type;
		score = _score;
	}
	void clear()
	{
		mark = false;
		card = 255;
		chair = 255;
		type = 255;
		score = 255;
	}
};


//杠
struct GangMine_SUIT
{
	BYTE nNum;		// 有几个杠
	BYTE card[5];		// 杠的牌
	BYTE type[5];	// 是暗杠,还是可胡明杠
	void clear()
	{
		nNum = 0;
		memset(card, -1, 5);
		memset(type, 0, 5);
	}
};

//吃牌的结构
struct EAT_SUIT
{
	BYTE nNum;		// 有几种吃法
	BYTE nCard[3][3];	// 第i种吃法3张牌
	EAT_SUIT() 
	{
		nNum = 0;
		memset(nCard, -1, sizeof(EAT_SUIT));
	}
};

///<cai
//定缺结构
struct DING_QUE
{
	bool bRecv;			// 是否收到客户端定缺消息
	BYTE nCardType;		// 定缺牌型
	void Clear() 
	{
		bRecv = false;
		nCardType = 255;
	}
};

struct CASINO_OPTION
{
	BYTE nRule;
	BYTE nMinFan;
    
	bool bPreventCheatRoom;
    
	long lCashBase;
	long lCashMin;
	long lCashMax;
	long lCashFee;
    
	CASINO_OPTION()
	{
		nRule		= 0;
		nMinFan		= 1;
        
		bPreventCheatRoom = false;
        
		lCashBase	= 0;
		lCashMin	= 0;
		lCashMax	= 0;
		lCashFee	= 0;
	}
};

struct NORMAL_OPTION
{
	BYTE nRule;
	BYTE nMinFan;
	
	
	UINT uScoreBase;
    
	NORMAL_OPTION()
	{
		nRule		= 0;
		nMinFan		= 1;
        
		uScoreBase	= 1;
	}
};

///cai>

//－－－－－－－－－－－ 牌的类型 OVER－－－－－－－－－－－－－－－－－－－－－－－－－


// －－－－－－－－－－－－－时钟－－－－－－－－－－－－－－－－－－－－－－－－－

// 显示出牌的时钟
#define TIME_ID_EXPIRE	50
const DWORD TIME_EXPIRE	=	180000; //三分钟
// －－－－－－－－－－－－－时钟 OVER－－－－－－－－－－－－－－－－－－－－－－－－－


#define DOWN_LORD_ADDRESS	"http://web.chinagames.net/mygames/download/Setup-MJSC.exe"

//－－－－－－－－－－－ Game Client－－－－－－－－－－－－－－－－－－－－－－－－－
//胡牌状态
enum eHUSTATE
{
	LOST	= 1,
	WASTE	= 2,
	WIN		= 3
    
};

#endif
