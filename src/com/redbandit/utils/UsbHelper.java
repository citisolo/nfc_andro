package com.redbandit.utils;

import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentTransaction;
import android.util.Log;

public class UsbHelper extends FragmentActivity {
	
	public String log = new String();
	String tag = "UsbHelper:";
	public static Intent intent = null;
	public static PendingIntent permissionIntent;
	
	
	static {
		System.loadLibrary("logger");
		System.loadLibrary("usb");
		System.loadLibrary("usbhelper");
	}
	
	public native int usbtest();
	public native void startDeviceSocket(String address, int descriptor);

	public UsbHelper(){
		
	}
	
	public void runTestDevice()
	{
		intent = getIntent();
		try 
		{
			final UsbManager manager = (UsbManager) getSystemService(Context.USB_SERVICE);
			final UsbDevice device = (UsbDevice) intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);
			permissionIntent = PendingIntent.getBroadcast(this, 0, new Intent("com.android.example.USB_PERMISSION"), 0);
			registerReceiver(mUsbReceiver, new IntentFilter("com.android.example.USB_PERMISSION"));
			
			
			
			if (device != null && !manager.hasPermission(device)) {
				//android.util.Log.d("rtl_tcp_andro", "No permissions for device, requesting!");
				manager.requestPermission(device, permissionIntent);
				return;
			}
			
			
			final UsbDeviceConnection connection = manager.openDevice(device);
			if (connection == null)
				throw new Exception();
			
			final String address = getFilesDir().getAbsolutePath()+"/socket";
			startDeviceSocket ( address, connection.getFileDescriptor());
			
		} 
		catch (Throwable e)
		{
			e.printStackTrace();
		}
		
		
	}
	
	/**
	 * Accepts permission
	 */
	public final BroadcastReceiver mUsbReceiver = new BroadcastReceiver() {

		
		public void onReceive(Context context, Intent intent) {

			String action = intent.getAction();
			if ("com.android.example.USB_PERMISSION".equals(action)) {
				synchronized (this) {

				}
			}

		}
	};

    
	
}
