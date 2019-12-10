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
    //传递基本数据类型给C++
    public native void transformBasicData(boolean boolValue,byte byteValue,char charValue,short shortValue,int intValue,long longValue,float floatValue,double doubleValue);
    //传递基本数据类型数组给C++
    public native void transformBasicDataArray(boolean[] booleanArray,byte[] byteArray,char[] charArray,short[] shortArray,int[] intArray,long[] longArray,float[] floatArray,double[] doubleArray);
}
