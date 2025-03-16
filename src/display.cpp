#include <Arduino.h>
#include <M5Core2.h>

#include "../lib/buttonEvent.h"
#include "../lib/display.h"
#include "../lib/network.h"

int POSITON_X = 20;
int POSITON_Y = 20;
int POSITION_HEIGHT = 60;
int POSITION_WIDTH = M5.Lcd.width();

const char *SCAN_OPT[] = {"WRITE", "READ", "OK"};
const char *CONNECT_OPT[] = {"CONNECT_1", "CONNECT_2", "CONNECT_3"};
const char *MAIN_OPT[] = {"MAIN_1", "MAIN_2", "MAIN_3"};

const char *optDisplay[OPT_MAX-1]; 
DISPLAY_MODE displayMode = DISPLAY_SCAN;
OPTS opt = OPT_1;

void DisplayInit(){

}

void DisplayInfo(int pos){
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE, BLACK);
    char str[128];

    if (!pBLEAdvertiesdDeviceList.empty()){
        sprintf(str,"DEVICE_COUNT: %d/%d", pos, pBLEAdvertiesdDeviceList.size());
        M5.Lcd.drawString(str, 0 , 30, 2);

        memset(str, 0, 128);
        sprintf(str,"DEVICE_NAME: %s", pBLEAdvertiesdDeviceList.at(pos).getAddress().toString());
        M5.Lcd.drawString(str, 0, 90, 2);
    }
    else{
        M5.Lcd.drawString("NO LIST", 0, 90, 2);
    }

}

void ShowDisplay(DISPLAY_MODE mode){
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.fillRect(0, 0, POSITION_WIDTH + 100, 20, TFT_DARKGREY);
    switch (mode)
    {
        case DISPLAY_SCAN:
            // show mode SCAN
            M5.Lcd.setTextDatum(MC_DATUM);
            M5.Lcd.drawString("SCANNING", 120, 6, 1);
            for(int opt=0; opt < OPT_MAX; opt++) {
                optDisplay[opt] = SCAN_OPT[opt];
            }
            break;
        case DISPLAY_CONNECT:
            // show mode CONNECT
            M5.Lcd.drawString("CONNECT", 120, 6, 1);
            for(int opt=0; opt < OPT_MAX; opt++) {
                optDisplay[opt] = CONNECT_OPT[opt];
            }
            break;
        case DISPLAY_MAIN:
            // show mode MAIN
            M5.Lcd.drawString("MAIN", 120, 6, 1);
            // OPT
            for(int opt=0; opt < OPT_MAX; opt++) {
                optDisplay[opt] = MAIN_OPT[opt];
            }
            break;
        default:
            break;
    }

    M5.Lcd.setTextSize(2);
    M5.Lcd.fillRect(0, 20, POSITION_WIDTH, POSITION_HEIGHT*3, BLACK);
    M5.Lcd.drawString(optDisplay[OPT_1], 100, 40, 2);
    M5.Lcd.drawString(optDisplay[OPT_2], 100, POSITION_HEIGHT + 40, 2);
    M5.Lcd.drawString(optDisplay[OPT_3], 100, POSITION_HEIGHT*2 + 40, 2);

    opt = OPT_1;
    ShowOptChoose();
}

void ShowOptChoose(){
    M5.Lcd.fillRect(0, 20, POSITION_WIDTH, POSITION_HEIGHT*3, BLACK);

    switch (opt)
    {
        case OPT_1:
            opt = OPT_2;
            M5.Lcd.fillRect(0, 20, POSITION_WIDTH, POSITION_HEIGHT, TFT_BLUE);
            break;
        case OPT_2:
            opt = OPT_3;
            M5.Lcd.fillRect(0, POSITION_HEIGHT + 20, POSITION_WIDTH, POSITION_HEIGHT, TFT_BLUE);
            break;
        case OPT_3:
            opt = OPT_1;
            M5.Lcd.fillRect(0, POSITION_HEIGHT*2 + 20, POSITION_WIDTH, POSITION_HEIGHT, TFT_BLUE);
            break;
    }

    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString(optDisplay[OPT_1], 100, 40, 2);
    M5.Lcd.drawString(optDisplay[OPT_2], 100, POSITION_HEIGHT + 40, 2);
    M5.Lcd.drawString(optDisplay[OPT_3], 100, POSITION_HEIGHT*2 + 40, 2);
}