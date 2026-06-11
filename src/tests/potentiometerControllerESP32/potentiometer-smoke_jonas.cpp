#include <Arduino.h>
#include <ESP32Servo.h> // This is a library to control the servo directly without any board

#define potentiometer_pin 26 // This pin reads an adc-input from the potentiometer
#define servo_pin 23 // This pin is the pin, that connects the servo motor with the esp32 directly

/*
 * These variables are there to control the Output on the serial monitor.
 * Every 1 second (degreeCountdown), the angel of the servo will be monitored on the serial monitor.
 */
unsigned int degreeCountdown = 1000;
unsigned int millisToNow = 0;
unsigned int lastMillis = 0;

Servo servo = Servo(); // This is the servo motor connected to the esp32.
float degrees = 0; // This is a variable to save the current degrees for the servo motor.

void setup() {
    Serial.begin(9600);
    pinMode(potentiometer_pin, INPUT);
    servo.attach(servo_pin); // Attaches the pin to the next free pwmChannel, because servos only understand PWM signals.
}

/**
 * This method turns the analog input of the potentiometer into degrees from 0 to 180 degrees.
 */
void readDegrees() {
    degrees = map(analogRead(potentiometer_pin), 0, 4095, 0, 180); // Potentiometers can give you 4096 values, but since the first value is 0 the highest value ist 4095.

}

void loop() {
    millisToNow = millis();
    readDegrees(); // This method has to be in the loop to always capture the current INPUT of the potentiometer.
    servo.write(degrees); // This writes the current servo angle to the degrees that are calculated above.
    if (millisToNow - lastMillis >= degreeCountdown) { // Every one second.
        Serial.print(degrees); // The current degrees value is printed in the serial monitor.
        lastMillis = millisToNow;
    }

}
