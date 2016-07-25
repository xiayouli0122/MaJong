//
//  CommonFunction.cpp
//  xzdd
//
//  Created by  on 12-3-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include <iostream>
#include "CommonFunction.h"
#include "MyTinyXmlParser.h"

#include "md5.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h> 
#include "platform/android/jni/JniHelper.h" 
#include <android/log.h>

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "IOSCommon.h"
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <alloca.h>

#else 


#endif

using namespace std;


bool CommonFunction::bIsEnterGame = false;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
    void Java_org_cocos2dx_lib_Cocos2dxActivity_nativeSetUploadResult(JNIEnv*  env, jobject thiz, jstring version)
	{
		const char* str;
		jboolean isCopy;
		str = env->GetStringUTFChars(version, &isCopy);
		if (isCopy) {
			//CCLog("--------------version=%s",str);
			cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey("record_version", str);
			env->ReleaseStringUTFChars(version, str);
		}
	}
    
	void Java_org_cocos2dx_lib_Cocos2dxActivity_nativeSetUploadResultCXWX(JNIEnv*  env, jobject thiz, jstring version)
	{
		const char* str;
		jboolean isCopy;
		str = env->GetStringUTFChars(version, &isCopy);
		if (isCopy) {
			//CCLog("--------------cxwx version=%s",str);
			cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey("record_version_cxwx", str);
			env->ReleaseStringUTFChars(version, str);
		}
	}
    
	//lyp 增加计费

	void Java_com_lyp_xzmj_nativePayPet(){

	}


    void Java_com_cgc_xzdd_ChinaGameXZDD_nativePayRet(JNIEnv* env, jobject thiz, jint gameUserID, int feeCode,
                                                   int feeChannel)
    {
        PLAYER user = CommonFunction::GetNetUser();
        char key[256]="";
        sprintf(key, "%s_buyrecord_count",user.nName);
        int count =  GetIntegerToXML(key,0);
        CCLOG("%s : record count = %d",key,count);
        SetIntegerToXML(key,count + 1);
        
        sprintf(key, "%s_buyrecord_time_%d",user.nName,count);
        SetStringToXML(key, CommonFunction::getDateStr());
        sprintf(key, "%s_buyrecord_count_%d",user.nName,count);
        
        SetStringToXML(key,GetStringToXML("lastpaysmscount","0").c_str());
        sprintf(key, "%s_buyrecord_status_%d",user.nName,count);
        
        if(feeCode == 1)
        {
            SetStringToXML(key,"成功");
            SetBoolToXML("isPaySucceed",true);
            SetBoolToXML("isPayCancel",false);
            CCLOG("call nativePayRet,支付成功");
            
            if (feeChannel == 1)
            {
                CommonFunction::AddCoin(COIN_NUM_PAY);
            }
            else if(feeChannel == 2)
            {
                CommonFunction::OpenGuanka();
            }
        }
        else if(feeCode == -1)
        {
            SetStringToXML(key,"失败");
            SetBoolToXML("isPaySucceed",false);
            SetBoolToXML("isPayCancel",false);
            CCLOG("call nativePayRet,支付失败");
        }
        else if(feeCode == -2)
        {
            SetStringToXML(key,"取消");
            SetBoolToXML("isPaySucceed",false);
            SetBoolToXML("isPayCancel",true);
            CCLOG("call nativePayRet,支付取消");
            
        }
        
        SetBoolToXML("isPayRet",true);
        
    }
    
    
    void Java_com_cgc_xzdd_xzdd_nativePayRet(JNIEnv* env, jobject thiz, jint gameUserID, int feeCode,
                                                                int feeChannel)
    {
        PLAYER user = CommonFunction::GetNetUser();
        char key[256]="";
        sprintf(key, "%s_buyrecord_count",user.nName);
        int count =  GetIntegerToXML(key,0);
        CCLOG("%s : record count = %d",key,count);
        SetIntegerToXML(key,count + 1);
        
        sprintf(key, "%s_buyrecord_time_%d",user.nName,count);
        SetStringToXML(key, CommonFunction::getDateStr());
        sprintf(key, "%s_buyrecord_count_%d",user.nName,count);
        
        SetStringToXML(key,GetStringToXML("lastpaysmscount","0").c_str());
        sprintf(key, "%s_buyrecord_status_%d",user.nName,count);
        
        if(feeCode == 1)
        {
            SetStringToXML(key,"成功");
            SetBoolToXML("isPaySucceed",true);
            SetBoolToXML("isPayCancel",false);
            CCLOG("call nativePayRet,支付成功");
            
            switch (feeChannel)
            {
                case PAY_ID_COIN:
                    CommonFunction::AddCoin(COIN_NUM_PAY);
                    break;
                    
                case PAY_ID_GUANKA:
                    CommonFunction::OpenGuanka();
                    break;
                    
                case PAY_ID_DELOCK:
                    CommonFunction::DelockGuanka();
                    break;
                    
                case PAY_ID_CARD:
                    CommonFunction::BuyCard();
                    break;
                    
                default:
                    CCLOG("unknow id: %d", feeChannel);
                    break;
            }
        }
        else if(feeCode == -1)
        {
            SetStringToXML(key,"失败");
            SetBoolToXML("isPaySucceed",false);
            SetBoolToXML("isPayCancel",false);
            CCLOG("call nativePayRet,支付失败");
        }
        else if(feeCode == -2)
        {
            SetStringToXML(key,"取消");
            SetBoolToXML("isPaySucceed",false);
            SetBoolToXML("isPayCancel",true);
            CCLOG("call nativePayRet,支付取消");
            
        }
        
        SetBoolToXML("isPayRet",true);
        
    }
    
    void Java_com_cgc_xzdd_single_xzddSingle_nativePayRet(JNIEnv* env, jobject thiz, jint gameUserID, int feeCode,
                                                      int feeChannel)
    {
        PLAYER user = CommonFunction::GetNetUser();
        char key[256]="";
        sprintf(key, "%s_buyrecord_count",user.nName);
        int count =  GetIntegerToXML(key,0);
        CCLOG("%s : record count = %d",key,count);
        SetIntegerToXML(key,count + 1);
        
        sprintf(key, "%s_buyrecord_time_%d",user.nName,count);
        SetStringToXML(key, CommonFunction::getDateStr());
        sprintf(key, "%s_buyrecord_count_%d",user.nName,count);
        
        SetStringToXML(key,GetStringToXML("lastpaysmscount","0").c_str());
        sprintf(key, "%s_buyrecord_status_%d",user.nName,count);
        
        if(feeCode == 1)
        {
            SetStringToXML(key,"成功");
            SetBoolToXML("isPaySucceed",true);
            SetBoolToXML("isPayCancel",false);
            CCLOG("call nativePayRet,支付成功");
            
            if (feeChannel == 1)
            {
               CommonFunction::AddCoin(COIN_NUM_PAY);
            }
            else if(feeChannel == 2)
            {
                CommonFunction::OpenGuanka();
            }
        }
        else if(feeCode == -1)
        {
            SetStringToXML(key,"失败");
            SetBoolToXML("isPaySucceed",false);
            SetBoolToXML("isPayCancel",false);
            CCLOG("call nativePayRet,支付失败");
        }
        else if(feeCode == -2)
        {
            SetStringToXML(key,"取消");
            SetBoolToXML("isPaySucceed",false);
            SetBoolToXML("isPayCancel",true);
            CCLOG("call nativePayRet,支付取消");
            
        }
        
        SetBoolToXML("isPayRet",true);
        
    }
    
    void Java_com_cgc_xzdd_social_xzddSocial_nativePayRet(JNIEnv* env, jobject thiz, jint gameUserID, int feeCode,
                                                          int feeChannel)
    {
        PLAYER user = CommonFunction::GetNetUser();
        char key[256]="";
        sprintf(key, "%s_buyrecord_count",user.nName);
        int count =  GetIntegerToXML(key,0);
        CCLOG("%s : record count = %d",key,count);
        SetIntegerToXML(key,count + 1);
        
        sprintf(key, "%s_buyrecord_time_%d",user.nName,count);
        SetStringToXML(key, CommonFunction::getDateStr());
        sprintf(key, "%s_buyrecord_count_%d",user.nName,count);
        
        SetStringToXML(key,GetStringToXML("lastpaysmscount","0").c_str());
        sprintf(key, "%s_buyrecord_status_%d",user.nName,count);
        
        if(feeCode == 1)
        {
            SetStringToXML(key,"成功");
            SetBoolToXML("isPaySucceed",true);
            SetBoolToXML("isPayCancel",false);
            CCLOG("call nativePayRet,支付成功");
            
            if (feeChannel == 1)
            {
                CommonFunction::AddCoin(COIN_NUM_PAY);
            }
            else if(feeChannel == 2)
            {
                CommonFunction::OpenGuanka();
            }
        }
        else if(feeCode == -1)
        {
            SetStringToXML(key,"失败");
            SetBoolToXML("isPaySucceed",false);
            SetBoolToXML("isPayCancel",false);
            CCLOG("call nativePayRet,支付失败");
        }
        else if(feeCode == -2)
        {
            SetStringToXML(key,"取消");
            SetBoolToXML("isPaySucceed",false);
            SetBoolToXML("isPayCancel",true);
            CCLOG("call nativePayRet,支付取消");
            
        }
        
        SetBoolToXML("isPayRet",true);
        
    }
    
    void Java_com_cgc_xzdd_ranking_xzddRanking_nativePayRet(JNIEnv* env, jobject thiz, jint gameUserID, int feeCode,
                                                          int feeChannel)
    {
        PLAYER user = CommonFunction::GetNetUser();
        char key[256]="";
        sprintf(key, "%s_buyrecord_count",user.nName);
        int count =  GetIntegerToXML(key,0);
        CCLOG("%s : record count = %d",key,count);
        SetIntegerToXML(key,count + 1);
        
        sprintf(key, "%s_buyrecord_time_%d",user.nName,count);
        SetStringToXML(key, CommonFunction::getDateStr());
        sprintf(key, "%s_buyrecord_count_%d",user.nName,count);
        
        SetStringToXML(key,GetStringToXML("lastpaysmscount","0").c_str());
        sprintf(key, "%s_buyrecord_status_%d",user.nName,count);
        
        if(feeCode == 1)
        {
            SetStringToXML(key,"成功");
            SetBoolToXML("isPaySucceed",true);
            SetBoolToXML("isPayCancel",false);
            CCLOG("call nativePayRet,支付成功");
            
            switch (feeChannel)
            {
                case PAY_ID_COIN:
                    CommonFunction::AddCoin(COIN_NUM_PAY);
                    break;
                    
                case PAY_ID_GUANKA:
                    CommonFunction::OpenGuanka();
                    break;
                    
                case PAY_ID_DELOCK:
                    CommonFunction::DelockGuanka();
                    break;
                    
                case PAY_ID_CARD:
                    CommonFunction::BuyCard();
                    break;
                    
                default:
                    CCLOG("unknow id: %d", feeChannel);
                    break;
            }
        }
        else if(feeCode == -1)
        {
            SetStringToXML(key,"失败");
            SetBoolToXML("isPaySucceed",false);
            SetBoolToXML("isPayCancel",false);
            CCLOG("call nativePayRet,支付失败");
        }
        else if(feeCode == -2)
        {
            SetStringToXML(key,"取消");
            SetBoolToXML("isPaySucceed",false);
            SetBoolToXML("isPayCancel",true);
            CCLOG("call nativePayRet,支付取消");
            
        }
        
        SetBoolToXML("isPayRet",true);
        
    }
    
    void Java_com_cgc_xzdd_customize_xzddCustomize_nativePayRet(JNIEnv* env, jobject thiz, jint gameUserID, int feeCode,
                                                            int feeChannel)
    {
        PLAYER user = CommonFunction::GetNetUser();
        char key[256]="";
        sprintf(key, "%s_buyrecord_count",user.nName);
        int count =  GetIntegerToXML(key,0);
        CCLOG("%s : record count = %d",key,count);
        SetIntegerToXML(key,count + 1);
        
        sprintf(key, "%s_buyrecord_time_%d",user.nName,count);
        SetStringToXML(key, CommonFunction::getDateStr());
        sprintf(key, "%s_buyrecord_count_%d",user.nName,count);
        
        SetStringToXML(key,GetStringToXML("lastpaysmscount","0").c_str());
        sprintf(key, "%s_buyrecord_status_%d",user.nName,count);
        
        if(feeCode == 1)
        {
            SetStringToXML(key,"成功");
            SetBoolToXML("isPaySucceed",true);
            SetBoolToXML("isPayCancel",false);
            CCLOG("call nativePayRet,支付成功");
            
            switch (feeChannel)
            {
                case PAY_ID_COIN:
                    CommonFunction::AddCoin(COIN_NUM_PAY);
                    break;
                    
                case PAY_ID_GUANKA:
                    CommonFunction::OpenGuanka();
                    break;
                    
                case PAY_ID_DELOCK:
                    CommonFunction::DelockGuanka();
                    break;
                    
                case PAY_ID_CARD:
                    CommonFunction::BuyCard();
                    break;
                    
                default:
                    CCLOG("unknow id: %d", feeChannel);
                    break;
            }
        }
        else if(feeCode == -1)
        {
            SetStringToXML(key,"失败");
            SetBoolToXML("isPaySucceed",false);
            SetBoolToXML("isPayCancel",false);
            CCLOG("call nativePayRet,支付失败");
        }
        else if(feeCode == -2)
        {
            SetStringToXML(key,"取消");
            SetBoolToXML("isPaySucceed",false);
            SetBoolToXML("isPayCancel",true);
            CCLOG("call nativePayRet,支付取消");
            
        }
        
        SetBoolToXML("isPayRet",true);
        
    }
    
    void Java_com_cgc_xzdd_single_xzddSingle_nativePause(JNIEnv* env, jobject thiz, jint n)
    {
        if (!CCDirector::sharedDirector()->isPaused())
        {
            CCLOG("CCDirector paused");
        }
        
        CCDirector::sharedDirector()->pause();
        
//        CCDirector::sharedDirector()->stopAnimation();
//        
//        // if you use SimpleAudioEngine, it must be pause
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
    
    void Java_com_cgc_xzdd_single_xzddSingle_nativeResume(JNIEnv* env, jobject thiz, jint n)
    {
        CCLOG("CCDirector resumed");
        CCDirector::sharedDirector()->resume();
    }
    
}

