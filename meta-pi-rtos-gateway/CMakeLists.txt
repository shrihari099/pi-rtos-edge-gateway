cmake_minimum_required(VERSION 3.10)

# Project definition
project(PiRTOS_Edge_Gateway C)

# Use C11 standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include directories
include_directories(inc)

# Source files
set(SOURCES
    src/gateway_main.c
    src/core1_sensor.c
    src/core2_cloud.c
    src/core3_ota.c
    src/core4_security.c
)

# Header files (for IDE organization)
set(HEADERS
    inc/gateway.h
)

# Build executable
add_executable(pi-rtos-gateway ${SOURCES} ${HEADERS})

# Link pthread for multi-threading
target_link_libraries(pi-rtos-gateway pthread)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Install executable
install(TARGETS pi-rtos-gateway DESTINATION bin)
