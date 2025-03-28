#include "../lib/network.h"

// std::vector<BLEAdvertisedDevice> pBLEAdvertiesdDeviceList;
// int device_count = 0;

void ClientCallback::onConnect(BLEClient *pclient){
  BLESecurity *pSecurity = new BLESecurity();
  pSecurity->setAuthenticationMode(ESP_LE_AUTH_REQ_SC_BOND);
  pSecurity->setCapability(ESP_IO_CAP_IO);
}

void ClientCallback::onDisconnect(BLEClient *pclient){

}

void AdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice) {
  if (advertisedDevice.haveName()){
    pBLEAdvertiesdDeviceList.push_back(advertisedDevice);
  }
}

void BLEControl::BLEStart(){
  BLEDevice::init(CENTRAL_NAME);
  BLEServer* pServer = BLEDevice::createServer();
  BLEService* pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic* pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_BROADCAST | BLECharacteristic::PROPERTY_READ  |
        BLECharacteristic::PROPERTY_NOTIFY    | BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_INDICATE
      );

  pCharacteristic->setValue("Hello World!");
  pService->start();
}

void BLEControl::BLEEnd(){
  BLEDevice::deinit();
}

void BLEControl::BLEScanPeripheralList(){
  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(advertiseDeviceCB);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  pBLEScan->setActiveScan(true);

  pBLEScan->start(5, false);
}

bool BLEControl::ConnectToServer(){
  BLEAdvertisedDevice pPeriphrealDevice = advertiseDeviceCB->pBLEAdvertiesdDeviceList.at(0);
  BLEClient *pClient = BLEDevice::createClient();

  pClient->connect(&pPeriphrealDevice);
  pClient->setClientCallbacks(new ClientCallback());

  BLERemoteService *pRemoteService = pClient->getService(SERVICE_UUID);
  if (pRemoteService == nullptr) {
    return false;
  }

  BLERemoteCharacteristic *pRemoteCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
  if (pRemoteCharacteristic == nullptr) {
    const char *deviceName = pRemoteCharacteristic->readValue().c_str();
    M5.Lcd.setTextColor(WHITE, BLUE);
    if (deviceName != nullptr){
      M5.Lcd.drawString(deviceName, 50, 150);
    }
    else{
      M5.Lcd.drawString("NO NAME", 50, 150);
    }
  }

  return true;
}