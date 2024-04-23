#include <flymode.hpp>

FlyMode::FlyMode(
    Mavsdk *mavsdtT,
    std::optional<std::shared_ptr<System>> *systemT,
    Action *actionT,
    Telemetry *telemetryT
    ){

    // const Action::Result arm_result = actionT->arm();
    // if (arm_result != Action::Result::Success) {
    //     std::cerr << "Armed: Arming failed: " << arm_result << '\n';
    // }

    mavsdk_ptr = mavsdtT;
    system_ptr = systemT;
    action_ptr = actionT;
    telemetry_ptr = telemetryT;
    // offboard_ptr = offboardT;

    std::cout << 321 << std::endl;
    std::cout << mavsdk_ptr << std::endl;
    std::cout << system_ptr << std::endl;
    std::cout << action_ptr << std::endl;
    std::cout << telemetry_ptr << std::endl;


    const Action::Result arm_result = action_ptr->set_takeoff_altitude(3.0);
    if (arm_result != Action::Result::Success) {
        std::cerr << "Armed: Takeoff altitude set failed:" << arm_result << '\n';
    }
    std::cout << "Armed: Takeoff altitude set successful!:" << arm_result << '\n';
    // const Action::Result arm_result = action_ptr->arm();
    // if (arm_result != Action::Result::Success) {
    //     std::cerr << "Armed: Arming failed: " << arm_result << '\n';
    // }

    // Offboard_status = offboard_ptr->is_active();
    Armed_status = telemetry_ptr->armed();
    FlightMode_status = telemetry_ptr->flight_mode();
    System_status = telemetry_ptr->health();

    // std::cout << "action_ptr: " << action_ptr <<std::endl;
    // std::cout << "telemetry_ptr: " << telemetry_ptr <<std::endl;

    std::cout << "FlyMode: System status: " << System_status << '\n';
    std::cout << "FlyMode: Flight mode: " << FlightMode_status << '\n';
    std::cout << "FlyMode: Armed: " << Armed_status << '\n';
    // std::cout << "FlyMode: Offboard: " << Offboard_status << '\n';

}
FlyMode::~FlyMode(){


    // std::cout << "FlyMode: System status: " << System_status << '\n';
    // std::cout << "FlyMode: Flight mode: " << FlightMode_status << '\n';
    // std::cout << "FlyMode: Armed: " << Armed_status << '\n';
    // std::cout << "FlyMode: Offboard: " << Offboard_status << '\n';
    std::cout << "Program over!"<<'\n';

}

bool FlyMode::Armed(){
    // std::cout << telemetry_ptr->in_air() <<std::endl;

    // const Action::Result arm_result2 = action_ptr->set_takeoff_altitude(3.0);
    // if (arm_result2 != Action::Result::Success) {
    //     std::cerr << "Armed: Takeoff altitude set failed:" << arm_result2 << '\n';
    // }
    // std::cout << "Armed: Takeoff altitude set successful!:" << arm_result2 << '\n';


    std::cout << "Armed: Arming...\n";
    std::cout << action_ptr << std::endl;
    const Action::Result arm_result = action_ptr->arm();

    if (arm_result != Action::Result::Success) {
        std::cerr << "Armed: Arming failed: " << arm_result << '\n';
        return false;
    }
    std::cout << "Armed: Armed successful!\n";

    return true;
}
bool FlyMode::Disarmed(){
    std::cout << "Disarmed: Disarming...\n";
    const Action::Result disarm_result = action_ptr->disarm();

    if (disarm_result != Action::Result::Success) {
        std::cerr << "Disarmed: Disarming failed: " << disarm_result << '\n';
        return false;
    }
    std::cout << "Disarmed: Disarmed successful!\n";
    return true;
}
bool FlyMode::Offboard_init(){
    // Init Offboard mode
    while (mavsdk_ptr->systems().size() == 0) {
        sleep_for(seconds(1));
    }
    std::shared_ptr<System> system_tmp = mavsdk_ptr->systems()[0];
    Offboard offboard_tmp = Offboard{system_tmp};
    offboard_ptr = &offboard_tmp;
    std::cout << "Offboard: Init successful!\n";

    Offboard::Result offboard_result = offboard_ptr->start();
    if (offboard_result != Offboard::Result::Success) {
        std::cerr << "Offboard::start() failed: " << offboard_result << '\n';
    }
    std::cout << "Offboard started\n";
    return true;
}
bool FlyMode::Offboard_close(){
    Offboard::Result offboard_result = offboard_ptr->stop();
    if (offboard_result != Offboard::Result::Success) {
        std::cerr << "Offboard::stop() failed: " << offboard_result << '\n';
    }
    std::cout << "Offboard closed\n";
    return true;
}
// bool FlyMode::Offboard_Forward(){
//     std::cout << "Offboard vbvForward……\n";
//     offboard->set_velocity_body(vbyForward);
// }