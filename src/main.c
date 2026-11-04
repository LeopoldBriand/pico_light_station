#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "proc/core_0.h"
#include "proc/core_1.h"
#include "storage/ring_buffer.h"
#include "hardware/adc.h"

int main(void)
{
    stdio_init_all();

    if (cyw43_arch_init()) {
        return -1;
    }

    cyw43_arch_enable_sta_mode();

    printf("Connecting to WiFi...\n");

    if (cyw43_arch_wifi_connect_timeout_ms(
            WIFI_SSID,
            WIFI_PASSWORD,
            CYW43_AUTH_WPA2_AES_PSK,
            30000)) {
        printf("WiFi connection failed\n");
        return -1;
    }

    printf("Connected!\n");

    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);

    printf("================================\n");
    printf("      PICO LIGHT MONITOR\n");
    printf("================================\n");
    
    RingBuffer rb;

    ring_buffer_init(&rb);

    shared_rb = &rb;

    multicore_launch_core1(core1_entry);

    core0_loop(&rb);

    return 0;
}