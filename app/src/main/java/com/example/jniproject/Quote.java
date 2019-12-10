package com.example.jniproject;

import java.util.List;

/**
 * 引用类型
 * created by xiaojun at 2019/12/10
 */
public class Quote {
    private int intValue;
    private String strValue;
    private List<String> list;

    public List<String> getList() {
        return list;
    }

    public void setList(List<String> list) {
        this.list = list;
    }

    public int getIntValue() {
        return intValue;
    }

    public void setIntValue(int intValue) {
        this.intValue = intValue;
    }

    public String getStrValue() {
        return strValue;
    }

    public void setStrValue(String strValue) {
        this.strValue = strValue;
    }
}
