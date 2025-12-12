#include "motor_driver.h"

// Initialize PWM for a given pin
static void pwm_init_pin(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice_num, 255);      // 8-bit resolution
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), 0);
    pwm_set_enabled(slice_num, true);
}

// Set PWM speed for a pin
static void pwm_set_speed(uint pin, uint8_t speed) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), speed);
}

// Initialize motor pins
void motor_init(void) {
    // Left motor
    gpio_init(MOTOR_L_IN1);
    gpio_init(MOTOR_L_IN2);
    gpio_set_dir(MOTOR_L_IN1, GPIO_OUT);
    gpio_set_dir(MOTOR_L_IN2, GPIO_OUT);
    pwm_init_pin(MOTOR_L_EN);

    // Right motor
    gpio_init(MOTOR_R_IN1);
    gpio_init(MOTOR_R_IN2);
    gpio_set_dir(MOTOR_R_IN1, GPIO_OUT);
    gpio_set_dir(MOTOR_R_IN2, GPIO_OUT);
    pwm_init_pin(MOTOR_R_EN);

    motor_stop();
}

// Move forward
void motor_forward(uint8_t speed) {
    // Left motor forward
    gpio_put(MOTOR_L_IN1, 1);
    gpio_put(MOTOR_L_IN2, 0);
    pwm_set_speed(MOTOR_L_EN, speed);

    // Right motor forward
    gpio_put(MOTOR_R_IN1, 1);
    gpio_put(MOTOR_R_IN2, 0);
    pwm_set_speed(MOTOR_R_EN, speed);
}

// Turn left (left motor slower, right motor full speed)
void motor_turn_left(uint8_t left_speed, uint8_t right_speed) {
    gpio_put(MOTOR_L_IN1, 1);
    gpio_put(MOTOR_L_IN2, 0);
    pwm_set_speed(MOTOR_L_EN, left_speed);

    gpio_put(MOTOR_R_IN1, 1);
    gpio_put(MOTOR_R_IN2, 0);
    pwm_set_speed(MOTOR_R_EN, right_speed);
}

// Turn right (right motor slower, left motor full speed)
void motor_turn_right(uint8_t left_speed, uint8_t right_speed) {
    gpio_put(MOTOR_L_IN1, 1);
    gpio_put(MOTOR_L_IN2, 0);
    pwm_set_speed(MOTOR_L_EN, left_speed);

    gpio_put(MOTOR_R_IN1, 1);
    gpio_put(MOTOR_R_IN2, 0);
    pwm_set_speed(MOTOR_R_EN, right_speed);
}

// Stop both motors
void motor_stop(void) {
    gpio_put(MOTOR_L_IN1, 0);
    gpio_put(MOTOR_L_IN2, 0);
    pwm_set_speed(MOTOR_L_EN, 0);

    gpio_put(MOTOR_R_IN1, 0);
    gpio_put(MOTOR_R_IN2, 0);
    pwm_set_speed(MOTOR_R_EN, 0);
}
