#pragma once

#ifdef RGB_MATRIX_ENABLE

static uint16_t key_timer;
static uint32_t elapsed_time = 0;
static void refresh_rgb(void);
static void check_rgb_timeout(void);
bool is_rgb_timeout = false;

void refresh_rgb() {
  key_timer = timer_read();
  elapsed_time = 0;
  if (is_rgb_timeout) {
    is_rgb_timeout = false;
    oled_on();
    rgb_matrix_enable_noeeprom();
  }
}

void check_rgb_timeout() {
  uint16_t current_time = timer_read();
  if (current_time < key_timer) {
    elapsed_time += (65535 - key_timer) + current_time;
  } else {
    elapsed_time += timer_elapsed(key_timer);
  }
  key_timer = current_time;

  if (!is_rgb_timeout && elapsed_time > RGBLIGHT_TIMEOUT) {
    oled_off();
    rgb_matrix_disable_noeeprom();
    is_rgb_timeout = true;
  }
}

void housekeeping_task_user(void) {
  #ifdef RGBLIGHT_TIMEOUT
  check_rgb_timeout();
  #endif
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef RGBLIGHT_TIMEOUT
  if (record->event.pressed) refresh_rgb();
  #endif
}

void post_encoder_update_user(uint8_t index, bool clockwise) {
  #ifdef RGBLIGHT_TIMEOUT
  refresh_rgb();
  #endif
}

#endif //RGB_MATRIX_ENABLE
