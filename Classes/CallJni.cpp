#include "CallJni.h"

void CallJni::forUnlockLevel(int nWhich)
{
#if(CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
	JniMethodInfo minfo;
	jobject jobj;
	jint jnWhich = (int)nWhich;
	if(JniHelper::getStaticMethodInfo(minfo, "com/lyp/xzmj/xzmj2", "getInstance", "()Ljava/lang/Object;"))
	{
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		if(JniHelper::getMethodInfo(minfo, "com/lyp/xzmj/xzmj2", "send_billing_for_get_levellock", "(I)V"))
		{
			minfo.env->CallVoidMethod(jobj, minfo.methodID, jnWhich);
		}
	}
#endif
}

void CallJni::forGet1Goal()
{
#if(CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
	JniMethodInfo minfo;
	jobject jobj;
	if(JniHelper::getStaticMethodInfo(minfo, "com/lyp/xzmj/xzmj2", "getInstance", "()Ljava/lang/Object;"))
	{
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		if(JniHelper::getMethodInfo(minfo, "com/lyp/xzmj/xzmj2", "send_billing_for_get_1Goal", "()V"))
		{
			minfo.env->CallVoidMethod(jobj, minfo.methodID);
		}
	}
#endif
}

void CallJni::forGet5Goal()
{
#if(CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
	JniMethodInfo minfo;
	jobject jobj;
	if(JniHelper::getStaticMethodInfo(minfo, "com/lyp/xzmj/xzmj2", "getInstance", "()Ljava/lang/Object;"))
	{
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		if(JniHelper::getMethodInfo(minfo, "com/lyp/xzmj/xzmj2", "send_billing_for_get_5Goal", "()V"))
		{
			minfo.env->CallVoidMethod(jobj, minfo.methodID);
		}
	}
#endif
}

void CallJni::forGet10Goal()
{
#if(CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
	JniMethodInfo minfo;
	jobject jobj;
	if(JniHelper::getStaticMethodInfo(minfo, "com/lyp/xzmj/xzmj2", "getInstance", "()Ljava/lang/Object;"))
	{
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		if(JniHelper::getMethodInfo(minfo, "com/lyp/xzmj/xzmj2", "send_billing_for_get_10Goal", "()V"))
		{
			minfo.env->CallVoidMethod(jobj, minfo.methodID);
		}
	}
#endif
}
