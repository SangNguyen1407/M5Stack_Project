#ifndef DISPLAY_H
#define DISPLAY_H

#include <M5Core2.h>

typedef enum {
    DISPLAY_SCAN,
    DISPLAY_CONNECT,
    DISPLAY_MAIN,
    DISPLAY_STRENGTH_SETUP,
} DISPLAY_MODE;

typedef enum {
    LEVEL_WEAK,
    LEVEL_MID,
    LEVEL_HIGHT
} LEVEL;

class DISPLAY_SHOW{
    public:
        DISPLAY_MODE displayMode;
        String strength_level;
        String device_name;
        

        DISPLAY_SHOW() {
            displayMode = DISPLAY_SCAN;
            strength_level = LEVEL_WEAK;
            device_name = "";
        };
        DISPLAY_SHOW(DISPLAY_MODE mode, String level, String name) {
            displayMode = mode;
            strength_level = level;
            device_name = name;
        };
        ~DISPLAY_SHOW() {};

        void ShowDisplay();
        void ShowDisplay(DISPLAY_MODE mode);
        void showTitle1(String name);
        void showTitle2(String name);
        void displayScanDevice(std::vector<BLEAdvertisedDevice> pBLEAdvertiesdDeviceList);
        void chooseDevice(std::vector<BLEAdvertisedDevice> pBLEAdvertiesdDeviceList, int opt);
        void showAdvertisedDeviceList(std::vector<BLEAdvertisedDevice> adverties_device_list, int opt);


        void displayScanDevice(std::vector<String> device_list);
        void chooseDevice(std::vector<String> device_list, int opt);
        void showAdvertisedDeviceList(std::vector<String> device_list, int opt);
        
        void showLineOff(String device_name, int pos);
        void showLineOn(String device_name, int pos);
        
        void showAssistOn();
        void showAssistOff();

        void updateStrengthLevel();
        void showStrengthLevel();
};


#endif //DISPLAY_H