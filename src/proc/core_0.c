#include "core_0.h"
#include "../storage/ring_buffer.h"
#include "hardware/adc.h"
#include <math.h>

void core0_loop() {
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);

    while (1) {
        DataPoint new_point;
        new_point.timestamp = time_us_64();
        adc_select_input(0);
        new_point.sensor_1 = adc_to_lux(adc_read());
        adc_select_input(1);
        new_point.sensor_2 = adc_to_lux(adc_read());

        ring_buffer_push(shared_rb, new_point);
        sleep_ms(60000); 
    }
}

float adc_to_voltage(uint16_t adc_value){
    return ((float)adc_value / ADC_MAX) * ADC_VREF;
}

float adc_to_ldr_resistance(uint16_t adc_value){
    float voltage = adc_to_voltage(adc_value);

    // Avoid division by zero
    if (voltage <= 0.001f)
        return INFINITY;

    // Avoid invalid readings at the upper rail
    if (voltage >= ADC_VREF)
        return 0.0f;

    return FIXED_RESISTOR * (ADC_VREF / voltage - 1.0f);
}


float adc_to_lux(uint16_t adc)
{
    float resistance = adc_to_ldr_resistance(adc);

    if (!isfinite(resistance) || resistance <= 0.0f)
        return 0.0f;

    return powf(LDR_A / resistance,
                1.0f / LDR_GAMMA);
}