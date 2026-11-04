cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")
set(PICO_BOARD pico2_w)

include(pico_sdk_import.cmake)

project(pico_light_station C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(pico_light_station
    src/main.c
)

target_link_libraries(pico_light_station
    pico_stdlib
)

pico_enable_stdio_usb(pico_light_station 1)
pico_enable_stdio_uart(pico_light_station 0)

pico_add_extra_outputs(pico_light_station)