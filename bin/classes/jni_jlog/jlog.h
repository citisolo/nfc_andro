/*
 * jlog.h
 *
 *  Created on: 16 Dec 2013
 *      Author: redbandit
 */

#ifndef JLOG_H_
#define JLOG_H_

#include <android/log.h>
#include <jni.h>



#include "com_redbandit_utils_JNILogger.h"

#ifdef JDEBUG
   #define JPRINT(message)  jprint_debug(message) ;
#else
   #define JPRINT(message)
#endif


#define DEBUG_LEVEL 9
#define LOG_TAG "JLOGGER"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif


#define LOGU(level, ...) if (level <= DEBUG_LEVEL){__android_log_print(ANDROID_LOG_UNKOWN, LOG_TAG, __VA_ARGS__);}
#define LOGD(level, ...) if (level <= DEBUG_LEVEL){__android_log_print(ANDROID_LOG_DEFAULT, LOG_TAG, __VA_ARGS__);}
#define LOGV(level, ...) if (level <= DEBUG_LEVEL){__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__);}
#define LOGDE(level, ...) if (level <= DEBUG_LEVEL){__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__);}
#define LOGI(level, ...) if (level <= DEBUG_LEVEL){__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__);}
#define LOGW(level, ...) if (level <= DEBUG_LEVEL){__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__);}
#define LOGE(level, ...) if (level <= DEBUG_LEVEL){__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__);}
#define LOGF(level, ...) if (level <= DEBUG_LEVEL){__android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__);}
#define LOGS(level, ...) if (level <= DEBUG_LEVEL){__android_log_print(ANDROID_LOG_SILENT, LOG_TAG, __VA_ARGS__);}

/*static void jprint_debug(JNIEnv *pEnv, jclass dummyCls, jmethodID mid, ...){
	va_list arList;
	va_start(arList, mid);
	(*pEnv)->CallStaticVoidMethodV(pEnv, dummyCls, mid, arList);
	va_end(arList);
}*/

typedef struct  {

	JavaVM * g_vm;
	jobject g_obj;
	jmethodID g_mid;

}  shmseg;

shmseg vm_data ;




JNIEXPORT jint JNICALL
Java_com_redbandit_utils_JNILogger_register(JNIEnv* pEnv, jobject jclazz);

/* Name: Jprint_debug
 * Desc: Callback used to log messages native to javaland
 *
 */
void jprint_debug(char * message);

#endif /* JLOG_H_ */
