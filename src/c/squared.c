/*
 * Original source code by lastfuture
 * SDK 2.0beta4 port by Jnm
 * SDK 3.0 port and colorizing by hexahedria
 * adaptations for Chalk and Aplite as well as continued development since SDK 3.8.2 by lastfuture
 * fix for SDK 4.3 by edlf
 */

#include <pebble.h>
#include "utils.h"
#include "preferences.h"
#include "date.h"
#include "resources.h"
#include "digit_slot.h"
#include "state.h"

// #define DEBUG

Window *window;
Preferences prefs;
Date curDate;

digitSlot slot[NUM_SLOTS];
static char weekday_buffer[2];
AnimationImplementation animImpl;
Animation *anim;
static State state;

static void handle_bluetooth(bool connected) {
  if (!quiet_time_is_active() && prefs.btvibe && !connected) {
    static const uint32_t segments[] = { 200, 200, 50, 150, 200 };

    VibePattern pat = {
    	.durations = segments,
    	.num_segments = ARRAY_LENGTH(segments),
    };

    vibes_enqueue_custom_pattern(pat);
  }
}

static GRect slotFrame(int8_t i) {
	int16_t x, y, w, h;

	if (i < 4) { // main digits
		w = state.font_width;
		h = state.font_height;

		if (i % 2) {
			x = state.origin_x + state.font_width + state.spacing_x; // i = 1 or 3
		} else {
			x = state.origin_x; // i = 0 or 2
		}

		if (i < 2) {
			y = state.origin_y;
		} else {
			y = state.origin_y + state.font_height + state.spacing_y;
		}

	} else if (i < 8) { // date digits
		w = state.font_width/2;
		h = state.font_height/2;
		x = state.origin_x + (state.font_width + state.spacing_x) * (i - 4) / 2;
		y = state.origin_y + (state.font_height + state.spacing_y) * 2;

	} else if (i < 10) { // top filler for round
    w = state.font_width;
		h = state.font_height;

    if (i % 2) {
			x = state.origin_x + state.font_width + state.spacing_x; // i = 1 or 3
		} else {
			x = state.origin_x; // i = 0 or 2
		}

    y = (int8_t) (state.origin_y - state.font_height - state.spacing_y);

  } else if (i < 14) { // side filler for round
    w = state.font_width;
		h = state.font_height;

    if (i % 2) {
			x = state.origin_x + state.font_width + state.spacing_x + state.font_width + state.spacing_x;
		} else {
			x = (int8_t) (state.origin_x - state.font_width - state.spacing_x);
		}

		if (i < 12) {
			y = state.origin_y;
		} else {
			y = state.origin_y + state.font_height + state.spacing_y;
		}

  } else if (i < 16) { // botom filler for round
		w = state.font_width/2;
		h = state.font_height/2;
    x = state.origin_x + (state.font_width + state.spacing_x) * (i - 13) / 2; // 13 = 14-1 (skipping invisible slot outside circle)
		y = state.origin_y + (state.font_height + state.spacing_y) * 2 + h + (h/6);

  } else { // bottom side filler for round
		w = state.font_width/2;
		h = state.font_height/2;

    if (i % 2) {
      x = state.origin_x + state.font_width + state.spacing_x + state.font_width + state.spacing_x;
    } else {
      x = state.origin_x - w - state.spacing_x/2; // todo: find correct value
    }

		y = state.origin_y + (state.font_height + state.spacing_y) * 2;
  }

	return GRect(x, y, w, h);
}

static uint8_t fetchrect(uint8_t digit, uint8_t x, uint8_t y, bool mirror) {
  // character_map maps 0-9 (digits), 10-13 (ornaments), ascii codes of uppercase letters and 100-109 (progress) to characters[]
  uint8_t color1 = characters[character_map[digit]][(y*2)]; // get one row of digit colors
  uint8_t color2 = characters[character_map[digit]][(y*2)+1]; // get one row of ornament colors
  uint8_t mask = 0b10000 >> x;

  if (mirror) {
    mask = 0b00001 << x;
  }

  if (color1 & mask) { // check column of row
    return 1;
  } else if (color2 & mask) {
    return 2;
  } else {
    return 0;
  }
}

