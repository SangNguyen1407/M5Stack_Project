#ifndef DISPLAY_HANDLE_H
#define DISPLAY_HANDLE_H

#include <M5Core2.h>

extern int width;
extern int height;

#define LIST_MENU_MAX    4

typedef enum {
    DISPLAY_MENU = 0,
    DISPLAY_BLUETOOTH,
    DISPLAY_CLOCK,
    DISPLAY_WIFI,
} DISPLAY_MODE;

typedef enum {
    LEVEL_WEAK,
    LEVEL_MID,
    LEVEL_HIGHT
} LEVEL;

// const char *LIST_MENU[LIST_MENU_MAX] = {
//     "MENU",
//     "Bluetooth",
//     "CLOCK",
//     "WIFI"
// };

class DISPLAY_SHOW{
    private: 
        std::vector<String> list;
        DISPLAY_MODE mode;

    public:
        DISPLAY_MODE displayMode;
        String strength_level;
        String device_name;

        DISPLAY_SHOW() {
            const char *LIST_MENU[LIST_MENU_MAX] = {
                            "MENU",
                            "BLUETOOTH",
                            "CLOCK",
                            "WIFI"
                        };
            for(int pos = 0; pos < LIST_MENU_MAX; pos++){
                list.push_back(LIST_MENU[pos]);
            }
        };

        DISPLAY_SHOW(DISPLAY_MODE mode, String level, String name) {
            displayMode = mode;
            strength_level = level;
            device_name = name;
        };
        ~DISPLAY_SHOW() {};

        // void ShowDisplay();
        // void showTitle(DISPLAY_MODE mode);
        void showTitleOnTop(String title);
        void showTitleOnTop(int pos);
        void showTitleOnMiddle(String title);


        // void displayScanDevice(std::vector<String> device_list);
        // void showAdvertisedDeviceList(std::vector<String> device_list, int opt);
        
        void showLineOff(String item, int pos);
        void showLineOn(String item, int pos);
        
        void showAssistOn();
        void showAssistOff();

        void resetDisplay();

        void updateStrengthLevel();
        void showStrengthLevel();

        // void showListMenu(std::vector<String> list);
        void showListMenu(int start_pos);
        void nextItem(int opt);
        void chooseItem(int opt);

        int getListMenuSize();
        String getItemName(int pos);

        void setModeDisplay(DISPLAY_MODE mode);
        DISPLAY_MODE getModeDisplay();
};


#endif //DISPLAY_HANDLE_H