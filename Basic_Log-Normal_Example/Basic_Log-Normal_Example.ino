#include <math.h>
#include "WiFi.h"
#include "LgNormShadow.h"

// Wi-Fi related variables
float distance;
float rssi;
int wifiChannel;
const float alpha = 0.2; // EMA smoothing factor (range: 0-1, higher values give more weight to recent readings)
float smoothedRssi = 0.0;

// Log-normal shadowing model parameters
float referenceDistance = 1.0; // Referensi jarak dalam meters
float referenceRSSI = -24.0; // RSSI dengan referensi jarak (do)
float pathLossExponent = 3; // Path loss exponent (shadowing urban celluar radio 3-5)
float shadowingStdDev = 2; // Standard deviation di log-normal shadowing dalam satuan dB
const float transmitterPower = 2.0; // Transmitter power in dBm

float LNSM(int rssi) {
  // Calculate distance using log-normal shadowing model
  float shadowing = lognormalShadowing(shadowingStdDev); //calling library log normal shadowing
  float formula_sqrt = -(transmitterPower - ((referenceRSSI - rssi) + shadowing)) / (10 * pathLossExponent); // formula square for distance
  float distance = pow(10, formula_sqrt) * referenceDistance; // pow to formula

  return distance
}

void find_WiFi() {
  // find wifi rssi
  int n = WiFi.scanNetworks();

  if (n == 0) {
    Serial.println("no networks found");
  } else {
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      String ssid = WiFi.SSID(i);
      rssi = WiFi.RSSI(i);
      smoothedRssi = alpha * rssi + (1 - alpha) * smoothedRssi; // stabilized RSSI value using EMA formula
      wifiChannel = WiFi.channel(i) * 5 + 2407;
      distance = LNSM(smoothedRssi);
      Serial.print("RSSI : ");
      Serial.print(smoothedRssi, 0);
      Serial.print(", Freq: ");
      Serial.print(wifiChannel);
      Serial.print(", distance: ");
      Serial.println(distance);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void loop() {
  find_WiFi();
  delay(1000);
}