static GColor8 getSlotColor(uint8_t x, uint8_t y, uint8_t digit, uint8_t pos, bool mirror) {
  static uint8_t argb;
  static bool should_add_var = false;
  uint8_t thisrect = fetchrect(digit, x, y, mirror);

  if (thisrect == 0) {

    if (state.contrastmode) {
      return GColorBlack;
    }

    return state.background_color;

  } else if (thisrect == 1) {

    #if defined(PBL_COLOR)
      if (state.contrastmode && pos >= 8) {
        argb = 0b11000000;
      } else {
        argb = state.contrastmode ? 0b11111111 : prefs.number_base_color;
        should_add_var = state.contrastmode ? false : prefs.number_variation;
      }
    #elif defined(PBL_BW)
      if (prefs.invert) {
        argb = 0b11000000;
      } else {
        argb = 0b11111111;
      }
    #endif
  } else {
    #if defined(PBL_COLOR)
      argb = state.contrastmode ? 0b11000001 : prefs.ornament_base_color;
      should_add_var = state.contrastmode ? false : prefs.ornament_variation;
    #elif defined(PBL_BW)
      if (prefs.monochrome) {
        argb = 0b11010101;
      } else {
        if (prefs.invert) {
          argb = 0b11000000;
        } else {
          argb = 0b11111111;
        }
      }
    #endif
  }

  if (should_add_var) {
    if (argb == 0b11111111) {
      argb -= variation[ ( y*5 + x + digit*17 + pos*19 )%sizeof(variation) ];
    } else {
      argb += variation[ ( y*5 + x + digit*17 + pos*19 )%sizeof(variation) ];
    }
  }

  if (pos >= 8) {
    uint8_t argb_temp = shadowtable[alpha & argb];

    if (argb_temp == state.background_color.argb) {
      argb_temp = argb;
    }

    argb = argb_temp;
  }

  GColor8 color = { .argb = argb };
  return color;
}

static void updateSlot(Layer *layer, GContext *ctx) {
	digitSlot *slot = *(digitSlot**)layer_get_data(layer);

  int widthadjust = 0;

	if (slot->divider == 2) {
		widthadjust = 1;
	}

	int tilesize = state.tile_size/slot->divider;
	uint32_t skewedNormTime = slot->normTime*3;

  graphics_context_set_fill_color(ctx, state.background_color);
	GRect r = layer_get_bounds(slot->layer);
	graphics_fill_rect(ctx, GRect(0, 0, r.size.w, r.size.h), 0, GCornerNone);

	for (int t=0; t < state.total_blocks; t++) {
		int w = 0;
		int tx = t % state.font_width_blocks;
		int ty = t / state.font_height_blocks;
		int shift = 0-(t-ty);

    GColor8 oldColor = getSlotColor(tx, ty, slot->prevDigit, slot->slotIndex, slot->mirror);
    GColor8 newColor = getSlotColor(tx, ty, slot->curDigit, slot->slotIndex, slot->mirror);

	  graphics_context_set_fill_color(ctx, oldColor);
    graphics_fill_rect(ctx, GRect((tx*tilesize)-(tx*widthadjust), ty*tilesize-(ty*widthadjust), tilesize-widthadjust, tilesize-widthadjust), 0, GCornerNone);

    if(!gcolor_equal(oldColor, newColor)) {
      w = (skewedNormTime*state.tile_size/ANIMATION_NORMALIZED_MAX)+shift-widthadjust;

   		if (w < 0) {
  			w = 0;
  		} else if (w > tilesize-widthadjust) {
  			w = tilesize-widthadjust;
  		}

      graphics_context_set_fill_color(ctx, newColor);
      graphics_fill_rect(ctx, GRect((tx*tilesize)-(tx*widthadjust), ty*tilesize-(ty*widthadjust), w, tilesize-widthadjust), 0, GCornerNone);
    }
	}
}

static unsigned short get_display_hour(uint8_t hour) {
    if (clock_is_24h_style()) {
        return hour;
    }

    uint8_t display_hour = hour % 12;

    return display_hour ? display_hour : 12;
}

static void setupAnimation() {
  anim = animation_create();
	animation_set_delay(anim, 0);
	animation_set_duration(anim, state.contrastmode ? 500 : state.in_shake_mode ? state.animation_time/2 : state.animation_time);
	animation_set_implementation(anim, &animImpl);
  animation_set_curve(anim, AnimationCurveEaseInOut);
  #ifdef DEBUG
    APP_LOG(APP_LOG_LEVEL_INFO, "Set up anim %i", (int)anim);
  #endif
}