#endif

string CommonFunction::getDateStr()
{
    
    
    time_t rawtime;
    struct tm * timeinfo;
    char timE [80];
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime ( timE,80,"%Y-%m-%d %I:%M:%S",timeinfo);
    return timE;
}


bool CommonFunction::isIpad()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
    return IOSCommon::IsIpad();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
    return false;
#else 
    return false;
#endif
}

void CommonFunction::openURL(char * url, int nID)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)        
	//    openURLJNI("http://wap.chinagames.net/Game/Index/");
	JniMethodInfo minfo;//定义Jni函数信息结构体 
	//getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, 
                                                 "org/cocos2dx/lib/Cocos2dxActivity", 
                                                 "openURL","(I)V");
	if (!isHave) { 
		CCLOG("jni:此函数不存在"); 
	}else{ 
		CCLOG("jni:此函数存在"); 
		//调用此函数 
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, nID);
        minfo.env->DeleteLocalRef(minfo.classID);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
	IOSCommon::OpenURL(url);
#else
    //windows环境
	//ShellExecute(NULL, NULL, L"http://wap.chinagames.net/Game/Index/", NULL, NULL, SW_SHOWNORMAL); 
#endif
    
}

void CommonFunction::openHall()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//    openURLJNI("http://wap.chinagames.net/Game/Index/");
	JniMethodInfo minfo;//定义Jni函数信息结构体
	//getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 "org/cocos2dx/lib/Cocos2dxActivity",
                                                 "openHall","()V");
	if (!isHave) {
		CCLog("jni:openHall()此函数不存在");
	}else{
		CCLog("jni:openHall()此函数存在");
		//调用此函数
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
	}
#endif
    
}

//bool CommonFunction::sendRequest()
//{
//    char url[256];
//    sprintf(url, "%s?MAC=%s&Version=%s&GameID=%d",CONS_RecordInfo_URL,CommonFunction::getMAC().c_str(),CONS_Version, GAME_ID);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	if(IOSCommon::SendRequest(url)){
//        SetStringToXML(UD_RecordVersion,CONS_Version);
//    }
//#else
//    sendAndroidRequest(url);
//#endif
//    return true;
//}

bool CommonFunction::sendStatistic(int nSet, int nGK, int nCoin)
{
    char url[256];
    switch (GAME_VER_TYPE) {
        case GAME_VER_SPRING:
            sprintf(url, "%s?count=%d&version=%d&amount=%d",CONS_StatisInfo_URL, nSet, nGK+100, nCoin);
            break;
        case GAME_VER_COMMUNITY:
            sprintf(url, "%s?count=%d&version=%d&amount=%d",CONS_StatisInfo_URL, nSet, nGK+200, nCoin);
            break;
        case GAME_VER_NEW_CXWX:
            sprintf(url, "%s?count=%d&version=%d&amount=%d",CONS_StatisInfo_URL, nSet, nGK+300, nCoin);
            break;
        case GAME_VER_MM:
            sprintf(url, "%s?count=%d&version=%d&amount=%d",CONS_StatisInfo_URL, nSet, nGK+1000, nCoin);
            break;
        default:
            sprintf(url, "%s?count=%d&version=%d&amount=%d",CONS_StatisInfo_URL, nSet, nGK, nCoin);
            break;
    }
    
//    if (IS_SPRING)
//    {
//        sprintf(url, "%s?count=%d&version=%d&amount=%d",CONS_StatisInfo_URL, nSet, nGK+100, nCoin);
//    }
//    else if(IS_NEW_SKIN)
//    {
//        sprintf(url, "%s?count=%d&version=%d&amount=%d",CONS_StatisInfo_URL, nSet, nGK+200, nCoin);
//    }
//    else if(IS_NON_EGAME)
//    {
//        sprintf(url, "%s?count=%d&version=%d&amount=%d",CONS_StatisInfo_URL, nSet, nGK+200, nCoin);
//    }
//    else
//    {
//        sprintf(url, "%s?count=%d&version=%d&amount=%d",CONS_StatisInfo_URL, nSet, nGK, nCoin);
//    }
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 //   sendAndroidRequest(url);
//#endif
    return true;
}

void CommonFunction::sendAndroidRequest(const char * url)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;//定义Jni函数信息结构体
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 "org/cocos2dx/lib/Cocos2dxActivity",
                                                 "sendRequest","(Ljava/lang/String;)V");
	if (!isHave) {
		CCLOG("jni:sendAndroidRequest()此函数不存在");
	}else{
		CCLOG("jni:sendAndroidRequest()此函数存在");
        jstring stringArg = minfo.env->NewStringUTF(url);
        
		//调用此函数
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg);
        minfo.env->DeleteLocalRef(stringArg);
		minfo.env->DeleteLocalRef(minfo.classID);
        
	}
    
#else
    
#endif
}

void CommonFunction::addMarketLog(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;//定义Jni函数信息结构体
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 "com/cgc/frame/Common",
                                                 "addMarketLog", "()V");
	if (!isHave) {
		CCLOG("jni:addMarketLog()此函数不存在");
	}else{
		CCLOG("jni:addMarketLog()此函数存在");
        
        JNIEnv* env = minfo.env;
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        
	}
    
#else
    
#endif
}

void CommonFunction::sendAndroidRequestCXWX()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;//定义Jni函数信息结构体 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, 
                                                 "org/cocos2dx/lib/Cocos2dxActivity", 
                                                 "sendRequestCXWX","()V");
	if (!isHave) { 
		CCLOG("jni:此函数不存在"); 
	}else{ 
		CCLOG("jni:此函数存在");         
        
		//调用此函数 
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID); 
		minfo.env->DeleteLocalRef(minfo.classID);        
	}
    
#else
    
#endif
}

//void CommonFunction::openURL(char * url)
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)        
//	//    openURLJNI("http://wap.chinagames.net/Game/Index/");
//	JniMethodInfo minfo;//定义Jni函数信息结构体 
//	//getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数 
//	bool isHave = JniHelper::getStaticMethodInfo(minfo, 
//                                                 "org/cocos2dx/lib/Cocos2dxActivity", 
//                                                 "openURL","(I)V");
//	if (!isHave) { 
//		CCLog("jni:此函数不存在"); 
//	}else{ 
//		CCLog("jni:此函数存在"); 
//		//调用此函数 
//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,823); 
//	}
//#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
//	IOSCommon::OpenURL(url);
//#else
//    //windows环境
//	//ShellExecute(NULL, NULL, L"http://wap.chinagames.net/Game/Index/", NULL, NULL, SW_SHOWNORMAL); 
//#endif
//    
//}

