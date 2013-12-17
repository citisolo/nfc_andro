/*
 * com_redbandit_utils_JNIInitializer.c
 *
 *  Created on: 17 Dec 2013
 *      Author: redbandit
 */
#include <jni.h>



#include "com_redbandit_utils_JNIInitializer.h"
#include "object-store.h"

OBJECT_STORE * object_store;

JNIEXPORT void JNICALL
Java_com_redbandit_utils_JNIInitializer_init_1logger
  (JNIEnv * pEnv, jobject jclass, jobject logger)
{
	//save the object reference
	object_store->objectRef = logger;
    object_store->pEnv = pEnv;
}


