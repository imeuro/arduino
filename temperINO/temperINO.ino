#include <elapsedMillis.h>          // Timer library
#include <Adafruit_GFX.h>           // Core graphics library
#include <SPI.h>
#include <Wire.h>                   // this is needed even tho we aren't using it
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
// gsm shield
#include <SerialGSM.h>              // light library: just sms and cell signal
#include <SoftwareSerial.h>
// ora e temp
#include <DS3231.h>                 //https://github.com/YoungxHelsinki/DS3231_weekday_accessible
// reset
#include <avr/wdt.h>

#include "vars_temperINO.h"         // Vars and defines
#include "Fn_temperINO.h"           // Functions
#include "smshandler.h"             // receive and send sms



void setup(void) {

  Serial.begin(9600);
  Wire.begin();
  tft.begin();
  if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  mainUI(9);              // at startup goes in AUTO prog
  set_heat_prog(9);       // at startup goes in AUTO prog
  
  cell.begin(9600);
  cell.Verbose(true);
  cell.Boot(); 
  cell.FwdSMS2Serial();
  Serial.flush();
}

void loop(void) {

  if (timeElapsed > INTERVAL) {
    timeElapsed -= INTERVAL; //reset the timer
    // update temp, signal, clock and program
    PrintTemp();
    PrintSignal();
    PrintTime();
    PrintHeatStatus();
  }


  if (cell.ReceiveSMS()){
    ProcessMsg();
  }


 // See if there's any  touch data for us
  if (!ts.bufferEmpty())
  {   
    // Retrieve a point  
    TS_Point p = ts.getPoint(); 
    while (ts.touched()) {
        p = ts.getPoint();
    }
    // Scale using the calibration #'s
    // and rotate coordinate system
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
    int y = tft.height() - p.x;
    int x = p.y;
  
    Serial.print("(x="); Serial.print(x);
    Serial.print(", y="); Serial.print(y);
    Serial.println(")");


    // OFF,AUTO o MAN
    if (y > 160) { // fascia bassa
      if (x >210 && MANmenuOpen == 0) { // MAN
        tft.fillRect(220, 170, 90, 50, YELLOW);
        tft.setCursor(248, 188);
        tft.setTextColor(BLACK);  tft.setTextSize(2);
        tft.print("MAN");
        open_MANmenu();
      } 
      else if (x < 210 && MANmenuOpen == 1) { // MAN
        close_MANmenu();
      } 
      else if (x >= 110 && x <= 200) { // AUTO
        tft.fillRect(110, 170, 100, 50, GREEN);
        tft.setCursor(138, 188);
        tft.setTextColor(BLACK);  tft.setTextSize(2);
        tft.print("AUTO");
        mainUI(9);
        set_heat_prog(9);
      }
      else if (x < 100) { //OFF
        tft.fillRect(10, 170, 90, 50, WHITE);
        tft.setCursor(38, 188);
        tft.setTextColor(BLACK);  tft.setTextSize(2);
        tft.print("OFF");
        mainUI(0);
        set_heat_prog(0);
      }      
    }
    else if (MANmenuOpen == 1) {
      if (y > 100 && y < 170) {
        tft.setTextColor(BLACK);  tft.setTextSize(2);
        if (x > 210) { // T3
          mainUI(3);
          set_heat_prog(3);
        }
        else if (x >= 110 && x <= 200) { // T2
          mainUI(2);
          set_heat_prog(2);
        }
      else if (x < 100) { // T1
          mainUI(1);
          set_heat_prog(1);
        }
      }
    }


  }  


}

