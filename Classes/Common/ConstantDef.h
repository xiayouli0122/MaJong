//
//  ConstantDef.h
//  xzdd
//
//  Created by  on 12-3-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_ConstantDef_h
#define xzdd_ConstantDef_h

#include "cocos2d.h"
//#include <pthread.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "TypeDef.h"

#else

#include "../GameCore/TypeDef.h"

#endif

#if IS_TEST_CARD
#define GUANKA_FILE_NAME "guanka_test.xml"
#else
#define GUANKA_FILE_NAME "guanka.xml"
#endif
#define CHENGJIU_FILE_NAME "cj.xml"
#define MOREGAME_FILE_NAME "moregames.xml"
#define HELP_FILE_NAME "help.xml"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define ISANDROID TRUE

#else
#define ISANDROID FALSE
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define PLAT_ID         100             //打包时候连同版本号一起改
#define IS_QUICK_PAY    true
#else
#define PLAT_ID         1               //打包时候连同版本号一起改
#define IS_QUICK_PAY    FALSE
#endif


#define GAME_VER_COMMON         0           //联网版
#define GAME_VER_LOCAL          1           //单机版
#define GAME_VER_SPRING         2           //春节活动版
#define GAME_VER_COMMUNITY      3           //换肤社区版
#define GAME_VER_CXWX           4           //CXWX版
#define GAME_VER_SCORE          5           //联网积分版
#define GAME_VER_HWCT           6           //单机定制版
#define GAME_VER_NEW_CXWX       7           //CXWX换肤版
#define GAME_VER_MM             8           //移动mm计费版
#define GAME_VER_CGHALL         9           //棋牌大厅版
#define GAME_VER_CPS            10          //爱游戏CPS版
#define GAME_VER_CTC            11          //营业厅预装版
#define GAME_VER_ALLSDK         12          //融合计费版
#define GAME_VER_ZTE	        13          //中兴内置版
#define GAME_VER_CPSDK	  		14          //cps计费sdk版
#define GAME_VER_CPSDK_HWCT		15


#define GAME_VER_TYPE   GAME_VER_CPSDK_HWCT
#define IS_TEST_CARD    TRUE
//1
#if (GAME_VER_TYPE == GAME_VER_COMMON)
#define IS_LOCAL                    false       //是否单机版
#define IS_CASINO                   true
#define IS_NEW_SKIN                 false       //是否换肤
#define IS_NON_EGAME                false       //是否非爱游戏渠道
#define STR_VER                     "2.0"       //GAME_VER_COMMON:  网络版
//2
#elif (GAME_VER_TYPE == GAME_VER_LOCAL)
#define IS_LOCAL                    true        //是否单机版
#define IS_CASINO                   true
#define IS_COMMUNITY                false       //是否社区
#define IS_NEW_SKIN                 false       //是否换肤
#define IS_NON_EGAME                false       //非爱游戏渠道
#define STR_VER                     "2.2"       //GAME_VER_LOCAL:   普通单机版
//3
#elif (GAME_VER_TYPE == GAME_VER_SPRING)
#define IS_LOCAL                    true        //是否单机版
#define IS_COMMUNITY                true        //是否社区
#define IS_SPRING                   true        //是否春节活动
#define IS_NEW_SKIN                 false       //是否换肤
#define IS_NON_EGAME                false       //是否非爱游戏渠道
#define STR_VER                     "1.1"       //GAME_VER_SPRING:  新春社区版
//4
#elif (GAME_VER_TYPE == GAME_VER_COMMUNITY)
#define IS_LOCAL                    true        //是否单机版
#define IS_COMMUNITY                true        //是否社区
#define IS_NEW_SKIN                 true        //是否换肤
#define IS_NON_EGAME                false       //是否非爱游戏渠道
#define STR_VER                     "2.1"       //GAME_VER_COMMUNITY: 社区达人版
//5
#elif (GAME_VER_TYPE == GAME_VER_CXWX)
#define IS_LOCAL                    true        //是否单机版
#define IS_COMMUNITY                false       //是否社区
#define IS_CXWX                     true        //是否创想无线
#define IS_NEW_SKIN                 false       //是否换肤
#define IS_NON_EGAME                false       //是否非爱游戏渠道
#define STR_VER                     "2.2"       //创想无线版
//6
#elif (GAME_VER_TYPE == GAME_VER_SCORE)
#define IS_LOCAL                    false       //是否单机版
#define IS_COMMUNITY                false       //是否社区
#define IS_NEW_SKIN                 false       //是否换肤
#define IS_NON_EGAME                false       //是否非爱游戏渠道
#define STR_VER                     "2.0"       //网络积分版
//7
#elif (GAME_VER_TYPE == GAME_VER_HWCT)
#define IS_LOCAL                    true        //是否单机版
#define IS_COMMUNITY                false       //是否社区
#define IS_NEW_SKIN                 true        //是否换肤
#define IS_NON_EGAME                true        //是否非爱游戏渠道
#define IS_HWCT                     true        //是否HW
#define IS_FREE_ACTIVATE            true	    //是否免激活
#define STR_VER                     "1.0.1"     //GAME_VER_HWCT:   普通单机版
//8
#elif (GAME_VER_TYPE == GAME_VER_NEW_CXWX)
#define IS_LOCAL                    true        //是否单机版
#define IS_COMMUNITY                false       //是否社区
#define IS_CXWX                     true        //是否创想无线
#define IS_NEW_SKIN                 true        //是否换肤
#define IS_NON_EGAME                false       //是否非爱游戏渠道
#define STR_VER                     "1.0.1"     //创想无线版
//9
#elif (GAME_VER_TYPE == GAME_VER_MM)
#define IS_LOCAL                    true        //是否单机
#define IS_COMMUNITY                false       //是否社区
#define IS_NEW_SKIN                 true        //是否血战换肤
#define IS_NON_EGAME                true        //是否非爱游戏渠道
#define IS_NEW_GK_CONDITION         true        //是否关卡新规则
#define IS_SHOW_MOREGAME            true        //是否大厅更多游戏
#define STR_VER                     "2.5.1"     //GAME_VER_MM:          mm计费版
//10
#elif (GAME_VER_TYPE == GAME_VER_CGHALL)
#define IS_LOCAL                    true        //是否单机
#define IS_COMMUNITY                false       //是否社区
#define IS_NEW_SKIN                 true        //是否血战换肤
#define IS_NON_EGAME                false       //是否非爱游戏渠道
#define IS_PLUGIN                   true        //是否是否插件包，打包时候改
#define IS_NEW_GK_CONDITION         true        //是否关卡新规则
#define STR_VER                     "2.5.1"     //GAME_VER_CGHALL:      大厅版
//11
#elif (GAME_VER_TYPE == GAME_VER_CPS)
#define IS_LOCAL                    true        //是否单机版
#define IS_COMMUNITY                true        //是否社区
#define IS_NEW_SKIN                 true        //是否换肤
#define IS_NON_EGAME                false       //是否非爱游戏渠道
#define STR_VER                     "2.1"       //GAME_VER_CPS:         CPS版
//12
#elif (GAME_VER_TYPE == GAME_VER_CTC)
#define IS_LOCAL                    true        //是否单机版
#define IS_COMMUNITY                false       //是否社区
#define IS_NEW_SKIN                 true        //是否血战换肤
#define IS_NON_EGAME                false       //是否非爱游戏渠道
#define IS_NEW_GK_CONDITION         true        //是否关卡新规则
#define IS_SHOW_MOREGAME            true        //是否大厅更多游戏
#define STR_VER                     "2.1"       //GAME_VER_CTC:         营业厅预装版
//13
#elif (GAME_VER_TYPE == GAME_VER_ALLSDK)
#define IS_LOCAL                    true        //是否单机
#define IS_COMMUNITY                false       //是否社区
#define IS_NEW_SKIN                 true        //是否血战换肤
#define IS_NON_EGAME                true        //是否非爱游戏渠道
#define IS_NEW_GK_CONDITION         true        //是否关卡新规则
#define IS_SHOW_MOREGAME            true        //是否大厅更多游戏
#define STR_VER                     "2.5.2"     //GAME_VER_ALLSDK:       all计费版
//14
#elif (GAME_VER_TYPE == GAME_VER_ZTE)
#define IS_LOCAL                    true        //是否单机
#define IS_COMMUNITY                false       //是否社区
#define IS_NEW_SKIN                 true        //是否血战换肤
#define IS_NON_EGAME                true        //是否非爱游戏渠道
#define IS_FREE_ACTIVATE            true	    //是否免激活
//15
#elif (GAME_VER_TYPE == GAME_VER_CPSDK)
#define IS_LOCAL                    true        //是否单机
#define IS_COMMUNITY                false       //是否社区
#define IS_NEW_SKIN                 true        //是否血战换肤
#define IS_NON_EGAME                true        //是否非爱游戏渠道
#define IS_SHOW_MOREGAME            true        //是否大厅更多游戏
#define IS_EGAME_LOGO				true		//是否爱游戏logo
#elif (GAME_VER_TYPE == GAME_VER_CPSDK_HWCT)
#define IS_LOCAL                    TRUE        //是否单机版
#define IS_COMMUNITY                FALSE       //是否社区
#define IS_NEW_SKIN                 TRUE        //是否换肤
#define IS_NON_EGAME                TRUE        //是否非爱游戏渠道
#define IS_FREE_ACTIVATE            TRUE	    //是否免激活
#define STR_VER                     "1.0.1"     //GAME_VER_HWCT:   普通单机版
#endif

