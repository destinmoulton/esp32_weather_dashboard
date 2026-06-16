//
// Created by destin on 5/28/26.
//

#pragma once

#include <WiFi.h>
#include <WiFiUdp.h>

class WifiInterface
{
public:
    WifiInterface();
    bool connect();

private:
    const char* m_wifi_ssid;
    const char* m_wifi_password;
    const IPAddress m_config_IP;
    const IPAddress m_config_gateway;
    const IPAddress m_config_subnet;
    const IPAddress m_config_primary_DNS;
    const IPAddress m_config_secondary_DNS;
};
