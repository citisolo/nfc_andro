package com.redbandit.utils;

public class JNILogger {
	
	static String log = new String();

	public static void print_debug(String message ){
		
		log += message;
		
	}
	
	public static String getLog(){
		return log;
	}
}
