//
// Created by destin on 6/8/26.
//

#include "screens/Dashboard.h"
#include "WiFi.h"
#include "HTTPClient.h"
#include "TFT_eSPI.h"
#include "time.h"
//#include "Fonts/GFXFF/FreeSansBold24pt7b.h"

Dashboard::Dashboard(TFT_eSPI& tft)
  : Screen(tft)
{
  m_isScreenOn = true;
}

void Dashboard::loop()
{
  unsigned long now = millis();
  if (now - m_msTimeoutClock >= 1000)
  {
    // Run functions on minute change
    if (getLocalTime(&m_timeinfo, 10000) && m_timeinfo.tm_min != m_clockMinute)
    {
      wakeOrSleep();
      render();

      // Set the current vars AFTER function calls
      m_clockMinute = m_timeinfo.tm_min;
      m_clockHour = m_timeinfo.tm_hour;
      m_msTimeoutClock = now;
    }
  }
}

void Dashboard::wakeOrSleep()
{
  if (m_isScreenOn
    && m_timeinfo.tm_hour == DASH_SLEEP_HOUR
    && m_timeinfo.tm_min == DASH_SLEEP_MINUTE)
  {
    turnScreenOff();
  }
  else if (!m_isScreenOn
    && m_timeinfo.tm_hour == DASH_WAKE_HOUR
    && m_timeinfo.tm_min == DASH_WAKE_MINUTE)
  {
    turnScreenOn();
  }
}

void Dashboard::render()
{
  if (!m_isScreenOn) return;

  // Get data before clearing the screen so it doesn't visibly flash
  WeatherSensorData upstairsWeather = getUpstairsWeather();
  SoilSensorData soilData = getUpstairsSoilData();

  // Clear the screen before render
  m_tft.fillScreen(TFT_BLACK);


  // 1. Create a buffer to hold the formatted string
  char timeBuffer[10]; // "11:45 PM" plus a null terminator is 9 characters

  // 2. Format the time into the buffer
  // %I = Hour (12-hour clock, 01-12)
  // %M = Minute (00-59)
  // %p = AM or PM designation
  strftime(timeBuffer, sizeof(timeBuffer), "%l:%M %P", &m_timeinfo);

  // 3. Convert it to a regular Arduino String
  String formattedTime = String(timeBuffer);
  m_tft.setFreeFont(&FreeSans24pt7b);
  m_tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);

  int16_t width = m_tft.textWidth(formattedTime); // pixel width
  int16_t height = m_tft.fontHeight(); // line height in pixels

  // Center text example:
  int x = (SCREEN_WIDTH - width) / 2;
  int y = (SCREEN_HEIGHT + height) / 2;
  m_tft.drawString(formattedTime, x, 2);

  u16_t upwy = 47;
  const u16_t leftx = 5;

  m_tft.setFreeFont(&FreeSansBold9pt7b);
  const String up_title = String("UPSTAIRS");
  m_tft.drawString(up_title, leftx, upwy);

  // Adjust down the title height
  upwy += 16;

  m_tft.setFreeFont(&FreeSans24pt7b);


  String upstairsTemp = String(upstairsWeather.temperature, 0);
  int16_t upwidth = m_tft.textWidth(upstairsTemp);
  m_tft.drawString(upstairsTemp, leftx, upwy);
  m_tft.drawCircle(leftx + upwidth + 5, upwy + 5, 3, TFT_WHITE);

  drawSoilSquares(leftx + upwidth + 15, upwy, soilData.sensor_a);
  drawSoilSquares(leftx + upwidth + 15, upwy + 14, soilData.sensor_b);
}

WeatherSensorData Dashboard::getUpstairsWeather()
{
  const String url = String("http://192.168.100.125/api/weather");
  String json = getAPIData(url);
  if (json != "")
  {
    return parseWeatherSensorJson(json);
  }
  return WeatherSensorData{0.0f, 0.0f};
}

SoilSensorData Dashboard::getUpstairsSoilData()
{
  const String url = String("http://192.168.100.125/api/soil");
  String json = getAPIData(url);
  if (json != "")
  {
    return parseSoilSensorJson(json);
  }
  return SoilSensorData{0, 0};
}

String Dashboard::getAPIData(const String& url)
{
  String json = String("");
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    http.begin(url); // set the URL
    http.addHeader("Accept", "application/json"); // optional headers

    int httpCode = http.GET();

    if (httpCode > 0)
    {
      Serial.printf("HTTP code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK)
      {
        String payload = http.getString();
        json = payload;
        Serial.println("Response: " + payload);
      }
    }
    else
    {
      Serial.printf("GET failed, error: %s\n",
                    http.errorToString(httpCode).c_str());
    }

    http.end(); // free resources
  }
  return json;
}