std::string CommonFunction::codeUTFtoGB2312(const char* strUTF)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;//定义Jni函数信息结构体
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 "org/cocos2dx/lib/Cocos2dxActivity",
                                                 "getLocalMacAddress","()Ljava/lang/String;");
	if (false) {
		CCLOG("jni: in codeUTFtoGB2312 getLocalMacAddress此函数不存在");
		return std::string("");
	}
	jstring jstr = minfo.env->NewStringUTF(strUTF);
	JNIEnv* env = minfo.env;
	
	char* rtn = 0;
	CCLOG("in CommonFunction");
	CCLOG("before codeUTFtoGB2312: %s",strUTF);
	
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("GB2312");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr,JNI_FALSE);
	if(alen > 0)
	{
		rtn = (char*)malloc(alen+1);
		memcpy(rtn,ba,alen);
		rtn[alen]=0;
	}
	env->ReleaseByteArrayElements(barr,ba,0);
	
	CCLOG("after codeUTFtoGB2312: %s",rtn);
	
	std::string stemp(rtn);
	free(rtn);
	
	
	minfo.env->DeleteLocalRef(strencode);
	minfo.env->DeleteLocalRef(jstr);
	minfo.env->DeleteLocalRef(clsstring);
	minfo.env->DeleteLocalRef(barr);
    minfo.env->DeleteLocalRef(minfo.classID);
	return stemp;
#else
    return std::string(strUTF);
#endif
}

std::string CommonFunction::codeGB2312toUTF(const char* strGB2312)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;//定义Jni函数信息结构体
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 "org/cocos2dx/lib/Cocos2dxActivity",
                                                 "getLocalMacAddress","()Ljava/lang/String;");
	if (false) {
		CCLOG("jni: in codeGB2312toUTF getLocalMacAddress此函数不存在");
		return std::string("");
	}
	
	JNIEnv* env = minfo.env;
	
	jclass strClass = (env)->FindClass("java/lang/String");
    //获取String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	
	//建立byte数组
    jbyteArray bytes = (env)->NewByteArray(strlen(strGB2312));
    //将char* 转换为byte数组
    (env)->SetByteArrayRegion(bytes, 0, strlen(strGB2312), (jbyte*)strGB2312);
    // 设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (env)->NewStringUTF("GB2312");
    
    //将byte数组转换为java String,并输出
	jstring jGB2312Str = (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
	
	jbyte* ba1 = env->GetByteArrayElements(bytes,JNI_FALSE);
	env->ReleaseByteArrayElements(bytes,ba1,0);
	
	jstring strToEncode = env->NewStringUTF("UTF-8");
	jmethodID mid = env->GetMethodID(strClass, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr= (jbyteArray)env->CallObjectMethod(jGB2312Str,mid,strToEncode);
    
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr,JNI_FALSE);
	char* rtn=0;
	if(alen > 0)
	{
		rtn = (char*)malloc(alen+1);
		memcpy(rtn,ba,alen);
		rtn[alen]=0;
	}
	env->ReleaseByteArrayElements(barr,ba,0);
	std::string stemp(rtn);
	free(rtn);
	
	minfo.env->DeleteLocalRef(strToEncode);
	minfo.env->DeleteLocalRef(jGB2312Str);
	minfo.env->DeleteLocalRef(encoding);
	minfo.env->DeleteLocalRef(bytes);
	minfo.env->DeleteLocalRef(strClass);
	minfo.env->DeleteLocalRef(barr);
	minfo.env->DeleteLocalRef(minfo.classID);
	
    
	
    return stemp;
#else
    return std::string(strGB2312);
#endif
    
}


//把GB2313转换为UTF8
int CommonFunction::Code_Convert(char *inbuf,int inlen,char *outbuf,int outlen)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	string str(inbuf,inlen);
	string strGB2312 = codeGB2312toUTF(str.c_str());
	//sprintf(outbuf,"%s",strGB2312.c_str()); //这个代码有潜在的问题，公告消息如果过长 FIX ,2.0
	strlcpy(outbuf, strGB2312.c_str(), outlen); //改为这个
	//	sprintf(outbuf,"%s",strGB2312.c_str());
#else

	iconv_t cd;    
	cd = iconv_open("UTF-8","GB2312");
	if (cd==0) return -1;
	memset(outbuf,0,outlen);

	char **pin = &inbuf;
	char **pout = &outbuf;
#ifdef _WIN32	//add mxs
	if (iconv(cd,(const char **)pin,(size_t *)&inlen,pout,(size_t *)&outlen)==-1) return -1;
#else
	if (iconv(cd,pin,(size_t *)&inlen,pout,(size_t *)&outlen)==-1) return -1;
#endif
	iconv_close(cd);
#endif

	return 0;
}


int CommonFunction::Code_Convert_G2U(char *inbuf,int inlen,char *outbuf,int outlen)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::string str(inbuf,inlen);
	std::string strTo = codeUTFtoGB2312(str.c_str());
	sprintf(outbuf,"%s",strTo.c_str());
#else
    iconv_t cd;
    
    cd = iconv_open("GB2312","UTF-8");
    if (cd==0) return -1;
    memset(outbuf,0,outlen);
    
    char **pin = &inbuf;
    char **pout = &outbuf;
    if (iconv(cd,(const char**)pin,(size_t *)&inlen,pout,(size_t *)&outlen)==-1) return -1;
    
    iconv_close(cd);
    return 0;
#endif
    
    return 0;
    
}
////#pragma mark ---------------获取图片资源---------------------
char * CommonFunction::GetImageByByte(CARDTYPE type,BYTE card)
{
    static char temp[20];
    memset(temp,0,sizeof(temp));
    char * str = temp;
    switch (GetCardStyleByType(type)) {
        case CardStyle_SZ:
            sprintf(str,"%s%d%s","sz_",card+1,".png");
            break;
        case CardStyle_X:
            sprintf(str,"%s%d%s","x_",card+1,".png");
            break;
        case CardStyle_SFX:
            sprintf(str,"%s%d%s","sfx_",card+1,".png");
            break;
        case CardStyle_SZX:
            sprintf(str,"%s%d%s","szx_",card+1,".png");
            break;
        case CardStyle_YX:
            sprintf(str,"%s%d%s","yx_",card+1,".png");
            break;
        case CardStyle_ZX:
            sprintf(str,"%s%d%s","zx_",card+1,".png");
            break;
        case CardStyle_BH:
            sprintf(str,"%s","bh.png");
            break;
        case CardStyle_BSX:
            sprintf(str,"%s","bsx.png");
            break;
        case CardStyle_BS:
            sprintf(str,"%s","bs.png");
            break;  
        case CardStyle_BXX:
            sprintf(str,"%s","bxx.png");
            break;  
        case CardStyle_BY:
            sprintf(str,"%s","by.png");
            break;  
        case CardStyle_BZ:
            sprintf(str,"%s","bz.png");
            break;
        default:
            break;
    }
    return str;
}

char * CommonFunction::GetIcoImageByByte(BYTE index)
{
    static char temp[10];
    memset(temp,0,sizeof(temp));
    char * str = temp;
    sprintf(str,"%s%d%s","ico_",index,".png");
    return str;
}
char * CommonFunction::GetExpressionImageByByte(BYTE index)
{
    static char temp[20];
    memset(temp,0,sizeof(temp));
    char * str = temp;
    sprintf(str,"%s%d%s","e",index,".png");
    return str;
}
char * CommonFunction::GetExpressionImageByByte(string image)
{
    static char temp[20];
    memset(temp,0,sizeof(temp));
    char * str = temp;
    sprintf(str,"%s","e1.png");
    //判断image名是否是1~80
    int i = atoi(image.c_str());
    if (i>0 && i<= 80) {
        sprintf(str,"%s%s%s","e",image.c_str(),".png");
    }
    return str;
}

char * CommonFunction::GetIcoSImageByByte(BYTE index)
{
    static char temp[20];
    memset(temp,0,sizeof(temp));
    char * str = temp;
    sprintf(str,"%s%d%s","ico_s",index,".png");
    return str;
}
BYTE CommonFunction::GetNetIcoByte(WORD index)
{
    BYTE ico = 1;
    switch (index) {
        case 1:
            ico = 9;
            break;
        case 2:
            ico = 11;
            break;
        case 3:
            ico = 10;
            break;
        case 4:
            ico = 2;
            break;
        case 5:
            ico = 3;
            break;
        case 6:
            ico = 12;
            break;
        case 7:
            ico = 7;
            break;
        case 8:
            ico = 4;
            break;
        case 9:
            ico = 5;
            break;
        case 10:
            ico = 8;
            break;
        case 11:
            ico = 6;
            break;
        case 12:
            ico = 1;
            break;
        default:
            break;
    }
    return ico;
}

WORD CommonFunction::GetNetIcoIdByIco(BYTE icoId)
{
    WORD start = 1047;
    switch (icoId) {
        case 9:
            return start;
        case 11:
            return start+1;
        case 10:
            return start+2;
        case 2:
            return start+3;
        case 3:
            return start+4;
        case 12:
            return start+5;
        case 7:
            return start+6;
        case 4:
            return start+7;
        case 5:
            return start+8;
        case 8:
            return start+9;
        case 6:
            return start+10;
        case 1:
            return start+11;
        default:
            return start;
    }
    
}

CARDSTYLE CommonFunction::GetCardStyleByType(CARDTYPE type)
{
    CARDSTYLE style = CardStyle_BXX;
    switch (type) {
        case CT_HAND_P:
        case CT_MO_P:
        case CT_OUT:
            style = CardStyle_X;
            break;
        case CT_STAND_P:
        case CT_HU_P:
            style = CardStyle_SZ;
            break;
        case CT_TABLE_D:
        case CT_STAND_D:
            style = CardStyle_SFX;
            break;
        case CT_TABLE_P:
            style = CardStyle_SZX;
            break;
        case CT_STAND_X:
        case CT_TABLE_X:
            style = CardStyle_YX;
            break;
        case CT_STAND_S:
        case CT_TABLE_S:
            style = CardStyle_ZX;
            break;
        case CT_HU_D:    
        case CT_WALL_P:
        case CT_WALL_D:
        case CT_STAND_B_D:
            style = CardStyle_BSX;
            break;
        case CT_HU_X:
        case CT_HU_S:
        case CT_WALL_S:
        case CT_WALL_X:
        case CT_STAND_B_S:
        case CT_STAND_B_X:
            style = CardStyle_BH;
            break;
        case CT_STAND_B_P:
            style = CardStyle_BS;
            break;
        case CT_HAND_D:
        case CT_MO_D:
            style = CardStyle_BXX;
            break;
        case CT_HAND_S:
        case CT_MO_S:
            style = CardStyle_BZ;
            break;
        case CT_HAND_X:
        case CT_MO_X:
            style = CardStyle_BY;
            break;
        default:
            break;
    }
    return style;
}


