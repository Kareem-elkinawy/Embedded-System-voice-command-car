#ifndef BUZZER_DRIVER_H
#define BUZZER_DRIVER_H

#include "pico/stdlib.h"

// Pin connected to the buzzer
#define BUZZER_PIN 10

// Initialize the buzzer pin
void buzzer_init(void);

// Beep the buzzer a certain number of times with a specific duration
void buzzer_beep(uint8_t times, uint16_t duration_ms);

// Predefined short error pattern for incorrect activation
void buzzer_error_pattern(void);

#endif // BUZZER_DRIVER_H