static void destroyAnimation() {
  #ifdef DEBUG
    APP_LOG(APP_LOG_LEVEL_INFO, "Destroying anim %i", (int)anim);
  #endif
  animation_destroy(anim);
  anim = NULL;
}

#ifdef PBL_HEALTH
static void setHeartRateSlots(uint16_t number, bool isHeartrate, bool isBottom) {
  static uint8_t digits[4];
  digits[0] = 0;
  digits[1] = 1;
  digits[2] = 2;
  digits[3] = 3;

  if (isBottom) {
    digits[0] = 4;
    digits[1] = 5;
    digits[2] = 6;
    digits[3] = 7;
  }

  if (isHeartrate) {
    slot[digits[0]].curDigit = 120;
    slot[digits[1]].curDigit = 10;
    slot[digits[2]].curDigit = 10;
    slot[digits[3]].curDigit = 10;
  }

  if (isHeartrate && number == 0) {
    if (isBottom) {
      slot[digits[1]].curDigit = 'N';
      slot[digits[2]].curDigit = '/';
      slot[digits[3]].curDigit = 'A';
    } else {
      slot[digits[2]].curDigit = 'N';
      slot[digits[3]].curDigit = 'A';
    }
  } else {
    uint16_t input = number;
    uint16_t hundreds = input/100;
    input -= (hundreds)*100;
    uint8_t tens = input/10;
    input -= (tens)*10;
    uint8_t units=input;

    if (hundreds > 0) {
      slot[digits[1]].curDigit = hundreds;
    }

    if (tens > 0 || hundreds > 0) {
      slot[digits[2]].curDigit = tens;
    }

    slot[digits[3]].curDigit = units;
  }

  if (!isBottom) {
    slot[4].curDigit = 121;
    slot[5].curDigit = 101;
    slot[6].curDigit = 10;
    slot[7].curDigit = 10;

    if (number > 158) {
      slot[5].curDigit = 13;
      slot[6].curDigit = 13;
      slot[7].curDigit = 13;

    } else if (number > 130) {
      slot[5].curDigit = 13;
      slot[6].curDigit = 13;

    } else if (number > 93) {
      slot[5].curDigit = 13;
    }
  }
}

static void showHeartRate(bool isBbottom) {
  #if defined(PBL_PLATFORM_EMERY) || defined(PBL_PLATFORM_DIORITE)
    HealthServiceAccessibilityMask hr = health_service_metric_accessible(HealthMetricHeartRateBPM, time(NULL), time(NULL));
    if (hr & HealthServiceAccessibilityMaskAvailable) {
      state.heartrate = (int)health_service_peek_current_value(HealthMetricHeartRateBPM);
    }
  #endif

  if (state.heartrate > 0) {
    setHeartRateSlots(state.heartrate, true, isBbottom);
  } else {
    setHeartRateSlots(0, true, isBbottom);
  }
}

static void update_step_goal() {
  const HealthMetric metric_stepcount = HealthMetricStepCount;
  time_t start = time_start_of_today();
  time_t now = time(NULL);
  time_t end = start + SECONDS_PER_DAY;
  const HealthServiceTimeScope scope = HealthServiceTimeScopeDaily;

  // Check the metric has data available for us
  HealthServiceAccessibilityMask mask_steps = health_service_metric_accessible(metric_stepcount, start, now);
  HealthServiceAccessibilityMask mask_average = health_service_metric_averaged_accessible(metric_stepcount, start, end, scope);

  if (prefs.dynamicstepgoal && (mask_average & HealthServiceAccessibilityMaskAvailable)) {
    state.stepgoal = (uint16_t)health_service_sum_averaged(metric_stepcount, start, end, scope);
  } else {
    state.stepgoal = prefs.stepgoal;
  }

  if(mask_steps & HealthServiceAccessibilityMaskAvailable) {
    // Data is available!
    uint16_t stepcount = health_service_sum_today(metric_stepcount);
    state.stepprogress = (uint16_t)(((float)stepcount/(float)state.stepgoal)*100);
    #ifdef DEBUG
      APP_LOG(APP_LOG_LEVEL_INFO, "Stepcount: %d / Stepgoal: %d", stepcount, stepgoal);
      APP_LOG(APP_LOG_LEVEL_INFO, "Step progress: %d%%", stepprogress);
    #endif
  } else {
    // No data recorded yet today
    #ifdef DEBUG
      APP_LOG(APP_LOG_LEVEL_ERROR, "Data unavailable!");
    #endif
  }
}
#endif