////#pragma mark ---------------获取声音资源---------------------
char * CommonFunction::GetSoundByByte(USERTYPE type, BYTE card)
{
    static char temp[20];
    memset(temp,0,sizeof(temp));
    char * str = temp;
    char * suffix  = new char[5];
    switch(card)
    {
        case 0:
            sprintf(suffix,"%s%d","-",rand() % 2);
            break;
        case 9:
            sprintf(suffix,"%s%d","-",rand() % 3);
            break;
        case 10:
            sprintf(suffix,"%s%d","-",rand() % 2);
            break;
        case 18:
            sprintf(suffix,"%s%d","-",rand() % 3);
            break;
        case 22:
            sprintf(suffix,"%s%d","-",rand() % 3);
            break;
        case 25:
            sprintf(suffix,"%s%d","-",rand() % 2);
            break;
        case 26:
            sprintf(suffix,"%s%d","-",rand() % 2);
            break;
        default:
            sprintf(suffix,"%s","");
            break;
    }
    
    switch (type) {
        case UT_MAN:
            if (ISANDROID) {
                sprintf(str,"%s%d%s%s","sound/man/",card,suffix,".OGG");
            }
            else{
                sprintf(str,"%s%d%s%s","sound/man/",card,suffix,".caf");
            }
            break;
        case UT_WOMAN:
            if (ISANDROID){
                sprintf(str,"%s%d%s%s","sound/woman/",card,suffix,".OGG");
            }
            else{
                sprintf(str,"%s%d%s%s","sound/woman/",card,suffix,".caf");
            }
            break;
        default:
            break;
    }
    delete [] suffix;
    suffix = NULL;
    return str;
}

char * CommonFunction::GetSoundByCommand(USERTYPE type, BYTE command)
{
    static char temp[20];
    memset(temp,0,sizeof(temp));
    char * str = temp;
    char * suffix  = new char[10];
    switch(command)
    {
        case CLIENT_PENG:
            sprintf(suffix,"%s%d","peng",rand() % 5);
            break;
        case CLIENT_ZHIGANG:
            sprintf(suffix,"%s%d","gang-",rand() % 3);
            break;
        case CLIENT_WANGANG:
            sprintf(suffix,"%s","gang-2");
            break;
        case CLIENT_ANGANG:
            sprintf(suffix,"%s%d","angang-",rand() % 2);
            break;
        case CLIENT_HU:
            sprintf(suffix,"%s","hu");
            break;
        default:
            sprintf(suffix,"%s","");
            break;
    }
    
    switch (type) {
        case UT_MAN:
            if (ISANDROID){
                sprintf(str,"%s%s%s","sound/man/",suffix,".OGG");
            }
            else{
                sprintf(str,"%s%s%s","sound/man/",suffix,".caf");
            }
            break;
        case UT_WOMAN:
            if (ISANDROID){
                sprintf(str,"%s%s%s","sound/woman/",suffix,".OGG");
            }
            else{
                sprintf(str,"%s%s%s","sound/woman/",suffix,".caf");
            }
            break;
        default:
            break;
    }
    
    if(command==CLIENT_HU)
    {
        CCLOG(str);
    }
    delete [] suffix;
    suffix = NULL;
    return str;
}


////#pragma mark ---------------其他公用方法---------------------
BYTE * CommonFunction::GetAGEnableCards(PLAYER_DATA pData,STAND_CARD standCard,bool haveWG)
{
    BYTE * enableCard = new BYTE[4];
    enableCard[0] = 255;
    enableCard[1] = 255;
    enableCard[2] = 255;
    enableCard[3] = 255;
    
    
    BYTE enableCardIndex = 0;
    
    for (int k=0; k<3; k++) {
        if (pData.nCard[k][0] >0) {
            
            for (int j=1; j<=pData.nCard[k][0]; j++) {
                //判断弯杠
                if (haveWG && IsWangGangCard(pData.nCard[k][j], standCard)) {
                    enableCard[enableCardIndex++] = pData.nCard[k][j];
                    continue;
                }
                //有3张牌
                if (j+2 <= pData.nCard[k][0]) {
                    if(pData.nCard[k][j] == pData.nCard[k][j+2] &&
                       pData.nCard[k][j] == pData.nCardTakenNow)
                    {
                        //有3张同样的牌,并且和手牌一样
                        enableCard[enableCardIndex++] = pData.nCard[k][j];
                        j = j+2;
                    }
                }
                
                //有4张牌
                if (j+3 <= pData.nCard[k][0]) {
                    if(pData.nCard[k][j] == pData.nCard[k][j+3])
                    {
                        //有4张同样的牌
                        enableCard[enableCardIndex++] = pData.nCard[k][j];
                        j = j+3;
                    }
                }
            }
        }
    }
    
    //判断手牌是否有弯杠
    if (haveWG && IsWangGangCard(pData.nCardTakenNow, standCard)) {
        enableCard[enableCardIndex++] = pData.nCardTakenNow;
    }
    
    return enableCard;
    
}

////#pragma mark获取显示座位号，根据实际位置和玩家位置
BYTE CommonFunction::GetChair(BYTE playerChair,BYTE chair)
{
    return (chair-playerChair+4)%4;
}

PAI_TYPE CommonFunction::GetCardTypeByContent(BYTE card)
{
    if (card >= 0 && card <9) {
        return WAN;
    }
    else if (card >= 9 && card <18) {
        return TIAO;
    }
    else if (card >= 18 && card <27) {
        return TONG;
    }
    return PAI_TYPE_INVALID;
}


bool CommonFunction::IsWangGangCard(BYTE card, STAND_CARD standCard)
{
    //循环倒牌，判断是否为 弯杠的牌
    bool isWGCard = false;
    for (int j=0; j<standCard.nNum; j++) {
        if (standCard.nType[j] == KE && standCard.nFirstCard[j]== card) {
            isWGCard = true;
            break;
        }
    }
    
    return isWGCard;
}

////#pragma mark ---------------获取和设置用户数据---------------------
//获取关卡的统计数据
GUANKA_STATS CommonFunction::GetGuanKaStats(BYTE guanKa)
{
    GUANKA_STATS gkStats;
    gkStats.clear();
    
    gkStats.guanKa = guanKa;
    
    static char sKey[50];
    
    sprintf(sKey, "guanka_%d_score",guanKa);
    gkStats.nScore  = GetIntegerToXML(sKey,0);
    
    sprintf(sKey, "guanka_%d_set",guanKa);
    gkStats.nSet    = GetIntegerToXML(sKey,0);
    
    sprintf(sKey, "guanka_%d_fan",guanKa);
    gkStats.nFan  = GetIntegerToXML(sKey,0);
    
    sprintf(sKey, "guanka_%d_jipin",guanKa);
    gkStats.nJiPin  = GetIntegerToXML(sKey,0);
    
    if (guanKa == 1) {
        gkStats.isLock = false; //不锁定第一关
    }
    else
    {
        sprintf(sKey, "guanka_%d_islock",guanKa);
        gkStats.isLock  = GetBoolToXML(sKey,true);
    }
    
    sprintf(sKey, "guanka_%d_star",guanKa);
    gkStats.passStar  = GetIntegerToXML(sKey,0);
    
    return gkStats;
}

//保存关卡的统计数据
void CommonFunction::SetGuanKaStats(GUANKA_STATS gkStats)
{
    static char sKey[50];
    
    sprintf(sKey, "guanka_%d_score",gkStats.guanKa);
    SetIntegerToXML(sKey,gkStats.nScore);
    
    sprintf(sKey, "guanka_%d_set",gkStats.guanKa);
    SetIntegerToXML(sKey,gkStats.nSet);
    
    sprintf(sKey, "guanka_%d_fan",gkStats.guanKa);
    SetIntegerToXML(sKey,gkStats.nFan);
    
    sprintf(sKey, "guanka_%d_jipin",gkStats.guanKa);
    SetIntegerToXML(sKey,gkStats.nJiPin);
    
    sprintf(sKey, "guanka_%d_islock",gkStats.guanKa);
    SetBoolToXML(sKey,gkStats.isLock);
    
    sprintf(sKey, "guanka_%d_star",gkStats.guanKa);
    SetIntegerToXML(sKey,gkStats.passStar);
    
}

//清除关卡数据
void CommonFunction::ClearGuanKaSaveData(BYTE guanKa)
{
    static char sKey[50];
    
    sprintf(sKey, "guanka_%d_score",guanKa);
    SetIntegerToXML(sKey,0);
    
    sprintf(sKey, "guanka_%d_set",guanKa);
    SetIntegerToXML(sKey,0);
    
    sprintf(sKey, "guanka_%d_fan",guanKa);
    SetIntegerToXML(sKey,0);
    
    sprintf(sKey, "guanka_%d_jipin",guanKa);
    SetIntegerToXML(sKey,0);
}


string CommonFunction::GetGkNameByIndex(BYTE gkIndex)
{
	switch(gkIndex)
	{
        case 1:						
            return string("卧龙");
            
        case 2:				
            return string("竹溪湖");
            
        case 3:						
            return string("九寨沟");
            
        case 4:						
            return string("都江堰");
            
        case 5:						
            return string("石象湖");
            
        case 6:						
            return string("武侯祠");
            
        case 7:					
            return string("剑门关");
            
        case 8:					
            return string("百里峡");
            
        case 9:					
            return string("青城山");
            
        case 10:
            if (IS_NEW_SKIN) {
                return string("四姑娘山");
            }
            else
            {
                return string("西岭雪山");
            }
            
        case 11:				
            return string("峨眉山");
            
        case 12:					
            return string("贡嘎山");
            
        case 13:							
            return string("亚丁");
            
        default:
            return string("卧龙");
	}
    
	return string("");
}

////#pragma mark ---------------关卡处理---------------------

//获取关卡
GUAN_KA CommonFunction::GetGuanKa(BYTE gk_id)
{
    GUAN_KA * gk = MyTinyXmlParser::GetGuanKa();
    while (gk->isUsed) {
        if (gk->nId == gk_id) {
            return * gk;
        }
        gk++;
    }
    // todo 如果返回空
    return * gk;
}
//判断是否达到关卡条件
bool CommonFunction::IsReachCONDITION(GUAN_KA_CONDITION condition,int nScore,int nSetNum,int nFanNum,int nJiPinNum)
{ 
    if (condition.nSetNum != 0) {
        if (nSetNum > condition.nSetNum) {
            return false;
        }
    }
    if (condition.nScore != 0) {
        if (nScore < condition.nScore) {
            return false;
        }
    }
    if (condition.nFanNum != 0) {
        if (nFanNum < condition.nFanNum) {
            return false;
        }
    }
    if (condition.nChaoHuNum != 0) {
        if (nJiPinNum < condition.nChaoHuNum) {
            return false;
        }
    }
    return true;
}

////#pragma mark ---------------成就处理---------------------

//获取成就
CHENGJIU CommonFunction::GetChengJiu(BYTE cj_id)
{
    CHENGJIU * cj = MyTinyXmlParser::GetChengJiu();
    while (cj->isUsed) {
        if (cj->id == cj_id) {
            return * cj;
        }
        cj++;
    }
    // todo 如果返回空
    return * cj;
}


