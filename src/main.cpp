#include <Arduino.h>
#include <M5Core2.h>
#include <BLEDevice.h>
#include <BLE2902.h>
#include <SPIFFS.h>

#include "../lib/display.h"
#include "../lib/network.h"
#include "../lib/buttonEvent.h"

void setup() {
  // LCD開始の表示
  M5.begin();
  delay(1000);
  char str[128];
  bool success = SPIFFS.begin(true);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE);
  File fileTest = SPIFFS.open("/test.txt", FILE_WRITE);
  fileTest.println("1,2,3,4,5,6,7\n");
  fileTest.close();

  fileTest = SPIFFS.open("/test.txt", FILE_READ);
  if (success && fileTest){
    int test = fileTest.read();
    String readStr = fileTest.readStringUntil('\n');
    
    int start = 0;
    int end = readStr.indexOf(',', start);
    
    start = end + 1;
    end = readStr.indexOf(',', start);
    sprintf(str, "test: %s", readStr.substring(start, end)); //2
    
    
    M5.Lcd.drawString(str, 10, 0, 2);
  }
  else{
    fileTest = SPIFFS.open("/test.txt", FILE_WRITE);
    if (fileTest){
      M5.Lcd.drawString("File is created", 0, 0, 2);
    }
    else{
      M5.Lcd.drawString("File is NOT exsisted", 0, 0, 2);
    }
  }
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.drawCentreString("SCAN", 30, 260, 2);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.drawCentreString("NEXT", 170, 260, 2);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.drawCentreString("OK", 270, 260, 2);

  M5.BtnA.addHandler(BtnAEvent, E_TOUCH);
  M5.BtnB.addHandler(BtnBEvent, E_TOUCH);
  M5.BtnC.addHandler(BtnCEvent, E_TOUCH);

}

void loop() {
  M5.update();
  delay(100);
}