#include <Adafruit_GFX.h> // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 11
#define OE 9
#define LAT 10
#define A A0
#define B A1
#define C A2
#define D A3
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

void setup() 
{
delay(1000);
matrix.begin();

}

void loop() 
{    
matrix.fillScreen(0);

  
// draw some text!
matrix.setTextSize(1); // size 1 == 8 pixels high
matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
matrix.setCursor(3, 3); // start at top left, with 3 pixel of spacing
uint8_t w = 0;
char *str = "Marry Christmas Feliz Navidad";

for (w=0; w<5; w++) 
{
matrix.setTextColor(Wheel(w));
matrix.print(str[w]);
}

matrix.setCursor(0, 11); // next line
for (w=5; w<15; w++) 
{
matrix.setTextColor(Wheel(w));
matrix.print(str[w]);
}

matrix.setCursor(0, 19); // next line
for (w=15; w<25; w++) 
{
matrix.setTextColor(Wheel(w));
matrix.print(str[w]);
}

delay(100000000);
}
// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(byte WheelPos) {
if(WheelPos < 8) {
return matrix.Color333(7 - WheelPos, WheelPos, 0);
} else if(WheelPos < 16) {
WheelPos -= 8;
return matrix.Color333(0, 7-WheelPos, WheelPos);
} else {
WheelPos -= 16;
return matrix.Color333(0, WheelPos, 7 - WheelPos);
}
}
