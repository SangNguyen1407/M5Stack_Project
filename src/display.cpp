#include <Arduino.h>
#include <M5Core2.h>

#include "../lib/buttonEvent.h"
#include "../lib/display.h"
#include "../lib/network.h"
#include "../lib/fileHandle.h"

#define DISPLAY_MAX_SIZE 6
#define FONT_JAPAN       4
#define LINE_MAX_CHAR    10

#define TITLE_1_COLOR    TFT_DARKGREEN

int title_h   = 30;
int padding_x = 10;
int padding_y = 5;
int circle    = 10;

int content_h = M5.Lcd.width() - title_h * 2;
int content_w = M5.Lcd.height();

void DISPLAY_SHOW::showTitle1(String title){
    M5.Lcd.fillRect(0, 0, content_w, title_h, TITLE_1_COLOR);
    M5.Lcd.drawString(title, padding_x, padding_y, FONT_JAPAN);
}

void DISPLAY_SHOW::showTitle2(String title){
    int color = (title == "1")? TFT_GREEN : (title == "2")? TFT_YELLOW : TFT_RED;

    M5.Lcd.fillRect(0, title_h + content_h, content_w, content_h, color);
}

void DISPLAY_SHOW::showLineOff(String device_name, int pos){
    M5.Lcd.fillRoundRect(0, title_h * pos, content_w, title_h, circle, TFT_BLACK);
    M5.Lcd.drawRoundRect(0, title_h * pos, content_w, title_h, circle, TFT_WHITE);
    M5.Lcd.drawString(device_name, padding_x, title_h*pos + padding_y, FONT_JAPAN);
}

void DISPLAY_SHOW::showLineOn(String device_name, int pos){
    M5.Lcd.fillRoundRect(0, title_h * pos, content_w, title_h, circle, TFT_DARKCYAN);
    M5.Lcd.drawRoundRect(0, title_h * pos, content_w, title_h, circle, TFT_WHITE);
    M5.Lcd.drawString(device_name, padding_x, title_h*pos + padding_y, FONT_JAPAN);
}

void DISPLAY_SHOW::ShowDisplay(DISPLAY_MODE mode){
    displayMode = mode;
    ShowDisplay();
}

void DISPLAY_SHOW::ShowDisplay(){
    M5.Lcd.fillRect(0, 0, content_w, content_h + title_h*2, TFT_BLACK);
    M5.Lcd.setTextColor(WHITE);

    switch (displayMode) {
        case DISPLAY_SCAN:
            showTitle1("SCANNING");
            break;

        case DISPLAY_CONNECT:
            showTitle1("CONNECT");
            break;

        case DISPLAY_MAIN:
            showTitle1(device_name);
            showTitle2(strength_level);
            break;

        case DISPLAY_STRENGTH_SETUP:
            showTitle1("SETUP");
            showStrengthLevel();
            break;

        default:
            break;
    }
}

void DISPLAY_SHOW::displayScanDevice(std::vector<BLEAdvertisedDevice> pAdvertiesdDeviceList){
    M5.Lcd.fillRect(0, 40, content_w, content_h, TFT_BLACK);
    int device_max = pAdvertiesdDeviceList.size();
    if (device_max <= 0){
        return;
    }
    
    M5.Lcd.fillRoundRect(0, 30, content_w, 30, 10, TFT_DARKCYAN);
    int count = 0;
    for (int opt = 0; opt< 10; opt++){
        if (count > 5){
            break;
        }
        M5.Lcd.drawRoundRect(0, 30*(opt+1), content_w, 30, 10, TFT_WHITE);
        M5.Lcd.drawString(pAdvertiesdDeviceList.at(opt).getName().substr(0,LINE_MAX_CHAR).c_str(), 10, 30*(opt+1), FONT_JAPAN);
    }

}

void DISPLAY_SHOW::showAdvertisedDeviceList(std::vector<BLEAdvertisedDevice> adverties_device_list, int start){

    M5.Lcd.fillRect(0, title_h, content_w, content_h, TFT_BLACK);
    int adverties_devices_count = (start + DISPLAY_MAX_SIZE > adverties_device_list.size())? 
                                    adverties_device_list.size() : start + DISPLAY_MAX_SIZE;

    for (int pos = start; pos< adverties_devices_count; pos++){
        int pos1 = pos % DISPLAY_MAX_SIZE;
        
        M5.Lcd.drawRoundRect(0, title_h*(pos1 + 1), content_w, title_h, circle, TFT_WHITE);
        M5.Lcd.drawString(adverties_device_list.at(pos).getName().substr(0,LINE_MAX_CHAR).c_str(), padding_x, title_h*(pos1 + 1) + padding_y, FONT_JAPAN);
    }   
}

