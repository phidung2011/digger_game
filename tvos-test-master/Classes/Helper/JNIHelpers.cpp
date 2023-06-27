//
//  JniHelpers.cpp
//  gamebase
//
//  Created by Phi Dzung on 7/8/15.
//
//
#include "JniHelpers.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "jni.h"
#include "jni/JniHelper.h"
#endif

//void CallMethodJava::callShowAdmob() {
//    JniMethodInfo t;
//    jobject myInstance;
//    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity",
//                                       "getObject", "()Ljava/lang/Object;")) {
//        myInstance = t.env->CallStaticObjectMethod(t.classID, t.methodID);
//        JniMethodInfo t2;
//        if (myInstance
//            && JniHelper::getMethodInfo(t2, "org/cocos2dx/cpp/AppActivity",
//                                        "callShowInterstitialAdmob",
//                                        "()V")) {
//                t2.env->CallNonvirtualVoidMethod(myInstance, t2.classID,
//                                                 t2.methodID);
//            }
//    }
//}

void JniHelpers::jniCommonVoidCall(const char* methodName,
		const char* classPath, unsigned int level, unsigned long score,
		unsigned int obstacles) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(IJI)V");

	if (isHave)
	{
		jlong scoreArg1 = score;

		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, level, scoreArg1, obstacles);

	}
#endif
}

unsigned int JniHelpers::jniCommonIntCall(const char* methodName,
		const char* classPath, const char* arg0) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;)I");

	if (isHave)
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);

		jint ret = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0);

		minfo.env->DeleteLocalRef(stringArg0);

		return (unsigned int)ret;
	}
#endif
	return 0;
}

unsigned int JniHelpers::jniCommonIntCall(const char* methodName,
		const char* classPath) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "()I");

	if (isHave)
	{

		jint ret = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);

		return (unsigned int)ret;
	}
#endif
	return 0;
}

std::string JniHelpers::jniCommonStringCall(const char* methodName,
		const char* classPath, const char* arg0) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;)Ljava/lang/String;");

	std::string st;
	if (isHave)
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);

		jstring ret = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID, stringArg0);

		st = cocos2d::JniHelper::jstring2string(ret);

		minfo.env->DeleteLocalRef(stringArg0);

	}
	return st;
#endif
}

unsigned int JniHelpers::jniCommonIntCall(const char* methodName,
		const char* classPath, const char* arg0, bool looping) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;Z)I");

	if (isHave)
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);

		jint ret = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0, looping);

		minfo.env->DeleteLocalRef(stringArg0);

		return (unsigned int)ret;
	}
#endif

	return 0;
}

void JniHelpers::jniCommonVoidCall(const char* methodName,
		const char* classPath, const char* arg0) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo, classPath, methodName, "(Ljava/lang/String;)V");

	if (isHave)
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);

		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0);

		minfo.env->DeleteLocalRef(stringArg0);
	}
#endif
}

void JniHelpers::jniCommonVoidCall(const char* methodName,
		const char* classPath, const char* arg0, bool looping) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;Z)V");

	if (isHave)
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);

		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0, looping);

		minfo.env->DeleteLocalRef(stringArg0);

	}
#endif

}

void JniHelpers::jniCommonVoidCall(const char* methodName,
		const char* classPath, const char* arg0, long score) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;J)V");

	if (isHave)
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);
		jlong scoreArg1 = score;

		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0, scoreArg1);

		minfo.env->DeleteLocalRef(stringArg0);

	}
#endif
}

void JniHelpers::jniCommonVoidCall(const char* methodName,
		const char* classPath, const char* arg0, int numSteps) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;I)V");

	if (isHave)
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);

		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0, numSteps);

		minfo.env->DeleteLocalRef(stringArg0);

	}
#endif
}
void JniHelpers::jniCommonVoidCall(const char* methodName,
		const char* classPath, const char* arg0, const char* arg1) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;Ljava/lang/String;)V");

	if (isHave)
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);
		jstring stringArg1 = minfo.env->NewStringUTF(arg1);
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0, stringArg1);

		minfo.env->DeleteLocalRef(stringArg0);
		minfo.env->DeleteLocalRef(stringArg1);

	}
#endif
}
void JniHelpers::jniCommonVoidCall(const char* methodName,
		const char* classPath) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "()V");

	if (isHave)
	{
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
#endif
}

void JniHelpers::jniCommonVoidCall(const char* methodName,
		const char* classPath, unsigned int arg0) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(I)V");

	if (isHave)
	{
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, arg0);
	}
#endif
}

float JniHelpers::jniCommonFloatCall(const char* methodName,
		const char* classPath) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "()F");

	if (isHave)
	{
		jfloat ret = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);
		return (float)ret;
	}
#endif

	return 0.0;
}

void JniHelpers::jniCommonVoidCall(const char* methodName,
		const char* classPath, float arg0) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo, classPath, methodName, "(F)V");

	if (isHave)
	{
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, arg0);
	}
#endif
}

bool JniHelpers::jniCommonBoolCall(const char* methodName,
		const char* classPath) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "()Z");

	if (isHave)
	{
		jboolean ret = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID);
		return (bool)ret;
	}
#endif
	return false;
}

bool JniHelpers::jniCommonBoolCall(const char* methodName,
		const char* classPath, unsigned int arg0) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo minfo;

	bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(I)Z");

	if (isHave)
	{
		jboolean ret = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID, arg0);
		return (bool)ret;
	}
#endif
	return false;
}
