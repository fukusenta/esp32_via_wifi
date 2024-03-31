/**
 * @file    esp32_via_wifi.ino
 * @brief   An IoT system using ESP32 that allows web-based configuration as an AP.
 * @author  Kusakari
 * @date    2024.03.31 - Created for test.
 */
#include "WiFiInfoManager.h"


viawifi::WiFiInfoManager wmanager;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();

  if(!wmanager.configure("testA", "testB", false)) Serial.println("reboot!");

  Serial.print("SSID: ");
  Serial.println(wmanager.getSSID());
  Serial.print("password: ");
  Serial.println(wmanager.getPassword());
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
}