void DISPLAY_SHOW::chooseDevice(std::vector<BLEAdvertisedDevice> adverties_device_list, int start){
    // 画面にデバイスの地位
    int opt_pos = start % DISPLAY_MAX_SIZE;

    if (opt_pos == 0){
        //　リストをリセットする
        showAdvertisedDeviceList(adverties_device_list, start);   
    }
    else {
        //　選択しない線
        showLineOff(adverties_device_list.at(start-1).getName().substr(0, LINE_MAX_CHAR).c_str(), opt_pos);
    }
    //　選択線
    showLineOn(adverties_device_list.at(start).getName().substr(0, LINE_MAX_CHAR).c_str(), opt_pos + 1);
    
}



void DISPLAY_SHOW::displayScanDevice(std::vector<String> device_list){
    M5.Lcd.fillRect(0, 40, content_w, content_h, TFT_BLACK);
    int device_max = device_list.size();
    if (device_max <= 0){
        return;
    }
    
    M5.Lcd.fillRoundRect(0, 30, content_w, 30, 10, TFT_DARKCYAN);
    int count = 0;
    for (int opt = 0; opt< 10; opt++){
        if (count > 5){
            break;
        }
        M5.Lcd.drawRoundRect(0, title_h*(opt+1), content_w, title_h, 10, TFT_WHITE);
        M5.Lcd.drawString(device_list.at(opt).substring(0, LINE_MAX_CHAR), padding_x, title_h*(opt+1) + padding_y, FONT_JAPAN);
    }
}

void DISPLAY_SHOW::chooseDevice(std::vector<String> device_list, int start){
    // 画面にデバイスの地位
    int opt_pos = start % DISPLAY_MAX_SIZE;

    if (opt_pos == 0){
        //　リストをリセットする
        showAdvertisedDeviceList(device_list, start);   
    }
    else {
        //　選択しない線
        showLineOff(device_list.at(start-1).substring(0,LINE_MAX_CHAR), opt_pos);
    }
    //　選択線
    showLineOn(device_list.at(start).substring(0, LINE_MAX_CHAR), opt_pos + 1);
}

void DISPLAY_SHOW::showAdvertisedDeviceList(std::vector<String> device_list, int start){
    M5.Lcd.fillRect(0, title_h, content_w, content_h, TFT_BLACK);
    int adverties_devices_count = (start + DISPLAY_MAX_SIZE > device_list.size())? 
    device_list.size() : start + DISPLAY_MAX_SIZE;

    for (int pos = start; pos< adverties_devices_count; pos++){
        int pos1 = pos % DISPLAY_MAX_SIZE;
        
        M5.Lcd.drawRoundRect(0, title_h*(pos1 + 1), content_w, title_h, circle, TFT_WHITE);
        M5.Lcd.drawString(device_list.at(pos).substring(0, LINE_MAX_CHAR), padding_x, title_h*(pos1 + 1) + padding_y, FONT_JAPAN);
    }   
}


void DISPLAY_SHOW::showAssistOn(){
    M5.Lcd.fillRect(0, title_h, content_w, content_h, TFT_GREEN);
}
void DISPLAY_SHOW::showAssistOff(){
    M5.Lcd.fillRect(0, title_h, content_w, content_h, TFT_DARKGREY);
}

void DISPLAY_SHOW::updateStrengthLevel(){
    strength_level = (strength_level == "1")? "2" : (strength_level == "2")? "3" : "1";
}

void DISPLAY_SHOW::showStrengthLevel(){
    int color = (strength_level == "1")? TFT_GREEN : (strength_level == "2")? TFT_YELLOW : TFT_RED;
    const char *level = (strength_level == "1")? "L" : (strength_level == "2")? "M" : "H";

    M5.Lcd.drawString("LEVEL: ", 0, title_h * 2, FONT_JAPAN);
    M5.Lcd.fillRect( content_w/2, title_h * 2 - padding_y, title_h * 2, title_h, color);
    M5.Lcd.drawString(level, content_w/2 + padding_x*2, title_h * 2, FONT_JAPAN);
}