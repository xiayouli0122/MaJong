//
//  ServerFrameDefs.h
//  xzdd
//
//  Created by  on 12-3-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_ServerFrameDefs_h
#define xzdd_ServerFrameDefs_h

#include "TypeDef.h"
#include "cocos2d.h"

#ifndef MAX_CHAIR
#define MAX_CHAIR 6
#endif
#ifndef MAX_LOOKON_COUNT
#define MAX_LOOKON_COUNT 500
#endif

#define INVALID_FRAME_USER_ID		0xFFFFFFFF	
#define FRAME_INVALID_CHAIR		-1		// 无效椅子号

#define CUSTOM_MAX_TIMER_ID 64

// 场景状态
enum SCENE_STATUS	
{
	SCENE_STATUS_PLAYING = 0,
	SCENE_STATUS_FREE
};

// 局状态
enum GAME_STATUS
{
	GAME_STATUS_PLAYING = 0,
	GAME_STATUS_FREE
};

// SetSceneStatusToFree中的nReason
#define CONDITION_STOP_LOGIC			3	// 逻辑停止
#define CONDITION_STOP_PLAYER_LEAVE		4	// 玩家离开
#define CONDITION_STOP_NEGOTIATE		6	// 协商停止
#define CONDITION_STOP_FRAME_NEGOTIATE	7	// 框架协商
#define CONDITION_STOP_SERVER			8	// 服务器停止
#define CONDITION_STOP_MASTER			9	// 网管停止
#define CONDITION_STOP_ERROR			10	// 出错导致停止
#define CONDITION_STOP_MATCH_NOT_START	11	// 有人没有开始导致假的结束
///////////////////////////////////////////////////////////////

// 检查开始模式
enum CHECK_START_MODE	
{
	START_WHEN_ALL_CHAIR_READY,	// 所有的椅子都开始
	START_WHEN_ALL_PLAYER_READY,// 所有的用户都开始(player num >= 2)	
	START_WHEN_ALL_PAIRS_READY,	// 所有对家都开始,like四国
	START_WHEN_ALL_CHAIR_HARD_READY_ALL_PLAYER_SOFT_READY,
};

// 场景数据
#pragma pack (push)
#pragma pack(1)
#pragma warning (disable:4200)

struct SCENE
{
	int cbSize;
	char lpdata[4000];
	SCENE()
	{
		memset(this,0,sizeof(SCENE));
	}
};

// 版本信息
struct VERSION_STRUCT 
{
	DWORD dwMainVersion;	// 主版本号
	DWORD dwSubVersion;		// 次版本号
	DWORD dwReserved;		// 保留
    
	VERSION_STRUCT()
	{
		dwMainVersion = -1;
		dwSubVersion = -1;
		dwReserved = -1;
	}
};

#pragma pack(pop)

// 旁观选项
enum LOOKON_OPTION
{
	LO_NO_HIDDEN_DATA,	// 无隐藏数据
	LO_SINGLE_CHAIR,	// 只能旁观所在椅子的数据	
	LO_ALL_CHAIR,		// 可能旁观所有椅子的隐藏数据
};



// 发送命令的类型
enum SEND_COMMAND_OPTION
{
	SCO_ALL_USER,			// 所有用户
	SCO_ALL_PLAYER,			// 所有玩家
	SCO_ALL_MY_LOOKON,		// 所有我的旁观
	SCO_ALL_USER_EXCEPT,	// 除指定用户之外的所有用户
	SCO_SINGLE_PLAYER,		// 指定用户
};

// 比分
struct Score_Struct// : public CMemObject<Score_Struct>
{
	long lScore;		// 分
	long lWinCount;		// 胜
	long lLoseCount;	// 负
	long lDrawCount;	// 和
	// lWholeCount == lWinCount + lLoseCount + lDrawCount
	long lFleeCount;	// 逃跑
	long lCash;			// 金币
	long lTax;			// 税
	long lRanking;		// 等级分
	long lSetCount;		// 局数
	// ...
	Score_Struct()
	{
		lScore = 0;
		lWinCount = 0;
		lLoseCount = 0;
		lDrawCount = 0;
		lFleeCount = 0;
		lCash = 0;
		lTax = 0;
		lRanking = 0;
		lSetCount = 0;
	}
};

