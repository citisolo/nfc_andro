#Android.mk

# Created on: 24 Dec 2013
# Author: redbandit

#build libnfc
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
 libnfc-andro/libnfc/conf.c \
 libnfc-andro/libnfc/iso14443-subr.c \
 libnfc-andro/libnfc/log-internal.c \
 libnfc-andro/libnfc/log.c \
 libnfc-andro/libnfc/mirror-subr.c \
 libnfc-andro/libnfc/nfc-device.c \
 libnfc-andro/libnfc/nfc-emulation.c \
 libnfc-andro/libnfc/nfc-internal.c \
 libnfc-andro/libnfc/nfc.c \
 libnfc-andro/libnfc/target-subr.c \
 libnfc-andro/utils/nfc-utils.c \
 libnfc-andro/libnfc/buses/usbbus.c \
 libnfc-andro/libnfc/chips/pn53x.c\
 libnfc-andro/libnfc/drivers/acr122_usb.c \


LOCAL_C_INCLUDES += \
$(LOCAL_PATH)/libnfc-andro \
$(LOCAL_PATH)/libnfc-andro/include \
$(LOCAL_PATH)/libnfc-andro/include/nfc \
$(LOCAL_PATH)/libnfc-andro/libnfc \
$(LOCAL_PATH)/libnfc-andro/libnfc/buses \
$(LOCAL_PATH)/libnfc-andro/libnfc/chips \
$(LOCAL_PATH)/libnfc-andro/libnfc/drivers \
$(LOCAL_PATH)/jni_jlog \
$(LOCAL_PATH)/libnfc-andro/utils \
$(LOCAL_PATH)

LOCAL_EXPORT_C_INCLUDES += \
$(LOCAL_PATH)/libusb-0.1.12 \

LOCAL_CFLAGS += -DHAVE_CONFIG_H -std=c99 -DHAVE_LIBUSB -DDRIVER_ACR122_USB_ENABLED 
LOCAL_MODULE:= libnfc
LOCAL_PRELINK_MODULE:= true
LOCAL_SHARED_LIBRARIES:= libusb \
logger

LOCAL_LDLIBS := -llog 

include $(BUILD_SHARED_LIBRARY)

#Build Nfc Reader Library
include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
jni_nfc_reader/com_redbandit_ndklibnfc_NfcReader.c \


LOCAL_C_INCLUDES += \
$(LOCAL_PATH)/libnfc-andro \
$(LOCAL_PATH)/libnfc-andro/include \
$(LOCAL_PATH)/libnfc-andro/include/nfc \
$(LOCAL_PATH)/libnfc-andro/libnfc \
$(LOCAL_PATH)/libnfc-andro/libnfc/buses \
$(LOCAL_PATH)/libnfc-andro/libnfc/chips \
$(LOCAL_PATH)/libnfc-andro/libnfc/drivers \
$(LOCAL_PATH)/libnfc-andro/utils \
$(LOCAL_PATH)/jni_nfc_reader \
$(LOCAL_PATH)/jni_jlog \
$(LOCAL_PATH) 



LOCAL_MODULE := jnfc
LOCAL_SHARED_LIBRARIES:= libnfc \
logger
 

LOCAL_LDLIBS := -llog 

include $(BUILD_SHARED_LIBRARY)

