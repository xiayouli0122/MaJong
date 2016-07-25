/******************************************************************
 ** 文件名:	IScoreDefs.h
 ** 版  权:	(c) 2003.12 深圳网域开发部
 ** 创建人:	husten
 ** 日  期:	2004.3
 ** 版  本:	0.0
 ** 描  述:	服务器端分数接口相关的公用结构定义
 *******************************************************************/
#ifndef _ISCOREDEFS_H_
#define _ISCOREDEFS_H_

//通用成绩接口
enum
{
	enScore_Score		=	0,	//成绩
	enScore_Win,				//胜利局数
	enScore_Loss,				//失败局数
	enScore_Draw,				//打平局数
	enScore_Flee,				//逃跑局数
	enScore_SetCount,			//总共局数
	
	enScore_Custom		=	16,	//...前面的保留，后面的自定义
	enScore_Gold,				//金币
	enScore_Tax,				//税
	enScore_Ranking,			//等级分
};

// 描述字符串
#define SCORE_SCORE_DESC	"分数"
#define SCORE_WIN_DESC		"赢"
#define SCORE_LOSS_DESC		"输"
#define SCORE_DRAW_DESC		"和"
#define SCORE_FLEE_DESC		"逃跑"
#define SCORE_SETCOUNT_DESC	"局数"
#define SCORE_GOLD_DESC		"金币"
#define SCORE_TAX_DESC		"税"
#define SCORE_RANKING_DESC	"等级分"

enum Score_Type			// 旧的分类,服务器端的创建
{
	enSType_Tentrix = 0,// 对战
	enSType_Siguo,		// 四国类
	enSType_Majiang,	// 麻将类
};

enum Score_Type_Client		// 新的分类,给客户端的数据结构的定义
{
	enClientType_Tentrix = 0,	// {score,gold,win,lose}
	enClientType_Siguo,			// {score,gold,win,lose,draw,flee}
	enClientType_Majiang,		// {score,gold,setcount,flee}
};


enum Data_Type	// 数据类型
{
	enDTLong = 0,	// long
	enDTDWORD,		// DWORD
	enDTInt,		// int
	enDTString,		// char*
	// more...
};


#pragma pack(push)
#pragma pack(1)
// 列描述
struct ScoreColumnDesc
{
	BYTE	cbLength;		// 数据长度
	BYTE	cbScoreField;	// 分数字段,参看前面的定义
	BYTE	cbDataType;		// 数据类型,见Data_Type定义
	char	szDesc[16];
	ScoreColumnDesc()
	{
		memset(this,0,sizeof(ScoreColumnDesc));
	}
};

#pragma pack(pop)

#endif	// _ISCOREDEFS_H_