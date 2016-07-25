/******************************************************************
 ** 文件名:	ClientFrameDefs.h
 ** 版  权:	(c) 2003.12 深圳网域开发部
 ** 创建人:	husten
 ** 日  期:	2003.12
 ** 版  本:	1.0
 ** 描  述:	客户端框架的相关数据定义(提供给使用者)
 *******************************************************************/
#ifndef _CLIENTFRAMEDEFS_H__
#define _CLIENTFRAMEDEFS_H__
#include "TypeDef.h"
#include "ClientCommon.h"
#include "ClientScoreDefs.h"

struct ITrace;

#define MAX_PACKAGE_LEN		1024	// 最大的包

#ifndef MAX_PLAYER
#define MAX_PLAYER	6
#endif

//用户状态
#define STATUS_GETOUT					0			//离开了
#define STATUS_FREE						1			//在房间站立
#define STATUS_WAIT_SIT					2			//等待Server回应
#define STATUS_SIT						3			//坐在椅子上，没按开始
#define STATUS_READY					4			//同意游戏开始
#define STATUS_PLAYING					5			//正在玩
#define STATUS_OFFLINE					6			//断线等待续玩
#define STATUS_LOOKON					7			//旁观
#define STATUS_LOGGING					8			//正在登录
#define STATUS_NOT_LOGIN				9			//连接成功，尚未发登录包


enum RightViewType	// RightView的类型
{
	enRight,	// 右
	enBottom,	// 底
	enNone,		// 不显示RightView
	// 目前只能实现两种
};

struct RightViewInfo
{
	RightViewType enType;	// 类型
	DWORD dwIdealWidth;		// 初始化的宽度(高度)
	DWORD dwMinWidth;		// 最小宽度(高度)
	DWORD dwMaxWidth;		// 最大宽度
	BOOL bEnableHide;		// 是否支持隐藏
	RightViewInfo()
	{
		enType = enRight;
		DWORD dwIdealWidth = 0;
		dwMinWidth = 0;
		dwMaxWidth = 0;
		bEnableHide = TRUE;
	}
};

#define MAX_SCORE_FIELD_COUNT		5	//游戏成绩的最大栏数

// 用户信息,from old frame
#pragma pack(push)
#pragma pack(1)
typedef struct tagUSER_INFO
{
	WORD	wUserID;					// 玩家标识
	char	szUserName[MAX_NAME_LEN];	// 玩家名
	WORD	wFaceID;					// 玩家脸谱
	WORD	wNetTimelag;				// 网络延时
	char	cChair;						// 玩家所在的椅子号，范围为0到3有效
	int		nState;						// 玩家的状态
	
	// 积分
	long	lScoreBuf[MAX_SCORE_FIELD_COUNT];
    
	char	szLookOnUserName[MAX_NAME_LEN];// 当此玩家在旁观时，否则无此项
    
    
	inline BOOL IsValidUser()
	{
		return wUserID != INVALID_USER_ID && wUserID < MAX_USER_ID && cChair >= 0 && cChair < MAX_PLAYER;
	}
    
}USER_INFO;
#pragma pack(pop)

typedef struct tagUSER_EXT_INFO
{
	DWORD	dwPing;			// Ping的GetTickCount值，如果为0，表示没有使用
}USER_EXT_INFO;

//// 场景状态
//enum SCENE_STATUS	
//{
//	SCENE_STATUS_PLAYING = 0,
//	SCENE_STATUS_FREE,
//};
//
//
//struct VERSION_STRUCT 
//{
//	DWORD dwMainVersion;	// 主版本号
//	DWORD dwSubVersion;		// 次版本号
//	DWORD dwReserved;		// 保留
//	
//	VERSION_STRUCT()
//	{
//		dwMainVersion = -1;
//		dwSubVersion = -1;
//		dwReserved = -1;
//	}
//};

// 游戏信息
struct GameInfomation
{
	int nGameID;			// 游戏ID
	char szGameName[48];	// "CChess"
	char szGameDesc[48];	// "中国象棋"
	Score_Type enScoreType;	// 分数类型
	RightViewInfo rightInfo;// RightView信息
	char szHelpURL[260];// 帮助页面
	char szReserved[128];
	GameInfomation()
	{
		nGameID = 0;
		szGameName[0] = 0;
		szGameDesc[0] = 0;
		// szReserved[0] = 0;
		enScoreType = enSType_Siguo;
		szHelpURL[0] = 0;
		memset(szReserved,0,sizeof(szReserved));
	}
};

// 扩展游戏信息，此结构存储于GameInfomatino的szReserved中
struct SExtGameInfo
{
	bool bNotCreateGameView;	// 是否不创建GameView的父窗口,如果不创建,则逻辑的CGameView
    //的父窗口为MainFrame本身;
	bool bFixMainWindowSize;	// 是否规定主窗口的大小,设定大小后起始位置在中间
	WORD wMainWindowWidth;
	WORD wMainWindowHeight;
	bool bRightInitialHide;
	char szSkin[16];
	SExtGameInfo()
	{
		bNotCreateGameView = false;
		bFixMainWindowSize = false;
		wMainWindowWidth = 0;
		wMainWindowHeight = 0;
		bRightInitialHide = false;
	}
};

// avatar's Image type
enum AvatarImageType
{
	enAIType_BODY = 1,	// 70*120
	enAIType_UP = 2,	// 50*70
	enAIType_FACE = 3,	// 32*32	
};


// 逻辑可用的timerid
#define CUSTOM_MAX_TIMER_ID 64

// 荣誉信息
struct SGloryInfo 
{
	WORD		wGloryID;						//荣誉ID			
	long		lGloryScore;					//荣誉分数			
	DWORD		dwSpecialFlag;					//特殊标志			
	TCHAR		szGloryName[GLORY_NAME_LEN];	//荣誉名称
	BYTE		cbGloryLevel;
	SGloryInfo()
	{
		memset(this,0,sizeof(SGloryInfo));
	}	
};

struct GameMySelfType
{
    bool    IsPlayer;       //是不是玩家。如果为false，用户可能是旁观者，可能已经离开
    bool    IsValidPlayer;  //用户是否有效。用户如果离开，其信息依然保留在用户列表中，用户被认为无效
    BYTE    UserChair;
    WORD    UserID;
    long    UserDBID;
    int     UserStatus;
};


#endif // _CLIENTFRAMEDEFS_H__