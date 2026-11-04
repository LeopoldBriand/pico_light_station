cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")
set(PICO_BOARD pico2_w)

include(pico_sdk_import.cmake)

project(pico_light_station C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(pico_light_station
    src/main.c
    src/proc/core_0.c
    src/proc/core_1.c
    src/storage/ring_buffer.c
    src/api/http_api.c
)

target_include_directories(pico_light_station PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(pico_light_station
    pico_stdlib
    pico_multicore
    hardware_adc
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
    pico_httpd_content
)

file(STRINGS "${CMAKE_CURRENT_LIST_DIR}/.env" ENV_VARS)

foreach(VAR ${ENV_VARS})
    if(VAR MATCHES "^([^#][^=]*)=(.*)$")
        set(${CMAKE_MATCH_1} "${CMAKE_MATCH_2}")
    endif()
endforeach()

if(NOT DEFINED WIFI_SSID OR NOT DEFINED WIFI_PASSWORD)
    message(FATAL_ERROR "WiFi credentials missing from .env")
endif()

target_compile_definitions(pico_light_station PRIVATE
    WIFI_SSID="${WIFI_SSID}"
    WIFI_PASSWORD="${WIFI_PASSWORD}"
)

pico_add_library(pico_httpd_content NOFLAG)
pico_set_lwip_httpd_content(pico_httpd_content INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/html/index.html)

pico_enable_stdio_usb(pico_light_station 1)
pico_enable_stdio_uart(pico_light_station 0)

pico_add_extra_outputs(pico_light_station)

add_custom_target(flash
    COMMAND sudo picotool load -f -x ${CMAKE_BINARY_DIR}/pico_light_station.uf2
    DEPENDS pico_light_station
    COMMENT "Building and flashing Pico 2 W"
)