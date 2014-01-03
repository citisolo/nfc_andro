package com.redbandit.ndklibnfc;

import com.redbandit.nfcTypes.*;
import android.widget.TextView;



public class NfcReader  {
	
	public NfcContext m_context = new NfcContext();
	
	String tag = "NfcReader:";
	
	static {
		System.loadLibrary("logger");
		System.loadLibrary("usb");
		System.loadLibrary("nfc");
		System.loadLibrary("jnfc");
	}

	public NfcReader(){

		
	}



	
	
	public native long jnfc_init();
	public native void jnfc_exit(long ctx);
    public native String jnfc_version();
    public native int jnfc_list_devices(long ctx, String connstrings[], int connstrings_len);
    //size_t szFound = nfc_list_devices(context, connstrings, MAX_DEVICE_COUNT);

    public native void device_test();
	


}
