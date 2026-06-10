#pragma once // The header file will now be used just once during the compiling-process

#include <Adafruit_PWMServoDriver.h> // This is the PCA9685 servo driver with 16 channels

/**
 * This ist the class for creating one Leg-object
 */
class Leg {

// This is where all the public methods are defined
public:
    Leg(Adafruit_PWMServoDriver& board, int ch1, int ch2, int ch3); // The constructor delivers the servo-driver and the needed channels on it for the servos
    void setAngles(float coxa, float femur, float tibia); // This method is a setter-method for the angles of all the 3 servos as PWM-pulses
    static int angleToPulse(float angle); // This is a method to create a PWM-pulse out of degrees
//This is where all the private class-attributes and methods are defined
private:
    Adafruit_PWMServoDriver& _board; // This is the PCA9685 servo driver, for adressing all the different servos
    int _ch1, _ch2, _ch3; // These are the 3 channels on the servo driver for the 3 different servos of one leg
};