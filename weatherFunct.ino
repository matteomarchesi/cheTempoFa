void getWeather()
{
  WiFiClient client;

  if (client.connect(host, 80))
  {
    client.print(String("GET /data/2.5/weather?") +
                "q="+location+
                "&appid="+apiKey+
                "&cnt=3"+lang+
                "&units=Metric\r\n"+
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
        const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 270;
        DynamicJsonDocument doc(capacity);

        deserializeJson(doc, line);

//        float coord_lon = doc["coord"]["lon"]; // 9.41
//        float coord_lat = doc["coord"]["lat"]; // 45.65
        
        JsonObject weather_0 = doc["weather"][0];
//        int weather_0_id = weather_0["id"]; // 800
//        const char* weather_0_main = weather_0["main"]; // "Clear"
        const char* weather_0_description = weather_0["description"]; // "cielo sereno"
        const char* weather_0_icon = weather_0["icon"]; // "01n"
        
//        const char* base = doc["base"]; // "stations"
        
        JsonObject main = doc["main"];
        float main_temp = main["temp"]; // 10.15
        int main_pressure = main["pressure"]; // 1025
        int main_humidity = main["humidity"]; // 53
        float main_temp_min = main["temp_min"]; // 7.78
        float main_temp_max = main["temp_max"]; // 12.78
        
        int visibility = doc["visibility"]; // 10000
        
        float wind_speed = doc["wind"]["speed"]; // 1.5
        int wind_deg = doc["wind"]["deg"]; // 10
        
        int clouds_all = doc["clouds"]["all"]; // 0
        
        long dt = doc["dt"]; // 1551216616
        
//        JsonObject sys = doc["sys"];
//        int sys_type = sys["type"]; // 1
//        int sys_id = sys["id"]; // 6735
//        float sys_message = sys["message"]; // 0.0074
//        const char* sys_country = sys["country"]; // "IT"
//        long sys_sunrise = sys["sunrise"]; // 1551161123
//        long sys_sunset = sys["sunset"]; // 1551200736
        
//        long id = doc["id"]; // 6534286
//        const char* name = doc["name"]; // "Bernareggio"
//        int cod = doc["cod"]; // 200


        
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
		current.cl = clouds_all;
        current.ep = dt;
        current.ti = "";
        Serial.print("current ");
        Serial.println(current.ep);
      }
    }
    client.stop();

  }
  else
  {
    client.stop();
  }
  
}

// api.openweathermap.org/data/2.5/forecast?q=Bernareggio,It&appid=2f31dba5954c10dc63d1047e2c28acf3&cnt=4&lang=it&units=Metric&cnt=4


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
        const size_t capacity = 4*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(4) + 8*JSON_OBJECT_SIZE(1) + 5*JSON_OBJECT_SIZE(2) + 4*JSON_OBJECT_SIZE(4) + 2*JSON_OBJECT_SIZE(5) + 4*JSON_OBJECT_SIZE(7) + 4*JSON_OBJECT_SIZE(8) + 980;
        DynamicJsonDocument doc(capacity);
        
