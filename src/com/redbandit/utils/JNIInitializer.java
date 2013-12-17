package com.redbandit.utils;

public class JNIInitializer {
	
	static {
		System.loadLibrary("jlog");
	}
	//public JNILogger logger = new JNILogger();
	
	public JNIInitializer(JNILogger logger){
		 logger = new JNILogger();
		init_logger(logger);
		
	}
	
	public native void init_logger(JNILogger logger);


}
