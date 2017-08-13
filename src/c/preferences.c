#include "preferences.h"

void preferences_set_defaults(Preferences *preferences){
   preferences->eu_date = true;
   preferences->leading_zero = false;
   preferences->background_color = GColorBlackARGB8;
   preferences->number_base_color = GColorTiffanyBlueARGB8;
   preferences->ornament_base_color = GColorPurpleARGB8;
   preferences->center = false;
   preferences->btvibe = false;
   preferences->nightsaver = false;
   preferences->ns_start = 0;
   preferences->ns_stop = 6;
   preferences->backlight = false;
   preferences->weekday = false;
   preferences->bottomrow = 0;
   preferences->wristflick = 0;
}

void preferences_load(DictionaryIterator *iter, Preferences *preferences) {
  Tuple *eu_date_t = dict_find(iter, KEY_EU_DATE);
  Tuple *leading_zero_t = dict_find(iter, KEY_LEADING_ZERO);
  Tuple *background_color_t = dict_find(iter, KEY_BACKGROUND_COLOR);
  Tuple *number_base_color_t = dict_find(iter, KEY_NUMBER_BASE_COLOR);
  Tuple *ornament_base_color_t = dict_find(iter, KEY_ORNAMENT_BASE_COLOR);
  Tuple *center_t = dict_find(iter, KEY_CENTER);
  Tuple *btvibe_t = dict_find(iter, KEY_BTVIBE);
  Tuple *nightsaver_t = dict_find(iter, KEY_NIGHTSAVER);
  Tuple *ns_start_t = dict_find(iter, KEY_NS_START);
  Tuple *ns_stop_t = dict_find(iter, KEY_NS_STOP);
  Tuple *backlight_t = dict_find(iter, KEY_BACKLIGHT);
  Tuple *weekday_t = dict_find(iter, KEY_WEEKDAY);
  Tuple *bottomrow_t = dict_find(iter, KEY_BOTTOMROW);
  Tuple *wristflick_t = dict_find(iter, KEY_WRISTFLICK);

  if (eu_date_t) {             preferences->eu_date =                eu_date_t->value->int8; }
  if (leading_zero_t) {        preferences->leading_zero =           leading_zero_t->value->int8; }
  if (background_color_t) {    preferences->background_color =       get_GColor8FromInt32(background_color_t->value->int32); }
  if (number_base_color_t) {   preferences->number_base_color =      get_GColor8FromInt32(number_base_color_t->value->int32); }
  if (ornament_base_color_t) { preferences->ornament_base_color =    get_GColor8FromInt32(ornament_base_color_t->value->int32); }
  if (center_t) {              preferences->center =                 center_t->value->int8; }
  if (btvibe_t) {              preferences->btvibe =                 btvibe_t->value->int8; }
  if (nightsaver_t) {          preferences->nightsaver =             nightsaver_t->value->int8; }
  if (ns_start_t) {            preferences->ns_start =               atoi(ns_start_t->value->cstring); }
  if (ns_stop_t) {             preferences->ns_stop =                atoi(ns_stop_t->value->cstring); }
  if (backlight_t) {           preferences->backlight =              backlight_t->value->int8; }
  if (weekday_t) {             preferences->weekday =                weekday_t->value->int8; }
  if (bottomrow_t) {           preferences->bottomrow =              atoi(bottomrow_t->value->cstring); }
  if (wristflick_t) {          preferences->wristflick =             atoi(wristflick_t->value->cstring); }
}
