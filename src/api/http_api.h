#ifndef HTTP_API_H
#define HTTP_API_H

#include "lwip/apps/fs.h"

int fs_open_custom(struct fs_file *file, const char *name);
void fs_close_custom(struct fs_file *file);

#endif