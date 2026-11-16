#include <WiFi.h>
#include <Arduino.h>
const char *target = "Hro";
int sumRSSI = 0;
int counter = 0;
void setup()
{

  Serial.begin(115200);
  delay(2000);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println("NEW CODE v3");
}

void loop()
{

  // TODO 1: scan with WiFi.scanNetworks()
  // TODO 2: loop through results, find the one whose SSID matches TARGET
  // TODO 3: print its RSSI with WiFi.RSSI(i)
  // TODO 4 (after it works): keep a running sum of 20 readings and print the average

  int n = WiFi.scanNetworks();
  Serial.printf("number of networks found: %d\n", n);

  for (int i = 0; i < n; i++)
  {
    if (WiFi.SSID(i) == target)
    {
      Serial.printf("Found target network %s with RSSI %d\n", target, WiFi.RSSI(i));
      sumRSSI += WiFi.RSSI(i);
      counter++;
      if (counter == 20)
      {
        Serial.printf("Average RSSI for %s is %d\n", target, sumRSSI / 20);
        sumRSSI = 0;
        counter = 0;
      }
    }
  }
  delay(500);
}