//胡牌判断
CHENGJIU * CommonFunction::GetChengJiu_Hu(bool isZhiMo,      //自摸
                                          bool isTianHu,     //天胡
                                          bool isDiHu,       //地胡
                                          bool isQiDui,      //青龙七对
                                          bool isGangHua,    //杠上花
                                          bool isEndHu,      //最后一轮胡牌
                                          bool isJiPin,      //极品
                                          bool isHuIn3,      //三轮内胡牌
                                          BYTE & countCJ)         
{
    static CHENGJIU cjs[15]; //最大一次获得成就数
    BYTE index = 0;
    
    //2 cj_hu 第一次胡牌
    CHENGJIU cj = GetChengJiu(2);
    if(!GetBoolToXML(cj.key,false))
    {
        SetBoolToXML(cj.key,true);
        cjs[index] = cj;
        index++;
    }
    
    //1 cj_zhimo 第一次自摸
    if (isZhiMo) {
        CHENGJIU cj = GetChengJiu(1);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    }   
    
    //4 cj_tianhu 第一次天胡
    if (isTianHu) {
        CHENGJIU cj = GetChengJiu(4);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    } 
    
    //5 cj_dihu 第一次地胡
    if (isDiHu) {
        CHENGJIU cj = GetChengJiu(5);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    } 
    
    //6 cj_qidui 第一次青龙七对
    if (isQiDui) {
        CHENGJIU cj = GetChengJiu(6);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    } 
    
    //9 cj_gangshanghua 第一次杠上花
    if (isGangHua) {
        CHENGJIU cj = GetChengJiu(9);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    } 
    
    //64 cj_hu_end 第一次最后一轮牌胡牌/自摸
    if (isEndHu) {
        CHENGJIU cj = GetChengJiu(64);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    } 
    
    //-----连续胡牌-----
    if (GetBoolToXML(UD_Last_Hu)) {
        //连续胡牌次数
        int count_hu = GetIntegerToXML(UD_Hu,0);
        if (count_hu < 100) { //最多记录100次
            count_hu++;
        }
        SetIntegerToXML(UD_Hu,count_hu);
        
        if (count_hu >= 5) {
            //连续5次胡牌
            int count_hu_time_5 = GetIntegerToXML(UD_Hu_time_5,0);
            if (count_hu_time_5 < 1000) { //最多记录1000次
                count_hu_time_5++;
            }
            SetIntegerToXML(UD_Hu_time_5,count_hu_time_5);
            SetIntegerToXML(UD_Hu,0);
            
            if (count_hu_time_5 == 1) {
                //28 cj_1_hu_5 第一次连续5局胡牌（包括自摸） 快说，你师傅是谁
                CHENGJIU cj = GetChengJiu(28);
                if(!GetBoolToXML(cj.key,false))
                {
                    SetBoolToXML(cj.key,true);
                    cjs[index] = cj;
                    index++;
                }
            }
            
            if (count_hu_time_5 == 2) {
                //29 cj_2_hu_5 第二次连续五局胡牌（包括自摸） 好吧，你赢了
                CHENGJIU cj = GetChengJiu(29);
                if(!GetBoolToXML(cj.key,false))
                {
                    SetBoolToXML(cj.key,true);
                    cjs[index] = cj;
                    index++;
                }
            }
        }
    }
    else
    {
        SetIntegerToXML(UD_Hu,1);
    }
    
    //三轮胡牌判断
    if(isHuIn3 && (!isTianHu && !isDiHu))
    {
        //30 cj_1_hu_in3 第一次摸三轮牌内胡牌（不包括天/地胡） 雷霆万钧
        CHENGJIU cj = GetChengJiu(30);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
        
        //连续三轮胡牌次数
        int count_hu_in3 = GetIntegerToXML(UD_Last_Hu_In3,0);
        if (count_hu_in3 < 100) { //最多记录100次
            count_hu_in3++;
        }
        SetIntegerToXML(UD_Last_Hu_In3,count_hu_in3);
        
        if (count_hu_in3 == 3) {
            //31 cj_3_hu_in3 第一次连续三局均在摸三轮牌内胡牌（不包括天/地胡） 电光火石
            CHENGJIU cj = GetChengJiu(31);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
    }
    else
    {
        SetIntegerToXML(UD_Last_Hu_In3,0);
    }
    
    //---------算极品------------
    if (isJiPin) {
        //极品的次数
        int count = GetIntegerToXML(UD_JiPin,0);
        if (count < 10000) { //最多记录10000次
            count++;
        }
        SetIntegerToXML(UD_JiPin,count);
        
        if (count == 1) {
            //34 cj_jipin_1 第一次打出极品 神功初成
            CHENGJIU cj = GetChengJiu(34);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        else if (count == 3) {
            //35 cj_jipin_3 累计打出3局极品牌 小有所成
            CHENGJIU cj = GetChengJiu(35);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        else if (count == 5) {
            //36 cj_jipin_5 累计打出5局极品牌 小露锋芒
            CHENGJIU cj = GetChengJiu(36);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }        
        else if (count == 10) {
            //37 cj_jipin_10 累计打出10局极品牌 运筹帷幄
            CHENGJIU cj = GetChengJiu(37);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        } 
        else if (count == 20) {
            //38 cj_jipin_20 累计打出20局极品牌 横扫千军
            CHENGJIU cj = GetChengJiu(38);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        } 
        else if (count == 40) {
            //39 cj_jipin_40 累计打出40局极品牌 常胜将军
            CHENGJIU cj = GetChengJiu(39);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        } 
        else if (count == 80) {
            //40 cj_jipin_80 累计打出80局极品牌 还能厉害些吗
            CHENGJIU cj = GetChengJiu(40);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        } 
        else if (count == 200) {
            //41 cj_jipin_200 累计打出200局极品牌 小有成就
            CHENGJIU cj = GetChengJiu(41);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        } 
        else if (count == 300) {
            //42 cj_jipin_300 累计打出300局极品牌 大有来头
            CHENGJIU cj = GetChengJiu(42);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        } 
        else if (count == 400) {
            //43 cj_jipin_400 累计打出400局极品牌 师出名门
            CHENGJIU cj = GetChengJiu(43);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        } 
        else if (count == 800) {
            //44 cj_jipin_800 累计打出800局极品牌 天下无双
            CHENGJIU cj = GetChengJiu(44);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        } 
        else if (count == 1000) {
            //45 cj_jipin_1000 累计打出1000局极品牌 空前绝后
            CHENGJIU cj = GetChengJiu(45);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        } 
    }
    countCJ = index;
    return cjs;
}

//结算判断
CHENGJIU * CommonFunction::GetChengJiu_GameOver(bool isHuaZhu,   //是否花猪
                                                bool isDaJiao,   //是否大叫
                                                bool isLiuJu,    //是否流局
                                                bool isHu,       //是否胡牌
                                                BYTE fan,        //番数
                                                BYTE & countCJ)
{
    static CHENGJIU cjs[5]; //最大一次获得成就数
    BYTE index = 0;
    
    SetBoolToXML(UD_Last_Hu,isHu);
    if(!isHu)
    {
        SetIntegerToXML(UD_Last_Hu_In3,0);
    }
    
    if (isHuaZhu) {
        //10 cj_huazhu 第一次被查花猪 在劫难逃
        CHENGJIU cj = GetChengJiu(10);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    }
    if (isDaJiao) {
        //11 cj_dajiao 第一次被查大叫 混迹江湖
        CHENGJIU cj = GetChengJiu(11);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    }
    
    if (isLiuJu) {
        //12 cj_liuju 第一次流局 难舍难分
        CHENGJIU cj = GetChengJiu(12);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
        
        //连续流局的次数
        int count_liuju = GetIntegerToXML(UD_LiuJu,0);
        if (count_liuju < 100) { //最多记录100次
            count_liuju++;
        }
        SetIntegerToXML(UD_LiuJu,count_liuju);
        
        if (count_liuju>= 3) {
            //13 cj_liuju_3 第一次连续3局流局 势均力敌
            CHENGJIU cj = GetChengJiu(13);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count_liuju>= 4) {
            //14 cj_liuju_4 第一次连续4局流局 欲罢不能
            CHENGJIU cj = GetChengJiu(14);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count_liuju>= 6) {
            //15 cj_weihu_6 第一次连续6局未胡牌 坐怀不乱
            CHENGJIU cj = GetChengJiu(15);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        
    }
    else
    {
        SetIntegerToXML(UD_LiuJu,0);
    }
    
    
    //---------算翻------------
    
    if (fan>= 3) {
        //16 cj_1_fan_3 第一次打得3番 学无止境
        CHENGJIU cj = GetChengJiu(16);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    }
    
    if (fan>= 4) {
        //17 cj_1_fan_4 第一次打得4番 八面玲珑
        CHENGJIU cj = GetChengJiu(17);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    }
    
    if (fan>= 5) {
        //18 cj_1_fan_5 第一次打得5番 鸿运当头
        CHENGJIU cj = GetChengJiu(18);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    }
    
    if (fan>= 6) {
        //19 cj_1_fan_6 第一次打得6番 鹤立鸡群
        CHENGJIU cj = GetChengJiu(19);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    }
    
    if (fan>= 7) {
        //20 cj_1_fan_7 第一次打得7番 不可多得
        CHENGJIU cj = GetChengJiu(20);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    }
    
    if (fan>= 8) {
        //21 cj_1_fan_8 第一次打得8番 鼎鼎大名
        CHENGJIU cj = GetChengJiu(21);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
            index++;
        }
    }
    
    //翻数大于等于9
    if(fan >= 9)
    {
        //翻数大于等于9的次数
        int count = GetIntegerToXML(UD_FanMoreThan9,0);
        if (count < 10000) { //最多记录10000次
            count++;
        }
        SetIntegerToXML(UD_FanMoreThan9,count);
        
        if (count == 1) {
            //22 cj_1_fan_9 第一次打得9番 百里挑一
            CHENGJIU cj = GetChengJiu(22);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        else if (count == 2) {
            //23 cj_2_fan_9 第2次打得9番 家喻户晓
            CHENGJIU cj = GetChengJiu(23);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        else if (count == 3) {
            //24 cj_3_fan_9 第3次打得9番 寥寥无几
            CHENGJIU cj = GetChengJiu(24);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        else if (count == 4) {
            //25 cj_4_fan_9 第4次打得9番 屈指可数
            CHENGJIU cj = GetChengJiu(25);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        else if (count == 5) {
            //26 cj_5_fan_9 第5次打得9番 大象无形
            CHENGJIU cj = GetChengJiu(26);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        else if (count == 6) {
            //27 cj_6_fan_9 第6次打得9番 通今达古
            CHENGJIU cj = GetChengJiu(27);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
    }
    
    //算累积翻
    if(fan > 0)
    {
        int count = GetIntegerToXML(UD_Fan,0);
        if (count < 100000) { //最多记录100000次
            count += fan;
        }
        SetIntegerToXML(UD_Fan,count);
        
        if (count >= 10) {
            //46 cj_fan_10 累计获得10番 初试身手
            CHENGJIU cj = GetChengJiu(46);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 30) {
            //47 cj_fan_30 累计获得30番 小试牛刀
            CHENGJIU cj = GetChengJiu(47);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 60) {
            //48 cj_fan_60 累计获得60番 小有名气
            CHENGJIU cj = GetChengJiu(48);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 100) {
            //49 cj_fan_100 累计获得100番 锋芒毕露
            CHENGJIU cj = GetChengJiu(49);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 200) {
            //50 cj_fan_200 累计获得200番 初尝胜果
            CHENGJIU cj = GetChengJiu(50);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 300) {
            //51 cj_fan_300 累计获得300番 势如破竹
            CHENGJIU cj = GetChengJiu(51);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 400) {
            //52 cj_fan_400 累计获得400番 来势汹汹
            CHENGJIU cj = GetChengJiu(52);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 500) {
            //53 cj_fan_500 累计获得500番 这没什么！
            CHENGJIU cj = GetChengJiu(53);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 600) {
            //54 cj_fan_600 累计获得600番 街头霸王
            CHENGJIU cj = GetChengJiu(54);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 700) {
            //55 cj_fan_700 累计获得700番 鸟枪换炮
            CHENGJIU cj = GetChengJiu(55);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 800) {
            //56 cj_fan_800 累计获得800番 重装上阵
            CHENGJIU cj = GetChengJiu(56);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 900) {
            //57 cj_fan_900 累计获得900番 千番在即
            CHENGJIU cj = GetChengJiu(57);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 1000) {
            //58 cj_fan_1000 累计获得1000番 唯我独尊
            CHENGJIU cj = GetChengJiu(58);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 2000) {
            //59 cj_fan_2000 累计获得2000番 登峰造极
            CHENGJIU cj = GetChengJiu(59);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 3000) {
            //60 cj_fan_3000 累计获得3000番 笑傲江湖
            CHENGJIU cj = GetChengJiu(60);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 5000) {
            //61 cj_fan_5000 累计获得5000番 功成名就
            CHENGJIU cj = GetChengJiu(61);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
        if (count >= 10000) {
            //62 cj_fan_10000 累计获得10000番 雀圣
            CHENGJIU cj = GetChengJiu(62);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[index] = cj;
                index++;
            }
        }
    }
    countCJ = index;
    return cjs;
}

//获取番数的最高成就名称，显示为级别
char * CommonFunction::GetMaxFanCJName()
{
    static CHENGJIU cj = GetChengJiu(62);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(61);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(60);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(59);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(58);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(57);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(56);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(54);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(53);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(52);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(51);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(50);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(49);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(48);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(47);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    cj = GetChengJiu(46);
    if (GetBoolToXML(cj.key,false)) {
        return cj.name;
    }
    
    return NULL;
}

//放炮判断 isDouble 是否是双响以上
CHENGJIU * CommonFunction::GetChengJiu_FangPao(bool isDouble,BYTE & countCJ)    
{
    static CHENGJIU cjs[2]; //最大一次获得成就数
    BYTE index = 0;
    
    //3，cj_fangpao，第一次放炮
    CHENGJIU cj = GetChengJiu(3);
    if(!GetBoolToXML(cj.key,false))
    {
        SetBoolToXML(cj.key,true);
        cjs[index] = cj;
        index++;
    }
    
    //65,cj_fangpao_to2,第一次一炮双响（放炮）
    if (isDouble) {
        CHENGJIU cj = GetChengJiu(65);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[index] = cj;
        }
    }
    countCJ = index;
    return cjs;
}

//抢杠判断 isQiang=true 抢杠 isQiang=false 被抢
CHENGJIU * CommonFunction::GetChengJiu_QiangGang(bool isQiang,BYTE & countCJ)  
{
    static CHENGJIU cjs[1]; //最大一次获得成就数
    countCJ = 0;
    if (isQiang) {
        //抢杠
        int count = GetIntegerToXML(UD_QiangGang,0);
        if (count < 10000) { //抢杠只记录10000次
            count++;
        }
        SetIntegerToXML(UD_QiangGang,count);
        
        if (count == 1) {
            //7，cj_qianggang，第一次抢杠
            CHENGJIU cj = GetChengJiu(7);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[0] = cj;
                countCJ = 1;
            }
        }
        else if (count == 10) {
            //63，cj_qianggang_10，第10次抢杠
            CHENGJIU cj = GetChengJiu(63);
            if(!GetBoolToXML(cj.key,false))
            {
                SetBoolToXML(cj.key,true);
                cjs[0]= cj;
                countCJ = 1;
            }
        }
    }
    else
    {
        //被抢杠
        //8,cj_beiqianggang,第一次被抢杠
        CHENGJIU cj = GetChengJiu(8);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[0]= cj;
            countCJ = 1;
        }
    }
    
    return cjs;
}

//出牌判断
CHENGJIU * CommonFunction::GetChengJiu_OutCard_OverTime(BYTE & countCJ)    
{
    static CHENGJIU cjs[1]; //最大一次获得成就数
    countCJ = 0;
    int count = GetIntegerToXML(UD_OverTime,0);
    if (count < 10000) { //超时出牌只记录10000次
        count++;
    }
    SetIntegerToXML(UD_OverTime,count);
    
    if (count == 1) {
        //32 cj_1_overtime 第一次超时未出牌
        CHENGJIU cj = GetChengJiu(32);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[0] = cj;
            countCJ = 1;
        }
    }
    else if (count == 10) {
        //33 cj_1_overtime 第10次超时未出牌
        CHENGJIU cj = GetChengJiu(32);
        if(!GetBoolToXML(cj.key,false))
        {
            SetBoolToXML(cj.key,true);
            cjs[0]= cj;
            countCJ = 1;
        }
    }
    
    return cjs;
}

////#pragma mark ---------------结算相关---------------------
//获取胡牌类型的字符串
string CommonFunction::HuTypeToString(int idx)
{
	switch(idx)
	{
        case PINGHU:						// 1 平胡
            return string("平胡1番");
            
        case PENGPENGHU:					// 2 碰碰胡
            return string("碰碰胡2番");
            
        case QINGYISE:						// 3 清一色
            return string("清一色3番");
            
        case YAOJIU:						// 4 幺九
            return string("幺九3番");
            
        case QIDUI:							// 5 七对
            return string("七对3番");
            
        case QING_PENG:						// 6 清碰
            return string("清碰4番");
            
        case JIANG_PENG:					// 7 将碰
            return string("将碰4番");
            
        case LONG_QIDUI:					// 8 龙七对
            return string("龙七对4番");
            
        case QING_QIDUI:					// 9 清七对
            return string("清七对5番");
            
        case QING_YAOJIU:					// 10清幺九
            return string("清幺九5番");
            
        case QINGLONG_QIDUI:				// 11青龙七对
            return string("青龙七对6番");
            
        case TIANHU:						 //1 天胡		6番
            return string("天胡6番");
            
        case DIHU:							 //2 地胡		6番
            return string("地胡6番");
            
        case RENHU:							 //3 人和		6番
            return string("地胡6番");
            
        case ZIMOFAN:						 //4 自摸加番	1番
            return string("自摸加番1番");
            
        case GANGKAI:						 //5 杠开		1番
            return string("杠开1番");
            
        case GANGPAO:						 //6 杠炮		1番
            return string("杠炮1番");
            
        case QIANGGANG:						 //7 抢杠		1番
            return string("抢杠1番");
            
        case GEN:							//8 根			1番
            return string("根1番");
            
        case GANG:							//9 杠			1番
            return string("杠1番");
	}
    
	return string("");
}

//判断是否有一种胡的类型
bool CommonFunction::HaveHuType(int type,HU_CURT huCurt)
{
    for(int j=0; j< huCurt.nCount; j++)
    {
        if (huCurt.nMethod[j] == type) {
            return true;
        }
    }
    return false;
}

////#pragma mark ---------------玩家信息---------------------

//在一关中 创建新的三个电脑玩家
void CommonFunction::CreatePlayersByGuan(BYTE guanKa)
{
    ClearPlayersByGuan(guanKa);
    
    static char temp[20];
    memset(temp,0,sizeof(temp));
    char * str = temp;
    
    BYTE pID = GetIntegerToXML(UD_User_Id,0);
    BYTE nId1 = 0;
    BYTE nId2 = 0;
    BYTE nId3 = 0;
    
    //rand()%ICO_COUNT 0~11
    while (nId1 == 0 || nId1 == pID) {
        nId1 = rand()%ICO_COUNT + 1; 
    }
    while (nId2 == 0 || nId2 == pID || nId2 == nId1) {
        nId2 = rand()%ICO_COUNT + 1; 
    }
    while (nId3 == 0 || nId3 == pID || nId3 == nId1 || nId3 == nId2) {
        nId3 = rand()%ICO_COUNT + 1; 
    }
    sprintf(str,"%s_%d_%d","player",guanKa,0);
    SetIntegerToXML(str,nId1);
    sprintf(str,"%s_%d_%d","player",guanKa,1);
    SetIntegerToXML(str,nId2);
    sprintf(str,"%s_%d_%d","player",guanKa,2);
    SetIntegerToXML(str,nId3);
    
}

//获取玩家
PLAYER * CommonFunction::GetPlayersByGuan(BYTE guanKa)
{
    static PLAYER player[3];
    static char temp[20];
    memset(temp,0,sizeof(temp));
    char * str = temp;
    
    for (int i=0; i<3; i++) {
        sprintf(str,"%s_%d_%d","player",guanKa,i);
        player[i]= CreatePlayer(GetIntegerToXML(str,0));
        
        player[i].nGuan = guanKa;
        
        sprintf(str,"%s_%d_%d","player_source",guanKa,i);
        player[i].nSource = GetIntegerToXML(str,0);
        
        //CCLOG("get g %d, i %d, s %d", guanKa, i, player[i].nSource);
    }
    
    return player;
}

//保存玩家数据
void CommonFunction::SetPlayers(PLAYER * player)
{
    static char temp[20];
    memset(temp,0,sizeof(temp));
    char * str = temp;
    
    for (int i=0; i<3; i++) {     
        sprintf(str,"%s_%d_%d","player_source",player[i].nGuan,i);
        SetIntegerToXML(str,player[i].nSource);
        CCLOG("set g %d, i %d, s %d", player[i].nGuan, i, player[i].nSource);
    }
}

//清除玩家数据
void CommonFunction::ClearPlayersByGuan(BYTE guanKa)
{
    static char temp[20];
    memset(temp,0,sizeof(temp));
    char * str = temp;
    
    for (int i=0; i<3; i++) {
        sprintf(str,"%s_%d_%d","player",guanKa,i);
        SetIntegerToXML(str,0);
        sprintf(str,"%s_%d_%d","player_source",guanKa,i);
        SetIntegerToXML(str,0);
    }
}

//获取玩家
PLAYER CommonFunction::GetUser()
{
    PLAYER user = CreatePlayer(GetIntegerToXML(UD_User_Id,0));
    
    return user;
}
//保存玩家
void CommonFunction::SetUser(PLAYER user)
{
    SetIntegerToXML(UD_User_Id,user.nId);
    SetStringToXML(UD_User_Name,user.nName);
}


PLAYER CommonFunction::CreatePlayer(BYTE id)
{
    PLAYER p;
    p.clear();
    p.nId = id;
    sprintf(p.nIco,"%s%d%s","ico_",id,".png");
    sprintf(p.nShowImage,"%s%d%s","show_",id,".png");
    switch (id) {
        case 0:
            sprintf(p.nIco,"%s%d%s","ico_",1,".png");
            sprintf(p.nShowImage,"%s%d%s","show_",1,".png");
            sprintf(p.nName,"%s","星星");
            p.nUtype = UT_MAN;
            break;
        case 1:
            sprintf(p.nName,"%s","星星");
            p.nUtype = UT_MAN;
            break;
        case 2:
            sprintf(p.nName,"%s","美美");
            p.nUtype = UT_WOMAN;
            break;
        case 3:
            sprintf(p.nName,"%s","小坏");
            p.nUtype = UT_MAN;
            break;
        case 4:
            sprintf(p.nName,"%s","小安安");
            p.nUtype = UT_WOMAN;
            break;
        case 5:
            sprintf(p.nName,"%s","南勇");
            p.nUtype = UT_MAN;
            break;
        case 6:
            sprintf(p.nName,"%s","可儿");
            p.nUtype = UT_WOMAN;
            break;
        case 7:
            sprintf(p.nName,"%s","虎小帅");
            p.nUtype = UT_MAN;
            break;
        case 8:
            sprintf(p.nName,"%s","虎妞");
            p.nUtype = UT_WOMAN;
            break;
        case 9:
            sprintf(p.nName,"%s","勇哥");
            p.nUtype = UT_MAN;
            break;
        case 10:
            sprintf(p.nName,"%s","绣绣");
            p.nUtype = UT_WOMAN;
            break;
        case 11:
            sprintf(p.nName,"%s","柳无言");
            p.nUtype = UT_MAN;
            break;
        case 12:
            sprintf(p.nName,"%s","小淘");
            p.nUtype = UT_WOMAN;
            break;
        default:
            break;
    }
    return p;
}

//获取玩家
PLAYER CommonFunction::GetNetUser()
{
    PLAYER user = CreateNetPlayer(GetIntegerToXML(UD_Net_User_Id,1));
    
    BYTE n = FindLoginUserByMaxIndex();
    char userName[20];
    sprintf(userName, "%s%s%d", UD_Net_User_Name, "_", n);
    char userPass[20];
    sprintf(userPass, "%s%s%d", UD_Net_User_Pass, "_", n);
    
    sprintf(user.nName,"%s",GetStringToXML(userName,"").c_str());
    sprintf(user.nPass,"%s",GetStringToXML(userPass,"").c_str());
    
    return user;
}
//保存玩家
void CommonFunction::SetNetUser(PLAYER user)
{
    bool isExist = false;
    char userName[20];
    BYTE targetNum = 0;
    
    //判断是否存在于列表当中
    for (int i=1; i<=5; i++) {
        sprintf(userName, "%s%s%d", UD_Net_User_Name, "_", i);
        if (strcmp(GetStringToXML(userName,"").c_str(), user.nName) == 0) {
            isExist = true;
            targetNum = i;
            break;
        }
    }
    
    if (isExist) {//存在
        int maxUserIndex = FindLoginUserMaxIndex();
        char targetUserIndex[20];
        sprintf(targetUserIndex, "%s%s%d", UD_Net_User_Index, "_", targetNum);
        BYTE indexValue = GetIntegerToXML(targetUserIndex,0);
        if (maxUserIndex == indexValue) {//本次登陆跟上次登陆的是同一个user
            //不用处理
        }else {//本次登陆跟上次登陆的不是同一个user,则更新此次登陆user的index
            SetIntegerToXML(targetUserIndex, maxUserIndex+1);
        }
        
        //更新密码
        char targetUserPass[20];
        sprintf(targetUserPass, "%s%s%d", UD_Net_User_Pass, "_", targetNum);
        SetStringToXML(targetUserPass, user.nPass);
        
    }else {//不存在
        char uName[20];
        char uPass[20];
        char uIndex[20];
        BYTE loginUserCount = FindLoginUserCount();
        if (loginUserCount == 5) {//已满5个
            targetNum = FindLoginUserByMinIndex();//找到最小索引那个,覆盖
        }else {//不满5个, 找到第一个空的
            for (int j=1; j<=5; j++) {
                sprintf(uName, "%s%s%d", UD_Net_User_Name, "_", j);
                if (strcmp(GetStringToXML(uName,"").c_str(), "") == 0){
                    targetNum = j;
                    break;
                }
            }
        }
        
        sprintf(uName, "%s%s%d", UD_Net_User_Name, "_", targetNum);
        sprintf(uPass, "%s%s%d", UD_Net_User_Pass, "_", targetNum);
        sprintf(uIndex, "%s%s%d", UD_Net_User_Index, "_", targetNum);
        SetStringToXML(uName,user.nName);
        SetStringToXML(uPass,user.nPass);
        SetIntegerToXML(uIndex, FindLoginUserMaxIndex()+1);
    }
    
    
    SetIntegerToXML(UD_Net_User_Id,user.nId);
    
}


PLAYER CommonFunction::CreateNetPlayer(BYTE id)
{
    PLAYER p;
    p.clear();
    p.nId = id;
    switch (id) {
        case 1:
            sprintf(p.nIco,"%s","ico_9.png");
            sprintf(p.nShowImage,"%s","show_9.png");
            p.nUtype = UT_MAN;
            break;
        case 2:
            sprintf(p.nIco,"%s","ico_11.png");
            sprintf(p.nShowImage,"%s","show_11.png");
            p.nUtype = UT_MAN;
            break;
        case 3:
            sprintf(p.nIco,"%s","ico_10.png");
            sprintf(p.nShowImage,"%s","show_10.png");
            p.nUtype = UT_WOMAN;
            break;
        case 4:
            sprintf(p.nIco,"%s","ico_2.png");
            sprintf(p.nShowImage,"%s","show_2.png");
            p.nUtype = UT_WOMAN;
            break;
        case 5:
            sprintf(p.nIco,"%s","ico_3.png");
            sprintf(p.nShowImage,"%s","show_3.png");
            p.nUtype = UT_MAN;
            break;
        case 6:
            sprintf(p.nIco,"%s","ico_12.png");
            sprintf(p.nShowImage,"%s","show_12.png");
            p.nUtype = UT_WOMAN;
            break;
        case 7:
            sprintf(p.nIco,"%s","ico_7.png");
            sprintf(p.nShowImage,"%s","show_7.png");
            p.nUtype = UT_MAN;
            break;
        case 8:
            sprintf(p.nIco,"%s","ico_4.png");
            sprintf(p.nShowImage,"%s","show_4.png");
            p.nUtype = UT_WOMAN;
            break;
        case 9:
            sprintf(p.nIco,"%s","ico_5.png");
            sprintf(p.nShowImage,"%s","show_5.png");
            p.nUtype = UT_MAN;
            break;
        case 10:
            sprintf(p.nIco,"%s","ico_8.png");
            sprintf(p.nShowImage,"%s","show_8.png");
            p.nUtype = UT_WOMAN;
            break;
        case 11:
            sprintf(p.nIco,"%s","ico_6.png");
            sprintf(p.nShowImage,"%s","show_6.png");
            p.nUtype = UT_WOMAN;
            break;
        case 12:
            sprintf(p.nIco,"%s","ico_1.png");
            sprintf(p.nShowImage,"%s","show_1.png");
            p.nUtype = UT_MAN;
            break;
        default:
            break;
    }
    return p;
}

//根据设备获取数值，安卓和iPad数值要*2
int CommonFunction::GetValueByDev(int size)
{
    if (ISANDROID || isIpad()) {
        return size * 2;
    }
    return size;
}

char* CommonFunction::str_replace(char* source, char* sub,char* rep)
{
    char result[512];
    /*pc1 是复制到结果result的扫描指针*/
    /*pc2 是扫描 source 的辅助指针*/
    /*pc3 寻找子串时,为检查变化中的source是否与子串相等,是指向sub的扫描指针 */
    /*找到匹配后,为了复制到结果串,是指向rep的扫描指针*/
    char *pc1, *pc2, *pc3;
    int isource, isub, irep;
    isub = strlen(sub); /*对比字符串的长度*/
    irep = strlen(rep); /*替换字符串的长度*/
    isource= strlen(source);/*源字符串的长度*/
    if(NULL == *sub)
        return strdup(source);
    /*申请结果串需要的空间*/
    //result = (char *)malloc(( (irep > isub) ? (float)strlen(source) / isub* irep+ 1:isource ) * sizeof(char));
    pc1 = result; /*为pc1依次复制结果串的每个字节作准备*/
    while(*source != NULL)
    {
        /*为检查source与sub是否相等作准备,为pc2,pc3 赋初值*/
        pc2 = source;
        pc3 = sub;
        /* 出循环的（任一）条件是：
         * *pc2不等于 *pc3（与子串不相等）
         * pc2 到源串结尾
         * pc3 到源串结尾（此时,检查了全部子串,source处与sub相等）
         *****************************************************/
        while(*pc2 == *pc3 && *pc3 != NULL && *pc2 != NULL)
            pc2++, pc3++;
        /* 如果找到了子串,进行以下处理工作*/
        if(NULL == *pc3)
        {
            pc3 = rep;
            /*将替代串追加到结果串*/
            while(*pc3 != NULL)
                *pc1++ = *pc3++;
            pc2--;
            source = pc2;
            /* 检查 source与sub相等的循环结束后，
             * pc2 对应的位置是在 sub 中串结束符处。该是源串中下一个位置。
             * 将source 指向其前面一个字符。
             ***************************************************/
        }
        else /*如果没找到子串,下面复制source所指的字节到结果串*/
            *pc1++ = *source;
        source++; /* 将source向后移一个字符*/
    }
    *pc1 = NULL;
    
    return result;
}

//取得常用短语数组
char* CommonFunction::getPhrases(){
    
    static char phrases[10][100];
    memset(phrases, 0, sizeof(phrases));
    
    strcpy(phrases[0], "大家好,很高兴见到各位!");
    strcpy(phrases[1], "快点吧,我等到花儿都谢了。");
    strcpy(phrases[2], "你是MM,还是GG?");
    strcpy(phrases[3], "再见了,我会想念大家都。");
    strcpy(phrases[4], "不要走,决战打到天亮!");
    strcpy(phrases[5], "搞个串串哦,咋有遭点炮了。");
    strcpy(phrases[6], "输家不开口,赢家不许走");
    strcpy(phrases[7], "今天输安逸了,下次再来收拾你们");
    
    return phrases[0];
}

int CommonFunction::calcCharCount(const char * pszText)
{
    int n = 0;
    char ch = 0;
    while ((ch = *pszText))
    {
        CC_BREAK_IF(! ch);
        
        if (0x80 != (0xC0 & ch))
        {
            ++n;
        }
        ++pszText;
    }
    return n;
}

string CommonFunction::subString(string insertStr,int length)
{
    if (length <=0) {
        return "";
    }
    const char * pszText = insertStr.c_str();
    int n = 0;
    char ch = 0;
    int index = 0;
    while ((ch = *pszText))
    {
        CC_BREAK_IF(! ch);
        
        if (0x80 != (0xC0 & ch))
        {
            ++n;
            if (n==length+1) {
                break;
            }
        }
        ++pszText;
        ++index;
    }
    string outStr = insertStr.substr(0,index);
    return outStr;
}

string CommonFunction::subString(string insertStr,int index,int length)
{
    return subString(trimString(insertStr, index),length);
}

string CommonFunction::trimString(string insertStr,int length)
{
    if (length <=0) {
        return insertStr;
    }
    const char * pszText = insertStr.c_str();
    int n = 0;
    char ch = 0;
    int index = 0;
    while ((ch = *pszText))
    {
        CC_BREAK_IF(! ch);
        
        if (0x80 != (0xC0 & ch))
        {
            ++n;
            if (n==length+1) {
                break;
            }
        }
        ++pszText;
        ++index;
    }
    string outStr = insertStr.substr(index);
    return outStr;
}

int CommonFunction::FindLoginUserMaxIndex(){
    //先找出最大的索引
    int maxUserIndex = GetIntegerToXML(UD_Net_User_Index1,0);
    char userIndex[20];
    for (int i=2; i<=5; i++) {
        sprintf(userIndex, "%s%s%d", UD_Net_User_Index, "_", i);
        if (GetIntegerToXML(userIndex,0) > maxUserIndex) {
            maxUserIndex = GetIntegerToXML(userIndex,0);
        }
    }
    
    return maxUserIndex;
}

int CommonFunction::FindLoginUserMinIndex(){
    //先找出小的索引
    int minUserIndex = GetIntegerToXML(UD_Net_User_Index1,0);
    char userIndex[20];
    for (int i=2; i<=5; i++) {
        sprintf(userIndex, "%s%s%d", UD_Net_User_Index, "_", i);
        if (GetIntegerToXML(userIndex,0) < minUserIndex) {
            minUserIndex = GetIntegerToXML(userIndex,0);
        }
    }
    
    return minUserIndex;
}

BYTE CommonFunction::FindLoginUserByMaxIndex(){
    //先找出最大的索引
    int maxUserIndex = FindLoginUserMaxIndex();
    
    //找出最大索引对应的序号
    char userIndex[20];
    for (int j=1; j<=5; j++) {
        sprintf(userIndex, "%s%s%d", UD_Net_User_Index, "_", j);
        if (GetIntegerToXML(userIndex,0) == maxUserIndex) {
            return j;
        }
    }
    
    return 1;
}

BYTE CommonFunction::FindLoginUserByMinIndex(){
    //先找出小的索引
    int minUserIndex = FindLoginUserMinIndex();
    
    //找出最小索引对应的序号
    char userIndex[20];
    for (int j=1; j<=5; j++) {
        sprintf(userIndex, "%s%s%d", UD_Net_User_Index, "_", j);
        if (GetIntegerToXML(userIndex,0) == minUserIndex) {
            return j;
        }
    }
    
    return 1;
}

BYTE CommonFunction::FindLoginUserCount(){
    BYTE count = 0;
    for (int i=1; i<=5; i++) {
        char userName[20];
        sprintf(userName, "%s%s%d", UD_Net_User_Name, "_", i);
        
        if (strcmp(GetStringToXML(userName,"").c_str(),"") != 0) {
            count++;
        }
    }
    
    return count;
}

string CommonFunction::getMAC()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;//定义Jni函数信息结构体 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, 
                                                 "org/cocos2dx/lib/Cocos2dxActivity", 
                                                 "getLocalMacAddress","()Ljava/lang/String;");
	if (!isHave) { 
		CCLOG("jni:此函数不存在"); 
	}else{ 
		CCLOG("jni:此函数存在"); 
		//调用此函数 
		jstring str = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID); 
		minfo.env->DeleteLocalRef(minfo.classID);
		CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
		ret->autorelease();
        
		//CCLOG(ret->m_sString.c_str());
        
		MD5 md5;
		md5.update(ret->m_sString);
        
		CCLOG(md5.toString().c_str());
        
		return string(md5.toString().c_str());
	}
    
	return string("");
    
#else 
    return string("");
    
#endif
}

//判断android系统版本是否>=2.2
bool CommonFunction::isValidAndroidSysVer(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;//定义Jni函数信息结构体 
	jboolean ret = false;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, 
                                                 "com/cgc/frame/Common", 
                                                 "isValidSysVersion","()Z");
	if (!isHave) { 
		CCLOG("jni:此函数不存在"); 
	}else{ 
		CCLOG("jni:此函数存在"); 
		//调用此函数 
		ret = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID); 
		minfo.env->DeleteLocalRef(minfo.classID);
        
		return ret;
	}
    
	return true;
#else
	return true;
#endif
}


