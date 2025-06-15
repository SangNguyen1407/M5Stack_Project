#ifndef TIME_EVENT_H
#define TIME_EVENT_H

#include <WiFi.h>
#include <M5Core2.h>
#include <WiFiClientSecure.h>


class WIFI_NETWORK{
    private:
        const char* ssid = "";// Wi-FiのSSID
        const char* password = "";// Wi-Fiのパスワード

        const char* host = "script.google.com";
        String url = "";
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