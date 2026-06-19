#include <Arduino.h>
#include <array>
#include "robot/kinematics/leg.h" // include leg file so one can use the setAngles method
#include "robot/kinematics/inverseKinematics.h" // include inverseKinematics file for basic angel calculations

Adafruit_PWMServoDriver board = Adafruit_PWMServoDriver(0x40); // servo driver for one leg and three servos

Leg leg(board, 0, 1, 2); // This is one defined leg with 3 servos for the inverse kinematics test

float angle1, angle2, angle3; // These are the three different angle variables the angles are calculated later in the program.

void setup() {
    Serial.begin(9600);
    board.begin();
    board.setPWMFreq(50);
    Serial.println("Enter X Y Z: "); // Command prompt on the serial monitor
}

void loop() {
    // checks if the buffer is available
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();

        int firstSpace = input.indexOf(' ');
        String rest = input.substring(firstSpace + 1);
        int secondSpace = input.indexOf(' ', firstSpace + 1);

        if (firstSpace == -1 || secondSpace == -1) {
            Serial.println("Fehler! Bitte X Y Z eingeben!");
        }

        // imports float values and saves them in x, y and z
        float x = input.substring(0, firstSpace).toFloat();
        float y = rest.substring(0, secondSpace).toFloat();
        float z = rest.substring(secondSpace + 1).toFloat();


        float r, d, c; // These are auxiliary variables that are used to calculate the different angles (coxa, femur, tibia)

        delay(10);
        while (Serial.available()) Serial.read(); // clear buffer

        auto coordinates = calculateMissingVariables(y, x, z); // getting entered coordinates from the user with an array

        // saving coordinates in different variables
        r = coordinates[0];
        d = coordinates[1];
        c = coordinates[2];


        // The three different calculations für each angle.
        angle1 = calculateAngle1(y, x);
        angle2 = calculateAngle2(d, -z, a, b, c);
        angle3 = calculateAngle3(a, b, c);

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
