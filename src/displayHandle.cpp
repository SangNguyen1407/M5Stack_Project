#include <Arduino.h>
#include <M5Core2.h>
#include "displayHandle.h"

#define DISPLAY_MAX_SIZE 7
#define FONT             4
#define LINE_MAX_CHAR    10

int title_h   = 30;
int padding_x = 10;
int padding_y = 5;
int circle    = 10;

// List menu
const char *LIST_MENU[LIST_MENU_MAX] = {
    "BLUETOOTH",
    "CLOCK",
    "WIFI",
    "MENU",
    "TIME",
    "COUNT",
    "SLEEP TIME",
};

// the child items of Sleep time items
const char *SLEEP_MENU[LIST_MENU_SLEEP_MAX] = {
    "SLEEP",
    "AWAKE"
};

// create list items to show display
void DISPLAY_SHOW::addListMenu(const char **list_menu, int list_size){
    // list is existed, remove all
    if (list.size()> 0){
        list.clear();
    }

    // add list items into list
    for(int pos = 0; pos < list_size; pos++){
        list.push_back(list_menu[pos]);
    }
}

// show title in the top of display
void DISPLAY_SHOW::showTitleOnTop(String title){
    // GREEN background
    M5.Lcd.fillRect(0, 0, width, title_h, TFT_DARKGREEN);
    // title in the middle
    M5.Lcd.drawCentreString(title, width/2, padding_y, FONT);
}

// show title in the top of display with position of list
void DISPLAY_SHOW::showTitleOnTop(int pos){
    // get title name in list
    String title = list.at(pos);
    // show title in the top of display
    showTitleOnTop(title);
}

// // 
// void DISPLAY_SHOW::showTitleOnMiddle(String title){
//     int color = (title == "1")? TFT_GREEN : (title == "2")? TFT_YELLOW : TFT_RED;

//     M5.Lcd.fillRect(0, title_h + height, width, height, color);
// }

// void printTime(tm time){
//   char time_char[100];
//   memset(time_char, '/0', 100);

//   M5.Lcd.fillRect(0, 60, 320, 60, TFT_BLACK);
//   M5.Lcd.drawCentreString(time_char, 0, 100, 4);
// }

// press buttonA to choose items, this item is OFF
void DISPLAY_SHOW::showLineOff(String item, int pos){
    // change to Black background
    M5.Lcd.fillRoundRect(0, title_h*pos, width, title_h, circle, TFT_BLACK);
    // white round
    M5.Lcd.drawRoundRect(0, title_h*pos, width, title_h, circle, TFT_WHITE);
    // show item name
    M5.Lcd.drawCentreString(item, width/2, title_h*pos + padding_y, FONT);
}

// press buttonA to choose items, this item is ON
void DISPLAY_SHOW::showLineOn(String item, int pos){
    // change to GREEN background
    M5.Lcd.fillRoundRect(0, title_h*pos, width, title_h, circle, TFT_DARKCYAN);
    // white round
    M5.Lcd.drawRoundRect(0, title_h*pos, width, title_h, circle, TFT_WHITE);
    // show item name
    M5.Lcd.drawCentreString(item, width/2, title_h*pos + padding_y, FONT);
}

/**
 * show list in main display
 */
void DISPLAY_SHOW::showListMenu(int start) {

    M5.Lcd.fillRect(0, title_h, width, height, TFT_BLACK);
    int list_max = (start + DISPLAY_MAX_SIZE > list.size())? 
                list.size() : start + DISPLAY_MAX_SIZE;

    for (int pos = start; pos< list_max; pos++){
        int diplay_pos = pos % DISPLAY_MAX_SIZE;
        M5.Lcd.drawRoundRect(0, title_h*(diplay_pos + 1), width, title_h, circle, TFT_WHITE);
        M5.Lcd.drawCentreString(list.at(pos), width/2, title_h*(diplay_pos + 1) + padding_y, FONT);
    }   
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