#ifndef IS_LOCAL
#define IS_LOCAL                FALSE   //单机
#endif
#ifndef IS_CASINO
#define IS_CASINO               FALSE   //积分
#endif
#ifndef IS_COMMUNITY
#define IS_COMMUNITY            FALSE   //社区
#endif
#ifndef IS_CXWX
#define IS_CXWX                 FALSE   //创想无线
#endif
#ifndef IS_SPRING
#define IS_SPRING               FALSE   //春节活动
#endif
#ifndef IS_NEW_SKIN
#define IS_NEW_SKIN             FALSE   //血战换肤
#endif
#ifndef IS_NON_EGAME
#define IS_NON_EGAME            FALSE   //非爱游戏渠道
#endif
#ifndef IS_HWCT
#define IS_HWCT                 FALSE   //HW
#endif
#ifndef IS_PLUGIN
#define IS_PLUGIN               FALSE   //是否插件包，打包时候改
#endif
#ifndef IS_SHOW_MOREGAME
#define IS_SHOW_MOREGAME        FALSE    //enabled more game
#endif
#ifndef IS_NEW_GK_CONDITION
#define IS_NEW_GK_CONDITION     FALSE    //关卡新规则
#endif
#ifndef IS_NEW_COIN_FEE
#define IS_NEW_COIN_FEE         FALSE    //新游戏币计费
#endif
#ifndef IS_FREE_ACTIVATE
#define IS_FREE_ACTIVATE        FALSE    //是否免激活
#endif
#ifndef IS_EGAME_LOGO
#define IS_EGAME_LOGO	        FALSE    //是否爱游戏logo
#endif
#define GAMEID_MJSICHUAN            119	// 四川麻将
#define GAMEID_CASINO_MJSICHUAN     124 // 豆版四川麻将

#define GAME_ID                     GAMEID_MJSICHUAN          //四川麻将
//#define GAME_ID                     GAMEID_CASINO_MJSICHUAN     //豆版四川麻将


#define PAY_ID_COIN           1   //充值
#define PAY_ID_GUANKA         2   //
#define PAY_ID_DELOCK         3   //
#define PAY_ID_CARD           4   //
#define PAY_ID_DELOCK_TOUCH   5

#if IS_HWCT
#define COIN_NUM_PAY            6
#elif IS_NEW_COIN_FEE
#define COIN_NUM_PAY            20
#else
#define COIN_NUM_PAY            10
#endif

#define COIN_NUM_GIVEN          1000//  lyp   10
#define COIN_MIN                1//   lyp   1
#define COIN_NUM_FLEE           2000//lyp  2
#define COIN_NUM_FLEE_JIPIN     10000 //lyp  10

//static const char CONS_Version[]                  = STR_VER;
static const char CONS_RecordInfo_URL[]           = "http://moterminal.chinagames.net/InsertLog.aspx";
static const char CONS_StatisInfo_URL[]           = "http://mobileservice.chinagames.net:8088/maj/default.aspx";
static const char CONS_MarketLog_URL[]            = "http://mhall.play.cn/ajax_data/AddMarketLog.ashx";
//static pthread_t pthId;

#if IS_NEW_SKIN
static const char CONS_DefaultMenuFrameFile[]       = "Image/Menu_new/menu.plist";
static const char CONS_DefaultMenuFrameFile_Ipad[]  = "Image/Menu_new/menu_ipad.plist";

static const char CONS_DefaultGkFrameFile[]         = "Image/GK_new/guanka.plist";
static const char CONS_DefaultGkFrameFile_Ipad[]    = "Image/GK_new/guanka_ipad.plist";

static const char CONS_DefaultPersonSetFrameFile[]      = "Image/Menu_new/personset.plist";
static const char CONS_DefaultPersonSetFrameFile_Ipad[] = "Image/Menu/personset_ipad.plist";

static const char CONS_DefaultMjFrameFile[]         = "Image/MJ_new/mjtt.plist";
static const char CONS_DefaultMjFrameImage[]        = "Image/MJ_new/mjtt.png";
static const char CONS_DefaultMjFrameFile_Ipad[]    = "Image/MJ_new/mjtt_ipad.plist";
static const char CONS_DefaultMjFrameImage_Ipad[]   = "Image/MJ_new/mjtt_ipad.png";

#else
static const char CONS_DefaultMenuFrameFile[]       = "Image/Menu/menu.plist";
static const char CONS_DefaultMenuFrameFile_Ipad[]  = "Image/Menu/menu_ipad.plist";

static const char CONS_DefaultGkFrameFile[]         = "Image/GK/guanka.plist";
static const char CONS_DefaultGkFrameFile_Ipad[]    = "Image/GK/guanka_ipad.plist";

static const char CONS_DefaultPersonSetFrameFile[]      = "Image/Menu/personset.plist";
static const char CONS_DefaultPersonSetFrameFile_Ipad[] = "Image/Menu/personset_ipad.plist";

static const char CONS_DefaultMjFrameFile[]         = "Image/MJ/mjtt.plist";
static const char CONS_DefaultMjFrameImage[]        = "Image/MJ/mjtt.png";
static const char CONS_DefaultMjFrameFile_Ipad[]    = "Image/MJ/mjtt_ipad.plist";
static const char CONS_DefaultMjFrameImage_Ipad[]   = "Image/MJ/mjtt_ipad.png";
#endif
//static const char CONS_DefaultMenuFrameImage[]      = "Image/Menu/menu.png";
//static const char CONS_DefaultMenuFrameImage_Ipad[] = "Image/Menu/menu_ipad.png";

static const char CONS_DefaultMjOutBJImage[]        = "timer_bj.png";
static const char CONS_DefaultChatFrameFile[]       = "Image/Net/Chat/chat.plist";
static const char CONS_DefaultChatFrameFile_Ipad[]  = "Image/Net/Chat/chat_ipad.plist";
static const char CONS_DefaultPlazaFrameFile[]      = "Image/Net/Plaza/plaza.plist";
static const char CONS_DefaultPlazaFrameFile_Ipad[] = "Image/Net/Plaza/plaza_ipad.plist";
//lyp 商城图片
static const char CONS_DefaultStoreBackGround[]     = "Image/Menu_new/frame_shop.png";


//菜单贴图项
#if IS_NON_EGAME
static const char CONS_Image_Menu_DJCG_1[]      = "djcg1_x.png";
static const char CONS_Image_Menu_DJCG_2[]      = "djcg2_x.png";
static const char CONS_Image_Menu_Set_1[]       = "gameset1_x.png";
static const char CONS_Image_Menu_Set_2[]       = "gameset2_x.png";
static const char CONS_Image_Menu_Help[]        = "help_x.png";
static const char CONS_Image_Menu_Help_2[]        = "help_2_x.png";
#elif (IS_NEW_SKIN&&!IS_COMMUNITY)
static const char CONS_Image_Menu_DJCG_1[]      = "djcg1_x.png";
static const char CONS_Image_Menu_DJCG_2[]      = "djcg2_x.png";
static const char CONS_Image_Menu_Set_1[]       = "gameset1_x.png";
static const char CONS_Image_Menu_Set_2[]       = "gameset2_x.png";
static const char CONS_Image_Menu_Help[]        = "help_x.png";
static const char CONS_Image_Menu_Help_2[]        = "help_2_x.png";
#elif (IS_NEW_SKIN&&IS_CXWX)
static const char CONS_Image_Menu_DJCG_1[]      = "djcg1_x.png";
static const char CONS_Image_Menu_DJCG_2[]      = "djcg2_x.png";
static const char CONS_Image_Menu_Set_1[]       = "gameset1_x.png";
static const char CONS_Image_Menu_Set_2[]       = "gameset2_x.png";
static const char CONS_Image_Menu_Help[]        = "help_x.png";
static const char CONS_Image_Menu_Help_2[]        = "help_2_x.png";
#else
static const char CONS_Image_Menu_DJCG_1[]      = "djcg1.png";
static const char CONS_Image_Menu_DJCG_2[]      = "djcg2.png";
static const char CONS_Image_Menu_Set_1[]       = "gameset1.png";
static const char CONS_Image_Menu_Set_2[]       = "gameset2.png";
static const char CONS_Image_Menu_Help[]        = "help.png";
static const char CONS_Image_Menu_Help_2[]        = "help_2.png";
#endif

