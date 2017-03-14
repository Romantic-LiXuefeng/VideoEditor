/*
 * audio_convert.h
 *
 *  Created on: 2014��7��24��
 *      Author: �в���
 */

#ifndef AUDIO_CONVERT_H_
#define AUDIO_CONVERT_H_

#include <base/f_audio_types.h>

#include "audio_reader_interface.h"
#include "audio_recorder_interface.h"


//FIXME �����̰߳�ȫ��
class AudioConvert{
public:
    const static int kNoError             = 0;
    const static int kAllocMemoryError    = -1;

    AudioConvert(char* libname);
    ~AudioConvert();

    //�����Ч����init֮ǰ����
    void AddAudioEffect(AudioEffect effect);
    //���������ƵPCM��ʽ
    void SetOutPutAudioFormat(int sample_rate, FAudioChannelLayout channel_layout,
		   FSampleFormat sample_format, int channel_count, int bit_rate);
    //��ʼ�������ļ������������[��Ч]��
    int Init(const char* in, const char* out);
    //ת����ֱ���ļ��������
    int Convert();

private:

AudioReaderInterface    *reader_;
AudioRecorderIntreface   *recorder_;

//����õ�����������
unsigned char* audio_frame_buffer_;
//����planar��ʽ��ÿ���������ݷֿ�����¼ÿ������������audio_frame_buffer_�ĵ�ַ
unsigned char** encode_frame_buffer_;

//volatile bool is_stopped;

const static AudioEncoderName kEncoder = kEncodeVoAacenc;
};



#endif // AUDIO_CONVERT_H_ 
