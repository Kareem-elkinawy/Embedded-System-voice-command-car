#include "led_driver.h"

// Initialize RGB LED pins as output and turn them off
void led_init(void) {
    gpio_init(LED_RED_PIN);
    gpio_init(LED_GREEN_PIN);
    gpio_init(LED_BLUE_PIN);
    
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    
    led_set_color(LED_OFF);
}

// Set the RGB LED to a specific color
void led_set_color(LEDColor color) {
    switch (color) {
        case LED_RED:
            gpio_put(LED_RED_PIN, 1);
            gpio_put(LED_GREEN_PIN, 0);
            gpio_put(LED_BLUE_PIN, 0);
            break;
        case LED_GREEN:
            gpio_put(LED_RED_PIN, 0);
            gpio_put(LED_GREEN_PIN, 1);
            gpio_put(LED_BLUE_PIN, 0);
            break;
        case LED_BLUE:
            gpio_put(LED_RED_PIN, 0);
            gpio_put(LED_GREEN_PIN, 0);
            gpio_put(LED_BLUE_PIN, 1);
            break;
        default: // LED_OFF
            gpio_put(LED_RED_PIN, 0);
            gpio_put(LED_GREEN_PIN, 0);
            gpio_put(LED_BLUE_PIN, 0);
            break;
    }
}
