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

unsigned long previousMillis = 0;
const long interval = 60000;

unsigned long previousMillis1 = 0;
const long interval1 = 10000;

#include <time.h>                       

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 0;

char buffer[80];

time_t rawtime;
struct tm * timeinfo;

int ora, sec;
int ora_pre = -1;
int sec_pre = -1;

void setup()
{
// set Serial connection for debug
  Serial.begin(115200);
  Serial.println();

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

/*  
  Serial.println(sec);
  Serial.println(sec_pre);
  Serial.println(ora);
  Serial.println(ora_pre);
*/
  if (sec!=sec_pre){
    printTime();
    sec_pre = sec;
  }
  if (ora!=ora_pre){
    getWeatherAndPrint();
    ora_pre = ora;
  }
}
