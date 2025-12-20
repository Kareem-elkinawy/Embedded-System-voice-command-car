#include "servo_driver.h"
#include <stdio.h>
#include <stdlib.h>   // <-- required for abs()


static uint pwm_slice_num;

// Initialize servo PWM
void servo_init(void) {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    pwm_slice_num = pwm_gpio_to_slice_num(SERVO_PIN);

    pwm_set_clkdiv(pwm_slice_num, 125.0f); // 125 MHz / 125 = 1 MHz (1 µs per tick)
    pwm_set_wrap(pwm_slice_num, 20000);    // 20 ms period = 50 Hz
    pwm_set_enabled(pwm_slice_num, true);
}

// Convert angle (0–180°) to PWM ticks (500–2500 µs)
static uint16_t angle_to_pwm(uint8_t angle) {
    return 500 + ((uint16_t)angle * 2000) / 180;
}

// Rotate servo to a given angle instantly
void servo_rotate(uint8_t angle) {
    pwm_set_gpio_level(SERVO_PIN, angle_to_pwm(angle));
}

// Smooth rotation from start_angle to target_angle over duration_ms
void servo_rotate_smooth(uint8_t start_angle, uint8_t target_angle, uint32_t duration_ms) {
    int16_t step = (target_angle > start_angle) ? 1 : -1;
    uint8_t angle = start_angle;
    uint32_t steps = abs(target_angle - start_angle);
    if (steps == 0) return;

    uint32_t delay_ms = duration_ms / steps;

    for (uint32_t i = 0; i < steps; i++) {
        angle += step;
        pwm_set_gpio_level(SERVO_PIN, angle_to_pwm(angle));
        sleep_ms(delay_ms);
    }
}

// Predefined reward push animation: rotate 0 → 90 → 0
void servo_push_reward(void) {
    printf("Pushing RFID reward...\n");
    servo_rotate_smooth(0, 90, 2000);   // rotate to 90°
    sleep_ms(500);                       // hold
    servo_rotate_smooth(90, 0, 2000);   // back to 0°
    printf("Reward pushed.\n");
}
