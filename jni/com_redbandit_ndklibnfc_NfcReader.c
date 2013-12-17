
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
