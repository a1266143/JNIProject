//
// Created by Administrator on 2019/11/28.
//

#include <jni.h>
#include <android/log.h>
#include <thread>
#include <chrono>//时间

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE,"xiaojunJNI_Verbose",__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"xiaojunJNI_Debug",__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"xiaojunJNI_Error",__VA_ARGS__)

//本地方法所在类
const char *NATIVE_CLASS_NAME = "com/example/jniproject/JNI";

//-----------------------------------------------常规方法声明---------------------------------------------
void JNI_invokeFunction(JNIEnv *env);

void JNI_transformBasicData(JNIEnv *env, jclass clazz, jboolean boolValue, jbyte byteValue,
                            jchar charValue, jshort shortValue, jint intValue, long longValue,
                            float floatValue, double doubleValue);

void JNI_transformBasicDataArray(JNIEnv *env, jclass clazz, jbooleanArray booleanArray,
                                 jbyteArray byteArray, jcharArray charArray, jshortArray shortArray,
                                 jintArray intArray, jlongArray longArray, jfloatArray floatArray,
                                 jdoubleArray doubleArray);

void JNI_transformQuoteData(JNIEnv *env, jclass clazz, jstring str);

void JNI_transformQuoteDataList(JNIEnv *env, jclass clazz, jobject arrayList);

jint JNI_getIntValue(JNIEnv *env, jclass clazz);

jboolean JNI_getBooleanValue(JNIEnv *env, jclass clazz);

jobject JNI_getQuoteValue(JNIEnv *env, jclass clazz);

void JNI_multiThreadOperation(JNIEnv *env, jclass clazz, jobject objLock);

jobject JNI_getArrayList(JNIEnv *env,jclass clazz);

jobject JNI_getEnumColor(JNIEnv *env,jclass clazz);

/**
 * JNI方法声明
 */
const JNINativeMethod nativeMethods[] = {
        {"invokeFunction",          "()V",                              (void *) JNI_invokeFunction},
        {"transformBasicData",      "(ZBCSIJFD)V",                      (void *) JNI_transformBasicData},
        {"transformBasicDataArray", "([Z[B[C[S[I[J[F[D)V",              (void *) JNI_transformBasicDataArray},
        {"transformQuoteData",      "(Ljava/lang/String;)V",            (void *) JNI_transformQuoteData},
        {"transformQuoteDataList",  "(Ljava/util/ArrayList;)V",         (void *) JNI_transformQuoteDataList},
        {"getIntValue",             "()I",                              (void *) JNI_getIntValue},
        {"getBooleanValue",         "()Z",                              (void *) JNI_getBooleanValue},
        {"getQuoteValue",           "()Lcom/example/jniproject/Quote;", (void *) JNI_getQuoteValue},
        {"multiThreadOperation",    "(Ljava/lang/Object;)V",            (void *) JNI_multiThreadOperation},
        {"getArrayList",    "()Ljava/util/ArrayList;",            (void *) JNI_getArrayList},
        {"getEnumColor",    "()Lcom/example/jniproject/EnumWrapper$Color;",            (void *) JNI_getEnumColor},
};

/**
 * 绑定Java层的native方法
 * @param env
 * @return
 */
jint bindJavaNative(JNIEnv *env) {
    jclass clazz = NULL;
    clazz = env->FindClass(NATIVE_CLASS_NAME);
    if (clazz == NULL)
        return false;
    int numberOfJNIMethods = sizeof(nativeMethods) / sizeof(nativeMethods[0]);
    return env->RegisterNatives(clazz, nativeMethods, numberOfJNIMethods);
}

bool unBindJavaNative(JNIEnv *env) {
    jclass clazz = NULL;
    clazz = env->FindClass(NATIVE_CLASS_NAME);
    if (clazz == NULL)
        return false;
    return env->UnregisterNatives(clazz) == 0;
}

/**
 *动态加载JNI方法
 */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    jint res = bindJavaNative(env);
    if (res != 0) {
        LOGE("---------------------------绑定本地方法失败------------------------");
    } else {
        LOGE("---------------------------绑定本地方法成功------------------------");
        return JNI_VERSION_1_6;
    }
}

