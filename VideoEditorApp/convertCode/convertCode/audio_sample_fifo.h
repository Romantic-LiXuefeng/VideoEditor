/*
 * audio_sample_fifo.h
 *
 *  Created on: 2014��8��28��
 *      Author: �в���
 */

#ifndef AUDIO_SAMPLE_FIFO_H_
#define AUDIO_SAMPLE_FIFO_H_

#include <base/f_audio_types.h>

//��Ƶ�������У������������򽻴�洢�Ĳ������ݣ�û��֧��planar�洢��
class AudioSampleFifo {
public:
	static int const kNoError 			= 0;
	static int const kOverMaxSize 		= -1;
	static int const kAllocMemeryError  = -2;

public:
	//������ʽ��ͨ��������ʼ����С����󻺴�
	AudioSampleFifo(FSampleFormat sample_format, int channel_count, int init_size = 1024, int max_size = 4096);
	~AudioSampleFifo();

	//��ǰ�洢������
	int GetSamplesCount();
	//�������ݣ�������������ʱ���Զ����䣬�ڴ泬����������ֵ�����ʧ�ܡ�0�ɹ�������ʧ�ܡ�
	int PutData(unsigned char* data, unsigned samples_count);
	//ȡ���ݣ������ַ�Ͳ�����������ȡ���Ĳ�����
	int GetData(unsigned char* data, unsigned samples_count);

private:

	//ÿ�����ֽ����������ֽ���*������
	int bytes_persample_;
	//�����ܴ�С
	int totle_sample_count_;
	int totle_bytes_size_;
	//��ǰ�洢������
	int current_sample_count_;
	//�����ַ
	unsigned char* buffer_;
	//��ǰ������ʼ��ַ
	unsigned char* buffer_start_;
	//���ݽ�����ַ
	unsigned char* buffer_end_;

	//��󻺴�
	int max_samples_;

};



#endif /* AUDIO_SAMPLE_FIFO_H_ */
