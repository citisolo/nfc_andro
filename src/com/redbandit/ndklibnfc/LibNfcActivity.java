package com.redbandit.ndklibnfc;

import android.os.Bundle;

import android.app.Activity;
import android.view.Menu;
import android.widget.TextView;
//import com.android.internal.util.*;
import com.redbandit.utils.*;


public class LibNfcActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//setContentView(R.layout.activity_lib_nfc);
		TextView tv = new TextView(this);
		String out = new String() ;
		tv.setTextSize(30);
		
		JNILogger jLogger;
		JNIInitializer logInitializer = new JNIInitializer(jLogger = new JNILogger());
		
		
		NfcReader nfc_reader = new NfcReader();
		long ctx = nfc_reader.jnfc_init(); // initialize context
		if (ctx == 0){
			//print failure message 
			out += "LibNfcActivity: context is null\n";
			
			
		}
		else
		{
			//Print success message
			out += "\nLibNfcActivity: context = 0x" + ctx  ;
		    
			String version = nfc_reader.jnfc_version();
		    out += "\nLibNfcActivity: Version is: " + version;    
			
		    String connstrings[] = new String[100];
		    int connstrings_len = 1024;
		    int szFound = nfc_reader.jnfc_list_devices(ctx, connstrings, connstrings_len);
		    
		    if(szFound == 0){
		    	out += "\nLibNfcActivity: No devices found " ;
		    	out += "\nszFound = " + Integer.toString(szFound)  ;
		    }else {
		    	out += "\nLibNfcActivity:  devices found " ;
		    	//check connstrings
		    	if(connstrings != null){
			    	//for (int i=0; i < szFound ; i++){
			    	//	out += "\n" + connstrings[i];
			    	//}
		    	}
		    }
			
			
			nfc_reader.jnfc_exit(ctx);
		}
		
		out += jLogger.getLog();
		tv.setText(out);
		this.setContentView(tv);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.lib_nfc, menu);
		return true;
	}
	

   	
	

}
