cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(test)

# 设置项目并指明链接库的具体路径
set(MAVFLY_LIB_PATH "/opt/dev/MAVfly/lib/libmavfly.so")

# 检查库文件是否存在
if(NOT EXISTS ${MAVFLY_LIB_PATH})
    message(FATAL_ERROR "libmavfly.so not found at ${MAVFLY_LIB_PATH}")
endif()

# 添加可执行文件及其源文件
add_executable(test
        test.cpp
)

# 链接到特定路径的动态库
target_link_libraries(test
        PRIVATE
        ${MAVFLY_LIB_PATH}
)

# 根据编译器设定警告选项
if (NOT MSVC)
    target_compile_options(test PRIVATE -Wall -Wextra)
else()
    target_compile_options(test PRIVATE /WX /W2)
endif()

# 如果需要包含头文件，添加包含目录（假设头文件也在类似路径下）
include_directories(/opt/dev/MAVfly/lib/includes)
include_directories(/opt/dev/MAVfly/lib/includes/mavsdk)
