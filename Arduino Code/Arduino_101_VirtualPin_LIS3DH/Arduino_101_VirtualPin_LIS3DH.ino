
//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial

//#define BLYNK_USE_DIRECT_CONNECT

#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>

// Accelerometer Libraries
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

char auth[] = "AUTH TOKEN HERE";

BLEPeripheral  blePeripheral;
BlynkTimer timer;

void myTimerEvent()
{
  lis.read();      // get X Y and Z data at once
  sensors_event_t event; 
  lis.getEvent(&event);
  Blynk.virtualWrite(V4, event.acceleration.x);
  Blynk.virtualWrite(V5, event.acceleration.y);
  Blynk.virtualWrite(V6, event.acceleration.z);
}


void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(1000);

  blePeripheral.setLocalName("ChickenBeef");
  blePeripheral.setDeviceName("ChickenBeef");
  blePeripheral.setAppearance(384);

  Blynk.begin(blePeripheral, auth);

  blePeripheral.begin();
  
  Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  lis.setRange(LIS3DH_RANGE_4_G);

  
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent); //in ms, 2000 = 2 seconds

}


void loop() {
  Blynk.run();
  blePeripheral.poll(); 
  timer.run(); // Initiates BlynkTimer
}

