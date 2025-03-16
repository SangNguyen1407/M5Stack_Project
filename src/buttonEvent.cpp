#include "../lib/buttonEvent.h"
#include "../lib/network.h"
#include "../lib/display.h"
#include "../lib/fileHandle.h"

/* Scan button
 */
void BtnAEvent(Event& e){
  // BLEStart();
  // BLEScanPeripheralList();
  DISPLAY_MODE mode = (displayMode == DISPLAY_SCAN)? DISPLAY_CONNECT : 
  (displayMode == DISPLAY_CONNECT)? DISPLAY_MAIN : DISPLAY_SCAN;
  
  displayMode = mode;
  ShowDisplay(mode);
}

void BtnBEvent(Event& e){
  //readFile();
  ShowOptChoose();
}

/* Connect button
 */
void BtnCEvent(Event& e){
  writeFile("1,2,3,4\n");
}