bool CommonFunction::payfee(int payid,int feeID)
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
   // JniMethodInfo minfo;//定义Jni函数信息结构体
//	bool isHave = JniHelper::getStaticMethodInfo(minfo,
      //                                           "org/cocos2dx/lib/Cocos2dxActivity",
      //                                           "payFeeCallByCpp","(II)Z");
//	if (!isHave) {
//		CCLOG("jni: in payfee此函数不存在");
//		return false;
//	}
	
//	JNIEnv* env = minfo.env;
//    minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID,payid,feeID);
    
    
//#endif
    
    
    return true;
}

int CommonFunction::AddCoin(int n)
{
    //paddy
    if (n<0)
    {
        return -1;
    }
    int nCoin = GetIntegerToXML(UD_SINGLE_COIN, 0);
    if (nCoin +n > 99999)
    {
        nCoin = 99999;
    }
    else
    {
        nCoin += n;
    }
    SetIntegerToXML(UD_SINGLE_COIN, nCoin);
    CCLOG("add coin:%d", n);
    return nCoin;
}

int CommonFunction::SubCoin(int n)
{
    //paddy
    if (n<0)
    {
        return -1;
    }
    
    int nCoin = GetIntegerToXML(UD_SINGLE_COIN, -1);
    
    if (nCoin<0)
    {
        return -1;
    }
    nCoin -= n;
    if (nCoin <0)
    {
        nCoin = 0;
    }
    SetIntegerToXML(UD_SINGLE_COIN, nCoin);
    CCLOG("SubCoin:%d", n);
    return nCoin;
}

