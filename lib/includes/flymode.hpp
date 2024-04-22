#ifndef __FLYMODE_HPP__
#define __FLYMODE_HPP__

#include <iostream>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/offboard/offboard.h>

using namespace mavsdk;

class FlyMode {
public:
    FlyMode(std::optional<std::shared_ptr<System>> *, Action *, Telemetry *, Offboard *);
    ~FlyMode();

    bool Armed();
    bool Disarmed();
    bool Offboard_init();
    bool Offboard_close();

private:
    std::optional<std::shared_ptr<System>> *system;
    Action *action;
    Telemetry *telemetry;
    Offboard *offboard;

    bool Offboard_status;
    bool Armed_status;
    Telemetry::FlightMode FlightMode_status;
    Telemetry::Health System_status;

};
#endif