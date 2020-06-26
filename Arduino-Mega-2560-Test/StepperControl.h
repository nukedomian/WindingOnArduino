// StepperControl.h

#ifndef _STEPPERCONTROL_h
#define _STEPPERCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class StepperControl
{

 public:
	 //Constants and Variables
	 int pinENA;
	 int pinDIR;
	 int pinPUL;

	 int FullRotationPulseCount = 400;				//步进电机旋转分度
	 int MachineCordinationRatio = 360;				//机械坐标比例

	 bool direcion = 0;
	 bool isEnable = 0;

	 //Constructors
	 StepperControl();
	 StepperControl(int pinEnable, int pinDirecrion, int pinPulse, int pulsePerRotation, int ratio);				
	 void StepperControl::setRotationPulseCount(int count);
	 void StepperControl::setMachineCordinationRatio(int count);
	 void StepperControl::setPinDIR(int pin);
	 void StepperControl::setPinENA(int pin);
	 void StepperControl::setPinPUL(int pin);


private:

};


#endif