static const char CONS_Image_Menu_Net_1[]       = "netgame1.png";
static const char CONS_Image_Menu_Net_2[]       = "netgame2.png";
static const char CONS_Image_Menu_Continue_1[]  = "continue1.png";
static const char CONS_Image_Menu_Continue_2[]  = "continue2.png";
static const char CONS_Image_Menu_GK_1[]        = "gkselect1.png";
static const char CONS_Image_Menu_GK_2[]        = "gkselect2.png";
static const char CONS_Image_Menu_Menu_1[]      = "menu1.png";
static const char CONS_Image_Menu_Menu_2[]      = "menu2.png";
static const char CONS_Image_Menu_ReGK_1[]      = "regk1.png";
static const char CONS_Image_Menu_ReGK_2[]      = "regk2.png";
static const char CONS_Image_Menu_Cancel[]      = "cancel.png";
static const char CONS_Image_Menu_Cancel_2[]      = "cancel_2.png";
static const char CONS_Image_Menu_Confirm[]     = "confirm.png";
static const char CONS_Image_Menu_Confirm_2[]     = "confirm_2.png";

static const char CONS_Image_Menu_MoreGames[]   = "moregames.png";
static const char CONS_Image_Menu_MoreGames_2[]   = "moregames_2.png";
static const char CONS_Image_Menu_Ico[]         = "ico_0.png";
static const char CONS_Image_Menu_Store1[]		 = "gameshop1_x.png";
static const char CONS_Image_Menu_Store2[]		 = "gameshop1_x.png";

static const char CONS_IMG_MENU_SPRING_1[]       = "btn_spring_1.png";
static const char CONS_IMG_MENU_SPRING_2[]       = "btn_spring_2.png";

static const char CONS_IMG_MENU_COMMUNITY_1[]    = "btn_community_1.png";
static const char CONS_IMG_MENU_COMMUNITY_2[]    = "btn_community_2.png";

static const char CONS_IMG_MENU_FRIENDS_1[]    = "btn_friends_1.png";
static const char CONS_IMG_MENU_FRIENDS_2[]    = "btn_friends_2.png";

static const char CONS_IMG_MENU_RANK_1[]       = "btn_rank_1.png";
static const char CONS_IMG_MENU_RANK_2[]       = "btn_rank_2.png";

static const char CONS_IMG_PAUSE_RANK_1[]       = "daren_1.png";
static const char CONS_IMG_PAUSE_RANK_2[]       = "daren_2.png";

static const char CONS_IMG_PAUSE_COMMUNITY_1[]    = "shequ_1.png";
static const char CONS_IMG_PAUSE_COMMUNITY_2[]    = "shequ_2.png";

static const char CONS_Image_Game_Quit[]        = "quit.png";
static const char CONS_Image_Game_CJ[]          = "cj.png";
static const char CONS_Image_Game_Set[]         = "set.png";
static const char CONS_Image_Game_Set_1[]       = "set1.png";
static const char CONS_Image_Game_Pause[]       = "pause.png";
static const char CONS_Image_Game_Pause_1[]     = "pause1.png";

static const char CONS_IMG_INFO_BG[]            = "msg_info_bg.png";//聊天文字输入背景

static const char CONS_IMG_INFO_TITLE_SINGLE[]  = "player_info_single.png";
static const char CONS_IMG_INFO_TITLE_NEWWORK[]  = "player_info_network.png";
static const char CONS_IMG_INFO_TITLE_NEWWORK_1[]  = "player_info_network_1.png";

#if IS_NEW_SKIN
static const char CONS_Image_BG[]               = "Image/bg_new/bg.jpg";
static const char CONS_Image_BG_Ipad[]          = "Image/bg_new/bg_ipad.jpg";
static const char CONS_Image_Loading[]          = "Image/bg_new/loading.jpg";
static const char CONS_Image_Loading_Ipad[]     = "Image/bg_new/loading_ipad.jpg";
static const char CONS_IMG_BG_GK_NAME[]         = "Image/bg_new/bg_gk_name_%d.png";

static const char CONS_Image_BG_MainMenu[]      = "Image/Menu_new/frame_mainmenu.jpg";
static const char CONS_Image_BG_MainMenu_Ipad[] = "Image/Menu_new/frame_mainmenu_ipad.jpg";
static const char CONS_Image_BG_Message[]       = "Image/Menu_new/frame_message.png";
static const char CONS_Image_BG_Message_Ipad[]  = "Image/Menu_new/frame_message_ipad.png";
static const char CONS_Image_BG_Pause[]         = "Image/Menu_new/frame_pause.png";
static const char CONS_Image_BG_Pause_SPRING[]  = "Image/Menu_new/frame_pause_spring.png";
static const char CONS_Image_BG_Pause_Ipad[]    = "Image/Menu_new/frame_pause_ipad.png";
static const char CONS_Image_BG_JS[]            = "Image/MJ_new/frame_js.png";
static const char CONS_Image_BG_JS_Ipad[]       = "Image/MJ_new/frame_js_ipad.png";
static const char CONS_Image_BG_PersonSet[]     = "Image/Menu_new/frame_personset.jpg";
static const char CONS_Image_BG_PersonSet_Ipad[]= "Image/Menu_new/frame_personset_ipad.jpg";

static const char CONS_Image_BG_Set[]           = "Image/Menu_new/frame_set.png";
static const char CONS_Image_BG_Set_Ipad[]      = "Image/Menu_new/frame_set_ipad.png";
static const char CONS_Image_Set_Progress[]     = "Image/Menu_new/set_progress.png";
static const char CONS_Image_Set_Progress_Ipad[]= "Image/Menu_new/set_progress_ipad.png";

static const char CONS_Image_GK_BG[]            = "Image/GK_new/gk_bg.png";//关卡屏背景
static const char CONS_Image_GK_BG_Ipad[]       = "Image/GK_new/gk_bg_ipad.png";//关卡屏背景
static const char CONS_Image_GK_Kuang[]         = "Image/GK_new/gk_kuang.png";//关卡框
static const char CONS_Image_GK_Kuang_Ipad[]    = "Image/GK_new/gk_kuang_ipad.png";//关卡框

static const char CONS_Image_SPLASH_PAGE[]              = "Image/bg_new/splash_page_%d.jpg";//page名字
static const char CONS_IMG_BTN_SPLASH_ENTRANCE_1[]      = "Image/bg_new/btn_splash_start_1.png";
static const char CONS_IMG_BTN_SPLASH_ENTRANCE_2[]      = "Image/bg_new/btn_splash_start_2.png";
static const char CONS_Image_SPLASH_Selected[]          = "Image/bg_new/splash_page_select.png";//splash选中图标
static const char CONS_Image_SPLASH_Unselected[]        = "Image/bg_new/splash_page_unselect.png";//splash未选中图标

static const char CONS_PATH_FONT_NUM_IPAD[]     = "Image/Menu_new/number_ipad.fnt";
static const char CONS_PATH_FONT_NUM[]           = "Image/Menu_new/number.fnt";

static const char CONS_PATH_PNG_MENU_CONFIRM_IPAD[]     = "Image/Menu_new/confirm_ipad.png";
static const char CONS_PATH_PNG_MENU_CONFIRM[]          = "Image/Menu_new/confirm.png";
static const char CONS_PATH_PNG_MENU_CONFIRM_2[]        = "Image/Menu_new/confirm_2.png";

#else
static const char CONS_Image_BG[]               = "Image/bg/bg.jpg";
static const char CONS_Image_BG_Ipad[]          = "Image/bg/bg_ipad.jpg";
static const char CONS_Image_Loading[]          = "Image/bg/loading.jpg";
static const char CONS_Image_Loading_Ipad[]     = "Image/bg/loading_ipad.jpg";

