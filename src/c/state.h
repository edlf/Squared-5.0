#ifndef STATE_H
#define STATE_H

#include <pebble.h>
#include "constants.h"
#include "preferences.h"

typedef struct {
  GColor8 background_color;

  bool splashEnded;
  bool in_shake_mode;
  bool chargestate;
  bool allow_animate;
  bool initial_anim;

  uint16_t animation_time;
} State;

void state_init(State*);
void state_update(State*, Preferences*);

#endif
