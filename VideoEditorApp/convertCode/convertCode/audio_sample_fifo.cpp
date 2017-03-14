/*
 * audio_sample_fifo.cpp
 *
 *  Created on: 2014��8��28��
 *      Author: �в���
 */

#include "audio_sample_fifo.h"

#include "audio_utils.h"
#include <string.h>

static int GetBytesCountPerSample(FSampleFormat sf) {
	switch (sf) {
	case kSampleFmtU8:
	case kSampleFmtU8p:
		return 1;
	case kSampleFmtS16:
	case kSampleFmtS16p:
		return 2;
	case kSampleFmtS32:
	case kSampleFmtS32p:
	case kSampleFmtFlt:
	case kSampleFmtFltp:
		return 4;
	case kSampleFmtDbl:
	case kSampleFmtDblp:
		return 8;

	}
	F_AUDIO_LOG_ASSERT(false, "No support sample format %d", sf);
	return 0;
}

//������ʽ��ͨ��������ʼ����С����󻺴�
AudioSampleFifo::AudioSampleFifo(FSampleFormat sample_format, int channel_count,
		int init_size, int max_size) {
	max_samples_ = max_size;
	bytes_persample_ = GetBytesCountPerSample(sample_format) * channel_count;
	totle_sample_count_ = init_size;
	current_sample_count_ = 0;
	buffer_ = new unsigned char[totle_sample_count_ * bytes_persample_];
	buffer_start_ = buffer_end_ = buffer_;
	totle_bytes_size_ = totle_sample_count_ * bytes_persample_;
}

AudioSampleFifo::~AudioSampleFifo() {
	current_sample_count_ = 0;
	totle_sample_count_ = 0;
	buffer_end_ = buffer_start_ = NULL;
	totle_bytes_size_ = 0;
	if (buffer_) {
		delete buffer_;
		buffer_ = NULL;
	}
}

//��ǰ�洢������
int AudioSampleFifo::GetSamplesCount() {
	return current_sample_count_;
}

//�������ݣ�������������ʱ���Զ�����
int AudioSampleFifo::PutData(unsigned char* data, unsigned samples_count) {
	if ((totle_bytes_size_ - (buffer_end_ - buffer_))
			>= (samples_count * bytes_persample_)) {
		//ĩβ���㹻�ռ�洢��ֱ�Ӵ�
		memcpy(buffer_end_, data, samples_count * bytes_persample_);
		buffer_end_ += samples_count * bytes_persample_;
		current_sample_count_ += samples_count;
	} else if (totle_sample_count_ - current_sample_count_ >= samples_count) {
		//���㹻�ռ䣬
		//�����ڴ�
		memcpy(buffer_, buffer_start_, buffer_end_ - buffer_start_);
		buffer_start_ = buffer_;
		buffer_end_ = buffer_start_ + current_sample_count_ * bytes_persample_;
		//����������
		memcpy(buffer_end_, data, samples_count * bytes_persample_);
		buffer_end_ += samples_count * bytes_persample_;
		current_sample_count_ += samples_count;
	} else {
		//��Ҫ�������ռ����洢����
		if (totle_sample_count_ > max_samples_) {
			//�����������������ڴ�
			return kOverMaxSize;
		}
		//�����µ��ڴ�ռ䣬��������ڴ�
		totle_sample_count_ += samples_count;
		totle_bytes_size_ = totle_sample_count_ * bytes_persample_;
		unsigned char* tmp = new unsigned char[totle_bytes_size_];
		if (tmp == NULL) {
			F_AUDIO_LOG_ERROR("fifo alloc memory failed");
			return kAllocMemeryError;
		}
		memcpy(tmp, buffer_start_, buffer_end_ - buffer_start_);
		delete buffer_;
		buffer_ = tmp;
		buffer_start_ = buffer_;
		buffer_end_ = buffer_start_ + current_sample_count_ * bytes_persample_;
		//����������
		memcpy(buffer_end_, data, samples_count * bytes_persample_);
		buffer_end_ += samples_count * bytes_persample_;
		current_sample_count_ += samples_count;

	}
	return kNoError;
}

//ȡ���ݣ������ַ�Ͳ�����������ȡ���Ĳ�����
int AudioSampleFifo::GetData(unsigned char* data, unsigned samples_count) {
	if (current_sample_count_ == 0) {
		return 0;
	} else if (current_sample_count_ >= samples_count) {
		//���㹻������
		memcpy(data, buffer_start_, samples_count * bytes_persample_);
		current_sample_count_ -= samples_count;
		buffer_start_ += samples_count * bytes_persample_;
		//���û�������ˣ�������ֹ��ַ
		if (buffer_end_ == buffer_start_) {
			buffer_end_ = buffer_start_ = buffer_;
		}
		return samples_count;
	} else {
		//���ݲ���
		int copy_sample_count = current_sample_count_;
		memcpy(data, buffer_start_, buffer_end_ - buffer_start_);
		current_sample_count_ = 0;
		buffer_end_ = buffer_start_ = buffer_;
		return copy_sample_count;
	}

}

