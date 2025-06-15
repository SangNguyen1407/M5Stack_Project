#ifndef TIME_EVENT_H
#define TIME_EVENT_H

#include <WiFi.h>
#include <M5Core2.h>
#include <WiFiClientSecure.h>


class WIFI_NETWORK{
    private:
        const char* ssid = "00CAE0892657-2G";// Wi-FiのSSID
        const char* password = "segmgx6nxz7c98";// Wi-Fiのパスワード

        const char* host = "script.google.com";
        String url = "https://script.google.com/macros/s/AKfycbzvH3nMD7we4A6SaylcxTOV6WDbDiaDXJYYRdLYkrZJ4t7oX9vzHp8sFG150SSLQ6T_sw/exec";
        String hostName;
        String dnsIP;
        String macAddress;

        WiFiClientSecure client;

    public:
        void connectWifi();
        
        void printLocalTime(tm timeinfo);
        void printLocalDay(tm timeinfo);
        
        tm getLocalTimeInfo();
        bool nextSecondTime(tm *time);
        String getHostName();
        String getDNSAddress();
        String postValues(String values_to_post);
};

#endif //TIME_EVENT_H