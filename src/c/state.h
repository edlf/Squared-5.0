#ifndef STATE_H
#define STATE_H

typedef struct {
  bool splashEnded;
  bool in_shake_mode;
  bool chargestate;
  bool contrastmode;
  bool allow_animate;
  bool initial_anim;

  uint8_t battprogress;
  uint16_t animation_time;

  #ifdef PBL_COLOR
  bool previous_contrastmode;
  #endif

  #ifdef PBL_HEALTH
  uint16_t stepgoal;
  uint16_t stepprogress;
  uint8_t heartrate;
  #endif
} State;

#endif
