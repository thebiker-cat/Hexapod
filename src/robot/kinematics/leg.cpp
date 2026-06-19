#include "leg.h" // This is the header file, which includes the Leg class
#include <Adafruit_PWMServoDriver.h> // This is the PCA9685 servo driver with 16 channels

/**
 * This is the constructor of a leg object, which sets a PCA9685 servo driver and 3 channels for the 3 motors of one leg, which
 * are on this board as the class attributes.
 *
 * @param board , this is the PCA9685 servo driver, which has 16 PWM channels on it
 * @param ch1 , this is the channel for the coxa - servo
 * @param ch2 , this is the channel for the femur - servo
 * @param ch3 , this is the channel for the tibia - servo
 */
Leg::Leg(Adafruit_PWMServoDriver& board, int ch1, int ch2, int ch3)
    : _board(board), _ch1(ch1), _ch2(ch2), _ch3(ch3) { // this is a list for setting all the class attributes immediately
}

/**
 * This is a method to set the different coordinates of a leg.
 *
 * @param yp is the parameter that takes over the coordinate y.
 * @param xp is the parameter that takes over the coordinate x.
 * @param zp is the parameter that takes over the vertical length from femur to the tip of the leg.
 */
void Leg::setCoordinates(float x, float y, float z) {

    auto angles = convertCoordinatesToAngles(x, y, z);

    float angle1 = angles[0];
    float angle2 = angles[1];
    float angle3 = angles[2];

    setAngles(angle1, angle2, angle3);
}

/**
 * This is a methode to set the different angles of the 3 servo motors on each leg.
 * The angles are being transformed in pulses (angleToPulse), because the servo works with PWM pulses.
 *
 * @param coxa , this is the param to control the coxa angle of the servo, which is the angle between the body and the first segment of the leg.
 * @param femur , this is the param to control the femur angle of the servo, which ist the angle between the first and second segment of the leg.
 * @param tibia , this is the param to control the tibia angle of the servo, which ist the angle between the second and third segment of the leg.
 */
void Leg::setAngles(float coxa, float femur, float tibia) {
    // _board is the class-attribute for the Servo-Driver
    _board.setPWM(_ch1, 0, angleToPulse(coxa));
    _board.setPWM(_ch2, 0, angleToPulse(femur));
    _board.setPWM(_ch3, 0, angleToPulse(tibia));

}

/**
 * This is a method to change an angle in degrees into a PWM-pulse format.
 *
 * @param angle, this is the param, which gives degrees as a float.
 * @return returns an int value
 */
int Leg::angleToPulse(float angle) {
    return map(angle, 0, 180, 102, 512); // 0° --> 102 ticks, 180° --> 512 ticks
}