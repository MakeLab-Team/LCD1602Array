#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "PwmOutput.h"
#include "PwmDriverPin.h"
#include "BuiltInHwPwmPin.h"

const uint8_t rs = 12;

const uint8_t d4 = 5;
const uint8_t d5 = 4;
const uint8_t d6 = 3;
const uint8_t d7 = 2;
constexpr size_t groups = 6;
constexpr size_t rows = 9;
constexpr size_t cols = 4;
const int lcdEn[groups] = {7, 8, A1, A2, A3, A4};
const uint8_t test_pin = 13;
const uint8_t test_select_pin = 13;

uint8_t backlight_pin[cols] = {6, 9, 10, 11}; 

LiquidCrystal *lcd_group[groups];


Adafruit_PWMServoDriver pwm_driver0 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm_driver1 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver *p_pwm_driver[2] = {&pwm_driver0, &pwm_driver1};

PwmOutput *pBacklight[rows][cols];
bool test_mode = true; // TODO: change to false;

void test_setup();
void test_loop();
void normal_setup();
void normal_loop();

void setup() {
  pinMode(test_pin, INPUT_PULLUP);
  if(analogRead(test_pin) == LOW) {
    test_mode = true;
  }
  Serial.begin(9600);
  for (size_t i=0; i<groups; i++) {
    lcd_group[i] = new LiquidCrystal(rs, lcdEn[i], d4, d5, d6, d7);
    lcd_group[i]->begin(16, 2);
    lcd_group[i]->clear();
  }
  pwm_driver0.begin();
  pwm_driver1.begin();
  pwm_driver0.setPWMFreq(1600);
  for (size_t i=0; i<4; i++) {
    pinMode(backlight_pin[i], OUTPUT);
  }
  for (size_t i=0; i<groups; i++) {
    pinMode(lcdEn[i], OUTPUT);
  }

  for (size_t c=0; c<cols; c++) {
    for (size_t r=0; r<8; r++) {
      pBacklight[r][c] = new PwmDriverPin(*p_pwm_driver[r/2], static_cast<uint8_t>((c%2)*8 + r));
    }
  }

  if (test_mode) {
    test_setup();
  } else {
    normal_setup();
  }
}

void normal_setup() {}
void normal_loop() {}

void test_setup() {
  for (size_t i=0; i<groups; i++) {
    lcd_group[i]->print('J' + i / 3);
    lcd_group[i]->print('0' + i % 3);
    lcd_group[i]->print("  |  ");
    lcd_group[i]->print('W' + i / 3);
    lcd_group[i]->print("/");
    lcd_group[i]->print('E' + i / 3);
    lcd_group[i]->print(" ");
    lcd_group[i]->print('0' + i % 3);
    lcd_group[i]->print("/");
    lcd_group[i]->print('3' + i % 3);
    lcd_group[i]->print("/");
    lcd_group[i]->print('6' + i % 3);
  }
}

void all_on() {
  for (size_t c=0; c<cols; c++) {
    for (size_t r=0; r<rows; r++) {
      pBacklight[r][c]->setValue(1.0);
    }
  }
}

void row_on(size_t row) {
  for (size_t c=0; c<cols; c++) {
    for (size_t r=0; r<rows; r++) {
      pBacklight[r][c]->setValue(r==row ? 1.0 : 0.0);
    }
  }
}

void col_on(size_t col) {
  for (size_t c=0; c<cols; c++) {
    for (size_t r=0; r<rows; r++) {
      pBacklight[r][c]->setValue(c==col ? 1.0 : 0.0);
    }
  }
}

void wave_all() {
  constexpr unsigned int period = 0x400; // must be a power of 2
  unsigned int t = static_cast<unsigned int>(millis());
  unsigned int in_phase = t & (period - 1);
  unsigned int phase = ((t & period) == 0 ? 0 : 1);
  for (size_t c=0; c<cols; c++) {
    for (size_t r=0; r<rows; r++) {
      pBacklight[r][c]->setValue((c+r)%2 == phase ? in_phase : 1.0 - in_phase);
    }
  }
}

void test_loop() {
  constexpr int mode_all_on_begin = 0;
  constexpr int mode_all_on_end = mode_all_on_begin + 1;
  constexpr int mode_row_on_begin = mode_all_on_end;
  constexpr int mode_row_on_end = mode_row_on_begin + rows;
  constexpr int mode_col_on_begin = mode_row_on_end;
  constexpr int mode_col_on_end = mode_col_on_begin + cols;
  constexpr int mode_wave_all_begin = mode_col_on_end;
  constexpr int mode_wave_all_end = mode_wave_all_begin + 1;
  constexpr int modes_num = mode_wave_all_end;

  delay(2); // wait for ADC to settle
  int knob_val = analogRead(test_select_pin);
  int mode = map(knob_val, 0, 1023, 0, modes_num - 1);
  if (mode == mode_all_on_begin) {
    all_on();
  } else if (mode < mode_row_on_end) {
    row_on(mode - mode_row_on_begin);
  } else if (mode < mode_col_on_end) {
    col_on(mode - mode_col_on_begin);
  } else if (mode < mode_wave_all_end) {
    wave_all();
  }
}


void loop() {
  if (test_mode) {
    test_loop();
  } else {
    normal_loop();
  }
}

