#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "pico/stdlib.h"  

// RGB LED pins
#define LED_RED_PIN   9
#define LED_GREEN_PIN 8
#define LED_BLUE_PIN  7

// LED colors
typedef enum {
    LED_OFF,
    LED_RED,
    LED_GREEN,
    LED_BLUE,
} LEDColor;

// Initialize LED pins
void led_init(void);

// Set LED color
void led_set_color(LEDColor color);

#endif // LED_DRIVER_H
