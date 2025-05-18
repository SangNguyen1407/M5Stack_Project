#include<wifiHandle.h>

#define JST 3600 * 9 

void WIFI_NETWORK::setupWifi(){
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  
  //init and get the time
  configTime(JST, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");

  hostName = WiFi.getHostname();
  macAddress = WiFi.macAddress();
}

void WIFI_NETWORK::printLocalDay(){
  struct tm timeinfo;
  char day_char[100];

  if(!getLocalTime(&timeinfo)){
    M5.Lcd.println("Failed to obtain time");
    return;
  }

  // 現在時刻を表示
  sprintf(day_char,"%04d-%02d-%02d" 
    ,timeinfo.tm_year + 1900
    ,timeinfo.tm_mon + 1
    ,timeinfo.tm_mday
  );

  
  M5.Lcd.fillRect(0, 60, 320, 60, TFT_BLACK);
  M5.Lcd.drawCentreString(getHostName(), 0, 60, 4);
  M5.Lcd.drawCentreString(day_char, 0, 100, 4); 
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
  sprintf(time_char,"%02d:%02d:%02d" 
    ,timeinfo.tm_hour
    ,timeinfo.tm_min
    ,timeinfo.tm_sec
    );

  M5.Lcd.fillRect(0, 160, 320, 30, TFT_BLACK);
  M5.Lcd.drawCentreString(time_char, 0, 160, 4);  
  
}

String WIFI_NETWORK::getHostName(){
  return hostName;
}
String WIFI_NETWORK::getDNSAddress(){
  return dnsIP;
}