
#include <stdint.h>
#include <string.h>
#include <nfc/nfc.h>
#include <jni.h>
#include <nfc/nfc.h>

#include "utils/nfc-utils.h"
#include "libnfc/chips/pn53x.h"
#include "utils/debug_trace.h"
#include "com_redbandit_ndklibnfc_NfcReader.h"
#include "jlog.h"
#include "jconfig.h"

//#define JDEBUG
# define JSUCCESS 1
# define JFAILURE 0
#define  MAX_DEVICE_COUNT 16

#define DEBUG_LEVEL 9
#define JLOG_TAG "\nJLogger: "

#ifdef JDEBUG || UDEBUG
   #define JPRINT(message)  jprint_debug(message) ;
#else
   #define JPRINT(message)
#endif

// cached refs for later callbacks
JavaVM * g_vm;
jobject g_obj;
jmethodID g_mid;
int calls ;


JNIEXPORT jlong JNICALL
Java_com_redbandit_ndklibnfc_NfcReader_jnfc_1init
  (JNIEnv * pEnv, jobject jclazz)
{
	if (set_perm() != 0){
		exit(EXIT_FAILURE);
	}
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

	if (set_perm() != 0){
		exit(EXIT_FAILURE);
	}
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
    //char  tag[1024];
    ++calls;
    //LOGDE(DEBUG_LEVEL, "jprint nfcreader" );
    //TO DO: bounds checking on buffer
    //strcat(tag, JLOG_TAG);
    //strcat(tag, message);

	// double check it's all ok
	/*LOGDE(DEBUG_LEVEL, "calling jprint #%d", calls );
	LOGDE(DEBUG_LEVEL, "jvm pointer -> : %d",(unsigned int)g_vm );
	LOGDE(DEBUG_LEVEL, "g_obj  -> : %d",(unsigned int)g_obj);
	LOGDE(DEBUG_LEVEL, "g_mid -> : %d",(unsigned int)g_mid );
     */
	int getEnvStat = (*g_vm)->GetEnv( g_vm ,(void **) &g_env, JNI_VERSION_1_6);
	//LOGDE(DEBUG_LEVEL, "g_env -> : %d",(unsigned int)g_env );

	jstring _message = (*g_env)->NewStringUTF(g_env, message);
	if (getEnvStat == JNI_EDETACHED) {

		//LOGDE(DEBUG_LEVEL, "GetEnv: not attached" );
		if ((*g_vm)->AttachCurrentThread(g_vm,(void **) &g_env, NULL) != 0) {

			//LOGDE(DEBUG_LEVEL, "Failed to attach" );
		}
	} else if (getEnvStat == JNI_OK) {
		//
	} else if (getEnvStat == JNI_EVERSION) {

		//LOGDE(DEBUG_LEVEL, "GetEnv: version not supported" );
	}

	(*g_env)->CallVoidMethod(g_env,g_obj, g_mid, _message);

	if ((*g_env)->ExceptionCheck(g_env)) {
		(*g_env)->ExceptionDescribe(g_env);
	}

	//LOGDE(DEBUG_LEVEL, "jprint finish" );
	(*g_vm)->DetachCurrentThread(g_env);

}

