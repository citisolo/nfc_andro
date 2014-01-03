package com.redbandit.utils;

import com.redbandit.utils.StringValStore.StringValStoreListener;
import android.content.Context;
import android.util.AttributeSet;
import android.widget.TextView;

public class StringTextView extends TextView implements StringValStoreListener {
	
	public StringTextView(Context context){
		super(context);
	}
	
	public StringTextView(Context context, AttributeSet attrs){
		super(context, attrs);
	}
    
	public void onValueChanged(String newValue){
		//setText(newValue);
		append(newValue);
	}
}
