#ifndef DATA_POINT_H
#define DATA_POINT_H

#include <stdint.h>

typedef struct {
    uint64_t timestamp;
    uint16_t sensor_1;
    uint16_t sensor_2;
} DataPoint;

#endif // DATA_POINT_H