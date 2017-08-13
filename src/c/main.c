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

digitSlot slot[CONST_NUM_SLOTS];
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

static GRect slot_frame(int8_t i) {
	int16_t x, y, w, h;

	if (i < 4) { // main digits
		w = CONST_FONT_W;
		h = CONST_FONT_W;

		if (i % 2) {
			x = CONST_ORIGIN_X + CONST_FONT_W + CONST_TILE_SIZE; // i = 1 or 3
		} else {
			x = CONST_ORIGIN_X; // i = 0 or 2
		}

		if (i < 2) {
			y = CONST_ORIGIN_Y;
		} else {
			y = CONST_ORIGIN_Y + CONST_FONT_W + CONST_TILE_SIZE;
		}

	} else if (i < 8) { // date digits
		w = CONST_FONT_W/2;
		h = CONST_FONT_W/2;
		x = CONST_ORIGIN_X + (CONST_FONT_W + CONST_TILE_SIZE) * (i - 4) / 2;
		y = CONST_ORIGIN_Y + (CONST_FONT_W + CONST_TILE_SIZE) * 2;

	} else if (i < 10) { // top filler for round
    w = CONST_FONT_W;
		h = CONST_FONT_W;

    if (i % 2) {
			x = CONST_ORIGIN_X + CONST_FONT_W + CONST_TILE_SIZE; // i = 1 or 3
		} else {
			x = CONST_ORIGIN_X; // i = 0 or 2
		}

    y = (int8_t) (CONST_ORIGIN_Y - CONST_FONT_W - CONST_TILE_SIZE);

  } else if (i < 14) { // side filler for round
    w = CONST_FONT_W;
		h = CONST_FONT_W;

    if (i % 2) {
			x = CONST_ORIGIN_X + CONST_FONT_W + CONST_TILE_SIZE + CONST_FONT_W + CONST_TILE_SIZE;
		} else {
			x = (int8_t) (CONST_ORIGIN_X - CONST_FONT_W - CONST_TILE_SIZE);
		}

		if (i < 12) {
			y = CONST_ORIGIN_Y;
		} else {
			y = CONST_ORIGIN_Y + CONST_FONT_W + CONST_TILE_SIZE;
		}

  } else if (i < 16) { // botom filler for round
		w = CONST_FONT_W/2;
		h = CONST_FONT_W/2;
    x = CONST_ORIGIN_X + (CONST_FONT_W + CONST_TILE_SIZE) * (i - 13) / 2; // 13 = 14-1 (skipping invisible slot outside circle)
		y = CONST_ORIGIN_Y + (CONST_FONT_W + CONST_TILE_SIZE) * 2 + h + (h/6);

  } else { // bottom side filler for round
		w = CONST_FONT_W/2;
		h = CONST_FONT_W/2;

    if (i % 2) {
      x = CONST_ORIGIN_X + CONST_FONT_W + CONST_TILE_SIZE + CONST_FONT_W + CONST_TILE_SIZE;
    } else {
      x = CONST_ORIGIN_X - w - CONST_TILE_SIZE/2; // todo: find correct value
    }

		y = CONST_ORIGIN_Y + (CONST_FONT_W + CONST_TILE_SIZE) * 2;
  }

	return GRect(x, y, w, h);
}

