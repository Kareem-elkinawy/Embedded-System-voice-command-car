# Embedded-System-voice-command-car
A mini car that moves using voice commands "forward",  "Left", "Right", "Stop" and when the car presses a limit switch it triggers a servo motor that opens a box

Required installments:
1. pyserial==3.5
2. vosk==0.3.45
3. pyaudio==0.2.11


Aether-Forge Protocol - Voice-Controlled Robot System 

A voice-controlled logistics robot built on Raspberry Pi Pico that navigates a maze, responds to voice 
commands, and dispenses rewards upon completion. 

System Overview:

This embedded system implements a voice-activated robot with the following features: 
1. Voice activation using "Go Robot!" command 
2. Real-time navigation via voice commands (Forward, Left, Right, Stop) 
3. Automatic reward dispensing when limit switch is triggered 
4. Audio and visual feedback through buzzer and RGB LED 
5. Parallel processing of voice input and motor control 

## ============================================================================== ##
Hardware Requirements:

1. Raspberry Pi Pico 
2. DC Motor pair with H-Bridge driver (L298N or similar) 
3. Servo motor (for reward mechanism) 
4. RGB LED (common cathode) 
5. Buzzer 
6. Push button 
7. Limit switch 
8. Microphone module or Microphone of PC (connected to PC via USB) 
9. USB cable for serial communication 
## ============================================================================== ##
Software Requirements:

1. Embedded System (Pico) 
2. Pico SDK 
3. CMake (3.13 or higher) 
4. ARM GCC compiler 
5. Standard C libraries 
6. Voice Recognition (PC) 
7. Python 3.7+ 
## ============================================================================== ##
Required packages: 

bash  pip install pyserial pyaudio vosk 

Installation: 
1. Pico Firmware Setup 
    1. bash# Clone the Pico SDK (if not already installed) 
    2. git clone https://github.com/raspberrypi/pico-sdk.git 
    3. cd pico-sdk 
    4. git submodule update --init 
    # Set SDK path 
    5. export PICO_SDK_PATH=/path/to/pico-sdk 
    # Build the project 
    6. mkdir build && cd build 
    7. cmake .. 
    8. make 
    Flash the generated .uf2 file to your Pico by: 
    9. Hold BOOTSEL button while connecting Pico to PC 
    10. Copy robot_system.uf2 to the mounted drive 
    Pico will reboot automatically 
2. Voice Recognition Setup 
    Download Vosk Model: 
    1. bash# Download the English language model 
    2. wget https://alphacephei.com/vosk/models/vosk-model-small-en-us-0.15.zip 
    3. unzip vosk-model-small-en-us-0.15.zip 
    4. Place the extracted folder in the same directory as voice_commands.py. 
    Configure Serial Port: 
    5. Edit voice_commands.py line 8: 
    pythonser = serial.Serial('COM4', 115200, timeout=1)  # Windows 
    # or 
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)  # Linux 
    Find your port: 
    Windows: Check Device Manager → Ports (COM & LPT) 
    Linux: Run ls /dev/tty* and look for /dev/ttyACM0 or /dev/ttyUSB0 
    macOS: Run ls /dev/tty.* and look for /dev/tty.usbmodem* 
## ============================================================================== ##
Pin Configuration:

Update the following in your header files if needed: 
c// button_driver.h 
#define BUTTON_PIN 1 

// limit_switch_driver.h 
#define LIMIT_SWITCH_PIN 22 

// led_driver.h 
#define LED_RED_PIN 9 
#define LED_GREEN_PIN 8 
#define LED_BLUE_PIN 7 

// buzzer_driver.h 
#define BUZZER_PIN 10 

// motor_driver.h 
#define MOTOR_L_EN 4    // Left motor PWM 
#define MOTOR_L_IN1 2   // Left motor direction 
#define MOTOR_L_IN2 3 
#define MOTOR_R_EN 0    // Right motor PWM 
#define MOTOR_R_IN1 16   // Right motor direction 
#define MOTOR_R_IN2 27 

// servo_driver.h 
#define SERVO_PIN 15 
## ======================================================================== ##
Running the System:

