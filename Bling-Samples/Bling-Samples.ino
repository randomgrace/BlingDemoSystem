/*
 * Bling-Samples -- 
 * 
 * Library of Adafruit NeoPixel animation examples. Also demonstrates:
 * - using rgbColor struct to break color into its components for easy reference
 * - listening on serial port for new animation commands -- start serial port to enter commands
 * - ALL animations require call to `delay()` tp listen for interruptions 
 * 
 * Important:
 * - Expected commands: ascii printable characters a and above; see `man ascii`. 
 * - Review NeoPixel setup and verify it matches your own wiring configuration
 * 
 * For more examples, see: https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
 */

/*
 * Used by the magic _delay() function for running animations
 */
#include <setjmp.h>

/*
 * Setup Adafruit NeoMatrix
 * - Important: validate PIN connection and number of LEDs
 * - Note: this NeoMatrix does not have 'w' component
 */
#include <Adafruit_NeoPixel.h>

// Configuration for our LED strip and Arduino
#define NUM_LEDS 64
#define PIN 4

// allocate our pixel memory, set interface to match our hardware
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// save the desired system wide brightness value -- 0:255 --> level 32 == 1/8th the brightness
uint8_t defaultSystemBrightness = 32;


/*
 * struct rgbColor --
 * Animations require easy access to color information: both full color, or its rgb parts
 * rgbColor struct supports this via the magic of 'union'
 *  - `union` allows storing different data types in the same memory location
 *  - different rgbColor constructors enables easy parsing of data
 * Reminder: we don't have 'w' component in our neopixels -- rgb components are represented
 */
struct rgbColor {
  // initializers
  rgbColor(){ color = 0x000000; }     // if 'w' component was present: 0x00000000
  rgbColor(uint32_t c) : color(c) {}
  rgbColor(uint8_t red, uint8_t green, uint8_t blue) : b(blue), g(green), r(red) {}
  
  union {
    uint32_t color;     // full color
    struct {
      uint8_t b;        // blue component
      uint8_t g;        // green component
      uint8_t r;        // red component
    };
  };
};

// Colors used in the animations
const rgbColor rgbColor_OFF(0, 0, 0);
const rgbColor rgbColor_RED(255, 0, 0);
const rgbColor rgbColor_GREEN(0x00ff00);
const rgbColor rgbColor_BLUE(0, 0, 255);
const rgbColor rgbColor_YELLOW(0xffff00);
const rgbColor rgbColor_ORANGE(255, 64, 0);
const rgbColor rgbColor_WHITE(0xffffff);

const rgbColor rgbColor_MAGENTA(0xff00ff);
const rgbColor rgbColor_MAGENTA_DIM(0x330033);


/* 
 * Animation library
 *  - List of animation examples for easy demonstration
 *  - loop() matches the animation to the command entered on the serial port
 * 
 * Note: for integrating with robot code, it is recommended to use animation names that
 * match the robot states. Ex. instead of 'Twinkle' use 'Intaking' which calls the
 * 'Twinkle' animation.
 */
enum {
  OFF = 0,
  SOLID,              
  SOLID_WITH_BLINK,
  TWINKLE,
  RANDOM_DOTS,
  RANDOM_SPARKLES,
  SNOW_SPARKLES,
  STROBE,
  FADE_WITH_COLOR,
  RGB_LOOP,
  INTERWEAVE_WITH_BLINK,
  INTERWEAVE_WITH_REVERSE,
  FILL_BY_ONE,
  FILL_WITH_SKIP_AND_BLINK,           
  RED_CRAWLER,
  RUNNING_LIGHTS,
  COGS_BLUE_YELLOW,
  BRIGHT_FLASH,

  
  ANIMATION_COUNT       // The number of animations
};


/*
 * Magic delay function for driving animation library
 * - Note that the delay() function mapped to _delay()
 * - Anytime there is a delay() introduced to animations, it allows to check for new commands
 * - commands drive the animation demo -- if a new command detected, we jump to the beginning
 * of the loop -- see loop()
 * 
 * important: _delay() is listening for printable characters 'a' and above. change 'commandCharacter'
 * to change what is listened for
 */

// A global variable to hold the current command to be executed
uint8_t currentCommand = OFF;

// The breadcrumb to get us back to the beginning of the loop
jmp_buf env;

// Our magic delay function
void _delay(uint16_t timeout)
{
  while (timeout != 0)
  {
    delay(1);
    timeout--;

    // If there are any characters available on the serial port, read them
    while (Serial.available() > 0)
    {
      char commandCharacter;
      commandCharacter = Serial.read();
      // use the ASCII table to identify the >= commandCharacter order
      // in this case we are looking for 'a'
      if (isprint(commandCharacter) && (commandCharacter >= 'a'))
      {
        uint8_t command = commandCharacter - 'a';
        if (command < ANIMATION_COUNT)
        {
          // Found a valid command!
          if (command != currentCommand)
          {
            // It's a new command!
            currentCommand = command;
            // Jump back to the top of the loop
            longjmp(env, 1);
          }
        }
      }
    }
  }
}

// redefining delay function
#define delay _delay

/*
 * Long waited setup() -- clear the strip and set brightness level
 */
void setup() {  
  Serial.begin(9600);   // required for listening to new commands
  // IMPORTANT: update this message if the command pattern changes
  Serial.println("Enter printable commands starting with 'a' (note a is OFF)");

  // Initialize all pixels to 'off' with default brightness
  pixels.begin();
  // set pixel brightness
  setDefaultBrightness();
  pixels.clear();
  pixels.show();    
}


