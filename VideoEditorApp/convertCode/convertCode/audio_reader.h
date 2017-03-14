/*
 * audio_reader.h
 *
 *  Created on: 2014��7��22��
 *      Author: �в���
 */

#ifndef AUDIO_READER_H_
#define AUDIO_READER_H_

#ifndef __CANNOT_USE_LIBAV__

#include "audio_utils.h"
#include "audio_reader_interface.h"

struct AVFormatContext;
struct AVCodecContext;
struct AVFrame;

//��InitInputFileȻ��GetBufferSize�õ�����֡�ֽ���
//GetFrame��������ݴ�С����GetBufferSize��ֵ
//����GetFrameȡ����sample_countΪ���ݴ�С�����һ֡���ܱȽ�С��is_finishedΪ1�����
class AudioReader : public AudioReaderInterface {
private:
	static const int kMaxAudioBufferSize = 2048*8*2; //���ÿ֡2048����double����2����������еĸ�ʽ����û��֡��С
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

    AudioReader();
    ~AudioReader();

    //��ʼ�����ļ�
    int InitInputFile(const char* file_name);

    //ȡ��������Ƶ���ݡ����ظ�����is_finished����Ϊ1��ʾ�ļ�������is_finishedΪ0ʱ�д���
    int GetFrame(short* data, int& sample_count, int &is_finished);

//�첽
//    int Start(int is_async);
//    int Pause();
//    int Stop();

    //�ر��ļ�
    int CloseInputFile();
    //һ֡�����ݴ�С
    int GetBufferSize() {
        return buffer_size_;
    }
    //������
    int sample_rate() {
        return sample_rate_;
    }
    //������ʽ
    FAudioChannelLayout channel_layout() {
        return channel_layout_;
    }
    //������ʽ
    FSampleFormat sample_format() {
        return sample_format_;
    }
    //������
    int channel_count() {
        return channel_count_;
    }
    //������
    int bit_rate() {
        return bit_rate_;
    }

private:
    int OpenInputAudioFile(const char* filename, AVFormatContext ** fmt_ctx, AVCodecContext **av_ctx,
            int& stream_index);

    int DecodeAudioFrame(AVFrame *frame, AVFormatContext *fmtctx, AVCodecContext *avctx, int stream_index,
            int *datapresent, int *finished);

    const char *AvcodecGetName(int id);

    AVFormatContext *avformat_context_;
    AVCodecContext *avcodec_context_;
    AVFrame *avframe_;

    int sample_rate_;
    FAudioChannelLayout channel_layout_;
    FSampleFormat sample_format_;
    int channel_count_;
    int bit_rate_;

    int buffer_size_;

    int state_;
    int stream_index_;
    //planar��ʽ�������������������Ƿֿ��ģ���Ҫ��buffer�ֳɼ��ȷ֣��ֱ�洢����������
    bool is_planar_;
};

#endif //#ifndef __CANNOT_USE_LIBAV__

#endif // AUDIO_READER_H_
