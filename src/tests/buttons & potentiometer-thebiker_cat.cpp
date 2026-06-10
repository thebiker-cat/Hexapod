#include <Arduino.h>
#include <ESP32Servo.h>

#define SERVO_PIN 18
#define ANGLE0_BUTTON 25
#define ANGLE90_BUTTON 26
#define ANGLE180_BUTTON 27
#define POT_PIN 34

Servo servo;
int lastPotValue = -1;

int angleToPulse(float angle) {
    return map(angle, 0, 180, 205, 410);
}

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
    pinMode(SERVO_PIN, OUTPUT);
    pinMode(ANGLE0_BUTTON, INPUT_PULLUP);
    pinMode(ANGLE90_BUTTON, INPUT_PULLUP);
    pinMode(ANGLE180_BUTTON, INPUT_PULLUP);
    servo.setPeriodHertz(50);
    servo.attach(SERVO_PIN, 500, 2400);
}

void loop() {
    setAngleWithButtons();
    setAngleWithPotentiometer();
}