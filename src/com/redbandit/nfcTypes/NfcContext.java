package com.redbandit.nfcTypes;

public class NfcContext {
	
	public NfcContext(){
		
		
	}
	public final int MAX_USER_DEFINED_DEVICES = 4;
	
	public boolean allow_autoscan;
	public boolean allow_intrusive_scan;
	public int log_level;
	public Object userDefinedDevices = new NfcUserDefinedDevice[MAX_USER_DEFINED_DEVICES];
	public int user_defined_device_count;

}
