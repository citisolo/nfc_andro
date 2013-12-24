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
	if (set_perm() != 0){
		exit(EXIT_FAILURE);
	}

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
            sprintf(num_string, "DeviceClass:%d\n",dev->descriptor.bDeviceClass );
	    	jprint_debug(num_string);
	    	jprint_debug("iterating devices\n");
	    }
	 }
    return 0;
}

int set_perm(){
	int r = system("su -c \"chmod -R 777 /dev/bus/usb/\"");
	if(r!=0) {
	    LOGDE(DEBUG_LEVEL,"Could not grant permissions to USB\n");
	    return -1;
	}
	return 0;
}