static const char CONS_Image_BG_MainMenu[]      = "Image/Menu/frame_mainmenu.jpg";
static const char CONS_Image_BG_MainMenu_Ipad[] = "Image/Menu/frame_mainmenu_ipad.jpg";
static const char CONS_Image_BG_Message[]       = "Image/Menu/frame_message.png";
static const char CONS_Image_BG_Message_Ipad[]  = "Image/Menu/frame_message_ipad.png";
static const char CONS_Image_BG_Pause[]         = "Image/Menu/frame_pause.png";
static const char CONS_Image_BG_Pause_SPRING[]  = "Image/Menu/frame_pause_spring.png";
static const char CONS_Image_BG_Pause_Ipad[]    = "Image/Menu/frame_pause_ipad.png";
static const char CONS_Image_BG_JS[]            = "Image/MJ/frame_js.png";
static const char CONS_Image_BG_JS_Ipad[]       = "Image/MJ/frame_js_ipad.png";
static const char CONS_Image_BG_PersonSet[]     = "Image/Menu/frame_personset.jpg";
static const char CONS_Image_BG_PersonSet_Ipad[]= "Image/Menu/frame_personset_ipad.jpg";

static const char CONS_Image_BG_Set[]           = "Image/Menu/frame_set.png";
static const char CONS_Image_BG_Set_Ipad[]      = "Image/Menu/frame_set_ipad.png";
static const char CONS_Image_Set_Progress[]     = "Image/Menu/set_progress.png";
static const char CONS_Image_Set_Progress_Ipad[]= "Image/Menu/set_progress_ipad.png";

static const char CONS_Image_GK_BG[]            = "Image/GK/gk_bg.png";//关卡屏背景
static const char CONS_Image_GK_BG_Ipad[]       = "Image/GK/gk_bg_ipad.png";//关卡屏背景
static const char CONS_Image_GK_Kuang[]         = "Image/GK/gk_kuang.png";//关卡框
static const char CONS_Image_GK_Kuang_Ipad[]    = "Image/GK/gk_kuang_ipad.png";//关卡框

static const char CONS_Image_SPLASH_PAGE[]              = "Image/bg/splash_page_%d.jpg";//page名字
static const char CONS_IMG_BTN_SPLASH_ENTRANCE_1[]      = "Image/bg/btn_splash_start_1.png";
static const char CONS_IMG_BTN_SPLASH_ENTRANCE_2[]      = "Image/bg/btn_splash_start_2.png";
static const char CONS_Image_SPLASH_Selected[]          = "Image/bg/splash_page_select.png";//splash选中图标
static const char CONS_Image_SPLASH_Unselected[]        = "Image/bg/splash_page_unselect.png";//splash未选中图标

static const char CONS_PATH_FONT_NUM_IPAD[]     = "Image/Menu/number_ipad.fnt";
static const char CONS_PATH_FONT_NUM[]           = "Image/Menu/number.fnt";

static const char CONS_PATH_PNG_MENU_CONFIRM_IPAD[]     = "Image/Menu/confirm_ipad.png";
static const char CONS_PATH_PNG_MENU_CONFIRM[]          = "Image/Menu/confirm.png";
static const char CONS_PATH_PNG_MENU_CONFIRM_2[]        = "Image/Menu/confirm_2.png";
#endif

//set 页面
static const char CONS_Image_Set_Progress_bg[]  = "set_progress_bg.png";
static const char CONS_Image_Set_Progress_button[]  = "set_progress_button.png";
static const char CONS_Image_Set_return[]       = "return.png";
static const char CONS_Image_Set_return_2[]       = "return_2.png";
static const char CONS_Image_BG_Set_Checkbox[]  = "set_checkbox_bj.png";
static const char CONS_Image_Set_Checkbox[]     = "set_checkbox.png";
static const char CONS_Image_Set_Yy_Text[]      = "set_yy.png";//音乐
static const char CONS_Image_Set_Yx_Text[]      = "set_yx.png";//音效
static const char CONS_Image_Set_Xsts_Text[]    = "set_xsts.png";//新手提示
static const char CONS_Image_Set_Jzmm_Text[]    = "set_jzmm.png";//记住密码
static const char CONS_Image_Set_Zddl_Text[]    = "set_zddl.png";//自动登陆
static const char CONS_Image_Set_Sdms_Text[]    = "set_sdms.png";//省电模式
static const char CONS_Image_Set_Xzdq_Text[]    = "set_xzdq.png";//血战定缺
static const char CONS_Image_Set_Ptxz_Text[]    = "set_ptxz.png";//普通血战
static const char CONS_Image_Set_Cbz_Text[]     = "set_cbz.png";//承包制
static const char CONS_Image_Set_Jjy_Text[]     = "set_jjy.png";//家家有
static const char CONS_Image_Set_Sfqh_Text[]    = "set_sfqh.png";//三番起和
static const char CONS_Image_Set_Zmjd_Text[]    = "set_zmjd.png";//自摸加底
static const char CONS_Image_Set_Yxpg_Text[]    = "set_yxpg.png";//允许旁观

static const char CONS_IMG_BTN_BUY_CARD_1[]     = "btn_buycard_1.png";
static const char CONS_IMG_BTN_BUY_CARD_2[]     = "btn_buycard_2.png";

//person set
static const char CONS_Image_PSet_Left[]        = "arrow_l.png";
static const char CONS_Image_PSet_Right[]       = "arrow_r.png";
static const char CONS_Image_PSet_Update[]      = "update.png";
static const char CONS_Image_PSet_Return[]      = "return.png";
static const char CONS_Image_PSet_Input[]       = "input.png";

static const char CONS_TIMER_BJImage[]          = "timer_bj.png";
static const char CONS_TIMER_SImage[]           = "timer_s.png";
static const char CONS_TIMER_XImage[]           = "timer_x.png";
static const char CONS_TIMER_ZImage[]           = "timer_z.png";
static const char CONS_TIMER_YImage[]           = "timer_y.png";

//定缺花色
static const char CONS_MARK_TONGImage[]         = "mark_tong.png";
static const char CONS_MARK_TIAOImage[]         = "mark_tiao.png";
static const char CONS_MARK_WANImage[]          = "mark_wan.png";
static const char CONS_MARK_ZhuangImage[]       = "mark_zhuang.png";
static const char CONS_MARK_HuImage[]           = "mark_hu.png";
static const char CONS_MARK_JiPinImage[]        = "mark_jipin.png";
static const char CONS_MARK_ZiMoImage[]         = "mark_zimo.png";
static const char CONS_MARK_LableFrameImage[]   = "infoframe.png";
static const char CONS_MARK_ReadyImage[]        = "ready.png";
static const char CONS_MARK_DisConn[]           = "duanxian.png"; //断线

static const char CONS_Image_Card_B[]           = "bx.png"; //旁观的时候，被旁观者不允许旁观时，手牌的显示

//action菜单
static const char CONS_ActionTiaoImage1[]       = "action_tiao1.png";   //条
static const char CONS_ActionTiaoImage2[]       = "action_tiao2.png";   //条
static const char CONS_ActionTiaoImage3[]       = "action_tiao3.png";   //条

static const char CONS_ActionTongImage1[]       = "action_tong1.png";   //条
static const char CONS_ActionTongImage2[]       = "action_tong2.png";   //条
static const char CONS_ActionTongImage3[]       = "action_tong3.png";   //条

static const char CONS_ActionWanImage1[]        = "action_wan1.png";   //万
static const char CONS_ActionWanImage2[]        = "action_wan2.png";   //万
static const char CONS_ActionWanImage3[]        = "action_wan3.png";   //万

static const char CONS_ActionxImage1[]          = "action_x1.png";    //消
static const char CONS_ActionxImage2[]          = "action_x2.png";    //消
static const char CONS_ActionxImage3[]          = "action_x3.png";    //消

static const char CONS_ActionpImage1[]          = "action_p1.png";    //碰
static const char CONS_ActionpImage2[]          = "action_p2.png";    //碰
static const char CONS_ActionpImage3[]          = "action_p3.png";    //碰

static const char CONS_ActiongImage1[]          = "action_g1.png";    //杠
static const char CONS_ActiongImage2[]          = "action_g2.png";    //杠
static const char CONS_ActiongImage3[]          = "action_g3.png";    //杠

static const char CONS_ActionagImage1[]         = "action_g1.png";   //暗杠
static const char CONS_ActionagImage2[]         = "action_g2.png";   //暗杠
static const char CONS_ActionagImage3[]         = "action_g3.png";   //暗杠

static const char CONS_ActionhImage1[]          = "action_h1.png";    //胡
static const char CONS_ActionhImage2[]          = "action_h2.png";    //胡
static const char CONS_ActionhImage3[]          = "action_h3.png";    //胡

static const char CONS_ActionApImage[]          = "action_a_p.png";
static const char CONS_ActionAgImage[]          = "action_a_g.png";
static const char CONS_ActionAhImage[]          = "action_a_h.png";

static const char CONS_ActionbjImage[]          = "action_bj.png";    //背景
static const char CONS_ActionDQImage[]          = "dingque_word.png"; //定缺文子

