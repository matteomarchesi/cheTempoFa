void clearLine(int lineN){
  display.setCursor(0,lineN*8);
  for (int y=lineN*8; y<lineN*8+8; y++)
  {
    for (int x=0; x<127; x++)
    {
      display.drawPixel(x, y, BLACK); 
    }
  } 
}

void clearChar(int lineN, int colN){
  display.setCursor(colN*6,lineN*8);
  for (int y=lineN*8; y<lineN*8+8; y++)
  {
    for (int x=colN*6; x<colN*6+6; x++)
    {
      display.drawPixel(x, y, BLACK); 
    }
  } 
}

/*
 *  char size 6x8
 *  rows start at 0, 8, 16, 24  
 *  +---------------------+
 *  |cielo sereno         |
 *  |1034hPa 100%RH       |
 *  |  8.0dC    4.1km/h   |
 *  |-10.1/-10.1dC        |
 *  |Sat 27-02-29 16:05:38|
 *  +---------------------+
 *   012345678901234567890
 */
 
void printWeather(weather_data data){
  display.clearDisplay();
  display.setCursor(0,0);
  display.print(data.de);
  display.setCursor(100,0);
  display.print(data.ti);
  display.setCursor(0,8);
  display.printf("%4dhPa %3d%%RH", data.pr, data.hu);
  display.setCursor(0,16);
  display.printf("%4.1fdC %5.1fkm/h", data.te, data.ws);
  display.setCursor(0,24);
  display.printf("%4d/%4ddC", data.mi, data.mx);
  display.display();      
 
}

void printWeatherC(weather_data data){
//  display.clearDisplay();
  clearLine(0);
  clearLine(1);
  clearLine(2);
  display.setCursor(0,0);
  display.print(data.de);
  display.setCursor(0,8);
  display.printf("%4dhPa %3d%%RH", data.pr, data.hu);
  display.setCursor(0,16);
  display.printf("%4.1fdC %5.1fkm/h", data.te, data.ws);
//  display.setCursor(0,24);
//  display.printf("%4d/%4ddC", data.mi, data.mx);
  display.display();      
 
}
