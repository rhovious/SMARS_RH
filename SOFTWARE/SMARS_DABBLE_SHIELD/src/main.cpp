/* 
 *  in this project we will be using HC-05 bluetooth module  
 *  for arduino "UNO" use bluetooth module buadrate below 38400
 *  
 *  HC-05 bluetooth module ----> arduino "UNO"
 *              Tx         ----> 2
 *              Rx         ----> 3  
 * 
 * https://www.impulseadventure.com/elec/robot-differential-steering.html
 *          
 */

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_MotorShield.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
#include <Adafruit_NeoPixel.h>
#include "functions.h"
#include "functions-led.h"
#include "config.h"

//---------------SHELD SETUP--------------
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *rMotor = AFMS.getMotor(1);
Adafruit_DCMotor *lMotor = AFMS.getMotor(2);

//---------------LED SETUP--------------

// Define the array of leds
Adafruit_NeoPixel strip(LED_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

unsigned long pixelPrevious = 0;   // Previous Pixel Millis
unsigned long patternPrevious = 0; // Previous Pattern Millis
int patternCurrent = 0;            // Current Pattern Number
int pixelQueue = 0;                // Pattern Pixel Queue
int pixelCycle = 0;                // Pattern Pixel Cycle
uint16_t pixelCurrent = 0;         // Pattern Current Pixel Number
uint16_t pixelNumber = LED_COUNT;  // Total Number of Pixels
int lightbarState = 0;
int headlightState = 0;

//---------FUNCTIONS------------------------

void setup()
{
    pinMode(BUILTIN_LED_PIN, OUTPUT);
    pinMode(HEADLIGHT_PIN, OUTPUT);

    Serial.begin(115200); // set up Serial library at 9600 bps
    Dabble.begin(9600);   //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive

    //---------------MOTOR SETUP--------------------------
    printCompilationInfo();
    Serial.println("Start SMARS Setup");

    if (!AFMS.begin())
    { // create with the default frequency 1.6KHz
        // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
        Serial.println("Motor shield is disconnected.");
        while (1)
            ;
    }
    Serial.println("Motor Shield found. Continuing");

    // Set the speed to start, from 0 (off) to 255 (max speed)
    rMotor->setSpeed(150);
    lMotor->setSpeed(150);
    rMotor->run(FORWARD);
    lMotor->run(FORWARD);
    // turn on motor
    rMotor->run(RELEASE);
    lMotor->run(RELEASE);
    //---------------LED SETUP

    strip.begin();                       // INITIALIZE NeoPixel strip object (REQUIRED)
    strip.show();                        // Turn OFF all pixels ASAP
    strip.setBrightness(MAX_BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop()
{
    digitalWrite(LED_BUILTIN, LOW);         //TURNS OFF LED. TURNS ON WHEN TEST LOOP RUNNING
    unsigned long currentMillis = millis(); //  Update current time

    Dabble.processInput(); //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.

    testRun(1000);
    testLedAnims(1000);
    handleButtons();
    handleSticks();
}