/**
 * 动态卸载JNI方法
 * 此方法需要被显示调用
 */
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE("获取Env失败,JNI_OnUnload");
        return;
    }
    bool res = unBindJavaNative(env);
    if (!res) {
        LOGE("---------------------------卸载JNI方法失败---------------------------");
    } else {
        LOGD("---------------------------卸载JNI方法成功---------------------------");
    }
}


//------------------------------------------JNI方法-----------------------------------------------
void JNI_invokeFunction(JNIEnv *env) {
    LOGD("你通过JNI调用了C++方法");
}

void JNI_transformBasicData(JNIEnv *env, jclass clazz, jboolean booleanValue, jbyte byteValue,
                            jchar charValue, jshort shortValue, jint intValue,
                            long longValue, float floatValue, double doubleValue) {
    LOGD("你通过JNI调用了C++方法,传递了booleanValue=%d,byteValue=%d,charValue=%c,shortValue=%d,intValue=%d,longValue=%ld,floatValue=%f,doubleValue=%f",
         booleanValue, byteValue, charValue, shortValue, intValue, longValue, floatValue,
         doubleValue);
}

void JNI_transformBasicDataArray(JNIEnv *env, jclass clazz, jbooleanArray booleanArray,
                                 jbyteArray byteArray, jcharArray charArray, jshortArray shortArray,
                                 jintArray intArray, jlongArray longArray, jfloatArray floatArray,
                                 jdoubleArray doubleArray) {
    jsize numOfbooleanArray = env->GetArrayLength(booleanArray);
    jsize numOfbyteArray = env->GetArrayLength(byteArray);
    jsize numOfcharArray = env->GetArrayLength(charArray);
    jsize numOfshortArray = env->GetArrayLength(shortArray);
    jsize numOfintArray = env->GetArrayLength(intArray);
    jsize numOflongArray = env->GetArrayLength(longArray);
    jsize numOffloatArray = env->GetArrayLength(floatArray);
    jsize numOfdoubleArray = env->GetArrayLength(doubleArray);
    LOGD("你通过JNI调用了C++方法,numOfbooleanArray=%d,numOfbyteArray=%d,numOfcharArray=%d,numOfshortArray=%d,numOfintArray=%d,numOflongArray=%d,numOffloatArray=%d,numOfdoubleArray=%d",
         numOfbooleanArray, numOfbyteArray, numOfcharArray, numOfshortArray, numOfintArray,
         numOflongArray, numOffloatArray, numOfdoubleArray);
}

void JNI_transformQuoteData(JNIEnv *env, jclass clazz, jstring str) {
    jsize lengthOfStr = env->GetStringLength(str);
    LOGD("获取到的java字符串长度为:%d", lengthOfStr);
    /*jboolean isCopy = JNI_FALSE;
    const jchar *chars = env->GetStringChars(str,&isCopy);
    LOGD("获取到的chars数组为:%s",chars);*/
    jsize lengthOfStrUTF_8 = env->GetStringUTFLength(str);
    LOGD("获取到的java字符串UTF-8长度为:%d", lengthOfStrUTF_8);
    const char *chars = env->GetStringUTFChars(str, NULL);
    LOGD("获取到的java字符串UTF-8为:%s", chars);
    env->ReleaseStringUTFChars(str, chars);
}

void JNI_transformQuoteDataList(JNIEnv *env, jclass clazz, jobject arrayList) {
    jclass classArrayList = env->GetObjectClass(arrayList);
    jmethodID methodID_ArrayList_add = env->GetMethodID(classArrayList, "add",
                                                        "(Ljava/lang/Object;)Z");
    jstring strValue = env->NewStringUTF("additem0");
    jint result = env->CallBooleanMethod(arrayList, methodID_ArrayList_add, strValue);
    if (result) {
        LOGD("底层给ArrayList增加对象成功");
    } else {
        LOGD("底层给ArrayList增加对象失败");
    }
}

jint JNI_getIntValue(JNIEnv *env, jclass clazz) {
    return 1;
}

jboolean JNI_getBooleanValue(JNIEnv *env, jclass clazz) {
    bool result = false;
    return static_cast<jboolean>(result);
//    return 0;//false
//    return 123;//true
}

