//
// Created by Administrator on 2019/11/28.
//

#include <jni.h>
#include <android/log.h>

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

/**
 * JNI方法声明
 */
const JNINativeMethod nativeMethods[] = {
        {"invokeFunction",          "()V",                 (void *) JNI_invokeFunction},
        {"transformBasicData",      "(ZBCSIJFD)V",         (void *) JNI_transformBasicData},
        {"transformBasicDataArray", "([Z[B[C[S[I[J[F[D)V", (void *) JNI_transformBasicDataArray},
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
         numOfbooleanArray,numOfbyteArray,numOfcharArray,numOfshortArray,numOfintArray,numOflongArray,numOffloatArray,numOfdoubleArray);
}

