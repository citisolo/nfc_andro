LOCAL_PATH:= $(call my-dir)
APP_PLATFORM:= android-18
APP_ABI:= armeabi armeabi-v7a x86



subdirs := $(addprefix $(LOCAL_PATH)/,$(addsuffix /Android.mk, jni_jlog\ jni_libusb \jni_nfc_reader \jni_usb_helper \jni_usb_permission_helper))
        

	

include $(subdirs)









