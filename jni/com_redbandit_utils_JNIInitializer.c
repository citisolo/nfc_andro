/*
 * com_redbandit_utils_JNIInitializer.c
 *
 *  Created on: 17 Dec 2013
 *      Author: redbandit
 */
#include <jni.h>



#include "com_redbandit_utils_JNIInitializer.h"
#include "object-store.h"
#include "jlog.h"

struct jobject_store *object_store;
// cached refs for later callbacks
JavaVM * g_vm;
jobject g_obj;
jmethodID g_mid;


JNIEXPORT void JNICALL
Java_com_redbandit_utils_JNIInitializer_init_1logger
  (JNIEnv * pEnv, jobject jclass, jobject logger)
{
	//get the jvm
	jint rs = (*pEnv)->GetJavaVM(pEnv, &jvm);
	LOGDE(9, "rs is %d", rs );
	LOGDE(9, "starting ... pEnv is %d", (long)pEnv );
	//save the object reference
	//object_store.objectRef = logger;
    //object_store.pEnv = pEnv;
    //object_store->jvm = jvm;
    //jclass localClass = (*pEnv)->FindClass
    LOGDE(9, " jvm  %d", (long)jvm);
    //object_store->objectRef = (jobject)(*pEnv)->NewGlobalRef(pEnv, logger);
    //CLASSPATH +=
    /*const char * classpath = getenv("CLASSPATH");
    if (classpath == NULL){
    	setenv("CLASSPATH", "~/workspace/ndkLibNFC/bin/classes/" , 1);
    }else{
    	strcat(classpath, "~/workspace/ndkLibNFC/bin/classes/");
    	int envOK = setenv("CLASSPATH", classpath , 1);
    }*/

    setenv("CLASSPATH", "~/workspace/ndkLibNFC/bin/classes/com/redbandit/utils/" , 1);


    objectRef = (*pEnv)->FindClass (pEnv, "JNILogger");
    if (objectRef == 0){
    	LOGDE(9, "Java class not found");
    	return;
    }
    //objectRef = (jobject)(*pEnv)->NewGlobalRef(pEnv, logger);
    LOGDE(9, "objectRef is %d", (long)objectRef );
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

	//LOGDE(LOG_LEVEL, "jprint_debug: objectRef is now %d", (long)objectRef);

}

