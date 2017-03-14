/*
 * audio_recorder.h
 *
 *  Created on: 2014��7��17��
 *      Author: �в���
 */

#ifndef AUDIO_RECODER_H_
#define AUDIO_RECODER_H_

#ifndef __CANNOT_USE_LIBAV__

#include "audio_recorder_interface.h"
#include "audio_resample_interface.h"
#include "audio_denoise_interface.h"
#include "audio_effect_interface.h"

struct AVFormatContext;
struct AVCodecContext;
struct AVFrame;
struct AVAudioFifo;

//FIXME ����ֻ֧�ֵ�����(��������)����Чֻ֧��16λ����(�������)
//�÷�����SetInputAudioFormat����ѡ[SetOutPutAudioFormat��SetAudioDenoise��SetAudioEffect]��
//     Ȼ��InitAudioFile��EncodeAudioFrame��CloseAudioFile
class AudioRecorder : public AudioRecorderIntreface,public AudioResampleCallbackIntreface {

public:
    AudioRecorder();
    ~AudioRecorder();

    //����������ƵPCM��ʽ
    void SetInputAudioFormat(int sample_rate, FAudioChannelLayout channel_layout,
            FSampleFormat sample_format, int channel_count, int bit_rate);
    //���������ƵPCM��ʽ
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

    //ʵ�ֽӿڵķ����������ز����ص�
    int AudioResampleCallback();

private:
    struct AudioFormat {
        int sample_rate;
        FAudioChannelLayout channel_layout;
        FSampleFormat sample_format;
        int channel_count;
        int bit_rate;
    } input_format_, output_format_;

    int OpenOutputAudioFile(AudioEncoderName codec_name, const char *filename,
            AVFormatContext **fmt_ctx, AVCodecContext **codec_ctx);

    int InitAvframe();
    int InitAudioFifo();

    int AddFrameToBuffer(unsigned char **data, const int sample_count);
    int GetFrameFromBuffer(unsigned char **data, int& sample_count);
    //  int GetFifoFrameDataSize();

    int Resample();

    int Encode();

    void InitAudioDenoise();
    void InitAudioEffect();
    int Denoise();

    //ÿ�δӻ���ȡ����֡��С�������ز�����ʹ���ز�������ڱ����֡��С��frame size��
    // int fifo_frame_size_;
    //  unsigned char *fifo_frame_data_;
    //  int fifo_frame_data_size_;
    AVFrame *fifo_avframe_;

    AudioEffect audio_effect_name_;

    AudioResampleIntreface* audio_resample_;
    AudioDenoiseInterface * audio_denoise_;
    AudioEffectInterface * audio_effect_;

    AVFormatContext *avformat_context_;
    AVCodecContext *avcodec_context_;
    AVFrame *avframe_;
    AVAudioFifo *audio_fifo_;
};

#endif //__CANNOT_USE_LIBAV__

#endif // AUDIO_RECODER_H_
