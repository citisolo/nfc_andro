LOCAL_PATH:= $(call my-dir)
APP_PLATFORM:= android-18
APP_ABI:= armeabi armeabi-v7a x86


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
 libusb-0.1.12/descriptors.c \
 libusb-0.1.12/error.c \
 libusb-0.1.12/linux.c \
 libusb-0.1.12/usb.c \
 citisolo-libnfc-andro/libnfc/conf.c \
 citisolo-libnfc-andro/libnfc/iso14443-subr.c \
 citisolo-libnfc-andro/libnfc/log-internal.c \
 citisolo-libnfc-andro/libnfc/log.c \
 citisolo-libnfc-andro/libnfc/mirror-subr.c \
 citisolo-libnfc-andro/libnfc/nfc-device.c \
 citisolo-libnfc-andro/libnfc/nfc-emulation.c \
 citisolo-libnfc-andro/libnfc/nfc-internal.c \
 citisolo-libnfc-andro/libnfc/nfc.c \
 citisolo-libnfc-andro/libnfc/target-subr.c \
 citisolo-libnfc-andro/utils/nfc-utils.c \
 citisolo-libnfc-andro/libnfc/buses/usbbus.c \
 citisolo-libnfc-andro/libnfc/chips/pn53x.c\
 citisolo-libnfc-andro/libnfc/drivers/acr122_usb.c \
 pn53x-diagnose.c \
 
 #citisolo-libnfc-andro/buses/empty.c \#
 #citisolo-libnfc-andro/buses/i2c.c \#
 

LOCAL_C_INCLUDES += \
$(LOCAL_PATH)/libusb-0.1.12 \
$(LOCAL_PATH)/citisolo-libnfc-andro \
$(LOCAL_PATH)/citisolo-libnfc-andro/include \
$(LOCAL_PATH)/citisolo-libnfc-andro/include/nfc \
$(LOCAL_PATH)/citisolo-libnfc-andro/libnfc \
$(LOCAL_PATH)/citisolo-libnfc-andro/libnfc/buses \
$(LOCAL_PATH)/citisolo-libnfc-andro/libnfc/chips \
$(LOCAL_PATH)/citisolo-libnfc-andro/libnfc/drivers \
$(LOCAL_PATH)/citisolo-libnfc-andro/utils




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

