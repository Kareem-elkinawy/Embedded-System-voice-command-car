#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Left Motor pins
#define MOTOR_L_IN1 2
#define MOTOR_L_IN2 3
#define MOTOR_L_EN  17   // PWM pin

// Right Motor pins
#define MOTOR_R_IN1 16
#define MOTOR_R_IN2 27

#define MOTOR_R_EN  0  // PWM pin

// Initialize both motors
void motor_init(void);

// Control functions
void motor_forward(uint8_t speed);
void motor_turn_left(uint8_t left_speed, uint8_t right_speed);
void motor_turn_right(uint8_t left_speed, uint8_t right_speed);
void motor_stop(void);

#endif // MOTOR_DRIVER_H