bool CommonFunction::IsEnoughCoin()
{
    int nCoin = GetIntegerToXML(UD_SINGLE_COIN, 0);
    if (nCoin<COIN_MIN)
    {
        return false;
    }
    return  true;
}


bool CommonFunction::BuyCard()
{
    //paddy
    bool bTACard = GetBoolToXML(UD_SINGLE_TACARD, false);
    
    if (bTACard) {
        return false;
    }
    
    SetBoolToXML(UD_SINGLE_TACARD, true);
    return true;
}

bool CommonFunction::OpenGuanka()
{
//    GUANKA_STATS gkState;
//    for (int i =2; i<=13; ++i)
//    {
//        gkState.guanKa = i;
//        gkState.isLock = false;
//        CommonFunction::SetGuanKaStats(gkState);
//    }
    
//    GUANKA_STATS gkState;
//    gkState.guanKa = 2;
//    gkState.isLock = false;
//    CommonFunction::SetGuanKaStats(gkState);
    
    SetBoolToXML(UD_GUANKA_OPEN, true);
    CCLOG("OpenGuanka");
    return true;
}

bool CommonFunction::DelockGuanka()
{
    GUANKA_STATS gkState;
    int nGK = GetIntegerToXML(UD_CurrentGuanKa,1) + 1;
    for (int i =nGK; i<=13; ++i)
    {
        gkState.guanKa = i;
        gkState.isLock = false;
        CommonFunction::SetGuanKaStats(gkState);
    }
    
    SetBoolToXML(UD_GUANKA_DELOCK, true);
    CCLOG("DelockGuanka");
    return true;
}

