#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "kinematics/leg.h"

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41);

Leg frontLeft(board1, 0, 1, 2);
Leg frontRight(board1, 3, 4, 5);
Leg midLeft(board1, 6, 7, 8);
Leg midRight(board2, 0, 1, 2);
Leg backLeft(board2, 3, 4, 5);
Leg backRight(board2, 6, 7, 8);

void setup() {
    board1.begin();
    board1.setPWMFreq(50);
    board2.begin();
    board2.setPWMFreq(50);
}

void loop() {

}