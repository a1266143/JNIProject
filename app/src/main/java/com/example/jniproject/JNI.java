package com.example.jniproject;

/**
 * 存放所有本地方法的类
 * created by xiaojun at 2019/11/28
 */
public class JNI {

    static {
        System.loadLibrary("native-lib");
    }

    private static JNI mJni = new JNI();

    public static JNI getInstance(){
        return mJni;
    }

    //调用C++中的空方法
    public native void invokeFunction();

}
