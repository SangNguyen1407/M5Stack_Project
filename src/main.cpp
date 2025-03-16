#include <Arduino.h>
#include <M5Core2.h>
#include <BLEDevice.h>
#include <BLE2902.h>
#include <SPIFFS.h>

#include "../lib/display.h"
#include "../lib/network.h"
#include "../lib/buttonEvent.h"
#include "../lib/fileHandle.h"

const char *CONF_FILENAME = "/test.txt";

void setup() {
  // LCD開始の表示
  M5.begin();
  delay(1000);
  M5.Lcd.setTextSize(2);
  File file = openFile();
  
  if (file){
    char str[128];
    String sData = readFile();

    if (sData != ""){
      int start = 0;
      int end = sData.indexOf(',', start);

      start = end + 1;
      end = sData.indexOf(',', start);
      sprintf(str, "test: %s", sData.substring(start, end)); //2
      displayMode = DISPLAY_MAIN;
      ShowDisplay(DISPLAY_MAIN);
      M5.Lcd.drawString(str, 10, 60, 2);
    }
    else{
      displayMode = DISPLAY_SCAN;
      ShowDisplay(DISPLAY_SCAN);
    }
  }
  else{
    M5.Lcd.drawString("SPIFFS NOT WORKING...", 10, 0, 2);
  }
  
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.drawCentreString("WRITE", 30, 260, 2);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.drawCentreString("NEXT", 170, 260, 2);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.drawCentreString("READ", 260, 260, 2);

  M5.BtnA.addHandler(BtnAEvent, E_TOUCH);
  M5.BtnB.addHandler(BtnBEvent, E_TOUCH);
  M5.BtnC.addHandler(BtnCEvent, E_TOUCH);

}

void loop() {
  M5.update();
  delay(100);
}