struct GAME_CMD_DATA			// 填写游戏数据的包装
{ // 游戏数据格式
	// 大批量数据自行处理
	GAME_CMD_DATA()
	{
		cChair = -1;
		cCmdID = -1;
		nDataLen = 0;
		data[0] = 0;
	};
	GAME_CMD_DATA(int nChair,char cmd)
	{
		InitData(nChair,cmd);
	}
	void InitData(int nChair,char cmd)
	{
		cChair = (char)nChair;
		cCmdID = cmd;
		nDataLen = 0;
	}
	BOOL SetData(LPCVOID buf, int nLen)
	{
		if(nLen > sizeof(data)/sizeof(char))
		{
			CCLOG("Error : GAME_CMD_DATA::SetData() : nLen = %d\n",nLen);
			return FALSE;
		}
		memcpy(data,buf,nLen);
		nDataLen = nLen;
		return TRUE;
	}
	BOOL AddData(LPCVOID buf, int nLen)
	{
		if(nLen + nDataLen > sizeof(data)/sizeof(char))
		{
			CCLOG("Error : GAME_CMD_DATA::AddData() : nLen = %d,nDataLen = %d\n",nLen,nDataLen);
			return FALSE;
		}
		memcpy(data + nDataLen,buf,nLen);
		nDataLen += nLen;
		return TRUE;
	}
    /*--
	LPCSTR GetBuf()
	{
		return (LPCSTR)this;
	}
     */
	int GetDataLen()
	{
		return nDataLen + 2;
	}
	
	char cChair;
	char cCmdID;
	char data[4096];
	int  nDataLen;
};


#define STOP_SERVERERROR		0x01	// 服务器出错
#define STOP_NOENOUGHPLAYER		0x02	// 玩家不够
#define STOP_SOMEONENOTSTART	0x03	// 有人未开始
#define STOP_NORMAL				0x04	// 正常结束(比如突破限制)

enum FrameDownloadType
{
	enDownload_Silently = 0,	// 后台
	enDownload_Promptly,		// 有对话框
};

struct GameLogic_DownloadInfo
{
	BOOL bSetupPackage;	// 是否要下载安装包
	BOOL bGameLogic;	// 只下载dll
	FrameDownloadType	enDownloadType;	// 怎么下载
	GameLogic_DownloadInfo()
	{
		memset(this,0,sizeof(GameLogic_DownloadInfo));
	}
};

// 服务器让客户端显示多含url的msgbox相关
#define MAX_BUTTON_COUNT_OF_MSGBOX 10
struct Functional_MsgBox
{
	char szTitle[32];		// 对话框标题
	char szContent[128];	// 对话框内容
	char szReserved[16];	// 保留
	// 按钮信息
	BYTE cbDefButtonID;		// 默认按钮(数组下标)
	BYTE cbButtonCount;		// 按钮个数
	
	struct ButtonInfo
	{
		char szButtonText[16];	// 按钮标题
		char szButtonURL[64];	// 按钮对应的url地址
		ButtonInfo()
		{
			memset(this,0,sizeof(ButtonInfo));
		}
	};
	
	ButtonInfo sButtons[MAX_BUTTON_COUNT_OF_MSGBOX];	// 按钮s
	
	Functional_MsgBox()
	{
		memset(this,0,sizeof(Functional_MsgBox));
	}
     
    /*-- 不需要使用
	
	UINT GetBufferSize()	// 得到数据长度
	{
		return (sizeof(Functional_MsgBox) - (MAX_BUTTON_COUNT_OF_MSGBOX - cbButtonCount) * sizeof(ButtonInfo));
	}
	
	// 增加按钮
	// 标题一定要有,但URL可以为NULL
	BOOL AddButton(LPCSTR lpszText,LPCSTR lpszURL,BOOL bDefButton = FALSE)
	{
		if(lpszText == NULL)
			return FALSE;
		if(cbButtonCount >= MAX_BUTTON_COUNT_OF_MSGBOX)
			return FALSE;
		if(bDefButton)
			cbDefButtonID = cbButtonCount;
		
		lstrcpyn(sButtons[cbButtonCount].szButtonText,lpszText,sizeof(sButtons[cbButtonCount].szButtonText));
		if(lpszURL != NULL)
			lstrcpyn(sButtons[cbButtonCount].szButtonURL,lpszURL,sizeof(sButtons[cbButtonCount].szButtonURL));
		
		cbButtonCount++;
		return TRUE;
	}
     */
};

#endif	// _SERVERFRAMEDEFS_H__

