#include <Arduino.h>
#include <M5Core2.h>
#include <BLEDevice.h>
#include <BLE2902.h>
#include <SPIFFS.h>

#include "displayHandle.h"
#include "networkHandle.h"
#include "fileHandle.h"
#include "wifiHandle.h"

using namespace std;

#define MAX_DISPLAY_COUNT   8
static DISPLAY_SHOW display;

static bool isShowing;
static bool isHandle;
static int list_size;
static int item_pos; 
static struct tm timeinfo;
WIFI_NETWORK wifi;

int width;
int height;

static void func_bleDisplay();
static void func_clockDisplay();
static void func_wifiDisplay();
static void func_menuDisplay();
static void func_timeDisplay();
static void func_countDisplay();
static void func_alarmDisplay();
static void func_sleepTimeDisplay();

static void func_menuDisplay(){
  if(isShowing){
    display.showTitleOnTop((int)DISPLAY_MENU);

    display.addListMenu(LIST_MENU, LIST_MENU_MAX);
    display.showListMenu(0);
    isShowing = false;
    item_pos = 0;

    display.chooseItem(0);
  }
}

static void func_clockDisplay(){
    if(isShowing){ 
      timeinfo = wifi.getLocalTimeInfo();
      display.showTitleOnTop((int)DISPLAY_CLOCK);
      display.resetDisplay();
      wifi.printLocalDay(timeinfo);
      isShowing = false;
    }

  // wifi.printLocalTime();
  // struct tm timeinfo = wifi.getLocalTimeInfo();
}

static void func_sleepTimeDisplay(){
  if(isShowing){ 
    isShowing = false;

    display.resetDisplay();
    display.showTitleOnTop((int)DISPLAY_SLEEP_TIME);
    display.addListMenu(SLEEP_MENU, LIST_MENU_SLEEP_MAX);

    item_pos = 0;
    display.showListMenu(0);
    display.chooseItem(0);
  }

  if (M5.BtnA.wasReleased()){
    item_pos++;
    if (item_pos >= 2){
      item_pos = 0;
    }
    display.chooseItem(item_pos);
  }

  if (M5.BtnB.wasReleased()){
    String values;
    if (item_pos == 0){
      values = "{ \"ID\":\"1\", \"value\":\"1\" }";
    }
    else{
      values = "{ \"ID\":\"1\", \"value\":\"2\" }";
    }

    wifi.postValues(values);

    isShowing = true;
    func_menuDisplay();

    delay(1000);
  }
}

static void func_timeDisplay(){}
static void func_countDisplay(){}
static void func_alarmDisplay(){}
static void func_wifiDisplay(){}
static void func_bleDisplay(){}

typedef void (*func_t)();

static const func_t funcTbl[MAX_DISPLAY_COUNT] = {
  func_bleDisplay,
  func_clockDisplay,
  func_wifiDisplay,
  func_menuDisplay,
  func_timeDisplay,
  func_countDisplay,
  func_sleepTimeDisplay,
};

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

  wifi.connectWifi();
}

void loop() {
  M5.update();

  funcTbl[(int) display.getModeDisplay()]();

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

  if (display.getModeDisplay() == DISPLAY_CLOCK && !isShowing){
    while(1){
      wifi.nextSecondTime(&timeinfo);
      wifi.printLocalTime(timeinfo);
      M5.update();
      if (M5.BtnC.isPressed()){
        break;
      }
      delay(1000); //1秒
    }
  }

  delay(100);
}