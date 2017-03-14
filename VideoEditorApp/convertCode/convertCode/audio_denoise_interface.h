/*
 * audio_denoise_interface.h
 *
 *  Created on: 2014��8��28��
 *      Author: �в���
 */

#ifndef AUDIO_DENOISE_INTERFACE_H_
#define AUDIO_DENOISE_INTERFACE_H_

//��������
class AudioDenoiseInterface {

public:
    static const int kNoError               = 0;
    static const int kNotFoundCodec         = -1;
    static const int kAllocContextError     = -2;


    virtual int Init(int frame_size, int sample_rate, int channel_count)=0;

    virtual int Denoise(short *data)=0;

    virtual ~AudioDenoiseInterface() {
    }
};

#endif // AUDIO_DENOISE_INTERFACE_H_
