unsigned long pixelPrevious = 0;   // Previous Pixel Millis
unsigned long patternPrevious = 0; // Previous Pattern Millis
int patternCurrent = 0;            // Current Pattern Number
int pixelQueue = 0;                // Pattern Pixel Queue
int pixelCycle = 0;                // Pattern Pixel Cycle
uint16_t pixelCurrent = 0;         // Pattern Current Pixel Number
int patternInterval = 5000;   // Pattern Interval (ms)
int pixelInterval = 50;       // Pixel Interval (ms)
extern int MAX_BRIGHTNESS;
extern int HEADLIGHT_PIN;
extern int MAX_BRIGHTNESS;
extern int LED_COUNT;
uint16_t pixelNumber = LED_COUNT; // Total Number of Pixels

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.


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

void rightLights(uint32_t color)
{

    for (uint16_t i = pixelNumber / 2; i < pixelNumber; i++)
    {

        strip.setPixelColor(i, color);
    }
    strip.show(); //  Update strip to match
}

void leftLights(uint32_t color)
{
    for (uint16_t i = 0; i < pixelNumber / 2; i++)
    {

        strip.setPixelColor(i, color);
    }
    strip.show(); //  Update strip to match
}

void allLights(uint32_t color)
{
    for (uint16_t i = 0; i < pixelNumber; i++)
    {

        strip.setPixelColor(i, color);
    }
    strip.show(); //  Update strip to match
}

void testLedAnims()
{
    Serial.print("Test");
}