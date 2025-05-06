#include <Arduino.h>
#include <M5Core2.h>
#include <BLEDevice.h>
#include <BLE2902.h>
#include <SPIFFS.h>

#include "../lib/displayHandle.h"
#include "../lib/networkHandle.h"
#include "../lib/buttonEvent.h"
#include "../lib/fileHandle.h"
#include "../lib/wifiHandle.h"

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

  switch (display.getModeDisplay()){
    case DISPLAY_BLUETOOTH:
      if(isShowing){
          display.showTitleOnTop((int)DISPLAY_BLUETOOTH);

          display.addListMenu(LIST_BLE);
          display.showListMenu(0);
          isShowing = false;
          item_pos = 0;

          display.chooseItem(0);
      }
      break;

    case DISPLAY_MENU:
      if(isShowing){
        display.showTitleOnTop("MENU");

        display.addListMenu(LIST_MENU);
        display.showListMenu(0);
        isShowing = false;
        item_pos = 0;

        display.chooseItem(0);
      }
      break;

    case DISPLAY_CLOCK:
      if(isShowing){
        display.showTitleOnTop((int)DISPLAY_CLOCK);
        display.addListMenu(LIST_CLOCK);
        display.showListMenu(0);
        isShowing = false;
        item_pos = 0;

        display.chooseItem(0);
      }
      else if(isHandle){
        isHandle = false;
        switch (item_pos)
        {
          case 0: // TIME
          display.setModeDisplay(DISPLAY_TIME);
          break;
          case 1: // COUNT
          break;
        }
      } 
      break;

    case DISPLAY_WIFI:
      if(isShowing){
        display.showTitleOnTop((int)DISPLAY_WIFI);
        isShowing = false;
      }
      break;

    case DISPLAY_TIME:
      wifi.printLocalTime();
      break;
  }

  if (M5.BtnA.wasReleased()){
    item_pos++;
    if (item_pos >= display.getListMenuSize()){
       item_pos = 0;
    }
    display.chooseItem(item_pos);
  }

  if (M5.BtnB.wasReleased()){
    // reset display
    display.resetDisplay();
    // show display
    if (display.getModeDisplay() == DISPLAY_MENU){
      display.setModeDisplay((DISPLAY_MODE)item_pos);
      isShowing = true;
      //reset position
      item_pos = 0;
    }
    else{
      // Title
      switch (display.getModeDisplay())
      {
        case DISPLAY_BLUETOOTH:
        //  display.showTitleOnTop(LIST_BLE[item_pos]);
          break;
        case DISPLAY_CLOCK:
          display.showTitleOnTop(LIST_CLOCK[item_pos]);
          break;
        case DISPLAY_WIFI:
          break;
      }

      isHandle = true;
    }
  }

  if (M5.BtnC.wasReleased()){
    display.resetDisplay();
    display.setModeDisplay(DISPLAY_MENU);
    isShowing = true;
  }


  delay(100);
}