/*
 * loop() --
 * - setup breadcrumb for magic _delay()
 * - add animations to switch statement --> ensure matches the animation library above
 */
void loop() {
  // Save a breadcrumb of where to jump back to
  if (setjmp(env) != 0)
  {
    // If we jumped back (non-zero return value), then exit the loop()
    // and it will be re-run again, leaving a new breadcrumb.
    return;
  }
  
  // clear the strip between animation changes
  pixels.clear();
  setDefaultBrightness();
  pixels.show();
  

  // From here everything should be interruptable (to switch animations)
  // as long as the animation code uses the `delay()` function.


  // Take the current command and set the parameters, i.e. animations
  switch (currentCommand)
  {
    // Annimations -- commands to match the enums above!
    case OFF:
      // all pixels are off
      solid(rgbColor_OFF);
      break;

    case SOLID:
      // all pixels set to magenta
      /* see solid() for use of helpers and basic animations */
      solid(rgbColor_MAGENTA);
      break;

    case SOLID_WITH_BLINK:
      // fills strip w/ ORANGE, waits & clears off pixels; repeats
      // void solidWithBlink(rgbColor c, uint8_t wait)
      solidWithBlink(rgbColor_ORANGE, 500);
      break;  
     
    case TWINKLE:
      // randomly displays LED given count of pixels -- 
      // single boolean determines if only one pixel shown at each cycle
      // void twinkle(rgbColor c, uint8_t cnt, int wait, boolean single) 
      twinkle(rgbColor_ORANGE, 5, 20, false);
      break;

    case RANDOM_DOTS:
      // number of LED groups w/ spacing in between to display
      // this example: 3 LED groups w/ spacing of 7 between groups
      // void randomDots(rgbColor c, uint8_t width, uint8_t space)
      randomDots(rgbColor_MAGENTA, 3, 8);
      break;

    case RANDOM_SPARKLES:
      // similar to twinkle -- demonstrates randomness
      // example of different method calls
      // void sparkle(rgbColor c, uint8_t wait) 
      //sparkle(color_white, 30);
      //sparkle(random(255), random(255), random(255), 30);
      sparkle(random(0xffffff), 30);
      break;

    case SNOW_SPARKLES:
      // given a starting color, randomly sets a pixel value to white w/ delay
      // snowSparkle(rgbColor c, uint8_t sparkleDelay, uint8_t wait)
      snowSparkle(rgbColor_MAGENTA_DIM, 10, 50);
      break;

    case STROBE:
      // play strobe color w/ # of strobes per cycle and wait between strobes
      // void strobe(rgbColor c, uint8_t numStrobes, int flashDelay, int strobePause)
      strobe(rgbColor_RED, 7, 50, 1000);
      break;

    case FADE_WITH_COLOR:
      // given a color it fades in/out -- can pass the full color, or just rgb values
      // fadeInOut(0xff, 0x00, 0xff, 3);
      fadeInOut(rgbColor_BLUE, 3);
      break;

    case RGB_LOOP:
      // fades in/out of the rgb loop
      RGBLoop(7);
      break;

    case INTERWEAVE_WITH_BLINK:
      // starting w/ 0th LED, interweave two colors one pixel at a time
      // blinkOff and restart again
      interweaveFillByOne(rgbColor_YELLOW.color, rgbColor_BLUE.color, 50);
      blinkOffWithDelay(100);
      break;

    case INTERWEAVE_WITH_REVERSE:
      // start w/ 0th LED, interweave two colors one pixel at a time
      // when reached to the end, reverse the colors
      interweaveFillByOne(rgbColor_YELLOW.color, rgbColor_BLUE.color, 50);
      reverseInterweaveFillByOne(rgbColor_BLUE.color, rgbColor_YELLOW.color, 50);
      break;

    case FILL_BY_ONE:
      // flash(FLASH_TIME_INTERVAL, WHITE, 255);
      // demonstrates how rgbColor's color component is passed
      fillPixelByPixel(rgbColor_BLUE, 50);
      break;

    case FILL_WITH_SKIP_AND_BLINK:
      // fill every other pixel: rotate MAGENTA, YELLOW, BLUE
      // demonstrates for loop increments
      fillPixelsWithSkip(rgbColor_MAGENTA.color, 0, 3);
      fillPixelsWithSkip(rgbColor_YELLOW.color, 1, 3);
      fillPixelsWithSkip(rgbColor_BLUE.color, 2, 3);
      
      // and, add a blink off
      blinkOffWithDelay(1000);
      break;

    case RED_CRAWLER:
      // void crawler(uint16_t timeInterval, uint32_t color, uint8_t length)
      crawler(10, rgbColor_RED.color, 30);
      break;

    // TODO: TEST the FOLLOWING ANIMATIONS
    case RUNNING_LIGHTS:
      // void runningLights(rgbColor color, uint8_t wait) 
      runningLights(rgbColor_MAGENTA, 50);
      break;
      
    case COGS_BLUE_YELLOW:
      cogs(rgbColor_BLUE.color, rgbColor_YELLOW.color);
      break;
      
    case BRIGHT_FLASH:
      // FLASH_TIME_INTERVAL = 250
      flash(250, rgbColor_WHITE.color, 255);
      break;

    default:
      solid(rgbColor_OFF);
      // at the end of the enum list -- reset the current command
      currentCommand = OFF;
  }
}
