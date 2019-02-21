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
  - function (TBD)
- program switch (hidded)
- USB adapter for program/debuggin

#Software:
Get date and time from NTP server
Get timezone and DST from (TBD)
  - http://worldclockapi.com/api/json/cet/now
Get weather from openweathermap.org
- current
- 3h forecast (TBD)
- next day(s) forecast (TBD)
- OTA (TBD)
- SPIFF (TBD) to manage config parameters (TBD)
  - ssid
  - password
  - apikey
  - location
