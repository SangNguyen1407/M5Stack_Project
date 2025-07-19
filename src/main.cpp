#include <Arduino.h>
#include <M5Core2.h>
#include <BLEDevice.h>
#include <BLE2902.h>
#include <SPIFFS.h>

#include "displayHandle.h"
#include "bleHandle.h"
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
BLEControl ble;

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
    //最初、Wifi接続し、日時を取得するです。
    if(isShowing){ 
      wifi.connectWifi();
      timeinfo = wifi.getLocalTimeInfo();
      display.showTitleOnTop((int)DISPLAY_CLOCK);
      display.resetDisplay();
      wifi.printLocalDay(timeinfo);

      isShowing = false;
    }

    //1秒で、画面に更新する
    while(true){
      wifi.nextSecondTime(&timeinfo);
      wifi.printLocalTime(timeinfo);
      M5.update();
      if (M5.BtnC.isPressed()){
        break;
      }
      delay(1000); //1秒
    }
}

static void func_sleepTimeDisplay(){
  bool isExisted = false;

  if(isShowing){ 
    isShowing = false;

    display.resetDisplay();
    display.showTitleOnTop((int)DISPLAY_SLEEP_TIME);
    display.addListMenu(SLEEP_MENU, LIST_MENU_SLEEP_MAX);

    item_pos = 0;
    display.showListMenu(0);
    display.chooseItem(0);
  }

  // handle when press buttonA
  if (M5.BtnA.wasReleased()){
    item_pos++;
    if (item_pos >= 2){
      item_pos = 0;
    }
    display.chooseItem(item_pos);
  }

  // handle when press buttonB
  if (M5.BtnB.wasReleased()){
    // create JSON data
    String values = "";
    // send data (SLEEP - AWAKE)
    // SLEEP value : 1
    // AWAKE value : 2
    if (item_pos == 0){
      values = "{ \"ID\":\"1\", \"value\":\"1\" }";
    }
    else{
      values = "{ \"ID\":\"1\", \"value\":\"2\" }";
    }
    // send data
    wifi.httpGETRequest(values);

    //show LIST MENU
    isExisted = true;
  }

    // handle when press buttonB
  if (M5.BtnC.wasReleased() || isExisted){
    //show LIST MENU
    isShowing = true;
    func_menuDisplay();
  }
}
static void func_bleDisplay(){
  if(isShowing){ 
    isShowing = false;

    display.resetDisplay();
    display.showTitleOnTop((int)DISPLAY_BLUETOOTH);
  }
  ble.BLEStart();
  ble.BLEScanPeripheralList();
}


static void func_timeDisplay(){}
static void func_countDisplay(){}
static void func_alarmDisplay(){}
static void func_wifiDisplay(){}

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
}

void loop() {
  M5.update();
  // メニューの処理
  funcTbl[(int) display.getModeDisplay()]();

  //Aボタンを押下すると、次の機能を移動するのを処理する
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

  //Bボタンを押下すると、機能を実施する
  if (M5.BtnB.wasReleased()){
    display.setModeDisplay((DISPLAY_MODE)item_pos);
    isShowing = true;
  }

  //Cボタンを押下すると、機能を止まて、メニュー画面に移動する
  if (M5.BtnC.isPressed() && 
    display.getModeDisplay() != DISPLAY_MENU){
    display.resetDisplay();
    display.setModeDisplay(DISPLAY_MENU);
    isShowing = true;
  }

  delay(100);
}