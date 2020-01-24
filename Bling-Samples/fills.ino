/*
 * Demonstrate filling dots 
 */
 
/* 
 *  Fill the dots one after the other with a color
 *  Specify color value & delay time
 */

/*
 * Start basic -- with solid colors
 * Important -- always add 'delay()' to listen for interrupts for new commands
 */
 
void solid(rgbColor c)
{
  setAllPixels(c.color);
  showPixels();
  delay(10);
}

void solidWithFullBrightness(rgbColor c, uint8_t brightness)
{
  setFullBrightness();
  solid(c);
}
 
void solidWithBlink(rgbColor c, uint8_t wait)
{
  solid(c);
  blinkOffWithDelay(wait);
}


 /*
  * One by one set pixel colors
  */
 void fillPixelByPixel(rgbColor c, uint8_t wait)
 {
  // start w/ pixel 0, set color, show color, wait and do it again
  for(uint16_t i=0; i<pixels.numPixels(); i++) 
  {
    // pass the color component of rgbColor 
    setPixel(i, c.color);
    showPixels();

    delay(wait);
  }
}

/*
 * Turns off the pixels creating a 'blink' animation
 */
void blinkOffWithDelay(uint8_t wait)
{
  // wait prior to turning off pixels
  delay(wait);
  setAllPixelsOff();
  delay(wait);
}

 
/*
 * Fill every other pixel
 * Specify the starting pixel and skip count
 */
void fillPixelsWithSkip(uint32_t color, uint8_t start, uint8_t skip)
{
  // using the starting pixel, turn on every other pixel by skip count
  for (uint8_t i=start; i < pixels.numPixels(); i += skip)
  {
    pixels.setPixelColor(i, color);
  }
  
  pixels.show();
}

/*
 * given pixel position, set color1 or color2
 * shows % operation
 */
void setOddEvenColors(uint8_t pixel, uint32_t color1, uint32_t color2)
{
    if (pixel % 2 == 0)   // if even pixel(0, 2, 4, ...) , color 1
    {
      pixels.setPixelColor(pixel, color1);
    }
    else            // if odd pixel(1, 3, 5, ...), color 2
    {
      pixels.setPixelColor(pixel, color2);
    }

}

/*
 * Interweave two colors on the strip
 */
void interweaveFillByOne(uint32_t color1, uint32_t color2, uint8_t wait)
{
  // set pixels one at a time, remembering to interweave colors
  for (uint8_t i=0; i < pixels.numPixels(); i++)
  {
    setOddEvenColors(i, color1, color2);

    // show pixels with delay & repeat till full strip is filled
    pixels.show();
    delay(wait);
  }
}

/*
 * reverseInterweaveFillByOne -- reverses the color combo
 * note: using getPixelColor() to change color value can be misleading due to change in brightness
 */
void reverseInterweaveFillByOne(uint32_t color1, uint32_t color2, uint8_t wait)
{
  uint32_t color;
  
  for (uint8_t i=pixels.numPixels(); i>0; i--)
  {
    setOddEvenColors(i, color1, color2);

    // show pixels w/ delay & repeat till the beginning of the strip is reached
    pixels.show();
    delay(wait);
  }
}

/*
 * running lights
 * demonstrates the rgbStruct parsing
 */
void runningLights(rgbColor color, uint8_t wait) 
{
  int pos = 0;
  uint8_t red = color.r;
  uint8_t green = color.g;
  uint8_t blue = color.b;
  
  for(int j=0; j<NUM_LEDS*2; j++)
  {
      pos++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+pos) * 127 + 128)/255)*red,
                   ((sin(i+pos) * 127 + 128)/255)*green,
                   ((sin(i+pos) * 127 + 128)/255)*blue);
      }
     
      showPixels();
      delay(delay);
  }
}
