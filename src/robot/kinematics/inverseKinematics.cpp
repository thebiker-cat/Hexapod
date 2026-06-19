#include "inverseKinematics.h"

/**
 * This is the calculateAngle1 method the method provides the feature to calculate the first angle (Coxa).
 * It can be used in any file that includes the inverse kinematics test.cpp file.
 *
 * @param yp is the parameter that takes over the coordinate y.
 * @param xp is the parameter that takes over the coordinate x.
 * @return the method returns the value of angle1.
 */
float calculateAngle1(float yp, float xp) {
    return atan2(yp, xp) * 180 / PI;
}

/**
 * This is the calculateAngle2 method the method provides the feature to calculate the second angle (femur).
 * It can be used in any file that includes the inverse kinematics test.cpp file.
 *
 * @param dp is the parameter that takes over the horizontal length from femur to the tip of the leg.
 * @param zp is the parameter that takes over the vertical length from femur to the tip of the leg.
 * @param ap is the parameter that takes over the length form femur to tibia.
 * @param bp is the parameter that takes over the length form tibia to the tip of the leg.
 * @param cp is the parameter that takes over the direct length from femur to the tip of the leg.
 * @return the method returns the value of angle2.
 */
float calculateAngle2(float dp, float zp, float ap, float bp, float cp) {
    return atan2(dp, zp) + acos(((ap * ap) + (cp * cp) - (bp * bp)) / (2 * ap * cp)) * 180 / PI;
}

/**
 * This is the calculateAngle3 method the method provides the feature to calculate the third angle (tibia).
 * It can be used in any file that includes the inverse kinematics test.cpp file.
 *
 * @param ap is the parameter that takes over the length from femur to tibia.
 * @param bp is the parameter that takes over the length from tibia to the tip of the leg.
 * @param cp is the parameter that takes over the direct length from femur to the tip of the leg.
 * @return the method returns the value of angle3.
 */
float calculateAngle3(float ap, float bp, float cp) {
    return acos(((ap * ap) + (bp * bp) - (cp * cp)) / (2 * ap * bp)) * 180 / PI;
}

/**
 * This is the calculateMissingVariables method it provides the feature to calculate the missing variables r, d and c.
 * It can be used in any file that includes the inverse kinematics test.cpp file.
 *
 * @param yp is the parameter that takes over the coordinate y.
 * @param xp is the parameter that takes over the coordinate x.
 * @param zp is the parameter that takes over the vertical length from femur to the tip of the leg.
 * @return the method returns the value of r, d and c in an array.
 */
std::array<float, 3> calculateMissingVariables(float yp, float xp, float zp) {
    float r = sqrt((xp * xp) + (yp * yp));
    float d = r - l;
    float c = sqrt((d * d) + (zp * zp));
    return {r, d, c};
}

/**
 * This is the convertCoordinatesToAngles method it provides the feature to calculate the inverse kinematics.
 *
 * @param xp is the parameter that takes over the coordinate x.
 * @param yp is the parameter that takes over the coordinate y.
 * @param zp is the parameter that takes over the vertical length from femur to the tip of the leg.
 * @return the three different angles (coxa, femur, tibia) in an array.
 */
std::array<float, 3> convertCoordinatesToAngles(float xp, float yp, float zp) {
    auto coordinates = calculateMissingVariables(yp, xp, zp); // getting entered coordinates from the user with an array

    // saving coordinates in different variables
    float r = coordinates[0];
    float d = coordinates[1];
    float c = coordinates[2];

    // The three different calculations für each angle with the conversion from degrees to radians (* 180 / PI).
    const float angle1 = calculateAngle1(yp, xp) * 180 / PI;
    const float angle2 = calculateAngle2(d, -zp, a, b, c) * 180 / PI;
    const float angle3 = calculateAngle3(a, b, c) * 180 / PI;

    return {angle1, angle2, angle3};
}
