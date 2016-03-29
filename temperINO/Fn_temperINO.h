// functions used in tftdelcazzo.ino

//////////////////////////////////////////////
// GET DATA
//////////////////////////////////////////////

// temperatura
// ===========================================
float GetTemp() {
  //read thermistor value
  float tempC = Clock.getTemperature();
  //tempC = tempC -2; // calibration :)
  return tempC;
}
void PrintTemp() {
  float measuredTemp = GetTemp();
  tft.setCursor(10, 65); 
  tft.setTextColor(WHITE);  
  tft.setTextSize(3);
  tft.println("Temp:");
  tft.setCursor(150, 60);
  tft.setTextColor(WHITE);  
  tft.setTextSize(4);
  tft.fillRect(150, 60, 100, 30, BLACK);
  tft.print(measuredTemp,1);// var with real temp...
  tft.print(" C");
}


// giorno e ora
// ===========================================
String printDigits(int digits)
{
  String gigi;
  String addendum;
  if(digits < 10) {
    addendum = "0";
  }
  gigi = addendum+digits;
  return gigi;
}
String GetTime() {
  String currenttime;
  String mese;
  byte curweekday = Clock.getDoW();
  switch (curweekday) {
  case 1: 
    giorno = "Mon"; 
    break;
  case 2: 
    giorno = "Tue"; 
    break;
  case 3: 
    giorno = "Wed"; 
    break;
  case 4: 
    giorno = "Thu"; 
    break;
  case 5: 
    giorno = "Fri"; 
    break;
  case 6: 
    giorno = "Sat"; 
    break;
  case 7: 
    giorno = "Sun"; 
    break;          
  }
  byte curday = Clock.getDate();
  byte curmonth = Clock.getMonth(Century);
  switch (curmonth) {
  case 1:  
    mese = "Jan"; 
    break;
  case 2:  
    mese = "Feb"; 
    break;
  case 3:  
    mese = "Mar"; 
    break;
  case 4:  
    mese = "Apr"; 
    break;
  case 5:  
    mese = "May"; 
    break;
  case 6:  
    mese = "Jun"; 
    break;
  case 7:  
    mese = "Jul"; 
    break;          
  case 8:  
    mese = "Aug"; 
    break;          
  case 9:  
    mese = "Sep"; 
    break;          
  case 10: 
    mese = "Oct"; 
    break;          
  case 11: 
    mese = "Nov"; 
    break;          
  case 12: 
    mese = "Dec"; 
    break;          
  }
  byte curyear = Clock.getYear();
  byte curhour = Clock.getHour(h12, PM);
  byte curminute = Clock.getMinute();
  ora = curhour;
  currenttime = giorno+" "+printDigits(curday)+" "+mese+" - "+printDigits(curhour)+":"+printDigits(curminute);
  return currenttime;
}

void PrintTime() {
  tft.fillRect(200,13,120,15,BLACK);
  tft.setCursor(200, 13);
  tft.setTextColor(WHITE);  
  tft.setTextSize(1);
  tft.println(GetTime());
  tft.drawFastHLine(0, 30, tft.width(), WHITE);
}

// segnale rete GSM
// ===========================================
void PrintSignal() {
int ricezione;
  ricezione=cell.checkSignal();
  Serial.println("===========");
  Serial.println(ricezione);
  Serial.println("/===========");
  tft.fillRect(15,8,45,15,BLACK);
  tft.fillRect(15,19,3,3,WHITE);
  tft.fillRect(20,16,3,6,WHITE);
  tft.fillRect(25,13,3,9,WHITE);
  tft.fillRect(30,10,3,12,SILVER);
  //tft.drawRect(39,8,5,16,WHITE);
  tft.setCursor(40, 13);
  tft.setTextColor(WHITE);  
  tft.setTextSize(1);
  tft.print("TIM - ");
  tft.print(ricezione);
}

// stato caldaia
// ===========================================
void PrintHeatStatus() {
  float measuredTemp = GetTemp();
  tft.setCursor(90, 13);
  tft.fillRect(115,13,75,15,BLACK);
  tft.setTextColor(SILVER);  
  tft.setTextSize(1);
  switch (currentprog) {
  case 0 : // OFF : do nothing, it's probably summer!
    tft.println("Heating:OFF");
    humanread_prog = "OFF";
    break;
  case 1 : // MAN/T1 : do not drop below 8 C
    if ( measuredTemp <= 8.00 ) {
      tft.println("Heating:ON");
    } 
    else {
      tft.println("Heating:OFF");
    }			
    humanread_prog = "T1";
    break;
  case 2 : // MAN/T2 : do not drop below 17.5 C
    if ( measuredTemp <= 17.50 ) {
      tft.println("Heating:ON");
    } 
    else {
      tft.println("Heating:OFF");
    }
    humanread_prog = "T2";
    break;
  case 3 : // MAN/T3 : do not drop below 20.5 C
    if ( measuredTemp <= 20.50 ) {
      tft.println("Heating:ON");
    } 
    else {
      tft.println("Heating:OFF");
    }
    humanread_prog = "T3";
    break;
  default : // AUTO (9) : do not drop below 8 C except Fri 17:00 -> 21.59 and Sat 10:00 -> 13:59
    if ( (giorno == "Fri" && (ora >= 17 && ora <= 22)) || (giorno == "Sat" && (ora >= 10 && ora < 14)) ) { 
      if ( measuredTemp <= 17.50 ) {
        tft.println("Heating:ON");
      } 
      else {
        tft.println("Heating:OFF");
      }
    } 
    else {
      if ( measuredTemp <= 8.0 ) {
        tft.println("Heating:ON");
      } 
      else {
        tft.println("Heating:OFF");
      }
    }
    humanread_prog = "AUTO";
    break;
  }
}
//////////////////////////////////////////////








