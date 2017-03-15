#pragma once

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<deque>
#include<string>


/*
* �ŵ��������dto
* ����Ҫ���þ��Ƿ�װ�ŵ���Ӧ�������
*/
class channel_input_dto {

};

/*
* �ŵ�������dto
* ����Ҫ���þ��Ƿ�װ�ŵ���Ӧ�������ĸ�������
*/
class channel_output_dto {

};

/*
* �ŵ�����������
* ��װ��������Ա,input_dto��output_dto
*/
class channel_job_detail {
private:
	channel_input_dto* m_input_dto;
	channel_output_dto* m_output_dto;
};


class channle_calculator_runnable {
public:
	static int s_runnable_count;

	/*
	* �����ŵ���Ӧ����
	*/
	void calculate();

	void setter_channel_job_detail(channel_job_detail *t_channel_job_detail) {
		m_channel_job_detail = t_channel_job_detail;
	}

	channle_calculator_runnable() { std::cout << "new channle_calculator_runnable() ......" << std::endl; }

	const int id = s_runnable_count++;
private:
	channel_job_detail* m_channel_job_detail = nullptr;
};


class channel_executor {

public:
	/*
	* ����һ�����л���ص�channel_executor,��ʵ����Ϊcached_pool_channel_executor
	* t_pool_num������������߳�����
	*/
	static channel_executor* new_cached_pool_channel_executor(int t_pool_num);

public:
	/*
	* ִ������
	*/
	virtual void execute(channle_calculator_runnable* t_channle_calculator_runnable) = 0;

	/*
	* ֹͣ��������,���ȴ������е�����ִ�����
	*/
	virtual void shutdown() = 0;
};

class cached_pool_channel_executor :public channel_executor {

private:
	/*
	* �̳߳ص�����
	*/
	int m_pool_num;

	/*
	* �̳߳�����
	*/
	std::vector<std::thread> m_threads;

	/*
	* ������
	*/
	std::mutex m_mutex;

	/*
	* ��������
	*/
	std::condition_variable m_condition_variable;

	/*
	* �������
	*/
	std::deque<channle_calculator_runnable*> m_task_queue;

	/*
	* �������
	*/
	bool m_is_running;

	/*
	* �����Ƿ�Ϊ�յ���������
	*/
	std::condition_variable m_task_queue_is_not_empty;
public:
	/*
	* ���캯����ָ���̳߳�����߳�����
	*/
	cached_pool_channel_executor(int t_pool_num);

	/*
	* ��������
	*/
	~cached_pool_channel_executor() { shutdown(); }

	/*
	* �����ŵ���Ӧ
	*/
	void execute(channle_calculator_runnable* t_channle_calculator_runnable) override;

	/*
	* ֹͣ��������,���ȴ������е�����ִ�����
	*/
	void shutdown() override;

private:
	/*
	* �߳�ѭ��ִ��
	*/
	void run();

	/*
	* ȡ���ж��˵�����
	*/
	channle_calculator_runnable* take();
};
