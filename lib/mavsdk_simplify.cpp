#include <mavsdk_simplify.hpp>

bool Mavsdk_Init(){

    Mavsdk mavsdk{Mavsdk::Configuration{Mavsdk::ComponentType::CompanionComputer}};
    mavsdk_my = &mavsdk;

    // Serial connection
    ConnectionResult connection_result = mavsdk_my->add_any_connection(SERIAL);
    if (connection_result != ConnectionResult::Success) {
        std::cerr << "Serial:Connection failed: " << connection_result << '\n';
        return false;
    }
    std::cout << "Serial:Connected success!\n";

    // find first_autopilot and init Telemetry and Action
    auto system = mavsdk_my->first_autopilot(3.0);
    system_my = &system;
    if (!system) {
        std::cerr << "System: Time out!\n";
        return false;
    }
    auto telemetry = Telemetry{system.value()};
    telemetry_my = &telemetry;
    auto action = Action{system.value()};
    action_my = &action;
    std::cout << "System: Find successful! and Telemetry/Action.\n";

    Armed();

    return true;
}
bool Offboard_Init(){

    return true;
}

bool Armed(){
    std::cout << "Armed: Arming...\n";
    const Action::Result arm_result = action_my->arm();

    if (arm_result != Action::Result::Success) {
        std::cerr << "Armed: Arming failed: " << arm_result << '\n';
        return false;
    }
    std::cout << "Armed: Armed successful!\n";

    return true;
}
bool Disarmed(){
    std::cout << "Disarmed: Disarming...\n";
    const Action::Result disarm_result = action_my->disarm();

    if (disarm_result != Action::Result::Success) {
        std::cerr << "Disarmed: Disarming failed: " << disarm_result << '\n';
        return false;
    }
    std::cout << "Disarmed: Disarmed successful!\n";
    return true;
}