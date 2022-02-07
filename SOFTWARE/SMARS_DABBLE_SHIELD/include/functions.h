extern Adafruit_DCMotor *rMotor;
extern Adafruit_DCMotor *lMotor;

extern void leftLights(uint32_t color);
extern void rightLights(uint32_t color);
extern void allLights(uint32_t color);
extern Adafruit_NeoPixel strip;
extern int pixelInterval;
extern int pixelCycle;
extern int pixelQueue;
extern int MAX_BRIGHTNESS;
extern int HEADLIGHT_PIN;
extern uint16_t pixelCurrent; // Pattern Current Pixel Number
extern uint16_t pixelNumber;  // Total Number of Pixels

extern int lightbarState;
extern int headlightState;
extern unsigned long currentMillis;

extern String ARDUINO_BOARD;
extern String ARDUINO_MCU;

void printCompilationInfo()
{
    String str, adjStr;
    Serial.print("Arduino IDE version ");
    str = String(ARDUINO);
    adjStr = str.substring(1, str.length() - 5) + ".";
    adjStr = adjStr + str.substring(str.length() - 4, str.length() - 2) + ".";
    adjStr = adjStr + str.substring(str.length() - 2);
    Serial.println(adjStr); // date and time sketch compiled
    Serial.print("Compiler version    ");
    Serial.println(__VERSION__);
    Serial.print("Compiled date       ");
    Serial.println(__DATE__);
    Serial.print("Compiled time       ");
    Serial.println(__TIME__);
    Serial.print("Sketch location     ");
    Serial.println(__FILE__);
    Serial.print("CPU frequency(MHz)  "); // CPU frequency
    Serial.println(F_CPU / 1000000);
    Serial.print("Development board   ");
    Serial.println(ARDUINO_BOARD);
#ifdef __AVR__ // development board
    Serial.print("Microcontroller     ");
    Serial.println(ARDUINO_MCU);
#endif // microcontroller
    Serial.print("SPI MOSI ");
    Serial.println(MOSI); // pin layout SPI
    Serial.print("SPI MISO ");
    Serial.println(MISO);
    Serial.print("SPI SCK  ");
    Serial.println(SCK);
    Serial.print("SPI SS   ");
    Serial.println(SS);
    Serial.print("I2C SDA  ");
    Serial.println(SDA); // pin layout I2C
    Serial.print("I2C SCL  ");
    Serial.println(SCL);
#ifndef ESP32
    Serial.print("LED      ");
    Serial.println(LED_BUILTIN); // built-in LED
#endif                           // Arduino IDE version
}

void lightbarToggle(int toggle)
{
    // Turn the LED on, then pause
    if (toggle == 1)
    {
        lightbarState = 1;
        allLights(strip.Color(MAX_BRIGHTNESS, MAX_BRIGHTNESS, MAX_BRIGHTNESS));// White
        
    }

    if (toggle == 0)
    {
        lightbarState = 0;
        allLights(strip.Color(0, 0, 0)); // OFF
    }
}

void headlightToggle(int toggle)
{
    // Turn the LED on, then pause
    if (toggle == 1)
    {
        headlightState = 1;
        analogWrite(HEADLIGHT_PIN, 255); // ON
    }

    if (toggle == 0)
    {
        headlightState = 0;
        analogWrite(HEADLIGHT_PIN, 0); // OFF
    }
}

//~~~~~~~~~~~~~~DRIVE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~

void goStop()
{
    //Serial.println("STOPPING");
    rMotor->run(RELEASE);
    lMotor->run(RELEASE);
}

void goTurnRight()
{ // amount is the parameter
    Serial.println("turnRight");
    lMotor->setSpeed(250);
    lMotor->run(FORWARD);
    rMotor->setSpeed(50);
    rMotor->run(BACKWARD);
}

void goTurnLeft()
{
    Serial.println("TurnLeft");
    lMotor->setSpeed(50);
    lMotor->run(BACKWARD);
    rMotor->setSpeed(250);
    rMotor->run(FORWARD);
}

void goForward()
{
    Serial.println("FORWARD");
    lMotor->setSpeed(250);
    lMotor->run(FORWARD);
    rMotor->setSpeed(250);
    rMotor->run(FORWARD);
}

void goBackward()
{
    Serial.println("BACKWARD");
    lMotor->setSpeed(250);
    lMotor->run(BACKWARD);
    rMotor->setSpeed(250);
    rMotor->run(BACKWARD);
}

//~~~~~~~~~~~~~~TESTING FUNCTIONS~~~~~~~~~~~~~~~~~~~~~

void forwardTest()
{
    uint8_t i;
    Serial.println("FORWARD");
    rMotor->run(FORWARD);
    lMotor->run(FORWARD);
    allLights(strip.Color(0, MAX_BRIGHTNESS, 0)); // w
    for (i = 0; i < 255; i++)
    {
        rMotor->setSpeed(i);
        lMotor->setSpeed(i);
        delay(10);
    }

    for (i = 255; i != 0; i--)
    {
        rMotor->setSpeed(i);
        lMotor->setSpeed(i);
        delay(10);
    }
    allLights(strip.Color(0, 0, 0)); // w
}