static void setProgressSlots(uint16_t progress, bool showgoal, bool bottom) {
  static uint8_t digits[4];
  static uint8_t progressoffset;
  uint8_t mappedProgress;

  if (bottom) {
    progressoffset = 100;
    mappedProgress = (((progress+3)*0.95*40)/100);
    digits[0] = 4;
    digits[1] = 5;
    digits[2] = 6;
    digits[3] = 7;

    if (showgoal && progress >= 102) {
      uint16_t input = progress;
      uint16_t hundreds = input/100;
      input -= (hundreds)*100;
      uint8_t tens = input/10;
      input -= (tens)*10;
      uint8_t units=input;
      slot[digits[0]].curDigit = hundreds;
      slot[digits[1]].curDigit = tens;
      slot[digits[2]].curDigit = units;
      slot[digits[3]].curDigit = '%';

    } else if (!showgoal && progress >= 100) {
      slot[digits[0]].curDigit = progressoffset+9;
      slot[digits[1]].curDigit = progressoffset+9;
      slot[digits[2]].curDigit = progressoffset+9;
      slot[digits[3]].curDigit = progressoffset+9;

    } else if (showgoal && progress >= 100) {
      slot[digits[0]].curDigit = 'G';
      slot[digits[1]].curDigit = 'O';
      slot[digits[2]].curDigit = 'A';
      slot[digits[3]].curDigit = 'L';

    } else {
      for(uint8_t dig = 0; dig < sizeof digits; dig++) {
        slot[digits[dig]].curDigit = 100;
      }

      uint8_t partialSegment = progressoffset+mappedProgress%10;
      slot[digits[0]].curDigit = partialSegment;

      if (mappedProgress >= 10) {
        slot[digits[0]].curDigit = progressoffset+9;
        slot[digits[1]].curDigit = partialSegment;
      }

      if (mappedProgress >= 20) {
        slot[digits[1]].curDigit = progressoffset+9;
        slot[digits[2]].curDigit = partialSegment;
      }

      if (mappedProgress >= 30) {
        slot[digits[2]].curDigit = progressoffset+9;
        slot[digits[3]].curDigit = partialSegment;
      }

      if (mappedProgress >= 40) {
        slot[digits[3]].curDigit = progressoffset+9;
      }
    }

    if (prefs.bottomrow == 1) {
      if (battery_state_service_peek().is_charging) {
        slot[digits[0]].curDigit = 14;
        slot[digits[1]].curDigit = 15;
        slot[digits[2]].curDigit = 16;
        slot[digits[3]].curDigit = 17;
      }
    }
  } else {
    progressoffset = 110;
    mappedProgress = (((progress+3)*0.92*40)/100);

    if (!showgoal || (showgoal && progress < 100)) {
      uint8_t front_digit = progress_top_seq[mappedProgress%20]/10;
      uint8_t back_digit = progress_top_seq[mappedProgress%20]%10;

      if (mappedProgress<19) {
        slot[0].curDigit = progressoffset;
        slot[1].curDigit = progressoffset;
        slot[2].curDigit = progressoffset+front_digit;
        slot[3].curDigit = progressoffset+back_digit;
      } else {
        slot[0].curDigit = progressoffset+front_digit;
        slot[1].curDigit = progressoffset+back_digit;
        slot[2].curDigit = progressoffset+9;
        slot[3].curDigit = progressoffset+9;
      }
      if (progress >= 100) {
        slot[0].curDigit = progressoffset+9;
        slot[1].curDigit = progressoffset+9;
        slot[2].curDigit = progressoffset+9;
        slot[3].curDigit = progressoffset+9;
      }
    } else if (showgoal && progress > 999) {
      slot[4].curDigit = 9;
      slot[5].curDigit = 9;
      slot[6].curDigit = 9;
      slot[7].curDigit = '%';

    } else if (showgoal && progress >= 100) {
      uint16_t input = progress;
      uint16_t hundreds=input/100;
      input-=(hundreds)*100;
      uint8_t tens=input/10;
      input-=(tens)*10;
      uint8_t units=input;
      slot[4].curDigit = hundreds;
      slot[5].curDigit = tens;
      slot[6].curDigit = units;
      slot[7].curDigit = '%';
    }

    if (prefs.cheeky && showgoal && progress >= 999) {
      slot[0].curDigit = 'F';
      slot[1].curDigit = '*';
      slot[2].curDigit = 'C';
      slot[3].curDigit = 'K';
    } else if (prefs.cheeky && showgoal && progress >= 750) {
      slot[0].curDigit = 'Y';
      slot[1].curDigit = 'O';
      slot[2].curDigit = 'L';
      slot[3].curDigit = 'O';
    } else if (prefs.cheeky && showgoal && progress >= 500) {
      slot[0].curDigit = 'W';
      slot[1].curDigit = 'H';
      slot[2].curDigit = 'A';
      slot[3].curDigit = 'T';
    } else if (prefs.cheeky && showgoal && progress >= 400) {
      slot[0].curDigit = 'T';
      slot[1].curDigit = 'I';
      slot[2].curDigit = 'L';
      slot[3].curDigit = 'T';
    } else if (prefs.cheeky && showgoal && progress >= 300) {
      slot[0].curDigit = 'O';
      slot[1].curDigit = 'M';
      slot[2].curDigit = 'F';
      slot[3].curDigit = 'G';
    } else if (prefs.cheeky && showgoal && progress >= 250) {
      slot[0].curDigit = 'S';
      slot[1].curDigit = 'T';
      slot[2].curDigit = 'A';
      slot[3].curDigit = 'R';
    } else if (prefs.cheeky && showgoal && progress >= 220) {
      slot[0].curDigit = 'H';
      slot[1].curDigit = 'O';
      slot[2].curDigit = 'L';
      slot[3].curDigit = 'Y';
    } else if (prefs.cheeky && showgoal && progress >= 200) {
      slot[0].curDigit = 'G';
      slot[1].curDigit = 'A';
      slot[2].curDigit = 'S';
      slot[3].curDigit = 'P';
    } else if (prefs.cheeky && showgoal && progress >= 175) {
      slot[0].curDigit = 'D';
      slot[1].curDigit = 'A';
      slot[2].curDigit = 'N';
      slot[3].curDigit = 'G';
    } else if (prefs.cheeky && showgoal && progress >= 150) {
      slot[0].curDigit = 'W';
      slot[1].curDigit = 'H';
      slot[2].curDigit = 'O';
      slot[3].curDigit = 'A';
    } else if (prefs.cheeky && showgoal && progress >= 130) {
      slot[0].curDigit = 'S';
      slot[1].curDigit = 'W';
      slot[2].curDigit = 'A';
      slot[3].curDigit = 'G';
    } else if (prefs.cheeky && showgoal && progress >= 115) {
      slot[0].curDigit = 'C';
      slot[1].curDigit = 'O';
      slot[2].curDigit = 'O';
      slot[3].curDigit = 'L';
    } else if (prefs.cheeky && showgoal && progress >= 105) {
      slot[0].curDigit = 'Y';
      slot[1].curDigit = 'E';
      slot[2].curDigit = 'A';
      slot[3].curDigit = 'H';
    } else if (prefs.cheeky && showgoal && progress >= 100) {
      slot[0].curDigit = 'G';
      slot[1].curDigit = 'O';
      slot[2].curDigit = 'A';
      slot[3].curDigit = 'L';
    } else if (prefs.cheeky && showgoal && progress >= 78) {
      slot[4].curDigit = 'N';
      slot[5].curDigit = 'I';
      slot[6].curDigit = 'C';
      slot[7].curDigit = 'E';
    } else if (prefs.cheeky && showgoal && progress >= 62) {
      slot[4].curDigit = 'N';
      slot[5].curDigit = 'E';
      slot[6].curDigit = 'A';
      slot[7].curDigit = 'T';
    } else if (prefs.cheeky && showgoal && progress >= 45) {
      slot[4].curDigit = 'G';
      slot[5].curDigit = 'O';
      slot[6].curDigit = 'O';
      slot[7].curDigit = 'D';
    } else if (prefs.cheeky && showgoal && progress >= 28) {
      slot[4].curDigit = 'O';
      slot[5].curDigit = 'K';
      slot[6].curDigit = 'A';
      slot[7].curDigit = 'Y';
    } else if (prefs.cheeky && showgoal && progress >= 16) {
      slot[4].curDigit = 'W';
      slot[5].curDigit = 'E';
      slot[6].curDigit = 'L';
      slot[7].curDigit = 'L';
    } else if (prefs.cheeky && showgoal && progress >= 12) {
      slot[4].curDigit = 'A';
      slot[5].curDigit = 'H';
      slot[6].curDigit = 'E';
      slot[7].curDigit = 'M';
    } else if (prefs.cheeky && showgoal && progress >= 8) {
      slot[4].curDigit = 'L';
      slot[5].curDigit = 'A';
      slot[6].curDigit = 'M';
      slot[7].curDigit = 'E';
    } else if (prefs.cheeky && showgoal) {
      slot[4].curDigit = 'O';
      slot[5].curDigit = 'U';
      slot[6].curDigit = 'C';
      slot[7].curDigit = 'H';
    } else if (!prefs.cheeky && showgoal) {
      slot[4].curDigit = 'S';
      slot[5].curDigit = 'T';
      slot[6].curDigit = 'E';
      slot[7].curDigit = 'P';
    } else {
      slot[4].curDigit = 'B';
      slot[5].curDigit = 'A';
      slot[6].curDigit = 'T';
      slot[7].curDigit = 'T';
    }
  }
}

