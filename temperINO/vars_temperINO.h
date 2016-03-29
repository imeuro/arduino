//////////////////////////////////////
// Project Components setup:
//////////////////////////////////////

// Pixnor UNO R3 2.8'' TFT
// ===================================
#define USE_ADAFRUIT_SHIELD_PINOUT

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// These are the pins for the shield!
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#ifdef __SAM3X8E__
  #define TS_MINX 125
  #define TS_MINY 170
  #define TS_MAXX 880
  #define TS_MAXY 940
#else
  #define TS_MINX  0
  #define TS_MINY  120
  #define TS_MAXX  920
  #define TS_MAXY  940
#endif

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);


// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 //A3 // Chip Select goes to Analog 3
#define LCD_CD A2 //A2 // Command/Data goes to Analog 2
#define LCD_WR A1 //A1 // LCD Write goes to Analog 1
#define LCD_RD A0 //A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 //reset // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	RED     0xF800
#define	GREEN   0x07E0
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define SILVER  0xA510

#define MINPRESSURE 0
#define MAXPRESSURE 1000

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


// Arduino GSM Shield
// ===================================
SerialGSM cell(12,11);

// Clock w/ battery + Temp sensor
// ===================================
DS3231 Clock;
bool Century=false;
bool h12;
bool PM;

// Relay (2) breakout board
// ===================================

//////////////////////////////////////
// MY VARS
//////////////////////////////////////

// 1 = MAN/T1
// 2 = MAN/T2
// 3 = MAN/T3
// 9 = AUTO
// 0 = OFF
int currentprog = 9;
String humanread_prog;

byte MANmenuOpen = 0;

String giorno;
byte ora;

elapsedMillis timeElapsed;
unsigned int interval = 30000; // milliseconds

float tempC;
char* cellsignal;
