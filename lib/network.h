#ifndef NETWORK_H
#define NETWORK_H

#include <Arduino.h>
#include <BLEClient.h>
#include <BLEDevice.h>
#include <BLESecurity.h>
#include <M5Core2.h>

#define SERVICE_UUID        ""
#define CHARACTERISTIC_UUID ""
#define CENTRAL_NAME        "C_TEST"
#define PERIPHERAL_NAME     "P_TEST"

// extern std::vector<BLEAdvertisedDevice> pBLEAdvertiesdDeviceList;
// extern int device_count; 

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

class BLEControl{
    public:
        AdvertisedDeviceCallbacks *advertiseDeviceCB;

        BLEControl(){
            advertiseDeviceCB = new AdvertisedDeviceCallbacks();
        };
        ~BLEControl(){
            delete(advertiseDeviceCB);
        };

        void BLEEnd();
        void BLEStart();
        bool ConnectToServer();
        void BLEScanPeripheralList();
};


#endif //NETWORK_H