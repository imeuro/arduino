##### Arduino Projects

#temperINO
TemperINO is my first attempt to build an Arduino powered GSM Thermostat
it's actually a work in progress and involves:

##hardware
- Arduino Uno Rev 3
- Arduno GSM Shield v2
- 2.8'' Pixnor UNO TFT touchscreen Shield (cheap)
  2.8'' Adafruit Capacitive TFT Shield (expensive, uses less pins than the pixnor!)
- DS3231 real time clock module + temperature 
- module w/ 2x relay switches

##software
libraries:
- Adafruit_GFX
- Adafruit_TFTLCD
- Touch Screen (Pixnor)
- Adafruit_ILI9341  (Adafruit)
- Adafruit_STMPE610  (Adafruit)
- DS3231
- SerialGSM
- Wire
- elapsedMillis
