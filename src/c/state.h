#ifndef STATE_H
#define STATE_H

#include <pebble.h>
#include "constants.h"
#include "preferences.h"

typedef struct {
  GColor8 background_color;
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
