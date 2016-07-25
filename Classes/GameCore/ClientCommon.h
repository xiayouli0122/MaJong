#ifndef COMMON_H
#define COMMON_H

// 数据范围
#define MAX_MSG_LEN			256
#define MAX_NAME_LEN		32
#define MAX_PASSWORD_LEN	16
#define MAX_USER_ID			2000		// 每个房间最多可容纳的用户数，用户ID也不应超出此范围
#define MAX_CHAIR			6			// 最大椅子数
#define MAX_SCORE_BUF_LEN	20			// 用户成绩的最大长度
#define MAX_RESERVE_LEN		32			// 何留字节最大长度
#define GLORY_NAME_LEN		32

#define MAGIC_NUM			((WORD)0x613)

// IPC name
#define GAME_CHANNEL_NAME		"iGameChannel"

//#define MAX_FREE_ACTIVITY	1

#define MAX_SEND_LEN		4096		// SendCmd() 最大一次发送Buf字节数
#define MAX_RECV_LEN		4096		// RecvCmd() 最大一次接收Buf字节数

#define RET_OK				0	// do the right thing
#define RET_ERROR			1	// common error occur
#define RET_EMPTY			2	// nothing 
#define RET_LINK_ERROR		3	// 通讯错误
#define RET_NO_MEMORY		4	// out of memory
#define RET_CANCEL			5	// cancel current operation
#define RET_TIME_OUT		6	// out if time error
#define RET_BUSY			7	// recv is retentering
#define RET_REFUSE			8	// server refuse to send data or function is refused
#define RET_WAIT			9
#define RET_INVALID_PARAM	10	// one of parameters is error

// 用户用于game的返回码从此值开始，与以上返回码不能冲突
#define RET_USER_DEFINE		100
#define RET_USER_DEFINE1	(RET_USER_DEFINE + 1)

// WinSock通讯相关通知消息
#define WM_RECV_DATA		(WM_USER + 0x123)		// 当CNetLink收到数据包时发此消息
#define WM_LINK_STATUS		(WM_RECV_DATA + 1)		// 当CNetLink的通讯状态发生改变时发此消息

// 游戏IPC通知消息
#define WM_IPC				(WM_RECV_DATA + 2)		// 用户IPC通讯消息

// 外部程序通知消息
#define WM_APP_NOTE			(WM_RECV_DATA + 3)		// 外部程序通知消息

#define WM_THREAD_TRACE		(WM_RECV_DATA + 4)		// 用于线程安全显示debug信息时，通知主程序显示debug信息

// UDP通讯相关通知消息
#define WM_MESSAGER_NOTIFY	(WM_RECV_DATA + 21)		// 当CUDPLink的通讯状态
#define WM_ICQ_NOTIFY		(WM_RECV_DATA + 22)		// 向ICQ向应用层发通知事件，如好友状态发生改变、收到ICQ事件
#define WM_TRAY_NOTIFY		(WM_RECV_DATA + 23)		// systemtray通知消息

#define MSG_COMM_CONNECT			1				// CGameLink 收到连接成功消息
#define MSG_COMM_EXIT				2				// CGameLink 一方宣布退出
#define MSG_COMM_RECV_DATA			3				// CGameLink 通知有数据到达

#define IGAME_MAIN_WND_CLASSNAME	"iGameMainWndClass"	
#define APP_NOTE_INSTALL			1				// 通知大厅：有新的游戏安装
#define APP_NOTE_EXIT				2				// 通知大厅：正在安装新大厅，请求退出大厅
#define	APP_NOTE_ENTER_GAME			3				// 通知大厅: 网管进入某游戏

#define RET_APP_NOTE_OK				2
#define RET_APP_NOTE_ERROR			3

// common structures
//##ModelId=3D47547D0095
typedef struct tagBUF_RESERVE
{
	BYTE	cbReserveLen;
	BYTE	ReserveBuf[MAX_RESERVE_LEN];
}BUF_RESERVE;



// 常用宏定义

