
#include <Arduino.h>
#include <ESP32Servo.h>

// These are the pin definitions
#define SERVO_PIN 18
#define ANGLE0_BUTTON 25
#define ANGLE90_BUTTON 26
#define ANGLE180_BUTTON 27
#define POT_PIN 34

Servo servo;
int lastPotValue = -1;

/**
 * This is a method to change an angle in degrees into a PWM-pulse format.
 * @param angle , this is the param, which gives degrees as a float.
 * @return returns an int value
 */
int angleToPulse(float angle) {
    return map(angle, 0, 180, 205, 410);
}

/**
 * This is the setAngleWithButtons method. It sets the angle based on which button was pressed.
 * Button 1 = 0°, Button 2 = 90°, Button 3 = 180°
 */
void setAngleWithButtons() {

    if (digitalRead(ANGLE0_BUTTON) == LOW) {
        servo.write(0);
        delay(1000);
    }
    if (digitalRead(ANGLE90_BUTTON) == LOW) {
        servo.write(90);
        delay(1000);
    }
    if (digitalRead(ANGLE180_BUTTON) == LOW) {
        servo.write(180);
        delay(1000);
    }
}

/**
 * The setAngleWithPotentiometer method sets the angle based on the current value of the potentiometer.
 */
void setAngleWithPotentiometer() {
    int currentPotValue = analogRead(POT_PIN);
    int angle = map(currentPotValue, 0, 4095, 0, 180);
    if (currentPotValue != lastPotValue) {
        servo.write(angle);
        lastPotValue = currentPotValue;
        delay(20);
    }
}

void setup() {
    // sets the pinModes
    pinMode(SERVO_PIN, OUTPUT);
    pinMode(ANGLE0_BUTTON, INPUT_PULLUP);
    pinMode(ANGLE90_BUTTON, INPUT_PULLUP);
    pinMode(ANGLE180_BUTTON, INPUT_PULLUP);
    servo.setPeriodHertz(50); // sets the PWM-frequency to 50 Hz
    servo.attach(SERVO_PIN, 500, 2400);
}

void loop() {
    setAngleWithButtons();
    setAngleWithPotentiometer();
}