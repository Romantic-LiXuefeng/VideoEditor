/*
 * audio_denoise_speex.h
 *
 *  Created on: 2014��7��18��
 *      Author: �в���
 */

#ifndef AUDIO_DENOISE_SPEEX_H_
#define AUDIO_DENOISE_SPEEX_H_

#include "audio_denoise_interface.h"

struct SpeexPreprocessState_;

//fixme ʹ��speex���룬Ŀǰֻ�ܴ���������ÿ��SpeexPreprocessState_ֻ�ܴ���һ��������
class AudioDenoiseSpeex : public AudioDenoiseInterface{
public:
    AudioDenoiseSpeex();
    virtual ~AudioDenoiseSpeex();

    virtual int Init(int frame_size, int sample_rate, int channel_count);

    virtual int Denoise(short *data);



private:
    SpeexPreprocessState_* speex_pre_process_state_;

};




#endif // AUDIO_DENOISE_SPEEX_H_ 
