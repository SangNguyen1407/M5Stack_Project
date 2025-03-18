#include <Arduino.h>
#include <M5Core2.h>
#include <BLEDevice.h>
#include <BLE2902.h>
#include <SPIFFS.h>

#include "../lib/display.h"
#include "../lib/network.h"
#include "../lib/buttonEvent.h"
#include "../lib/fileHandle.h"
#include "esp_system.h"

const char *CONF_FILENAME = "/test.txt";
int deviceCount = 0;

void setup() {
  // LCD開始の表示
  M5.begin();
  M5.Lcd.setTextSize(2);
  String sData = readFile();
  opt = OPT_1;

  if (sData != "" && sData != "\n"){
    displayMode = DISPLAY_MAIN;
    const char* opt = sData.substring(0,1).c_str();
    optStrength = (sData[0] == '1')? LEVEL_WEAK : (sData[0] == '2')? LEVEL_MID : LEVEL_HIGHT;
    ShowDisplay(DISPLAY_MAIN);
  }
  else{
    displayMode = DISPLAY_SCAN;
    ShowDisplay(DISPLAY_SCAN);
    writeFile("1,\n");
    BLEScanPeripheralList();
    deviceCount = pBLEAdvertiesdDeviceList.size();
  }
  M5.BtnA.addHandler(BtnAEvent, E_TOUCH);
  M5.BtnB.addHandler(BtnBEvent, E_TOUCH);
  M5.BtnC.addHandler(BtnCEvent, E_TOUCH);

}

void loop() {
  M5.update();

  if ( M5.BtnB.pressedFor(1000)){
    deleteFile();
    esp_restart();
  }

  if (displayMode == DISPLAY_SCAN && deviceCount > 0){
    displayMode = DISPLAY_CONNECT;
    ShowDisplay(DISPLAY_CONNECT);
  }

  if (displayMode == DISPLAY_MAIN && opt == OPT_1){
    if (M5.BtnA.isPressed()) {
      M5.Lcd.fillRect(0, 20, POSITION_WIDTH, POSITION_HEIGHT, TFT_GREEN);
    } else {
      M5.Lcd.fillRect(0, 20, POSITION_WIDTH, POSITION_HEIGHT, TFT_BLUE);
    }
    M5.Lcd.drawString(optDisplay[OPT_1], 100, 40, 2);
    
  }

  delay(100);
}