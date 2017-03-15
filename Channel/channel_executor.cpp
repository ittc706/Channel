#include<iostream>
#include <cassert>
#include"channel_executor.h"

using namespace std;

int channle_calculator_runnable::s_runnable_count=0;

void channle_calculator_runnable::calculate(){
    cout<<"running channle_calculator_runnable#calculate("<<id<<")"<<endl;
}


channel_executor* channel_executor::new_cached_pool_channel_executor(int t_pool_num) {
    return new cached_pool_channel_executor(t_pool_num);
}


cached_pool_channel_executor::cached_pool_channel_executor(int t_pool_num) {
    m_pool_num = t_pool_num;
    m_is_running=true;
    m_threads.reserve(m_pool_num);//预分配指定数量的内存,避免表扩展,由于thread不可拷贝
    for(int i=0;i<m_pool_num;i++){
        m_threads.push_back(thread(&cached_pool_channel_executor::run,this));
    }
}

void cached_pool_channel_executor::execute(channle_calculator_runnable* t_channle_calculator_runnable){
    m_task_queue.push_back(t_channle_calculator_runnable);

    m_task_queue_is_not_empty.notify_one();
}


void cached_pool_channel_executor::shutdown(){
    m_is_running=false;
    //这个notify_all()是要让所有线程都苏醒,然后退出while循环结束run方法
    m_task_queue_is_not_empty.notify_all();
    for(int i=0;i<m_pool_num;i++){
        m_threads[i].join();
    }
}

void cached_pool_channel_executor::run(){
    try{
        while(m_is_running){
            channle_calculator_runnable* runnable=take();
            if(runnable!=nullptr){
                runnable->calculate();
            }
        }
        cout<<"thread is ending"<<endl;
    }
    catch (const exception& ex) {

    }
    catch(...) {

    }
}


channle_calculator_runnable* cached_pool_channel_executor::take(){
    unique_lock<mutex> lock(m_mutex);
    while(m_task_queue.empty()&&m_is_running){
        m_task_queue_is_not_empty.wait(lock);
    }

    channle_calculator_runnable* runnable=nullptr;
    if(!m_task_queue.empty()){
        runnable=m_task_queue.front();
        m_task_queue.pop_front();
    }
    return runnable;
}