//        const char* json = "{\"cod\":\"200\",\"message\":0.0054,\"cnt\":4,\"list\":[{\"dt\":1551225600,\"main\":{\"temp\":7.28,\"temp_min\":2.63,\"temp_max\":7.28,\"pressure\":1027.34,\"sea_level\":1027.34,\"grnd_level\":993.64,\"humidity\":77,\"temp_kf\":4.64},\"weather\":[{\"id\":800,\"main\":\"Clear\",\"description\":\"cielo sereno\",\"icon\":\"01n\"}],\"clouds\":{\"all\":0},\"wind\":{\"speed\":0.6,\"deg\":77.0071},\"sys\":{\"pod\":\"n\"},\"dt_txt\":\"2019-02-27 00:00:00\"},{\"dt\":1551236400,\"main\":{\"temp\":5.51,\"temp_min\":2.02,\"temp_max\":5.51,\"pressure\":1027.08,\"sea_level\":1027.08,\"grnd_level\":993.13,\"humidity\":74,\"temp_kf\":3.48},\"weather\":[{\"id\":800,\"main\":\"Clear\",\"description\":\"cielo sereno\",\"icon\":\"01n\"}],\"clouds\":{\"all\":0},\"wind\":{\"speed\":1.91,\"deg\":36.5007},\"sys\":{\"pod\":\"n\"},\"dt_txt\":\"2019-02-27 03:00:00\"},{\"dt\":1551247200,\"main\":{\"temp\":4.42,\"temp_min\":2.1,\"temp_max\":4.42,\"pressure\":1027.59,\"sea_level\":1027.59,\"grnd_level\":993.61,\"humidity\":72,\"temp_kf\":2.32},\"weather\":[{\"id\":800,\"main\":\"Clear\",\"description\":\"cielo sereno\",\"icon\":\"01n\"}],\"clouds\":{\"all\":0},\"wind\":{\"speed\":2.7,\"deg\":50.0024},\"sys\":{\"pod\":\"n\"},\"dt_txt\":\"2019-02-27 06:00:00\"},{\"dt\":1551258000,\"main\":{\"temp\":10.82,\"temp_min\":9.66,\"temp_max\":10.82,\"pressure\":1028.08,\"sea_level\":1028.08,\"grnd_level\":994.44,\"humidity\":78,\"temp_kf\":1.16},\"weather\":[{\"id\":800,\"main\":\"Clear\",\"description\":\"cielo sereno\",\"icon\":\"01d\"}],\"clouds\":{\"all\":0},\"wind\":{\"speed\":2.01,\"deg\":87.0018},\"sys\":{\"pod\":\"d\"},\"dt_txt\":\"2019-02-27 09:00:00\"}],\"city\":{\"id\":6534286,\"name\":\"Bernareggio\",\"coord\":{\"lat\":45.6485,\"lon\":9.4064},\"country\":\"IT\",\"population\":8298}}";
        
        deserializeJson(doc, line);
        
//        const char* cod = doc["cod"]; // "200"
//        float message = doc["message"]; // 0.0054
//        int cnt = doc["cnt"]; // 4
        
        JsonArray list = doc["list"];
        
        JsonObject list_0 = list[0];
        long list_0_dt = list_0["dt"]; // 1551225600
        
        JsonObject list_0_main = list_0["main"];
        float list_0_main_temp = list_0_main["temp"]; // 7.28
        float list_0_main_temp_min = list_0_main["temp_min"]; // 2.63
        float list_0_main_temp_max = list_0_main["temp_max"]; // 7.28
        float list_0_main_pressure = list_0_main["pressure"]; // 1027.34
//        float list_0_main_sea_level = list_0_main["sea_level"]; // 1027.34
//        float list_0_main_grnd_level = list_0_main["grnd_level"]; // 993.64
        int list_0_main_humidity = list_0_main["humidity"]; // 77
//        float list_0_main_temp_kf = list_0_main["temp_kf"]; // 4.64
        
        JsonObject list_0_weather_0 = list_0["weather"][0];
//        int list_0_weather_0_id = list_0_weather_0["id"]; // 800
//        const char* list_0_weather_0_main = list_0_weather_0["main"]; // "Clear"
        const char* list_0_weather_0_description = list_0_weather_0["description"]; // "cielo sereno"
        const char* list_0_weather_0_icon = list_0_weather_0["icon"]; // "01n"
        
        int list_0_clouds_all = list_0["clouds"]["all"]; // 0
        
        float list_0_wind_speed = list_0["wind"]["speed"]; // 0.6
        float list_0_wind_deg = list_0["wind"]["deg"]; // 77.0071
        
        const char* list_0_sys_pod = list_0["sys"]["pod"]; // "n"
        
        const char* list_0_dt_txt = list_0["dt_txt"]; // "2019-02-27 00:00:00"
        
        JsonObject list_1 = list[1];
        long list_1_dt = list_1["dt"]; // 1551236400
        
        JsonObject list_1_main = list_1["main"];
        float list_1_main_temp = list_1_main["temp"]; // 5.51
        float list_1_main_temp_min = list_1_main["temp_min"]; // 2.02
        float list_1_main_temp_max = list_1_main["temp_max"]; // 5.51
        float list_1_main_pressure = list_1_main["pressure"]; // 1027.08
