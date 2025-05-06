#include "../lib/networkHandle.h"

const char* ssid       = "00CAE0892657-5G";
const char* password   = "segmgx6nxz7c98";

const char* ntpServer = "ntp.nict.jp";
const long  gmtOffset_sec = 3600 * 9;
const int   daylightOffset_sec = 0;

// std::vector<BLEAdvertisedDevice> pBLEAdvertiesdDeviceList;
// int device_count = 0;

void ClientCallback::onConnect(BLEClient *pclient){
  BLESecurity *pSecurity = new BLESecurity();
  pSecurity->setAuthenticationMode(ESP_LE_AUTH_REQ_SC_BOND);
  pSecurity->setCapability(ESP_IO_CAP_IO);
}

void ClientCallback::onDisconnect(BLEClient *pclient){

}

void CharacteristicCallback::onWrite(BLECharacteristic *pCharacteristic) {
  std::string value = pCharacteristic->getValue();
  int rxData = atoi(value.c_str());

  if (xQueueSend(TxQueue, &rxData, portMAX_DELAY) == pdPASS) {
    Serial.printf("Data received via BLE: %d\n", rxData);
    M5.Lcd.printf("BLE Rx: %d\n", rxData);

  }
}

void CharacteristicCallback::onRead(BLECharacteristic *pCharacteristic) {
}


void AdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice) {
  if (advertisedDevice.haveName()){
    pBLEAdvertiesdDeviceList.push_back(advertisedDevice);
  }
}

void BLEControl::BLEStart(){
  BLEDevice::init(CENTRAL_NAME);
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_WRITE | 
        BLECharacteristic::PROPERTY_READ  |
        BLECharacteristic::PROPERTY_NOTIFY    
      );

  pCharacteristic->setCallbacks(new CharacteristicCallback());

  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();
}

void BLEControl::BLEEnd(){
  BLEDevice::deinit();
}

void BLEControl::BLEScanPeripheralList(){
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(advertiseDeviceCB);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  pBLEScan->setActiveScan(true);

  pBLEScan->start(5, false);
}

// static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
//   Serial.print("Notification received: ");
//   uint8_t response = pData[0];
//   char test[128];
//   if (response == 0x23) { //OK
//     M5.Lcd.drawString("2345", 50, 180);
//   } else {
//     M5.Lcd.drawString("0987", 50, 180);
//   }
// }

bool BLEControl::ConnectToServer(){
  BLEAdvertisedDevice pPeriphrealDevice = advertiseDeviceCB->pBLEAdvertiesdDeviceList.at(0);
  pClient = BLEDevice::createClient();

  pClient->connect(&pPeriphrealDevice);
  pClient->setClientCallbacks(new ClientCallback());
  pRemoteService = pClient->getService(BLEUUID(SERVICE_UUID));
  if (pRemoteService == nullptr) {
    return false;
  }

  pRemoteCharacteristic = pRemoteService->getCharacteristic(BLEUUID(CHARACTERISTIC_UUID));
  if (pRemoteCharacteristic == nullptr) {
    return false;
  }

  // pRemoteCharacteristic->registerForNotify(notifyCallback);
  // Write to CCCD to enable notifications
  // uint8_t notifyEnable[] = {0x01, 0x00}; // 0x0001 enables notifications
  // pRemoteCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue(notifyEnable, 2);
  // pRemoteCharacteristic->writeValue(notifyEnable, 2);
  if(pRemoteCharacteristic->canNotify()){
    pRemoteCharacteristic->registerForNotify(notifyCallback);
  }
  // if(pRemoteCharacteristic->canNotify()){
  //   pRemoteCharacteristic->registerForNotify(notifyCallback);
  // }
  // const char *deviceName = pRemoteCharacteristic->readValue().c_str();
  // char test[128];
  // sprintf(test, "test %s",deviceName);
  // M5.Lcd.drawString("test", 50, 150);
  return true;
}

bool BLEControl::sendCommand(){
  // uint8_t *msg;
  // const char* txData;
  // sprintf(( char*)msg, "%s", "test");
  // pRemoteCharacteristic->writeValue({0x01, 0x00}, 2);
  // if (xQueueReceive(RxQueue,(void *)txData, 0) == pdTRUE) {
    // pCharacteristic->setValue(msg, sizeof(msg));
    // pCharacteristic->notify();
  // }
  if (pRemoteCharacteristic == nullptr) {
    return false;
  }
  if(pRemoteCharacteristic->canWrite()){
    pRemoteCharacteristic->writeValue({0x01, 0x00}, 0);
  }
  delay(1000);
}
