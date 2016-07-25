//
//  CommonFunction.h
//  xzdd
//
//  Created by  on 12-3-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#ifndef xzdd_CommonFunction_h
#define xzdd_CommonFunction_h

#include "ConstantDef.h"
#include <string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "iconv.h"
#include "TypeDef.h"
#include "MjDef.h"
#include "tinyxml.h"

#else
#include "platform/third_party/win32/iconv/iconv.h"
#include "../GameCore/TypeDef.h"
#include "../GameCore/MjDef.h"
#include "../tinyxml/tinyxml.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
//#include "platform/third_party/android/iconv/iconv.h"
#endif

#define Convert_XY()

#ifdef _WIN32
#define UTEXT(str) CommonFunction::GBKToUTF8(str)
#else
#define UTEXT(str) str
#endif

using namespace std;


class CommonFunction
{
public:
    static bool bIsEnterGame;
    static bool isIpad();
    static void openURL(char * url, int nID = 0);
    static void openHall();
//    static bool sendRequest();
    static bool sendStatistic(int nSet, int nGK, int nCoin);
    static void sendAndroidRequest(const char * url);
    static void sendAndroidRequestCXWX();
    static void addMarketLog();
    //该函数只在android平台下起作用
    static std::string codeUTFtoGB2312(const char* strUTF);
    //该函数只在android平台下起作用
	static std::string codeGB2312toUTF(const char* strGB2312);
    static int  Code_Convert(char *inbuf,int inlen,char *outbuf,int outlen);
    static int  Code_Convert_G2U(char *inbuf,int inlen,char *outbuf,int outlen);
    static char * GetImageByByte(CARDTYPE type, BYTE card);
    static char * GetIcoImageByByte(BYTE index);
    static char * GetExpressionImageByByte(BYTE index);
    static char * GetExpressionImageByByte(std::string image);
    static char * GetIcoSImageByByte(BYTE index);
    static BYTE GetNetIcoByte(WORD index);
    static WORD GetNetIcoIdByIco(BYTE icoId);
    
    //获取出牌的音效文件
    static char * GetSoundByByte(USERTYPE type, BYTE card);
    //获取命令的音效文件
    static char * GetSoundByCommand(USERTYPE type, BYTE command);
    
    //获取能够暗杠牌的列表
    static BYTE * GetAGEnableCards(PLAYER_DATA pData,STAND_CARD standCard,bool haveWG);
    
    //根据牌的类型，获取牌的样式
    static CARDSTYLE GetCardStyleByType(CARDTYPE type);
    
    //根据牌的内容，获取牌的类型
    static PAI_TYPE GetCardTypeByContent(BYTE card);
    
    //判断是否时弯杠牌， 一张牌是否在倒牌的碰牌中
    static bool IsWangGangCard(BYTE card, STAND_CARD standCard);
    
    //获取显示座位号，根据实际位置和玩家位置
    static BYTE GetChair(BYTE playerChair,BYTE chair);
    
    //获取关卡的统计数据
    static GUANKA_STATS GetGuanKaStats(BYTE guanKa);
    //保存关卡的统计数据
    static void SetGuanKaStats(GUANKA_STATS gkStats);
    
    //清除关卡数据
    static void ClearGuanKaSaveData(BYTE guanKa);
    
    //根据关卡索引返回关卡名字
    static std::string GetGkNameByIndex(BYTE gkIndex);
    
    //获取关卡
    static GUAN_KA GetGuanKa(BYTE gk_id);
    //判断是否达到条件
    static bool IsReachCONDITION(GUAN_KA_CONDITION condition,int nScore,int nSetNum,int nFanNum,int nJiPinNum);
    
    //获取成就
    static CHENGJIU GetChengJiu(BYTE cj_id);
    
    //胡牌判断
    static CHENGJIU * GetChengJiu_Hu(bool isZhiMo,      //自摸
                                     bool isTianHu,     //天胡
                                     bool isDiHu,       //地胡
                                     bool isQiDui,      //青龙七对
                                     bool isGangHua,    //杠上花
                                     bool isEndHu,      //最后一轮胡牌
                                     bool isJiPin,      //极品
                                     bool isHuIn3,      //三轮内胡牌
                                     BYTE & countCJ);
    //结算判断
    static CHENGJIU * GetChengJiu_GameOver(bool isHuaZhu,   //是否花猪
                                           bool isDaJiao,   //是否大叫
                                           bool isLiuJu,    //是否流局
                                           bool isHu,       //是否胡牌
                                           BYTE fan,        //番数
                                           BYTE & countCJ);
    
