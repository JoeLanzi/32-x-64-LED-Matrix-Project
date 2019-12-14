#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <MD_DS1307.h>
#include <Wire.h>
#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);
// Global variables
#define MAX_MESG  4
#define MAX_MES  20
unsigned int NewRTCh = 24;
unsigned int NewRTCm = 60;
unsigned int NewRTCs = 60;
char szTime[12];    // mm:ss\0
char szMesg[MAX_MESG+1] = "";
char szDate[MAX_MES+1] = "";
char *mon2str(uint8_t mon, char *psz, uint8_t len)
// Get a label from PROGMEM into a char array
{
  static const char str[][4] PROGMEM =
  {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };

  *psz = '\0';
  mon--;
  if (mon < 12)
  {
    strncpy_P(psz, str[mon], len);
    psz[len] = '\0';
  }

  return(psz);
}

char *dow2str(uint8_t code, char *psz, uint8_t len)
{
  static const char str[][10] PROGMEM =
  {
    "Su", "Mo", "Tu", "We",
    "Th", "Fr", "Sa"
  };

  *psz = '\0';
  code--;
  if (code < 7)
  {
    strncpy_P(psz, str[code], len);
    psz[len] = '\0';
  }

  return(psz);
}
void getTime(char *psz, bool f = true)
// Code for reading clock time
{
 
  RTC.readTime();
    if (NewRTCh != RTC.h) 
  {
  sprintf(psz, "%02d", RTC.h);
  matrix.setCursor(2, 4); 
  matrix.setTextSize(2);
    matrix.setTextColor(matrix.Color333(7, 0, 7));
  matrix.fillRect(2, 4, 64, 14, matrix.Color333(0, 0, 0));
    matrix.print(szTime);
  sprintf(psz, "%02d", RTC.m);
  matrix.setCursor(28, 4); 
    matrix.setTextColor(matrix.Color333(7, 0, 7));
  matrix.fillRect(25, 4, 25, 14, matrix.Color333(0, 0, 0));
    matrix.print(szTime);
  matrix.setCursor(21, 4); 
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.fillRect(25, 8, 2, 6, matrix.Color333(0, 0, 0));
    matrix.print(f ? ':' : ' ');
  matrix.setCursor(52, 9); 
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 7, 0));
  matrix.fillRect(52, 9, 11, 7, matrix.Color333(0, 0, 0));
  sprintf(psz, "%02d", RTC.s);
    matrix.print(szTime);
        getDate(szDate);
  matrix.setCursor(5, 20);
  matrix.fillRect(5, 20, 54, 8, matrix.Color333(0, 0, 0));
  uint8_t y = 0;
  for (y=0; y<10; y++) {
    matrix.setTextColor(Wheel(y));
    matrix.print(szDate[y]);
    }
        getDay(szMesg);
  matrix.setTextSize(1);
  matrix.setCursor(52, 1);
  matrix.setTextColor(matrix.Color333(0, 7, 0));
  matrix.fillRect(52, 1, 11, 7, matrix.Color333(0, 0, 0));
    matrix.print(szMesg);
      NewRTCh=RTC.h;
    }
    else if (NewRTCm != RTC.m) 
  {
  sprintf(psz, "%02d", RTC.m);
  matrix.setCursor(28, 4); 
  matrix.setTextSize(2);
    matrix.setTextColor(matrix.Color333(7, 0, 7));
  matrix.fillRect(25, 4, 25, 14, matrix.Color333(0, 0, 0));
    matrix.print(szTime);
  matrix.setCursor(21, 4); 
  matrix.setTextColor(matrix.Color333(0, 0, 7));
  matrix.fillRect(25, 8, 2, 6, matrix.Color333(0, 0, 0));
    matrix.print(f ? ':' : ' ');
  matrix.setCursor(52, 9); 
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(0, 7, 7));
  sprintf(psz, "%02d", RTC.s);
  matrix.fillRect(52, 9, 11, 7, matrix.Color333(0, 0, 0));
    matrix.print(szTime);
      NewRTCm=RTC.m;
    }
    else if (NewRTCs != RTC.s/10) 
  {
  matrix.setCursor(21, 4); 
  matrix.setTextSize(2);
  matrix.setTextColor(matrix.Color333(0, 7, 0));
  matrix.fillRect(25, 8, 2, 6, matrix.Color333(0, 0, 0));
    matrix.print(f ? ':' : ' ');
  matrix.setCursor(52, 9); 
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(0, 0, 7));
  sprintf(psz, "%02d", RTC.s);
  matrix.fillRect(52, 9, 11, 7, matrix.Color333(0, 0, 0));
    matrix.print(szTime);
      NewRTCs=RTC.s/10;
    }
    else
  {
  matrix.setCursor(21, 4); 
  matrix.setTextSize(2);
  matrix.setTextColor(matrix.Color333(0, 0, 7));
  matrix.fillRect(25, 8, 2, 6, matrix.Color333(0, 0, 0));
    matrix.print(f ? ':' : ' ');
  matrix.setCursor(52, 9); 
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  sprintf(psz, "%02d", RTC.s);
  matrix.fillRect(58, 9, 5, 7, matrix.Color333(0, 0, 0));
    matrix.print(szTime);
    }
  }
void getDate(char *psz)
// Code for reading date
{
  char  szBuf[10];
  sprintf(psz, "%02d%s%04d", RTC.dd, mon2str(RTC.mm, szBuf, sizeof(szBuf)-1), RTC.yyyy);
}
void getDay(char *psz)
// Code for reading day date
{
  dow2str(RTC.dow, szMesg, MAX_MESG);
}

void setup() {

  matrix.begin();
  matrix.setTextWrap(false);
  RTC.control(DS1307_CLOCK_HALT, DS1307_OFF);
  RTC.control(DS1307_12H, DS1307_OFF);
}

void loop() {
  static uint32_t lastime = 0; // millis() memory
  static bool flasher = false;  // seconds passing flasher
  if (millis() - lastime >= 1000)
  
   {
    lastime = millis();
    getTime(szTime, flasher);
    flasher = !flasher;
  }
 
}


// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(byte WheelPos) {
  if(WheelPos < 2) {
   return matrix.Color333(0, 7, 0);
  } else if(WheelPos < 5) {
   WheelPos -= 2;
   return matrix.Color333(7 , 0, 0);
  } else {
   WheelPos -= 5;
   return matrix.Color333(0, 7, 0);
  }
}
