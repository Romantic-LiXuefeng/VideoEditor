/*
 * audio_recoder_interface.h
 *
 *  Created on: 2014��8��28��
 *      Author: Administrator
 */

#ifndef AUDIO_RECODER_INTERFACE_H_
#define AUDIO_RECODER_INTERFACE_H_

#include <base/f_audio_types.h>

//FIXME ����ֻ֧�ֵ�����(��������)����Чֻ֧��16λ����(�������)
//�÷�����SetInputAudioFormat����ѡ[SetOutPutAudioFormat��SetAudioDenoise��SetAudioEffect]��
//     Ȼ��InitAudioFile��EncodeAudioFrame��CloseAudioFile
class AudioRecorderIntreface {

public:
    enum {
        kNoError = 0,
        kCannotOpenOutputFile = -1,
        KAllocAvformatError = -2,
        kNotSupportFormatOfOutputFile = -3,
        kNotFoundEncoder = -4,
        kAllocStreamError = -5,
        kCannotOpenCodec = -6,
        kWriteFileHeaderError = -7,
        kFrameAllocError = -8,
        kAvframeGetbufferError = -9,
        kAudioEncodeError = -10,
        kWriteFrameError = -11,
        kFillFrameError = -12,
        kWriteFileTrailerError = -13,
        kFifoAllocError = -14,
        kCannotReallocateFifo = -15,
        kCannotWriteFifo = -16,
        kCannotReadFifo = -17,

    };

public:
    virtual ~AudioRecorderIntreface(){}

    //����������ƵPCM��ʽ
    virtual void SetInputAudioFormat(int sample_rate, FAudioChannelLayout channel_layout,
            FSampleFormat sample_format, int channel_count, int bit_rate)=0;
    //���������ƵPCM��ʽ
    virtual void SetOutPutAudioFormat(int sample_rate, FAudioChannelLayout channel_layout,
            FSampleFormat sample_format, int channel_count, int bit_rate)=0;
    //��������
    virtual void SetAudioDenoise()=0;
    //�����Ч
    virtual void SetAudioEffect(AudioEffect audio_effect)=0;

    //��ʼ���������ļ�����ʼ��������
    virtual int InitAudioFile(AudioEncoderName codec_name, const char* filename)=0;

    //������Ƶ���ݣ�����д���ļ���ע��planarʱdata��ָ������(����char*[4])
    virtual int EncodeAudioFrame(unsigned char **data, int sample_count)=0;

    //�ر��ļ�������
    virtual int CloseAudioFile()=0;
};



#endif /* AUDIO_RECODER_INTERFACE_H_ */
