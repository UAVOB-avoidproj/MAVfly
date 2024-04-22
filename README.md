# MAVfly
## Function instructions
### 飞行控制插件初始化

1. Mavsdk对象
2. first_autopilot第一个自动飞行系统
3. Action和Telemetry插件
4. Offboard对象

### 特定飞行模式

1. 开启offboard模式
    1. 持续发送offboard信号（多线程）
2. 关闭offboard模式

### 封装特定的动作库（简单调用）

1. takeoff起飞
2. land降落
3. return_and_land返航
4. 以offboard模式各向方向飞行
    1. 前
    2. 后
    3. 左
    4. 右
    5. 上
    6. 下
    7. 左旋
    8. 右旋
    9. 悬停（定高、定点）
  
