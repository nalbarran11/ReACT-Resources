/************************************************************************
 * SSD1306 WhiskerBoard 0.49" OLED Display Demo/Tutorial:
 *
 * Initiated: Mon. 11/20/2017 
 * Updated: Tue. 07/03/2018
 ************************************************************************/

#include <Wire.h>                   // For I2C communication
#include "TinyCircuits_SSD1306.h"   // Library for OLED screen


TinyCircuits_SSD1306 WhiskerOLED = TinyCircuits_SSD1306();

void setup() {
  Wire.begin();   // Begin I2C communication
  
  //Power up Whisker board
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  delay(10);
  //Toggle OLED reset line for port0
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  delay(10);
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);
  delay(10);

  selectPort(0);  // This port# matches the one labeled on the adapter board
  WhiskerOLED.begin();      // Begin and initialize OLED to display 
  WhiskerOLED.clear();

}

int x=40;
int direction=1;

void loop() {
  x+=direction;
  if(x>=20){
    direction=-1;
  }
  if(x<=0){
    direction=1;
  }
  WhiskerOLED.setCursor(x,1);
  WhiskerOLED.print(" Test ");
  delay(5);
}

// **This function is necessary for all Whisker boards attached through an Adapter board**
// Selects the correct address of the port being used in the Adapter board
void selectPort(int port) {
  Wire.beginTransmission(0x70);
  Wire.write(0x04 + port);
  Wire.endTransmission(0x70);
}
