#include <Arduino.h>
#include <ESP32Servo.h>
#include <robot/kinematics/leg.h>
#define potentiometer_pin 26
#define servo_pin 2

Servo servo = Servo();

void setup() {
    pinMode(potentiometer_pin, INPUT);
    servo.setPeriodHertz(50);
    servo.attach(servo_pin);
}

float readDegrees() {
    float degrees = map(analogRead(potentiometer_pin), 0, 4096, 0, 180);
    return degrees;
}

void loop() {
    servo.write(Leg::angleToPulse(readDegrees()));
}
