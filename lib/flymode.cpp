#include <flymode.hpp>

FlyMode::FlyMode(
    std::optional<std::shared_ptr<System>> *systemT,
    Action *actionT,
    Telemetry *telemetryT,
    Offboard *offboardT
    ){

    system = systemT;
    action = actionT;
    telemetry = telemetryT;
    offboard = offboardT;

    Offboard_status = offboard->is_active();
    Armed_status = telemetry->armed();
    FlightMode_status = telemetry->flight_mode();
    System_status = telemetry->health();

    std::cout << "FlyMode: System status: " << System_status << '\n';
    std::cout << "FlyMode: Flight mode: " << FlightMode_status << '\n';
    std::cout << "FlyMode: Armed: " << Armed_status << '\n';
    std::cout << "FlyMode: Offboard: " << Offboard_status << '\n';

}
FlyMode::~FlyMode(){


    std::cout << "FlyMode: System status: " << System_status << '\n';
    std::cout << "FlyMode: Flight mode: " << FlightMode_status << '\n';
    std::cout << "FlyMode: Armed: " << Armed_status << '\n';
    std::cout << "FlyMode: Offboard: " << Offboard_status << '\n';

}

bool FlyMode::Armed(){
    std::cout << "Armed: Arming...\n";
    const Action::Result arm_result = action->arm();

    if (arm_result != Action::Result::Success) {
        std::cerr << "Armed: Arming failed: " << arm_result << '\n';
        return false;
    }
    std::cout << "Armed: Armed successful!\n";

    return true;
}
bool FlyMode::Disarmed(){
    std::cout << "Disarmed: Disarming...\n";
    const Action::Result disarm_result = action->disarm();

    if (disarm_result != Action::Result::Success) {
        std::cerr << "Disarmed: Disarming failed: " << disarm_result << '\n';
        return false;
    }
    std::cout << "Disarmed: Disarmed successful!\n";
    return true;
}
bool FlyMode::Offboard_init(){
    Offboard::Result offboard_result = offboard.start();
    if (offboard_result != Offboard::Result::Success) {
        std::cerr << "Offboard::start() failed: " << offboard_result << '\n';
    }
    std::cout << "Offboard started\n";
    return true;
}
bool FlyMode::Offboard_close(){
    offboard_result = offboard.stop();
    if (offboard_result != Offboard::Result::Success) {
        std::cerr << "Offboard::stop() failed: " << offboard_result << '\n';
    }
    std::cout << "Offboard closed\n";
    return true;
}
