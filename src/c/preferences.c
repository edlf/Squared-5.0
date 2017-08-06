#include "preferences.h"

void preferences_set_defaults(Preferences *preferences){
   preferences->large_mode = false;
   preferences->eu_date = true;
   preferences->quick_start = false;
   preferences->leading_zero = false;
   preferences->background_color = GColorBlackARGB8;
   preferences->number_base_color = GColorTiffanyBlueARGB8;
   preferences->number_variation = true;
   preferences->ornament_base_color = GColorPurpleARGB8;
   preferences->ornament_variation = true;
   preferences->invert = false;
   preferences->monochrome = true;
   preferences->center = false;
   preferences->btvibe = false;
   preferences->contrast = false;
   preferences->nightsaver = false;
   preferences->ns_start = 0;
   preferences->ns_stop = 6;
   preferences->backlight = false;
   preferences->weekday = false;
   preferences->bottomrow = 0;
   preferences->wristflick = 0;
   preferences->stepgoal = 10000;
   preferences->dynamicstepgoal = false;
   preferences->cheeky = true;
   preferences->use_presets = true;
   preferences->bg_preset = 0;
   preferences->number_preset = 1;
   preferences->ornament_preset = 2;
   preferences->battery_saver = false;
}
