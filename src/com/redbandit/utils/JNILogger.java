package com.redbandit.utils;

import com.redbandit.utils.StringValStore;
import com.redbandit.utils.StringValStore.StringValStoreListener;


public class JNILogger {
	public String log = new String();
	String tag = "NfcReader:";
    
	public StringValStore mLog = new StringValStore("");
	
	static {
		System.loadLibrary("logger");
	}
    
	public native int register();
	
	
	public JNILogger(StringValStoreListener listener){
		
		mLog.setListener(listener);
		register();
		
	}
	public  void print_debug(String message ){
		
		//log += "\n" + tag + message + "\n";
		mLog.setValue("\n" + tag + message + "\n");
	
	}
	public void clearLog(){
		//log = "";
		mLog.setValue("");
	}
}
