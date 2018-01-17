#include "RTClib.h"

#include <SPI.h>
#include <SD.h>

#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

//RTC
RTC_PCF8523 rtc;

const int chipSelect = 15;

void setup() {
  Serial.begin(9600);
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  
  }


  Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");

  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile){
    dataFile.println("......................");
    dataFile.println("Date, Time, X, Y, Z");
    dataFile.close(); 
  }
  else{
    Serial.println("Couldn't open data file");
    return;
  }

}

void loop() {

  DateTime now = rtc.now();
  String ahoraDate = String(int(now.month())) + "/" + String(int(now.day())) + "/" + String(int(now.year()));
  String ahoraTime = String(int(now.hour())) + ":" + String(int(now.minute())) + ":" + String(int(now.second()));
  
  String ahora = ahoraDate + "  " + ahoraTime;

  lis.read();      // get X Y and Z data at once
  sensors_event_t event; 
  lis.getEvent(&event);

String dataString = String(ahoraDate)  + ", " + String(ahoraTime)  + ", " + String(event.acceleration.x) + ", " + String(event.acceleration.y) + ", " + String(event.acceleration.z);

   File dataFile = SD.open("datalog.csv", FILE_WRITE);
   if(dataFile){
      dataFile.println(dataString);
      dataFile.close();
      Serial.println(dataString);
   }
   else{
      Serial.println("Couldn't access file");
   }
   delay(100);
}









