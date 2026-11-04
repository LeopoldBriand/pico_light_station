#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_api.h"

#include "lwip/apps/fs.h"
#include "../storage/ring_buffer.h"
#include "../proc/core_1.h"

extern RingBuffer *shared_rb;

static char json[4096];

int fs_open_custom(struct fs_file *file, const char *name)
{
    if (strcmp(name, "/api/data") == 0) {

        DataPoint *points = ring_buffer_get_all(shared_rb);

        if (points == NULL)
            return 0;

        size_t count = shared_rb->count;
        size_t offset = 0;

        offset += snprintf(json + offset, sizeof(json) - offset, "[");

        for (size_t i = 0; i < count; i++) {
            offset += snprintf(
                json + offset,
                sizeof(json) - offset,
                "%s{\"timestamp\":%lu,\"sensor_1\":%.2f,\"sensor_2\":%.2f}",
                i ? "," : "",
                (unsigned long)points[i].timestamp,
                points[i].sensor_1,
                points[i].sensor_2
            );

            if (offset >= sizeof(json))
                break;
        }

        snprintf(json + offset, sizeof(json) - offset, "]");

        free(points);
    } else if (strcmp(name, "/api/status") == 0) {
        snprintf(json, sizeof(json),
                 "{\"status\":\"online\"}");
    }
    else {
        return 0;
    }

    file->data = json;
    file->len = strlen(json);
    file->index = file->len;
    file->flags = 0;

    return 1;
}

void fs_close_custom(struct fs_file *file){}