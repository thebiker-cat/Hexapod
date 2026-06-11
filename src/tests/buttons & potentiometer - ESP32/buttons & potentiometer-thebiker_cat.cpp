#include <Arduino.h>
#include <ESP32Servo.h> // This is a library for the ESP32 to control the servo directly


#define SERVO_PIN 18 // This is where the data pin of the servo ist being connected.
#define ANGLE0_BUTTON 25 // With this button, the angle of the servo can be set to 0 degrees.
#define ANGLE90_BUTTON 26 // With this button, the angle of the servo can be set to 90 degrees.
#define ANGLE180_BUTTON 27 // With this button, the angle of the servo can be set to 180 degrees.
#define POT_PIN 34 // This is the adc pin to read the input of the potentiometer.

Servo servo; // This is the servo, that is connected directly to the ESP32.
int lastPotValue = -1; // This variable is being used to detect changes from the potentiometer input.

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
    int currentPotValue = analogRead(POT_PIN); // This variable always saves the current potentiometer value.
    int angle = map(currentPotValue, 0, 4095, 0, 180); // With this map method the input of the potentiometer ist being changed from 0 to 4095 --> 0, 180.
    if (currentPotValue != lastPotValue) { // If the potentiometer input has changed.
        servo.write(angle); // The servo writes the new angle.
        lastPotValue = currentPotValue; // The last value is being changed, so the loop can react to changes again for the next changes.
        delay(20);
    }
}

void setup() {
    // sets the pinModes
    pinMode(SERVO_PIN, OUTPUT);
    pinMode(ANGLE0_BUTTON, INPUT_PULLUP);
    pinMode(ANGLE90_BUTTON, INPUT_PULLUP);
    pinMode(ANGLE180_BUTTON, INPUT_PULLUP);
    servo.setPeriodHertz(50); // Sets the PWM-frequency to 50 Hz so it sends 50 signals per second.
    servo.attach(SERVO_PIN); //  I am personally not sure if you need to restrict the PWM levels, because we are working with degrees here.
}

void loop() {
    setAngleWithButtons(); // Reacts to button inputs.
    setAngleWithPotentiometer(); // Reacts to potentiometer inputs.
}