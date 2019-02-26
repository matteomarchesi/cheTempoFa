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
 *   
 *   
 *  char size 6x8
 *  rows start at 0, 8, 16, 24  
 *  +---------------------+
 *  |cielo sereno         |
 *  | 1034hPa 100%RH      |
 *  |  4.1km/h    8.0dC   |
 *  |Sat 27-02-19 16:05:38|
 *  +---------------------+
 *   012345678901234567890
 */

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include <Wire.h>;
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const char* host      = "api.openweathermap.org";

const char* ssid      = "Vodafone-50556336";
const char* password  = "ub5se8djzl2xvea";
String apiKey         = "2f31dba5954c10dc63d1047e2c28acf3";
String lang = "&lang=it";  
String location= "bernareggio,IT";

String weatherString;

// oled setup
#define OLED_address  0x78
#define OLED_RESET -1

Adafruit_SSD1306 display(OLED_RESET);

#include <time.h>                       

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 0;

char buffer[80];

time_t rawtime;
struct tm * timeinfo;

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
  String ti; // time
} weather_data;

weather_data current;
weather_data next3;
weather_data next6;
weather_data next12;
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
bool checkDST();

unsigned long previousMillis = 0;
unsigned long interval = 5000;

int displayWhat = 0;

void setup()
{
// set Serial connection for debug
  Serial.begin(115200,SERIAL_8N1,SERIAL_TX_ONLY);
  Serial.println();

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

  Serial.printf("Connect %s ", ssid);

  display.setCursor(0,0);
  display.printf("%s\n",ssid);
  display.display();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    display.print(".");
    display.display();
  }
  Serial.println(" connected");
  display.println("\nconnected");
  display.display();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  Serial.println("\nWaiting for time");
  unsigned timeout = 5000;
  unsigned start = millis();
  while (!time(nullptr)) 
  {
    Serial.print(".");
    delay(1000);
  }
  delay(1000);
  
  Serial.println("Time...");
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
  if (reading==0){
      previousMillis = currentMillis;
      displayWhat++;
      if (displayWhat>6){
          displayWhat=0;
        }
    }
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
      case 3: // +12h
        printWeather(next12);
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
    getWeather();
    getWeatherHourly();
    getWeatherDaily();
    ora_pre = ora;
  }
}
