
/*
 * For some animations, we may want full brightness 
 */
void setFullBrightness()
{
  pixels.setBrightness(255);
  pixels.show();
}

void setDefaultBrightness()
{
  pixels.setBrightness(defaultSystemBrightness);
  pixels.show();
}

/*
 * helper methods
 */
void setAllPixelsOff()
{
  pixels.clear();
  pixels.show();
}

void setAllPixels(uint8_t r, uint8_t b, uint8_t g)
{
  pixels.fill(pixels.Color(r, b, g));
}

void setAllPixels(rgbColor c)
{
  pixels.fill(pixels.Color(c.r, c.g, c.b));
}

void setPixel(uint8_t i, uint32_t color)
{
  pixels.setPixelColor(i, color);
}

void setPixel(uint8_t i, uint8_t r, uint8_t g, uint8_t b)
{
  pixels.setPixelColor(i, r, g, b);
}

void showPixels()
{
  pixels.show();
}

//// Fill the strip with a single color
//void fillStrip(uint32_t c)
//{
//   for (unsigned i=0; i<pixels.numPixels(); i++)
//   {
//      pixels.setPixelColor(i, c);
//   }
//   pixels.show();
//}
