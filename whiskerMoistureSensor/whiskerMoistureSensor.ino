#include <Wire.h>

#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif


//tuneable values
int minimumVal = 700; // This is the value read from the Moisture Sensor when completely dry
int maximumVal = 964; // This is the value read from the Moisture Sensor when completely submerged


void setup() {
  Wire.begin();
  SerialMonitorInterface.begin(9600);
  while (!SerialMonitorInterface);

  selectPort(0);
  delay(100);
}

void loop() {
  int val = readMoisture();
  int percent = (constrain(val,minimumVal,maximumVal) - minimumVal)*100 / (maximumVal-minimumVal);
  SerialUSB.print("Raw value: "); SerialUSB.print(val);
  SerialUSB.print("\tMoisture level: "); SerialUSB.println(percent);

  delay(100);
}


// Read moisture from Soil Moisture Whisker
int readMoisture(){
  Wire.beginTransmission(0x23);
  Wire.write(1);
  Wire.endTransmission();
  delay(5);
  int c=0;
  Wire.requestFrom(0x23, 2);
  if(Wire.available()==2)
  { 
    c = Wire.read();
    c<<=8;
    c|=Wire.read();
  }
  return c;
}


void selectPort(int port) {
  Wire.beginTransmission(0x70);
  Wire.write(0x04 + port);
  Wire.endTransmission();
}
