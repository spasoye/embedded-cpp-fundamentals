cmake_minimum_required(VERSION 3.20.0)

# Set devicetree overlay file
set(DTC_OVERLAY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/promicro_nrf52840.overlay)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(cpp_embedded_fundamentals)

# Enable C++ support
enable_language(CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable features not needed in embedded
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

# Your source files
target_sources(app PRIVATE 
     src/main.cpp
)

target_include_directories(app PRIVATE inc)
