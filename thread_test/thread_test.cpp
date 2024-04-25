#include <iostream>
#include <thread>

using std::chrono::seconds;
using std::this_thread::sleep_for;

void thread_task(int id) {
    std::cout << "Thread " << id << " started." << std::endl;
    // ... 执行相关任务 ...
    std::cout << "Thread " << id << " finished." << std::endl;
}


int main(){

    std::thread thread1(thread_task, 1);  // 使用函数
    // thread1.join();
    thread1.detach();

    std::cout << "OK\n";

    sleep_for(seconds(3));


    return 0;
}