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
static BLEControl Ble;
static DISPLAY_SHOW displayShow;
std::vector<String> device_list;
String strength_level;
String device_name;


void setup() {
  
  // LCD開始の表示
  M5.begin();
  M5.Lcd.setTextSize(1);

  // フラッシュのメモリーに情報を読み出す
  String sData = readFile();
  device_list.push_back("test1");
  device_list.push_back("日本語");
  device_list.push_back("あいうえお");
  device_list.push_back("アイウエオ");
  device_list.push_back("日本語１２３");
  device_list.push_back("日本語123");
  device_list.push_back("あいうえおアイウエオtest7");
  device_list.push_back("アイウエオ日本語test8");
  device_list.push_back("你好");
  device_list.push_back("안녕하세요");
  device_list.push_back("Päivää");
  device_list.push_back("Здравствуйте");
  device_list.push_back("Доброе утро");
  device_list.push_back("test15test15test15test15test15test15test15test15test15test15test15");
  device_list.push_back("#$%&'()()~.?<L+");
  device_list.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz");
  device_list.push_back("test18");
  device_list.push_back("test19");
  device_list.push_back("test20");
  // フラッシュのメモリーに情報があれば、MAIN画面に移動する
  if (sData != "" && sData.length() != 0){
    String strength_level = sData.substring(0, sData.indexOf(','));
    String device_name = sData.substring(2,sData.length()).c_str();

    DISPLAY_SHOW displayInit(DISPLAY_MAIN, strength_level, sData.substring(2,sData.length()).c_str());
    displayShow = displayInit;

    // displayShow.displayMode = DISPLAY_MAIN;
    displayShow.ShowDisplay();
    // displayShow.showTitle1(device_name);
    // displayShow.showTitle2(strength_level);
  }
  else{
    //最初の起動する場合、SCAN画面に実施する
    displayShow.ShowDisplay(DISPLAY_SCAN);
    Ble.BLEScanPeripheralList();
    delay(1000);
  }
}

void loop() {
  M5.update();
  static int opt = 0;
  //Bボタンを長押すと、なんでも画面でフラッシュにファイルを削除し、再起動する。
  if ( M5.BtnB.pressedFor(1000) && M5.BtnA.isPressed()){
    // フラッシュにファイルを削除し
    deleteFile();
    // 再起動
    esp_restart();
  }

  switch (displayShow.displayMode){
    case DISPLAY_CONNECT:
      // CONNECT画面にAボタンを長押すと、選択した設備をBLEで接続する
      // MAIN画面に移動する

      if (M5.BtnA.pressedFor(1000)){
        //　選択した設備をBLEで接続する
        char str[128];
        memset(str, '\0', strlen(str));
        sprintf(str, "%s,%s\n", "1", device_list.at(opt).substring(0, 120));
        writeFile(str, FILE_WRITE);
        // MAIN画面に移動する
        esp_restart();
      }
      if (M5.BtnA.wasReleased()){
        if (opt++ >= device_list.size()-1){
          opt = 0;
        }
        // displayShow.chooseDevice(Ble.advertiseDeviceCB->pBLEAdvertiesdDeviceList, opt);
        displayShow.chooseDevice(device_list, opt);
      }
      break;

    case DISPLAY_MAIN:
      //  MAIN画面にリアルタイムで処理する
      if (M5.BtnA.isPressed()) {
        displayShow.showAssistOn();
      } else {
        displayShow.showAssistOff();
      }

      if (M5.BtnB.pressedFor(1000)){
        displayShow.ShowDisplay(DISPLAY_STRENGTH_SETUP);        
      }
      break;

    case DISPLAY_SCAN:
    //  if (Ble.advertiseDeviceCB->pBLEAdvertiesdDeviceList.size() > 0){
        opt = 0;
        displayShow.ShowDisplay(DISPLAY_CONNECT);
        // displayShow.showList(Ble.advertiseDeviceCB->pBLEAdvertiesdDeviceList, opt);
        displayShow.chooseDevice(device_list, opt);
    //  }
      break;

    case DISPLAY_STRENGTH_SETUP:
      if (M5.BtnA.pressedFor(1000)){
        char str[128];
        memset(str, '\0', 128);
        sprintf(str, "%s,%s\n", displayShow.strength_level, displayShow.device_name);
        writeFile(str, FILE_WRITE);

        displayShow.ShowDisplay(DISPLAY_MAIN);
      }
      else if(M5.BtnA.wasReleased()) {
        displayShow.updateStrengthLevel();
        displayShow.showStrengthLevel();
      }
  }


  delay(100);
}