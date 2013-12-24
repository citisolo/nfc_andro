LOCAL_PATH:= $(call my-dir)
APP_PLATFORM:= android-18
APP_ABI:= armeabi armeabi-v7a x86



subdirs := $(addprefix $(LOCAL_PATH)/,$(addsuffix /Android.mk, jni_jlog\ jni_libusb \jni_nfc_reader \jni_usb_helper \jni_usb_permission_helper))
        

	

include $(subdirs)


#build executable file 
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
 pn53x-diagnose.c \
 
LOCAL_C_INCLUDES += \
$(LOCAL_PATH)/libnfc-andro \
$(LOCAL_PATH)/libnfc-andro/include \
$(LOCAL_PATH)/libnfc-andro/include/nfc \
$(LOCAL_PATH)/libnfc-andro/libnfc \
$(LOCAL_PATH)/libnfc-andro/libnfc/buses \
$(LOCAL_PATH)/libnfc-andro/libnfc/chips \
$(LOCAL_PATH)/libnfc-andro/libnfc/drivers \
$(LOCAL_PATH)/libnfc-andro/utils


LOCAL_CFLAGS += -std=c99 
LOCAL_MODULE:= nfctest
LOCAL_LDLIBS := -llog
LOCAL_PRELINK_MODULE:= true
LOCAL_STATIC_LIBRARIES:= libnfc \
libusb \

#include $(BUILD_EXECUTABLE)







