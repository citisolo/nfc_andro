
#include <stdint.h>
#include <string.h>
#include <nfc/nfc.h>
#include <jni.h>

#include "utils/nfc-utils.h"
#include "libnfc/chips/pn53x.h"
#include "utils/debug_trace.h"
#include "com_redbandit_ndklibnfc_NfcReader.h"

# define JSUCCESS 1
# define JFAILURE 0

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



JNIEXPORT jcharArray JNICALL
Java_com_redbandit_ndklibnfc_NfcReader_jnfc_1version
  (JNIEnv * pEnv, jobject jclazz)
{
	const char *acLibnfcVersion;
    acLibnfcVersion = nfc_version();

    int jsize = sizeof(acLibnfcVersion);
    jstring message;

    /*for (int i=0; i< jsize; j++) {


    }*/


    //char ver[jsize] ;
    //strcpy()
    return (*pEnv)->NewStringUTF(pEnv, acLibnfcVersion);
    //return (jcharArray)acLibnfcVersion;


}