static void setBigDate() {
  // OPTIMIZE!!
  uint8_t localeid = 0;
  static char weekdayname[3];
  static char locale[3];
  static uint8_t da, mo, ye;

  time_t now = time(NULL);
  tm *t = localtime(&now);

  da = t->tm_mday;
  mo = t->tm_mon+1;
  ye = t->tm_year;

  uint16_t input = ye+1900;
  uint16_t thousands=input/1000;
  input-=(thousands)*1000;
  uint16_t hundreds=input/100;
  input-=(hundreds)*100;
  uint8_t tens=input/10;
  input-=(tens)*10;
  uint8_t units=input;
  slot[4].curDigit = thousands;
  slot[5].curDigit = hundreds;
  slot[6].curDigit = tens;
  slot[7].curDigit = units;

  strncpy(locale, i18n_get_system_locale(), 2);

  if (prefs.weekday) {
    strftime(weekday_buffer, sizeof(weekday_buffer), "%w", t);

    for (uint8_t lid = 0; lid < 6; lid++) {
      if (strncmp(locales[lid], locale, 2) == 0) {
        localeid = lid;
      }
    }

    uint8_t weekdaynum = ((int)weekday_buffer[0])-0x30;
    strcpy(weekdayname, weekdays[localeid][weekdaynum]);
  }

  if (!prefs.eu_date) {
    if (prefs.weekday) {
      slot[0].curDigit = (uint8_t) weekdayname[0];
      slot[1].curDigit = (uint8_t) weekdayname[1];
    } else {
      slot[0].curDigit = mo/10;
      slot[1].curDigit = mo%10;
    }

    slot[2].curDigit = da/10;
    slot[3].curDigit = da%10;

  } else {
    slot[0].curDigit = da/10;
    slot[1].curDigit = da%10;

    if (prefs.weekday) {
      slot[2].curDigit = (uint8_t) weekdayname[0];
      slot[3].curDigit = (uint8_t) weekdayname[1];
    } else {
      slot[2].curDigit = mo/10;
      slot[3].curDigit = mo%10;
    }
  }
}

