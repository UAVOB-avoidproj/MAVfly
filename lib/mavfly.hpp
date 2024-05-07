#ifndef __MAVFLY_HPP__
#define __MAVFLY_HPP__

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
#include <mavsdk/plugin_base.h>

#include <enumVelocityBodyYawspeed.h>

using namespace mavsdk;
using std::chrono::seconds;
using std::this_thread::sleep_for;

#define SERIAL "serial:///dev/serial/by-id/usb-ArduPilot_QioTekZealotH743_2D0040000D51303037363639-if00"

const auto interval_20hz = std::chrono::milliseconds(50); // 20HZ频率发送offboard信号(50ms)
static Mavsdk *mavsdk_my = nullptr;
static std::optional<std::shared_ptr<mavsdk::System> > *system_my = nullptr;
static Action *action_my = nullptr;
static Telemetry *telemetry_my = nullptr;
static Offboard *offboard_my = nullptr;
static mavsdk::Offboard::VelocityBodyYawspeed VBYvalue = vbyStop;

void Mavsdk_Init(int *);
void Offboard_Init(int *, int);
void Offboard_Start(int *);
void Offboard_Stop(int *);

void setOffboard_VBY(mavsdk::Offboard::VelocityBodyYawspeed);
void Action_takeoff(int *, int);
void Action_land(int *);
void Return_to_Launch(int *);

bool Armed();
bool Disarmed();

void cout_sth();


#endif