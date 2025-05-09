#include <Arduino.h>
#include <M5Core2.h>

// #include "../lib/buttonEvent.h"
#include "../lib/displayHandle.h"
// #include "../lib/networkHandle.h"
// #include "../lib/fileHandle.h"

#define DISPLAY_MAX_SIZE 6
#define FONT             4
#define LINE_MAX_CHAR    10

int title_h   = 30;
int padding_x = 10;
int padding_y = 5;
int circle    = 10;

const char *LIST_MENU[LIST_MENU_MAX] = {
    "BLUETOOTH",
    "CLOCK",
    "WIFI",
    "GAME"
};

const char *LIST_BLE[LIST_MENU_MAX] = {
    "SCAN",
    "CENTERAL",
    "PERIHERAL",
    "MAX"
};

const char *LIST_CLOCK[LIST_MENU_MAX] = {
    "TIME",
    "COUNT",
    "ALARM",
    "STEP WATCH"
};

const char *LIST_GAME[LIST_MENU_MAX] = {
    "CARO",
    "ANGRY BIRD",
    "MAX_1",
    "MAX_2"
};

void DISPLAY_SHOW::addListMenu(const char *list_menu[]){
    if (list.size()> 0){
        list.clear();
    }

    int list_size = sizeof(list_menu)/ sizeof(list_menu[0]);
    for(int pos = 0; pos < LIST_MENU_MAX; pos++){
        list.push_back(list_menu[pos]);
    }
}

void DISPLAY_SHOW::showTitleOnTop(String title){
    M5.Lcd.fillRect(0, 0, width, title_h, TFT_DARKGREEN);
    M5.Lcd.drawCentreString(title, width/2, padding_y, FONT);
}

void DISPLAY_SHOW::showTitleOnTop(int pos){
    String title = list.at(pos);
    showTitleOnTop(title);
}

void DISPLAY_SHOW::showTitleOnMiddle(String title){
    int color = (title == "1")? TFT_GREEN : (title == "2")? TFT_YELLOW : TFT_RED;

    M5.Lcd.fillRect(0, title_h + height, width, height, color);
}

void DISPLAY_SHOW::showLineOff(String item, int pos){
    M5.Lcd.fillRoundRect(0, title_h*pos, width, title_h, circle, TFT_BLACK);
    M5.Lcd.drawRoundRect(0, title_h*pos, width, title_h, circle, TFT_WHITE);
    M5.Lcd.drawCentreString(item, width/2, title_h*pos + padding_y, FONT);
}

void DISPLAY_SHOW::showLineOn(String item, int pos){
    M5.Lcd.fillRoundRect(0, title_h*pos, width, title_h, circle, TFT_DARKCYAN);
    M5.Lcd.drawRoundRect(0, title_h*pos, width, title_h, circle, TFT_WHITE);
    M5.Lcd.drawCentreString(item, width/2, title_h*pos + padding_y, FONT);
}

/**
 * show list in main display
 */
void DISPLAY_SHOW::showListMenu(int start){

    M5.Lcd.fillRect(0, title_h, width, height, TFT_BLACK);
    int list_max = (start + DISPLAY_MAX_SIZE > list.size())? 
                list.size() : start + DISPLAY_MAX_SIZE;

    for (int pos = start; pos< list_max; pos++){
        int diplay_pos = pos % DISPLAY_MAX_SIZE;
        M5.Lcd.drawRoundRect(0, title_h*(diplay_pos + 1), width, title_h, circle, TFT_WHITE);
        M5.Lcd.drawCentreString(list.at(pos), width/2, title_h*(diplay_pos + 1) + padding_y, FONT);
    }   
}

void DISPLAY_SHOW::nextItem(int start){
    // 画面にデバイスの地位
    int opt_pos = start % DISPLAY_MAX_SIZE;

    if (opt_pos == 0){
        //　リストをリセットする
        showListMenu(start);
    }
    else {
        //　選択しない線
        showLineOff(list.at(start-1), opt_pos);
    }
    //　選択線
    showLineOn(list.at(start), opt_pos + 1);
    
}

int DISPLAY_SHOW::getListMenuSize(){
    return LIST_MENU_MAX;
}


String DISPLAY_SHOW::getItemName(int pos){
    return list.at(pos).c_str();
}

void DISPLAY_SHOW::setModeDisplay(DISPLAY_MODE display_mode){
    mode = display_mode;
}

DISPLAY_MODE DISPLAY_SHOW::getModeDisplay(){
    return mode;
}

void DISPLAY_SHOW::chooseItem( int start){
    // 画面にデバイスの地位
    int opt_pos = start % DISPLAY_MAX_SIZE;
    if (opt_pos == 0){
        //　リストをリセットする
        showListMenu(start);   
    }
    else {
        //　選択しない線
        showLineOff(list.at(start-1), opt_pos);
    }
    //　選択線
    showLineOn(list.at(start), opt_pos + 1);
}

void DISPLAY_SHOW::showAssistOn(){
    M5.Lcd.fillRect(0, title_h, width, height, TFT_GREEN);
}

void DISPLAY_SHOW::showAssistOff(){
    M5.Lcd.fillRect(0, title_h, width, height, TFT_DARKGREY);
}

void DISPLAY_SHOW::resetDisplay(){
    M5.Lcd.fillRect(0, title_h, width, height, TFT_BLACK);
}

void DISPLAY_SHOW::updateStrengthLevel(){
    strength_level = (strength_level == "1")? "2" : (strength_level == "2")? "3" : "1";
}

void DISPLAY_SHOW::showStrengthLevel(){
    int color = (strength_level == "1")? TFT_GREEN : (strength_level == "2")? TFT_YELLOW : TFT_RED;
    const char *level = (strength_level == "1")? "L" : (strength_level == "2")? "M" : "H";

    M5.Lcd.drawString("LEVEL: ", 0, title_h * 2, FONT);
    M5.Lcd.fillRect( width/2, title_h * 2 - padding_y, title_h * 2, title_h, color);
    M5.Lcd.drawString(level, width/2 + padding_x*2, title_h * 2, FONT);
}