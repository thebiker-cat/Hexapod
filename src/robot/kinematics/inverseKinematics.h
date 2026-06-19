#pragma once
#include <Arduino.h>
#include <math.h>
#include <array>

const float a = 60.0; // This is the length from femur to tibia the length is final, because it never changes, except one use another model then one must change the value.
const float b = 103.0; // This is the length from tibia to the tip of the leg the length is final, because it never changes, except one use another model then one must change the value.
const float l = 33.0; // This is the coxa offset so the length from coxa to femur. It is final because it never changes, except one use another model then on mus change the value.

// method configurations
float calculateAngle1(float yp, float xp);
float calculateAngle2(float dp, float zp, float ap, float bp, float cp);
float calculateAngle3(float ap, float bp, float cp);
std::array<float, 3> calculateMissingVariables(float yp, float xp, float zp);
std::array<float, 3> convertCoordinatesToAngles(float x, float y, float z);
