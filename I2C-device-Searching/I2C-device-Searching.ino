/*
 Name:		I2C_device_Searching.ino
 Created:	2020-06-05 14:34:43
 Author:	liunian
*/

// the setup function runs once when you press reset or power the board

#include <Wire.h>
#include <Liquidcrystal.h>


void setup() {
	Serial.begin(115200); // Leonardo: wait for serial port to connect 
	while (!Serial) {}
	Serial.println();
	Serial.println("I2C scanner. Scanning ...");
	byte count = 0;
	Wire.begin();
	for (byte i = 8; i < 120; i++) {
		Wire.beginTransmission(i);
		if (Wire.endTransmission() == 0) {
			Serial.print("Found address: ");
			Serial.print(i, DEC);
			Serial.print(" (0x");
			Serial.print(i, HEX);
			Serial.println(")");
			count++;
			delay(1); // maybe unneeded? 
		} // end of good response 
	} // end of for loop 
	Serial.println("Done.");
	Serial.print("Found ");
	Serial.print(count, DEC);
	Serial.println(" device(s).");
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
