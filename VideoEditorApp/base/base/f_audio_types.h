/*
 * f_audio_types.h
 *
 *  Created on: 2014��7��16��
 *      Author: �в���
 */

#ifndef F_AUDIO_TYPES_H_
#define F_AUDIO_TYPES_H_

//TODO ��Ƶ����ͨ�õĽṹ�嶨�壬��Ҫʱ���

//��Ƶ֡��PCM
struct FAudioFrame{
    void *data;                 //��Ƶ֡����
    unsigned sample_count;      //������
};

//��Ƶ���������
struct FAudioPacket{
    void *data;                 //��Ƶ��������
    unsigned size;              //���ݳ���
    int stream_index;           //������Ƶ��
    long long pts;                //��ʾʱ���
    long long dts;                //����ʱ���
};

//�����������ڱ�ʾʱ��
struct FRational{
    int num; //����
    int den; //��ĸ
};

//֧�ֵ���Ƶ������
enum AudioEncoderName{
    kEncodeNone = -1,
    kEncodeVoAacenc   = 0,
    kEncodeSpeex      = 1,
    kEncodeAmrNb      = 2
};

//֧�ֵ���Ƶ������
enum AudioDecoderName{
    kDecodeAAC,
    kDecodeSpeex,
    kDecodeAmrNb
};

//��Ƶ������ʽ
enum FAudioChannelLayout{
    kMono      = 0,
    kStereo    = 1
};

//������ʽ
enum FSampleFormat{
    kSampleFmtU8        = 0,         // unsigned 8 bits
    kSampleFmtS16       = 1,         // signed 16 bits
    kSampleFmtS32       = 2,         // signed 32 bits
    kSampleFmtFlt       = 3,         // float
    kSampleFmtDbl       = 4,         // double

    kSampleFmtU8p       = 5,        // unsigned 8 bits, planar
    kSampleFmtS16p      = 6,        // signed 16 bits, planar
    kSampleFmtS32p      = 7,        // signed 32 bits, planar
    kSampleFmtFltp      = 8,        // float, planar
    kSampleFmtDblp      = 9         // double, planar
};

enum AudioEffect{
    kMale               = 0,
    kFemale             = 1,
    kLabixiaoxin        = 2
};

#endif // F_AUDIO_TYPES_H_ 
