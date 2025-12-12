#include "buzzer_driver.h"

void buzzer_init(void) {
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0);  // Buzzer off initially
}

void buzzer_beep(uint8_t times, uint16_t duration_ms) {
    for (uint8_t i = 0; i < times; i++) {
        gpio_put(BUZZER_PIN, 1);  // Buzzer ON
        sleep_ms(duration_ms);
        gpio_put(BUZZER_PIN, 0);  // Buzzer OFF
        sleep_ms(duration_ms);
    }
}

void buzzer_error_pattern(void) {
    buzzer_beep(3, 150);  // 3 short pulses for error feedback
}
