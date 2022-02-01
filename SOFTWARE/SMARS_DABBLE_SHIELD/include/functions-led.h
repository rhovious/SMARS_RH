// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.

/*
extern uint16_t pixelCurrent; // Pattern Current Pixel Number
extern uint16_t pixelNumber;  // Total Number of Pixels
extern Adafruit_NeoPixel strip;
extern int pixelInterval;
extern int pixelCycle;
extern int pixelQueue;
extern int MAX_BRIGHTNESS;
extern int HEADLIGHT_PIN;
*/
unsigned long pixelPrevious = 0;   // Previous Pixel Millis
unsigned long patternPrevious = 0; // Previous Pattern Millis
int patternCurrent = 0;            // Current Pattern Number
int pixelQueue = 0;                // Pattern Pixel Queue
int pixelCycle = 0;                // Pattern Pixel Cycle
uint16_t pixelCurrent = 0;         // Pattern Current Pixel Number
int patternInterval = 5000;        // Pattern Interval (ms)
int pixelInterval = 50;            // Pixel Interval (ms)
extern int MAX_BRIGHTNESS;
extern int HEADLIGHT_PIN;
extern int MAX_BRIGHTNESS;

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void colorWipe(uint32_t color, int wait)
{
    if (pixelInterval != wait)
        pixelInterval = wait;                 //  Update delay time
    strip.setPixelColor(pixelCurrent, color); //  Set pixel's color (in RAM)
    strip.show();                             //  Update strip to match
    pixelCurrent++;                           //  Advance current pixel
    if (pixelCurrent >= pixelNumber)          //  Loop the pattern from the first LED
        pixelCurrent = 0;
}

void rightLights(uint32_t color, int wait)
{

    for (uint16_t i = pixelNumber / 2; i < pixelNumber; i++)
    {

        strip.setPixelColor(i, color);
    }
    strip.show(); //  Update strip to match
}

void leftLights(uint32_t color, int wait)
{
    for (uint16_t i = 0; i < pixelNumber / 2; i++)
    {

        strip.setPixelColor(i, color);
    }
    strip.show(); //  Update strip to match
}

void allLights(uint32_t color, int wait)
{
    for (uint16_t i = 0; i < pixelNumber; i++)
    {

        strip.setPixelColor(i, color);
    }
    strip.show(); //  Update strip to match
}

void backupLights(uint32_t color, int wait)
{
    for (uint16_t i = 0; i < pixelNumber / 2; i++)
    {

        strip.setPixelColor(i, color);
    }
    strip.show(); //  Update strip to match
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait)
{
    if (pixelInterval != wait)
        pixelInterval = wait; //  Update delay time
    for (uint16_t i = 0; i < pixelNumber; i++)
    {
        Serial.println(i);
        strip.setPixelColor(i + pixelQueue, color); //  Set pixel's color (in RAM)
    }
    strip.show(); //  Update strip to match
    for (uint16_t i = 0; i < pixelNumber; i + 3)
    {
        strip.setPixelColor(i + pixelQueue, strip.Color(0, 0, 0)); //  Set pixel's color (in RAM)
    }
    pixelQueue++; //  Advance current pixel
    if (pixelQueue >= 3)
        pixelQueue = 0; //  Loop the pattern from the first LED
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(uint8_t wait)
{
    if (pixelInterval != wait)
        pixelInterval = wait;
    for (uint16_t i = 0; i < pixelNumber; i++)
    {
        strip.setPixelColor(i, Wheel((i + pixelCycle) & 255)); //  Update delay time
    }
    strip.show(); //  Update strip to match
    pixelCycle++; //  Advance current cycle
    if (pixelCycle >= 256)
        pixelCycle = 0; //  Loop the cycle back to the begining
}

// Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait)
{
    if (pixelInterval != wait)
        pixelInterval = wait; //  Update delay time
    for (uint16_t i = 0; i < pixelNumber; i + 3)
    {
        strip.setPixelColor(i + pixelQueue, Wheel((i + pixelCycle) % 255)); //  Update delay time
    }
    strip.show();
    for (uint16_t i = 0; i < pixelNumber; i + 3)
    {
        strip.setPixelColor(i + pixelQueue, strip.Color(0, 0, 0)); //  Update delay time
    }
    pixelQueue++; //  Advance current queue
    pixelCycle++; //  Advance current cycle
    if (pixelQueue >= 3)
        pixelQueue = 0; //  Loop
    if (pixelCycle >= 256)
        pixelCycle = 0; //  Loop
}

void testLedAnims()
{
    // Serial.println("Starting LED Test");
    currentMillis = millis(); //  Update current time
    if ((currentMillis - patternPrevious) >= patternInterval)
    { //  Check for expired time
        patternPrevious = currentMillis;
        patternCurrent++; //  Advance to next pattern
        if (patternCurrent >= 4)
            patternCurrent = 0;
    }

    if (currentMillis - pixelPrevious >= pixelInterval)
    {                                  //  Check for expired time
        pixelPrevious = currentMillis; //  Run current frame
        switch (patternCurrent)
        {

        case 3:
            // theaterChase(strip.Color(127, 127, 127), 50); // White
            colorWipe(strip.Color(0, 0, 255), 50); // Red
            break;
        case 2:
            colorWipe(strip.Color(0, 0, 255), 50); // Blue
            break;
        case 1:
            colorWipe(strip.Color(255, 0, 0), 50); // Green
            break;
        default:
            colorWipe(strip.Color(127, 127, 127), 50); // White
            break;
        }
    }
    // Serial.println("Finish LED Test");
}