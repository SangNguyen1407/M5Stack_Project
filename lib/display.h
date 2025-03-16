#ifndef DISPLAY_H
#define DISPLAY_H

#include <M5Core2.h>

typedef enum {
    DISPLAY_SCAN,
    DISPLAY_CONNECT,
    DISPLAY_MAIN,
} DISPLAY_MODE;

typedef enum {
    OPT_1,
    OPT_2,
    OPT_3,
    OPT_MAX
} OPTS;

extern DISPLAY_MODE displayMode;
extern OPTS opt;

extern int BUTTON_WIDTH;
extern int BUTTON_HEIGHT;
extern const char *optDisplay[]; 

void DisplayInit();
void DisplayInfo(int info);
void ShowDisplay(DISPLAY_MODE mode);
void ShowOptChoose();

#endif //DISPLAY_H