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
The project now has NDK support which just means you no longer have to run ndk-build manually. If any of the NDK classes are modified then javah has to be run manually to re-generate header(warning: there is defined code in the headers so before running javah make sure to copy out the code and re-paste into header file)

Build with eclipse as you would any other application


Installation
=================

Eclipse should take care of this 
