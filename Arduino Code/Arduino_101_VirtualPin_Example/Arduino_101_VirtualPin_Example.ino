
//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

//#define BLYNK_USE_DIRECT_CONNECT

#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>

#include <Wire.h>
#include "Adafruit_VCNL4010.h"

char auth[] = "AUTH TOKEN HERE";

Adafruit_VCNL4010 vcnl;

BLEPeripheral  blePeripheral;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(1000);

  blePeripheral.setLocalName("Blynk_Sp");
  blePeripheral.setDeviceName("Blynk_Sp");
  blePeripheral.setAppearance(384);

  Blynk.begin(blePeripheral, auth);

  blePeripheral.begin();

  Serial.println("Waiting for connections...");
  
    if (! vcnl.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }
  Serial.println("Found VCNL4010");
}


void loop() {
  Blynk.run();
  blePeripheral.poll(); 
}

BLYNK_READ(V5){
  float prox = vcnl.readProximity();
  float light = vcnl.readAmbient(); 
  int new_prox = map(prox, 2000, 65500, 0, 9999);
  Blynk.virtualWrite(V5, new_prox);
}
