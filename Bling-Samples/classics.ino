/*
 * classic patterns used in the past
 * TODO: clean this up -- 
 */

// Flash of light for a short period of time, then off (runs once only)
void flash(unsigned long timeInterval, uint32_t color, uint8_t brightness)
{
  pixels.setBrightness(brightness);
  setAllPixels(color);
  delay(timeInterval);
  setAllPixels(rgbColor_OFF);
}

// Number of LEDs per "cog" on the animation
#define COG_SIZE 5

// A counter from 0 to (2*COG_SIZE)-1
uint8_t cogOffset=0;

// Classic Spartronics Cogs
void cogs_init(uint32_t color1, uint32_t color2)
{
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    if ((((uint8_t) (i / COG_SIZE)) & 1) == 0) {
      pixels.setPixelColor(i, color1);
    }
    else {
      pixels.setPixelColor(i, color2);
    }
  }
  pixels.show();
}

//moves every led up one, and inserts colorIn at leds[0]
void shiftUp(uint32_t colorIn) {
  for (int i = (NUM_LEDS - 1); i > 0; i--) {
    //The last led becomes the previous led's color
    pixels.setPixelColor(i, pixels.getPixelColor(i-1));
  }
  pixels.setPixelColor(0, colorIn);
}

//moves every led down one, and inserts colorIn at leds[(NUM_LEDS - 1)]
void shiftDown(uint32_t colorIn) {
  for (int i = 0; i < (NUM_LEDS - 1); i++) {
    //The first led becomes the next led's color
    pixels.setPixelColor(i, pixels.getPixelColor(i+1));
  }
  pixels.setPixelColor(NUM_LEDS-1, colorIn);
}

void moveCogsUp() {
  boolean changeColor = true;
  for (int i = 0; i < (COG_SIZE - 1); i++) {
    if (pixels.getPixelColor(i) != pixels.getPixelColor(i+1)) {
      changeColor = false;
    }
  }
  if (changeColor) {
    shiftUp(pixels.getPixelColor(COG_SIZE));
  }
  else {
    shiftUp(pixels.getPixelColor(0));
  }
}

void moveCogsDown() {
  boolean changeColor = true;
  for (int i = (NUM_LEDS - 1); i > (NUM_LEDS - (COG_SIZE)); i--) {
    if (pixels.getPixelColor(i) != pixels.getPixelColor(i-1)) {
      changeColor = false;
    }
  }
  if (changeColor) {
    shiftDown(pixels.getPixelColor(NUM_LEDS - COG_SIZE - 1));
  }
  else {
    shiftDown(pixels.getPixelColor(NUM_LEDS - 1));
  }
}

void rotatingCogsUp(uint32_t colorOne, uint32_t colorTwo) {
  pixels.show();
  for (int i = 0; i < 30; i++) {
    for (int c = 0; c < COG_SIZE; c++) {
      moveCogsUp();
      _delay(100);
      pixels.show();
    }
  }
}

void rotatingCogsDown(uint32_t colorOne, uint32_t colorTwo) {
  pixels.show();
  for (int i = 0; i < 30; i++) {
    for (int c = 0; c < COG_SIZE; c++) {
      moveCogsDown();
      _delay(100);
      pixels.show();
    }
  }
}

void cogs(uint32_t color1, uint32_t color2)
{
  cogs_init(color1, color2);
  while (1) {
    rotatingCogsUp(color1, color2);
    rotatingCogsDown(color1, color2);
  }
}


void crawler(uint16_t timeInterval, uint32_t color, uint8_t length)
{
  // From the middle of the top, start illuminating pixels towards the ends
  // After length pixels have been added to each side, turn old pixels off
  // Pixels continue to scroll off of ends, then the scheme reverses

  uint8_t tempLength;
  uint8_t headUp;
  uint8_t headDown;
  uint8_t tailUp;
  uint8_t tailDown;

  while (1)
  {
    // Turn off the strip
    setAllPixels(rgbColor_OFF);

    tempLength = length;
    headUp = (NUM_LEDS/2);
    headDown = headUp - 1;
    for (uint8_t i=0; i<length; i++)
    {
      pixels.setPixelColor(headUp++, color);
      pixels.setPixelColor(headDown--, color);
      pixels.show();
      delay(timeInterval);
    }
    tailUp = (NUM_LEDS/2);
    tailDown = tailUp - 1;
    while (headUp < NUM_LEDS)
    {
      pixels.setPixelColor(headUp++, color);
      pixels.setPixelColor(headDown--, color);
      pixels.setPixelColor(tailUp++, OFF);
      pixels.setPixelColor(tailDown--, OFF);
      pixels.show();
      delay(timeInterval);
    }
    while (tailUp < NUM_LEDS)
    {
      pixels.setPixelColor(tailUp++, OFF);
      pixels.setPixelColor(tailDown--, OFF);
      pixels.show();
      delay(timeInterval);
    }
    // Reverse!
    tempLength = length;
    headUp = NUM_LEDS - 1;
    headDown = 0;
    for (uint8_t i=0; i<length; i++)
    {
      pixels.setPixelColor(headUp--, color);
      pixels.setPixelColor(headDown++, color);
      pixels.show();
      delay(timeInterval);
    }
    tailUp = NUM_LEDS - 1;
    tailDown = 0;
    while (headUp >= (NUM_LEDS/2))
    {
      pixels.setPixelColor(headUp--, color);
      pixels.setPixelColor(headDown++, color);
      pixels.setPixelColor(tailUp--, OFF);
      pixels.setPixelColor(tailDown++, OFF);
      pixels.show();
      delay(timeInterval);
    }
    while (tailUp >= (NUM_LEDS/2))
    {
      pixels.setPixelColor(tailUp--, OFF);
      pixels.setPixelColor(tailDown++, OFF);
      pixels.show();
      delay(timeInterval);
    }
  }
}
