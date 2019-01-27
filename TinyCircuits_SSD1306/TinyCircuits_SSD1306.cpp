//*******************************************************************
// TinyCircuits - SSD1306 OLED Display Library
// Written by: Brandon Farmer for TinyCircuits
//
// Initiated: Fri. 11/24/2017 @ 12:30PM
//   Updated: Fri. 11/24/2017 @ 12:45PM
//
// Revision 0 - Original Release
//	RELEASED: MM/DD/YYYY ***Not Yet Released***
//
//*******************************************************************

#include <stdlib.h>
#include <Arduino.h>
#include <Wire.h>
#include "TinyCircuits_SSD1306.h"

//Constructor
TinyCircuits_SSD1306::TinyCircuits_SSD1306(void) {
  //Nothing
}

//Send Command Function 
void TinyCircuits_SSD1306::sendCommand(uint8_t command) {
  Wire.beginTransmission(SSD1306_DEFAULT_ADDRESS);
  Wire.write(0x00);
  Wire.write(command);
  Wire.endTransmission();
}


//Start the I2C Communication
void TinyCircuits_SSD1306::begin(void) {
  // Turn display off
  sendCommand(SSD1306_DISPLAYOFF);

  sendCommand(SSD1306_SETDISPLAYCLOCKDIV);
  sendCommand(0x80);

  sendCommand(SSD1306_SETMULTIPLEX);
  sendCommand(0x1F);

  sendCommand(SSD1306_SETDISPLAYOFFSET);
  sendCommand(0x00);

  sendCommand(SSD1306_SETSTARTLINE | 0x00);

  // We use internal charge pump
  sendCommand(SSD1306_CHARGEPUMP);
  sendCommand(0x14);

  sendCommand(SSD1306_SEGREMAP | 0x1);

  sendCommand(SSD1306_COMSCANDEC);

  sendCommand(SSD1306_SETCOMPINS);
  sendCommand(0x12);

  // Max contrast
  sendCommand(SSD1306_SETCONTRAST);
  sendCommand(0xAF);

  sendCommand(SSD1306_SETPRECHARGE);
  sendCommand(0x1F);

  sendCommand(SSD1306_SETVCOMDETECT);
  sendCommand(0x40);

  sendCommand(SSD1306_DISPLAYALLON_RESUME);

  // Non-inverted display
  sendCommand(SSD1306_NORMALDISPLAY);

  // Turn display back on
  sendCommand(SSD1306_DISPLAYON);


  // Horizontal memory mode
  sendCommand(SSD1306_MEMORYMODE);
  sendCommand(0x00);
}

void TinyCircuits_SSD1306::sendFramebuffer(uint8_t *buffer) {
    sendCommand(SSD1306_COLUMNADDR);
  sendCommand(0x00);
  sendCommand(0x5F);

  sendCommand(SSD1306_PAGEADDR);
  sendCommand(0x00);
  sendCommand(0x01);

  // We have to send the buffer as 16 bytes packets
  // Our buffer is 1024 bytes long, 1024/16 = 64
  // We have to send 64 packets
  for (uint8_t packet = 0; packet < 24; packet++) {
    Wire.beginTransmission(SSD1306_DEFAULT_ADDRESS);
    Wire.write(0x40);
    for (uint8_t packet_byte = 0; packet_byte < 8; ++packet_byte) {
      Wire.write(buffer[packet * 8 + packet_byte]);
    }
    Wire.endTransmission();
  }
}
void TinyCircuits_SSD1306::clear() {
    sendCommand(SSD1306_COLUMNADDR);
  sendCommand(32+0x00);
  sendCommand(32+64-1);

  sendCommand(SSD1306_PAGEADDR);
  sendCommand(0x00);
  sendCommand(0x03);

  // We have to send the buffer as 16 bytes packets
  // Our buffer is 1024 bytes long, 1024/16 = 64
  // We have to send 64 packets
  for (uint8_t packet = 0; packet < 24; packet++) {
    Wire.beginTransmission(SSD1306_DEFAULT_ADDRESS);
    Wire.write(0x40);
    for (uint8_t packet_byte = 0; packet_byte < 8; ++packet_byte) {
      Wire.write(0);
    }
    Wire.endTransmission();
  }
}

void TinyCircuits_SSD1306::setCursor(int x, int y) {
  sendCommand(SSD1306_COLUMNADDR);
  sendCommand(32+x);
  sendCommand(32+64-1);

  sendCommand(SSD1306_PAGEADDR);
  sendCommand(y);
  sendCommand(0x03);
  
}

size_t TinyCircuits_SSD1306::write(uint8_t c) {
  if (c < ' ' || c > ('}'+2))return 0;
  c -= ' ';

  Wire.beginTransmission(SSD1306_DEFAULT_ADDRESS);
  Wire.write(0x40);
  for (int i = 0; i < 5; i++) {
    Wire.write(Font5x7[c * 5 + i]);
  }
  Wire.endTransmission();
  return 1;
}