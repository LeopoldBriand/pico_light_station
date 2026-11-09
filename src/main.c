#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "proc/core_0.h"
#include "proc/core_1.h"
#include "storage/ring_buffer.h"

int main(void)
{
    stdio_init_all();

    printf("================================\n");
    printf("      PICO LIGHT MONITOR\n");
    printf("================================\n");
    
    RingBuffer rb;

    ring_buffer_init(&rb);

    shared_rb = &rb;

    multicore_launch_core1(core1_entry);

    core0_loop();

    return 0;
}