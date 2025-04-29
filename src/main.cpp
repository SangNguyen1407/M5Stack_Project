#include <Arduino.h>
#include <M5Core2.h>
#include <BLEDevice.h>
#include <BLE2902.h>
#include <SPIFFS.h>

#include "../lib/displayHandle.h"
#include "../lib/networkHandle.h"
#include "../lib/buttonEvent.h"
#include "../lib/fileHandle.h"

using namespace std;

static DISPLAY_SHOW display;

static bool isShowing;
static int list_size;
static int item_pos; 

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
}

void loop() {
  M5.update();

  switch (display.getModeDisplay()){
    case DISPLAY_BLUETOOTH:
      if(isShowing){
          display.showTitleOnTop((int)DISPLAY_BLUETOOTH);
          isShowing = false;
      }
      
      break;

    case DISPLAY_MENU:
      if(isShowing){
        display.showTitleOnTop((int)DISPLAY_MENU);
        display.showListMenu(0);
        isShowing = false;
        item_pos = 0;

        display.chooseItem(0);
      }

      if (M5.BtnA.wasReleased()){
        item_pos++;
        if (item_pos >= display.getListMenuSize()){
           item_pos = 0;
        }
        display.chooseItem(item_pos);
      }

      if (M5.BtnB.isPressed()){
        display.resetDisplay();
        display.setModeDisplay((DISPLAY_MODE)item_pos);
        isShowing = true;
      }

      break;

    case DISPLAY_CLOCK:
      if(isShowing){
        display.showTitleOnTop((int)DISPLAY_CLOCK);
        isShowing = false;
      }
      break;

    case DISPLAY_WIFI:
      if(isShowing){
        display.showTitleOnTop((int)DISPLAY_WIFI);
        isShowing = false;
      }
       break;
  }

  if (M5.BtnC.isPressed()){
    display.setModeDisplay(DISPLAY_MENU);
    isShowing = true;
  }


  delay(100);
}