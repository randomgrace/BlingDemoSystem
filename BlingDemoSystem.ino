/*
  Description: A program to demo some bling on NeoPixels

  Written by: Riyadth Al-Kazily
*/

// Include a library to communicate with colorful LEDs
#include <Adafruit_NeoPixel.h>

// Name some constant values to make them easy to remember
// Note that this is a different way than declaring an integer (below)
#define STRIP_PIN       4
#define STRIP_PIXELS    30
#define RING_PIN        5
#define RING_PIXELS     12

// Tell the computer about the arrangement and type of the pixels we are using
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_PIXELS, STRIP_PIN,
                                             NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(RING_PIXELS, RING_PIN,
                                             NEO_GRB + NEO_KHZ800);

int sensorPin = A0;     // A pin connected to a potentiomenter
int sensorValue;        // A place to store the value from the potentiometer

void setup()
{
    // Code placed here will run one time when the Arduino is started
    Serial.begin(9600);

    // Configure the Arduino to make a pin output a voltage
    pinMode(LED_BUILTIN, OUTPUT);

    // Initialize the pixels to get them ready for use
    strip.begin();
    ring.begin();

    all_pixels(&strip, Adafruit_NeoPixel::Color(0, 0, 0));
    all_pixels(&ring, Adafruit_NeoPixel::Color(0, 0, 0));

    strip.setPixelColor(0, Adafruit_NeoPixel::Color(32, 0, 0));
    strip.setPixelColor(1, Adafruit_NeoPixel::Color(32, 32, 0));
    strip.setPixelColor(2, Adafruit_NeoPixel::Color(0, 32, 0));
    strip.setPixelColor(3, Adafruit_NeoPixel::Color(0, 32, 32));
    strip.setPixelColor(4, Adafruit_NeoPixel::Color(0, 0, 32));
    strip.setPixelColor(5, Adafruit_NeoPixel::Color(32, 0, 32));
    strip.setPixelColor(6, Adafruit_NeoPixel::Color(32, 32, 32));
    strip.show();
    ring.setPixelColor(0, Adafruit_NeoPixel::Color(32, 0, 0));
    ring.setPixelColor(1, Adafruit_NeoPixel::Color(0, 32, 0));
    ring.setPixelColor(2, Adafruit_NeoPixel::Color(0, 0, 32));
    ring.show();

    Serial.println("Setup complete.");
}

void loop()
{
    // Code placed here will run over and over forever

    // Read the voltage value on the sensor input pin
    sensorValue = analogRead(sensorPin);

    sensorValue = sensorValue - 512;

    if (sensorValue < 0)
    {
        shift_down(&strip);
        shift_down(&ring);
    }
    else
    {
        shift_up(&strip);
        shift_up(&ring);
    }

    delay(650 - abs(sensorValue));
}

/**
 *  Set all pixels of the strip to the specified color.
 */
void all_pixels(Adafruit_NeoPixel *pixels, uint32_t color)
{
    uint16_t numPixels = pixels->numPixels();

    for (unsigned i=0; i<numPixels; i++)
    {
        pixels->setPixelColor(i, color);
    }
    pixels->show();
}

/**
 *  Shift the pixel display up the strip by one position, rotating the
 *  highest pixel around from the top to the bottom.
 */
void shift_up(Adafruit_NeoPixel *pixels)
{
    uint32_t saved_pixel;
    uint16_t numPixels = pixels->numPixels();

    saved_pixel = pixels->getPixelColor(numPixels - 1);
    for (int i=0; i<numPixels; i++)
    {
        uint32_t temp;
        temp = pixels->getPixelColor(i);
        pixels->setPixelColor(i, saved_pixel);
        saved_pixel = temp;
    }
    pixels->show();
}

/**
 *  Shift the pixel display down the strip by one position, rotating the
 *  lowest pixel around from the bottom to the top.
 */
void shift_down(Adafruit_NeoPixel *pixels)
{
    uint32_t saved_pixel;
    uint16_t numPixels = pixels->numPixels();

    saved_pixel = pixels->getPixelColor(0);
    for (int i=numPixels - 1; i>=0; i--)
    {
        uint32_t temp;
        temp = pixels->getPixelColor(i);
        pixels->setPixelColor(i, saved_pixel);
        saved_pixel = temp;
    }
    pixels->show();
}

void make_a_rainbow(Adafruit_NeoPixel *pixels, int brightness)
{
    uint16_t numPixels = pixels->numPixels();

    // Set the NeoPixels to a rainbow of colors
    for (unsigned i=0; i<numPixels; i++)
    {
        // TODO: Compute the rainbow spectrum across all the pixels
    }
    /*
    pixels->setPixelColor(0, pixels.Color(brightness, 0, 0));
    pixels->setPixelColor(1, pixels.Color(brightness, brightness, 0));
    pixels->setPixelColor(2, pixels.Color(0, brightness, 0));
    pixels->setPixelColor(3, pixels.Color(0, brightness, brightness));
    pixels->setPixelColor(4, pixels.Color(0, 0, brightness));
    pixels->setPixelColor(5, pixels.Color(brightness, 0, brightness));
    pixels->setPixelColor(6, pixels.Color(brightness, brightness, brightness));
    pixels->setPixelColor(7, pixels.Color(0, 0, 0));
    pixels->show();
    */
}
