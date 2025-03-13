#include "../lib/buttonEvent.h"
#include "../lib/network.h"
#include "../lib/display.h"

/* Scan button
 */
void BtnAEvent(Event& e){
  BLEStart();
  BLEScanPeripheralList();
}

/* Next button
*/
void BtnBEvent(Event& e){
  if (device_count++ >= pBLEAdvertiesdDeviceList.size()){
    device_count = 0;
  }
  DisplayInfo(device_count);
}

/* Connect button
 */
void BtnCEvent(Event& e){
  if (ConnectToServer()){
      M5.Lcd.drawString("Connect BLE OK.", 0, 150);
  }
}