#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Pin connected to the servo
#define SERVO_PIN 6

// Initialize servo PWM
void servo_init(void);

// Rotate servo to a specific angle (0–180°)
void servo_rotate(uint8_t angle);

// Smoothly rotate servo from start_angle to target_angle over duration_ms
void servo_rotate_smooth(uint8_t start_angle, uint8_t target_angle, uint32_t duration_ms);

// Rotate servo to push the reward (predefined animation)
void servo_push_reward(void);

#endif // SERVO_DRIVER_H
