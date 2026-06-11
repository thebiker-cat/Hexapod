#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <robot/kinematics/leg.cpp> // This include is used, so the angleToPulse method can be used.

#define potentiometer_pin 26 // This is the adc pin for reading inputs of the potentiometer.

const int channel = 0; // This is the channel the servo is being accessed from.

float degree = 0; // This is the variable used to save the degrees of the servo motor temporary, because they will be transformed into a pulse.

unsigned int pulse = 0; // This variable is used to set a PWM Pulse for the servo motor.

Adafruit_PWMServoDriver board = Adafruit_PWMServoDriver(0x40); // This is the board, where all the servos can be mounted on.


/**
 * This method is being used to transform any degrees from 0 to 180 degrees into a format, that can be used as a PWM frequency.
 */
void setPulse() {
    degree = map(analogRead(potentiometer_pin), 0, 4095, 0, 180);
    pulse = Leg::angleToPulse(degree);
}

void setup() {
    pinMode(potentiometer_pin, INPUT);
    board.begin(); // This is essential for setting up the board to be able to access it.
    board.setPWMFreq(50); // This means that the ESP32 sends a signal to the servo 50 times a second.
}

void loop() {
    setPulse(); // To be able to set a new angle on the servo motor, the pulse has to be calculated every time.
    board.setPWM(channel, 0, pulse); // With this command you can set a PWM on one of the 16 channels on the driver board.
}

