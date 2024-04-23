#ifndef __FLYMODE_HPP__
#define __FLYMODE_HPP__

#include <iostream>
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

// #include <enumVelocityBodyYawspeed.h>

using namespace mavsdk;
using std::chrono::seconds;
using std::this_thread::sleep_for;

class FlyMode {
public:
    // FlyMode(std::optional<std::shared_ptr<System>> *, Action *, Telemetry *, Offboard *);
    FlyMode(Mavsdk *, std::optional<std::shared_ptr<System>> *, Action *, Telemetry *);
    ~FlyMode();

    bool Armed();
    bool Disarmed();
    bool Offboard_init();
    bool Offboard_close();

    // bool Offboard_Forward();

private:
    Mavsdk *mavsdk_ptr;
    std::optional<std::shared_ptr<System>> *system_ptr;
    Action *action_ptr;
    Telemetry *telemetry_ptr;
    Offboard *offboard_ptr;

    bool Offboard_status;
    bool Armed_status;
    Telemetry::FlightMode FlightMode_status;
    Telemetry::Health System_status;

};
#endif