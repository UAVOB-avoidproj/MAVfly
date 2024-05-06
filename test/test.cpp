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
    int rt = 0;
    std::thread thread1(Mavsdk_Init, &rt);
    thread1.detach();
    while(1){
        if(rt == 0) std::cout << "mavsdk_init ……\n";
        if(rt == 1) break;
        if(rt == -1) {std::cout << "mavsdk_init failed\n";return 0;}
        sleep_for(seconds(1));
    }
    std::cout << "mavsdk_init success" << std::endl;

    while(1){
        cout_sth();
        sleep_for(seconds(1));
    }

    if(!Armed()){return 0;}

    //  action 控制起飞
    rt = 0;
    std::thread thread_takeoff(Action_takeoff, &rt, 3);
    thread_takeoff.detach();
    while(1){
        if(rt == 0) std::cout << "Action_takeoff ……\n";
        if(rt == 1) break;
        if(rt == -1) {std::cerr << "Action_takeoff failed\n";return 0;}
        sleep_for(seconds(1));
    }
    std::cout << "Action_takeoff successful!\n";



    // 等候 5 秒
    sleep_for(seconds(30));


    // 初始化 offboard 控制
    rt = 0;
    std::thread thread2(Offboard_Init, &rt, wait_time);
    thread2.detach();
    while(1){
        if(rt == 0) std::cout << "offboard_init ……\n";
        if(rt == 1) break;
        if(rt == -1) {std::cerr << "offboard_init failed\n";return 0;}
        sleep_for(seconds(1));
    }
    std::cout << "offboard_init successful!\n";

    // // // 设置 offboard 飞行姿态为“向前”
    // setOffboard_VBY(vbyForward);

    // // 等候 5 秒
    // sleep_for(seconds(10));
    // setOffboard_VBY(vbyStop);

    // action 控制降落
    rt = 0;
    std::thread thread_land(Action_land, &rt);
    thread_land.detach();
    while(1){
        if(rt == 0) std::cout << "Action_land ……\n";
        if(rt == 1) break;
        if(rt == -1) {std::cerr << "Action_land failed\n";return 0;}
        sleep_for(seconds(1));
    }
    std::cout << "Action_land successful!\n";

    // 停止 offboard 控制
    rt = 0;
    std::thread thread3(Offboard_Stop, &rt);
    thread3.detach();
    while(1){
        if(rt == 0) std::cout << "offboard_stop ……\n";
        if(rt == 1) break;
        if(rt == -1) {std::cerr << "offboard_stop failed\n";return 0;}
        sleep_for(seconds(1));
    }
    std::cout << "offboard_stop successful!\n";

    while(1){
        sleep_for(seconds(5));
    }
    return 0;
}