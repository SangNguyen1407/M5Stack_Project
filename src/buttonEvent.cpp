#include "../lib/buttonEvent.h"
#include "../lib/network.h"
#include "../lib/display.h"
#include "../lib/fileHandle.h"

/* Scan button
 */
void BtnAEvent(Event& e){
  
  if (displayMode == DISPLAY_MAIN && opt == OPT_1){
  }
  else if (displayMode == DISPLAY_MAIN && opt == OPT_2){
    handleOpt(displayMode);
  }
  else if (displayMode == DISPLAY_CONNECT && opt == OPT_1){
    nextDevice();
  }
  else if (displayMode == DISPLAY_CONNECT && opt == OPT_2){
    displayMode = DISPLAY_MAIN;
    ShowDisplay(DISPLAY_MAIN);
  }
}

void BtnBEvent(Event& e){
  // DISPLAY_MODE mode = (displayMode == DISPLAY_SCAN)? DISPLAY_CONNECT : 
  // (displayMode == DISPLAY_CONNECT)? DISPLAY_MAIN : DISPLAY_SCAN;
  
  // displayMode = mode;
  // ShowDisplay(mode);
  ShowOptChoose();
}

/* Connect button
 */
void BtnCEvent(Event& e){
  writeFile("1,2,3,4\n");
}