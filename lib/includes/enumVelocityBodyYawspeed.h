#ifndef __ENUMVELOCITYBODYYAWSPEED_H__
#define __ENUMVELOCITYBODYYAWSPEED_H__

#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugin_base.h>

// Define an enumeration for the different directions and speeds for the drone to move in.


mavsdk::Offboard::VelocityBodyYawspeed vbyForward = {0.5f, 0.f, 0.f, 0.f};
mavsdk::Offboard::VelocityBodyYawspeed vbyBackward = {-0.5f, 0.f, 0.f, 0.f};

mavsdk::Offboard::VelocityBodyYawspeed vbyLeft = {0.f, -0.5f, 0.f, 0.f};
mavsdk::Offboard::VelocityBodyYawspeed vbyRight = {0.f, 0.5f, 0.f, 0.f};

mavsdk::Offboard::VelocityBodyYawspeed vbyUp = {0.f, 0.f, 0.5f, 0.f};
mavsdk::Offboard::VelocityBodyYawspeed vbyDown = {0.f, 0.f, -0.5f, 0.f};

mavsdk::Offboard::VelocityBodyYawspeed vbyYawLeft = {0.f, 0.f, 0.f, -0.5f};
mavsdk::Offboard::VelocityBodyYawspeed vbyYawRight = {0.f, 0.f, 0.f, 0.5f};
mavsdk::Offboard::VelocityBodyYawspeed vbyStop = {0.f, 0.f, 0.f, 0.f};


#endif