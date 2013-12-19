package com.redbandit.utils;

public class UsbHelper {
	
	public String log = new String();
	String tag = "UsbHelper:";
	
	static {
		System.loadLibrary("usbhelper");
	}
	
	public native int usbtest();
	public native int register();
	
	public UsbHelper(){
		register();
	}
	
	public  void print_debug(String message ){
		
		log += "\n" + tag + message + "\n";
		
	}
	
}
