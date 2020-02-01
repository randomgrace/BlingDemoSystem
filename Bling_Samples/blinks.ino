/*
 * Example patterns derived from blinks
 */


/*
 * strobe: strobe a given color number of times with specified delay
 * pause between strobes
 */
 void strobe(rgbColor c, uint8_t numFlashes, int flashDelay, int strobePause)
 {
  for(int j = 0; j < numFlashes; j++) 
  {
    setAllPixels(c);
    showPixels();
    
    delay(flashDelay);
    
    setAllPixels(rgbColor_OFF);
    showPixels();
    delay(flashDelay);
  }
 
 delay(strobePause);
}

/*
 * Random dots
 *  - width per pixel group -- 
 *  - space between dots
 */
 void randomDots(rgbColor c, uint8_t width, uint8_t space)
 {

  randomSeed(analogRead(0));
 
  int i;
  int pixelGroup1  = random( 0, NUM_LEDS - (2*width) - space );
  int pixelGroup2 = pixelGroup1 + width + space;
 
  for(i = 0; i < width; i++) {
    pixels.setPixelColor(pixelGroup1 + i, c.r, c.g, c.b);
    pixels.setPixelColor(pixelGroup2 + i, c.r, c.g, c.b);
  }
 
  showPixels();

  delay(100);
 
  setAllPixels(0,0,0); // Set all black
 
  delay(200);
}

/*
 * twinkle... random LEDs based on paraments
 *  - cnt: number of LEDs to turn on every cycle
 *  - wait: delay time between twinkles
 *  - single: if only 1 LED or all cnt LEDs shown at each cycle
 */
void twinkle(rgbColor c, uint8_t cnt, int wait, boolean single) 
{
  // turn off all pixels
  setAllPixels(0, 0, 0);

  // # of LEDs turned on based on 'cnt' value
  for (int i=0; i<cnt; i++) 
  {
    // randomly set a pixel to color
    setPixel(random(NUM_LEDS), c.r, c.g, c.b);
    showPixels();
    delay(wait);

    // if single twinkle at a time, clear pixels before setting next one
    if(single) 
    {
      setAllPixels(0,0,0);
    }
  }
 
  delay(wait);
}

/*
 * sparkle: randomly selects pixel position and sets its color 
 */
void sparkle(rgbColor c, uint8_t wait) 
{
  int pix = random(NUM_LEDS);
  setPixel(pix, c.r, c.g, c.b);
  showPixels();
  delay(wait);
  setPixel(pix, 0, 0, 0);
}

void sparkle(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{
  rgbColor color = rgbColor(red, green, blue);
  sparkle(color, wait);
}


// given a color - it randomly sets is value to white to give snow sparkle illusion
void snowSparkle(rgbColor c, uint8_t sparkleDelay, uint8_t wait) {
  setAllPixels(c.r, c.g, c.b);
  int pix = random(NUM_LEDS);
  setPixel(pix, 0xff, 0xff, 0xff);
  showPixels();
  delay(sparkleDelay);
  setPixel(pix, c.r, c.g, c.b);
  showPixels();
  delay(wait);
}
