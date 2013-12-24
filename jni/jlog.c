/*
 * jlog.c
 *
 *  Created on: 24 Dec 2013
 *      Author: redbandit
 */

#include <stddef.h>
#include "jlog.h"


JNIEXPORT jint JNICALL
Java_com_redbandit_utils_JNILogger_register(JNIEnv* pEnv, jobject jclazz){

	LOGDE(DEBUG_LEVEL, "Register is called" );
	(*pEnv)->GetJavaVM(pEnv, &vm_data.g_vm);
	LOGDE(DEBUG_LEVEL, "We got the pointer" );
	// convert local to global reference
		// (local will die after this method call)
	vm_data.g_obj = (*pEnv)->NewGlobalRef(pEnv, jclazz);

	// save refs for callback
	jclass g_clazz = (*pEnv)->GetObjectClass(pEnv, vm_data.g_obj);

	if (g_clazz == 0) {
	  LOGDE(DEBUG_LEVEL, "Failed to find class" );
	  return -1;

	}

	vm_data.g_mid = (*pEnv)->GetMethodID(pEnv, g_clazz, "print_debug", "(Ljava/lang/String;)V");
	if (vm_data.g_mid == 0) {

	 LOGDE(DEBUG_LEVEL, "Unable to get method ref" );
     return -1;
	}


	LOGDE(DEBUG_LEVEL, "jvm pointer -> : %d",(unsigned int)vm_data.g_vm );
	LOGDE(DEBUG_LEVEL, "g_obj  -> : %d",(unsigned int)vm_data.g_obj);
	LOGDE(DEBUG_LEVEL, "g_mid -> : %d",(unsigned int)vm_data.g_mid );
   return 0;
}


void jprint_debug(char * message){
	JNIEnv * g_env;
    //char  tag[1024];
    //++calls;
    LOGDE(DEBUG_LEVEL, "jprint executed" );
    //TO DO: bounds checking on buffer
    //strcat(tag, JLOG_TAG);
    //strcat(tag, message);

	// double check it's all ok
	/*LOGDE(DEBUG_LEVEL, "calling jprint #%d", calls );
	LOGDE(DEBUG_LEVEL, "jvm pointer -> : %d",(unsigned int)g_vm );
	LOGDE(DEBUG_LEVEL, "g_obj  -> : %d",(unsigned int)g_obj);
	LOGDE(DEBUG_LEVEL, "g_mid -> : %d",(unsigned int)g_mid );
     */
	int getEnvStat = (*vm_data.g_vm)->GetEnv( vm_data.g_vm ,(void **) &g_env, JNI_VERSION_1_6);
	//LOGDE(DEBUG_LEVEL, "g_env -> : %d",(unsigned int)g_env );

	jstring _message = (*g_env)->NewStringUTF(g_env, message);
	if (getEnvStat == JNI_EDETACHED) {

		//LOGDE(DEBUG_LEVEL, "GetEnv: not attached" );
		if ((*vm_data.g_vm)->AttachCurrentThread(vm_data.g_vm,(void **) &g_env, NULL) != 0) {

			//LOGDE(DEBUG_LEVEL, "Failed to attach" );
		}
	} else if (getEnvStat == JNI_OK) {
		//
	} else if (getEnvStat == JNI_EVERSION) {

		//LOGDE(DEBUG_LEVEL, "GetEnv: version not supported" );
	}

	(*g_env)->CallVoidMethod(g_env,vm_data.g_obj, vm_data.g_mid, _message);

	if ((*g_env)->ExceptionCheck(g_env)) {
		(*g_env)->ExceptionDescribe(g_env);
	}

	LOGDE(DEBUG_LEVEL, "jprint finish" );
	(*vm_data.g_vm)->DetachCurrentThread(g_env);

}

