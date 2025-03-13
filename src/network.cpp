#include "../lib/network.h"
#include <M5Core2.h>


std::vector<BLEAdvertisedDevice> pBLEAdvertiesdDeviceList;
int device_count = 0;
 
void ClientCallback::onConnect(BLEClient *pclient){
  BLESecurity *pSecurity = new BLESecurity();
  pSecurity->setAuthenticationMode(ESP_LE_AUTH_REQ_SC_BOND);
  pSecurity->setCapability(ESP_IO_CAP_IO);
  BLEDevice::setSecurityCallbacks(new TestSecurity());

}

void ClientCallback::onDisconnect(BLEClient *pclient){
}

void AdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice) {
  if (advertisedDevice.haveName()){
    pBLEAdvertiesdDeviceList.push_back(advertisedDevice);
  }
}

void BLEStart(){
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

void BLEEnd(){
  BLEDevice::deinit();
}

void BLEAdvertise(){
  // BLEAdvertising* pAdvertising = pServer->getAdvertising();
  // pAdvertising->addServiceUUID(pService->getUUID());
  // pAdvertising->start();
}

void BLEScanPeripheralList(){
  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  pBLEScan->setActiveScan(true);

  pBLEScan->start(5, false);
}

bool ConnectToServer(){
  BLEAdvertisedDevice pPeriphrealDevice = pBLEAdvertiesdDeviceList.at(device_count);
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