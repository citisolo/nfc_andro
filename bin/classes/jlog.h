/*
 * jlog.h
 *
 *  Created on: 16 Dec 2013
 *      Author: redbandit
 */

#ifndef JLOG_H_
#define JLOG_H_

#include <android/log.h>
#include "com_redbandit_utils_JNIInitializer.h"
#include "object-store.h"

//OBJECT_STORE * object_store;
//__thread struct jobject_store object_store;
//extern __thread struct  jobject_store object_store;

jobject objectRef ;

#define LOG_LEVEL 9
#define LOG_TAG "JLOGGER"

#define LOGU(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_UNKOWN, LOG_TAG, __VA_ARGS__);}
#define LOGD(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_DEFAULT, LOG_TAG, __VA_ARGS__);}
#define LOGV(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__);}
#define LOGDE(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__);}
#define LOGI(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__);}
#define LOGW(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__);}
#define LOGE(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__);}
#define LOGF(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__);}
#define LOGS(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_SILENT, LOG_TAG, __VA_ARGS__);}

JavaVM *jvm ;

static void jprint_debugV(JavaVM *jvm, jobject logger, ...){

	JNIEnv *pEnv;

	jmethodID mid ;

	jclass dummyCls = (*pEnv)->GetObjectClass(pEnv, logger);

	mid = (*pEnv)->GetStaticMethodID(pEnv, dummyCls, "print_debug", "(Ljava/lang/String;)V");

	va_list arList;
	va_start(arList, mid);
	(*pEnv)->CallStaticVoidMethodV(pEnv, dummyCls, mid, arList);
	va_end(arList);
}

static void jprint_debug(  char * message){

	/*LOGDE(LOG_LEVEL, "jprint_debug: jvm is %d",(long)object_store->jvm );
	LOGDE(LOG_LEVEL, "jprint_debug: jobject is %d",(long)object_store->objectRef);

	JNIEnv *env;
	JavaVM* dvm = object_store->jvm;
	jint rs = (*dvm)->AttachCurrentThread(object_store->jvm, &env, 0);
	//jint rs = object_store->(*jvm)->AttachCurrentThread(object_store.jvm, &env, 0);
    JNIEnv* pEnv = env;
    jobject logger = object_store->objectRef;
	jmethodID mid ;

    //get the class
	jclass dummyCls = (*pEnv)->GetObjectClass(pEnv, logger);

	//get the method id
	mid = (*pEnv)->GetStaticMethodID(pEnv, dummyCls, "print_debug", "(Ljava/lang/String;)V");


	jstring jmessage = (*pEnv)->NewStringUTF(pEnv, message );
	//(*pEnv)->CallStaticVoidMethodV(pEnv, dummyCls, mid, jmessage);
	(*pEnv)->CallStaticVoidMethodA(pEnv, dummyCls, mid, jmessage); */

	LOGDE(LOG_LEVEL, "jprint_debug: objectRef is now %d", (long)objectRef);

}

#endif /* JLOG_H_ */
