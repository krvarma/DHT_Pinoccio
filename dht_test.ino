#include <SPI.h>
#include <Wire.h>
#include <Scout.h>
#include <GS.h>
#include <bitlash.h>
#include <lwm.h>
#include <js0n.h>

extern "C" {
  #include "key/key.h"
  #include "util/memdebug.h"
  #include "util/StringBuffer.h"
}

#include "dht.h"

#define DHT22_PIN 4

dht odht;

void setup() {
  Serial.begin(115200);
  Scout.setup();
  
  // Add Bitlash functions
  addBitlashFunction("dht22.temperature", (bitlash_function)temperature);
  addBitlashFunction("dht22.humidity", (bitlash_function)humidity);
}

void loop() {
  Scout.loop();

  // Read DHT Values
  odht.read(DHT22_PIN);
  
  // Debug output
  Serial.print("DHT Temperature: ");
  Serial.println(odht.temperature);
  Serial.print("Onboard Temperature: ");
  Serial.println(Scout.getTemperatureC());
  Serial.print("Humidity: ");
  Serial.println(odht.humidity);
  
  // Report to HQ
  reportToHQ((int)odht.temperature, (int)odht.humidity);
  
  // Delay
  delay(2000);
}

// Bitlash function to retrieve temperature
numvar temperature(void){
  return (numvar)odht.temperature;
}

// Bitlash function to retrieve humidity
numvar humidity(void){
  return (numvar)odht.humidity;
}

void reportToHQ(int temperature, int humidity){
  // Report temperature and humidity to HQ
  StringBuffer report(100);
  report.appendSprintf("[%d,[%d, %d],[%d, %d]]",
          keyMap("DHT22", 0),
          keyMap("t", 0),
          keyMap("h", 0),
          (int)(odht.temperature * 100),
          (int)(odht.humidity * 100));
          
  Scout.handler.report(report); 
}
