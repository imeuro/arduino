//////////////////////////////////////
// Project Components setup:
//////////////////////////////////////

// Adafruit 2.8'' TFT v2.0
// ===================================
// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// The STMPE610 uses hardware SPI on the shield, and #8
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

// The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	RED     0xF800
#define	GREEN   0x07E0
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define SILVER  0xA510

#define MINPRESSURE 0
#define MAXPRESSURE 1000

// Arduino GSM Shield
// ===================================
SerialGSM cell(2,3);

// Clock w/ battery + Temp sensor
// ===================================
DS3231 Clock;


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

byte currentprog = 9;
byte MANmenuOpen = 0;
String giorno;
byte curhour;

elapsedMillis timeElapsed;
#define INTERVAL 5000 // milliseconds

float tempC;

