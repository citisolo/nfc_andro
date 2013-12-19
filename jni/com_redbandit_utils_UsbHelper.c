/*
 * com_redbandit_utils_UsbHelper.c
 *
 *  Created on: 18 Dec 2013
 *      Author: redbandit
 */
#include <usb.h>
#include <stdlib.h>

#include "com_redbandit_utils_UsbHelper.h"
#include "jlog.h"

#define DEBUG_LEVEL 9

// cached refs for later callbacks
JavaVM * g_vm;
jobject g_obj;
jmethodID g_mid;
int calls ;



JNIEXPORT jint JNICALL Java_com_redbandit_utils_UsbHelper_usbtest
  (JNIEnv * pEnv, jobject jclazz)
{
	struct usb_bus *busses;
	struct usb_bus *bus;
	char num_string[100];

	usb_init();
	jprint_debug("initializing usb\n");
	usb_find_busses();
	jprint_debug("finding busses\n");
	usb_find_devices();
	jprint_debug("finding devices\n");
	busses = usb_get_busses();
	jprint_debug("got busses \n");
	if(busses == 0){
		jprint_debug("no busses found\n");
		return -1;
	}
	else
		jprint_debug("busses found\n");

	    sprintf(num_string, "Busses = %d", busses);
	    jprint_debug(num_string);

	for (bus = busses; bus; bus = bus->next) {
	    struct usb_device *dev;
	    jprint_debug("iterating busses\n");

	    for (dev = bus->devices; dev; dev = dev->next) {
            //sprintf(num_string, "DeviceClass:%d\n",dev->descriptor.bDeviceClass );
	    	//jprint_debug(num_string);
	    	jprint_debug("iterating devices\n");
	    }\
	 }
    return 0;
}
JNIEXPORT jint JNICALL Java_com_redbandit_utils_UsbHelper_register
  (JNIEnv * pEnv, jobject jclazz){
	LOGDE(DEBUG_LEVEL, "registering callback" );
	(*pEnv)->GetJavaVM(pEnv, &g_vm);
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


	LOGDE(DEBUG_LEVEL, "jvm pointer -> : %d",(unsigned int)g_vm );
	LOGDE(DEBUG_LEVEL, "g_obj  -> : %d",(unsigned int)g_obj);
	LOGDE(DEBUG_LEVEL, "g_mid -> : %d",(unsigned int)g_mid );
   return 0;
}

void jprint_debug(char * message){
	JNIEnv * g_env;
    //char  tag[1024];
    ++calls;
    LOGDE(DEBUG_LEVEL, "jprint usbhelper" );
    //TO DO: bounds checking on buffer
    //strcat(tag, JLOG_TAG);
    //strcat(tag, message);

	// double check it's all ok
	LOGDE(DEBUG_LEVEL, "calling jprint #%d", calls );
	LOGDE(DEBUG_LEVEL, "jvm pointer -> : %d",(unsigned int)g_vm );
	LOGDE(DEBUG_LEVEL, "g_obj  -> : %d",(unsigned int)g_obj);
	LOGDE(DEBUG_LEVEL, "g_mid -> : %d",(unsigned int)g_mid );


	int getEnvStat = (*g_vm)->GetEnv( g_vm ,(void **) &g_env, JNI_VERSION_1_6);
	LOGDE(DEBUG_LEVEL, "g_env -> : %d",(unsigned int)g_env );

	jstring _message = (*g_env)->NewStringUTF(g_env, message);
	if (getEnvStat == JNI_EDETACHED) {

		LOGDE(DEBUG_LEVEL, "GetEnv: not attached" );
		if ((*g_vm)->AttachCurrentThread(g_vm,(void **) &g_env, 0) != 0) {

			LOGDE(DEBUG_LEVEL, "Failed to attach" );
		}
	} else if (getEnvStat == JNI_OK) {
		//
	} else if (getEnvStat == JNI_EVERSION) {

		LOGDE(DEBUG_LEVEL, "GetEnv: version not supported" );
	}

	(*g_env)->CallVoidMethod(g_env,g_obj, g_mid, _message);

	if ((*g_env)->ExceptionCheck(g_env)) {
		(*g_env)->ExceptionDescribe(g_env);
	}

	LOGDE(DEBUG_LEVEL, "jprint finish" );
	(*g_vm)->DetachCurrentThread(g_env);

}
