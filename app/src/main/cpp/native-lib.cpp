#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_mmappro_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_mmappro_FileLogger_mNativeCreate(JNIEnv *env, jobject thiz, jstring log_path,
                                                  jint max_file_size) {
    // TODO: implement mNativeCreate()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_mmappro_FileLogger_mNativeWrite(JNIEnv *env, jobject thiz, jlong m_native_ptr,
                                                 jbyteArray data, jint length) {
    // TODO: implement mNativeWrite()
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_mmappro_FileLogger_mRealLength(JNIEnv *env, jobject thiz, jlong m_native_ptr) {
    // TODO: implement mRealLength()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_mmappro_FileLogger_mNativeRelease(JNIEnv *env, jobject thiz, jlong m_native_ptr) {
    // TODO: implement mNativeRelease()
}