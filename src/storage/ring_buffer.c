#include "ring_buffer.h"
#include <stdlib.h>
#include <stdio.h>

RingBuffer *shared_rb = NULL;

void ring_buffer_init(RingBuffer *buffer) {
    buffer->head = 0;
    buffer->tail = 0;
    buffer->count = 0;
    mutex_init(&buffer->lock); 
}

void ring_buffer_push(RingBuffer *buffer, DataPoint val) {
    mutex_enter_blocking(&buffer->lock);

    if (buffer->count == BUFFER_SIZE) {
        buffer->tail = (buffer->tail + 1) & BUFFER_MASK;
    } else {
        buffer->count++;
    }

    buffer->data[buffer->head] = val;

    buffer->head = (buffer->head + 1) & BUFFER_MASK;

    mutex_exit(&buffer->lock);

    printf("Timestamp: %llu | Sensor 1: %u | Sensor 2: %u\n",
           (unsigned long long)val.timestamp,
           (unsigned int)val.sensor_1,
           (unsigned int)val.sensor_2);
    
}

size_t ring_buffer_get_all(
    RingBuffer *buffer,
    DataPoint *out_array,
    size_t max_items
) {
    mutex_enter_blocking(&buffer->lock);

    size_t count = buffer->count;

    if (count > max_items) {
        count = max_items;
    }

    for (size_t i = 0; i < count; i++) {
        out_array[i] =
            buffer->data[(buffer->tail + i) & BUFFER_MASK];
    }

    mutex_exit(&buffer->lock);

    return count;
}