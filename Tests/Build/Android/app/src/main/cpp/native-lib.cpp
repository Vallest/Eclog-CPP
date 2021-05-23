#include "UnitTesting.h"

#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <stdio.h>
#include <stdarg.h>

namespace {

    JNIEnv* g_JNIEnv;
    jobject g_Object;
    jclass g_MainActivity;
    jmethodID g_MainActivity_message;

    AAssetManager* g_AAssetManager;
}

extern "C" JNIEXPORT void JNICALL Java_com_eclog_1cpp_tests_MainActivity_setAssetManager(JNIEnv* env, jobject obj, jobject assetManager)
{
    g_AAssetManager = AAssetManager_fromJava(env, assetManager);
}

extern "C" JNIEXPORT void JNICALL Java_com_eclog_1cpp_tests_MainActivity_runTestCases(JNIEnv* env, jobject obj)
{
    g_JNIEnv = env;
    g_Object = obj;
    g_MainActivity = env->GetObjectClass(obj);
    g_MainActivity_message = env->GetMethodID(g_MainActivity, "message", "(Ljava/lang/String;)V");

    runTestCases();
}

class StreamBuf : public std::streambuf {
protected:
    int_type overflow(int_type ch)
    {
        buf_.push_back(traits_type::to_char_type(ch));
        
        if (ch == traits_type::to_int_type('\n'))
        {
            g_JNIEnv->CallVoidMethod(g_Object, g_MainActivity_message, g_JNIEnv->NewStringUTF(buf_.c_str()));
            buf_.clear();
        }

        return ch;
    }

private:
    std::string buf_;
};

std::ostream& getOutStream()
{
    static StreamBuf buf;
    static std::ostream os(&buf);

    return os;
}

bool loadTextFile(const char* filename, std::string& text)
{
    AAsset* assetFile = AAssetManager_open(g_AAssetManager, filename, AASSET_MODE_STREAMING);

    if (assetFile == 0) {
        return false;
    }

    size_t size = AAsset_getLength(assetFile);
    const void* data = AAsset_getBuffer(assetFile);

    text.resize(size);

    memcpy(&text[0], data, size);

    AAsset_close(assetFile);

    return true;
}

