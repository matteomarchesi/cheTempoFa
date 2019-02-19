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
