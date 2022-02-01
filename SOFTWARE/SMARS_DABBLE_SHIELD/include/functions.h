extern Adafruit_DCMotor *rMotor;
extern Adafruit_DCMotor *lMotor;

extern void colorWipe(uint32_t color, int wait);
extern void leftLights(uint32_t color, int wait);
extern void rightLights(uint32_t color, int wait);
extern void allLights(uint32_t color, int wait);
extern void backupLights(uint32_t color, int wait);
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

    /*
        Serial.print(F("Compiled: "));
        Serial.print(F(__DATE__));
        Serial.print(F(", "));
        Serial.print(F(__TIME__));
        Serial.print(F(", "));
        Serial.println(F(__VERSION__));
        Serial.print(F("Arduino IDE version: "));
        Serial.println(ARDUINO, DEC);
        */
}

void goStop()
{
    Serial.println("STOPPING");
    rMotor->run(RELEASE);
    lMotor->run(RELEASE);
}

void turnRight(int amount)
{ // amount is the parameter
    Serial.println("turnRight");
    lMotor->setSpeed(250);
    lMotor->run(FORWARD);
    rMotor->setSpeed(50);
    rMotor->run(BACKWARD);
    delay(amount); // here we are using the parameter
    goStop();
    delay(250);
}

void turnLeft()
{
    Serial.println("turnLeft");
    lMotor->setSpeed(250);
    lMotor->run(BACKWARD);
    rMotor->setSpeed(50);
    rMotor->run(FORWARD);
}

void goForward()
{
    uint8_t i;
    Serial.println("FORWARD");
    rMotor->run(FORWARD);
    lMotor->run(FORWARD);
    allLights(strip.Color(0, MAX_BRIGHTNESS, 0), 50); // w
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
    allLights(strip.Color(0, 0, 0), 50); // w
}

void leftTest()
{
    uint8_t i;
    Serial.println("LEFT ONLY");
    // rMotor->run(FORWARD);
    lMotor->run(FORWARD);

    leftLights(strip.Color(0, MAX_BRIGHTNESS, 0), 50); // green
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
    leftLights(strip.Color(0, 0, 0), 50); // whit
}

void rightTest()
{
    uint8_t i;
    Serial.println("RIGHT ONLY");
    rMotor->run(FORWARD);

    rightLights(strip.Color(0, MAX_BRIGHTNESS, 0), 50); // green
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
    rightLights(strip.Color(0, 0, 0), 50); // off
}

void goBackward()
{
    uint8_t i;
    Serial.println("BACKWARD");
    allLights(strip.Color(MAX_BRIGHTNESS, 0, 0), 50); // red

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
    allLights(strip.Color(0, 0, 0), 50); // off
}

void lightbarToggle(int toggle)
{
    // Turn the LED on, then pause
    if (toggle == 1)
    {
        lightbarState = 1;
        colorWipe(strip.Color(MAX_BRIGHTNESS, MAX_BRIGHTNESS, MAX_BRIGHTNESS), 50); // White
    }

    if (toggle == 0)
    {
        lightbarState = 0;
        colorWipe(strip.Color(0, 0, 0), 50); // OFF
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

void handleButtons()
{
    Serial.print("KeyPressed: ");
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
        turnRight(1);
    }

    if (GamePad.isRightPressed())
    {
        Serial.print("Right");
        turnRight(1);
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
        Serial.print("Circle");
        if (headlightState == 1)
        {
            headlightToggle(0);
            Serial.print("Turning OFF Headlights");
        }
        else if (headlightState == 0)
        {
            headlightToggle(1);
            Serial.print("Turning ON Headlights");
        }
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

void testDrive(int testDriveDelay)
{
    digitalWrite(LED_BUILTIN, HIGH); // TURNS ON LED AT BEGINNING
    // turnRight(10);
    leftTest();
    goStop();
    delay(testDriveDelay);
    rightTest();
    goStop();
    delay(testDriveDelay);
    goForward();
    goStop();
    delay(testDriveDelay);
    goBackward();
    goStop();
    delay(testDriveDelay);
    digitalWrite(LED_BUILTIN, LOW); // TURNS OFF LED AT END
}
