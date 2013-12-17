package com.redbandit.utils;

public class JNILogger {
	
	static String log = new String();
    
	
	static {
		System.loadLibrary("jni_initializer");
	}
	
	
	public native int register();

	
	public  void print_debug(String message ){
		
		log += "\n" + message + "\n";
		
	}
	
	public  String getLog(){
		return log;
	}
	
	
}