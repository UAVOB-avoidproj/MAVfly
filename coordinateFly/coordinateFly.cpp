#include <chrono>
#include <cstdint>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/offboard/offboard.h>
#include <iostream>
#include <future>
#include <memory>
#include <thread>

#include "enumVelocityBodyYawspeed.h"

using namespace mavsdk;
using std::chrono::seconds;
using std::this_thread::sleep_for;

int main(int argc, char** argv){
    
    // 创建Mavsdk对象，配置类型为CompanionComputer
    Mavsdk mavsdk{Mavsdk::Configuration{Mavsdk::ComponentType::CompanionComputer}};
    // 使用命令行参数连接到无人机
    ConnectionResult connection_result = mavsdk.add_any_connection("serial:///dev/serial/by-id/usb-ArduPilot_QioTekZealotH743_2D0040000D51303037363639-if00");

    // 如果连接失败，返回1
    if (connection_result != ConnectionResult::Success) {
        std::cerr << "Connection failed: " << connection_result << '\n';
        return 1;
    }
    // 寻找第一个自动飞行系统
    auto system = mavsdk.first_autopilot(3.0);
    if (!system) {
        std::cerr << "Timed out waiting for system\n";
        return 1;
    }
    // 获取自动飞行系统中的Action和Telemetry插件
    auto telemetry = Telemetry{system.value()};
    auto action = Action{system.value()};
    // 配置Telemetry插件以获取位置信息，并设置位置更新频率为1Hz
    const auto set_rate_result = telemetry.set_rate_position(1.0);
    if (set_rate_result != Telemetry::Result::Success) {
        std::cerr << "Setting rate failed: " << set_rate_result << '\n';
        return 1;
    }
    // 配置一个回调函数，当位置信息更新时被调用，打印出当前高度信息
    telemetry.subscribe_position([](Telemetry::Position position) {
        std::cout << "Altitude: " << position.relative_altitude_m << " m\n";
    });
    // 等待无人机准备就绪，可以执行飞行任务
//    while (telemetry.health_all_ok() != true) {
//        std::cout << "Vehicle is getting ready to arm\n";
//        sleep_for(seconds(1));
//    }

    // 解锁无人机，可以起飞
    std::cout << "Arming...\n";
    const Action::Result arm_result = action.arm();

    if (arm_result != Action::Result::Success) {
        std::cerr << "Arming failed: " << arm_result << '\n';
        return 1;
    }

    // 开始起飞
    std::cout << "Taking off...\n";
    const Action::Result takeoff_result = action.takeoff();
    if (takeoff_result != Action::Result::Success) {
        std::cerr << "Takeoff failed: " << takeoff_result << '\n';
        return 1;
    }

    //设置悬停高度为五米，并等待无人机到达悬停高度
    // std::cout << "Ascending to 5m...\n";
    // const Action::Result hover_result = action.goto_location(0, 0, 5, 0);
    // if (hover_result != Action::Result::Success) {
    //     std::cerr << "Hover failed: " << hover_result << '\n';
    //     return 1;
    // }

    // 无人机悬停10s
    std::cout << "Hovering for 10s...\n";
    sleep_for(seconds(10));

    // 设置无人机以 offboard 模式飞行
    while (mavsdk.systems().size() == 0) {
        sleep_for(seconds(1));
    }
    // 找到已发现的系统矢量
    auto system2 = mavsdk.systems()[0];
    auto offboard = Offboard{system2};

    // 创建初始设定值
    offboard.set_velocity_body({0.0f, 0.0f, 0.0f, 0.0f});

    // 开启 offboard 模式
    Offboard::Result offboard_result = offboard.start();
    if (offboard_result != Offboard::Result::Success) {
        std::cerr << "Offboard::start() failed: " << offboard_result << '\n';
    }
    std::cout << "Offboard started\n";
    // 设置飞行方向向前，持续3秒
    std::cout << "Offboard vbvForward……\n";
    offboard.set_velocity_body(vbyForward);
    sleep_for(seconds(7));

    // 设置悬停
    std::cout << "Offboard vbyStop……\n";
    offboard.set_velocity_body(vbyStop);
    sleep_for(seconds(3));
    //关闭 offboard 模式
    offboard_result = offboard.stop();
    if (offboard_result != Offboard::Result::Success) {
        std::cerr << "Offboard::stop() failed: " << offboard_result << '\n';
    }

    // 降落无人机
    std::cout << "Landing...\n";
    const Action::Result land_result = action.land();
    if (land_result != Action::Result::Success) {
        std::cerr << "Land failed: " << land_result << '\n';
        return 1;
    }
    // 等待无人机降落，并关闭连接
    while (telemetry.in_air()) {
        std::cout << "Vehicle is landing...\n";
        sleep_for(seconds(1));
    }
    std::cout << "Vehicle landed！\n";
    return 0;

}