#include <Arduino.h>
#include <M5Core2.h>
#include <BLEDevice.h>
#include <BLE2902.h>
#include <SPIFFS.h>

#include "displayHandle.h"
#include "networkHandle.h"
#include "buttonEvent.h"
#include "fileHandle.h"
#include "wifiHandle.h"

using namespace std;

static DISPLAY_SHOW display;

static bool isShowing;
static bool isHandle;
static int list_size;
static int item_pos; 
WIFI_NETWORK wifi;

int width;
int height;

void setup() {
  
  // LCD開始の表示
  M5.begin();
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE);

  width  = M5.Lcd.width(); //320
  height = M5.Lcd.height(); //240

  display.setModeDisplay(DISPLAY_MENU);
  isShowing = true;
  isHandle = false;

  wifi.setupWifi();
}

void loop() {
  M5.update();
/*
    "BLUETOOTH",
    "CLOCK",
    "WIFI",
    "GAME"
 */
  switch (display.getModeDisplay()){
    case DISPLAY_BLUETOOTH:
      if(isShowing){
          display.showTitleOnTop((int)DISPLAY_BLUETOOTH);
          display.showListMenu(0);
          isShowing = false;
          item_pos = 0;

          display.chooseItem(0);
      }
      break;
    
    case DISPLAY_CLOCK:
      if(isShowing){ 
        display.showTitleOnTop((int)DISPLAY_CLOCK);
        display.resetDisplay();
        wifi.printLocalDay();
        isShowing = false;
      }

      wifi.printLocalTime();
      break;

    case DISPLAY_WIFI:
      if(isShowing){
        display.showTitleOnTop((int)DISPLAY_WIFI);
        isShowing = false;
      }
      break;
    
    case DISPLAY_MENU:
      if(isShowing){
        display.showTitleOnTop((int)DISPLAY_MENU);

        display.addListMenu(LIST_MENU);
        display.showListMenu(0);
        isShowing = false;
        item_pos = 0;

        display.chooseItem(0);
      }
      break;
  }

  if (M5.BtnA.wasReleased()){
    if (display.getModeDisplay() != DISPLAY_MENU){
      return;
    }
    
    item_pos++;
    if (item_pos >= display.getListMenuSize()){
       item_pos = 0;
    }
    display.chooseItem(item_pos);
  }

  if (M5.BtnB.wasReleased()){
    display.setModeDisplay((DISPLAY_MODE)item_pos);
    isShowing = true;
  }

  if (M5.BtnC.wasReleased()){
    display.resetDisplay();
    display.setModeDisplay(DISPLAY_MENU);
    isShowing = true;
  }


  delay(100);
}