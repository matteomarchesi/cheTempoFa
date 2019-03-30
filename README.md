# cheTempoFa

Weather gadged based on ESP8266 ESP-01.

cheTempoFa.ino
- dateTimeFunct.ino
- displayFunct.ino
- weatherFunct.ino
 
#Hardware:
- ESP-01
- SSD1306 0.96" dispaly 128x32  --> to be upgraded
- 3.3K pullup resistors
- 330R pass resistor
- pushbuttons
  - reset (hidden)
  - function
- program switch (hidded)
- USB adapter for program/debuggin

#Software:
Get date and time from NTP server
Get DST from
  - http://worldclockapi.com/api/json/cet/now
Get weather from openweathermap.org
- current
- 3h forecast
- next day(s) forecast
- OTA (TBD)
- SPIFF (TBD) to manage config parameters (TBD)
  - ssid
  - password
  - apikey
  - location

REQUIRES ArduinoJSON 6

in Adafruit_SSD1306.h set the 128x64 configuration!!!
#define SSD1306_128_64
//   #define SSD1306_128_32

