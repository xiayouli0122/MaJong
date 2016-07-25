package com.cgc.frame;

public class Common {
	
	public static boolean isValidSysVersion() {
    	String sVersion = android.os.Build.VERSION.RELEASE;
    	float ver = Float.parseFloat(sVersion.substring(0, 3));
    	//System.out.println("---------------------------build version="+ver);
    	float minVer = 2.2f;
        return ver >= minVer ? true : false;
    }
	
	public static void addMarketLog() {
    	   
    }
}
