#include "Timer3.h"

#define pin_LED1 13
#define pin_LED2 12

void setup()
{
	pinMode(pin_LED1, OUTPUT);
	pinMode(pin_LED2, OUTPUT);
	Timer3 Timer(14, 256, 20, 10);
	digitalWrite(pin_LED1, 1);
	digitalWrite(pin_LED2, 0);

	Timer.enable();
	sei();
}

void loop()

{
	delay(10);
}



ISR(TIMER3_OVF_vect)
{
	digitalWrite(pin_LED1, !digitalRead(pin_LED1));
	digitalWrite(pin_LED2, !digitalRead(pin_LED2));

}

ISR(TIMER3_COMPA_vect)
{
	digitalWrite(pin_LED1, !digitalRead(pin_LED1));
	digitalWrite(pin_LED2, !digitalRead(pin_LED2));
}