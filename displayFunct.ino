void clearPixArea(int ys, int ye, int xs, int xe){
  display.setCursor(ys,ye);
  for (int y=ys; y<=ye; y++)
  {
    for (int x=xs; x<=xe; x++)
    {
      display.drawPixel(x, y, BLACK); 
    }
  } 
}
 
void printWeatherC(weather_data data){
//  display.clearDisplay();
  clearPixArea(0,54,0,127); 
  display.setFont(&FreeMono9pt7b);
  display.setCursor(0,11);
  display.print(data.de.substring(0,11)); // cielo seren
  display.setCursor(0,24);
  display.printf("%+-4.1fC", data.te);     // -12.0dC   
  display.setFont(); 
  display.setCursor(0,27); 
  display.printf("%4dhPa %3d%%RH", data.pr, data.hu);
  display.setCursor(0,36); 
  display.printf("vento: %3.0fm/s %3ddeg", data.ws, data.wd);
  display.setCursor(0,45); 
  display.printf("%3d%%nubi  vi: %5dm", data.cl, data.vi);
  display.display();      
 
}

void printWeather(weather_data data){
//  display.clearDisplay();
  clearPixArea(0,63,0,127); 
  display.setFont(&FreeMono9pt7b);
  display.setCursor(0,11);
  display.print(data.de.substring(0,11)); // cielo seren
  display.setCursor(0,24);
  display.printf("%+-4d/%+-4dC ", data.mi, data.mx );     
  display.setFont(); 
  display.setCursor(0,27); 
  display.printf("%4dhPa %3d%%RH", data.pr, data.hu);
  display.setCursor(0,36); 
  display.printf("vento: %3.0fm/s %3ddeg", data.ws, data.wd);
  display.setCursor(0,45); 
  display.printf("%3d%%nubi", data.cl);
  display.setFont(&FreeMono9pt7b);
  display.setCursor(60,63);
  char charBuf[6];
  data.ti.toCharArray(charBuf, 6);
  display.printf("%5s", charBuf);
  display.setFont();
  display.display();      
 
}
