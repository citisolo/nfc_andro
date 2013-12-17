package com.redbandit.ndklibnfc;

import com.redbandit.nfcTypes.*;


public class NfcReader {
	
	public NfcContext m_context = new NfcContext();
	public String log = new String();
	
	static {
		System.loadLibrary("jnfc");
	}
	public  void print_debug(String message ){
		
		log += "\n" + message + "\n";
		
	}
	
	public native long jnfc_init();
	public native void jnfc_exit(long ctx);
    public native String jnfc_version();
    public native int jnfc_list_devices(long ctx, String connstrings[], int connstrings_len);
    //size_t szFound = nfc_list_devices(context, connstrings, MAX_DEVICE_COUNT);
    public native int register();

}
