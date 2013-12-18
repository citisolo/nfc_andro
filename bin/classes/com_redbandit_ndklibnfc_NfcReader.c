
#include <stdint.h>
#include <string.h>
#include <nfc/nfc.h>
#include <jni.h>

#include "utils/nfc-utils.h"
#include "libnfc/chips/pn53x.h"
#include "utils/debug_trace.h"
#include "com_redbandit_ndklibnfc_NfcReader.h"
#include "jlog.h"

#define  DEBUG_LEVEL 9

# define JSUCCESS 1
# define JFAILURE 0
#define  MAX_DEVICE_COUNT 16

#define DEBUG_LEVEL 9
#define JLOG_TAG "\nJLogger: "


// cached refs for later callbacks
JavaVM * g_vm;
jobject g_obj;
jmethodID g_mid;
int calls ;


JNIEXPORT jlong JNICALL
Java_com_redbandit_ndklibnfc_NfcReader_jnfc_1init
  (JNIEnv * pEnv, jobject jclazz)
{
  nfc_context *context;

  nfc_init(&context);
  if (context == NULL) {
	//ERR("Unable to init libnfc (malloc)");
	//exit(EXIT_FAILURE);
	return JFAILURE ;
  }


  return (long)context ;

}

JNIEXPORT void JNICALL
Java_com_redbandit_ndklibnfc_NfcReader_jnfc_1exit
 (JNIEnv * pEnv, jobject jclazz, jlong ctx)
{
	nfc_context* context = (unsigned long)ctx;
	nfc_exit(context);


}



JNIEXPORT jstring JNICALL
Java_com_redbandit_ndklibnfc_NfcReader_jnfc_1version
  (JNIEnv * pEnv, jobject jclazz)
{
	const char *acLibnfcVersion;
    acLibnfcVersion = nfc_version();

    return (*pEnv)->NewStringUTF(pEnv, acLibnfcVersion);
    //return (jcharArray)acLibnfcVersion;


}

JNIEXPORT jint JNICALL
Java_com_redbandit_ndklibnfc_NfcReader_jnfc_1list_1devices
  (JNIEnv * pEnv, jobject jclazz, jlong ctx, jobjectArray jconnstrings, jint len)
{

	 nfc_context* context = (unsigned long)ctx;
	 nfc_connstring connstrings[MAX_DEVICE_COUNT];

     jint szFound = (jint)nfc_list_devices(context, connstrings, MAX_DEVICE_COUNT);
     LOGDE(DEBUG_LEVEL, "returning szFound" );

     //convert the constrings to virtual


     return szFound;

}

JNIEXPORT jint
JNICALL Java_com_redbandit_ndklibnfc_NfcReader_register
  (JNIEnv * pEnv, jobject jclazz)
{
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
    char  tag[1024];
    ++calls;

    //TO DO: bounds checking on buffer
    strcat(tag, JLOG_TAG);
    strcat(tag, message);

	// double check it's all ok
	LOGDE(DEBUG_LEVEL, "calling jprint #%d", calls );
	LOGDE(DEBUG_LEVEL, "jvm pointer -> : %d",(unsigned int)g_vm );
	LOGDE(DEBUG_LEVEL, "g_obj  -> : %d",(unsigned int)g_obj);
	LOGDE(DEBUG_LEVEL, "g_mid -> : %d",(unsigned int)g_mid );

	int getEnvStat = (*g_vm)->GetEnv( g_vm ,(void **) &g_env, JNI_VERSION_1_6);
	LOGDE(DEBUG_LEVEL, "g_env -> : %d",(unsigned int)g_env );

	jstring _message = (*g_env)->NewStringUTF(g_env, tag);
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

	(*g_env)->CallVoidMethod(g_env,g_obj, g_mid, _message);

	if ((*g_env)->ExceptionCheck(g_env)) {
		(*g_env)->ExceptionDescribe(g_env);
	}

	LOGDE(DEBUG_LEVEL, "jprint finish" );
	(*g_vm)->DetachCurrentThread(g_env);

}




