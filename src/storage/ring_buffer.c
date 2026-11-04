#include "ring_buffer.h"
#include <stdlib.h>
#include <stdio.h>

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
        printf("Buffer count: %d\n", buffer->count);
    }

    buffer->data[buffer->head] = val;

    printf("Timestamp: %llu | Sensor 1: %u | Sensor 2: %u\n",
           (unsigned long long)val.timestamp,
           (unsigned int)val.sensor_1,
           (unsigned int)val.sensor_2);
    
    buffer->head = (buffer->head + 1) & BUFFER_MASK;

    mutex_exit(&buffer->lock);
}

DataPoint* ring_buffer_get_all(RingBuffer *buffer) {
    mutex_enter_blocking(&buffer->lock);

    size_t items_to_copy = buffer->count;
    size_t current_tail = buffer->tail;

    DataPoint* out_array = (DataPoint*)malloc(items_to_copy * sizeof(DataPoint));

    for (size_t i = 0; i < items_to_copy; i++) {
        // Copie des éléments dans l'ordre chronologique (du plus ancien au plus récent)
        out_array[i] = buffer->data[(current_tail + i) & BUFFER_MASK];
    }

    mutex_exit(&buffer->lock);
    
    return out_array;
}