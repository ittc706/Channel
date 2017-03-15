#pragma once

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<deque>
#include<string>


/*
* 信道计算参数dto
* 其主要作用就是封装信道响应输入参数
*/
class channel_input_dto {

};

/*
* 信道计算结果dto
* 其主要作用就是封装信道响应计算结果的各个参数
*/
class channel_output_dto {

};

/*
* 信道计算任务类
* 封装了两个成员,input_dto和output_dto
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
	* 计算信道响应矩阵
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
	* 产生一个带有缓存池的channel_executor,其实现类为cached_pool_channel_executor
	* t_pool_num：缓存池最大的线程数量
	*/
	static channel_executor* new_cached_pool_channel_executor(int t_pool_num);

public:
	/*
	* 执行任务
	*/
	virtual void execute(channle_calculator_runnable* t_channle_calculator_runnable) = 0;

	/*
	* 停止接受任务,并等待队列中的任务执行完毕
	*/
	virtual void shutdown() = 0;
};

class cached_pool_channel_executor :public channel_executor {

private:
	/*
	* 线程池的数量
	*/
	int m_pool_num;

	/*
	* 线程池容器
	*/
	std::vector<std::thread> m_threads;

	/*
	* 互斥量
	*/
	std::mutex m_mutex;

	/*
	* 条件变量
	*/
	std::condition_variable m_condition_variable;

	/*
	* 任务队列
	*/
	std::deque<channle_calculator_runnable*> m_task_queue;

	/*
	* 任务队列
	*/
	bool m_is_running;

	/*
	* 队列是否为空的条件对象
	*/
	std::condition_variable m_task_queue_is_not_empty;
public:
	/*
	* 构造函数，指定线程池最大线程数量
	*/
	cached_pool_channel_executor(int t_pool_num);

	/*
	* 析构函数
	*/
	~cached_pool_channel_executor() { shutdown(); }

	/*
	* 计算信道响应
	*/
	void execute(channle_calculator_runnable* t_channle_calculator_runnable) override;

	/*
	* 停止接受任务,并等待队列中的任务执行完毕
	*/
	void shutdown() override;

private:
	/*
	* 线程循环执行
	*/
	void run();

	/*
	* 取队列顶端的任务
	*/
	channle_calculator_runnable* take();
};
