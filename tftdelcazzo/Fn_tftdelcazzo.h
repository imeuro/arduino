// functions used in tftdelcazzo.ino

//////////////////////////////////////////////
// GET DATA
//////////////////////////////////////////////

// temperatura
// ===========================================
float GetTemp() {
  //read thermistor value
  float tempC = RTC.temperature() / 4.;
  //tempC = tempC -2; // calibration :)
  return tempC;
}
void PrintTemp() {
  float measuredTemp = GetTemp();
  tft.setCursor(10, 65); 
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("Temp:");
  tft.setCursor(150, 60);
  tft.setTextColor(WHITE);  tft.setTextSize(4);
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
        String sepa = "/";
        int curweekday = weekday();
	int curday = day();
	int curmonth = month();
	int curyear = year();
	int curhour = hour();
	int curminute = minute();
        currenttime = printDigits(curday)+sepa+printDigits(curmonth)+sepa+curyear+" - "+printDigits(hour())+":"+printDigits(minute());
        //currenttime = curweekday+" "+printDigits(curday)+sepa+printDigits(curmonth)+sepa+curyear+" - "+printDigits(hour())+":"+printDigits(minute());
	return currenttime;
}

void PrintTime() {
  tft.setCursor(200, 13);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  //tft.println("Sun Mar 6 - 20.45"); // currenttime
  tft.println(GetTime());
  tft.drawFastHLine(0, 30, tft.width(), WHITE);
}

// segnale rete GSM
// ===========================================
int GetSignal() {
	float cellsignal;
	// ...
	return cellsignal;
}
void PrintSignal() {
	tft.fillRect(15,8,45,15,BLACK);
	tft.fillRect(15,19,3,3,WHITE);
	tft.fillRect(20,16,3,6,WHITE);
	tft.fillRect(25,13,3,9,WHITE);
	tft.fillRect(30,10,3,12,SILVER);
	//tft.drawRect(39,8,5,16,WHITE);
	tft.setCursor(40, 13);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("TIM");
}

// stato caldaia
// ===========================================
void PrintHeatStatus() {
	float measuredTemp = GetTemp();
	Serial.println(measuredTemp);
	tft.setCursor(90, 13);
	tft.fillRect(115,13,75,15,BLACK);
	tft.setTextColor(SILVER);  tft.setTextSize(1);
	switch (currentprog) {
		case 0 : // OFF : do nothing, it's probably summer!
			tft.println("Heating:OFF");
			break;
		case 1 : // MAN/T1 : do not drop below 8 C
			if ( measuredTemp <= 8.00 ) {
				tft.println("Heating:ON");
			} else {
				tft.println("Heating:OFF");
			}			break;
		case 2 : // MAN/T2 : do not drop below 17.5 C
			if ( measuredTemp <= 17.50 ) {
				tft.println("Heating:ON");
			} else {
				tft.println("Heating:OFF");
			}
			currentprog = 2;
			break;
		case 3 : // MAN/T3 : do not drop below 20.5 C
			if ( measuredTemp <= 20.50 ) {
				tft.println("Heating:ON");
			} else {
				tft.println("Heating:OFF");
			}
			break;
		default : // AUTO (9) : do not drop below 8 C except Fri evening and Sat late morning
			//	if (day == 5 && (time > 17:00 && time < 22:00)) || if (day == 6 && (time > 10:00 && time < 14:00)) { 
				if ( measuredTemp <= 17.50 ) {
					tft.println("Heating:ON");
				} else {
					tft.println("Heating:OFF");
				}
			//	} else {
			//		if ( measuredTemp <= 8.0 ) {
			//			tft.println("Heating:ON");
			//		} else {
			//			tft.println("Heating:OFF");
			//		}
			//	}
			break;
	}
}
//////////////////////////////////////////////





//////////////////////////////////////////////
// SET DATA
//////////////////////////////////////////////
int set_heat_prog(unsigned char set_prog) {
	currentprog = set_prog;
	return currentprog;
}








//////////////////////////////////////////////
// DRAW THE UI
//////////////////////////////////////////////

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
void mainUI(unsigned char prog) { // initial UI state
  MANmenuOpen = 0; // MANmenu is closed
  unsigned long start = micros();
  PrintSignal();
  PrintHeatStatus();
	PrintTime();

// ln 1: temp
  PrintTemp();

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
  Serial.print("new prog: "); Serial.print(prog); Serial.println(); // prog  
}

void MANmenu() {
  MANmenuOpen = 1; // MANmenu is open
  tft.fillRect(10, 95, 300, 70, YELLOW);
  tft.setTextColor(BLACK);
  tft.setCursor(45, 115);
  tft.setTextSize(2); tft.println("T1");
  tft.setCursor(42, 140);
  tft.setTextSize(1); tft.println("8.0 C");
  tft.drawFastVLine(105, 105, 50, BLACK);
  tft.setCursor(148, 115);
  tft.setTextSize(2); tft.println("T2");
  tft.setCursor(143, 140);
  tft.setTextSize(1); tft.println("17.5 C");
  tft.drawFastVLine(215, 105, 50, BLACK);
  tft.setCursor(250, 115);
  tft.setTextSize(2); tft.println("T3");
  tft.setCursor(245, 140);
  tft.setTextSize(1); tft.println("20.5 C");
}
// END DRAW THE UI
//////////////////////////////////////////////
