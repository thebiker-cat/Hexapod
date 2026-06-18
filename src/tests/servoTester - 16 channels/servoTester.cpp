#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <robot/kinematics/leg.h>
#include <iostream>

String currentInput = "";
Adafruit_PWMServoDriver board = Adafruit_PWMServoDriver();
int currentPulse = 0;
int inputArray[] = {};
int inputCounter = -1;
int maxServoSpeed = 0;
String currentStringInput = "";
boolean servosChoosing = false;
boolean testRunning = false;

#define potentiometer_pin 26
#define speedTest_button_pin 25
#define button0degrees_pin 18
#define button90degrees_pin 19
#define button180degrees_pin 20


void readString(String message)
{
    Serial.println(message);

    while (!Serial.available())
    {

    }
    String rueckgabe = Serial.readStringUntil('\n');
    currentStringInput = rueckgabe;
    inputCounter++;
}

boolean correctServoInput()
{
    int number = currentStringInput.toInt();
    if (number >= 0 && number <= 18)
    {
        return false;
    }

    return true;
}


int calculateLowestChannel()
{
    int lowestChannel = 0;
    for (int i = 0; i < sizeof(inputArray) / sizeof(inputArray[0]); i++)
    {
        if (i == 0)
        {
            lowestChannel = inputArray[0];
        }

        if (inputArray[i] < lowestChannel)
        {
            lowestChannel = inputArray[i];
        }
    }

    return lowestChannel;
}

int calculateHighestChannel()
{
    int highestChannel = 0;
    for (int i = 0; i < sizeof(inputArray) / sizeof(inputArray[0]); i++)
    {
        if (i == 0)
        {
            highestChannel = inputArray[0];
        }

        if (inputArray[i] > highestChannel)
        {
            highestChannel = inputArray[i];
        }
    }

    return highestChannel;
}

void attachServos(int channel)
{
    if (!correctServoInput())
    {
        inputCounter++;
        inputArray[inputCounter] = channel;
    }
    else if (currentStringInput == "e")
    {
        Serial.println("Test will start now: ");
        Serial.println("---------------------------------------------------------");
        servosChoosing = false;
    }
    else
    {
        Serial.println("Servo channel out of range");
    }
}


void servoChooser()
{
    Serial.println("Which servos should be tested (0 - 16)?");
    servosChoosing = true;
    while (servosChoosing)
    {
        readString("Choose channel: ");
        attachServos(currentStringInput.toInt());

    }
}

void attachAllServos(int degrees)
{
    int pulse = Leg::angleToPulse(degrees);
    for (int i = 0; i < sizeof(inputArray) / sizeof(inputArray[0]); i++)
    {
        board.setPWM(inputArray[i], 0, pulse);
    }
}

void rotateServosWithDelay(int wait)
{
    for (int i = 0; i < 180; i++)
    {
        attachAllServos(i);
        delay(wait);
    }
}

void speedTest()
{
    int time25percent = 0;
    int time50percent = 0;
    int time75percent = 0;
    int time100percent = 0;
    attachAllServos(0);
    Serial.print("Calculating max speed now .");
    int timeOffset = millis();
    board.setPWM(calculateLowestChannel(), 0, Leg::angleToPulse(180));
    maxServoSpeed = millis() - timeOffset;
    int Servo25Speed = 4 * maxServoSpeed;
    int Servo50Speed = 2 * maxServoSpeed;
    int Servo75Speed = Servo25Speed - Servo50Speed;

    int delay25Percent = Servo25Speed / 180;
    int delay50Percent = Servo50Speed / 180;
    int delay75Percent = Servo75Speed / 180;
    Serial.println();

    Serial.println("Took " + maxServoSpeed);
    Serial.println("Starting testing speed modes now: ");
    Serial.print("25 % speed: ");
    timeOffset = millis();
    rotateServosWithDelay(delay25Percent);
    time25percent = (int)millis() - timeOffset;
    Serial.println("Took " + time25percent );
    Serial.print("50 % speed: ");
    timeOffset = millis();
    rotateServosWithDelay(delay50Percent);
    time50percent = (int)millis() - timeOffset;
    Serial.println("Took " + time50percent);
    Serial.print("75 % speed: ");
    timeOffset = millis();
    rotateServosWithDelay(delay75Percent);
    time75percent = (int)millis() - timeOffset;
    Serial.println("Took " + time75percent);
    Serial.print("100 % speed: ");
    timeOffset = millis();
    attachAllServos(180);
    time100percent = (int)millis() - timeOffset;
    Serial.print("Took" + time100percent);

    Serial.println("---------------------------------------------------------");
    //Serial.println("Summary:");
    //                 + "25 percent: Should take " + Servo25Speed + "; Took: " + time25percent + "\n \t"
    //                 + "50 percent: Should take " + Servo50Speed + "; Took: " + time50percent + "\n \t"
    //                 + "75 percent: Should take " + Servo75Speed + "; Took: " + time75percent + "\n \t"
    //                 + "100 percent: Should take " + maxServoSpeed + "; Took: " + time100percent + "\n \t");
}

void accuracyTest()
{
}

void adjustancyTest()
{
}

int pulseSetter()
{
    float degrees = map(analogRead(potentiometer_pin), 0, 4095, 0, 180);
    return Leg::angleToPulse(degrees);
}
void manuellServoSetter()
{
    if (Serial.available() > 0)
    {
        char eingabe = Serial.read();
        if (eingabe == 'e')
        {

        }
    }
    attachAllServos(pulseSetter());
}
void testMenu()
{
    boolean wrongTestInput = true;
    while (wrongTestInput)
    {
        Serial.println("---------------------------------------------------------");
        Serial.println("Choose test mode: ");
        Serial.println("Speed test (1), Accuracy test (2), Calculate Adjustancy (3), Manual Servo Settings (4) :");
        Serial.println("---------------------------------------------------------");
        readString("Choose test mode: ");
        switch (currentStringInput.toInt())
        {
        case 1:
            servoChooser();
            speedTest();
            break;
        case 2:
            servoChooser();
            accuracyTest();
            break;
        case 3:
            servoChooser();
            adjustancyTest();
            break;
        case 4:
            servoChooser();
            manuellServoSetter();
            break;
        default:
            wrongTestInput = true;
        }

        wrongTestInput = false;
    }
    Serial.println("---------------------------------------------------------");
}


void setup()
{
    Serial.begin(9600);
    board.begin();
    board.setPWMFreq(50);
    pinMode(speedTest_button_pin, INPUT_PULLUP);
}

void loop()
{
    testMenu();
}
