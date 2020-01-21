package com.example.jniproject;

/**
 * 枚举包裹类
 * created by xiaojun at 2020/01/21
 */
public class EnumWrapper {

    enum Color{
        RED,GREEN,BLUE
    }

    private Color mColor;

    public void setColor(Color color){
        this.mColor = color;
    }

    public Color getColor(){
        return this.mColor;
    }

}
