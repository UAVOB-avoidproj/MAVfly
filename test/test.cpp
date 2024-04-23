#include <chrono>
#include <cstdint>
#include <iostream>
#include <future>
#include <memory>
#include <thread>

#include <mavsdk_init.hpp>
#include <flymode.hpp>

using std::chrono::seconds;
using std::this_thread::sleep_for;

int main(){
    FlyMode *rt = mavsdk_init();
    if(rt != nullptr){
        std::cout << "mavsdk_init success" << std::endl;
    }
    else{
        std::cout << "mavsdk_init failed" << std::endl;
        return 0;
    }

    sleep_for(seconds(3));

    bool rt2;
    //rt2 = rt->Offboard_init();
    // rt2 = rt->Offboard_close();
    rt2 = rt->Armed();
    // rt2 = rt->Disarmed();


    while(1){
        sleep_for(seconds(5));
    }
    return 0;
}