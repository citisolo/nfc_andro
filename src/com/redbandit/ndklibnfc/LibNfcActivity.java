package com.redbandit.ndklibnfc;

import android.os.Bundle;

import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.TextView;
import android.widget.Button;


public class LibNfcActivity extends Activity {
	
	 TextView logView ;
	 Button   btnStart ;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_lib_nfc);
		logView = (TextView)findViewById(R.id.vwLog);
		btnStart = (Button) findViewById(R.id.btnStart);
		
		//logView.setBackgroundColor(255);
		
		//btnStart.setOnClickListener(l)
		//this.setContentView(tv);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.lib_nfc, menu);
		return true;
	}
	
    public void start_server(View view){
    	TextView tv = new TextView(this);
		String out = new String() ;
		logView.setTextSize(15);
		
		
		NfcReader nfc_reader = new NfcReader();
		int logOK = nfc_reader.register();
		if (logOK != 0 ){
			
		}
		
		
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
		out += nfc_reader.log;
		logView.setText(out);
    	
    }
   	
	

}
