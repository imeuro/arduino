//////////////////////////////////////////////////////
// My personal project for a GSM thermostat 
// using an Arduino Uno Rev3 and a Raspberry Pi 2
//
// still far from the final objective
// done:
// - temperature sensor (calibrated?)
// - LCD screen displaying current temperature
// - green led when over 19 C, red if below
//
// todo:
// - send an email when temperature drops below 19
// - buy GSM module
// - make the GSM module work
// - test test test and more tests possibly
// - build a case and nicely assemble everything
//
//////////////////////////////////////////////////////


// include the library code:
#include <LiquidCrystal.h>

#define analogPin  A0 //the thermistor attach to
#define beta 4090 //the beta of the thermistor
#define resistance 10 //the value of the pull-down resistor

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// red and green Led pins
const int RedLedPin = 7;
const int GreenLedPin = 8;

void setup() {
  // Log: open the serial port at 9600 bps
  Serial.begin(9600);    

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Temp:");
  lcd.setCursor(0, 1);
  lcd.print("Set:");
  pinMode(RedLedPin,OUTPUT);
  pinMode(GreenLedPin,OUTPUT);

}

void loop() {
  //read thermistor value
  long a = analogRead(analogPin);
  //the calculating formula of temperature
  float tempC = beta /(log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
  //tempC = tempC -2; // calibration :)

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(8, 0);
  lcd.print(tempC);
  //lcd.setCursor(14, 0);
  //lcd.print("C");
  lcd.setCursor(8, 1);
  lcd.print("T2");

  if(tempC < 19.00) {
    digitalWrite(RedLedPin,HIGH);//turn on the red led
    digitalWrite(GreenLedPin,LOW);//turn off the green led
  } 
  else {
    digitalWrite(RedLedPin,LOW);//turn on the red led
    digitalWrite(GreenLedPin,HIGH);//turn off the green led
  }

  Serial.println(tempC);

  delay(30000); //wait for 30 sec then recheck
}


