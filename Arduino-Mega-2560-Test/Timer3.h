#ifndef Timer3_h
#define Timer3_h
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


class Timer3
{
public:
	//Constructors
	Timer3(int mode, int prescaler, unsigned int top, unsigned int ocr);
	Timer3();
	unsigned int TOP;
	int PRESCALER;
	unsigned int OCR;
	int MODE;

	//设置计时器的溢出计数 中断TIMER3_OVF_vect
	void setTOP(unsigned int top);
	//设置计数器的比较输出计数 中断TIMER3_COMPA_vect
	void setOCR(unsigned int ocr);
	/*设置计数器的工作模式

	*/
	void setMode(int mode);
	//启动计数器
	void enable();
	//禁用计数器
	void disable();
	//设置倍率值
	void setPrescaler(int Prescaler);

	~Timer3() {
	};

private:

};
#endif