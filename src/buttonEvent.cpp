#include "../lib/buttonEvent.h"
#include "../lib/network.h"
#include "../lib/display.h"
#include "../lib/fileHandle.h"

/* Scan button
 */
void BtnAEvent(Event& e){
  // BLEStart();
  // BLEScanPeripheralList();
  readFile();
}

// /* Next button
// */
// void BtnBEvent(Event& e){
//   if (device_count++ >= pBLEAdvertiesdDeviceList.size()){
//     device_count = 0;
//   }
//   DisplayInfo(device_count);
// }

void BtnBEvent(Event& e){
  DISPLAY_MODE mode = (displayMode == DISPLAY_SCAN)? DISPLAY_CONNECT : 
  (displayMode == DISPLAY_CONNECT)? DISPLAY_MAIN : DISPLAY_SCAN;
  
  displayMode = mode;
  ShowDisplay(mode);
}

/* Connect button
 */
void BtnCEvent(Event& e){
  // if (ConnectToServer()){
  //     M5.Lcd.drawString("Connect BLE OK.", 0, 150);
  // }
  writeFile("1,2,3,4\n");
}