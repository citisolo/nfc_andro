package com.redbandit.ndklibnfc;

import android.os.Bundle;

import android.app.Activity;
import android.view.Menu;
import android.widget.TextView;


public class LibNfcActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//setContentView(R.layout.activity_lib_nfc);
		TextView tv = new TextView(this);
		tv.setTextSize(30);
		
		
		NfcReader nfc_reader = new NfcReader();
		long ctx = nfc_reader.jnfc_init(); // initialize context
		if (ctx == 0){
			//print failure message 
			tv.setText("LibNfcActivity: context is null");
		}
		else
		{
			//Print success message
			tv.setText("LibNfcActivity: context = 0x" + ctx );
			nfc_reader.jnfc_exit(ctx);
		}
			
		this.setContentView(tv);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.lib_nfc, menu);
		return true;
	}
	

   	
	

}
