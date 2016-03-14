#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

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
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MINPRESSURE 0
#define MAXPRESSURE 1000

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// 1 = MAN/T1
// 2 = MAN/T2
// 3 = MAN/T3
// 9 = AUTO
// 0 = OFF
int(prog);
int(MANmenuOpen);



void mainUI(unsigned char prog);
void resetModeButtons(unsigned char prog);
void MANmenu();

void setup(void) {
  Serial.begin(9600);
  //Serial.println(F("TFT LCD test"));
  //Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();
  tft.begin(0x9341);//this is important!!!
  tft.setRotation(3);
  tft.fillScreen(BLACK);

  mainUI(9); // at startup goes in AUTO prog
}

void loop(void) {
  
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);


  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    
    p.x = tft.width()-(map(p.x, TS_MINX, TS_MAXX, tft.width(), 0)); // da 70 a 300
    p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0)); // da 20 a 230
    //Serial.print("X = "); Serial.print(p.x);
    //Serial.print("\tY = "); Serial.println(p.y);
    
    // OFF,AUTO o MAN
    if (p.x > 240) { // fascia bassa
      if (p.y > 160 && MANmenuOpen == 0) { // MAN
        resetModeButtons(1);
        tft.fillRect(220, 170, 90, 50, YELLOW);
        tft.setCursor(248, 188);
        tft.setTextColor(BLACK);  tft.setTextSize(2);
        tft.print("MAN");
        MANmenu();
      } 
      else if (p.y >= 80 && p.y <= 160) { // AUTO
        resetModeButtons(9);
        tft.fillRect(110, 170, 100, 50, GREEN);
        tft.setCursor(138, 188);
        tft.setTextColor(BLACK);  tft.setTextSize(2);
        tft.print("AUTO");
        mainUI(9);
      }
      else if (p.y < 80) { //OFF
        resetModeButtons(0);
        tft.fillRect(10, 170, 90, 50, WHITE);
        tft.setCursor(38, 188);
        tft.setTextColor(BLACK);  tft.setTextSize(2);
        tft.print("OFF");
        mainUI(0);
      }      
    }
    else if (MANmenuOpen == 1) {
      if (p.x > 110 && p.x < 240) {
        tft.setTextColor(BLACK);  tft.setTextSize(2);
        if (p.y > 160) { // T3
          resetModeButtons(3);
          mainUI(3);
        }
        else if (p.y >= 80 && p.y <= 160) { // T2
          resetModeButtons(2);
          mainUI(2);
        }
      else if (p.y < 80) { // T1
          resetModeButtons(1);
          mainUI(1);
        }
      }
    }
    
  }

}

void mainUI(unsigned char prog) { // initial UI state
  MANmenuOpen = 0; // MANmenu is closed
  unsigned long start = micros();
  tft.setCursor(200, 13);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("Sun Mar 6 - 20.45");
  tft.drawFastHLine(0, 30, tft.width(), WHITE);
  
// ln 1: temp
  tft.setCursor(10, 65); 
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("Temp:");
  tft.setCursor(150, 60);
  tft.setTextColor(WHITE);  tft.setTextSize(4);
  tft.print("20.0");// var with real temp...
  tft.print(" C");

// ln 2: program status
  tft.setCursor(10, 115); 
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("Prog:");
 
// ln 3: mode buttons
  resetModeButtons(prog);

// ln 2: program status
  tft.setCursor(150, 110);
  tft.setTextColor(WHITE);  tft.setTextSize(4);
  if ( prog == 1 ) {tft.print("MAN/T1");}
  if ( prog == 2 ) {tft.print("MAN/T2");}
  if ( prog == 3 ) {tft.print("MAN/T3");}
  if ( prog == 9 ) {tft.print("AUTO");}
  if ( prog == 0 ) {tft.print("OFF");}
  Serial.print("prog: "); Serial.print(prog); Serial.println(); // prog  
}

void resetModeButtons(unsigned char prog) { // initial button state
  delay(200);
  tft.fillRect(10, 95, 300, 70, BLACK);
  tft.setCursor(10, 115); 
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("Prog:");
  tft.setTextSize(2);
  if ( prog == 0 ) { // OFF
    tft.fillRect(10, 170, 90, 50, WHITE);
    tft.setTextColor(BLACK);
  } else {
    tft.fillRect(10, 170, 90, 50, BLACK);
    tft.drawRect(10, 170, 90, 50, WHITE);
    tft.setTextColor(WHITE);
  }
  tft.setCursor(38, 188);
  tft.print("OFF");
  
  if ( prog == 9 ) { // AUTO
    tft.fillRect(110, 170, 100, 50, GREEN);
    tft.setTextColor(BLACK);
  } else {
    tft.fillRect(110, 170, 100, 50, BLACK);
    tft.drawRect(110, 170, 100, 50, GREEN);
    tft.setTextColor(GREEN);
  }
  tft.setCursor(138, 188);
  tft.print("AUTO");

  if ( prog >= 1 && prog <= 3 ) {
    tft.fillRect(220, 170, 90, 50, YELLOW);
    tft.setTextColor(BLACK);
  } else {
    tft.fillRect(220, 170, 90, 50, BLACK);
    tft.drawRect(220, 170, 90, 50, YELLOW);
    tft.setTextColor(YELLOW);
  }
  tft.setCursor(248, 188);
  tft.print("MAN");
}

void MANmenu() {
  MANmenuOpen = 1; // MANmenu is open
  tft.fillRect(10, 95, 300, 70, YELLOW);
  tft.setTextColor(BLACK);  tft.setTextSize(2);
  tft.setCursor(45, 125);
  tft.print("T1");
  tft.drawFastVLine(105, 105, 50, BLACK);
  tft.setCursor(148, 125);
  tft.print("T2");
  tft.drawFastVLine(215, 105, 50, BLACK);
  tft.setCursor(250, 125);
  tft.print("T3");
}