//        float list_1_main_sea_level = list_1_main["sea_level"]; // 1027.08
//        float list_1_main_grnd_level = list_1_main["grnd_level"]; // 993.13
        int list_1_main_humidity = list_1_main["humidity"]; // 74
        float list_1_main_temp_kf = list_1_main["temp_kf"]; // 3.48
        
        JsonObject list_1_weather_0 = list_1["weather"][0];
//        int list_1_weather_0_id = list_1_weather_0["id"]; // 800
//        const char* list_1_weather_0_main = list_1_weather_0["main"]; // "Clear"
        const char* list_1_weather_0_description = list_1_weather_0["description"]; // "cielo sereno"
        const char* list_1_weather_0_icon = list_1_weather_0["icon"]; // "01n"
        
        int list_1_clouds_all = list_1["clouds"]["all"]; // 0
        
        float list_1_wind_speed = list_1["wind"]["speed"]; // 1.91
        float list_1_wind_deg = list_1["wind"]["deg"]; // 36.5007
        
        const char* list_1_sys_pod = list_1["sys"]["pod"]; // "n"
        
        const char* list_1_dt_txt = list_1["dt_txt"]; // "2019-02-27 03:00:00"
        
        JsonObject list_2 = list[2];
        long list_2_dt = list_2["dt"]; // 1551247200
        
        JsonObject list_2_main = list_2["main"];
        float list_2_main_temp = list_2_main["temp"]; // 4.42
        float list_2_main_temp_min = list_2_main["temp_min"]; // 2.1
        float list_2_main_temp_max = list_2_main["temp_max"]; // 4.42
        float list_2_main_pressure = list_2_main["pressure"]; // 1027.59
//        float list_2_main_sea_level = list_2_main["sea_level"]; // 1027.59
//        float list_2_main_grnd_level = list_2_main["grnd_level"]; // 993.61
        int list_2_main_humidity = list_2_main["humidity"]; // 72
        float list_2_main_temp_kf = list_2_main["temp_kf"]; // 2.32
        
        JsonObject list_2_weather_0 = list_2["weather"][0];
//        int list_2_weather_0_id = list_2_weather_0["id"]; // 800
//        const char* list_2_weather_0_main = list_2_weather_0["main"]; // "Clear"
        const char* list_2_weather_0_description = list_2_weather_0["description"]; // "cielo sereno"
        const char* list_2_weather_0_icon = list_2_weather_0["icon"]; // "01n"
        
        int list_2_clouds_all = list_2["clouds"]["all"]; // 0
        
        float list_2_wind_speed = list_2["wind"]["speed"]; // 2.7
        float list_2_wind_deg = list_2["wind"]["deg"]; // 50.0024
        
        const char* list_2_sys_pod = list_2["sys"]["pod"]; // "n"
        
        const char* list_2_dt_txt = list_2["dt_txt"]; // "2019-02-27 06:00:00"
        
        JsonObject list_3 = list[3];
        long list_3_dt = list_3["dt"]; // 1551258000
        
        JsonObject list_3_main = list_3["main"];
        float list_3_main_temp = list_3_main["temp"]; // 10.82
        float list_3_main_temp_min = list_3_main["temp_min"]; // 9.66
        float list_3_main_temp_max = list_3_main["temp_max"]; // 10.82
        float list_3_main_pressure = list_3_main["pressure"]; // 1028.08
//        float list_3_main_sea_level = list_3_main["sea_level"]; // 1028.08
//        float list_3_main_grnd_level = list_3_main["grnd_level"]; // 994.44
        int list_3_main_humidity = list_3_main["humidity"]; // 78
        float list_3_main_temp_kf = list_3_main["temp_kf"]; // 1.16
        
        JsonObject list_3_weather_0 = list_3["weather"][0];
//        int list_3_weather_0_id = list_3_weather_0["id"]; // 800
//        const char* list_3_weather_0_main = list_3_weather_0["main"]; // "Clear"
        const char* list_3_weather_0_description = list_3_weather_0["description"]; // "cielo sereno"
        const char* list_3_weather_0_icon = list_3_weather_0["icon"]; // "01d"
        
        int list_3_clouds_all = list_3["clouds"]["all"]; // 0
        
        float list_3_wind_speed = list_3["wind"]["speed"]; // 2.01
        float list_3_wind_deg = list_3["wind"]["deg"]; // 87.0018
        
        const char* list_3_sys_pod = list_3["sys"]["pod"]; // "d"
        
        const char* list_3_dt_txt = list_3["dt_txt"]; // "2019-02-27 09:00:00"
        
