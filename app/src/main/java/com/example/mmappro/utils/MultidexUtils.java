package com.example.mmappro.utils;

import android.os.Looper;
import android.util.Log;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MultidexUtils {

    public static boolean isMainThread() {return Looper.myLooper() == Looper.getMainLooper();}
    public static boolean isVMMultidexCapable(){
        return isVMMultidexCapable(System.getProperty("java.vm.version"));
    }
    //MultiDex 拷出来的的方法，判断VM是否支持多dex
    public static boolean isVMMultidexCapable(String versionString) {
        boolean isMultidexCapable = false;
        if (versionString != null) {
            Matcher matcher = Pattern.compile("(\\d+)\\.(\\d+)(\\.\\d+)?").matcher(versionString);
            if (matcher.matches()) {
                try {
                    int major = Integer.parseInt(matcher.group(1));
                    int minor = Integer.parseInt(matcher.group(2));
                    isMultidexCapable = major > 2 || major == 2 && minor >= 1;
                } catch (NumberFormatException var5) {
                }
            }
        }
        Log.i("MultiDex", "VM with version " + versionString + (isMultidexCapable ? " has multidex support" : " does not have multidex support"));
        return isMultidexCapable;
    }
}
