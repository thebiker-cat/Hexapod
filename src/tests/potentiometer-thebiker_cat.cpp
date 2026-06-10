#include <Arduino.h>
#include <ESP32Servo.h>
#include "robot/kinematics/leg.h"

#define SERVO_PIN 2

Servo servo;


void setup() {
    servo.setPeriodHertz(50);
    servo.attach(SERVO_PIN, 0, 2400);
    servo.write(90);
}

void loop() {
    //Leg::angleToPulse();
    servo.write(0);
    delay(1000);
    servo.write(180);
}