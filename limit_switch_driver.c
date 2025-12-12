#include "limit_switch_driver.h"
#include <stdio.h>

// Internal flag set by ISR
static volatile bool switch_triggered = false;

// Last trigger timestamp (for debounce)
static absolute_time_t last_trigger_time;

// Debounce time (400 ms)
#define LIMIT_SWITCH_DEBOUNCE_US 400000

// ISR callback
static void limit_switch_callback(uint gpio, uint32_t events) {
    absolute_time_t now = get_absolute_time();
    if (absolute_time_diff_us(last_trigger_time, now) < LIMIT_SWITCH_DEBOUNCE_US)
        return;
    last_trigger_time = now;
    switch_triggered = true;
    printf("ISR: Limit switch triggered.\n");
}

// Initialize limit switch
void limit_switch_init(void) {
    gpio_init(LIMIT_SWITCH_PIN);
    gpio_set_dir(LIMIT_SWITCH_PIN, GPIO_IN);
    gpio_pull_up(LIMIT_SWITCH_PIN);  // ACTIVE LOW

    last_trigger_time = get_absolute_time();

    gpio_set_irq_enabled_with_callback(
        LIMIT_SWITCH_PIN,
        GPIO_IRQ_EDGE_FALL,   // trigger when pressed
        true,
        &limit_switch_callback
    );

    printf("Limit switch initialized (pin %d, active LOW).\n", LIMIT_SWITCH_PIN);
}

bool limit_switch_was_triggered(void) {
    if (switch_triggered) {
        switch_triggered = false;
        return true;
    }
    return false;
}

bool limit_switch_is_pressed(void) {
    return !gpio_get(LIMIT_SWITCH_PIN);  // LOW = pressed
}
