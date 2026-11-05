#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_api.h"

#include "lwip/apps/fs.h"
#include "../storage/ring_buffer.h"

#include <stdio.h>

static DataPoint points[BUFFER_SIZE];
static char json[4096];

int fs_open_custom(struct fs_file *file, const char *name)
{
    printf("Route %s called", name);

    if (strcmp(name, "/api/data") == 0) {

        size_t count = ring_buffer_get_all(shared_rb, points, BUFFER_SIZE);

        printf("Get %u points", count);

        if (points == NULL)
            return 0;

        size_t offset = 0;

        offset += snprintf(json + offset, sizeof(json) - offset, "[");

        for (size_t i = 0; i < count; i++) {
            offset += snprintf(
                json + offset,
                sizeof(json) - offset,
                "%s{\"timestamp\":%lu,\"sensor_1\":%u,\"sensor_2\":%u}",
                i ? "," : "",
                (unsigned long)points[i].timestamp,
                points[i].sensor_1,
                points[i].sensor_2
            );

            if (offset >= sizeof(json))
                break;
        }

        snprintf(json + offset, sizeof(json) - offset, "]");

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