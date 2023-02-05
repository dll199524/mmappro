package com.example.mmappro;

import java.io.File;

public class FileLogger {

    private long mNativePtr;
    File mlogFile;
    public FileLogger(File logFile, int maxFileSize) {
        this.mlogFile = logFile;
        mNativePtr = mNativeCreate(mlogFile.getAbsolutePath(), maxFileSize);
    }

    public void log(String content) {
        byte[] data = content.getBytes();
        mNativeWrite(mNativePtr, data, data.length);
    }
    public int length() {return mRealLength(mNativePtr);}
    public void release() {mNativeRelease(mNativePtr);}

    private native long mNativeCreate(String logPath, int maxFileSize);
    private native void  mNativeWrite(long mNativePtr, byte[] data, int length);
    private native int mRealLength(long mNativePtr);
    private native void mNativeRelease(long mNativePtr);


}
