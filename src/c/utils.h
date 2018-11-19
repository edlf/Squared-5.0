#ifndef UTILS_H
#define UTILS_H

#include <pebble.h>

inline uint8_t get_GColor8FromInt32(int32_t color) {
    return 192 + ((((color >> 16) & 0xFF) >> 6) << 4)
               + ((((color >>  8) & 0xFF) >> 6) << 2)
               + ((((color >>  0) & 0xFF) >> 6) << 0);
}

#endif /* end of include guard:  */
