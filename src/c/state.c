#include "state.h"

void state_init(State *state) {
  state->splashEnded = false;
  state->in_shake_mode = false;
  state->chargestate = false;
  state->allow_animate = true;
  state->initial_anim = false;
  state->animation_time = 2000;
}

void state_update(State* state, Preferences* preferences) {
  state->background_color = (GColor8) { .argb = preferences->background_color };

  if (preferences->quick_start) {
    state->animation_time = 1500;
  } else {
    state->animation_time = 2000;
  }
}
