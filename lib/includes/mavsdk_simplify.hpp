#ifndef __MAVSDK_SIMPLIFY_HPP__
#define __MAVSDK_SIMPLIFY_HPP__

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


using namespace mavsdk;
using std::chrono::seconds;
using std::this_thread::sleep_for;

#define SERIAL "serial:///dev/serial/by-id/usb-ArduPilot_QioTekZealotH743_2D0040000D51303037363639-if00"

static Mavsdk *mavsdk_my;
static System *system_my;
static Action *action_my;
static Telemetry *telemetry_my;
static Offboard *offboard_my;

bool Mavsdk_Init();
bool Offboard_Init();

bool Armed();
bool Disarmed();


#endif