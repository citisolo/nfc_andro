package com.redbandit.utils;

public class UsbHelper {
	
	static {
		System.loadLibrary("usbhelper");
	}
	
	public native int usbtest();
}
