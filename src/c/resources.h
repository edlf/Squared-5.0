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

#ifdef PBL_COLOR
#define NUMBER_OF_BG_PRESETS 15
#define NUMBER_OF_CHAR_PRESETS 20

extern const uint8_t background_color_presets[NUMBER_OF_BG_PRESETS];
extern const uint8_t character_base_color_presets[NUMBER_OF_CHAR_PRESETS];
extern const bool    character_variation_presets[NUMBER_OF_CHAR_PRESETS];
#endif

#endif /* end of include guard: RESOURCES_H */
