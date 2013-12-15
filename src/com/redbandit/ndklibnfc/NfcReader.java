package com.redbandit.ndklibnfc;

import com.redbandit.nfcTypes.*;


public class NfcReader {
	
	public NfcContext m_context = new NfcContext();
	
	
	static {
		System.loadLibrary("jnfc");
	}
	
	public native long jnfc_init();
	public native void jnfc_exit(long ctx);
    

}
