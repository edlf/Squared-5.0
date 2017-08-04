#ifndef PREFERENCES_H
#define PREFERENCES_H

#define PREFERENCES_KEY 0

typedef struct {
  bool large_mode;
  bool eu_date;
  bool quick_start;
  bool leading_zero;
  uint8_t background_color;
  uint8_t number_base_color;
  bool number_variation;
  uint8_t ornament_base_color;
  bool ornament_variation;
  bool invert;
  bool monochrome;
  bool center;
  bool btvibe;
  bool contrast;
  bool nightsaver;
  uint8_t ns_start;
  uint8_t ns_stop;
  bool backlight;
  bool weekday;
  uint8_t bottomrow;
  uint8_t wristflick;
  uint16_t stepgoal;
  bool dynamicstepgoal;
  bool cheeky;
} Preferences;

enum {
  KEY_LARGE_MODE,
  KEY_EU_DATE,
  KEY_QUICK_START,
  KEY_LEADING_ZERO,
  KEY_BACKGROUND_COLOR,
  KEY_NUMBER_BASE_COLOR,
  KEY_NUMBER_VARIATION,
  KEY_ORNAMENT_BASE_COLOR,
  KEY_ORNAMENT_VARIATION,
  KEY_INVERT,
  KEY_MONOCHROME,
  KEY_CENTER,
  KEY_BTVIBE,
  KEY_CONTRAST,
  KEY_NIGHTSAVER,
  KEY_NS_START,
  KEY_NS_STOP,
  KEY_BACKLIGHT,
  KEY_WEEKDAY,
  KEY_BOTTOMROW,
  KEY_WRISTFLICK,
  KEY_STEPGOAL,
  KEY_CHEEKY,
  KEY_DYNAMICSTEPGOAL,
};

#endif /* end of include guard: PREFERENCES_H */
