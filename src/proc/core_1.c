#include "core_1.h"
#include "../storage/ring_buffer.h"
#include <stdio.h>

static RingBuffer *shared_rb;

void core1_loop(RingBuffer *rb) {
    while (1) {
        printf("Core1 loop\n");
        sleep_ms(1500); 
    }
}

void core1_entry(void)
{
    core1_loop(shared_rb);
}