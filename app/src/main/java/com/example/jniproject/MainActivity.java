package com.example.jniproject;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

import java.util.ArrayList;

/**
 * MainActivity
 * created by xiaojun
 */
public class MainActivity extends AppCompatActivity {

    boolean[] booleanArray = {true};
    byte[] byteArray = {(byte)1,(byte)2};
    char[] charArray = {'c','b','d'};
    short[] shortArray = {1,2,3,4};
    int[] intArray = {1,2,3,4,5};
    long[] longArray = {1,2,3,4,5,6};
    float[] floatArray = {1.f,2.f,3.f,4.f,5.f,6.f,7.f};
    double[] doubleArray = {1.,2.,3.,4.,5.,6.,7.,8.};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        /*JNI.getInstance().invokeFunction();//调用JNI方法
        JNI.getInstance().transformBasicData(false,(byte)11,'c',(short)22,1222,223222422,111.11f,22.22220000);
        JNI.getInstance().transformBasicDataArray(booleanArray,byteArray,charArray,shortArray,intArray,longArray,floatArray,doubleArray);
        JNI.getInstance().transformQuoteData("hahaha");
        Log.e("xiaojun","返回的intValue="+JNI.getInstance().getIntValue());
        Log.e("xiaojun","返回的booleanValue="+JNI.getInstance().getBooleanValue());
        Quote quote = JNI.getInstance().getQuoteValue();
        Log.e("xiaojun","返回的str="+quote.getStrValue());
        Log.e("xiaojun","返回的int="+quote.getIntValue());
        ArrayList<String> list = new ArrayList<>();
        JNI.getInstance().transformQuoteDataList(list);
        for (int i = 0; i < list.size(); i++) {
            Log.e("xiaojun","获取到的ArrayList.get="+list.get(i));
        }
        //返回ArrayList
        ArrayList<Quote> listQuotes = JNI.getInstance().getArrayList();
        Log.e("xiaojun","listQuote的数量为:"+listQuotes.size());
        Log.e("xiaojun","第一个Quote的值为:"+listQuotes.get(0).getIntValue());
        EnumWrapper.Color color = JNI.getInstance().getEnumColor();
        Log.e("xiaojun","获取到的Color为:"+color);
        //多线程调用某一个jni函数
        multiThreadOpearteNativeMethod();*/
        JNI.getInstance().findCustomClassInThread();
    }

    private void multiThreadOpearteNativeMethod(){
        Object objLock = new Object();
        Thread thread1 = new Thread(new MRunnable(objLock),"thread-1");
        Thread thread2 = new Thread(new MRunnable(objLock),"thread-2");
        thread1.start();
        thread2.start();
    }

    class MRunnable implements Runnable{

        private Object mObjLock;

        public MRunnable(Object objLock){
            this.mObjLock = objLock;
        }

        @Override
        public void run() {
            Log.e("xiaojun","开始调用 "+Thread.currentThread().getName()+" 线程");
            JNI.getInstance().multiThreadOperation(this.mObjLock);
            Log.e("xiaojun","调用 "+Thread.currentThread().getName()+" 线程------完成");
        }
    }

}
