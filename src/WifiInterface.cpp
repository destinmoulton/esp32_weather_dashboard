//
// Created by destin on 5/28/26.
//

#include <WiFi.h>
#include <WiFiUdp.h>
#include "WifiInterface.h"
#include "time.h"

#define SSID "Bigger Brother"
#define PASSWORD "TheOutpost575"
#define IP 192,168,100,130
#define GATEWAY 192,168,100,1
#define SUBNET 255,255,255,0
#define PRIMARY_DNS 1,1,1,1
#define SECONDARY_DNS 8,8,8,8
#define NTP_SERVER "pool.ntp.org"
#define NTP_GMT_OFFSET -21600 // GMT-7 (IMPORTANT: negative for -7)
#define TIMEZONE_POSIX "MST7MDT,M3.2.0/2:00:00,M11.1.0/2:00:00"

WifiInterface::WifiInterface()
    : m_wifi_ssid(SSID),
      m_wifi_password(PASSWORD),
      m_config_IP(IP),
      m_config_gateway(GATEWAY),
      m_config_subnet(SUBNET),
      m_config_primary_DNS(PRIMARY_DNS),
      m_config_secondary_DNS(SECONDARY_DNS)
{
}

bool WifiInterface::connect()
{
    WiFi.begin(SSID, PASSWORD);

    Serial.println("\nConfiguring static ip...");
    // Configures static IP address
    if (!WiFi.config(m_config_IP, m_config_gateway, m_config_subnet, m_config_primary_DNS, m_config_secondary_DNS))
    {
        Serial.println("Static IP Failed to configure...");
        return false;
    }

    Serial.println("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }

    // Synchronize the time
    //m_udp.begin(123);
    configTzTime(TIMEZONE_POSIX, NTP_SERVER);
    // 3. Wait for time to sync
    tm timeinfo;
    if (getLocalTime(&timeinfo, 10000)) { // 10-second timeout
        Serial.println("Time successfully synced!");
    } else {
        Serial.println("Time sync failed.");
    }
    // Format and print the time
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

    Serial.print("Connected to WiFi! Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    return true;
}
