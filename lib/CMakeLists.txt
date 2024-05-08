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

# 创建动态库之前，明确指定输出目录为绝对路径
set(LIBRARY_OUTPUT_PATH /opt/dev/MAVfly/lib)
message("Output directory set to: ${LIBRARY_OUTPUT_PATH}")

# 创建动态库
add_library(mavfly SHARED # 修改为SHARED类型创建动态库
        ${MAVFLY_LIB_DIRS}/mavsdk_simplify.cpp
)

# 注意：由于前面设置了LIBRARY_OUTPUT_PATH，此处的set_target_properties可能不再必要
# 但根据具体CMake版本和配置，有时仍需显式设置，确保兼容性
set_target_properties(mavfly PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${LIBRARY_OUTPUT_PATH}"
)
message("LIBRARY_OUTPUT_PATH: ${LIBRARY_OUTPUT_PATH}")

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
