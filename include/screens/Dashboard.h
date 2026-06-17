//
// Created by destin on 6/8/26.
//

#pragma once

#include "Screen.h"
#include "TFT_eSPI.h"

#define DASH_SLEEP_HOUR 21
#define DASH_SLEEP_MINUTE 0
#define DASH_WAKE_HOUR 7
#define DASH_WAKE_MINUTE 0

struct WeatherSensorData
{
    float temperature;
    float humidity;
};

struct SoilSensorData
{
    u_int16_t sensor_a;
    u_int16_t sensor_b;
};

class Dashboard : public Screen
{
public:
    explicit Dashboard(TFT_eSPI& tft);
    void render() override;
    void loop() override;

protected:
    unsigned long m_msTimeoutClock;
    unsigned long m_msTimeoutTemp;
    int m_clockMinute;
    int m_clockHour;
    bool m_isScreenOn;
    tm m_timeinfo;
    String getAPIData(const String& url);
    WeatherSensorData getUpstairsWeather();
    SoilSensorData getUpstairsSoilData();
    WeatherSensorData parseWeatherSensorJson(const String& json);
    SoilSensorData parseSoilSensorJson(const String& json);
    void drawSoilSquares(u_int16_t x, u_int16_t y, u_int16_t value);
    void wakeOrSleep();
    void turnScreenOff();
    void turnScreenOn();
};
