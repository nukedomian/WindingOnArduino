/*
 Name:		_1602TestProgram.ino
 Created:	2020-06-05 14:37:38
 Author:	liunian
*/

// the setup function runs once when you press reset or power the board
#include "LiquidCrystal_I2C.h"
#include <Wire.h>
#include <Liquidcrystal.h>


LiquidCrystal_I2C lcd(0x27, 16,2);

int incomingData = 0;
float x = 0;


void setup()
{
    lcd.init();                      // initialize the lcd 
    lcd.backlight();
    Serial.begin(9600);
}

void loop()
{
    // when characters arrive over the serial port...
    if (Serial.available()) {
        // wait a bit for the entire message to arrive
        delay(100);
        // clear the screen
        lcd.clear();
        // read all the available characters
        while (Serial.available() > 0) {
            lcd.write(Serial.read());
        }
    }
}