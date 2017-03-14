/*
 * audio_recoder_wav.h
 *
 *  Created on: 2014��8��28��
 *      Author: �в���
 */

#ifndef AUDIO_RECODER_WAV_H_
#define AUDIO_RECODER_WAV_H_

#include <stdio.h>

#include "audio_recorder_interface.h"
#include "audio_denoise_interface.h"
#include "audio_effect_interface.h"

class AudioSampleFifo;

//FIXME ֻ֧�ֵ�������16λ����
//�÷�����SetInputAudioFormat����ѡ[SetOutPutAudioFormat��SetAudioDenoise��SetAudioEffect]��
//     Ȼ��InitAudioFile��EncodeAudioFrame��CloseAudioFile
class AudioRecorderWav : public AudioRecorderIntreface {

public:
	AudioRecorderWav();
    ~AudioRecorderWav();

    //����������ƵPCM��ʽ
    void SetInputAudioFormat(int sample_rate, FAudioChannelLayout channel_layout,
            FSampleFormat sample_format, int channel_count, int bit_rate);
    //���������ƵPCM��ʽ��
    // FIXME ��Ч��Ϊ�˼򵥣���ʵ����Ƶ�ز��������Բ���ת��ʽ
    void SetOutPutAudioFormat(int sample_rate, FAudioChannelLayout channel_layout,
            FSampleFormat sample_format, int channel_count, int bit_rate);
    //��������
    void SetAudioDenoise();
    //�����Ч
    void SetAudioEffect(AudioEffect audio_effect);

    //��ʼ���������ļ�����ʼ��������
    int InitAudioFile(AudioEncoderName codec_name, const char* filename);

    //������Ƶ���ݣ�����д���ļ���ע��planarʱdata��ָ������(����char*[4])
    int EncodeAudioFrame(unsigned char **data, int sample_count);

    //�ر��ļ�������
    int CloseAudioFile();

private:
	typedef struct{
		char riff_fileid[4];//"RIFF"
		unsigned int riff_file_length;
		char waveid[4];//"WAVE"

		char fmt_chkid[4];//"fmt"
		unsigned int     fmt_chk_length;

		unsigned short    format_tag;        /* format type */
		unsigned short    channels_count;         /* number of channels (i.e. mono, stereo, etc.) */
		unsigned int  	  samples_persecond;    /* sample rate */
		unsigned int  	  bytes_persecond;   /* for buffer estimation */
		unsigned short    block_align;       /* block size of data */
		unsigned short    bits_persample;

		char data_chkid[4];//"DATA"
		unsigned int data_chkLen;
	}WaveHeader;

    struct AudioFormat {
        int sample_rate;
        FAudioChannelLayout channel_layout;
        FSampleFormat sample_format;
        int channel_count;
        int bit_rate;
    } input_format_, output_format_;

    void InitWaveHeader(WaveHeader& wh);
    int GetBytesCountPerSample(FSampleFormat sf);

    int AddFrameToBuffer(unsigned char **data, const int sample_count);
    int GetFrameFromBuffer(unsigned char **data, int& sample_count);

    int Encode(int sample_count);

    int InitFrame();
    int InitAudioFifo();
    void InitAudioDenoise();
    void InitAudioEffect();
    int Denoise();

    AudioDenoiseInterface * audio_denoise_;
    AudioEffectInterface * audio_effect_;

    AudioEffect audio_effect_name_;
    FILE * wav_file_;

    WaveHeader wav_header_;

    AudioSampleFifo* audio_fifo_;
    // ÿ�δ����������20����������
    int frame_size_;
    // ��fifoȡ��������
    short *frame_buffer_;
};



#endif /* AUDIO_RECODER_WAV_H_ */
