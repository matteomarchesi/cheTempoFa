void getWeatherAndPrint()
{
  WiFiClient client;

//  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
//    Serial.println("connected]");
//    Serial.println("[Sending a request]");
    client.print(String("GET /data/2.5/weather?") +
                "q="+location+
                "&appid="+apiKey+
                "&cnt=3"+lang+
                "&units=Metric\r\n"+
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
    );

//    Serial.println("[Response:]");
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
//        Serial.println(line);
// Json
        
        DynamicJsonBuffer jsonBuf;
        JsonObject& root = jsonBuf.parseObject(line);
        if (!root.success())
        {
//          Serial.println("parseObject() failed");
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
        current.ti = "";
/*
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
        */
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

//    Serial.println("\n[Disconnected]");
  }
  else
  {
//    Serial.println("connection failed!]");
/*
    display.clearDisplay();
    display.print("connection failed!");
    display.display(); 
*/
    client.stop();
  }
  
}


void getWeatherHourly()
{
  WiFiClient client;

  if (client.connect(host, 80))
  {
    client.print(String("GET /data/2.5/forecast?") +
                "q="+location+
                "&appid="+apiKey+
                "&cnt=4"+lang+
                "&units=Metric&cnt=4\r\n"+
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
    );

    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
// Json
        
        DynamicJsonBuffer jsonBuf;
        JsonObject& root = jsonBuf.parseObject(line);
        if (!root.success())
        {
          return;
        }

// *************************** + 3H
        JsonObject& list_0 = list[0];
        long list_0_dt = list_0["dt"]; // 1551106800
        
        JsonObject& list_0_main = list_0["main"];
        float list_0_main_temp = list_0_main["temp"]; // 13.63
        float list_0_main_temp_min = list_0_main["temp_min"]; // 11.94
        float list_0_main_temp_max = list_0_main["temp_max"]; // 13.63
        float list_0_main_pressure = list_0_main["pressure"]; // 1033.77
        float list_0_main_sea_level = list_0_main["sea_level"]; // 1033.77
        float list_0_main_grnd_level = list_0_main["grnd_level"]; // 1000.2
        int list_0_main_humidity = list_0_main["humidity"]; // 76
        float list_0_main_temp_kf = list_0_main["temp_kf"]; // 1.69
        
        JsonObject& list_0_weather_0 = list_0["weather"][0];
        int list_0_weather_0_id = list_0_weather_0["id"]; // 800
        const char* list_0_weather_0_main = list_0_weather_0["main"]; // "Clear"
        const char* list_0_weather_0_description = list_0_weather_0["description"]; // "cielo sereno"
        const char* list_0_weather_0_icon = list_0_weather_0["icon"]; // "01d"
        
        int list_0_clouds_all = list_0["clouds"]["all"]; // 0
        
        float list_0_wind_speed = list_0["wind"]["speed"]; // 1.82
        float list_0_wind_deg = list_0["wind"]["deg"]; // 263.504
        
        const char* list_0_sys_pod = list_0["sys"]["pod"]; // "d"
        
        const char* list_0_dt_txt = list_0["dt_txt"]; // "2019-02-25 15:00:00"
// *************************** +6h
        JsonObject& list_1 = list[1];
        long list_1_dt = list_1["dt"]; // 1551117600
        
        JsonObject& list_1_main = list_1["main"];
        float list_1_main_temp = list_1_main["temp"]; // 7.5
        float list_1_main_temp_min = list_1_main["temp_min"]; // 6.23
        float list_1_main_temp_max = list_1_main["temp_max"]; // 7.5
        float list_1_main_pressure = list_1_main["pressure"]; // 1033.92
        float list_1_main_sea_level = list_1_main["sea_level"]; // 1033.92
        float list_1_main_grnd_level = list_1_main["grnd_level"]; // 999.97
        int list_1_main_humidity = list_1_main["humidity"]; // 84
        float list_1_main_temp_kf = list_1_main["temp_kf"]; // 1.27
        
        JsonObject& list_1_weather_0 = list_1["weather"][0];
        int list_1_weather_0_id = list_1_weather_0["id"]; // 800
        const char* list_1_weather_0_main = list_1_weather_0["main"]; // "Clear"
        const char* list_1_weather_0_description = list_1_weather_0["description"]; // "cielo sereno"
        const char* list_1_weather_0_icon = list_1_weather_0["icon"]; // "01n"
        
        int list_1_clouds_all = list_1["clouds"]["all"]; // 0
        
        float list_1_wind_speed = list_1["wind"]["speed"]; // 1.61
        float list_1_wind_deg = list_1["wind"]["deg"]; // 272.001
        
        const char* list_1_sys_pod = list_1["sys"]["pod"]; // "n"
        
        const char* list_1_dt_txt = list_1["dt_txt"]; // "2019-02-25 18:00:00"
// *************************** +12h
        JsonObject& list_3 = list[1];
        long list_3_dt = list_3["dt"]; // 1551117600
        
        JsonObject& list_3_main = list_3["main"];
        float list_3_main_temp = list_3_main["temp"]; // 7.5
        float list_3_main_temp_min = list_3_main["temp_min"]; // 6.23
        float list_3_main_temp_max = list_3_main["temp_max"]; // 7.5
        float list_3_main_pressure = list_3_main["pressure"]; // 1033.92
        float list_3_main_sea_level = list_3_main["sea_level"]; // 1033.92
        float list_3_main_grnd_level = list_3_main["grnd_level"]; // 999.97
        int list_3_main_humidity = list_3_main["humidity"]; // 84
        float list_3_main_temp_kf = list_3_main["temp_kf"]; // 1.27
        
        JsonObject& list_3_weather_0 = list_3["weather"][0];
        int list_3_weather_0_id = list_3_weather_0["id"]; // 800
        const char* list_3_weather_0_main = list_3_weather_0["main"]; // "Clear"
        const char* list_3_weather_0_description = list_3_weather_0["description"]; // "cielo sereno"
        const char* list_3_weather_0_icon = list_3_weather_0["icon"]; // "01n"
        
        int list_3_clouds_all = list_3["clouds"]["all"]; // 0
        
        float list_3_wind_speed = list_3["wind"]["speed"]; // 1.61
        float list_3_wind_deg = list_3["wind"]["deg"]; // 272.001
        
        const char* list_3_sys_pod = list_3["sys"]["pod"]; // "n"
        
        const char* list_3_dt_txt = list_3["dt_txt"]; // "2019-02-25 18:00:00"


// ***************************
      
        next3.de = list_0_weather_0_description;
        next3.ic = list_0_weather_0_icon;
        next3.te = list_0_main_temp;
        next3.mi = list_0_main_temp_min;
        next3.mx = list_0_main_temp_max;
        next3.hu = list_0_main_humidity;
        next3.pr = list_0_main_pressure;
        next3.ws = list_0_wind_speed;
        next3.wd = list_0_wind_deg;
        next3.ti = list_0_dt_txt.substring(12);
        
        next6.de = list_1_weather_0_description;
        next6.ic = list_1_weather_0_icon;
        next6.te = list_1_main_temp;
        next6.mi = list_1_main_temp_min;
        next6.mx = list_1_main_temp_max;
        next6.hu = list_1_main_humidity;
        next6.pr = list_1_main_pressure;
        next6.ws = list_1_wind_speed;
        next6.wd = list_1_wind_deg;
        next6.ti = list_1_dt_txt.substring(12);

        next12.de = list_4_weather_0_description;
        next12.ic = list_4_weather_0_icon;
        next12.te = list_4_main_temp;
        next12.mi = list_4_main_temp_min;
        next12.mx = list_4_main_temp_max;
        next12.hu = list_4_main_humidity;
        next12.pr = list_4_main_pressure;
        next12.ws = list_4_wind_speed;
        next12.wd = list_4_wind_deg;
        next12.ti = list_4_dt_txt.substring(12);
      }
    }
    client.stop();
  }
  else
  {
    client.stop();
  }
  
}

