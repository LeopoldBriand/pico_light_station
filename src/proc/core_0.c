#include "core_0.h"
#include "../storage/ring_buffer.h"
#include "hardware/adc.h"

void core0_loop() {
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);

    while (1) {
        DataPoint new_point;
        new_point.timestamp = time_us_64();
        adc_select_input(0);
        new_point.sensor_1 = adc_read();
        adc_select_input(1);
        new_point.sensor_2 = adc_read();

        ring_buffer_push(shared_rb, new_point);
        sleep_ms(60000); 
    }
}