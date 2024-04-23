cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(test)

find_package(MAVSDK REQUIRED)
if (MAVSDK_FOUND)
    message("Found")
else ()
    message("Not Found")
    return()
endif ()
set(MAVFLY_LIB_DIRS "$ENV{MAVFLY_LIB_DIRS}/../lib-old")
message("MAVFLY_LIB_DIRS: ${MAVFLY_LIB_DIRS}")
include_directories(
    ${MAVFLY_LIB_DIRS}/includes
#    ${MAVFLY_LIB_DIRS}
    )
link_directories(${MAVFLY_LIB_DIRS})

add_executable(test
        test.cpp
        ${MAVFLY_LIB_DIRS}/flymode.cpp
)


target_link_libraries(test
        MAVSDK::mavsdk
)

if (NOT MSVC)
    add_compile_options(test PRIVATE -Wall -Wextra)
else ()
    add_compile_options(test PRIVATE -WX -W2)
endif ()

