#Android.mk

# Created on: 24 Dec 2013
# Author: redbandit

#Build logger lib

include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
jni_jlog/jlog.c \

LOCAL_C_INCLUDES += \
$(LOCAL_PATH) \
$(LOCAL_PATH)/jni_log 

LOCAL_MODULE := logger
LOCAL_LDLIBS := -llog 

include $(BUILD_SHARED_LIBRARY)