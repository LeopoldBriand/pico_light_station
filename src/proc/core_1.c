#include "core_1.h"
#include "../storage/ring_buffer.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/httpd.h"

static RingBuffer *shared_rb;

void core1_loop(RingBuffer *rb) {
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