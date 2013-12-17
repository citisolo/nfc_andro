/*
 * com_redbandit_utils_JNILogger.c
 *
 *  Created on: 17 Dec 2013
 *      Author: redbandit
 */
#include <jni.h>

#include "com_redbandit_utils_JNILogger.h"
#include "jlog.h"

#define DEBUG_LEVEL 9


// cached refs for later callbacks
JavaVM * g_vm;
jobject g_obj;
jmethodID g_mid;

JNIEXPORT jint JNICALL
Java_com_redbandit_utils_JNILogger_register
  (JNIEnv *pEnv , jobject jclazz)
{

	// convert local to global reference
		// (local will die after this method call)
	g_obj = (*pEnv)->NewGlobalRef(pEnv, jclazz);

	// save refs for callback
	jclass g_clazz = (*pEnv)->GetObjectClass(pEnv, g_obj);

	if (g_clazz == 0) {
	  LOGDE(DEBUG_LEVEL, "Failed to find class" );
	  return -1;

	}

	g_mid = (*pEnv)->GetMethodID(pEnv, g_clazz, "print_debug", "(Ljava/lang/String;)V");
	if (g_mid == 0) {

	 LOGDE(DEBUG_LEVEL, "Unable to get method ref" );
     return -1;
	}

   return 0;
}

 void jprint_debug(char * message)
{
	JNIEnv * g_env;
	// double check it's all ok

	int getEnvStat = (*g_vm)->GetEnv( g_vm ,g_env, JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {

		LOGDE(DEBUG_LEVEL, "GetEnv: not attached" );
		if ((*g_vm)->AttachCurrentThread(g_vm,(void **) &g_env, NULL) != 0) {

			LOGDE(DEBUG_LEVEL, "Failed to attach" );
		}
	} else if (getEnvStat == JNI_OK) {
		//
	} else if (getEnvStat == JNI_EVERSION) {

		LOGDE(DEBUG_LEVEL, "GetEnv: version not supported" );
	}

	(*g_env)->CallVoidMethod(g_env,g_obj, g_mid, message);

	if ((*g_env)->ExceptionCheck(g_env)) {
		(*g_env)->ExceptionDescribe(g_env);
	}

	(*g_vm)->DetachCurrentThread(g_env);

}