void getWeatherDaily()
{
  WiFiClient client;

  if (client.connect(host, 80))
  {
    client.print(String("GET /data/2.5/forecast/daily?") +
                "q="+location+
                "&appid="+apiKey+
                "&cnt=4"+lang+
                "&units=Metric&cnt=3\r\n"+
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
    );

    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
// Json
        
        DynamicJsonBuffer jsonBuf;
        JsonObject& root = jsonBuf.parseObject(line);
        if (!root.success())
        {
          return;
        }

// *************************** + 1d
        JsonObject& list_0 = list[0];
        long list_0_dt = list_0["dt"]; // 1551092400
        
        JsonObject& list_0_temp = list_0["temp"];
        int list_0_temp_day = list_0_temp["day"]; // 14
        float list_0_temp_min = list_0_temp["min"]; // 1.68
        float list_0_temp_max = list_0_temp["max"]; // 14.31
        float list_0_temp_night = list_0_temp["night"]; // 1.68
        int list_0_temp_eve = list_0_temp["eve"]; // 8
        int list_0_temp_morn = list_0_temp["morn"]; // 14
        
        float list_0_pressure = list_0["pressure"]; // 1034.71
        int list_0_humidity = list_0["humidity"]; // 83
        
        JsonObject& list_0_weather_0 = list_0["weather"][0];
        int list_0_weather_0_id = list_0_weather_0["id"]; // 800
        const char* list_0_weather_0_main = list_0_weather_0["main"]; // "Clear"
        const char* list_0_weather_0_description = list_0_weather_0["description"]; // "cielo sereno"
        const char* list_0_weather_0_icon = list_0_weather_0["icon"]; // "01d"
        
        float list_0_speed = list_0["speed"]; // 1.86
        int list_0_deg = list_0["deg"]; // 235
        int list_0_clouds = list_0["clouds"]; // 0

// *************************** +2d
        JsonObject& list_1 = list[1];
        long list_1_dt = list_1["dt"]; // 1551092400
        
        JsonObject& list_1_temp = list_1["temp"];
        int list_1_temp_day = list_1_temp["day"]; // 14
        float list_1_temp_min = list_1_temp["min"]; // 1.68
        float list_1_temp_max = list_1_temp["max"]; // 14.31
        float list_1_temp_night = list_1_temp["night"]; // 1.68
        int list_1_temp_eve = list_1_temp["eve"]; // 8
        int list_1_temp_morn = list_1_temp["morn"]; // 14
        
        float list_1_pressure = list_1["pressure"]; // 1034.71
        int list_1_humidity = list_1["humidity"]; // 83
        
        JsonObject& list_1_weather_0 = list_1["weather"][0];
        int list_1_weather_0_id = list_1_weather_0["id"]; // 800
        const char* list_1_weather_0_main = list_1_weather_0["main"]; // "Clear"
        const char* list_1_weather_0_description = list_1_weather_0["description"]; // "cielo sereno"
        const char* list_1_weather_0_icon = list_1_weather_0["icon"]; // "01d"
        
        float list_1_speed = list_1["speed"]; // 1.86
        int list_1_deg = list_1["deg"]; // 235
        int list_1_clouds = list_1["clouds"]; // 0

// *************************** +3d
        JsonObject& list_2 = list[2];
        long list_2_dt = list_2["dt"]; // 1551092400
        
        JsonObject& list_2_temp = list_2["temp"];
        int list_2_temp_day = list_2_temp["day"]; // 14
        float list_2_temp_min = list_2_temp["min"]; // 1.68
        float list_2_temp_max = list_2_temp["max"]; // 14.31
        float list_2_temp_night = list_2_temp["night"]; // 1.68
        int list_2_temp_eve = list_2_temp["eve"]; // 8
        int list_2_temp_morn = list_2_temp["morn"]; // 14
        
        float list_2_pressure = list_2["pressure"]; // 1034.71
        int list_2_humidity = list_2["humidity"]; // 83
        
        JsonObject& list_2_weather_0 = list_2["weather"][0];
        int list_2_weather_0_id = list_2_weather_0["id"]; // 800
        const char* list_2_weather_0_main = list_2_weather_0["main"]; // "Clear"
        const char* list_2_weather_0_description = list_2_weather_0["description"]; // "cielo sereno"
        const char* list_2_weather_0_icon = list_2_weather_0["icon"]; // "01d"
        
        float list_2_speed = list_2["speed"]; // 1.86
        int list_2_deg = list_2["deg"]; // 235
        int list_2_clouds = list_2["clouds"]; // 0
// ***************************
      
        dp1.de = list_0_weather_0_description;
        dp1.ic = list_0_weather_0_icon;
        dp1.te = list_0_temp_day;
        dp1.mi = list_0_temp_min;
        dp1.mx = list_0_temp_max;
        dp1.hu = list_0_humidity;
        dp1.pr = list_0_pressure;
        dp1.ws = list_0_speed;
        dp1.wd = list_0_deg;
        dp1.ti = list_0_dt_txt.substring(12); 
        dp1.ti = day(list_0_dt) + "-" + month(list_0_dt) + "-" + year(list_0_dt);
        
        dp2.de = list_1_weather_0_description;
        dp2.ic = list_1_weather_0_icon;
        dp2.te = list_1_temp_day;
        dp2.mi = list_1_temp_min;
        dp2.mx = list_1_temp_max;
        dp2.hu = list_1_humidity;
        dp2.pr = list_1_pressure;
        dp2.ws = list_1_speed;
        dp2.wd = list_1_deg;
        dp2.ti = day(list_1_dt) + "-" + month(list_1_dt) + "-" + year(list_1_dt);

        dp3.de = list_2_weather_0_description;
        dp3.ic = list_2_weather_0_icon;
        dp3.te = list_2_temp_day;
        dp3.mi = list_2_temp_min;
        dp3.mx = list_2_temp_max;
        dp3.hu = list_2_humidity;
        dp3.pr = list_2_pressure;
        dp3.ws = list_2_speed;
        dp3.wd = list_2_deg;
        dp3.ti = day(list_2_dt) + "-" + month(list_2_dt) + "-" + year(list_2_dt);
      }
    }
    client.stop();
  }
  else
  {
    client.stop();
  }
  
}
