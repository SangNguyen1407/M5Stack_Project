#ifndef TIME_EVENT_H
#define TIME_EVENT_H

#include <WiFi.h>
#include <M5Core2.h>


class WIFI_NETWORK{
    private:
        const char* ssid       = "00CAE0892657-2G";// Wi-FiのSSID
        const char* password   = "segmgx6nxz7c98";// Wi-Fiのパスワード

    public:
        void printLocalTime();
        void setupWifi();
};

#endif //TIME_EVENT_H