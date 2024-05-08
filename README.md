## 飞行控制插件初始化

1. 初始化Mavsdk对象
    - 参数说明
        - int *：携带返回值的指针。值为0表示正在运行，1表示运行成功，-1表示运行失败。

```C++
// 声明
void Mavsdk_Init(int *);

// 使用示例
int rt = 0;
std::thread thread1(Mavsdk_Init, &rt);
thread1.detach();
while(1){
    if(rt == 0) std::cout << "mavsdk_init ……\n";
    if(rt == 1) break;
    if(rt == -1) {std::cout << "mavsdk_init failed\n";return 0;}
    sleep_for(seconds(1));
}
std::cout << "mavsdk_init success" << std::endl;
```
2. 初始化Offboard对象
    - 参数说明
        - int *：携带返回值的指针。值为0表示正在运行，1表示运行成功，-1表示运行失败。
        - int：超时时间（单位秒），无默认值不可为空。

```C++
// 声明
void Offboard_Init(int *, int);

// 使用示例
#define wait_time 3
int rt = 0;
std::thread thread2(Offboard_Init, &rt, wait_time);
thread2.detach();
while(1){
    if(rt == 0) std::cout << "offboard_init ……\n";
    if(rt == 1) break;
    if(rt == -1) {std::cerr << "offboard_init failed\n";return 0;}
    sleep_for(seconds(1));
}
std::cout << "offboard_init successful!\n";
```

## 特定飞行模式

1. Armed解锁
    - 参数说明
        - 无参数

```C++
// 声明
bool Armed();

// 使用示例
if(!Armed()){return 0;}
```
2. Disarmed上锁
    - 参数说明
        - 无参数

```C++
// 声明
bool Disarmed();

// 使用示例
if(!Disarmed()){return 0;}
```
3. 开启offboard模式
    - 参数说明
        - int *：携带返回值的指针。值为0表示正在运行，1表示运行成功，-1表示运行失败。

```C++
// 声明
void Offboard_Start(int *);

// 使用示例
int rt = 0;
std::thread t2(Offboard_Start, &rt);
t2.detach();
while(1){
    if(rt == 0) std::cout << "offboard_start ……\n";
    if(rt == 1) break;
    if(rt == -1) {std::cerr << "offboard_start failed\n";return;}
    sleep_for(seconds(1));
}
std::cout << "offboard_start successful!\n";

```
4. 关闭offboard模式
    - 参数说明
        - int *：携带返回值的指针。值为0表示正在运行，1表示运行成功，-1表示运行失败。

```C++
// 声明
void Offboard_Stop(int *);

// 使用示例
int rt = 0;
std::thread thread3(Offboard_Stop, &rt);
thread3.detach();
while(1){
    if(rt == 0) std::cout << "offboard_stop ……\n";
    if(rt == 1) break;
    if(rt == -1) {std::cerr << "offboard_stop failed\n";return 0;}
    sleep_for(seconds(1));
}
std::cout << "offboard_stop successful!\n";
```

## 封装特定的动作库（简单调用）

1. Action_takeoff起飞
    - 参数说明
        - int *：携带返回值的指针。值为0表示正在运行，1表示运行成功，-1表示运行失败。
        - int：起飞后的悬空高度

```C++
// 声明
void Action_takeoff(int *, int);

// 使用示例
int rt = 0;
std::thread thread_takeoff(Action_takeoff, &rt, 3);
thread_takeoff.detach();
while(1){
    if(rt == 0) std::cout << "Action_takeoff ……\n";
    if(rt == 1) break;
    if(rt == -1) {std::cerr << "Action_takeoff failed\n";return 0;}
    sleep_for(seconds(1));
}
std::cout << "Action_takeoff successful!\n";
```
2. Action_land降落
    - 参数说明
        - int *：携带返回值的指针。值为0表示正在运行，1表示运行成功，-1表示运行失败。

```C++
// 声明
void Action_land(int *);

// 使用示例
int rt = 0;
std::thread thread_land(Action_land, &rt);
thread_land.detach();
while(1){
    if(rt == 0) std::cout << "Action_land ……\n";
    if(rt == 1) break;
    if(rt == -1) {std::cerr << "Action_land failed\n";return 0;}
    sleep_for(seconds(1));
}
std::cout << "Action_land successful!\n";
```
3. Return_to_Launch返航
    - 参数说明
        - int *：携带返回值的指针。值为0表示正在运行，1表示运行成功，-1表示运行失败。

```C++
// 声明
void Return_to_Launch(int *);

// 使用示例
int rt = 0;
std::thread thread_rtl(Return_to_Launch, &rt);
thread_rtl.detach();
while(1){
    if(rt == 0) std::cout << "mavsdk_rtl ……\n";
    if(rt == 1) break;
    if(rt == -1) {std::cout << "mavsdk_rtl failed\n";return 0;}
    sleep_for(seconds(1));
}
std::cout << "mavsdk_rtl success" << std::endl;
```
4. setOffboard_VBY控制飞行方向
    - 参数说明
        - mavsdk::Offboard::VelocityBodyYawspeed：头文件enumVelocityBodyYawspeed.h中定义的常量值，分别有：
            - vbyForward 机身前斜
            - vbyBackward机身后斜
            - vbyLeft机身左斜
            - vbyRight机身右斜
            - vbyUp机身上浮
            - vbyDown机身下降
            - vbyYawLeft机身左旋
            - vbyYawRight机身右旋
            - vbyStop原地悬浮

```C++
// 声明
void setOffboard_VBY(mavsdk::Offboard::VelocityBodyYawspeed);

// 使用示例
setOffboard_VBY(vbyForward);// 设置 offboard 飞行姿态为“向前”
```

