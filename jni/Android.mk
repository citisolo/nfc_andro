LOCAL_PATH:= $(call my-dir)
APP_PLATFORM:= android-18
APP_ABI:= armeabi armeabi-v7a x86

#build libusb


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
 libusb-0.1.12/descriptors.c \
 libusb-0.1.12/error.c \
 libusb-0.1.12/linux.c \
 libusb-0.1.12/usb.c \
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
 pn53x-diagnose.c \
 
 #citisolo-libnfc-andro/buses/empty.c \#
 #citisolo-libnfc-andro/buses/i2c.c \#
 

LOCAL_C_INCLUDES += \
$(LOCAL_PATH)/libusb-0.1.12 \
$(LOCAL_PATH)/libnfc-andro \
$(LOCAL_PATH)/libnfc-andro/include \
$(LOCAL_PATH)/libnfc-andro/include/nfc \
$(LOCAL_PATH)/libnfc-andro/libnfc \
$(LOCAL_PATH)/libnfc-andro/libnfc/buses \
$(LOCAL_PATH)/libnfc-andro/libnfc/chips \
$(LOCAL_PATH)/libnfc-andro/libnfc/drivers \
$(LOCAL_PATH)/libnfc-andro/utils




LOCAL_CFLAGS += -DLIBUSB_DESCRIBE=""  -O3 -DHAVE_CONFIG_H -std=c99 -DHAVE_LIBUSB -DDRIVER_ACR122_USB_ENABLED
LOCAL_MODULE:= libnfc
LOCAL_PRELINK_MODULE:= true
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE := UsbPermissionHelper
LOCAL_LDLIBS := -llog
LOCAL_SRC_FILES := \
marto_rtl_tcp_andro_tools_UsbPermissionHelper.c
include $(BUILD_SHARED_LIBRARY)

