#include <mavsdk_init.hpp>
#include <flymode.hpp>

int main(){
    FlyMode *rt = mavsdk_init();
    if(rt != nullptr){
        std::cout << "mavsdk_init success" << std::endl;
    }
    else{
        std::cout << "mavsdk_init failed" << std::endl;
    }
    

    return 0;
}