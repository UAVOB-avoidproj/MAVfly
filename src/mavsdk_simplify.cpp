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
    std::cout << "System: Find successful! in Telemetry/Action.\n";

    *rt = 1;
    while(1) sleep_for(seconds(10));
}
void Offboard_Init(int *rt, int wait_time){
    // 初始化 offboard 变量
    for (;mavsdk_my->systems().size() == 0 && wait_time; wait_time--) {
        sleep_for(seconds(1));
    }
    if(!wait_time) {*rt = -1;return;}
    std::shared_ptr<System> system2 = mavsdk_my->systems()[0];
    Offboard offboard = Offboard{system2};
    offboard_my = &offboard;

    // 开启重复发送 offboard 信号的新线程
    // 结束 offboard 控制时需要结束 t 线程
    std::thread t([]() {
        VBYvalue = vbyStop;
        std::cout << "Offboard " << VBYvalue << "……\n";
        while(1) {
            offboard_my->set_velocity_body(VBYvalue);
            sleep_for(interval_20hz);
        }
    });
    t.detach();
    sleep_for(seconds(2));

    // 不再自动切入 offboard 控制，需用户自行手动调用 Offboard_Start 函数
    // int rt2 = 0;
    // std::thread t2(Offboard_Start, &rt2);
    // t2.detach();
    // while(1){
    //     if(rt2 == 0) std::cout << "offboard_start ……\n";
    //     if(rt2 == 1) break;
    //     if(rt2 == -1) {std::cerr << "offboard_start failed\n";return;}
    //     sleep_for(seconds(1));
    // }
    // std::cout << "offboard_start successful!\n";

    *rt = 1;

    while(1) sleep_for(seconds(10));
}
void Offboard_Start(int *rt){
    Offboard::Result result = offboard_my->start();
    if(result != Offboard::Result::Success){
        std::cerr << "offboard start-err: \""<< result << "\"\n";
        *rt = -1;
        return;
    }
    *rt = 1;
}
void Offboard_Stop(int *rt){
    Offboard::Result result = offboard_my->stop();
    if(result != Offboard::Result::Success){
        std::cerr << "offboard stop-err: \""<< result << "\"\n";
        *rt = -1;
        return;
    }
    *rt = 1;
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
void setOffboard_VBY(mavsdk::Offboard::VelocityBodyYawspeed VBYvalue_set){
    VBYvalue = VBYvalue_set;
    std::cout << "Offboard VBYvalue is set:" << VBYvalue << "……\n";
}
void Action_takeoff(int *rt, int attitude){
    action_my->set_takeoff_altitude(attitude);

    Action::Result result = action_my->takeoff();
    if(result != Action::Result::Success){
        std::cerr << "action takeoff-err: \""<< result << "\"\n";
        *rt = -1;
        return;
    }
    *rt = 1;
}
void Action_land(int *rt){
    Action::Result result = action_my->land();
    if(result != Action::Result::Success){
        std::cerr << "action land-err: \""<< result << "\"\n";
        *rt = -1;
        return;
    }
    *rt = 1;
}
void Return_to_Launch(int *rt){
    Action::Result result = action_my->return_to_launch();
    if(result != Action::Result::Success){
        std::cerr << "action return_to_launch-err: \""<< result << "\"\n";
        *rt = -1;
        return;
    }
    *rt = 1;
}
void cout_sth(){
    Telemetry::Heading head_rt = telemetry_my->heading();
    std::cout << "heading_deg: " << head_rt << std::endl;
}
void subscribe_Global_Position(Telemetry::PositionCallback &callback){
    // Telemetry::Position oldFlightMode=Telemetry::Position::Unknown;
    telemetry_my->subscribe_position(callback);
}