static const char CONS_ActionStart[]            = "start.png"; //开始
static const char CONS_ActionStart2[]           = "start2.png"; //开始
static const char CONS_ActionChangeTable[]      = "changetable.png";  //换桌

static const char CONS_IMG_START_CARD_1[]       = "btn_cardstart_1.png";
static const char CONS_IMG_START_CARD_2[]       = "btn_cardstart_2.png";

//Plaze begin
static const char CONS_Image_Plaza_Bj[]                 = "Image/Net/Plaza/plaza_bg.jpg";//桌子列表背景
static const char CONS_Image_Plaza_Bj_Ipad[]            = "Image/Net/Plaza/plaza_bg_ipad.jpg";//桌子列表背景
static const char CONS_Image_Plaza_Kuang[]              = "Image/Net/Plaza/plaza_kuang.png";//桌子列表外框
static const char CONS_Image_Plaza_Kuang_Ipad[]         = "Image/Net/Plaza/plaza_kuang_ipad.png";//桌子列表外框
static const char CONS_Image_Plaza_Register_Bg[]        = "Image/Net/Plaza/register_bg.jpg";//注册背景
static const char CONS_Image_Plaza_Register_Bg_Ipad[]   = "Image/Net/Plaza/register_bg_ipad.jpg";//注册背景
static const char CONS_Image_Plaza_Logon_Bg[]           = "Image/Net/Plaza/login_bj.jpg";//登陆背景
static const char CONS_Image_Plaza_Logon_Bg_Ipad[]      = "Image/Net/Plaza/login_bj_ipad.jpg";//登陆背景
static const char CONS_Image_Plaza_Logon_Ntext[]    = "zy_username_text.png";//中游账号文字
static const char CONS_Image_Plaza_Logon_Ptext[]    = "pass_text.png";//密码文字
static const char CONS_Image_Plaza_Logon_P2text[]   = "confirm_pass.png";//确认密码文字
static const char CONS_Image_Plaza_Logon_Jzmm[]     = "login_rem_pass.png";//记住密码文字
static const char CONS_Image_Plaza_Logon_Auto[]     = "login_auto_login.png";//自动登陆文字
static const char CONS_Image_Plaza_Logon_Input_Bj[] = "login_input_bg.png";//输入框背景
static const char CONS_Image_Plaza_Logon[]          = "login.png";//登陆按钮
static const char CONS_Image_Plaza_Logon_return[]   = "login_return.png";//登陆返回按钮

static const char CONS_Image_Plaza_Ulist_T[]        = "user_list_top.png";//用户列表上部背景
static const char CONS_Image_Plaza_Ulist_M[]        = "user_list_middle.png";//用户列表背景
static const char CONS_Image_Plaza_Ulist_B[]        = "user_list_bottom.png";//用户列表下部背景
static const char CONS_Image_Plaza_User_Delete[]    = "user_delete_button.png";//删除用户按钮

static const char CONS_Image_Plaza_Register_Text[]  = "register_user_text.png";//创建中国游戏中心账号
static const char CONS_Image_Plaza_Register_Name[]  = "register_name.png";//注册账号名
static const char CONS_Image_Plaza_Register_Reset[] = "reset.png";//注册重置
static const char CONS_Image_Plaza_Register_Create[] = "register.png";//注册创建
static const char CONS_Image_Plaza_Register[]   = "register_user.png";//注册按钮
static const char CONS_Image_Plaza_Gun_Bj[]     = "scrollbar_bg.png";//滚动条背景
static const char CONS_Image_Plaza_Gun[]        = "scrollbar.png";//滚动条
static const char CONS_Image_Plaza_Qenter1[]    = "quick_enter1.png";//快速进入1
static const char CONS_Image_Plaza_Qenter2[]    = "quick_enter2.png";//快速进入2
static const char CONS_Image_Plaza_Return1[]    = "return1.png";//返回1
static const char CONS_Image_Plaza_Return2[]    = "return2.png";//返回2
static const char CONS_Image_Plaza_S_Unselect[] = "server_unselected.png";//未选中的服务器
static const char CONS_Image_Plaza_S_Select[]   = "server_selected.png";//选中的服务器
static const char CONS_Image_Plaza_DeskStart[]  = "desk_start.png";//桌子开始
static const char CONS_Image_Plaza_DeskUnStart[] = "desk_unstart.png";//桌子开始
static const char CONS_Image_Plaza_EmptyChair[]  = "empty_chair.png";//空座位
static const char CONS_Image_Plaza_HandUp[]      = "handup.png";//举手
static const char CONS_Image_Plaza_HeadIco1[]    = "ico_s1.png";//网络用户头像1
static const char CONS_Image_Plaza_HeadIco2[]    = "ico_s2.png";//网络用户头像2
static const char CONS_Image_Plaza_HeadIco3[]    = "ico_s3.png";//网络用户头像3
static const char CONS_Image_Plaza_HeadIco4[]    = "ico_s4.png";//网络用户头像4
static const char CONS_Image_Plaza_HeadIco5[]    = "ico_s5.png";//网络用户头像5
static const char CONS_Image_Plaza_HeadIco6[]    = "ico_s6.png";//网络用户头像6
static const char CONS_Image_Plaza_HeadIco7[]    = "ico_s7.png";//网络用户头像7
static const char CONS_Image_Plaza_HeadIco8[]    = "ico_s8.png";//网络用户头像8
static const char CONS_Image_Plaza_HeadIco9[]    = "ico_s9.png";//网络用户头像9
static const char CONS_Image_Plaza_HeadIco10[]   = "ico_s10.png";//网络用户头像10
static const char CONS_Image_Plaza_HeadIco11[]   = "ico_s11.png";//网络用户头像11
static const char CONS_Image_Plaza_HeadIco12[]   = "ico_s12.png";//网络用户头像12

//Plaza end

//关卡begin
static const char CONS_Image_Lock1[]            = "gk_lock_1.png";//未支付锁
static const char CONS_Image_Lock2[]            = "gk_lock_2.png";//暗锁
static const char CONS_Image_Lock3[]            = "gk_lock_3.png";//暗锁
static const char CONS_Image_GK_Star[]          = "gk_star.png";//亮星
static const char CONS_Image_GK_Star_Dark[]     = "gk_star_dark.png";//暗星
static const char CONS_Image_GK_Selected[]      = "gk_selected.png";//关卡屏选中图标
static const char CONS_Image_GK_Unselected[]    = "gk_unselected.png";//关卡屏未选中图标
static const char CONS_Image_GK_Return[]        = "gk_return.png";//返回图片
static const char CONS_Image_GK_Return_2[]        = "gk_return_2.png";//返回图片
static const char CONS_Image_GK_Info[]          = "gk_gksm.png";//关卡说明按钮图片
static const char CONS_Image_GK_Info_2[]          = "gk_gksm_2.png";//关卡说明按钮图片
static const char CONS_Image_GK_Info_Text[]     = "gk_gksm_word.png";//关卡说明按钮图片
static const char CONS_Image_GK_Cj[]            = "gk_cj.png";//成就按钮图片
static const char CONS_Image_GK_Cj_2[]            = "gk_cj_2.png";//成就按钮图片
static const char CONS_Image_GK_Cj_Text[]       = "gk_cj_word.png";//成就文字图片
static const char CONS_Image_GK_Xz_Text[]       = "gk_gkxz_word.png";//关卡选择文字图片
static const char CONS_Image_GK_Dark[]          = "gk_dark.png";//被锁关卡
static const char CONS_IMAGE_GK_UNPAY[]         = "gk_un_pay.png";//未支付关卡
static const char CONS_Image_GK_Num1[]          = "gk_num_1.png";//关卡数字1
static const char CONS_Image_GK1[]              = "gk_1.png";//关卡1
static const char CONS_Image_GK_Text1[]         = "gk_1_text.png";//关卡1名字

#if IS_SPRING
static const char CONS_IMG_GK_RANK_1[]            = "btn_rank_1.png";//按钮图片
static const char CONS_IMG_GK_RANK_2[]            = "btn_rank_2.png";//按钮图片
#else
static const char CONS_IMG_GK_RANK_1[]            = "btn_gk_rank_1.png";//按钮图片
static const char CONS_IMG_GK_RANK_2[]            = "btn_gk_rank_2.png";//按钮图片
#endif

static const char CONS_IMG_GK_DELOCK_1[]            = "gk_btn_delock_1.png";//按钮图片
static const char CONS_IMG_GK_DELOCK_2[]            = "gk_btn_delock_2.png";//按钮图片


