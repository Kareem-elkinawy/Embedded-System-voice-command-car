#ifndef LIMIT_SWITCH_DRIVER_H
#define LIMIT_SWITCH_DRIVER_H

#include "pico/stdlib.h"
#include <stdbool.h>

// Your limit switch pin
#define LIMIT_SWITCH_PIN 12


// Setup GPIO + debounce + interrupt
void limit_switch_init(void);

// Returns true once when the ISR fires
bool limit_switch_was_triggered(void);

// Direct read (polling)
bool limit_switch_is_pressed(void);



#endif
