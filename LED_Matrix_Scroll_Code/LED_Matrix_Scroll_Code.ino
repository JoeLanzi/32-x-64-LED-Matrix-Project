// Written by Joe Lanzi/ Manhattan College 
// for 64x32 LED Matrix Board

#include <RGBmatrixPanel.h>

// Arduino Pins Initialization
// Pin 11 works in the Arduino Mega as signal pin
#define CLK 11 
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

// 'true' enables double-buffering, for flicker-free, buttery smooth animation.
// '64' initializes the 64x32 board
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, true,64);

// Similar to F(), but for PROGMEM string pointers rather than literals
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

// String to be Displayed
const char str[] PROGMEM = "Merry Christmas Feliz Navidad";
int16_t    textX         = matrix.width(),
           textMin       = sizeof(str) * -14, // Display Length
           hue           = 0;
           
int8_t ball[3][4] = {
  {  3,  0,  1,  1 }, // Initial X,Y pos & velocity for 3 bouncy balls
  { 17, 15,  1, -1 },
  { 27,  4, -1,  1 }
};
static const uint16_t PROGMEM ballcolor[3] = {
  0x0080, // Green=1
  0x0002, // Blue=1
  0x1000  // Red=1
};

void setup() {
  matrix.begin();
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextSize(2); // Size of text; 1 = 8bits
}

void loop() {
  byte i;

  // Clear background
  matrix.fillScreen(0);

  // Bounce three balls around
  for(i=0; i<4; i++) {
    // Draw 'ball'
    matrix.fillCircle(ball[i][0], ball[i][1], 3, pgm_read_word(&ballcolor[i]));
    // Update X, Y position
    ball[i][0] += ball[i][2];
    ball[i][1] += ball[i][3];
    // Bounce off edges
    if((ball[i][0] == 0) || (ball[i][0] == (matrix.width() - 1)))
      ball[i][2] *= -1;
    if((ball[i][1] == 0) || (ball[i][1] == (matrix.height() - 1)))
      ball[i][3] *= -1;
  }

  // Draw big scrolly text on middle
  matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
  matrix.setCursor(textX, 9);
  matrix.print(F2(str));

  // Move text left (w/wrap), increase hue
  if((--textX) < textMin) textX = matrix.width();
  hue += 7;
  if(hue >= 1536) hue -= 1536;

  // Delay LED display
  delay(5);

  // Update display
  matrix.swapBuffers(false);
}
