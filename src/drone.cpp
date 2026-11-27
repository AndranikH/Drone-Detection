#include <WiFi.h>
#include <Arduino.h>
#include "FS.h"
#include <LittleFS.h>
#include "config.h" 
const char* const TARGET_SSID = CONF_TARGET;
const char* FILE_PATH = "/distanceLog.csv"; 
int distance;
int sumRSSI = 0;
int counter = 0;
bool csvExists(){
  File f = LittleFS.open(FILE_PATH, "r");
  if(f && f.size() > 0){
    f.close();
    return true;
  }
  f.close();
  return false;
}
void writeCsvHeader(){
 
    File f = LittleFS.open(FILE_PATH, "w"); //will overwrite everything, so its fired only once
    if(f) {
      f.printf("Distance,Average_RSSI,Sample\n");
      f.close();
  }
  
}

int askDistance(){
  Serial.printf("Distance: \n");
  while(Serial.available() == 0){
    delay(10);
  }
  distance = Serial.parseInt();
  Serial.printf("Distance set to:  %d\n", distance);
  return distance;
}

void writeRow(int distance, float avg, int sampleSize){
  File f = LittleFS.open(FILE_PATH, "a");
  // "Distance, Average RSSI, Sample"
  if(f){
    f.printf("%d,%.2f,%d\n" , distance, avg, sampleSize);
    f.close();
  }else{
    Serial.println("Failed to Log Row");
  }
  
  
}
void dumpCSV(){
  File f = LittleFS.open(FILE_PATH, "r");
  if(f && f.size() > 0){
  while(f.available()){
    Serial.write(f.read());
     
  }
 f.close();
}
}

void setup()
{

  Serial.begin(115200);
  delay(2000);
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println("NEW CODE v3");

  if(!LittleFS.begin(true)){
    Serial.println("Failed to mount LittleFS");
    while(1){
      delay(10);
    }
  }
 
  if(!csvExists()){
  writeCsvHeader(); 
  }
  
  //ask user for distance
  askDistance();
}



void loop()
{

  // TODO 1: scan with WiFi.scanNetworks()
  // TODO 2: loop through results, find the one whose SSID matches TARGET
  // TODO 3: print its RSSI with WiFi.RSSI(i)
  // TODO 4 (after it works): keep a running sum of 20 readings and print the average
 if(Serial.available() && Serial.read() == 'd'){
  dumpCSV();
 }
  
  int n = WiFi.scanNetworks();
 
  Serial.printf("number of networks found: %d\n", n);

  for (int i = 0; i < n; i++)
  {
    if (WiFi.SSID(i) == TARGET_SSID)
    {
      Serial.printf("Found target network %s with RSSI %d\n", TARGET_SSID, (int)WiFi.RSSI(i));
      sumRSSI += WiFi.RSSI(i);
      counter++;
      if (counter == 20)
      {
        float avgRSSI = sumRSSI / 20.0;
        Serial.printf("Average RSSI for %s is %.2f\n", TARGET_SSID, avgRSSI);
        writeRow(distance, avgRSSI, counter);
        Serial.printf("-------ROW LOGGED-------\n");
        sumRSSI = 0;
        counter = 0;
      }
    }
     
  }
  WiFi.scanDelete();
  delay(500);
}
