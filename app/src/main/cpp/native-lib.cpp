#include <jni.h>
#include <string>
#include "FileLogger.h"

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
    const char *logPath = env->GetStringUTFChars(log_path, JNI_FALSE);
    FileLogger *fileLogger = new FileLogger(logPath, max_file_size);
    env->ReleaseStringUTFChars(log_path, logPath);
    return (jlong)(fileLogger);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_mmappro_FileLogger_mNativeWrite(JNIEnv *env, jobject thiz, jlong m_native_ptr,
                                                 jbyteArray data_, jint length) {
    // TODO: implement mNativeWrite()
    jbyte *data = env->GetByteArrayElements(data_, NULL);
    FileLogger *logger = reinterpret_cast<FileLogger *>(m_native_ptr);
    if (logger != NULL)
        logger->writeDate((char *)data, length);
    env->ReleaseByteArrayElements(data_, data, 0);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_mmappro_FileLogger_mRealLength(JNIEnv *env, jobject thiz, jlong m_native_ptr) {
    // TODO: implement mRealLength()
    FileLogger *logger = reinterpret_cast<FileLogger *>(m_native_ptr);
    if (logger != NULL)
        return logger->dataDos;
    return 0;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_mmappro_FileLogger_mNativeRelease(JNIEnv *env, jobject thiz, jlong m_native_ptr) {
    // TODO: implement mNativeRelease()
    FileLogger *fileLogger = reinterpret_cast<FileLogger *>(m_native_ptr);
    if (fileLogger != NULL) {
        delete (fileLogger);
    }
}