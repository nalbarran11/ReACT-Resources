#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "HTU-test";
char password[] = "123456789";

//SD+RTC Libraries
#include <SD.h>
#include "RTClib.h"

// Accelerometer Libraries
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

//RTC
RTC_PCF8523 rtc;

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

const int chipSelect = 15;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Auth Token";

BlynkTimer timer;

void myTimerEvent()
{
  lis.read();      // get X Y and Z data at once
  sensors_event_t event; 
  lis.getEvent(&event);
  Blynk.virtualWrite(V4, event.acceleration.x);
  Blynk.virtualWrite(V5, event.acceleration.y);
  Blynk.virtualWrite(V6, event.acceleration.z);

  // RTC
  DateTime now = rtc.now();
  String ahoraDate = String(int(now.month())) + "/" + String(int(now.day())) + "/" + String(int(now.year()));
  String ahoraTime = String(int(now.hour())) + ":" + String(int(now.minute())) + ":" + String(int(now.second()));
  
  String ahora = ahoraDate + "  " + ahoraTime;

  //Logging
  String dataString = String(ahoraDate)  + ", " + String(ahoraTime)  + ", " + String(event.acceleration.x) + ", " + String(event.acceleration.y) + ", " + String(event.acceleration.z);
  
  // if the file is available, write to it:
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if(dataFile)
  {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  else
  {
    Serial.println("Couldn't access file");
  }
}


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  delay(500);
  
  Blynk.begin(auth, ssid, password);

  //Accelerometer Setup
  Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  lis.setRange(LIS3DH_RANGE_4_G);

  
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent); //in ms, 2000 = 2 seconds

  // RTC Setup
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

  //SD Setup
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
  else
  {
    Serial.println("Couldn't open data file");
    return;
  }
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
