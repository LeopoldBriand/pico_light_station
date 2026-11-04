#include "core_0.h"
#include "../storage/ring_buffer.h"
#include <stdio.h>
#include "hardware/adc.h"

void core0_loop(RingBuffer *rb) {
    while (1) {
        DataPoint new_point;
        new_point.timestamp = time_us_64();
        adc_select_input(0);
        new_point.sensor_1 = adc_read();
        adc_select_input(1);
        new_point.sensor_2 = adc_read();

        ring_buffer_push(rb, new_point);
        printf("Core0 loop\n");
        sleep_ms(1000); 
    }
}