//////////////////////////////////////////////
// DRAW THE UI
//////////////////////////////////////////////

void resetModeButtons(unsigned char prog) { // resets button state after prog is set
  MANmenuOpen = 0; // MANmenu is closed
  delay(200);
  tft.fillRect(10, 95, 300, 70, BLACK);
  tft.setCursor(10, 115); 
  tft.setTextColor(WHITE);  
  tft.setTextSize(3);
  tft.println("Prog:");
  tft.setTextSize(2);

  //reset all buttons:
  //OFF
  tft.fillRect(10, 170, 90, 50, BLACK);
  tft.drawRect(10, 170, 90, 50, WHITE);
  tft.setTextColor(WHITE);
  tft.setCursor(38, 188);
  tft.print("OFF");

  // AUTO
  tft.fillRect(110, 170, 100, 50, BLACK);
  tft.drawRect(110, 170, 100, 50, GREEN);
  tft.setTextColor(GREEN);
  tft.setCursor(138, 188);
  tft.print("AUTO");

  // T1,T2,T3
  tft.fillRect(220, 170, 90, 50, BLACK);
  tft.drawRect(220, 170, 90, 50, YELLOW);
  tft.setTextColor(YELLOW);
  tft.setCursor(248, 188);
  tft.print("MAN");

  // swich on the correct one
  switch (prog) {
  case 0:   // OFF
    tft.fillRect(10, 170, 90, 50, WHITE);
    tft.setTextColor(BLACK);
    tft.setCursor(38, 188);
    tft.print("OFF");
    break;
  case 9:   // AUTO
    tft.fillRect(110, 170, 100, 50, GREEN);
    tft.setTextColor(BLACK);
    tft.setCursor(138, 188);
    tft.print("AUTO");
    break;
  default: // T1,T2,T3
    tft.fillRect(220, 170, 90, 50, YELLOW);
    tft.setTextColor(BLACK);
    tft.setCursor(248, 188);
    tft.print("MAN");
    break;
  }


/*
  if ( prog == 0 ) { // OFF
    tft.fillRect(10, 170, 90, 50, WHITE);
    tft.setTextColor(BLACK);
  } 
  else {
    tft.fillRect(10, 170, 90, 50, BLACK);
    tft.drawRect(10, 170, 90, 50, WHITE);
    tft.setTextColor(WHITE);
  }

  if ( prog == 9 ) { // AUTO
    tft.fillRect(110, 170, 100, 50, GREEN);
    tft.setTextColor(BLACK);
  } 
  else {
    tft.fillRect(110, 170, 100, 50, BLACK);
    tft.drawRect(110, 170, 100, 50, GREEN);
    tft.setTextColor(GREEN);
  }
  tft.setCursor(138, 188);
  tft.print("AUTO");

  if ( prog >= 1 && prog <= 3 ) {
    tft.fillRect(220, 170, 90, 50, YELLOW);
    tft.setTextColor(BLACK);
  } 
  else {
    tft.fillRect(220, 170, 90, 50, BLACK);
    tft.drawRect(220, 170, 90, 50, YELLOW);
    tft.setTextColor(YELLOW);
  }
  tft.setCursor(248, 188);
  tft.print("MAN");
*/
}

void mainUI(unsigned char prog) { // initial UI state
  MANmenuOpen = 0; // MANmenu is closed
  unsigned long start = micros();
  //PrintSignal();
  //PrintHeatStatus();
  //PrintTime();

  // ln 1: temp
  PrintTemp();

  // ln 2: program status
  tft.setCursor(10, 115); 
  tft.setTextColor(WHITE);  
  tft.setTextSize(3);
  tft.println("Prog:");

  // ln 3: mode buttons
  resetModeButtons(prog);

  // ln 2: program status
  tft.setCursor(150, 110);
  tft.setTextColor(WHITE);  
  tft.setTextSize(4);
  if ( prog == 1 ) {
    tft.print("MAN/T1");
  }
  if ( prog == 2 ) {
    tft.print("MAN/T2");
  }
  if ( prog == 3 ) {
    tft.print("MAN/T3");
  }
  if ( prog == 9 ) {
    tft.print("AUTO");
  }
  if ( prog == 0 ) {
    tft.print("OFF");
  }
  Serial.print("new prog: "); 
  Serial.print(prog); 
  Serial.println(MANmenuOpen); // prog  
}

void open_MANmenu() {
  MANmenuOpen = 1; // MANmenu is open
  tft.fillRect(10, 95, 300, 70, YELLOW);
  tft.setTextColor(BLACK);
  tft.setCursor(45, 115);
  tft.setTextSize(2); 
  tft.println("T1");
  tft.setCursor(42, 140);
  tft.setTextSize(1); 
  tft.println("8.0 C");
  tft.drawFastVLine(105, 105, 50, BLACK);
  tft.setCursor(148, 115);
  tft.setTextSize(2); 
  tft.println("T2");
  tft.setCursor(143, 140);
  tft.setTextSize(1); 
  tft.println("17.5 C");
  tft.drawFastVLine(215, 105, 50, BLACK);
  tft.setCursor(250, 115);
  tft.setTextSize(2); 
  tft.println("T3");
  tft.setCursor(245, 140);
  tft.setTextSize(1); 
  tft.println("20.5 C");
}
void close_MANmenu() {
  MANmenuOpen = 0; // MANmenu is closed
  mainUI(currentprog);
}
// END DRAW THE UI
//////////////////////////////////////////////






//////////////////////////////////////////////
// SET DATA
//////////////////////////////////////////////
int set_heat_prog(unsigned char set_prog) {
  currentprog = set_prog;
  mainUI(currentprog);
  return currentprog;
}
