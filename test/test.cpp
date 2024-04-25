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

int main(){
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

    
    *rt = 0;
    std::thread thread2(Offboard_Init, std::ref(rt));
    thread2.detach();
    while(1){
        if(*rt == 0) std::cout << "offboard_init ……\n";
        if(*rt == 1) break;
        if(*rt == -1) {std::cout << "offboard_init failed\n";return 0;}
        sleep_for(seconds(1));
    }
    std::cout << "offboard_init successful!\n";

    std::thread thread3(Offboard_VBY, vbyForward);
    thread3.detach();

    

    while(1){
        sleep_for(seconds(5));
    }
    return 0;
}