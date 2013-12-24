package com.redbandit.utils;

public class UsbHelper {
	
	public String log = new String();
	String tag = "UsbHelper:";
	
	static {
		System.loadLibrary("logger");
		System.loadLibrary("usb");
		System.loadLibrary("usbhelper");
	}
	
	public native int usbtest();

	public UsbHelper(){
		
	}
	public void clearLog(){
		log = "";
	}

	
}