    //获取番数的最高成就，显示为级别
    static char * GetMaxFanCJName();
    
    static CHENGJIU * GetChengJiu_FangPao(bool isDouble,BYTE & countCJ);   //放炮判断 isDouble 是否是双响以上
    static CHENGJIU * GetChengJiu_QiangGang(bool isQiang,BYTE & countCJ);  //抢杠判断 isQiang=true 抢杠 isQiang=false 被抢
    static CHENGJIU * GetChengJiu_OutCard_OverTime(BYTE & countCJ);       //出牌超时判断
    
    static string HuTypeToString(int idx); //获取胡牌类型的字符串
    static bool HaveHuType(int type,HU_CURT huCurt); //判断是否有一种胡的类型
    
    //在一关中 创建新的三个电脑玩家
    static void CreatePlayersByGuan(BYTE guanKa);
    //获取电脑玩家
    static PLAYER * GetPlayersByGuan(BYTE guanKa);
    //保存电脑玩家数据
    static void SetPlayers(PLAYER * player);
    //清除电脑玩家数据
    static void ClearPlayersByGuan(BYTE guanKa);
    //获取玩家
    static PLAYER GetUser();
    //保存玩家
    static void SetUser(PLAYER user);
    
    static PLAYER CreatePlayer(BYTE id);
    
    //获取网络玩家
    static PLAYER GetNetUser();
    //保存网络玩家
    static void SetNetUser(PLAYER user);
    
    static PLAYER CreateNetPlayer(BYTE id);
    
    //根据设备获取数值，安卓和iPad数值要*2
    static int GetValueByDev(int size);
    
    //字符串替代
    static char* str_replace(char* source, char* sub,char* rep);
    
    //取得常用短语数组
    static char* getPhrases();
    
    //计算字符串长度，英文和中文都算一个
    static int calcCharCount(const char * pszText);
    
    //获取子字符串，从左边起
    static string subString(string insertStr,int length);
    static string subString(string insertStr,int index,int length);
    //获取子字符串, 从length起
    static string trimString(string insertStr,int length);
    
    static int FindLoginUserMaxIndex();
    static int FindLoginUserMinIndex();
    static BYTE FindLoginUserByMaxIndex();
    static BYTE FindLoginUserByMinIndex();
    static BYTE FindLoginUserCount();
    
    static string getMAC();
    static bool isValidAndroidSysVer(); //判断android系统版本是否>=2.
    
    static string getDateStr();
    
    static bool payfee(int payid,int feeID);
    static bool callEgameAPI(int arg1, int arg2);
    
    static int AddCoin(int n);
    static int SubCoin(int n);
    static bool IsEnoughCoin();
    
    static bool BuyCard();
    
    static int SubmitCoin(int nCoin);
    
    static bool OpenGuanka();
    static bool DelockGuanka();

	static char * GBKToUTF8(const char* szStr);	//add mxs	//此函数只用在win32
};

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//extern "C"
//{
//    
//    void Java_com_cgc_xzdd_single_xzddSingle_nativePayRet(JNIEnv* env, jobject thiz, jint gameUserID, int feeCode,
//                                                   int feeChannel);
//    
//    void Java_com_cgc_xzdd_social_xzddSocial_nativePayRet(JNIEnv* env, jobject thiz, jint gameUserID, int feeCode,
//                                                          int feeChannel);
//    
//    void Java_com_cgc_xzdd_ChinaGameXZDD_nativePayRet(JNIEnv* env, jobject thiz, jint gameUserID, int feeCode,
//                                                      int feeChannel);
//    
//    void Java_com_cgc_xzdd_single_xzddSingle_nativePause(JNIEnv* env, jobject thiz, int n);
//    void Java_com_cgc_xzdd_single_xzddSingle_nativeResume(JNIEnv* env, jobject thiz, int n);
//}
//#endif
#endif
