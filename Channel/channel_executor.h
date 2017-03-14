#pragma once

#include<thread>

/*
* �ŵ�����������
* ����Ҫ���þ��Ƿ�װ�����ŵ���Ӧ����ĸ�������
* ���䴫�ݸ��ŵ���������
*/
class channel_job {

};

class channel_executor {
	
public:
	/*
	* ����һ�����л���ص�channel_executor,��ʵ����Ϊcached_pool_channel_executor
	* t_pool_num������������߳�����
	*/
	static channel_executor* new_cached_pool_channel_executor(int t_pool_num);

};

class cached_pool_channel_executor :public channel_executor {

private:
	int m_pool_num;
public:
	/*
	* ���캯����ָ���̳߳�����س�����
	*/
	cached_pool_channel_executor(int t_pool_num);

	std::thread t;

};
