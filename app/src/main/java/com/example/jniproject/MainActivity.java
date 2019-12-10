package com.example.jniproject;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        JNI.getInstance().invokeFunction();//调用JNI方法
        JNI.getInstance().transformBasicData(false,(byte)11,'c',(short)22,1222,223222422,111.11f,22.22220000);
        boolean[] booleanArray = {true};
        byte[] byteArray = {(byte)1,(byte)2};
        char[] charArray = {'c','b','d'};
        short[] shortArray = {1,2,3,4};
        int[] intArray = {1,2,3,4,5};
        long[] longArray = {1,2,3,4,5,6};
        float[] floatArray = {1.f,2.f,3.f,4.f,5.f,6.f,7.f};
        double[] doubleArray = {1.,2.,3.,4.,5.,6.,7.,8.};
        JNI.getInstance().transformBasicDataArray(booleanArray,byteArray,charArray,shortArray,intArray,longArray,floatArray,doubleArray);
    }
}
