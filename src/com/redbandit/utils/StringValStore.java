package com.redbandit.utils;

public class StringValStore {
	
	
	
	String mValue ;
	
	
	private StringValStoreListener mListener;
	
	
	
	public StringValStore(String initialValue){
		mValue = initialValue;
	}
	
	public void setListener(StringValStoreListener listener ){
		
		mListener = listener;
	}
     
	public void setValue(String newValue){
		mValue = newValue;
		if(mListener != null){
			mListener.onValueChanged(mValue);
		}
	}
	
	
	public String getValue(){
		return mValue;
	}
	
	public static interface StringValStoreListener {
		void onValueChanged(String newValue);
	}
	
}