jobject JNI_getQuoteValue(JNIEnv *env, jclass clazz) {
    jclass classQuote = env->FindClass("com/example/jniproject/Quote");
    jobject objQuote = env->AllocObject(classQuote);
    jmethodID methodIDQuote_setIntValue = env->GetMethodID(classQuote, "setIntValue", "(I)V");
    jmethodID methodIDQuote_setStrValue = env->GetMethodID(classQuote, "setStrValue",
                                                           "(Ljava/lang/String;)V");
    jmethodID methodIDQuote_setListValue = env->GetMethodID(classQuote, "setList",
                                                            "(Ljava/util/List;)V");

    //生成值
    jint intValue = 123;
    const char *cStr = "cpp";
    jstring str = env->NewStringUTF(cStr);
    //创建ArrayList对象,并且添加数据到数据集中
    jclass classArrayList = env->FindClass("java/util/ArrayList");
    jobject objArrayList = env->AllocObject(classArrayList);
    jmethodID methodIDArrayList_add = env->GetMethodID(classArrayList, "add","(Ljava/lang/Object;)Z");
    jstring jstr = env->NewStringUTF("c++ArrayValue");

// TODO this will crash when set jstr to the following method
//    jboolean result = env->CallBooleanMethod(objArrayList, methodIDArrayList_add, jstr);
//    if (!result) {
//        LOGD("c++增加数据到ArrayList失败");
//        return NULL;
//    }

    env->CallVoidMethod(objQuote, methodIDQuote_setIntValue, intValue);
    env->CallVoidMethod(objQuote, methodIDQuote_setStrValue, str);
    env->CallVoidMethod(objQuote, methodIDQuote_setListValue, objArrayList);

    return objQuote;

}

jobject JNI_getArrayList(JNIEnv *env,jclass clazz){
    //新建ArrayList对象
    jclass cls_ArrayList = env->FindClass("java/util/ArrayList");
    //jobject obj_ArrayList = env->AllocObject(cls_ArrayList);
    //构造方法(注意:这里新建ArrayList对象不能调用上面的AllocObject方法，会Crash)
    jmethodID methoID_listInit = env->GetMethodID(cls_ArrayList,"<init>","()V");
    jobject obj_ArrayList = env->NewObject(cls_ArrayList,methoID_listInit);
    jmethodID methodID_add = env->GetMethodID(cls_ArrayList,"add","(Ljava/lang/Object;)Z");
    //新建Quote对象
    jclass cls_Quote = env->FindClass("com/example/jniproject/Quote");
    jobject obj_Quote = env->AllocObject(cls_Quote);
    jmethodID methodID_setIntValue = env->GetMethodID(cls_Quote,"setIntValue","(I)V");
    env->CallVoidMethod(obj_Quote,methodID_setIntValue,10);
    //调用ArrayList中的add方法
    env->CallBooleanMethod(obj_ArrayList,methodID_add,obj_Quote);
    return obj_ArrayList;
}

//因为枚举类是一个内部类，所以在签名的地方表示内部类中需要写成 Class$Class,以$连接
//因为枚举也是类，枚举中的值是静态变量
jobject JNI_getEnumColor(JNIEnv *env,jclass clazz){
    jclass cls_enumColor = env->FindClass("com/example/jniproject/EnumWrapper$Color");
    jfieldID fid_RED = env->GetStaticFieldID(cls_enumColor,"GREEN","Lcom/example/jniproject/EnumWrapper$Color;");
    jobject obj_RED = env->GetStaticObjectField(cls_enumColor,fid_RED);
    return obj_RED;
}


//这里使用c++11中的线程库实现线程sleep操作(注意，请在module中加入cppFlags "-std=c++11"以支持c++11
void JNI_multiThreadOperation(JNIEnv *env, jclass clazz, jobject objLock) {
    //进入同步区(临界区)，类似于Synchronzied
    jint lockEnterStatus = env->MonitorEnter(objLock);
    LOGD("线程正在执行");
    if (lockEnterStatus == JNI_OK) {
        //执行耗时操作,这里睡眠5秒
        std::chrono::milliseconds duration(5000);
        std::this_thread::sleep_for(duration);
    }
    //退出临界区
    jint lockExitStatus = env->MonitorExit(objLock);
    LOGD("线程执行完成");
//    if (lockExitStatus == JNI_OK)
}

