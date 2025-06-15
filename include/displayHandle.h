#ifndef DISPLAY_HANDLE_H
#define DISPLAY_HANDLE_H

#include <M5Core2.h>

extern int width;
extern int height;

#define LIST_MENU_MAX    8

typedef enum {
    DISPLAY_BLUETOOTH = 0,
    DISPLAY_CLOCK,
    DISPLAY_WIFI,
    DISPLAY_MENU,
    DISPLAY_TIME,
    DISPLAY_COUNT,
    DISPLAY_SLEEP_TIME,
} DISPLAY_MODE;

typedef enum {
    LEVEL_WEAK,
    LEVEL_MID,
    LEVEL_HIGHT
} LEVEL;

extern const char *LIST_MENU[LIST_MENU_MAX];
// extern const char *LIST_BLE[LIST_MENU_MAX];
// extern const char *LIST_CLOCK[LIST_MENU_MAX];

class DISPLAY_SHOW{
    private: 
        std::vector<String> list;
        DISPLAY_MODE mode;

    public:
        DISPLAY_MODE displayMode;
        String strength_level;
        String device_name;

        DISPLAY_SHOW() {
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

        void printTime(tm time);


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
        void addListMenu(const char **list_menu, int list_size); 
};


#endif //DISPLAY_HANDLE_H