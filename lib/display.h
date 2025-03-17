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
    OPT_MAX
} OPTS;

typedef enum {
    LEVEL_WEAK,
    LEVEL_MID,
    LEVEL_HIGHT,
    LEVEL_MAX
} LEVEL;

extern DISPLAY_MODE displayMode;
extern OPTS opt;
extern LEVEL optStrength;

extern int POSITON_X;
extern int POSITON_Y;
extern int POSITION_HEIGHT;
extern int POSITION_WIDTH;

extern int BUTTON_WIDTH;
extern int BUTTON_HEIGHT;
extern const char *optDisplay[]; 

void DisplayInit();
void DisplayInfo(int info);
void ShowDisplay(DISPLAY_MODE mode);
void handleOpt(DISPLAY_MODE mode);
void ShowOptChoose();
void nextDevice();

#endif //DISPLAY_H