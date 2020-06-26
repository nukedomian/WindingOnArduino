// 
// 
// 

#include "Timer3.h"
#include "Arduino.h"

//Constructor with mode number, prescaler, top and ocr3A
Timer3::Timer3(int mode, int prescaler, unsigned int top, unsigned int ocr)
{
	TCCR3A = 0;
	TCCR3B = 0;

	this->MODE = mode;
	this->PRESCALER = prescaler;
	this->TOP = top;
	this->OCR = ocr;
	setMode(MODE);
	setPrescaler(PRESCALER);
	setTOP(TOP);
	setOCR(OCR);
	}
Timer3::Timer3() 
{
}
void Timer3::setTOP(unsigned int top)
{
	cli();
	this->TOP = top;
	if ((TOP > 65535) || (TOP <= 0))
	{
			ICR3 = 65535;
	}
	else
	{
			ICR3 = TOP;
	}
	sei();
}

void Timer3::setOCR(unsigned int ocr) {
	cli();
	this->OCR = ocr;
	if ((ocr > 65535) || (ocr <= 0))
	{
		OCR3A = 65535;
	}
	else
	{
		OCR3A = OCR;
	}
	sei();
}

void Timer3::setMode(int mode) {
	//Set Timer 3 Mode to CTC (Compare to Clear) Mode 12 where TOP3 is defined by ICR3
	//Set Timer 3 Mode to Fast PWM  Mode 14 where TOP3 is defined by ICR3
	if (mode==14)
	{
		cli();
		TCCR3B &= ~(1 << ICNC3);
		TCCR3B &= ~(1 << ICES3);
		TCCR3B |= (1 << WGM33);
		TCCR3B |= (1 << WGM32);
		TCCR3A |= (1 << WGM31);
		TCCR3A &= ~(1 << WGM30);
		sei();
	}
}

void Timer3::enable() {
	//		TIMSK3 |= (1 << OCIE3B);
	//		TIMSK3 |= (1 << OCIE3C);
	TIMSK3 |= (1 << OCIE3A);
	TIMSK3 |= (1 << TOIE3);
}

void Timer3::disable() {
	TIMSK3 &= ~(1 << OCIE3B);
	TIMSK3 &= ~(1 << OCIE3C);
	TIMSK3 &= ~(1 << OCIE3A);
	TIMSK3 &= ~(1 << TOIE3);
}

void Timer3::setPrescaler(int Prescaler) {
	this->PRESCALER = Prescaler;
	switch(PRESCALER)
	{
	case 0:
		TCCR3B &= ~(1 << CS32);
		TCCR3B &= ~(1 << CS31);
		TCCR3B &= ~(1 << CS30);
		break;
	case 1:
		TCCR3B &= ~(1 << CS32);
		TCCR3B &= ~(1 << CS31);
		TCCR3B |= (1 << CS30);
		break;
	case 8:
		TCCR3B &= ~(1 << CS32);
		TCCR3B |= (1 << CS31);
		TCCR3B &= ~(1 << CS30);
		break;
	case 64:
		TCCR3B &= ~(1 << CS32);
		TCCR3B |= (1 << CS31);
		TCCR3B |= (1 << CS30);
		break;
	case 256:
		TCCR3B |= (1 << CS32);
		TCCR3B &= ~(1 << CS31);
		TCCR3B &= ~(1 << CS30);
		break;
	case 1024:
		TCCR3B |= (1 << CS32);
		TCCR3B &= ~(1 << CS31);
		TCCR3B |= (1 << CS30);
		break;
	default:
		TCCR3B &= ~(1 << CS32);
		TCCR3B &= ~(1 << CS31);
		TCCR3B &= ~(1 << CS30);
		break;
	}
}