#include <chrono>
#include <cstdint>
#include <iostream>
#include <future>
#include <memory>
#include <thread>

#include <mavsdk_simplify.hpp>
#include <enumVelocityBodyYawspeed.h>

using std::chrono::seconds;
using std::this_thread::sleep_for;

#define wait_time 3

int main(){
    // 初始换基本的 MAVSDK 参数
    int *rt = new int;
    *rt = 0;
    std::thread thread1(Mavsdk_Init, std::ref(rt));
    thread1.detach();
    while(1){
        if(*rt == 0) std::cout << "mavsdk_init ……\n";
        if(*rt == 1) break;
        if(*rt == -1) {std::cout << "mavsdk_init failed\n";return 0;}
        sleep_for(seconds(1));
    }
    std::cout << "mavsdk_init success" << std::endl;

    // Armed();

    // 初始化 offboard 控制
    *rt = 0;
    std::thread thread2(Offboard_Init, std::ref(rt), wait_time);
    thread2.detach();
    while(1){
        if(*rt == 0) std::cout << "offboard_init ……\n";
        if(*rt == 1) break;
        if(*rt == -1) {std::cerr << "offboard_init failed\n";return 0;}
        sleep_for(seconds(1));
    }
    std::cout << "offboard_init successful!\n";

    // 设置 offboard 飞行姿态为“向前”
    setOffboard_VBY(vbyForward);
    

    while(1){
        sleep_for(seconds(5));
    }
    return 0;
}