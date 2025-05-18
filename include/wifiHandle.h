#ifndef TIME_EVENT_H
#define TIME_EVENT_H

#include <WiFi.h>
#include <M5Core2.h>


class WIFI_NETWORK{
    private:
        const char* ssid       = "00CAE0892657-2G";// Wi-FiのSSID
        const char* password   = "segmgx6nxz7c98";// Wi-Fiのパスワード
        String hostName;
        String dnsIP;
        String macAddress;
;
    public:
        void setupWifi();
        
        void printLocalTime();
        void printLocalDay();
        void printInfo();
        
        String getHostName();
        String getDNSAddress();
};

#endif //TIME_EVENT_H