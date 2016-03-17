#include <elapsedMillis.h>        // Timer library
#include <Adafruit_GFX.h>         // Core graphics library
#include <Adafruit_TFTLCD.h>      // Hardware-specific library
#include <TouchScreen.h>          // Standard touchscreen library
#include <GSM.h>                  // Basic GSM functions

#include "vars_tftdelcazzo.h"     // Vars and defines
#include "Fn_tftdelcazzo.h"       // Functions

void setup(void) {

  Serial.begin(9600);
  //Serial.println(F("TFT LCD test"));
  //Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();
  tft.begin(0x9341);//this is important!!!
  tft.setRotation(3);
  tft.fillScreen(BLACK);

  mainUI(9);        // at startup goes in AUTO prog
  set_heat_prog(9);  // at startup goes in AUTO prog
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

  if (timeElapsed > interval) {
    // update temp, signal, clock and program
    PrintTemp();
    PrintSignal();
    PrintTime();
    PrintHeatStatus();
    timeElapsed = 0;      // reset the counter to 0 so the counting starts over...
  }

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
        set_heat_prog(9);
      }
      else if (p.y < 80) { //OFF
        resetModeButtons(0);
        tft.fillRect(10, 170, 90, 50, WHITE);
        tft.setCursor(38, 188);
        tft.setTextColor(BLACK);  tft.setTextSize(2);
        tft.print("OFF");
        mainUI(0);
        set_heat_prog(0);
      }      
    }
    else if (MANmenuOpen == 1) {
      if (p.x > 110 && p.x < 240) {
        tft.setTextColor(BLACK);  tft.setTextSize(2);
        if (p.y > 160) { // T3
          resetModeButtons(3);
          mainUI(3);
          set_heat_prog(3);
        }
        else if (p.y >= 80 && p.y <= 160) { // T2
          resetModeButtons(2);
          mainUI(2);
          set_heat_prog(2);
        }
      else if (p.y < 80) { // T1
          resetModeButtons(1);
          mainUI(1);
          set_heat_prog(1);
        }
      }
    }
    
  }

}