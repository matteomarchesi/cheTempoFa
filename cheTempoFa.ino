#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include <Wire.h>;
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define CET (1)

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

#include <time.h>                       // time() ctime()
#include <sys/time.h>                   // struct timeval
#include <coredecls.h>                  // settimeofday_cb()

#define TZ              0       // (utc+) TZ in hours
#define DST_MN          0      // use 60mn for summer time in some countries

#define RTC_TEST     1510592825 // 1510592825 = Monday 13 November 2017 17:07:05 UTC

#define TZ_MN           ((TZ)*60)
#define TZ_SEC          ((TZ)*3600)
#define DST_SEC         ((DST_MN)*60)

timeval cbtime;      // time set in callback
bool cbtime_set = false;

void time_is_set(void) {
  gettimeofday(&cbtime, NULL);
  cbtime_set = true;
  Serial.println("------------------ settimeofday() was called ------------------");
}

timeval tv;
timespec tp;
time_t now;

bool updateDateTime = true;
bool updateWeather = true;
int minu, seco;

void setup()
{
// set Serial connection for debug
  Serial.begin(115200);
  Serial.println();

// clock initialization
  settimeofday_cb(time_is_set);
  configTime(TZ_SEC, DST_SEC, "pool.ntp.org");

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
//    display.setCursor(0,8);
    display.print(".");
    display.display();
  }
  Serial.println(" connected");
  display.println("\nconnected");
  display.display();
}





void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    updateDateTime = true;
  }
  
  if (currentMillis - previousMillis >= interval*60) {
    previousMillis = currentMillis;
    updateWeather = true;
  }

  if (updateDateTime) {
    getDateTime();
    updateDateTime = false;
  }

  if (updateWeather) {
    getWeatherAndPrint();
    updateWeather = false;
  }
}
