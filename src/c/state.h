#ifndef STATE_H
#define STATE_H

#include <pebble.h>
#include "constants.h"
#include "preferences.h"

typedef struct {
  uint8_t num_slots;
  GColor8 background_color;

  uint8_t spacing_x;
  uint8_t spacing_y;

  uint8_t font_width_blocks;
  uint8_t font_height_blocks;

  uint8_t total_blocks;

  uint8_t font_width;
  uint8_t font_height;

  uint8_t tiles_x;
  uint8_t tiles_y;

  uint8_t origin_x;
  uint8_t origin_y;

  bool splashEnded;
  bool in_shake_mode;
  bool chargestate;
  bool contrastmode;
  bool allow_animate;
  bool initial_anim;

  uint16_t animation_time;

  #ifdef PBL_COLOR
  bool previous_contrastmode;
  #endif
} State;

void state_init(State*);
void state_update(State*, Preferences*);

#endif
