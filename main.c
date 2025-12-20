#include "pico/stdlib.h"
#include <stdio.h>

#include "button_driver.h"
#include "limit_switch_driver.h"
#include "led_driver.h"
#include "buzzer_driver.h"
#include "motor_driver.h"
#include "servo_driver.h"

// Motor speeds
#define MOTOR_FULL_SPEED 255
#define MOTOR_SLOW_SPEED 0

// -------- Serial input functions --------
// Non-blocking read from USB serial
char get_serial_input_nonblocking() {
    int c = getchar_timeout_us(0);
    return (c == PICO_ERROR_TIMEOUT) ? 0 : (char)c;
}

// Blocking read from USB serial (used for activation)
char get_serial_input() {
    int c = getchar_timeout_us(1000000); // 1s timeout
    return (c == PICO_ERROR_TIMEOUT) ? 0 : (char)c;
}

int main() {
    stdio_init_all();
    sleep_ms(3000);

    // Initialize drivers
    button_init();
    limit_switch_init();
    led_init();
    buzzer_init();
    motor_init();
    servo_init();

    printf("Robot system initialized.\n");

    while (true) {
        
        while(1){
            if(button_is_pressed()){
            led_set_color(LED_RED);
            break;
        }
        }

        // -------- WAIT FOR ACTIVATION --------
        printf("Press button or say 'Go Robot!' to activate...\n");
            while (1) {
                    if (get_serial_input() == 'G') {
                        led_set_color(LED_GREEN);
                        printf("System Activated!\n");
                        break;
                    } else{
                        buzzer_error_pattern();
                    }
                    sleep_ms(20);
                
            }
        

        // -------- COMMAND LOOP --------
        while (1) {

            // ## CHECK LIMIT SWITCH
            if (limit_switch_was_triggered()) {
                printf("LIMIT SWITCH ACTIVATED! Stopping motor & pushing reward.\n");

                motor_stop();
                led_set_color(LED_BLUE);
                servo_push_reward();
                led_set_color(LED_OFF);

                break;  // back to waiting mode
            }

            // ## READ VOICE COMMANDS FROM SERIAL (non-blocking)
            char cmd = get_serial_input_nonblocking();
            if (cmd != 0) {
                switch (cmd) {
                    case 'W':  // Forward
                        printf("Forward\n");
                        motor_forward(MOTOR_FULL_SPEED);
                        break;

                    case 'A':  // Turn Left
                        printf("Left\n");
                        motor_turn_left(MOTOR_SLOW_SPEED, MOTOR_FULL_SPEED);
                        break;

                    case 'D':  // Turn Right
                        printf("Right\n");
                        motor_turn_right(MOTOR_FULL_SPEED, MOTOR_SLOW_SPEED);
                        break;

                    case 'S':  // Stop
                        printf("Stop\n");
                        motor_stop();
                        break;

                    default:
                        printf("Unknown command: %c\n", cmd);
                        break;
                }
            }

            sleep_ms(50);  // slower loop to reduce serial spam & debounce
        }
    }

    return 0;
}