//        JsonObject city = doc["city"];
//        long city_id = city["id"]; // 6534286
//        const char* city_name = city["name"]; // "Bernareggio"
        
//        float city_coord_lat = city["coord"]["lat"]; // 45.6485
//        float city_coord_lon = city["coord"]["lon"]; // 9.4064
        
//        const char* city_country = city["country"]; // "IT"
//        int city_population = city["population"]; // 8298


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
		next3.vi = 0;
		next3.cl = list_0_clouds_all;
        next3.ep = list_0_dt;
//        next3.ti = "0"+String((list_0_dt % 86400)/3600)+":00";
		int h = (next3.ep+dst_tz.tz+dst_tz.dst) % 86400 / 3600;
		if (h<10){next3.ti = "0"+String(h)+":00";}		else{next3.ti = String(h)+":00";}
        
        next6.de = list_1_weather_0_description;
        next6.ic = list_1_weather_0_icon;
        next6.te = list_1_main_temp;
        next6.mi = list_1_main_temp_min;
        next6.mx = list_1_main_temp_max;
        next6.hu = list_1_main_humidity;
        next6.pr = list_1_main_pressure;
        next6.ws = list_1_wind_speed;
        next6.wd = list_1_wind_deg;
        next6.wd = list_0_wind_deg;
		next6.vi = 0;
        next6.ep = list_1_dt;
//        next6.ti = "0"+String((list_1_dt % 86400)/3600)+":00";
		h = (next6.ep+next3.ep+dst_tz.tz+dst_tz.dst) % 86400 / 3600;
		if (h<10){next6.ti = "0"+String(h)+":00";}else{next6.ti = String(h)+":00";};

		
        next9.de = list_3_weather_0_description;
        next9.ic = list_3_weather_0_icon;
        next9.te = list_3_main_temp;
        next9.mi = list_3_main_temp_min;
        next9.mx = list_3_main_temp_max;
        next9.hu = list_3_main_humidity;
        next9.pr = list_3_main_pressure;
        next9.ws = list_3_wind_speed;
        next9.wd = list_3_wind_deg;
        next9.wd = list_0_wind_deg;
		next9.vi = 0;
        next9.ep = list_3_dt;
//        next9.ti = "0"+String((list_3_dt % 86400)/3600)+":00";		
		h = (next9.ep+next3.ep+dst_tz.tz+dst_tz.dst) % 86400 / 3600;
		if (h<10){next9.ti = "0"+String(h)+":00";}else{next9.ti = String(h)+":00";};
		

        Serial.print("next3h ");
        Serial.println(next3.ep);
        Serial.print("next6h ");
        Serial.println(next6.ep);
        Serial.print("next9h ");
        Serial.println(next9.ep);

      }
    }
    client.stop();
  }
  else
  {
    client.stop();
  }
  
}

//api.openweathermap.org/data/2.5/forecast/daily?q=Bernareggio,It&appid=2f31dba5954c10dc63d1047e2c28acf3&cnt=4&lang=it&units=Metric&cnt=4
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

        const size_t capacity = 3*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(2) + 3*JSON_OBJECT_SIZE(4) + 2*JSON_OBJECT_SIZE(5) + 3*JSON_OBJECT_SIZE(6) + 3*JSON_OBJECT_SIZE(8) + 520;
        DynamicJsonDocument doc(capacity);
        
        deserializeJson(doc, line);
        
//        JsonObject city = doc["city"];
//        long city_id = city["id"]; // 6534286
//        const char* city_name = city["name"]; // "Bernareggio"
        
//        float city_coord_lon = city["coord"]["lon"]; // 9.4064
//        float city_coord_lat = city["coord"]["lat"]; // 45.6485
        
//        const char* city_country = city["country"]; // "IT"
//        int city_population = city["population"]; // 8298
        
//        const char* cod = doc["cod"]; // "200"
//        float message = doc["message"]; // 2.3220518
//        int cnt = doc["cnt"]; // 3
        
        JsonArray list = doc["list"];
        
