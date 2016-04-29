#include <elapsedMillis.h>          // Timer library
#include <Adafruit_GFX.h>           // Core graphics library
#include <SPI.h>
#include <Wire.h>      // this is needed even tho we aren't using it
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
// gsm shield
#include <SerialGSM.h>              // light library: just sms and cell signal
#include <SoftwareSerial.h>
// ora e temp
#include <DS3231.h>                 //https://github.com/YoungxHelsinki/DS3231_weekday_accessible
// reset
#include <avr/wdt.h>

#include "vars_temperINO.h"       // Vars and defines
#include "Fn_temperINO.h"         // Functions
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
 // See if there's any  touch data for us
  if (ts.bufferEmpty()) {
    return;
  }
  /*
  // You can also wait for a touch
  if (! ts.touched()) {
    return;
  }
  */

  // Retrieve a point  
  TS_Point p = ts.getPoint();

  // Scale from ~0->4000 to tft.width using the calibration #'s
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

  
  //Serial.print("("); Serial.print(p.x);
  //Serial.print(", "); Serial.print(p.y);
  //Serial.println(")");
  

  if (timeElapsed > interval) {
    // update temp, signal, clock and program
    PrintTemp();
    PrintSignal();
    PrintTime();
    PrintHeatStatus();
    timeElapsed = 0;      // reset the counter to 0 so the counting starts over...
  }


  if (cell.ReceiveSMS()){
    ProcessMsg();
  }
  
    
    // OFF,AUTO o MAN
    if (p.x < 130) { // fascia bassa
      if (p.y >160 && MANmenuOpen == 0) { // MAN
        tft.fillRect(220, 170, 90, 50, YELLOW);
        tft.setCursor(248, 188);
        tft.setTextColor(BLACK);  tft.setTextSize(2);
        tft.print("MAN");
        open_MANmenu();
      } 
      else if (p.y < 80 && MANmenuOpen == 1) { // MAN
        close_MANmenu();
      } 
      else if (p.y >= 80 && p.y <= 160) { // AUTO
        tft.fillRect(110, 170, 100, 50, GREEN);
        tft.setCursor(138, 188);
        tft.setTextColor(BLACK);  tft.setTextSize(2);
        tft.print("AUTO");
        mainUI(9);
        set_heat_prog(9);
      }
      else if (p.y < 80) { //OFF
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
          mainUI(3);
          set_heat_prog(3);
        }
        else if (p.y >= 80 && p.y <= 160) { // T2
          mainUI(2);
          set_heat_prog(2);
        }
      else if (p.y < 80) { // T1
          mainUI(1);
          set_heat_prog(1);
        }
      }
    }
  


}