static uint8_t fetch_rect(uint8_t digit, uint8_t x, uint8_t y, bool mirror) {
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

static GColor8 get_slot_color(uint8_t x, uint8_t y, uint8_t digit, uint8_t pos, bool mirror) {
  static uint8_t argb;
  uint8_t thisrect = fetch_rect(digit, x, y, mirror);

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
      }
    #elif defined(PBL_BW)
      argb = 0b11111111;
    #endif
  } else {
    #if defined(PBL_COLOR)
      argb = state.contrastmode ? 0b11000001 : prefs.ornament_base_color;
    #elif defined(PBL_BW)
      argb = 0b11111111;
    #endif
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

static void update_slot(Layer *layer, GContext *ctx) {
	digitSlot *slot = *(digitSlot**)layer_get_data(layer);

  int widthadjust = 0;

	if (slot->divider == 2) {
		widthadjust = 1;
	}

	int tilesize = CONST_TILE_SIZE/slot->divider;
	uint32_t skewedNormTime = slot->normTime*3;

  graphics_context_set_fill_color(ctx, state.background_color);
	GRect r = layer_get_bounds(slot->layer);
	graphics_fill_rect(ctx, GRect(0, 0, r.size.w, r.size.h), 0, GCornerNone);

	for (int t=0; t < CONST_TOTAL_BLOCKS; t++) {
		int w = 0;
		int tx = t % CONST_FONT_SIZE;
		int ty = t / CONST_FONT_SIZE;
		int shift = 0-(t-ty);

    GColor8 oldColor = get_slot_color(tx, ty, slot->prevDigit, slot->slotIndex, slot->mirror);
    GColor8 newColor = get_slot_color(tx, ty, slot->curDigit, slot->slotIndex, slot->mirror);

	  graphics_context_set_fill_color(ctx, oldColor);
    graphics_fill_rect(ctx, GRect((tx*tilesize)-(tx*widthadjust), ty*tilesize-(ty*widthadjust), tilesize-widthadjust, tilesize-widthadjust), 0, GCornerNone);

    if(!gcolor_equal(oldColor, newColor)) {
      w = (skewedNormTime*CONST_TILE_SIZE/ANIMATION_NORMALIZED_MAX)+shift-widthadjust;

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

static void setup_animation() {
  anim = animation_create();
	animation_set_delay(anim, 0);
	animation_set_duration(anim, state.contrastmode ? 500 : state.in_shake_mode ? state.animation_time/2 : state.animation_time);
	animation_set_implementation(anim, &animImpl);
  animation_set_curve(anim, AnimationCurveEaseInOut);
  #ifdef DEBUG
    APP_LOG(APP_LOG_LEVEL_INFO, "Set up anim %i", (int)anim);
  #endif
}

static void destroy_animation() {
  #ifdef DEBUG
    APP_LOG(APP_LOG_LEVEL_INFO, "Destroying anim %i", (int)anim);
  #endif
  animation_destroy(anim);
  anim = NULL;
}

static void set_battery_slots(bool bottom){
  static uint8_t digits[4];
  uint8_t progress = battery_state_service_peek().charge_percent;

  if (bottom) {
    digits[0] = 4;
    digits[1] = 5;
    digits[2] = 6;
    digits[3] = 7;
  } else {
    digits[0] = 0;
    digits[1] = 1;
    digits[2] = 2;
    digits[3] = 3;
  }

  if (battery_state_service_peek().is_charging) {
    slot[digits[0]].curDigit = 14;
    slot[digits[1]].curDigit = 15;
    slot[digits[2]].curDigit = 16;
    slot[digits[3]].curDigit = 17;
  } else {
    if (progress >= 100) {
      slot[digits[0]].curDigit = 109;
      slot[digits[1]].curDigit = 109;
      slot[digits[2]].curDigit = 109;
      slot[digits[3]].curDigit = 109;
    } else {
      uint8_t mappedProgress = (((progress+3)*0.92*40)/100);;
      uint8_t front_digit = progress_top_seq[mappedProgress%20]/10;
      uint8_t back_digit = progress_top_seq[mappedProgress%20]%10;

      if (mappedProgress<19) {
        slot[digits[0]].curDigit = 100;
        slot[digits[1]].curDigit = 100;
        slot[digits[2]].curDigit = 100+front_digit;
        slot[digits[3]].curDigit = 100+back_digit;
      } else {
        slot[digits[0]].curDigit = 100+front_digit;
        slot[digits[1]].curDigit = 100+back_digit;
        slot[digits[2]].curDigit = 109;
        slot[digits[3]].curDigit = 109;
      }
    }
  }
}

static void set_big_date() {
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

    for (uint8_t i=0; i < CONST_NUM_SLOTS; i++) {
      slot[i].prevDigit = slot[i].curDigit;
    }

    for (int dig = 0; dig < CONST_NUM_SLOTS; dig++) {
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
        set_battery_slots(true);
        break;

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

    setup_animation();
    animation_schedule(anim);
  }
}

static void initial_animation_done() {
  state.initial_anim = false;
}

void handle_timer(void *data) {
  state.splashEnded = true;
  time_t curTime = time(NULL);
  handle_tick(localtime(&curTime), SECOND_UNIT|MINUTE_UNIT|HOUR_UNIT|DAY_UNIT|MONTH_UNIT|YEAR_UNIT);
	state.in_shake_mode = false;
  state.initial_anim = true;
  app_timer_register(state.contrastmode ? 500 : state.in_shake_mode ? state.animation_time/2 : state.animation_time, initial_animation_done, NULL);
}

static void tap_handler(AccelAxisType axis, int32_t direction) {

  if (prefs.wristflick != 0 && !state.in_shake_mode) {

    for (uint8_t i=0; i<CONST_NUM_SLOTS; i++) {
      slot[i].prevDigit = slot[i].curDigit;
    }

    switch (prefs.wristflick) {
      case 1:
        set_battery_slots(false);
        break;

      case 2:
        set_big_date();
        break;

      default:
        break;
    }

    state.in_shake_mode = true;
    setup_animation();
    animation_schedule(anim);
    app_timer_register(3000, handle_timer, NULL);
  }
}

void init_slot(int i, Layer *parent) {
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

  s->layer = layer_create_with_data(slot_frame(i), sizeof(digitSlot *));
	*(digitSlot **)layer_get_data(s->layer) = s;

	layer_set_update_proc(s->layer, update_slot);
	layer_add_child(parent, s->layer);
}

static void deinit_slot(uint8_t i) {
	layer_destroy(slot[i].layer);
}

static void animate_digits(struct Animation *anim, const AnimationProgress normTime) {
	for (uint8_t i=0; i < CONST_NUM_SLOTS; i++) {
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

static void setup_ui() {
  window_set_background_color(window, state.background_color);
	window_stack_push(window, true);

	Layer *rootLayer = window_get_root_layer(window);

	for (uint8_t i=0; i < CONST_NUM_SLOTS; i++) {
		init_slot(i, rootLayer);
	}

	animImpl.setup = NULL;
	animImpl.update = animate_digits;
	animImpl.teardown = destroy_animation;

	setup_animation();

  // Choose animation start delay according to settings
  if (state.contrastmode) {
    app_timer_register(0, handle_timer, NULL);
  } else if (prefs.quick_start) {
    app_timer_register(700, handle_timer, NULL);
  } else {
    app_timer_register(2000, handle_timer, NULL);
  }
}

static void teardown_ui() {
	for (uint8_t i=0; i < CONST_NUM_SLOTS; i++) {
		deinit_slot(i);
	}

	animation_destroy(anim);
}

static void battery_handler(BatteryChargeState charge_state) {
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

  teardown_ui();
  setup_ui();
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

  setup_ui();

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
  teardown_ui();
  window_destroy(window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
