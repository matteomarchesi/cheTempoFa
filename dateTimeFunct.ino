void getDateTime()
{
  gettimeofday(&tv, nullptr);
  now = time(nullptr);
  
  // localtime / gmtime every second change
  static time_t lastv = 0;
  
  struct tm * ptm;
  time ( &now );
  
  ptm = gmtime ( &now );
  minu = ptm->tm_min;
  seco = ptm->tm_sec;
  Serial.printf("%2d/%2d/%2d %2d:%2d:%02d\n", ptm->tm_mday, ptm->tm_mon, (ptm->tm_year-100), (ptm->tm_hour+CET)%24, ptm->tm_min, ptm->tm_sec);

  clearLine(3);
  display.printf("%2d-%2d-%2d %2d:%2d\n", ptm->tm_mday, ptm->tm_mon, (ptm->tm_year-100), (ptm->tm_hour+CET)%24, ptm->tm_min);
  display.display();
}
