extern int pixelInterval;
extern Adafruit_NeoPixel strip;
extern int pixelCycle;
extern int pixelQueue;
extern int MAX_BRIGHTNESS;

extern uint16_t pixelCurrent;         // Pattern Current Pixel Number
extern uint16_t pixelNumber;  // Total Number of Pixels
extern int headlightState;
extern Adafruit_DCMotor *rMotor;
extern Adafruit_DCMotor *lMotor;
extern void colorWipe(uint32_t color, int wait);

void goStop()
{
    Serial.print("STOPPING");
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
    Serial.print("FORWARD");
    rMotor->run(FORWARD);
    lMotor->run(FORWARD);
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
}

void goBackward()
{
    uint8_t i;
    Serial.print("BACKWARD");

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
}

void headlightToggle(int toggle)
{
    // Turn the LED on, then pause
    if (toggle == 1)
    {
        headlightState = 1;
        colorWipe(strip.Color(MAX_BRIGHTNESS, MAX_BRIGHTNESS, MAX_BRIGHTNESS), 50); // White
    }

    if (toggle == 0)
    {
        headlightState = 0;
        colorWipe(strip.Color(0, 0, 0), 50); // OFF
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
    }

    if (GamePad.isRightPressed())
    {
        Serial.print("Right");
    }

    if (GamePad.isSquarePressed())
    {
        Serial.print("Square");
        if (headlightState == 1)
        {
            headlightToggle(0);
            Serial.print("Turning OFF headlights");
        }
        else if (headlightState == 0)
        {
            headlightToggle(1);
            Serial.print("Turning ON headlights");
        }
    }

    if (GamePad.isCirclePressed())
    {
        Serial.print("Circle");
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



void testRun(int testRunDelay)
{
    goForward();
    delay(testRunDelay);
    goBackward();
    delay(testRunDelay);
    goStop();
    delay(testRunDelay);
}

