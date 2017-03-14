/*
 * audio_reader_interface.h
 *
 *  Created on: 2014��8��28��
 *      Author: �в���
 */

#ifndef AUDIO_READER_INTERFACE_H_
#define AUDIO_READER_INTERFACE_H_


#include "audio_utils.h"


struct AVFormatContext;
struct AVCodecContext;
struct AVFrame;

//��InitInputFileȻ��GetBufferSize�õ�����֡�ֽ���
//GetFrame��������ݴ�С����GetBufferSize��ֵ
//����GetFrameȡ����sample_countΪ���ݴ�С�����һ֡���ܱȽ�С��is_finishedΪ1�����
class AudioReaderInterface {
public:
    enum {
        kNoError = 0,
        kCannotOpenInputFile = -1,
        kNotFindStream = -2,
        kNotFindCodec = -3,
        kCannotOpenCodec = -4,
        kNotFindAudioStream = -5,
        kFileEnd = -6,
        kDecodeFrameError = -7,
        kAvframeMallocError = -8,
        kDatabufferError    = -9,
        kReadFrameError      = -10,
    };

    virtual ~AudioReaderInterface(){}

    //��ʼ�����ļ�
    virtual int InitInputFile(const char* file_name)=0;

    //ȡ��������Ƶ���ݡ����ظ�����is_finished����Ϊ1��ʾ�ļ�������is_finishedΪ0ʱ�д���
    virtual int GetFrame(short* data, int& sample_count, int &is_finished)=0;

    //�ر��ļ�
    virtual int CloseInputFile()=0;
    //һ֡�����ݴ�С
    virtual int GetBufferSize() =0;
    //������
    virtual int sample_rate() =0;
    //������ʽ
    virtual FAudioChannelLayout channel_layout() =0;
    //������ʽ
    virtual FSampleFormat sample_format() =0;
    //������
    virtual int channel_count() =0;
    //������
    virtual int bit_rate() =0;

};


#endif /* AUDIO_READER_INTERFACE_H_ */
