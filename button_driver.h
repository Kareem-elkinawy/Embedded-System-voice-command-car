#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

#include "pico/stdlib.h"
#include <stdbool.h>

// Pin connected to the push button
#define BUTTON_PIN 1

// Initializes the push button GPIO
void button_init(void);

// Returns true if the button is pressed, false otherwise
bool button_is_pressed(void);

#endif // BUTTON_DRIVER_H
