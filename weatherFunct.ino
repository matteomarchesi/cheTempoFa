void getWeatherAndPrint()
{
  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client.print(String("GET /data/2.5/weather?") +
                "q="+location+
                "&appid="+apiKey+
                "&cnt=3"+lang+
                "&units=Metric\r\n"+
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
    );

    Serial.println("[Response:]");
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
// Json
        
        DynamicJsonBuffer jsonBuf;
        JsonObject& root = jsonBuf.parseObject(line);
        if (!root.success())
        {
          Serial.println("parseObject() failed");
          return;
        }

        float coord_lon = root["coord"]["lon"]; // 9.41/        float coord_lat = root["coord"]["lat"]; // 45.65
        
        JsonObject& weather_0 = root["weather"][0];
        int weather_0_id = weather_0["id"]; // 800
        const char* weather_0_main = weather_0["main"]; // "Clear"
        const char* weather_0_description = weather_0["description"]; // "cielo sereno"
        const char* weather_0_icon = weather_0["icon"]; // "01n"
        
        const char* base = root["base"]; // "stations"
        
        JsonObject& main = root["main"];
        float main_temp = main["temp"]; // 1.22
        int main_pressure = main["pressure"]; // 1025
        int main_humidity = main["humidity"]; // 80
        int main_temp_min = main["temp_min"]; // 0
        int main_temp_max = main["temp_max"]; // 3
        
        int visibility = root["visibility"]; // 10000
        
        float wind_speed = root["wind"]["speed"]; // 2.1
        int wind_deg = root["wind"]["deg"]; // 360
        
        int clouds_all = root["clouds"]["all"]; // 0
        
        long dt = root["dt"]; // 1549398000
        
        JsonObject& sys = root["sys"];
        int sys_type = sys["type"]; // 1
        int sys_id = sys["id"]; // 6735
        float sys_message = sys["message"]; // 0.0035
        const char* sys_country = sys["country"]; // "IT"
        long sys_sunrise = sys["sunrise"]; // 1549348693
        long sys_sunset = sys["sunset"]; // 1549384511
        
        long id = root["id"]; // 6534286
        const char* name = root["name"]; // "Bernareggio"
        int cod = root["cod"]; // 200

        current.de = weather_0_description;
        current.ic = weather_0_icon;
        current.te = main_temp;
        current.mi = main_temp_min;
        current.mx = main_temp_max;
        current.hu = main_humidity;
        current.pr = main_pressure;
        current.ws = wind_speed;
        current.wd = wind_deg;
        current.vi = visibility;

        Serial.println("-----------------------");

        Serial.println(String("desc=")+weather_0_description);
        Serial.println(String("icon=")+weather_0_icon);

        Serial.println(String("temp=")+main_temp);
        Serial.println(String("pres=")+main_pressure);
        Serial.println(String("humi=")+main_humidity);

        Serial.println(String("visi=")+visibility);
        Serial.println(String("wind=")+wind_speed);
        Serial.println(String("deg =")+wind_deg);
        
        Serial.println(String("cloud=")+clouds_all);
        Serial.println(String("dt  =")+dt);

        Serial.println(String("count=")+sys_country);
        Serial.println(String("rise=")+sys_sunrise);
        Serial.println(String("name=")+name);
        Serial.println(String("cod =")+cod);


        Serial.println("-----------------------");
        /*
       // display.clearDisplay();
    for (int y=0; y<=23; y++)
        {
         for (int x=0; x<127; x++)
         {
          display.drawPixel(x, y, BLACK); 
         }
        } 

        
        display.display();      
        display.setCursor(0,0);
        display.print(weather_0_description);
        display.setCursor(0,8);
        display.printf("%5dhPa %3d%%RH", main_pressure, main_humidity);
        display.setCursor(0,16);
        display.printf("%5.1fkm/h  %5.1f*C", wind_speed, main_temp);

        display.display();      
        */
      }
    }
    client.stop();

    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
/*
    display.clearDisplay();
    display.print("connection failed!");
    display.display(); 
*/
    client.stop();
  }
  
}