/*
        JsonObject list_0 = list[0];
        long list_0_dt = list_0["dt"]; // 1551178800
        
        JsonObject list_0_temp = list_0["temp"];
        int list_0_temp_day = list_0_temp["day"]; // 10
        float list_0_temp_min = list_0_temp["min"]; // 7.26
        int list_0_temp_max = list_0_temp["max"]; // 10
        float list_0_temp_night = list_0_temp["night"]; // 7.26
        int list_0_temp_eve = list_0_temp["eve"]; // 10
        int list_0_temp_morn = list_0_temp["morn"]; // 10
        
        float list_0_pressure = list_0["pressure"]; // 1027.03
        int list_0_humidity = list_0["humidity"]; // 81
        
        JsonObject list_0_weather_0 = list_0["weather"][0];
        int list_0_weather_0_id = list_0_weather_0["id"]; // 800
        const char* list_0_weather_0_main = list_0_weather_0["main"]; // "Clear"
        const char* list_0_weather_0_description = list_0_weather_0["description"]; // "cielo sereno"
        const char* list_0_weather_0_icon = list_0_weather_0["icon"]; // "01n"
        
        float list_0_speed = list_0["speed"]; // 1.11
        int list_0_deg = list_0["deg"]; // 12
        int list_0_clouds = list_0["clouds"]; // 0
*/        
        JsonObject list_1 = list[1];
        long list_1_dt = list_1["dt"]; // 1551265200
        
        JsonObject list_1_temp = list_1["temp"];
//        float list_1_temp_day = list_1_temp["day"]; // 13.1
        float list_1_temp_min = list_1_temp["min"]; // 3.09
        float list_1_temp_max = list_1_temp["max"]; // 13.95
//        float list_1_temp_night = list_1_temp["night"]; // 3.09
//        float list_1_temp_eve = list_1_temp["eve"]; // 8.26
//        float list_1_temp_morn = list_1_temp["morn"]; // 4.41
        
        float list_1_pressure = list_1["pressure"]; // 1027.18
        int list_1_humidity = list_1["humidity"]; // 86
        
        JsonObject list_1_weather_0 = list_1["weather"][0];
//        int list_1_weather_0_id = list_1_weather_0["id"]; // 800
//        const char* list_1_weather_0_main = list_1_weather_0["main"]; // "Clear"
        const char* list_1_weather_0_description = list_1_weather_0["description"]; // "cielo sereno"
        const char* list_1_weather_0_icon = list_1_weather_0["icon"]; // "01d"
        
        float list_1_speed = list_1["speed"]; // 1.86
        int list_1_deg = list_1["deg"]; // 156
        int list_1_clouds = list_1["clouds"]; // 0
        
        JsonObject list_2 = list[2];
        long list_2_dt = list_2["dt"]; // 1551351600
        
        JsonObject list_2_temp = list_2["temp"];
//        float list_2_temp_day = list_2_temp["day"]; // 13.4
        float list_2_temp_min = list_2_temp["min"]; // 1.27
        float list_2_temp_max = list_2_temp["max"]; // 13.4
//        float list_2_temp_night = list_2_temp["night"]; // 4.06
//        float list_2_temp_eve = list_2_temp["eve"]; // 8.55
//        float list_2_temp_morn = list_2_temp["morn"]; // 1.27
        
        float list_2_pressure = list_2["pressure"]; // 1020.55
        int list_2_humidity = list_2["humidity"]; // 86
        
        JsonObject list_2_weather_0 = list_2["weather"][0];
//        int list_2_weather_0_id = list_2_weather_0["id"]; // 800
//        const char* list_2_weather_0_main = list_2_weather_0["main"]; // "Clear"
        const char* list_2_weather_0_description = list_2_weather_0["description"]; // "cielo sereno"
        const char* list_2_weather_0_icon = list_2_weather_0["icon"]; // "01d"
        
        float list_2_speed = list_2["speed"]; // 3.02
        int list_2_deg = list_2["deg"]; // 261
        int list_2_clouds = list_2["clouds"]; // 0

