#include <Arduino.h>
#include <M5Core2.h>

#include "../lib/buttonEvent.h"
#include "../lib/display.h"
#include "../lib/network.h"

int BUTTON_HEIGHT = 60;
int BUTTON_WIDTH = M5.Lcd.width();

const char *CONNECT_OPT[] = {"CONNECT_1", "CONNECT_2", "CONNECT_3"};
const char *MAIN_OPT[] = {"MAIN_1", "MAIN_2", "MAIN_3"};

const char *optDisplay[OPT_MAX-1]; 
DISPLAY_MODE displayMode = DIS_SCAN;

void DisplayInit(){
    // M5.Lcd.clear();
    // M5.Lcd.setTextSize(2);

    // M5.Lcd.setTextColor(WHITE, BLUE);
    // M5.Lcd.drawString("SCAN", 0, 200, 2);

    // M5.Lcd.setTextColor(BLACK, GREEN);
    // M5.Lcd.drawString("NEXT", 150, 200, 2);

    // M5.Lcd.setTextColor(BLACK, YELLOW);
    // M5.Lcd.drawString("OK", 260, 200, 2);

    // M5.BtnA.addHandler(BtnAEvent, E_TOUCH);
    // M5.BtnB.addHandler(BtnBEvent, E_TOUCH);
    // M5.BtnC.addHandler(BtnCEvent, E_TOUCH);
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

// void DisplayScan(){
//     M5.Lcd.clear();
//     M5.Lcd.setTextSize(2);
//     M5.Lcd.setTextColor(WHITE);
//     M5.Lcd.drawString("Scanning...", 50, 150);
// }

void ShowDisplay(){
    switch (displayMode)
    {
    case DIS_SCAN:
        break;
    case DIS_CONNECT:
        for(int opt=0; opt < OPT_MAX; opt++) {
            optDisplay[opt] = CONNECT_OPT[opt];
        }
        // M5.Lcd.drawRect(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK);
        // M5.Lcd.drawRect(0, BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK);
        // M5.Lcd.drawRect(0, BUTTON_HEIGHT*2, BUTTON_WIDTH, BUTTON_HEIGHT, BLACK);
        break;
    case DIS_MAIN:
        for(int opt=0; opt < OPT_MAX; opt++) {
            optDisplay[opt] = MAIN_OPT[opt];
        }
        break;
    default:
        break;
    }

    M5.Lcd.drawCentreString(optDisplay[OPT_1], 20, 20, 2);
    M5.Lcd.drawCentreString(optDisplay[OPT_2], 20, BUTTON_HEIGHT + 20, 2);
    M5.Lcd.drawCentreString(optDisplay[OPT_3], 20, BUTTON_HEIGHT*2 + 20, 2);
}