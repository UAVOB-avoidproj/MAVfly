#ifndef __FLYMODE_HPP__
#define __FLYMODE_HPP__

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

static Mavsdk *mavsdk_ptr = nullptr;
static std::optional<std::shared_ptr<System>> *system_ptr = nullptr;
static Action *action_ptr = nullptr;
static Telemetry *telemetry_ptr = nullptr;
static Offboard *offboard_ptr = nullptr;

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


    bool Offboard_status;
    bool Armed_status;
    Telemetry::FlightMode FlightMode_status;
    Telemetry::Health System_status;

};
#endif