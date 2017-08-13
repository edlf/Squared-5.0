#ifndef RESOURCES_H
#define RESOURCES_H

#include <pebble.h>
#include "constants.h"

extern const char * locales[6];
extern const char * weekdays[6][7];

extern const uint8_t character_map[122];
extern const uint8_t characters[64][10];
extern const uint8_t progress_top_seq[19];
extern const uint8_t startDigit[18];
extern const uint8_t variation[100];
extern const uint8_t shadowtable[256];
extern const uint8_t alpha;

extern const int16_t slot_frame_x[CONST_NUM_SLOTS];
extern const int16_t slot_frame_y[CONST_NUM_SLOTS];
extern const int16_t slot_frame_w[CONST_NUM_SLOTS];
extern const int16_t slot_frame_h[CONST_NUM_SLOTS];

#endif /* end of include guard: RESOURCES_H */