JNIEXPORT void JNICALL Java_com_redbandit_ndklibnfc_NfcReader_device_1test
  (JNIEnv * pEnv, jobject jclazz){

	JPRINT("Set permissions");

	if (set_perm() != 0){
		LOGDE(DEBUG_LEVEL, "devicetest:cant get permissions" );
		exit(EXIT_FAILURE);
	}

	JPRINT("Diagnosing...");
	size_t  i;
	nfc_device *pnd = NULL;
	const char *acLibnfcVersion;
	bool    result;

	uint8_t  abtRx[PN53x_EXTENDED_FRAME__DATA_MAX_LEN];
	size_t  szRx = sizeof(abtRx);
	const uint8_t pncmd_diagnose_communication_line_test[] = { Diagnose, 0x00, 0x06, 'l', 'i', 'b', 'n', 'f', 'c' };
	const uint8_t pncmd_diagnose_rom_test[] = { Diagnose, 0x01 };
	const uint8_t pncmd_diagnose_ram_test[] = { Diagnose, 0x02 };



	LOGDE(DEBUG_LEVEL, "devicetest:getting context" );
	nfc_context *context;
	nfc_init(&context);
	if (context == NULL) {
	  ERR("Unable to init libnfc (malloc)");
	  JPRINT("Unable to init libnfc (malloc)");
	  exit(EXIT_FAILURE);
	}


	LOGDE(DEBUG_LEVEL, "devicetest:finding devices" );
	nfc_connstring connstrings[MAX_DEVICE_COUNT];
	size_t szFound = nfc_list_devices(context, connstrings, MAX_DEVICE_COUNT);

	if (szFound == 0) {
	  printf("No NFC device found.\n");
	  JPRINT("No NFC device found.\n");
	  LOGDE(DEBUG_LEVEL, "No NFC device found.\n" );
	}



	for (i = 0; i < szFound; i++) {
	  LOGDE(DEBUG_LEVEL, "Opening device" );
	  int res = 0;
	  pnd = nfc_open(context, connstrings[i]);

	  if (pnd == NULL) {
		ERR("%s", "Unable to open NFC device.");
		JPRINT("No NFC device found.\n");
		LOGDE(DEBUG_LEVEL, "No device found" );
		nfc_exit(context);
		exit(EXIT_FAILURE);
	  }

	  printf("NFC device [%s] opened.\n", nfc_device_get_name(pnd));
	  JPRINT("NFC device opened");
	  LOGDE(DEBUG_LEVEL, "NFC device opened" );

	  res = pn53x_transceive(pnd, pncmd_diagnose_communication_line_test, sizeof(pncmd_diagnose_communication_line_test), abtRx, szRx, 0);
	  if (res > 0) {
		szRx = (size_t) res;
		// Result of Diagnose ping for RC-S360 doesn't contain status byte so we've to handle both cases
		result = (memcmp(pncmd_diagnose_communication_line_test + 1, abtRx, sizeof(pncmd_diagnose_communication_line_test) - 1) == 0) ||
				 (memcmp(pncmd_diagnose_communication_line_test + 2, abtRx, sizeof(pncmd_diagnose_communication_line_test) - 2) == 0);
		printf(" Communication line test: %s\n", result ? "OK" : "Failed");
		char str[64];
		sprintf(str," Communication line test: %s\n",result ? "OK" : "Failed" );
		JPRINT(str);

	  } else {
		nfc_perror(pnd, "pn53x_transceive: cannot diagnose communication line");
	  }

	  res = pn53x_transceive(pnd, pncmd_diagnose_rom_test, sizeof(pncmd_diagnose_rom_test), abtRx, szRx, 0);
	  if (res > 0) {
		szRx = (size_t) res;
		result = ((szRx == 1) && (abtRx[0] == 0x00));
		printf(" ROM test: %s\n", result ? "OK" : "Failed");
		char str[64];
		sprintf(str,"ROM test: %s\n",result ? "OK" : "Failed" );
		JPRINT(str);
	  } else {
		nfc_perror(pnd, "pn53x_transceive: cannot diagnose ROM");
	  }

	  res = pn53x_transceive(pnd, pncmd_diagnose_ram_test, sizeof(pncmd_diagnose_ram_test), abtRx, szRx, 0);
	  if (res > 0) {
		szRx = (size_t) res;
		result = ((szRx == 1) && (abtRx[0] == 0x00));
		printf(" RAM test: %s\n", result ? "OK" : "Failed");
		char str[64];
		sprintf(str,"RAM test: %s\n",result ? "OK" : "Failed" );
		JPRINT(str);
	  } else {
		nfc_perror(pnd, "pn53x_transceive: cannot diagnose RAM");
	  }
	}
	nfc_close(pnd);
	nfc_exit(context);

}



int set_perm(){
	int r = system("su -c \"chmod -R 777 /proc/bus/usb/\"");
	if(r!=0) {
	    LOGDE(DEBUG_LEVEL,"Could not grant permissions to USB\n");
	    return -1;
	}
	return 0;
}


