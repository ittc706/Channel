#include <iostream>
#include"channel_executor.h"

using namespace std;


int main() {
	channel_executor* exec = channel_executor::new_cached_pool_channel_executor(5);

	channle_calculator_runnable *cjd1 = new channle_calculator_runnable();
	channle_calculator_runnable *cjd2 = new channle_calculator_runnable();
	channle_calculator_runnable *cjd3 = new channle_calculator_runnable();
	channle_calculator_runnable *cjd4 = new channle_calculator_runnable();
	channle_calculator_runnable *cjd5 = new channle_calculator_runnable();
	channle_calculator_runnable *cjd6 = new channle_calculator_runnable();

	std::chrono::milliseconds dura1(2000);
	std::this_thread::sleep_for(dura1);

	exec->execute(cjd1);
	exec->execute(cjd2);
	exec->execute(cjd3);
	exec->execute(cjd4);
	exec->execute(cjd5);
	exec->execute(cjd6);

	std::chrono::milliseconds dura2(2000);
	std::this_thread::sleep_for(dura2);

	cout << "wake up" << endl;

	exec->shutdown();
	return 0;
}