static void handle_tick(struct tm *t, TimeUnits units_changed) {
	static uint8_t ho, mi, da, mo;

  if (state.splashEnded && !state.initial_anim) {
    if (animation_is_scheduled(anim)){
      animation_unschedule(anim);
      animation_destroy(anim);
    }

    ho = get_display_hour(t->tm_hour);
    mi = t->tm_min;
    da = t->tm_mday;
    mo = t->tm_mon+1;

    #ifdef DEBUG
      ho = 8+(mi%4);
    #endif

    uint8_t localeid = 0;
    static char weekdayname[3];
    static char locale[3];
    strncpy(locale, i18n_get_system_locale(), 2);

    if (prefs.weekday) {
      strftime(weekday_buffer, sizeof(weekday_buffer), "%w", t);

      for (uint8_t lid = 0; lid < 6; lid++) {
        if (strncmp(locales[lid], locale, 2) == 0) { localeid = lid; }
      }

      uint8_t weekdaynum = ((int)weekday_buffer[0])-0x30;
      #ifdef DEBUG
        weekdaynum = (int)mi%7;
      #endif
      strcpy(weekdayname, weekdays[localeid][weekdaynum]);
    }

    if (prefs.battery_saver || prefs.ns_start == prefs.ns_stop) {
      state.allow_animate = false;

    } else {

      if (prefs.nightsaver) {
        if (prefs.ns_start > prefs.ns_stop) {
          // across midnight
          if (t->tm_hour >= prefs.ns_start || t->tm_hour < prefs.ns_stop) {
            state.allow_animate = false;
          }
        } else {
          // prior to midnight
          if (t->tm_hour >= prefs.ns_start && t->tm_hour < prefs.ns_stop) {
            state.allow_animate = false;
          }
        }

      } else {
        state.allow_animate = true;
      }
    }

    for (uint8_t i=0; i < state.num_slots; i++) {
      slot[i].prevDigit = slot[i].curDigit;
    }

    for (int dig = 0; dig < state.num_slots; dig++) {
      if (slot[dig].prevDigit == 10 || slot[dig].prevDigit == 12) {
        slot[dig].curDigit = 11;
      } else {
        slot[dig].curDigit = 10;
      }
    }

    if (ho/10 > 0 || prefs.leading_zero) {
      slot[0].curDigit = ho/10;
    }

    slot[1].curDigit = ho%10;
    slot[2].curDigit = mi/10;
    slot[3].curDigit = mi%10;

    switch (prefs.bottomrow) {
      case 1:
        state.battprogress = battery_state_service_peek().charge_percent;
        setProgressSlots(state.battprogress, false, true);
        break;

      #ifdef PBL_HEALTH
      case 2:
        update_step_goal();
        setProgressSlots(state.stepprogress, true, true);
        break;

      case 3:
        showHeartRate(true);
        break;
      #endif

      default:
        if (!prefs.eu_date) {
          if (prefs.weekday) {
            slot[4].curDigit = (uint8_t) weekdayname[0];
            slot[5].curDigit = (uint8_t) weekdayname[1];
          } else {
            slot[4].curDigit = mo/10;
            slot[5].curDigit = mo%10;
          }
          if (prefs.center && da < 10) {
            slot[6].curDigit = da%10;
          } else {
            slot[6].curDigit = da/10;
            slot[7].curDigit = da%10;
          }

        } else {
          slot[4].curDigit = da/10;
          slot[5].curDigit = da%10;
          if (prefs.weekday) {
            slot[6].curDigit = (uint8_t) weekdayname[0];
            slot[7].curDigit = (uint8_t) weekdayname[1];
          } else {
            if (prefs.center && mo < 10) {
              slot[6].curDigit = mo%10;
            } else {
              slot[6].curDigit = mo/10;
              slot[7].curDigit = mo%10;
            }
          }
        }
        break;
    }

    setupAnimation();
    animation_schedule(anim);
  }
}

