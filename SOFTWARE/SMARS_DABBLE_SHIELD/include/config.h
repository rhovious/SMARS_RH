String __version__ = "0.0.1";
String ARDUINO_MCU = "atmega328p";

#define LED_COUNT 8
#define ARDUINO_BOARD "uno"

#define NEOPIXEL_PIN 6
#define BUILTIN_LED_PIN 13
#define MAX_BRIGHTNESS 128
#define HEADLIGHT_PIN 6

int patternInterval = 5000;        // Pattern Interval (ms)
int pixelInterval = 50;            // Pixel Interval (ms)