#ifndef __CALL_JNI_H__
#define __CALL_JNI_H__

#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#endif



class CallJni
{
public:

	static void forUnlockLevel(int nWhich);		//解锁关卡
	static void forGet1Goal();
	static void forGet5Goal();
	static void forGet10Goal();

};


#endif