static const char CONS_Image_SPLASH1[]          = "splash_1.png";//page1名字
static const char CONS_Image_SPLASH2[]          = "splash_2.png";//page2名字
static const char CONS_Image_SPLASH3[]          = "splash_3.png";//page3名字
//关卡end

//聊天begin
static const char CONS_Image_Chat_Bg[]          = "Image/Net/Chat/chat_bg.png";//聊天背景
static const char CONS_Image_Chat_Bg_Ipad[]     = "Image/Net/Chat/chat_bg_ipad.png";//聊天背景
static const char CONS_Image_Chat_Button[]      = "chat_button.png";//聊天按钮
static const char CONS_Image_Chat_Kuang[]       = "chat_kuang.png";//聊天栏内容的框
static const char CONS_Image_Delegate_Robot[]   = "delegate_robot.png";//托管小人
static const char CONS_Image_Delegate[]         = "delegate.png";//托管
static const char CONS_Image_Delegate_Cancel[]  = "cancel_delegate.png";//取消托管
static const char CONS_Image_Chat_Zuo[]         = "chat_z.png";//聊天左背景
static const char CONS_Image_Chat_Shang[]       = "chat_s.png";//聊天上背景
static const char CONS_Image_Chat_You[]         = "chat_y.png";//聊天右
static const char CONS_Image_Chat_Send[]        = "send.png";//聊天发送按钮
static const char CONS_Image_Chat_Scrollbar[]   = "scrollbar.png";//滚动条
static const char CONS_Image_Chat_Phrase1[]     = "phrase1.png";//常用短语1
static const char CONS_Image_Chat_Phrase2[]     = "phrase2.png";//常用短语2
static const char CONS_Image_Chat_Expression1[] = "expression1.png";//表情1
static const char CONS_Image_Chat_Expression2[] = "expression2.png";//表情2
static const char CONS_Image_Chat_Expression_bg[] = "expression_bg.png";//表情背景
static const char CONS_Image_Chat_Record1[]     = "chatrecord1.png";//聊天记录1
static const char CONS_Image_Chat_Record2[]     = "chatrecord2.png";//聊天记录2
static const char CONS_Image_Chat_Text_Bg[]     = "chat_text_bg.png";//聊天文字背景
static const char CONS_Image_Chat_Text_Input[]  = "chat_text_input.png";//聊天文字输入背景
//聊天end

//成就
static const char CONS_Image_Cj_Light[]         = "cj_list_1.png";//成就亮图标背景
static const char CONS_Image_Cj_Dark[]          = "cj_list_2.png";//成就暗图标背景

//更多游戏
static const char CONS_Image_MG_Pic[]           = "moregame_word.png";
static const char CONS_Image_MG_List[]			= "moregame_list.png";

//声音和音效
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

static const char CONS_Sound_Gaming[]           = "sound/gaming.OGG";   //游戏中
static const char CONS_Sound_Complete[]         = "sound/complete.OGG"; //胜利
static const char CONS_Sound_Failed[]           = "sound/failed.OGG";   //失败
static const char CONS_Sound_End[]              = "sound/end.OGG";      //流局
static const char CONS_Sound_Get[]              = "sound/get.OGG";      //成就
static const char CONS_Sound_Through[]          = "sound/through.OGG";  //过关

#else

static const char CONS_Sound_Gaming[]           = "sound/gaming.mp3";   //游戏中
static const char CONS_Sound_Complete[]         = "sound/complete.mp3"; //胜利
static const char CONS_Sound_Failed[]           = "sound/failed.mp3";   //失败
static const char CONS_Sound_End[]              = "sound/end.mp3";      //流局
static const char CONS_Sound_Get[]              = "sound/get.mp3";      //成就
static const char CONS_Sound_Through[]          = "sound/through.mp3";  //过关

#endif


//UserDefault
static const char UD_CurrentGuanKa[]    = "current_guanka_id";          //当前关卡ID
static const char UD_OverTime[]         = "count_outcard_overtime";     //超时出牌次数
static const char UD_QiangGang[]        = "count_qianggang";            //抢杠次数
static const char UD_FanMoreThan9[]     = "count_fan_morethan9";        //翻数大于等于9的次数
static const char UD_JiPin[]            = "count_jipin";                //打得极品的次数
static const char UD_Hu[]               = "count_hu";                   //连续胡牌次数
static const char UD_Hu_time_5[]        = "count_hu_time_5";            //连续5次胡牌次数
static const char UD_LiuJu[]            = "count_liuju";                //连续流局次数
static const char UD_Fan[]              = "count_fan";                  //总番数
static const char UD_GUANKA_OPEN[]      = "isGuankaOpened";
static const char UD_GUANKA_DELOCK[]    = "isGuankaDelock";
static const char UD_PASS_GUANKA_1[]    = "isPassedGuanka1";
static const char UD_PASS_GUANKA_3[]    = "isPassedGuanka3";

static const char UD_SINGLE_COIN[]      = "single_game_coin";
static const char UD_COIN_MAX_RECORD[]  = "maxCoinRecord";
static const char UD_IS_MAX_COIN_REC[]  = "isMaxCoinRec";

static const char UD_SINGLE_TACARD[]    = "single_game_card";
static const char UD_SINGLE_TIMER[]		= "single_game_timer";			//记录本地登录时间


static const char UD_Last_Hu[]          = "last_hu";                    //上一局是否胡牌
static const char UD_Last_Hu_In3[]      = "last_hu_in3";                //三轮内胡牌

static const char UD_User_Id[]          = "user_ico_id";                //用户图标id
static const char UD_User_Name[]        = "user_name";                  //用户名

static const char UD_Net_User_Id[]      = "net_user_ico_id";            //网络用户图标id
static const char UD_Net_User_Name[]    = "net_user_name";              //网络用户名
static const char UD_Net_User_Pass[]    = "net_user_pass";              //网络用户密码
static const char UD_User_Logoned[]     = "user_logoned";               //成功登陆过网络大厅
static const char UD_User_Room_Logoned[]  = "user_room_logoned";        //成功登陆过网络房间
static const char UD_User_Last_Logon_IP[]  = "last_logon_ip";           //上一次成功登陆过的房间IP
static const char UD_User_Last_Logon_Port[] = "last_logon_port";        //上一次成功登陆过的房间Port
static const char UD_User_Last_Logon_Rname[] = "last_logon_rname";      //上一次成功登陆过的房间Name
static const char UD_User_Last_Score[]  = "last_score";                 //最新的积分

static const char UD_Net_User_Index[]   = "net_user_index";              //网络用户索引
static const char UD_Net_User_Index1[]   = "net_user_index_1";              //网络用户索引1

//UserDefault Set
static const char UD_Set_Music[]        = "music_value";                //音乐大小
static const char UD_Set_Effect[]       = "effect_value";               //音效大小
static const char UD_Set_Xsts[]         = "xsts_value";                 //新手提示
static const char UD_Set_Sdms[]         = "effect_value";               //省电模式
static const char UD_Set_Xzdq[]         = "xzdq_value";                 //血战定缺
static const char UD_Set_Ptxz[]         = "ptxz_value";                 //普通血战
static const char UD_Set_Cbz[]          = "cbz_value";                  //承包制
static const char UD_Set_Jjy[]          = "jjy_value";                  //家家有
static const char UD_Set_Sfqh[]         = "sfqh_value";                 //三番起和
static const char UD_Set_Zmjd[]         = "zmjd_value";                 //自摸加底
static const char UD_Set_Jzmm[]         = "jzmm_value";                 //记住密码
static const char UD_Set_Zddl[]         = "zddl_value";                 //自动登陆
static const char UD_Set_Yxpg[]         = "yxpg_value";                 //允许旁观
static const char UD_Set_Zdjrfq[]       = "zdjrfq_value";               //自动进入分区

static const char UD_IsRegularSet[]    = "iscontinueset";              //前一局是否正常结束(可用大牌)

static const char UD_RecordVersion[]    = "record_version";             //被记录的版本号
static const char UD_RecordVersion_CXWX[]    = "record_version_cxwx";        //被记录的版本号 for 畅想无限

static const char UD_IsFirstRun[]   = "isFirstRun";           //记录app第一次启动

//Message
#if IS_HWCT
static const char CONS_MESSAGE_NO_COIN[]    = "您的游戏币不足，充值%d枚游戏币（1元）吗？";
static const char CONS_MESSAGE_ADD_COIN[]    = "您要充值%d枚游戏币（1元）吗？";
#elif IS_NEW_COIN_FEE
static const char CONS_MESSAGE_NO_COIN[]    = "您的游戏币不足，充值%d枚游戏币（4元）吗？";
static const char CONS_MESSAGE_ADD_COIN[]    = "您要充值%d枚游戏币（4元）吗？";
#else
static const char CONS_MESSAGE_NO_COIN[]    = "您的游戏币不足，充值2000枚游戏币（2元）吗？";//lyp  %d
static const char CONS_MESSAGE_ADD_COIN[]    = "您要充值2000枚游戏币（2元）吗？";//lyp  %d
#endif

