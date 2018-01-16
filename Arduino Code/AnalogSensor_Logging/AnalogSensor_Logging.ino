// *For Adalogger 32u4 SD card chipselect is on pin 4
// *Photoresistor or other analog sensor on pin A0
 

#include <Wire.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
int reading = 0;
int sensorpin = A1;

uint32_t start_time = 0;

void setup() {
  Serial.begin(9600);
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
    dataFile.println("Time, Reading");
    dataFile.close(); 
  }
  else
  {
    Serial.println("Couldn't open data file");
    return;
  }
  start_time=millis();
  Serial.print("Start Time: ");
  Serial.println(start_time);
}

void loop() {
  // make a string for assembling the data to log:

  reading = analogRead(sensorpin);
  
  String dataString = String(millis()-start_time) + " ," + String(reading) + " ,"  + String(whateverreading);
  Serial.println(dataString);
  
   File dataFile = SD.open("datalog.csv", FILE_WRITE);
   if(dataFile){
      dataFile.println(dataString);
      dataFile.close();
   }
   else{
      Serial.println("Couldn't access file");
   }
   delay(500);
}

