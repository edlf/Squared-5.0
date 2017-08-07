#ifndef UTILS_H
#define UTILS_H

#include <pebble.h>

inline uint8_t get_GColor8FromInt32(int32_t color) {
  //uint8_t a = 192;
  //uint8_t r = (((color >> 16) & 0xFF) >> 6) << 4;
  //uint8_t g = (((color >>  8) & 0xFF) >> 6) << 2;
  //uint8_t b = (((color >>  0) & 0xFF) >> 6) << 0;
  //return a+r+g+b;
  return 192 + ((((color >> 16) & 0xFF) >> 6) << 4)
   + ((((color >>  8) & 0xFF) >> 6) << 2)
   + ((((color >>  0) & 0xFF) >> 6) << 0);
}

#endif /* end of include guard:  */
