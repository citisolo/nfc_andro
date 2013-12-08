nfc_andro
=========

nfc lib and tools port to android Nfc Andro is a is a port of the libnfc library to the android platform(CyanogenMod). 
Nfc_andro is essentially a driver that runs on the Android platform that allows communication with an ACR122 nfc device 
via usb otg. The model of phone Nfc Andro  using is the samsung n7000 

General information 
=================
nfc andro is a hack which is stil in its early days but the aim is to build a fully fledged library of nfc applications 
built on the back of this library. 

Hardware Setup
=================
Phone: Samsung Galaxy n7000 (running cyanogenmod)
Platform: armeabi android platform 18
hardware:ACR122 nfc smart card reader

Requirements
=================
This library depends on 
*Root access to phone to run app from command line
*Android NDK
*acr122_usb 
*libusb-0.1(which is compiled into executable)

Building 
=================
Use the ndk in the following way;
cd /path/to/jni folder/
ndk-build 


Installation
=================
*note: only the backend has been built so compiling it into an apk will achieve nothing . 
currently i copy the binary file which is stored in the libs/armeabi  to the /data/local/tmp 
(android won't allow you to run executable on sdcard) connect the device and then execute the program on the command line.
