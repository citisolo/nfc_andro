package com.redbandit.ndklibnfc;

import com.redbandit.nfcTypes.*;


public class NfcReader {
	
	public NfcContext m_context = new NfcContext();
	
	
	static {
		System.loadLibrary("jnfc");
	}
	
	public native long jnfc_init();
	public native void jnfc_exit(long ctx);
    public native String jnfc_version();
    public native int jnfc_list_devices(long ctx, String connstrings[], int connstrings_len);
    //size_t szFound = nfc_list_devices(context, connstrings, MAX_DEVICE_COUNT);

}