int CommonFunction::SubmitCoin(int nCoin)
{
//    int nCoin = GetIntegerToXML(UD_SINGLE_COIN, 0);
    
    if (IS_COMMUNITY  && nCoin>0)
    {
        bool bIsGkOpened = GetBoolToXML(UD_GUANKA_OPEN, false);
        SetBoolToXML(UD_IS_MAX_COIN_REC, false);
        
        if (bIsGkOpened)
        {
            CommonFunction::callEgameAPI(API_ID_SUBMIT_SCORE, nCoin);
            int nRecore = GetIntegerToXML(UD_COIN_MAX_RECORD, 0);
            
            if (nCoin>nRecore)
            {
                SetIntegerToXML(UD_COIN_MAX_RECORD, nCoin);
                SetBoolToXML(UD_IS_MAX_COIN_REC, true);
                return 1;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            CommonFunction::callEgameAPI(API_ID_SUBMIT_SCORE, -1);
        }
    }
    
    return 0;
}

bool CommonFunction::callEgameAPI(int arg1, int arg2)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    JniMethodInfo minfo;//定义Jni函数信息结构体
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 "org/cocos2dx/lib/Cocos2dxActivity",
                                                 "methodCallByCpp","(II)Z");
	if (!isHave) {
		CCLOG("jni: methodCallByCpp此函数不存在");
		return false;
	}
	
	JNIEnv* env = minfo.env;
    minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID, arg1, arg2);
    
    
#endif
    
    return true;
}

char * CommonFunction::GBKToUTF8( const char* szStr )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static char szBuf[1024];
	int nOutLen = 1024;
	memset(szBuf,0,nOutLen);
	iconv_t cd;
	cd = iconv_open("UTF-8","GB2312");
	if (cd==0) return szBuf;
	int nInlen = strlen(szStr);
	const char **pin = &szStr;
	char *pout = szBuf;
	if (iconv(cd,(const char **)(&szStr),(size_t *)&nInlen,&pout,(size_t *)&nOutLen)==-1)
	{
		szBuf[0] = 0;
	}
	iconv_close(cd);
	return szBuf;
#endif

	return (char*)szStr;
}