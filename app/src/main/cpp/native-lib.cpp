#include <unistd.h>
#include "com_androidlittleboy_fmodpractice_MainActivity.h"

extern "C"
JNIEXPORT void JNICALL Java_com_androidlittleboy_fmodpractice_MainActivity_voiceChangeNative
        (JNIEnv *env, jobject jobject1, jint jint1, jstring jstring1) {
    char *content_ = "默认 播放完毕";
    const char *path = env->GetStringUTFChars(jstring1, NULL);
    //音效引擎系统
    FMOD::System * system1 = 0;
    //声音
    FMOD::Sound * sound = 0;
    //音轨
    FMOD::Channel * channel = 0;
    //数据信号处理
    FMOD::DSP * dsp = 0;

    //创建系统
    FMOD::System_Create(&system1);
    //系统的初始化
    system1->init(32,FMOD_INIT_NORMAL,0);
    //创建声音
    system1->createSound(path,FMOD_DEFAULT,0,&sound);
    //播放声音
    system1->playSound(sound,0, false,&channel);

    bool isPlaying = true;
    while (isPlaying){
        channel->isPlaying(&isPlaying);
        usleep(1000*1000);
    }

    //回收
    sound->release();
    system1->close();
    system1->release();
    env->ReleaseStringUTFChars(jstring1,path);


}