void leftWheelTest()
{
    uint8_t i;
    Serial.println("LEFT ONLY");
    // rMotor->run(FORWARD);
    lMotor->run(FORWARD);

    leftLights(strip.Color(0, MAX_BRIGHTNESS, 0)); // green
    for (i = 0; i < 255; i++)
    {
        // rMotor->setSpeed(i);
        lMotor->setSpeed(i);
        delay(10);
    }

    for (i = 255; i != 0; i--)
    {
        // rMotor->setSpeed(i);
        lMotor->setSpeed(i);
        delay(10);
    }
    leftLights(strip.Color(0, 0, 0)); // whit
}

void rightWheelTest()
{
    uint8_t i;
    Serial.println("RIGHT ONLY");
    rMotor->run(FORWARD);

    rightLights(strip.Color(0, MAX_BRIGHTNESS, 0)); // green
    // lMotor->run(FORWARD);
    for (i = 0; i < 255; i++)
    {
        rMotor->setSpeed(i);
        // lMotor->setSpeed(i);
        delay(10);
    }

    for (i = 255; i != 0; i--)
    {
        rMotor->setSpeed(i);
        // lMotor->setSpeed(i);
        delay(10);
    }
    rightLights(strip.Color(0, 0, 0)); // off
}

void backwardTest()
{
    uint8_t i;
    Serial.println("BACKWARD");
    allLights(strip.Color(MAX_BRIGHTNESS, 0, 0)); // red

    rMotor->run(BACKWARD);
    lMotor->run(BACKWARD);
    for (i = 0; i < 255; i++)
    {
        rMotor->setSpeed(i);
        lMotor->setSpeed(i);
        delay(10);
    }

    for (i = 255; i != 0; i--)
    {
        rMotor->setSpeed(i);
        lMotor->setSpeed(i);
        delay(10);
    }
    allLights(strip.Color(0, 0, 0)); // off
}

void testDrive(int testDriveDelay)
{
    digitalWrite(LED_BUILTIN, HIGH); // TURNS ON LED AT BEGINNING
    // turnRight(10);
    leftWheelTest();
    goStop();
    delay(testDriveDelay);
    rightWheelTest();
    goStop();
    delay(testDriveDelay);
    forwardTest();
    goStop();
    delay(testDriveDelay);
    backwardTest();
    goStop();
    delay(testDriveDelay);
    digitalWrite(LED_BUILTIN, LOW); // TURNS OFF LED AT END
}

//~~~~~~~~~~~~~~CONTROL FUNCTIONS~~~~~~~~~~~~~~~~~~~~~
void handleButtons()
{
    //Serial.print("KeyPressed: ");
    if (GamePad.isUpPressed())
    {
        Serial.print("UP");
        goForward();
    }

    if (GamePad.isDownPressed())
    {
        Serial.print("DOWN");
        goBackward();
    }

    if (GamePad.isLeftPressed())
    {
        Serial.print("Left");
        goTurnLeft();
    }

    if (GamePad.isRightPressed())
    {
        Serial.print("Right");
        goTurnRight();
    }
    if (!GamePad.isUpPressed() && !GamePad.isDownPressed() && !GamePad.isLeftPressed() && !GamePad.isRightPressed())
    {
        goStop();
    }


    if (GamePad.isSquarePressed())
    {
        Serial.print("Square");
        if (lightbarState == 1)
        {
            lightbarToggle(0);
            Serial.print("Turning OFF Lightbar");
        }
        else if (lightbarState == 0)
        {
            lightbarToggle(1);
            Serial.print("Turning ON Lightbar");
        }
    }

    if (GamePad.isCirclePressed())
    {
        allLights(strip.Color(random(0, MAX_BRIGHTNESS), random(0, MAX_BRIGHTNESS), random(0, MAX_BRIGHTNESS)));// random color
    }

    if (GamePad.isCrossPressed())
    {
        Serial.print("Cross");
    }

    if (GamePad.isTrianglePressed())
    {
        Serial.print("Triangle");
    }

    if (GamePad.isStartPressed())
    {
        Serial.print("Start");
        testDrive(1000);
    }

    if (GamePad.isSelectPressed())
    {
        Serial.print("Select");
    }
    Serial.print('\t');
    //  Update current time
}

void handleSticks()
{
    int a = GamePad.getAngle();
    Serial.print("Angle: ");
    Serial.print(a);
    Serial.print('\t');
    int b = GamePad.getRadius();
    Serial.print("Radius: ");
    Serial.print(b);
    Serial.print('\t');
    float c = GamePad.getXaxisData();
    Serial.print("x_axis: ");
    Serial.print(c);
    Serial.print('\t');
    float d = GamePad.getYaxisData();
    Serial.print("y_axis: ");
    Serial.println(d);
    Serial.println();
}

