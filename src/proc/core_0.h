#ifndef CORE0_H
#define CORE0_H

#include <stdint.h>

#define ADC_MAX 4095.0f
#define ADC_VREF 3.3f
#define FIXED_RESISTOR 10000.0f

#define LDR_A 116000.0f
#define LDR_GAMMA 0.78f

void core0_loop();

float adc_to_voltage(uint16_t adc_value);
float adc_to_ldr_resistance(uint16_t adc_value);
float adc_to_lux(uint16_t adc);

#endif