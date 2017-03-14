#pragma once

#include<thread>

/*
* 信道计算任务类
* 其主要作用就是封装计算信道响应矩阵的各个参数
* 将其传递给信道计算引擎
*/
class channel_job_detail {

};

/*
* 信道计算结果类
* 其主要作用就是封装信道响应计算结果的各个参数
*/
class channel_output_dto {

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
	* 计算信道响应
	*/
	virtual channel_output_dto* calculate(channel_job_detail* t_channel_job_detail) = 0;

};

class cached_pool_channel_executor :public channel_executor {

private:
	int m_pool_num;
public:
	/*
	* 构造函数，指定线程池最大县城数量
	*/
	cached_pool_channel_executor(int t_pool_num);

	std::thread t;

};
