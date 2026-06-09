#pragma once

#include <Adafruit_PWMServoDriver.h>

class Leg {
public:
    Leg(Adafruit_PWMServoDriver& board, int ch1, int ch2, int ch3);
    void setAngles(float coxa, float femur, float tibia);
private:
    Adafruit_PWMServoDriver& _board;
    int _ch1, _ch2, _ch3;
    int angleToPulse(float angle);
};