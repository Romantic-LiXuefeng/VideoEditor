/*
 * audio_effect_interface.h
 *
 *  Created on: 2014��7��16��
 *      Author: �в���
 */

#ifndef AUDIO_EFFECT_INTERFACE_H_
#define AUDIO_EFFECT_INTERFACE_H_

#include <base/f_audio_types.h>

//��Ч����
class AudioEffectInterface{
public:

    static const int kNoError             = 0;
    static const int kNoSupportEffect     = -1;


    //��ʼ��
    virtual int InitAudioEffect(int channel_count, int sample_rate, AudioEffect effect)=0;

    //����PCM����
    virtual int PutSamples(short *data, int sample_count)=0;

    //ȡ���������PCM��data�������max_sample_count��������������
    virtual int ReceiveSamples(short* data, int max_sample_count)=0;

    //�����δ����Ĳ�����
    virtual int GetRemainedSampleCount()=0;

    virtual ~AudioEffectInterface(){}
};



#endif // AUDIO_EFFECT_INTERFACE_H_ 
