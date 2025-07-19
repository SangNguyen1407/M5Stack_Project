#ifndef TIME_EVENT_H
#define TIME_EVENT_H

#include <WiFi.h>
#include <M5Core2.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>


class WIFI_NETWORK{
    private:
        const char* ssid = "00CAE0892657-2G";// Wi-FiのSSID
        const char* password = "segmgx6nxz7c98";// Wi-Fiのパスワード

        const char* host = "script.google.com";
        const int httpsPort = 443;
        String url = "https://script.google.com/macros/s/AKfycbxW96FWH7dM5Hi7IA95j4kRTeIRce07axB6jhCjyoCZEK1lk7qhJlK8zeYKj4RLfNcv_w/exec";
        String hostName;
        String dnsIP;
        String macAddress;

        WiFiClientSecure client;
        // HTTP通信開始
        HTTPClient http;

    public:
        void connectWifi();
        
        void printLocalTime(tm timeinfo);
        void printLocalDay(tm timeinfo);
        
        tm getLocalTimeInfo();
        bool nextSecondTime(tm *time);
        String getHostName();
        String getDNSAddress();
        String httpPOSTRequest(String values_to_post);
        String httpGETRequest(String values_to_post);
};

#endif //TIME_EVENT_H