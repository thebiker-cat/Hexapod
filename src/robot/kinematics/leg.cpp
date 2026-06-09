#include "leg.h"
#include <Adafruit_PWMServoDriver.h>

Leg::Leg(Adafruit_PWMServoDriver& board, int ch1, int ch2, int ch3)
    : _board(board), _ch1(ch1), _ch2(ch2), _ch3(ch3) {
}

void Leg::setAngles(float coxa, float femur, float tibia) {

}
