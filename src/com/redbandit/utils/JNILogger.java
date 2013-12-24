package com.redbandit.utils;

public class JNILogger {
	public String log = new String();
	String tag = "NfcReader:";

	static {
		System.loadLibrary("logger");
	}
    
	public native int register();
	
	
	public JNILogger(){
		register();
	}
	public  void print_debug(String message ){
		
		log += "\n" + tag + message + "\n";
		
	
	}
	public void clearLog(){
		log = "";
	}
}
