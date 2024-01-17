//
// Created by bingdff on 2024/1/17.
//

#ifndef SCOPED_JNI_SCOPED_H
#define SCOPED_JNI_SCOPED_H

#include <jni.h>

class ScopedJavaLocalFrame {
        public:
        explicit ScopedJavaLocalFrame(JNIEnv* env);
        ScopedJavaLocalFrame(JNIEnv* env, int capacity);

        ScopedJavaLocalFrame(const ScopedJavaLocalFrame&) = delete;
        ScopedJavaLocalFrame& operator=(const ScopedJavaLocalFrame&) = delete;

        ~ScopedJavaLocalFrame();

        private:
        // This class is only good for use on the thread it was created on so
        // it's safe to cache the non-threadsafe JNIEnv* inside this object.
        JNIEnv* env_;
};
#endif //SCOPED_JNI_SCOPED_H
