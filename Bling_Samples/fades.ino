/*
 * Demonstration of different fade patterns
 */

/*
 * fade in/out of rgb colors
 * wait as delay changes the heartbeat of the animation
 *   - for each rgb color
 *   - fades in that pure color by increasing the intensity until full on, 255
 *   - fades out
 *   - cycles to next r, g, or b value
 */
void RGBLoop(uint8_t wait)
{
  // 
  for(int setRGB = 0; setRGB < 3; setRGB++ ) {        // for each rgb value   
    // Fade IN
    for(int k = 0; k < 256; k++) {     // 1st increase its brightness
      switch(setRGB) {   
        case 0: setAllPixels(k,0,0); break;
        case 1: setAllPixels(0,k,0); break;
        case 2: setAllPixels(0,0,k); break;
      }
      showPixels();
      delay(wait);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) {    // 2nd decrease its brightness
      switch(setRGB) {
        case 0: setAllPixels(k,0,0); break;
        case 1: setAllPixels(0,k,0); break;
        case 2: setAllPixels(0,0,k); break;
      }
      showPixels();
      delay(wait);
    }
  }
}


/*
 * Given a color fade in & out
 * Note: start and end values for k determines if color is ever off
 */
void fadeInOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait){
  float r, g, b;

  // fade in: increase k intensity ratio
  for(int k = 50; k < 256; k=k+1)    // experiment w/ starting 'k' value
  {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAllPixels(r,g,b);
    showPixels();
    delay(wait);
  }

  // fade out: decrease k intensity ratio
  for(int k = 255; k >= 50; k=k-2)  // experiment w/ ending 'k' value
  {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAllPixels(r,g,b);
    showPixels();
    delay(wait);
  }
}

void fadeInOut(rgbColor color, uint8_t wait)
{
  fadeInOut(color.r, color.g, color.b, wait);
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      pixels.setPixelColor(i, *c, *(c+1), *(c+2));
    }
    showPixels();
    delay(SpeedDelay);
  }
}

// used by rainbowCycle and theaterChaseRainbow
byte * Wheel(byte WheelPos) {
  static byte c[3];

  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

void theaterChaseRainbow(int SpeedDelay) {
  byte *c;

  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < NUM_LEDS; i=i+3) {
          c = Wheel( (i+j) % 255);
          pixels.setPixelColor(i+q, *c, *(c+1), *(c+2));    //turn every third pixel on
        }
        showPixels();

        delay(SpeedDelay);

        for (int i=0; i < NUM_LEDS; i=i+3) {
          pixels.setPixelColor(i+q, 0,0,0);        //turn every third pixel off
        }
    }
  }
}