// 游戏种类ID
#define GAMEID_TENTRIX			0	// 俄罗斯方块
#define GAMEID_24POINTS			1	// 24点
#define GAMEID_I_GO				2	// 围棋
#define GAMEID_CCHESS			3	// 中国象棋
#define GAMEID_GOBANG			4	// 五子棋
#define GAMEID_JUNQI			5	// 四国军棋
#define GAMEID_CHESS			6	// 国际象棋
#define GAMEID_ANQI				7	// 暗棋
#define GAMEID_UPGRADE			8	// 升级
#define GAMEID_RED_HEARTS		9	// 红心大战
#define GAMEID_RUNOUT			10	// 跑得快
#define GAMEID_BRIDGE			11	// 桥牌
#define GAMEID_MJ				12	// 麻将
#define GAMEID_DIG				13	// 锄大D

#define GAMEID_DOUBLE			14	// 双扣
#define GAMEID_LANDLORD			15	// 斗地主
#define GAMEID_SHOWHAND			16	// 梭哈
#define GAMEID_21P				17	// 21点
#define GAMEID_DRAGON			18	// 接龙
#define GAMDID_CLAMP			19	// 奥塞罗

#define GAMEID_TESTGAME			20	// 测试游戏

#define GAMEID_LANLORD2P		21	// 斗地主两副牌
#define GAMEID_DALU				22	// 大怪路子
#define GAMEID_FRIEND			23	// 找朋友
#define GAMEID_CATTLE			24	// 吹牛
#define GAMEID_BOULT			25	// 筛钟
#define GAMEID_ANIMAL			26	// 斗兽棋
#define GAMEID_GOJI				27	// 够级

#define GAMEID_TESTGAME2		28	// 测试游戏2
#define GAMEID_TESTGAME3		29	// 测试游戏3
#define GAMEID_TESTGAME4		30	// 测试游戏4
#define GAMEID_TESTGAME5		31	// 测试游戏5

#define GAMEID_TANK				32	// 坦克大战
#define GAMEID_BILLIARDS		33	// 网络台球
#define GAMEID_BC_MJ			34	// 博彩麻将
#define GAMEID_SANDAHA			35	// 三打哈
#define GAMEID_CASINOSDH		36	// 金币三打哈

#define GAMEID_BCLANDLORD		37	// 金币斗地主
#define GAMEID_BCDIG			38	// 金币锄大地
#define GAMEID_BJL				39

