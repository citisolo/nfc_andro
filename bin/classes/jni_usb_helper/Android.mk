#Android.mk

# Created on: 24 Dec 2013
# Author: redbandit

#Build UsbHelper Library
include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
jni_usb_helper/com_redbandit_utils_UsbHelper.c \


LOCAL_C_INCLUDES += \
$(LOCAL_PATH)/libusb-0.1.12 \
$(LOCAL_PATH)/jni_usb_helper\
$(LOCAL_PATH)/jni_jlog \


LOCAL_MODULE := usbhelper
LOCAL_SHARED_LIBRARIES:= libusb \
logger

LOCAL_LDLIBS := -llog 

include $(BUILD_SHARED_LIBRARY)