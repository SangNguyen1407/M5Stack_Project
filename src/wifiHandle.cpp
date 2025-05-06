#include<../lib/wifiHandle.h>

#define JST 3600 * 9 

void WIFI_NETWORK::setupWifi(){
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  
  //init and get the time
  configTime(JST, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");
  printLocalTime();
}

void WIFI_NETWORK::printLocalTime(){
  struct tm timeinfo;
  char time_char[100];
  memset(time_char, '/0', 100);

  if(!getLocalTime(&timeinfo)){
    M5.Lcd.println("Failed to obtain time");
    return;
  }

  // 現在時刻を表示
  sprintf(time_char,"%04d-%02d-%02d %02d:%02d:%02d" 
    ,timeinfo.tm_year + 1900
    ,timeinfo.tm_mon + 1
    ,timeinfo.tm_mday
    ,timeinfo.tm_hour
    ,timeinfo.tm_min
    ,timeinfo.tm_sec
    );

    M5.Lcd.fillRect(0, 120, 320, 30, TFT_BLACK);
    M5.Lcd.drawCentreString(time_char, 0, 120, 4);  
  
}