package com.example.jniproject;

import java.util.ArrayList;

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

    //---------------------------------------------传递数据------------------------------------------------------

    //传递基本数据类型给C++
    public native void transformBasicData(boolean boolValue,byte byteValue,char charValue,short shortValue,int intValue,long longValue,float floatValue,double doubleValue);
    //传递基本数据类型数组给C++
    public native void transformBasicDataArray(boolean[] booleanArray,byte[] byteArray,char[] charArray,short[] shortArray,int[] intArray,long[] longArray,float[] floatArray,double[] doubleArray);
    //传递引用类型数据给C++
    public native void transformQuoteData(String str);
    //传递更复杂的ArrayList对象
    public native void transformQuoteDataList(ArrayList<String> list);

    //---------------------------------------------返回数据---------------------------------------------------

    //返回基本数据类型
    public native  int getIntValue();
    public native boolean getBooleanValue();
    //返回引用类型
    public native Quote getQuoteValue();
    //返回集合类型
    public native ArrayList<Quote> getArrayList();
    //返回枚举类型
    public native EnumWrapper.Color getEnumColor();
    //------------------------------------------------多线程---------------------------------------------------

    /**
     * 多线程调用此函数测试线程同步问题
     * 本地方法被多个线程调用
     * @param objLock java层的同步锁对象
     */
    public native void multiThreadOperation(Object objLock);
}
