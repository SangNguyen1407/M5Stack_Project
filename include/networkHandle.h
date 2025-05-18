#ifndef NETWORK_HANDLE_H
#define NETWORK_HANDLE_H

#include <Arduino.h>
#include <M5Core2.h>

#include <BLEClient.h>
#include <BLEDevice.h>
#include <BLESecurity.h>
#include <BLE2902.h>

#define SERVICE_UUID        "1234"
#define CHARACTERISTIC_UUID "1234"
#define CENTRAL_NAME        "C_TEST"
#define PERIPHERAL_NAME     "P_TEST"

// extern std::vector<BLEAdvertisedDevice> pBLEAdvertiesdDeviceList;
// extern int device_count; 
extern void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);
class ClientCallback : public BLEClientCallbacks {
  public:
    virtual void onConnect (BLEClient* pclient);
    virtual void onDisconnect (BLEClient* pclient);
};

class AdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  public:
    std::vector<BLEAdvertisedDevice> pBLEAdvertiesdDeviceList;
    virtual void onResult (BLEAdvertisedDevice advertisedDevice);
};

class CharacteristicCallback : public BLECharacteristicCallbacks{
  public:
    QueueHandle_t TxQueue;
    virtual void onRead(BLECharacteristic *pCharacteristic);
    virtual void onWrite(BLECharacteristic *pCharacteristic);
};

class BLEControl{
    public:
        AdvertisedDeviceCallbacks *advertiseDeviceCB;
        BLEScan* pBLEScan;
        BLEClient *pClient;
        BLEServer* pServer;
        BLEService* pService;
        BLECharacteristic* pCharacteristic;

        BLERemoteService *pRemoteService;
        BLERemoteCharacteristic *pRemoteCharacteristic;

        QueueHandle_t TxQueue;
        QueueHandle_t RxQueue;

        BLEControl(){
            advertiseDeviceCB = new AdvertisedDeviceCallbacks();

            TxQueue = xQueueCreate(10, sizeof(int));
            RxQueue = xQueueCreate(10, sizeof(int));
          
        };
        ~BLEControl(){
            delete(advertiseDeviceCB);
        };

        void BLEEnd();
        void BLEStart();
        bool ConnectToServer();
        void BLEScanPeripheralList();

        bool sendCommand();
};


#endif //NETWORK_HANDLE_H