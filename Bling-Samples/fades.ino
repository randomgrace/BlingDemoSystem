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
