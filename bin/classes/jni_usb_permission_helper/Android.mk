#Android.mk

# Created on: 24 Dec 2013
# Author: redbandit

#Build Usb permission helper
include $(CLEAR_VARS)
LOCAL_MODULE := UsbPermissionHelper
LOCAL_LDLIBS := -llog
LOCAL_SRC_FILES := \
jni_usb_permission_helper/marto_rtl_tcp_andro_tools_UsbPermissionHelper.c


include $(BUILD_SHARED_LIBRARY)
