#include <chrono>
#include <cstdint>
#include <iostream>
#include <future>
#include <memory>
#include <thread>

#include <mavsdk_simplify.hpp>

using std::chrono::seconds;
using std::this_thread::sleep_for;

int main(){
    std::thread thread1(Mavsdk_Init);
    thread1.detach();
    // auto rt = Mavsdk_Init();
    // if(rt){
    //     std::cout << "mavsdk_init success" << std::endl;
    // }
    // else{
    //     std::cout << "mavsdk_init failed" << std::endl;
    //     return 0;
    // }

    sleep_for(seconds(3));

    bool rt2;
    //rt2 = rt->Offboard_init();
    // rt2 = rt->Offboard_close();
    rt2 = Armed();
    // rt2 = rt->Disarmed();
    if(rt2){
        std::cout << "Test OK!" << std::endl;
    }
    else{
        std::cout << "Test Failed!" << std::endl;
    }

    while(1){
        sleep_for(seconds(5));
    }
    return 0;
}