#include "core_1.h"
#include "../storage/ring_buffer.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/httpd.h"

void core1_loop() {
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
    httpd_init();
    while (1) {
        cyw43_arch_poll();
        sleep_ms(1);
    }
}

void core1_entry(void)
{
    core1_loop(shared_rb);
}