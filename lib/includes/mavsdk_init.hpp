#ifndef __MAVSDK_INIT_HPP__
#define __MAVSDK_INIT_HPP__

#include <chrono>
#include <cstdint>
#include <iostream>
#include <future>
#include <memory>
#include <thread>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/offboard/offboard.h>

#include <flymode.hpp>

using namespace mavsdk;
using std::chrono::seconds;
using std::this_thread::sleep_for;

#define SERIAL "serial:///dev/serial/by-id/usb-ArduPilot_QioTekZealotH743_2D0040000D51303037363639-if00"

FlyMode *mavsdk_init(){
    Mavsdk mavsdk{Mavsdk::Configuration{Mavsdk::ComponentType::CompanionComputer}};

    // Serial connection
    ConnectionResult connection_result = mavsdk.add_any_connection(SERIAL);
    if (connection_result != ConnectionResult::Success) {
        std::cerr << "Serial:Connection failed: " << connection_result << '\n';
        return nullptr;
    }
    std::cout << "Serial:Connected success!\n";

    // find first_autopilot and init Telemetry and Action
    std::optional<std::shared_ptr<System>> system = mavsdk.first_autopilot(3.0);
    if (!system) {
        std::cerr << "System: Time out!\n";
        return nullptr;
    }
    Telemetry telemetry = Telemetry{system.value()};
    Action action = Action{system.value()};
    std::cout << "System: Find successful! and Telemetry/Action.\n";
    // std::cout << "System-action: " << &action <<std::endl;
    // std::cout << "System-telemetry: " << &telemetry <<std::endl;

    // const Action::Result arm_result = (&action)->arm();
    // if (arm_result != Action::Result::Success) {
    //     std::cerr << "Arming failed: " << arm_result << '\n';
    //     return nullptr;
    // }

    // Init Offboard mode
    // while (mavsdk.systems().size() == 0) {
    //     sleep_for(seconds(1));
    // }
    // std::shared_ptr<System> system2 = mavsdk.systems()[0];
    // Offboard offboard = Offboard{system2};
    // std::cout << "Offboard: Init successful!\n";
    // FlyMode *flymode = new FlyMode( &system, &action, &telemetry, &offboard);
    FlyMode *flymode = new FlyMode(&mavsdk, &system, &action, &telemetry);
    std::cout << 123 << std::endl;
    std::cout << &mavsdk << std::endl;
    std::cout << &system << std::endl;
    std::cout << &action << std::endl;
    std::cout << &telemetry << std::endl;

    return flymode;
}


#endif