static const char CONS_MESSAGE_ReGK[]       = "重新开始本关，以前的记录将会被替换\n确定重新开始？";
static const char CONS_MESSAGE_RunAway[]    = "当前游戏正在进行，未胡玩家退出将被扣分，已胡\n玩家退出不扣分，是否退出？";

static const char CONS_MESSAGE_SINGLE_FLEE[]    = "本局游戏还未结束，请您先胡牌或打完后再离开哦\n若确定离开，您将损失%d游戏币";
static const char CONS_MESSAGE_SINGLE_FLEE_JIPIN[]    = "您的对手胡了极品牌，请不要耍赖退出哦\n若确定离开，您将损失%d游戏币";
static const char CONS_MESSAGE_PAY_COIN_OK[] = "游戏币充值成功！\n充值后您的游戏币数量为:%d";

static const char CONS_MESSAGE_UNPASS[]          = "您还未通过前面关卡，加油哦";
static const char CONS_MESSAGE_RECEIVE[]		 = "今日免费赠送金币2000";

static const char CONS_MESSAGE_TOW[]			 = "您已经成功购买2RMB金币10000";
static const char CONS_MESSAGE_FOUR[]			 = "您已经成功购买4RMB金币50000";
static const char CONS_MESSAGE_SIX[]			 = "您已经成功购买6RMB金币100000";

#if IS_NEW_GK_CONDITION
static const char CONS_MESSAGE_OPEN_GUANKA[]        = "游戏未激活！激活后闯关更刺激！\n立即激活游戏进行闯关吗？";
static const char CONS_MESSAGE_OPEN_GUANKA_PASS[]   = "您已闯过前3关！后面的关卡更刺激！\n立即激活游戏继续闯关吗？";
static const char CONS_MESSAGE_PAY_GK_OK[]          = "游戏激活成功！";

static const char CONS_MSG_DELOCK_OPEN_GK[]         = "快速解锁全部关卡需要先激活游戏\n立即激活游戏吗？";
#elif IS_COMMUNITY
static const char CONS_MESSAGE_OPEN_GUANKA[]        = "游戏未激活！激活后游戏币成绩可进入达人榜！\n立即激活游戏吗？";
static const char CONS_MESSAGE_OPEN_GUANKA_PASS[]   = "您已闯过第1关！激活游戏可进入达人榜pk！\n立即激活游戏吗？";
static const char CONS_MESSAGE_PAY_GK_OK[]          = "游戏激活成功！\n您的游戏币成绩将加入达人榜pk！";

static const char CONS_MSG_DELOCK_OPEN_GK[]         = "快速解锁全部关卡需要先激活游戏\n立即激活游戏吗？";
#else
static const char CONS_MESSAGE_OPEN_GUANKA[]        = "游戏未激活！激活后闯关更刺激！\n立即激活游戏进行闯关吗？";
static const char CONS_MESSAGE_OPEN_GUANKA_PASS[]   = "您已闯过第1关！后面的关卡更刺激！\n立即激活游戏进行闯关吗？";
static const char CONS_MESSAGE_PAY_GK_OK[]          = "游戏激活成功！";

static const char CONS_MSG_DELOCK_OPEN_GK[]         = "快速解锁全部关卡需要先激活游戏\n立即激活游戏吗？";
#endif

//Net Message
static const char CONS_NET_MESSAGE_RoomFull[]   = "抱歉，该房间已爆满，请返回房间列表选择别的\n房间";
static const char CONS_NET_MESSAGE_NetBroken[]   = "网络连接错误，请检查网络";
static const char CONS_NET_MESSAGE_NetDisConn[]   = "与服务器连接中断，是否重新回到游戏？";
static const char CONS_NET_MESSAGE_WrongName[]   = "登陆失败：此帐号已不存在，请重新尝试或到受理\n中心http://www.ChinaGames.net汇报给我们!";
static const char CONS_NET_MESSAGE_WrongPass[]   = "登陆失败：密码错误，请重新尝试或到受理中心\nhttp://www.ChinaGames.net汇报给我们!";
static const char CONS_NET_MESSAGE_NotExistUser[] = "对不起,您输入的用户不存在!";
static const char CONS_NET_MESSAGE_RoomWillStop[] = "抱歉，该服务器马上就要停机，拒绝再接受登陆。\n请先登录其他服务器。";
static const char CONS_NET_MESSAGE_ClientTooHign[] = "游戏客户端的版本太高，请先进入其他高版本的\n服务器。";
static const char CONS_NET_MESSAGE_ClientTooLow[] = "游戏客户端版本太低，请下载最新客户端。";
static const char CONS_NET_MESSAGE_RegSuccess[]   = "注册成功，请点击确定直接登陆";
static const char CONS_NET_MESSAGE_JumpTooMuch[]   = "进出桌子过于频繁,被请出房间,禁入10分钟,\n请稍后再进。";
static const char CONS_NET_MESSAGE_DomainNameError[] = "%s不能访问，请检查网络";


static const char CONS_STRING_CASH[]    = "剩余游戏币: %ld";
static const char CONS_STRING_CGJD[]    = "闯关进度: %d局 \n积分（%d/%d）\n番数 （%d/%d）\n极品牌（%d/%d）";
static const char CONS_STRING_DJG[]     = "第%d关 %s";
static const char CONS_STRING_JI[]      = "计";
#if IS_CASINO
static const char CONS_STRING_Fen[]     = "豆";
static const char CONS_STRING_NetTemp[] = "(中游超级豆)";
#else
static const char CONS_STRING_Fen[]     = "分";
static const char CONS_STRING_NetTemp[] = "(联网积分)";
#endif
static const char CONS_STRING_Fan[]     = "番";
static const char CONS_STRING_GFXY[]    = "刮风下雨";
static const char CONS_STRING_GP[]      = "放炮";
static const char CONS_STRING_ZM[]      = "自摸";
static const char CONS_STRING_CJ[]      = "成就: ";
static const char CONS_STRING_15s[]     = "本关为15秒出牌快牌模式";
static const char CONS_STRING_JiFen[]   = "积分: %ld";

static const char CONS_STRING_DQJD[]    = "当前进度:%d局 积分:%d 番数:%d 极品牌:%d\n是否继续当前进度？";
static const char CONS_STRING_InputName[]   = "请输入昵称！";
static const char CONS_STRING_InputPass[]   = "请输入密码！";
static const char CONS_STRING_InputPass2[]   = "请输入确认密码！";

static const char CONS_STRING_Net_Scene[] ="中国游戏中心四川麻将联网版本将在近期推出与您相见^_^";

static const char CONS_STR_IS_PAY_COIN[]            = "isCoinRecharge";
static const char CONS_STR_IS_PAY_GUANKA[]          = "isGuankaCharge";
static const char CONS_STR_IS_PAY_DELOCK[]          = "isDelockCharge";
static const char CONS_STR_IS_PAY_CARD[]            = "isCardRecharge";

static const cocos2d::ccColor3B CCDisable={80,80,80};   //Disable的颜色效果

static const cocos2d::ccColor3B CCPauseTitle={255,86,116};   //Pause title
static const cocos2d::ccColor3B CCPauseContent={255,250,105};   //Pause title
static const cocos2d::ccColor3B CCPauseCash={255,180,0};   //Pause title

static const cocos2d::ccColor3B CC_Red={255,93,116};        //Pause title
static const cocos2d::ccColor3B CC_Yellow={255,240,0};      //Pause title
static const cocos2d::ccColor3B CC_Blue={108,222,255};      //Pause title
static const cocos2d::ccColor3B CC_Black={10,10,10};        //Chat text
static const cocos2d::ccColor3B CC_White={242,242,242};     //white

#define GetIntegerToXML cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey
#define SetIntegerToXML cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey
#define GetStringToXML cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey
#define SetStringToXML cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey
#define GetBoolToXML cocos2d::CCUserDefault::sharedUserDefault()->getBoolForKey
#define SetBoolToXML cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey

#define SOUND CocosDenshion::SimpleAudioEngine::sharedEngine()

//预编译类型
//typedef enum
//{
//    enCommonGame = 0,
//    enLocalGame = 1,
//    enSocialGame = 2
//
//} GameMode;

//社区版AIP类型
typedef enum
{
    API_ID_START_EGAME  = 1,
    API_ID_VIEW_RANK    = 2,
    API_ID_ACHIVE       = 3,
    API_ID_PK           = 4,
    API_ID_SUBMIT_SCORE = 5,
    API_ID_VIEW_MORE    = 6
    
} EgameAPI;

