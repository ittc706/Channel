#include"channel_executor.h"

using namespace std;

channel_executor* channel_executor::new_cached_pool_channel_executor(int t_pool_num) {
	return new cached_pool_channel_executor(t_pool_num);
}


cached_pool_channel_executor::cached_pool_channel_executor(int t_pool_num) {
	this->m_pool_num = t_pool_num;
}
