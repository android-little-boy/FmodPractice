#include <unistd.h>
#include "com_androidlittleboy_fmodpractice_MainActivity.h"

extern "C"
JNIEXPORT void JNICALL Java_com_androidlittleboy_fmodpractice_MainActivity_voiceChangeNative
        (JNIEnv *env, jobject jobject1, jint jint1, jstring jstring1) {
    char *content_ = "默认 播放完毕";
    const char *path = env->GetStringUTFChars(jstring1, NULL);
    //音效引擎系统
    FMOD::System *system1 = 0;
    //声音
    FMOD::Sound *sound = 0;
    //音轨
    FMOD::Channel *channel = 0;
    //数据信号处理
    FMOD::DSP *dsp = 0;

    //创建系统
    FMOD::System_Create(&system1);
    //系统的初始化
    system1->init(32, FMOD_INIT_NORMAL, 0);
    //创建声音
    system1->createSound(path, FMOD_DEFAULT, 0, &sound);
    //播放声音
    system1->playSound(sound, 0, false, &channel);

    jclass mainAcJc = env->GetObjectClass(jobject1);
    jmethodID showComplete = env->GetMethodID(mainAcJc, "showComplete", "(Ljava/lang/String;)V");

    switch (jint1) {
        case com_androidlittleboy_fmodpractice_MainActivity_MODE_NORMAL:
            content_ = "默认 播放完毕";
            break;
        case com_androidlittleboy_fmodpractice_MainActivity_MODE_LUOLI:
            system1->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,2.0f);
            channel->addDSP(0,dsp);
            content_ = "萝莉 播放完毕";
            break;
        case com_androidlittleboy_fmodpractice_MainActivity_MODE_DASHU:
            system1->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,0.7f);
            channel->addDSP(0,dsp);
            content_ = "大叔 播放完毕";
            break;
        case com_androidlittleboy_fmodpractice_MainActivity_MODE_JINGSONG:
            content_ = "惊悚 播放完毕";
            system1->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,0.7f);
            channel->addDSP(0,dsp);

            // TODO 搞点回声
            // 回音 ECHO
            system1->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200); // 回音 延时    to 5000.  Default = 500.
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 10); // 回音 衰减度 Default = 50   0 完全衰减了
            channel->addDSP(1,dsp); // 第二个音轨

            // TODO 颤抖
            // Tremolo 颤抖音 正常5    非常颤抖  20
            system1->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_FREQUENCY, 20); // 非常颤抖
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.8f); // ？？？
            channel->addDSP(2, dsp); // 第三个音轨
            break;
        case com_androidlittleboy_fmodpractice_MainActivity_MODE_GAOGUAI:
            content_ = "搞怪 小黄人 播放完毕";

            // 小黄人声音 频率快

            // 从音轨拿 当前 频率
            float mFrequency;
            channel->getFrequency(&mFrequency);

            // 修改频率
            channel->setFrequency(mFrequency * 1.5f); // 频率加快  小黄人的声音
            break;
        case com_androidlittleboy_fmodpractice_MainActivity_MODE_KONGLING:
            content_ = "空灵 播放完毕";

            // 回音 ECHO
            system1->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200); // 回音 延时    to 5000.  Default = 500.
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 10); // 回音 衰减度 Default = 50   0 完全衰减了
            channel->addDSP(0,dsp);
            break;
    }


    bool isPlaying = true;
    while (isPlaying) {
        channel->isPlaying(&isPlaying);
        usleep(1000 * 1000);
    }

    //回收
    sound->release();
    system1->close();
    system1->release();
    env->ReleaseStringUTFChars(jstring1, path);

    jstring msg = env->NewStringUTF(content_);
    env->CallVoidMethod(jobject1, showComplete, msg);


}