//颜色类型定义
typedef enum
{
    CT_None,
    CT_Black,
    CT_White
    
} ColorType;

//游戏类型
typedef enum
{
    GT_SingleGame,
    GT_NetGame
} GameType;

//菜单类型定义
typedef enum
{
    MenuType_ChooseAction,
    MenuType_DingQue
    
} ActionMenuType;

//场景标签，用来判断当前场景是否是游戏场景，弹出暂停菜单
enum SCENETAG
{
    ST_MENU = 1,
    ST_GAME = 2,
    ST_NETGAME = 3
};

//单机游戏离开当前局
typedef enum
{
    TargetMainMenu,
    TargetRestart,
    TargetGuankaMenu
    
} FleeTargetType;


//单机游戏玩家当前状态
typedef enum
{
    StatusPlayerNoHu,         //player no hu
    StatusPlayerHu,       //player hu
    StatusJipinHu      //computer got high hu
    
} FleeStatusType;

//Message类型定义
typedef enum
{
    MT_None,
    MT_ReGK,
    MT_ContinueGK,
    MT_RunAway,      //逃跑
    MT_NO_COIN,       //游戏币不足
    MT_ADD_COIN,
    MT_SINGLE_FLEE,      //单机游戏重开局
    MT_OPEN_GUANKA,
    MT_PAY_COIN_MSG,
    MT_PAY_GK_MSG,
    MT_UNPASS_MSG,
	MT_RECEIVE_COIN,	//领取金币
	MT_BUY_TOW_COIN,
	MT_BUY_FOUR_COIN,
	MT_BUY_SIX_COIN,
    
} MessageType;

//Info Message类型定义
typedef enum
{
    INFO_RANK_DENY,
    INFO_BLOOD_TIPS,
    INFO_PAY_COIN_SUCCESS,
    INFO_NEW_RECORD,
    INFO_PROP_CARD_INUSE
    
} InfoMsgType;

//UI状态定义
typedef enum
{
    UI_None,
    UI_Menu,
    UI_Room,
    UI_Game
} UIStatus;
//Net Message类型定义
typedef enum
{
    NMT_None,
    NMT_RoomFull,
    NMT_NetBroken,
    NMT_WrongName,
    NMT_WrongPass,
    NMT_NotExistUser,
    NMT_RoomWillStop,
    NMT_ClientTooHigh,
    NMT_ClientTooLow,
    NMT_RegSuccess,
    NMT_SitDownError,
    NMT_LookOnError,
    NMT_NetDisConn,
    NMT_DomainNameError,
    NMT_LowAndroidVer,
    NMT_JumpTooMuch
    
} NetMessageType;

//阶段状态
enum CARDSTYLE
{
    CardStyle_SZ,   //上正
    CardStyle_X,    //下
    CardStyle_SFX,  //上反小
    CardStyle_SZX,  //上正小
    CardStyle_YX,   //右小
    CardStyle_ZX,   //左小
    
    CardStyle_BH,   //背 横
    CardStyle_BS,   //背 上
    CardStyle_BSX,  //背 上小
    CardStyle_BXX,  //背 下小
    CardStyle_BY,   //背 右
    CardStyle_BZ    //背 左
    
};

enum CARDTYPE
{
    //手牌
    CT_HAND_P,
    CT_HAND_S,
    CT_HAND_D,
    CT_HAND_X,
    
    //倒牌
    CT_STAND_P,
    CT_STAND_S,
    CT_STAND_D,
    CT_STAND_X,
    
    //背面向上的倒牌
    CT_STAND_B_P,
    CT_STAND_B_S,
    CT_STAND_B_D,
    CT_STAND_B_X,
    
    //桌面牌
    CT_TABLE_P,
    CT_TABLE_S,
    CT_TABLE_D,
    CT_TABLE_X,
    
    //摸牌
    CT_MO_P,
    CT_MO_S,
    CT_MO_D,
    CT_MO_X,
    
    //牌墙
    CT_WALL_P,
    CT_WALL_S,
    CT_WALL_D,
    CT_WALL_X,
    
    //胡牌
    CT_HU_P,
    CT_HU_S,
    CT_HU_D,
    CT_HU_X,
    
    //打出牌
    CT_OUT
};

enum USERTYPE
{
    UT_MAN,
    UT_WOMAN
};

//关卡统计数据
struct GUANKA_STATS
{
    BYTE guanKa;    //第几关 1开始
    int  nScore;    //分
	int  nSet;      //局
	int  nFan;      //翻
	int  nJiPin;   //极品
	
    bool isLock;    //是否锁定
    BYTE passStar;  //几星过关
    
    GUANKA_STATS()
    {
        clear();
    }
    
	void clear()
	{
        guanKa = 0;
		nScore = 0;
		nSet = 0;
		nFan = 0;
		nJiPin = 0;
        
        isLock = true;
        passStar = 0;
	}
};

//成就
struct CHENGJIU
{
    BYTE id;
    char name[50];
    char key[50];
    char info[255];
    bool isUsed;
    
    void clear()
    {
        id = 0;
        memset(name, 0, sizeof(name));
        memset(key, 0, sizeof(key));
        memset(info, 0, sizeof(info));
        isUsed = false;
    }
};

//更多游戏
struct MOREGAME
{
    BYTE id;
    char name[50];
    char ico[50];
    char url[255];
    bool isUsed;
    
    void clear()
    {
        id = 0;
        memset(name, 0, sizeof(name));
        memset(ico, 0, sizeof(ico));
        memset(url, 0, sizeof(url));
        isUsed = false;
    }
};



//－－－－－－－－－－－－－－关卡－－－－－－－－－－－－－－－－－－－－－－－

struct GUAN_KA_CONDITION
{
	int nScore;        //积分
	int nSetNum;       //局数
	int nFanNum;       //番数
	int nChaoHuNum;    //极品牌数
};

struct GUAN_KA
{
	BYTE nId;                     //ID
    bool isUsed;
	char nName[20];               //名称
	BYTE nAILevel;                //AI级别
	bool isFastMode;              //是否15秒内快牌模式
    BYTE nomi;                    //大牌几率 分子
    BYTE denomi;                  //大牌几率 分母
	GUAN_KA_CONDITION conditionOne;   //第一颗星
	char conOneText[80];              //第一颗星过关条件说明
	GUAN_KA_CONDITION conditionTwo;   //第二颗星
	char conTwoText[80];              //第二颗星过关条件说明
	bool isDoubleCondition;			  //第三颗星是否有并列的两种条件
	char conThreeText[80];             //第三颗星过关条件说明
	GUAN_KA_CONDITION conditionThree1; //第三颗星条件1
	GUAN_KA_CONDITION conditionThree2; //第三颗星条件2
    
    void clear()
    {
        nId = 0;
        isUsed = false;
        memset(nName, 0, sizeof(nName));
		memset(conOneText, 0, sizeof(conOneText));
		memset(conTwoText, 0, sizeof(conTwoText));
		memset(conThreeText, 0, sizeof(conThreeText));
        isFastMode = false;
        nomi = 0;
        denomi = 0;
    }
    
};

struct PLAYER   //电脑玩家
{
    BYTE nId;               //ID 1~12
    char nIco[20];          //ico文件
    char nShowImage[20];    //show 图片
    char nName[100];         //玩家名
    char nPass[100];         //玩家密码
    BYTE nGuan;             //关卡
    long nSource;           //总分
    USERTYPE nUtype;        //用户类型 男，女
    
    void clear()
    {
        nId = 0;
        memset(nIco, 0, sizeof(nIco));
        memset(nShowImage, 0, sizeof(nShowImage));
        memset(nName, 0, sizeof(nName));
        memset(nPass, 0, sizeof(nPass));
        nGuan = 0;
        nSource = 0;
        nUtype = UT_MAN;
    }
};
#define ICO_COUNT   12
//－－－－－－－－－－－－－－关卡 OVER－－－－－－－－－－－－－－－－－－－－－－－

#define TIME_AfterMo_ChooseAction       30
#define TIME_AfterMo_ChooseOut          30
#define TIME_AfterOut_ChooseAction      30
#define TIME_AfterAction_ChooseCard     30
#define TIME_DingQue                    30

#define TIME_AfterMo_ChooseAction_F     15
#define TIME_AfterMo_ChooseOut_F        15
#define TIME_AfterOut_ChooseAction_F    15
#define TIME_AfterAction_ChooseCard_F   15
#define TIME_DingQue_F                  15

//桌面排位
#define MAX_Card_Table      27

#define TABLE_COUNT_PAGE    4

#endif
