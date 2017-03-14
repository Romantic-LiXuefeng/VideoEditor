/*
 * audio_denoise_speex.cpp
 *
 *  Created on: 2014��7��18��
 *      Author: �в���
 */

#include "audio_denoise_speex.h"

#include <stdlib.h>

#include "speex/speex_preprocess.h"

#include "audio_utils.h"

AudioDenoiseSpeex::AudioDenoiseSpeex() :
        speex_pre_process_state_(NULL) {

}
AudioDenoiseSpeex::~AudioDenoiseSpeex() {
    if (speex_pre_process_state_ != NULL) {
        speex_preprocess_state_destroy(speex_pre_process_state_);
        speex_pre_process_state_ = NULL;
    }
}

int AudioDenoiseSpeex::Init(int frame_size, int sample_rate,
        int channel_count) {
    F_AUDIO_LOG_ASSERT(channel_count == 1, "only support 1 channel now");

    int i;
    //  int count = 0;
    // float f;

    speex_pre_process_state_ = speex_preprocess_state_init(frame_size,
            sample_rate);
    i = 1;
    speex_preprocess_ctl(speex_pre_process_state_, SPEEX_PREPROCESS_SET_DENOISE,
            &i); // ����
    i = 25;
    speex_preprocess_ctl(speex_pre_process_state_,
            SPEEX_PREPROCESS_SET_NOISE_SUPPRESS, &i); //����������dB
    i = 0; // ���ٷ��ֲ� 1 �� 2 �رգ������뻳�ɲ���������Ӧ����0��,1����
    speex_preprocess_ctl(speex_pre_process_state_, SPEEX_PREPROCESS_SET_AGC,
            &i); //�Զ�����
    //    i = 8000;
    //    speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_AGC_LEVEL, &i);
    //    i = 0;
    //    speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_DEREVERB, &i);
    //    f = .0;
    //    speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_DEREVERB_DECAY, &f);
    //    f = .0;
    //    speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_DEREVERB_LEVEL, &f);

    return kNoError;
}

int AudioDenoiseSpeex::Denoise(short *data) {

    speex_preprocess_run(speex_pre_process_state_, data);

    return kNoError;
}