WeatherSensorData Dashboard::parseWeatherSensorJson(const String& json)
{
  WeatherSensorData out = {0.0f, 0.0f};
  // Extract temperature
  int tKey = json.indexOf("\"temperature\":");
  if (tKey == -1) return out;
  int tStart = tKey + 14; // skip past "temperature":
  int tEnd = json.indexOf(',', tStart);
  if (tEnd == -1) return out;

  // Extract humidity
  int hKey = json.indexOf("\"humidity\":");
  if (hKey == -1) return out;
  int hStart = hKey + 11; // skip past "humidity":
  int hEnd = json.indexOf('}', hStart);
  if (hEnd == -1) return out;

  out.temperature = json.substring(tStart, tEnd).toFloat();
  out.humidity = json.substring(hStart, hEnd).toFloat();
  return out;
}

SoilSensorData Dashboard::parseSoilSensorJson(const String& json)
{
  SoilSensorData out = {0, 0};
  // Extract soil_sensor_a
  int aKey = json.indexOf("\"soil_sensor_a\":");
  if (aKey == -1) return out;
  int aStart = aKey + 16; // skip past "soil_sensor_a":
  int aEnd = json.indexOf(',', aStart);
  if (aEnd == -1) return out;

  // Extract soil_sensor_b
  int bKey = json.indexOf("\"soil_sensor_b\":");
  if (bKey == -1) return out;
  int bStart = bKey + 16; // skip past "soil_sensor_b":
  int bEnd = json.indexOf('}', bStart);
  if (bEnd == -1) return out;

  out.sensor_a = json.substring(aStart, aEnd).toInt();
  out.sensor_b = json.substring(bStart, bEnd).toInt();
  return out;
}

void Dashboard::drawSoilSquares(u_int16_t x, u_int16_t y, u_int16_t value)
{
  const u_int16_t width = 10;
  const u_int16_t height = 10;
  const u_int16_t gap = 4;

  if (value > 2700)
  {
    m_tft.fillRect(x, y, width, height, TFT_RED);
    m_tft.fillRect(x + width + gap, y, width, height, TFT_RED);
    m_tft.fillRect(x + (2 * (width + gap)), y, width, height, TFT_RED);
    m_tft.fillRect(x + (3 * (width + gap)), y, width, height, TFT_RED);
  }
  else if (value <= 2700 && value > 2300)
  {
    m_tft.fillRect(x, y, width, height, TFT_YELLOW);
    m_tft.fillRect(x + width + gap, y, width, height, TFT_YELLOW);
    m_tft.fillRect(x + (2 * (width + gap)), y, width, height, TFT_RED);
    m_tft.fillRect(x + (3 * (width + gap)), y, width, height, TFT_RED);
  }
  else if (value <= 2300 && value > 1900)
  {
    m_tft.fillRect(x, y, width, height, TFT_GREEN);
    m_tft.fillRect(x + width + gap, y, width, height, TFT_GREENYELLOW);
    m_tft.fillRect(x + (2 * (width + gap)), y, width, height, TFT_YELLOW);
    m_tft.fillRect(x + (3 * (width + gap)), y, width, height, TFT_YELLOW);
  }
  else if (value <= 1900 && value > 1500)
  {
    m_tft.fillRect(x, y, width, height, TFT_GREEN);
    m_tft.fillRect(x + width + gap, y, width, height, TFT_GREEN);
    m_tft.fillRect(x + (2 * (width + gap)), y, width, height, TFT_GREENYELLOW);
    m_tft.fillRect(x + (3 * (width + gap)), y, width, height, TFT_YELLOW);
  }
  else if (value <= 1500)
  {
    m_tft.fillRect(x, y, width, height, TFT_GREEN);
    m_tft.fillRect(x + width + gap, y, width, height, TFT_GREEN);
    m_tft.fillRect(x + (2 * (width + gap)), y, width, height, TFT_GREEN);
    m_tft.fillRect(x + (3 * (width + gap)), y, width, height, TFT_GREEN);
  }
}

void Dashboard::turnScreenOff()
{
  m_isScreenOn = false;
  digitalWrite(TFT_BL, LOW); // Kill backlight
  m_tft.writecommand(0x10); // Sleep IN
  delay(120);
}

void Dashboard::turnScreenOn()
{
  m_isScreenOn = true;
  m_tft.writecommand(0x11); // Sleep OUT
  delay(120);
  m_tft.writecommand(0x29); // Display ON
  digitalWrite(TFT_BL, HIGH); // Restore backlight
}
