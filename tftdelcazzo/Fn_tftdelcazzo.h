// functions used in tftdelcazzo.ino


void resetModeButtons(unsigned char prog) { // initial button state
  delay(200);
  tft.fillRect(10, 95, 300, 70, BLACK);
  tft.setCursor(10, 115); 
  tft.setTextColor(SILVER);  tft.setTextSize(3);
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

void PrintTemp() {
  //read thermistor value
  long a = analogRead(analogPin);
  //the calculating formula of temperature
  float tempC = beta /(log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
  //tempC = tempC -2; // calibration :)

  tft.setCursor(150, 60);
  tft.setTextColor(SILVER);  tft.setTextSize(4);
  tft.fillRect(150, 60, 100, 30, BLACK);
  tft.print(tempC,1);// var with real temp...
  tft.print(" C");
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
  tft.setTextColor(SILVER);  tft.setTextSize(3);
  tft.println("Temp:");
  PrintTemp();

// ln 2: program status
  tft.setCursor(10, 115); 
  tft.setTextColor(SILVER);  tft.setTextSize(3);
  tft.println("Prog:");
 
// ln 3: mode buttons
  resetModeButtons(prog);

// ln 2: program status
  tft.setCursor(150, 110);
  tft.setTextColor(SILVER);  tft.setTextSize(4);
  if ( prog == 1 ) {tft.print("MAN/T1");}
  if ( prog == 2 ) {tft.print("MAN/T2");}
  if ( prog == 3 ) {tft.print("MAN/T3");}
  if ( prog == 9 ) {tft.print("AUTO");}
  if ( prog == 0 ) {tft.print("OFF");}
  Serial.print("prog: "); Serial.print(prog); Serial.println(); // prog  
}