// *******************
        JsonObject list_3 = list[2];
        long list_3_dt = list_3["dt"]; // 1551351600
        
        JsonObject list_3_temp = list_3["temp"];
        float list_3_temp_min = list_3_temp["min"]; // 1.27
        float list_3_temp_max = list_3_temp["max"]; // 13.4
        
        float list_3_pressure = list_3["pressure"]; // 1020.55
        int list_3_humidity = list_3["humidity"]; // 86
        
        JsonObject list_3_weather_0 = list_3["weather"][0];
        const char* list_3_weather_0_description = list_3_weather_0["description"]; // "cielo sereno"
        const char* list_3_weather_0_icon = list_3_weather_0["icon"]; // "01d"
        
        float list_3_speed = list_3["speed"]; // 3.02
        int list_3_deg = list_3["deg"]; // 261
        int list_3_clouds = list_3["clouds"]; // 0

// *******************		

		
        dp1.de = list_1_weather_0_description;
        dp1.ic = list_1_weather_0_icon;
//        dp1.te = list_1_temp_day;
        dp1.mi = list_1_temp_min;
        dp1.mx = list_1_temp_max;
        dp1.hu = list_1_humidity;
        dp1.pr = list_1_pressure;
        dp1.ws = list_1_speed;
        dp1.wd = list_1_deg;
        dp1.ep = list_1_dt;
		dp1.cl = list_1_clouds;
        dp1.ti = "+1 D";//list_0_dt;

        dp2.de = list_2_weather_0_description;
        dp2.ic = list_2_weather_0_icon;
//        dp2.te = list_2_temp_day;
        dp2.mi = list_2_temp_min;
        dp2.mx = list_2_temp_max;
        dp2.hu = list_2_humidity;
        dp2.pr = list_2_pressure;
        dp2.ws = list_2_speed;
        dp2.wd = list_2_deg;
        dp2.ep = list_2_dt;
		dp2.cl = list_2_clouds;
        dp2.ti = "+2 D";//list_0_dt;

        dp3.de = list_3_weather_0_description;
        dp3.ic = list_3_weather_0_icon;
//        dp3.te = list_3_temp_day;
        dp3.mi = list_3_temp_min;
        dp3.mx = list_3_temp_max;
        dp3.hu = list_3_humidity;
        dp3.pr = list_3_pressure;
        dp3.ws = list_3_speed;
        dp3.wd = list_3_deg;
        dp3.ep = list_3_dt;
		dp3.cl = list_3_clouds;
        dp3.ti = "+3 D";//list_0_dt;


/*
        dp1.de = list_0_weather_0_description;
        dp1.ic = list_0_weather_0_icon;
        dp1.te = list_0_temp_day;
        dp1.mi = list_0_temp_min;
        dp1.mx = list_0_temp_max;
        dp1.hu = list_0_humidity;
        dp1.pr = list_0_pressure;
        dp1.ws = list_0_speed;
        dp1.wd = list_0_deg;
        dp1.ep = list_0_dt;
        dp1.ti = "+1D";//list_0_dt;
        
        dp2.de = list_1_weather_0_description;
        dp2.ic = list_1_weather_0_icon;
        dp2.te = list_1_temp_day;
        dp2.mi = list_1_temp_min;
        dp2.mx = list_1_temp_max;
        dp2.hu = list_1_humidity;
        dp2.pr = list_1_pressure;
        dp2.ws = list_1_speed;
        dp2.wd = list_1_deg;
        dp2.ep = list_1_dt;
        dp2.ti = "+2D";//list_1_dt;

        dp3.de = list_2_weather_0_description;
        dp3.ic = list_2_weather_0_icon;
        dp3.te = list_2_temp_day;
        dp3.mi = list_2_temp_min;
        dp3.mx = list_2_temp_max;
        dp3.hu = list_2_humidity;
        dp3.pr = list_2_pressure;
        dp3.ws = list_2_speed;
        dp3.wd = list_2_deg;
        dp3.ep = list_2_dt;
        dp3.ti = "+3D";//list_2_dt;
        Serial.print("next1 ");
        Serial.println(dp1.ep);
        Serial.print("next2 ");
        Serial.println(dp2.ep);
        Serial.print("next3 ");
        Serial.println(dp3.ep);
*/
      }
    }
    client.stop();
  }
  else
  {
    client.stop();
  }
  
}
