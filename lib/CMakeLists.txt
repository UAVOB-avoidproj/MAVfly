cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(libmavfly) # 修改项目名为库名

find_package(MAVSDK REQUIRED)

# 设置动态库输出路径及其他配置
set(MAVFLY_LIB_DIRS "/opt/dev/MAVfly/lib")
message("MAVFLY_LIB_DIRS: ${MAVFLY_LIB_DIRS}")

# 添加头文件目录
include_directories(
    ${MAVFLY_LIB_DIRS}/includes
)

# 添加链接目录（如果mavsdk库需要）
link_directories(${MAVFLY_LIB_DIRS}) 

# 创建动态库
add_library(mavfly SHARED # 修改为SHARED类型创建动态库
        ${MAVFLY_LIB_DIRS}/mavsdk_simplify.cpp
)

# 链接所需的库
target_link_libraries(mavfly
        MAVSDK::mavsdk
)

# 根据编译器设置警告级别
if (NOT MSVC)
    target_compile_options(mavfly PRIVATE -Wall -Wextra) # 更改为针对库的目标
else ()
    target_compile_options(mavfly PRIVATE -WX -W2) # 同样更改为针对库
endif ()

# 如果有其他特定于动态库的配置，如导出符号、版本控制等，可以在这里添加
