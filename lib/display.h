#ifndef DISPLAY_H
#define DISPLAY_H

#include <M5Core2.h>

typedef enum {
    DIS_SCAN,
    DIS_CONNECT,
    DIS_MAIN,
} DISPLAY_MODE;

typedef enum {
    OPT_1,
    OPT_2,
    OPT_3,
    OPT_MAX
} OPTS;

extern DISPLAY_MODE displayMode;
extern int BUTTON_WIDTH;
extern int BUTTON_HEIGHT;
extern const char *optDisplay[]; 

void DisplayInit();
// void DisplayScan();
void DisplayInfo(int info);
void ShowDisplay();

#endif //DISPLAY_H