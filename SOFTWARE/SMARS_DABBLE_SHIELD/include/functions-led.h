// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.

//extern int MAX_BRIGHTNESS;

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

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait)
{
    if (pixelInterval != wait)
        pixelInterval = wait; //  Update delay time
    for (uint16_t i = 0; i < pixelNumber; i++)
    {
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

//Theatre-style crawling lights with rainbow effect
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


void testLedAnims(int delayTime)
{
    theaterChaseRainbow(50);                      // Rainbow-enhanced theaterChase variant
    delay(delayTime);

    rainbow(10);                                  // Flowing rainbow cycle along the whole strip
    delay(delayTime);

    theaterChase(strip.Color(0, 0, 127), 50);     // Blue
    delay(delayTime);
    theaterChase(strip.Color(127, 0, 0), 50);     // Red
    delay(delayTime);
    theaterChase(strip.Color(127, 127, 127), 50); // White
    delay(delayTime);

    colorWipe(strip.Color(0, 0, 255), 50);        // Blue
    delay(delayTime);
    colorWipe(strip.Color(0, 255, 0), 50);        // Green
    delay(delayTime);
    colorWipe(strip.Color(255, 0, 0), 50);        // Red
    delay(delayTime);
}