#ifndef CORE1_H
#define CORE1_H

#include "../storage/ring_buffer.h"

static RingBuffer *shared_rb;
void core1_loop(RingBuffer *rb);
void core1_entry(void);

#endif