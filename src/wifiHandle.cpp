#include<wifiHandle.h>
#include <HTTPClient.h>
#define JST 3600 * 9 
/*
https://www.geosense.co.jp/blog_m5upload/
*/
void WIFI_NETWORK::connectWifi(){
  
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

bool WIFI_NETWORK::nextSecondTime(tm *time){
  bool nextTime = false;

  if (time->tm_sec == 59){
    time->tm_sec = 0;
    nextTime = true;
  }
  else{
    time->tm_sec += 1;
  }

  if (nextTime == true){
    nextTime = false;
    if (time->tm_min == 59){
      time->tm_min = 0;
      nextTime = true;
    }
    time->tm_min += 1;
  }
  
  if (nextTime == true){
    nextTime = false;
    if (time->tm_hour == 23){
      if(!getLocalTime(time)){
        M5.Lcd.println("Failed to obtain time");
        return false;
      }

      printLocalDay(*time);
    }
    else{
      time->tm_hour += 1;
    }
  }

  return true;
}

tm WIFI_NETWORK::getLocalTimeInfo(){
  struct tm timeinfo;
  char day_char[100];

  if(!getLocalTime(&timeinfo)){
    M5.Lcd.println("Failed to obtain time");
  }

  return timeinfo;
}

void WIFI_NETWORK::printLocalDay(tm timeinfo){
  char day_char[100];
  memset(day_char, '/0', 100);
  
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

void WIFI_NETWORK::printLocalTime(tm timeinfo){
  char time_char[100];
  memset(time_char, '/0', 100);

  // 現在時刻を表示
  sprintf(time_char,"%02d:%02d:%02d" 
    ,timeinfo.tm_hour
    ,timeinfo.tm_min
    ,timeinfo.tm_sec
    );

  M5.Lcd.fillRect(0, 160, 320, 60, TFT_BLACK);
  M5.Lcd.drawCentreString(time_char, 0, 160, 6);  
  
}

String WIFI_NETWORK::getHostName(){
  return hostName;
}
String WIFI_NETWORK::getDNSAddress(){
  return dnsIP;
}

String WIFI_NETWORK::httpPOSTRequest(String values_to_post){
  M5.Lcd.print("Connected to ");
  M5.Lcd.println("\nStarting connection to server...");
  connectWifi();

  client.setInsecure();
  if (!client.connect(host, httpsPort))
    M5.Lcd.println("Connection failed!");
  else {
    M5.Lcd.println("Connected to server!");
    client.println("POST " + url + " HTTP/1.1");
    client.println("HOST: " + (String)host);
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(values_to_post.length());
    client.println();
    client.println(values_to_post);

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        M5.Lcd.println("headers received");
        break;
      }
    }
    
    while (client.available()) {
      char c = client.read();
      M5.Lcd.write(c);
    }

    client.stop();
    delay(1000);
  }
}

String WIFI_NETWORK::httpGETRequest(String values_to_post){
  M5.Lcd.print("Connected to ");
  M5.Lcd.println("\nStarting connection to server...");
  connectWifi();
  
  http.begin(url);
  int httpCode = http.POST(values_to_post);
  String RESULT = "<b>Result:";
  if(httpCode > 0){
      M5.Lcd.printf(" HTTP Response:%d\n", httpCode);
      if(httpCode == HTTP_CODE_OK){
        M5.Lcd.println(" HTTP Success!!");
        String payload = http.getString();
        int valueStart = payload.indexOf('<b>Result:');
        int valueEnd = payload.indexOf('</b>');
        String valueStr = payload.substring(valueStart, valueEnd);
        M5.Lcd.println(payload);
      }
  }else{
    M5.Lcd.println(" FAILED");
    Serial.printf(" HTTP failed,error: %s\n", http.errorToString(httpCode).c_str());
  }
   
    http.end();
}