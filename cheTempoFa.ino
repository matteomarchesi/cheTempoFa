/*
 * cheTempoFa.ino
 * - dateTimeFunct.ino
 * - displayFunct.ino
 * - weatherFunct.ino
 * 
 * weather gadget.
 * HW:
 * - ESP-01
 * - SSD1306 0.96" dispaly 128x32  --> to be upgraded
 * - 3.3K pullup resistors
 * - 330R pass resistor
 * - pushbuttons
 *   - reset (hidden)
 *   - function 
 * - program switch (hidded)
 * - USB adapter for program/debuggin
 * 
 * SW:
 * Get date and time from NTP server
 * Get timezone and DST from (TBD)
 *   - http://worldclockapi.com/api/json/cet/now
 * Get weather from openweathermap.org
 * - current
 * - 3h forecast 
 * - next day(s) forecast 
 * - OTA (TBD)
 * - SPIFF (TBD) to manage config parameters (TBD)
 *   - ssid
 *   - password
 *   - apikey
 *   - location
 */

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include <Wire.h>;
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono9pt7b.h>
/*
 * in Adafruit_SSD1306.h set the 128x64 configuration!!!
 * #define SSD1306_128_64
 * //   #define SSD1306_128_32
 */

const char* host      = "api.openweathermap.org";

const char* ssid      = "Vodafone-50556336";
const char* password  = "ub5se8djzl2xvea";
String apiKey         = "2f31dba5954c10dc63d1047e2c28acf3";
String lang = "&lang=it";  
String location= "bernareggio,IT";

String weatherString;

// oled setup
#define OLED_address  0x78

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_RESET);

#include <time.h>                       

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 0;

char buffer[80];

time_t rawtime;
struct tm * timeinfo;

typedef struct{
	long dst = 0;
	long tz = 3600;
} dsttz;

dsttz dst_tz;

typedef struct {
  String de; // description
  String ic; // icon
  float  te; // temperature
  int    mi; // minimum temp.
  int    mx; // maximum temp.
  int    hu; // humidity
  int    pr; // pressure
  float  ws; // wind speed
  int    wd; // wind direction
  int    vi; // visibility 
  int	   cl; // clouds
  String ti; // time
  long   ep; // epoch day time
} weather_data;

weather_data current;
weather_data next3;
weather_data next6;
weather_data next9;
weather_data dp1;
weather_data dp2;
weather_data dp3;

int ora, sec;
int ora_pre = -1;
int sec_pre = -1;

void getWeather();
void getWeatherHourly();
void clearLine(int lineN);
void clearChar(int lineN, int colN);
void printTime();
void checkDST();

unsigned long previousMillis = 0;
unsigned long interval = 5000;

int displayWhat = 0;

// debounce
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup()
{
// set Serial connection for debug
  Serial.begin(115200,SERIAL_8N1,SERIAL_TX_ONLY);

  pinMode(3,INPUT_PULLUP);

//I2C initialization for oled display
  Wire.pins(0, 2);
  Wire.begin(0,2);// 0=sda, 2=scl

//display
  display.begin(0x78);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();

  display.setCursor(10,0);
  display.print("cheTempoFa");
  display.setCursor(0,8);
  display.print("Matteo Marchesi 2019");
  display.setCursor(0,16);
  display.print("github.com/matteomarchesi/cheTempoFa");
  display.setCursor(0,32);
  display.setCursor(0,40);
  display.printf("%s\n",ssid);
  display.display();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    display.print(".");
    display.display();
  }
  display.println("\nconnected");
  display.display();
  checkDST();

//  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  configTime(dst_tz.tz, dst_tz.dst, ntpServer);

  unsigned timeout = 5000;
  unsigned start = millis();
  while (!time(nullptr)) 
  {
    delay(1000);
  }
  delay(1000);

  display.clearDisplay();
  display.display();
  
  printTime();
}


void loop()
{
  sec = timeinfo->tm_sec;
  ora = timeinfo->tm_hour;
  
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  
  unsigned long currentMillis = millis();
  
// ready keypressed
  int reading = digitalRead(3);

// Debounce start  
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        previousMillis = currentMillis;
        displayWhat++;
        if (displayWhat>6){
            displayWhat=0;
        }


      }
    }
  }

  lastButtonState = reading;
  
// Debounce end
  

// 5" after last keypressed reset display
  if (currentMillis-previousMillis > interval){
    displayWhat=0;
  }
     
  if (sec!=sec_pre){
    switch (displayWhat)
    {
      case 0: // now
        printWeatherC(current);
        printTime();
        break;
      case 1: // +3h
        printWeather(next3);
        break;
      case 2: // +6h
        printWeather(next6);
        break;
      case 3: // +9h
        printWeather(next9);
        break;
      case 4: // +1d
        printWeather(dp1);
        break;
      case 5: // +2d
        printWeather(dp2);
        break;
      case 6: // +3d
        printWeather(dp3);
        break;
    }
    sec_pre = sec;
  }
  if (ora!=ora_pre){
  	if (ora==4){
      checkDST();
  		configTime(dst_tz.tz, dst_tz.dst, ntpServer);
  	}
    getWeather();
    getWeatherHourly();
    getWeatherDaily();
    ora_pre = ora;
  }
}
