#include <Arduino.h>
#include <M5Core2.h>

#include "../lib/buttonEvent.h"
#include "../lib/display.h"
#include "../lib/network.h"
#include "../lib/fileHandle.h"

int POSITON_X = 20;
int POSITON_Y = 20;
int POSITION_HEIGHT = 60;
int POSITION_WIDTH = M5.Lcd.width();

const char *CONNECT_OPT[] = {"NEXT", "OK"};
const char *MAIN_OPT[] = {"PUSH", "STRENGTH"};

const char *optDisplay[OPT_MAX-1]; 
DISPLAY_MODE displayMode = DISPLAY_SCAN;
OPTS opt = OPT_1;
LEVEL optStrength = LEVEL_WEAK;

void ShowDisplay(DISPLAY_MODE mode){
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.fillRect(0, 0, POSITION_WIDTH + 100, 20, TFT_DARKGREY);

    opt = OPT_1;
    switch (mode)
    {
        case DISPLAY_SCAN:
            M5.Lcd.setTextSize(2);
            M5.Lcd.drawString("SCANNING", 40, POSITION_HEIGHT + 40, 1);
            break;

        case DISPLAY_CONNECT:
            M5.Lcd.drawString("CONNECT", 120, 6, 1);
            device_count = 0;
            char str[128];
            sprintf(str, "%s %d/%d", pBLEAdvertiesdDeviceList.at(0).getName().c_str(), 
                                        device_count + 1, 
                                        pBLEAdvertiesdDeviceList.size());
            optDisplay[OPT_1] = str;
            optDisplay[OPT_2] = CONNECT_OPT[OPT_2];
            ShowOptChoose();
            break;

        case DISPLAY_MAIN:
            M5.Lcd.drawString("MAIN", 120, 6, 1);
            for(int opt=0; opt < OPT_MAX; opt++) {
                optDisplay[opt] = MAIN_OPT[opt];
            }
            ShowOptChoose();
            break;
        default:
            break;
    }
}

void ShowOptChoose(){
    M5.Lcd.fillRect(0, 20, POSITION_WIDTH, POSITION_HEIGHT*3, BLACK);
    char str[128];
    switch (opt)
    {
        case OPT_1:
            opt = OPT_2;
            M5.Lcd.fillRect(0, POSITION_HEIGHT + 20, POSITION_WIDTH, POSITION_HEIGHT, TFT_BLUE);
            break;
        case OPT_2:
            opt = OPT_1;
            M5.Lcd.fillRect(0, 20, POSITION_WIDTH, POSITION_HEIGHT, TFT_BLUE);
            if (displayMode == DISPLAY_MAIN){
                int level = (optStrength == LEVEL_WEAK)? 1 : (optStrength == LEVEL_MID)? 2 : 3;
                memset(str,'\0', 128);
                sprintf(str, "%d,\n", level);
                writeFile(str);
            }
            break;
        default:
            opt = OPT_1;
            M5.Lcd.fillRect(0, 20, POSITION_WIDTH, POSITION_HEIGHT, TFT_BLUE);
            break;
    }

    if (displayMode == DISPLAY_MAIN){
        int color = (optStrength == LEVEL_WEAK)? TFT_GREEN : (optStrength == LEVEL_MID)? TFT_YELLOW : TFT_RED;
        M5.Lcd.fillRect(0, POSITION_HEIGHT + 20, POSITION_WIDTH, POSITION_HEIGHT, color);
    }
    if (displayMode == DISPLAY_CONNECT){
        memset(str,'\0', 128);
        sprintf(str, "%s %d/%d", pBLEAdvertiesdDeviceList.at(device_count).getName().c_str(), 
        device_count + 1, 
        pBLEAdvertiesdDeviceList.size());
        optDisplay[OPT_1] = str;
    }
    
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.drawString(optDisplay[OPT_1], 100, 40, 2);
    M5.Lcd.drawString(optDisplay[OPT_2], 100, POSITION_HEIGHT + 40, 2);
}

void handleOpt(DISPLAY_MODE mode){
    optStrength = (optStrength == LEVEL_WEAK)? LEVEL_MID : (optStrength == LEVEL_MID)? LEVEL_HIGHT : LEVEL_WEAK;
    int color = (optStrength == LEVEL_WEAK)? TFT_GREEN : (optStrength == LEVEL_MID)? TFT_YELLOW : TFT_RED;
    M5.Lcd.fillRect(0, POSITION_HEIGHT + 20, POSITION_WIDTH, POSITION_HEIGHT, color);
    M5.Lcd.drawString(optDisplay[OPT_2], 100, POSITION_HEIGHT + 40, 2);
}

void nextDevice(){
    M5.Lcd.fillRect(0, 20, POSITION_WIDTH, POSITION_HEIGHT, BLUE);
    device_count++;
    if (device_count >= pBLEAdvertiesdDeviceList.size()){
        device_count = 0;
    }
    char str[128];
    sprintf(str, "%s %d/%d", pBLEAdvertiesdDeviceList.at(device_count).getName().c_str(), 
                                device_count + 1, 
                                pBLEAdvertiesdDeviceList.size());
    optDisplay[OPT_1] = str;
    M5.Lcd.drawString(optDisplay[OPT_1], 100, 40, 2);
}