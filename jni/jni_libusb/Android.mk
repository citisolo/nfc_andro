#Android.mk

# Created on: 24 Dec 2013
# Author: redbandit

#build libusb
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
 libusb-0.1.12/descriptors.c \
 libusb-0.1.12/error.c \
 libusb-0.1.12/linux.c \
 libusb-0.1.12/usb.c \
 
LOCAL_C_INCLUDES += \
 $(LOCAL_PATH)/libusb-0.1.12 \
 $(LOCAL_PATH)/jni_jlog
 
 LOCAL_CFLAGS += -DLIBUSB_DESCRIBE=""  -O3 -DHAVE_CONFIG_H -std=c99 
 LOCAL_MODULE:= libusb
 LOCAL_SHARED_LIBRARIES:= logger
include $(BUILD_SHARED_LIBRARY)