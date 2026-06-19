#include <Arduino.h>
#include "robot/kinematics/leg.h"
#include "robot/kinematics/inverseKinematics.h"
#include <array>
#include <ios>

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41);

// These are all 6 legs defined with the different channels and boards their servos are on, so they can be adressed
Leg frontLeft(board1, 0, 1, 2);
Leg frontRight(board1, 3, 4, 5);
Leg midLeft(board1, 6, 7, 8);
Leg midRight(board2, 0, 1, 2);
Leg backLeft(board2, 3, 4, 5);
Leg backRight(board2, 6, 7, 8);


/**
 * This is the oneLegMoveForward method it provides the feature to move one leg in a direction with coordinates.
 *
 * @param leg is the Parameter that takes over the current leg object.
 */
void oneLegMoveForward(Leg leg) {
    leg.setCoordinates(80, 30, -50);
    delay(500);
    leg.setCoordinates(80, 80, -50);
    delay(500);
    leg.setCoordinates(80, 80, -80);
    delay(500);
    leg.setCoordinates(80, 30, -80);
    delay(500);
}

/**
 * This is the walkHexapod method it provides the feature to let the Hexapod walk in the tripod gait.
 */
void walkHexapod() {
    oneLegMoveForward(frontLeft);
    oneLegMoveForward(midRight);
    oneLegMoveForward(backLeft);
    delay(500);

    oneLegMoveForward(frontRight);
    oneLegMoveForward(midLeft);
    oneLegMoveForward(backRight);
    delay(500);
}

/**
 * This is the setStartPosition method it provides the feature to set a default position of the 6 Hexapod legs.
 *
 * @param xp is the parameter that takes over the coordinate x.
 * @param yp is the parameter that takes over the coordinate y.
 * @param zp is the parameter that takes over the vertical length from femur to the tip of the leg.
 */
void setStartPosition(float xp, float yp, float zp) {
    frontLeft.setCoordinates(xp, yp, zp);
    frontRight.setCoordinates(xp, yp, zp);
    midLeft.setCoordinates(xp, yp, zp);
    midRight.setCoordinates(xp, yp, zp);
    backLeft.setCoordinates(xp, yp, zp);
    backRight.setCoordinates(xp, yp, zp);
}

void setup() {
    board1.begin(); // starts the first servo-driver
    board1.setPWMFreq(50); //sets the PWM-frequency of the first servo-driver to 50 Hz
    board2.begin(); // starts the second servo-driver
    board2.setPWMFreq(50); //sets the PWM-frequency of the second servo-drover to 50 Hz

    setStartPosition(80, 30, -80); // sets the default start position
    delay(500);
}

void loop() {
    walkHexapod(); // lets the Hexapod walk
}