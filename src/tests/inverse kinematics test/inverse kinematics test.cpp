#include <Arduino.h>
#include <array>
#include <math.h> // include math library for equations for example for cos and tan and especially for tan2
#include "robot/kinematics/leg.cpp" // include leg file so one can use the setAngles method

Adafruit_PWMServoDriver board = Adafruit_PWMServoDriver(0x40); // servo driver for one leg and three servos

Leg leg(board, 0, 1, 2); // This is one defined leg with 3 servos for the inverse kinematics test

const float a = 60.0; // This is the length from femur to tibia the length is final, because it never changes, except one use another model then one must change the value.
const float b = 103.0; // This is the length from tibia to the tip of the leg the length is final, because it never changes, except one use another model then one must change the value.
const float l = 33.0; // This is the coxa offset so the length from coxa to femur. It is final because it never changes, except one use another model then on mus change the value.

float angle1, angle2, angle3; // These are the three different angle variables the angles are calculated later in the program.

/**
 * This is the calculateAngle1 method the method provides the feature to calculate the first angle (Coxa).
 * It can be used in any file that includes the inverse kinematics test.cpp file.
 *
 * @param yp is the parameter that takes over the coordinate y.
 * @param xp is the parameter that takes over the coordinate x.
 * @return the method returns the value of angle1.
 */
float calculateAngle1(float yp, float xp) {
    return atan2(yp, xp);
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
    return atan2(d, z) + acos(((a * a) + (c * c) - (b * b)) / (2 * a * b));
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
    return 180 - acos(((a * a) + (b * b) - (c * c)) / (2 * a * b));
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

void setup() {
    Serial.begin(9600);
    board.begin();
    board.setPWMFreq(50);
    Serial.println("Enter X Y Z: "); // Command prompt on the serial monitor
}

void loop() {
    // checks if the buffer is available
    if (Serial.available()) {
        // imports float values and saves them in x, y and z
        float x = Serial.parseFloat();
        float y = Serial.parseFloat();
        float z = Serial.parseFloat();

        float r, d, c; // These are auxiliary variables that are used to calculate the different angles (coxa, femur, tibia)

        delay(10);
        while (Serial.available()) Serial.read(); // clear buffer

        auto coordinates = calculateMissingVariables(y, x, z); // getting entered coordinates from the user with an array

        // saving coordinates in different variables
        float r = coordinates[0];
        float d = coordinates[1];
        float c = coordinates[2];

        // The three different calculations für each angle with the conversion from degrees to radians (* 180 / PI).
        angle1 = calculateAngle1(y, x) * 180 / PI;
        angle2 = calculateAngle2(d, -z, a, b, c) * 180 / PI;
        angle3 = calculateAngle3(a, b, c) * 180 / PI;

        // Define standard output on the serial monitor
        Serial.print("Angle1 (Coxa): ");
        Serial.println(angle1);
        Serial.print("Angle2 (femur): ");
        Serial.println(angle2);
        Serial.print("Angle3 (tibia): ");
        Serial.println(angle3);

        // The setAngles method from the leg file is used to set the three different angles properly. The servo drivers are also included.
        leg.setAngles(angle1, angle2, angle3);
    }
}
