package com.redbandit.utils;

public class JNIInitializer {
	
	static {
		System.loadLibrary("jni_initializer");
	}
	
	public JNIInitializer(){
		JNILogger logger = new JNILogger();
		init_logger(logger);
		
	}
	
	public native void init_logger(JNILogger logger);
	

}
