#ifndef RESOURCES_H
#define RESOURCES_H

#include <pebble.h>

extern const char * locales[6];
extern const char * weekdays[6][7];

extern const uint8_t character_map[122];
extern const uint8_t characters[64][10];
extern const uint8_t progress_top_seq[19];
extern const uint8_t startDigit[18];
extern const uint8_t variation[100];
extern const uint8_t shadowtable[256];
extern const uint8_t alpha;

extern const uint8_t background_color_presets[15];
extern const uint8_t character_base_color_presets[20];
extern const bool character_variation_presets[20];

#endif /* end of include guard: RESOURCES_H */
