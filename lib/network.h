#ifndef NETWORK_H
#define NETWORK_H

#include <Arduino.h>
#include <BLEClient.h>
#include <BLEDevice.h>
#include <BLESecurity.h>

#define SERVICE_UUID        ""
#define CHARACTERISTIC_UUID ""
#define CENTRAL_NAME        "C_TEST"
#define PERIPHERAL_NAME     "P_TEST"

extern std::vector<BLEAdvertisedDevice> pBLEAdvertiesdDeviceList;
extern int device_count; 

class ClientCallback : public BLEClientCallbacks {
  public:
    virtual void onConnect (BLEClient* pclient);
    virtual void onDisconnect (BLEClient* pclient);
};

class AdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  public:
    virtual void onResult (BLEAdvertisedDevice advertisedDevice);
};

class TestSecurity : public BLESecurityCallbacks {
  uint32_t onPassKeyRequest() {
      Serial.println("PassKeyRequest");
      return 123456; // Return your desired PIN
  }
  void onPassKeyNotify(uint32_t pass_key) {
      Serial.println("PassKeyNotify");
  }
  bool onConfirmPIN(uint32_t pass_key) {
      Serial.printf("Confirming PIN: %d\n", pass_key);
      return true; // Return true if the PIN is correct
  }
  bool onSecurityRequest() {
      return true; // Allow pairing requests
  }
  void onAuthenticationComplete(esp_ble_auth_cmpl_t auth_cmpl) {
      if (auth_cmpl.success) {
          Serial.println("Authentication successful!");
      } else {
          Serial.println("Authentication failed.");
      }
  }
};

void BLEStart();
void BLEEnd();

void BLEAdvertise();
bool ConnectToServer();
void BLEScanPeripheralList();


#endif