1. Start the Pico Robot 
Connect Pico to PC via USB 
Press the physical push button on the robot 
Wait for LED to turn RED (system ready) 
Serial monitor should show: " say 'Go Robot!' to activate..." 
2. Start Voice Recognition 
bashpython voice_commands.py 
``` 
You should see: 
``` 
Listening for commands... 
3. Activate the Robot 
Say "Go Robot!" clearly into the microphone. The system will: 
LED turns GREEN 
Serial prints: "System Activated!" 
Robot enters command mode 
4. Control the Robot 
Use these voice commands: 
"Forward" or "Go Forward" → Move forward at full speed 
"Left" → Turn le (differen al steering) 
"Right" → Turn right (differen al steering) 
"Stop" → Stop all motors 
5. Reward Sequence 
When the robot reaches the maze end: 
Limit switch triggers automatically 
Motors stop immediately 
LED turns BLUE 
Servo pushes RFID tag (0° → 90° → 0° over 4.5 seconds) 
System returns to activation waiting state
 
Voice Command Mapping 
Voice Phrase Serial Code Robot Action 
"go robot" G Activate system  
"forward" / "go forward"  W Move forward (speed 64) 
"left" A Turn left (L:36, R:64) 
"right" D Turn right (L:64, R:36) 
"stop" S Stop motors 
## ======================================================================== ##
Troubleshooting:

Voice Recognition Issues 
Problem: Commands not recognized 
Check microphone connection and permissions 
Verify Vosk model is in correct directory 
Test with print(text) to see raw recognition output 
Speak clearly and at moderate pace 
Problem: Wrong serial port 
python# Test connection 
python -c "import serial; print(serial.Serial('COM4'))" 
``` 

## Robot Issues:

**Problem**: Robot doesn't respond to activation - Check serial connection (baud rate: 115200) - Verify button press turns LED RED - Open serial monitor to see debug messages 
**Problem**: Motors not moving - Check motor connections and power supply - Verify PWM pins are correctly configured - Test motor speed values (0-255 range) 
**Problem**: Servo not working - Ensure 5V power supply is adequate (servos draw significant current) - Check PWM frequency (should be 50Hz for standard servos) - Verify servo is connected to correct pin 
 
**Problem**: Limit switch not triggering - Check switch wiring (active LOW configuration) - Test with `limit_switch_is_pressed()` in debug mode - Verify 400ms debounce isn't filtering out real presses 

## ======================================================================== ##


## System Architecture 
``` 
┌─────────────────┐         ┌──────────────────┐ 
│   PC (Python)   │  USB    │  Pico (C/C++)    │ 
│                 │◄────────┤                  │ 
│ • Vosk Model    │ Serial  │ • Motor Control  │ 
│ • PyAudio       │         │ • Servo Control  │ 
│ • Command Map   │         │ • GPIO Drivers   │ 
└─────────────────┘         └──────────────────┘ 
                                     │ 
                    ┌────────────────┼────────────────┐ 
                    │                │                │ 
              ┌─────▼─────┐   ┌─────▼─────┐   ┌─────▼─────┐ 
              │  Motors   │   │   Servo   │   │  Sensors  │ 
              │  (DC x2)  │   │           │   │ • Bu on   │ 
              └───────────┘   └───────────┘   │ • Limit   │ 
                                              │ • LED/Buzz│ 
                                              └───────────┘ 
## ======================================================================== ##

``` 
## Code Structure 
``` 

├── main.c                      
├── button_driver.c/h           
├── limit_switch_driver.c/h     
├── led_driver.c/h              
├── buzzer_driver.c/h           
├── motor_driver.c/h            
├── servo_driver.c/h            
├── PYTHON_MIC 
├── voice_commands.py           
└── CMakeLists.txt 
# Main control loop 
# Push button initialization 
# RGB LED control 
# Buzzer patterns 
# DC motor PWM control 
# Servo positioning and smooth rotation        
# Voice recognition and serial interface 
# Build configuration 

## ======================================================================== ##

Safety Notes:

Ensure adequate power supply for motors (typically 6-12V separate from Pico) 
Use current-limiting resistors for LEDs (220Ω recommended) 
Don't exceed servo torque limits when pushing rewards 
Test in open space before maze navigation 
Credits 
Course: CSEN701 - Embedded System Architectures 
Institution: German University in Cairo (GUC) 
Faculty: Media Engineering and Technology 
Challenge: The "Aether-Forge Protocol" 