#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <SerialESP8266wifi.h>

#include <Arduino.h>

const char* SSID = "CANGURU";

// Return RSSI or 0 if target SSID not found
int32_t getRSSI(const char* target_ssid) {
  byte available_networks = WiFi.scanNetworks();

  for (int network = 0; network < available_networks; network++) {
    if (strcmp(WiFi.SSID(network), target_ssid) == 0) {
      return WiFi.RSSI(network);
    }
  }
  return 0;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long before = millis();
  int32_t rssi = getRSSI(SSID);
  unsigned long after = millis();
  Serial.print("Signal strength: ");
  Serial.print(rssi);
  Serial.println("dBm");

  Serial.print("Took ");
  Serial.print(after - before);
  Serial.println("ms");
  delay(1000);
}