static void initialAnimationDone() {
  state.initial_anim = false;
}

void handle_timer(void *data) {
  state.splashEnded = true;
  time_t curTime = time(NULL);
  handle_tick(localtime(&curTime), SECOND_UNIT|MINUTE_UNIT|HOUR_UNIT|DAY_UNIT|MONTH_UNIT|YEAR_UNIT);
	state.in_shake_mode = false;
  state.initial_anim = true;
  app_timer_register(state.contrastmode ? 500 : state.in_shake_mode ? state.animation_time/2 : state.animation_time, initialAnimationDone, NULL);
}

static void tap_handler(AccelAxisType axis, int32_t direction) {

  if (prefs.wristflick != 0 && !state.in_shake_mode) {

    for (uint8_t i=0; i<state.num_slots; i++) {
      slot[i].prevDigit = slot[i].curDigit;
    }

    switch (prefs.wristflick) {
      case 1:
        state.battprogress = battery_state_service_peek().charge_percent;
        setProgressSlots(state.battprogress, false, false); // only show "GOAL" if PERCENTAGE is STEP_PERCENTAGE
        break;

      #ifdef PBL_HEALTH
      case 2:
        update_step_goal();
        setProgressSlots(state.stepprogress, true, false);
        break;

      case 3:
        showHeartRate(false);
        break;
      #endif

      case 4:
        setBigDate();
        break;

      default:
        break;
    }

    state.in_shake_mode = true;
    setupAnimation();
    animation_schedule(anim);
    app_timer_register(3000, handle_timer, NULL);
  }
}

