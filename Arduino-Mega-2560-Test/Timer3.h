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

	//���ü�ʱ����������� �ж�TIMER3_OVF_vect
	void setTOP(unsigned int top);
	//���ü������ıȽ�������� �ж�TIMER3_COMPA_vect
	void setOCR(unsigned int ocr);
	/*���ü������Ĺ���ģʽ

	*/
	void setMode(int mode);
	//����������
	void enable();
	//���ü�����
	void disable();
	//���ñ���ֵ
	void setPrescaler(int Prescaler);

	~Timer3() {
	};

private:

};
#endif