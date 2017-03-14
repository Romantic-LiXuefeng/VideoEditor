/*
 * audio_effect_soundtouch.h
 *
 *  Created on: 2014��7��21��
 *      Author: �в���
 */

#ifndef AUDIO_EFFECT_SOUNDTOUCH_H_
#define AUDIO_EFFECT_SOUNDTOUCH_H_

#include "audio_effect_interface.h"

namespace soundtouch{
class SoundTouch;
}

//soundtouchʵ����Ч,ֻ֧��16λ������soundtouch�Ĳ���λ����ͨ����ָ���ģ�ֻ���ڱ���ʱ�ı䣩
class AudioEffectSoundtouch : public AudioEffectInterface{
public:
    AudioEffectSoundtouch();
    ~AudioEffectSoundtouch();

    virtual int InitAudioEffect(int channel_count, int sample_rate, AudioEffect effect);

    virtual int PutSamples(short *data, int sample_count);

    virtual int ReceiveSamples(short* data, int max_sample_count);

    virtual int GetRemainedSampleCount();


private:
    int SetEffect(AudioEffect effect);


soundtouch::SoundTouch *soundtouch_;

};



#endif // AUDIO_EFFECT_SOUNDTOUCH_H_ 
