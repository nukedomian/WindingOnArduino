#include "Timer3.h"

#define pin_LED1 13
#define pin_LED2 12

void setup() 
{
	pinMode(pin_LED1, OUTPUT);
	pinMode(pin_LED2, OUTPUT);
	Timer3 Timer(14,64,32767,65535);
	digitalWrite(pin_LED1,1);
	digitalWrite(pin_LED1,0);


}

void loop() 

{
	delay(100);
}



ISR(TIMER3_OVF_vect) 
{
	digitalWrite(pin_LED1,!digitalRead(pin_LED1));
	digitalWrite(pin_LED2, !digitalRead(pin_LED2));
}

ISR(TIMER3_COMPA_vect)
{
}