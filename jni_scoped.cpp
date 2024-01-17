//
// Created by bingdff on 2024/1/17.
//

#ifndef SCOPED_JNI_SCOPED_H
#define SCOPED_JNI_SCOPED_H
#include "jni_scoped.h"

ScopedJavaLocalRef<jclass> GetClassInternal(JNIEnv* env,
                                            const char* class_name,
                                            jobject class_loader) {
    jclass clazz;
    if (class_loader != nullptr) {
        // ClassLoader.loadClass expects a classname with components separated by
        // dots instead of the slashes that JNIEnv::FindClass expects. The JNI
        // generator generates names with slashes, so we have to replace them here.
        // TODO(torne): move to an approach where we always use ClassLoader except
        // for the special case of base::android::GetClassLoader(), and change the
        // JNI generator to generate dot-separated names. http://crbug.com/461773
        size_t bufsize = strlen(class_name) + 1;
        char dotted_name[bufsize];
        memmove(dotted_name, class_name, bufsize);
        for (size_t i = 0; i < bufsize; ++i) {
            if (dotted_name[i] == '/') {
                dotted_name[i] = '.';
            }
        }

        clazz = static_cast<jclass>(
                env->CallObjectMethod(class_loader, g_class_loader_load_class_method_id,
                                      ConvertUTF8ToJavaString(env, dotted_name).obj()));
    } else {
        clazz = env->FindClass(class_name);
    }
    if (ClearException(env) || !clazz) {
        LOG(FATAL) << "Failed to find class " << class_name;
    }
    return ScopedJavaLocalRef<jclass>(env, clazz);
}
#endif //SCOPED_JNI_SCOPED_H
