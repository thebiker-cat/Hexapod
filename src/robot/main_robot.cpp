#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h> // This includes the library for the servo driver
#include "kinematics/leg.h" // This includes the library for creating a LEG-object

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40); // first servo driver for the first 3 legs (9 servos)
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41); // second servo driver for the last 3 legs (9 servos)

// These are all 6 legs defined with the different channels and boards their servos are on, so they can be adressed
Leg frontLeft(board1, 0, 1, 2);
Leg frontRight(board1, 3, 4, 5);
Leg midLeft(board1, 6, 7, 8);
Leg midRight(board2, 0, 1, 2);
Leg backLeft(board2, 3, 4, 5);
Leg backRight(board2, 6, 7, 8);

void setup() {
    board1.begin(); // starts the first servo-driver
    board1.setPWMFreq(50); //sets the PWM-frequency of the first servo-driver to 50 Hz
    board2.begin(); // starts the second servo-driver
    board2.setPWMFreq(50); //sets the PWM-frequency of the second servo-drover to 50 Hz
}

void loop() {

}