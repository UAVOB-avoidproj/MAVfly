cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(coordinateFly)

find_package(MAVSDK REQUIRED)
if (MAVSDK_FOUND)
    message("Found")
else ()
    message("Not Found")
    return()
endif ()
add_executable(coordinateFly
        coordinateValue.h
        enumVelocityBodyYawspeed.h
        coordinateFly.cpp
)


target_link_libraries(coordinateFly
        MAVSDK::mavsdk
)

if (NOT MSVC)
    add_compile_options(takeoff_and_land PRIVATE -Wall -Wextra)
else ()
    add_compile_options(takeoff_and_land PRIVATE -WX -W2)
endif ()

