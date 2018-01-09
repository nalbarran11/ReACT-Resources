# TinyCircuits Dual Motor Driver Arduino Library

This library is intended for use with TinyCircuits' ASD2302 Dual Motor Driver TinyShield. This shield uses a ATtiny841 microcontroller and motor driver hardware to provide two 16 bit motor outputs controlled through I2C. The Arduino library itself allows for easy interface using the TinyDuino platform. Included with the library is the ATtiny841 firmware- it is intended to be hackable and allow for extra functionality to be implemented(full ATtiny register access through I2C).

## Basic Example

An example program is included that shows how to drive motors from the TinyDuino.