#define GAMEID_3DBILLIARDS		40	// 3D台球
#define GAMEID_NEW_BILLIARDS	41	// 新台球
#define GAMEID_NEWSHOWHAND		42	// 梭哈
#define GAMEID_WAKENG			43	// 挖坑
#define GAMEID_BAOHUANG			44	// 保皇
#define GAMEID_MJGUANGDONG		45	// 广东麻将
#define GAMEID_BCMJGUANGDONG	46	// 金币广东麻将
#define GAMEID_NCMJ				47	// 南昌麻将
#define GAMEID_MJCHANGSHA		48	// 长沙麻将
#define GAMEID_NEW21P			49	// 新21点
#define GAMEID_CQLANDLORD		50	// 重庆斗地主
#define GAMEID_BIGPOOL			51	// 大台球
#define GAMEID_POOL3D16			52	// 3d16球
#define GAMEID_CHAODIPI			53	// 抄地皮
#define GAMEID_GOLDFLOWER		54	// 扎金花
#define GAMEID_BOMBERMAN		55	// 炸弹人
#define GAMEID_BULLETIN			56	// 色盅公告
#define GAMEID_BULLETIN1		57	// 21点公告
#define GAMEID_FIVECARDS		58	// 港式五张,梭哈
#define GAMEID_PLANE			59	// 飞行棋
#define GAMEID_ACADEMY_CCHESS	60	// 网络棋院中国象棋
#define GAMEID_ACADEMY_CHESS	61	// 网络棋院国际象棋
#define GAMEID_ACADEMY_GO		62	// 网络棋院围棋
#define GAMEID_ACADEMY_GOBANG	63	// 网络棋院五子棋
#define GAMEID_BULLETIN2		64	// 梭哈公告
#define GAMEID_NEWMJGUANGDONG	65	// 新广东麻将
#define GAMEID_CHUZZLE			66	// 鸡鸡碰
#define GAMEID_BALLOON			67	// 气球
#define GAMEID_GDMJTDH			68	// 广东麻将推倒胡
#define GAMEID_NEWGOBANG		69	// 新五子棋
#define GAMEID_SCORE240			70	// 240
#define GAMEID_SUPER_LANDLORD	71	// 超级斗地主
#define GAMEID_SUPER_MAHJONG	72	// 超级麻将
#define GAMEID_MATCH_LANLORD	73	// 斗地主比赛
#define GAMEID_MATCH_UPGRADE	74	// 升级比赛
#define GAMEID_MATCH_CCHESS		75	// 中国象棋比赛
#define GAMEID_MATCH_JUNQI		76	// 军棋比赛
#define GAMEID_ONESANDAHA		77	// 三打哈一副
#define GAMEID_NEWJUNQI			78	// 新军旗
#define GAMEID_BJWAKENG			79	// 宝鸡挖坑
#define GAMEID_PAOHUZI			80	// 跑胡子
#define GAMEID_SANGEN			81	// 三跟
#define GAMEID_NEWUPGRADE		82	// 新升级
#define GAMEID_LORDEXP			83	// 超级斗地主表情版
#define GAMEID_SUPGRADE			84	// 超级升级	
#define GAMEID_SGDMJ			85	// 超级广东麻将
#define GAMEID_SUPERDIG			86	// 超级锄大地
#define GAMEID_DARKCHESS		87	// 暗棋
#define GAMEID_NEWBRIDGE		88	// 新桥牌
#define GAMEID_BRIDGEMATCH		89	// 桥牌比赛
#define GAMEID_LORDMATCH		90	// 超斗竞技
#define GAMEID_LINK				91	// 连连看
#define GAMEID_CRYSTAL			92	// 水晶方块
#define GAMEID_DDP				93	// 超级瓶盖
#define GAMEID_CHECKER			94	// 跳棋
#define GAMEID_DIFFERENT		95	// 找茬

// 3个保留项
#define GAMEID_ZONE             96	// zone
#define GAMEID_GROUP            97	// group
#define GAMEID_BBS              98	// bbs
#define GAMEID_FLASH            99	// flash

#define GAMEID_QIGUI            100	// 七鬼五二三
#define GAMEID_UPGRADE4         101	// 4副升级(Upgrade4.dll)
#define GAMEID_MJWUHAN          102	// 武汉麻将(mjwuhan)
#define GAMEID_DUALMAHJONG		103	// 二人麻将
#define GAMEID_SUPERBILLIARDS	104	// 超级台球
#define GAMEID_TESTGAMES		105	// 105-114都是测试游戏
#define GAMEID_LANDLORDZJ		115	// 湛江打地主
#define GAMEID_DIG3				116	// 三人锄大地
#define GAMEID_CASINO_LORD		117	// 游戏豆超斗
#define GAMEID_FISH				118

#define GAMEID_MJSICHUAN            119	// 四川麻将
#define GAMEID_CASINO_LORDZJ        120 // 超级豆版湛江打地主
#define GAMEID_CASINO_MJSICHUAN     124 // 豆版四川麻将

#define TOTAL_GAME_KIND_NUM         125  //  目前游戏种类数，目前就这些游戏了，玩死你

#define MAX_GAME_KIND_NUM		256	// GAMEID的最大值

#define MAX_GAME_SERVER_NUM		4096	// 最大游戏服务器数
#define INVALID_USER_ID			0xFFFF	// 无效用户索引ID

#define MAX_SERVER_NAME_LEN		128     //新服务器名字长度   2009-12-2 LUYQ  加了这个

//##ModelId=3D47547D00A9
enum FRIEND_TYPE
{
	friendNone = 0,friendFriend = 1,friendEnemy = 2
};

#ifndef	TCHAR
#define	TCHAR char
#endif

#endif	// COMMON_H
