#cheTempoFa

Weather gadged based on ESP8266 ESP-01.

*Files*
cheTempoFa.ino
- dateTimeFunct.ino
- displayFunct.ino
- weatherFunct.ino
 
#Hardware:
- 1x ESP-01
- 1x SSD1306 0.96" dispaly 128x64 monchrome
- 4x 3.3K pullup resistors
- 2x 330R pass resistor
- 2x pushbuttons
  - reset (hidden in the case)
  - function
- program switch (jumper hidden in the case)
- HLK-PM01
- USB adapter for program/debugging (to be removed in the case)

*Schematic:*
![](scheme/cheTempoFa-0.1_schem.png) 
(Fritzing and pdf files in scheme/ folder)
#Software:
Get date and time from NTP server
Auto DST for Europe.
Get weather from openweathermap.org
- current
- 3x 3h forecast
- next 3 days forecast
- SPIFF (TBD) to manage config parameters (TBD)
  - ssid
  - password
  - apikey
  - location

**REQUIRED libraries**
```
#include <ESP8266WiFi.h>
#include <ArduinoJson.h> // version 6!!!
#include <Wire.h>;
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono9pt7b.h>
#include <time.h>    
```
In Adafruit_SSD1306 the display dimension setup seems not to work out of the box.
I'm using a 0.96" OLED display 128x64. To configure it correctly the Adafruit_SSD1306.h should be modified as follow:
```
// file location: libraries/Adafruit_SSD1306/Adafruit_SSD1306.h
	#define SSD1306_128_64
	//   #define SSD1306_128_32
```

**Known issues**
Sometims the data is not pulled from web
--> add a retry?