void initSlot(int i, Layer *parent) {
	digitSlot *s = &slot[i];

  s->slotIndex = i;
	s->normTime = ANIMATION_NORMALIZED_MAX;
	s->prevDigit = startDigit[i];
	s->curDigit = startDigit[i];

	if ((i<4 || i>=8) && i<14) {
		s->divider = 1;
	} else {
		s->divider = 2;
	}

  s->layer = layer_create_with_data(slotFrame(i), sizeof(digitSlot *));
	*(digitSlot **)layer_get_data(s->layer) = s;

	layer_set_update_proc(s->layer, updateSlot);
	layer_add_child(parent, s->layer);
}

static void deinitSlot(uint8_t i) {
	layer_destroy(slot[i].layer);
}

static void animateDigits(struct Animation *anim, const AnimationProgress normTime) {
	for (uint8_t i=0; i < state.num_slots; i++) {
		if (slot[i].curDigit != slot[i].prevDigit) {
      if (state.allow_animate) {
        slot[i].normTime = normTime;
      } else {
        slot[i].normTime = ANIMATION_NORMALIZED_MAX;
      }

			layer_mark_dirty(slot[i].layer);
		}
	}
}

static void setupUI() {
  window_set_background_color(window, state.background_color);
	window_stack_push(window, true);

	Layer *rootLayer = window_get_root_layer(window);

	for (uint8_t i=0; i < state.num_slots; i++) {
		initSlot(i, rootLayer);
	}

	animImpl.setup = NULL;
	animImpl.update = animateDigits;
	animImpl.teardown = destroyAnimation;

	setupAnimation();

  // Choose animation start delay according to settings
  if (state.contrastmode) {
    app_timer_register(0, handle_timer, NULL);
  } else if (prefs.quick_start) {
    app_timer_register(700, handle_timer, NULL);
  } else {
    app_timer_register(2000, handle_timer, NULL);
  }
}

static void teardownUI() {
	for (uint8_t i=0; i < state.num_slots; i++) {
		deinitSlot(i);
	}

	animation_destroy(anim);
}

static void battery_handler(BatteryChargeState charge_state) {
  if (prefs.bottomrow == 1 || prefs.wristflick == 1) {
    state.battprogress = charge_state.charge_percent;
  }

  #ifdef PBL_COLOR
  if (prefs.contrast) {
    if (state.previous_contrastmode != charge_state.is_plugged) {
      window_set_background_color(window, state.background_color);
      app_timer_register(0, handle_timer, NULL);
    }

    state.previous_contrastmode = charge_state.is_plugged;
  }
  #endif

  if (prefs.backlight) {
    light_enable(charge_state.is_plugged);
  }

  if (state.chargestate != charge_state.is_plugged) {
    window_set_background_color(window, state.background_color);
    app_timer_register(0, handle_timer, NULL);
  }

  state.chargestate = charge_state.is_plugged;
}

static void in_received_handler(DictionaryIterator *iter, void *context) {
  preferences_load(iter, &prefs);
  persist_write_data(PREFERENCES_KEY, &prefs, sizeof(prefs));
  state_update(&state, &prefs);

  if (prefs.backlight) {
    light_enable(battery_state_service_peek().is_plugged);
  }

  teardownUI();
  setupUI();
}

static void in_dropped_handler(AppMessageResult reason, void *context) {
  #ifdef DEBUG
    APP_LOG(APP_LOG_LEVEL_WARNING, "Dropped message because %i", (int)reason);
  #endif
}

static void init() {
  state_init(&state);
  window = window_create();

  if(persist_exists(PREFERENCES_KEY)){
    persist_read_data(PREFERENCES_KEY, &prefs, sizeof(prefs));
  } else {
    preferences_set_defaults(&prefs);
  }

  state_update(&state, &prefs);

  setupUI();

  if (battery_state_service_peek().is_plugged) {
    if (prefs.backlight) {
      light_enable(true);
    }
  }

  // Setup app message
  app_message_register_inbox_received(in_received_handler);
  app_message_register_inbox_dropped(in_dropped_handler);
  app_message_open(264,0);

	tick_timer_service_subscribe(MINUTE_UNIT, handle_tick);

  handle_bluetooth(connection_service_peek_pebble_app_connection());

  battery_state_service_subscribe(battery_handler);

  connection_service_subscribe((ConnectionHandlers) {
    .pebble_app_connection_handler = handle_bluetooth
  });

  accel_tap_service_subscribe(tap_handler);
}

static void deinit() {
	tick_timer_service_unsubscribe();
  connection_service_unsubscribe();
  battery_state_service_unsubscribe();
  accel_tap_service_unsubscribe();
  teardownUI();
  window_destroy(window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
