#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#define BUFFER_SIZE 16 
#define BUFFER_MASK (BUFFER_SIZE - 1)

#include <stdio.h>
#include "pico/mutex.h"
#include "data_point.h"

typedef struct {
    DataPoint data[BUFFER_SIZE];
    size_t head;
    size_t tail;
    size_t count;
    mutex_t lock; 
} RingBuffer;

void ring_buffer_init(RingBuffer *buffer);
void ring_buffer_push(RingBuffer *buffer, DataPoint val);
DataPoint* ring_buffer_get_all(RingBuffer *buffer);

#endif // RING_BUFFER_H