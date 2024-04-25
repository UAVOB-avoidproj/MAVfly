#include <mavsdk_simplify.hpp>

void Mavsdk_Init(int * rt){

    Mavsdk mavsdk{Mavsdk::Configuration{Mavsdk::ComponentType::CompanionComputer}};
    mavsdk_my = &mavsdk;

    // Serial connection
    ConnectionResult connection_result = mavsdk_my->add_any_connection(SERIAL);
    if (connection_result != ConnectionResult::Success) {
        std::cerr << "Serial:Connection failed: " << connection_result << '\n';
        *rt = -1;
        return;
    }
    std::cout << "Serial:Connected success!\n";

    // find first_autopilot and init Telemetry and Action
    auto system = mavsdk_my->first_autopilot(3.0);
    system_my = &system;
    if (!system) {
        std::cerr << "System: Time out!\n";
        *rt = -1;
        return;
    }
    auto telemetry = Telemetry{system.value()};
    telemetry_my = &telemetry;
    auto action = Action{system.value()};
    action_my = &action;
    std::cout << "System: Find successful! and Telemetry/Action.\n";

    *rt = 1;
    while(1) sleep_for(seconds(10));
}
void Offboard_Init(int *rt, int time){
    // Init Offboard mode
    while (mavsdk_my->systems().size() == 0) {
        sleep_for(seconds(1));
    }
    std::shared_ptr<System> system2 = mavsdk_my->systems()[0];
    Offboard offboard = Offboard{system2};
    offboard_my = &offboard;
    *rt = 1;

    while(1) sleep_for(seconds(10));
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

void Offboard_VBY(mavsdk::Offboard::VelocityBodyYawspeed VBYvalue){
    std::cout << "Offboard vbvForward……\n";
    while(1) {
        
        offboard_my->set_velocity_body(VBYvalue);
        sleep_for(seconds(1));
    }
    
}