// 
// 
// 

#include "StepperControl.h"
#include "Arduino.h"

StepperControl::StepperControl()
{
}

 StepperControl::StepperControl(int pinEnable, int pinDirecrion, int pinPulse, int pulsePerRotation, int ratio)
{
	{
		this->pinENA = pinEnable;
		this->pinDIR = pinDirecrion;
		this->pinPUL = pinPulse;
		this->FullRotationPulseCount = pulsePerRotation;
		this->MachineCordinationRatio = ratio;
	}

}

 void StepperControl::setRotationPulseCount(int input) {
	 this->FullRotationPulseCount = input;
 }
 void StepperControl::setMachineCordinationRatio(int input) {
	 this->MachineCordinationRatio = input;
 }
 void StepperControl::setPinDIR(int pin) {
	 this->pinDIR = pin;
 }
 void StepperControl::setPinENA(int pin) {
	 this->pinENA = pin;
 }
 void StepperControl::setPinPUL(int pin) {
	 this->pinPUL = pin;
 }