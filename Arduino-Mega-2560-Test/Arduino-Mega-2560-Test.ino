
/*
滑台低电平向左()

主轴低电平向后退纱

*/

#include "StepperControl.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Liquidcrystal.h>
#include <math.h>
#include "Timer3.h"

#define pin_Stepper1_PUL 13
#define pin_Stepper1_DIR 12 //1右0左
#define pin_Stepper2_PUL 11
#define pin_Stepper2_DIR 10	//1进0退
#define pin_Stepper1_ENA 9
#define pin_Stepper2_ENA 8
#define pin_Switch1_TRIG 2
#define pin_Switch2_TRIG 3

#define pin_JOYSTICK_X A0
#define pin_JOYSTICK_Y A1
#define Frequency 16000000

LiquidCrystal_I2C lcd(0x27, 16, 2);
static double currentPositionX = 0;
static double currentPositionY = 0;
static double targetX = 0;
static double targetY = 0;
static double deltaX = 0;
static double deltaY = 0;
static int prescaler = 8;
//直线补差标记
static double Fi = 0;
//步进计数器
static long sigma = 0;
//运动方向标记
bool kx; //X轴运动方向标记 0:向左 1:向右
bool ky; //y轴运动方向标记 0：
Timer3 Timer_3;
StepperControl stepperx(pin_Stepper1_ENA, pin_Stepper1_DIR, pin_Stepper1_PUL, 400, 4);				//100脉冲周期前进1mm
StepperControl steppery(pin_Stepper2_ENA, pin_Stepper2_DIR, pin_Stepper2_PUL, 400, 1);				//360脉冲周期前进1圈

void setup()
{
	Timer3 Timer_3(14, 0, 0, 0);
	StepperControl stepperx(pin_Stepper1_ENA, pin_Stepper1_DIR, pin_Stepper1_PUL, 400, 4);				//100脉冲周期前进1mm
	StepperControl steppery(pin_Stepper2_ENA, pin_Stepper2_DIR, pin_Stepper2_PUL, 400, 1);
	currentPositionX = 0;
	currentPositionY = 0;
//	pinMode(pin_Stepper1_PUL, OUTPUT);
//	pinMode(pin_Stepper2_PUL, OUTPUT);
//	pinMode(pin_Stepper1_DIR, OUTPUT);
//	pinMode(pin_Stepper2_DIR, OUTPUT);

	DDRB |= (1<<DDB7)| (1 << DDB6) | (1 << DDB5) | (1 << DDB4);
//	digitalWrite(pin_Stepper1_ENA, LOW);
//	digitalWrite(pin_Stepper2_ENA, LOW);
//	digitalWrite(pin_Stepper1_PUL, LOW);
//	digitalWrite(pin_Stepper2_PUL, LOW);
	PORTB &= ~((1<<PORTB7)| (1 << PORTB6) | (1 << PORTB5) | (1 << PORTB4));
//	pinMode(pin_Stepper1_ENA, OUTPUT);
//	pinMode(pin_Stepper2_ENA, OUTPUT);
	DDRH |= (1 << DDH6) | (1 << DDH5);
	PORTH &= ~(1 << PORTH6)|(1<<PORTH5);

//	pinMode(pin_JOYSTICK_X, INPUT);
//	pinMode(pin_JOYSTICK_Y, INPUT);
	DDRF &= ~((1 << DDF0) | (1 << DDF1));

//	InterruptPins
	DDRE |= (1 << DDE4) | (1 << DDE5);
	EICRB |= (1 << ISC51) | (1 << ISC41);
	EICRB &= ~((1 << ISC50) | (1 << ISC40));
	EIMSK |= (1 << INT5) | (1 << INT4);
	Serial.begin(115200);

//	digitalWrite(pin_Stepper1_DIR,HIGH);
//	digitalWrite(pin_Stepper2_DIR,LOW);



	Timer_3.disable();
	lcd.init();
	Serial.println("Intitialization Complete");
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.backlight();
	lcd.print("INIT CMPLT");
															// enable all interrupts
}

void linearMoveTo(double tgtX,double tgtY, double time) {
	
	while (stepperx.isEnable|| steppery.isEnable ==1)
	{
		delay(5);
	}
	Fi = 0;
	deltaX = abs(tgtX - currentPositionX);
	deltaY = abs(tgtY - currentPositionY);
	if (deltaX+deltaY==0)
	{
		Serial.println("no movement needed");
		return;
	}
	//lcd.setCursor(0, 0);
	//lcd.print("stlmov stdby");
	//lcd.setCursor(0,1);
	//lcd.print(tgtX);
	//lcd.print(" ");
	//lcd.print(tgtY);
	
		Serial.print("try moving to ");
		Serial.print(tgtX);
		Serial.print(" ");
		Serial.println(tgtY);
		Serial.println(stepperx.isEnable);
	
	if (stepperx.isEnable)
	{
		//lcd.setCursor(0, 0);
		//lcd.print("stlmov stdby");
		while (stepperx.isEnable)
		{

		}

	}
	targetX = tgtX;
	targetY = tgtY;
	//Serial.println(currentPositionX);
	//Serial.println(currentPositionY);
	//Serial.println(targetX);
	//Serial.println(targetY);
	//第一象限直线
	if (currentPositionX <= targetX & currentPositionY <= targetY) 
	{
		kx = 1;
		ky = 1;
	}
	//第二象限直线
	if (currentPositionX > targetX & currentPositionY <= targetY) 
	{
		kx = 0;
		ky = 1;
	}
	//第三象限直线
	if (currentPositionX > targetX & currentPositionY > targetY)  
	{
		kx = 0;
		ky = 0;
	}
	//第四象限直线
	if (currentPositionX <= targetX & currentPositionY > targetY) 
	{
		kx = 1;
		ky = 0;
	}
	//设置两个电机的运行方向
	digitalWrite(stepperx.pinDIR, (int)kx);
	digitalWrite(steppery.pinDIR, (int)ky);
	Serial.println("Direction SET");
	long pulseneededX = abs(floor((targetX - currentPositionX) / stepperx.MachineCordinationRatio * stepperx.FullRotationPulseCount));
	long pulseneededY = abs(floor((targetY - currentPositionY) / steppery.MachineCordinationRatio * steppery.FullRotationPulseCount));
	
	Serial.print("targetX=");
	Serial.println(targetX);

	Serial.print("targetY=");
	Serial.println(targetY);

	Serial.print("pulseneededX=");
	Serial.println(pulseneededX);
	
	Serial.print("pulseneededY=");
	Serial.println(pulseneededY);
	
	double pwmPeriod = time / (pulseneededX + pulseneededY);
	
	Serial.println(pwmPeriod,10);


	int newtop = floor(pwmPeriod * Frequency / prescaler);
	Serial.print("newtop=");
	Serial.println(newtop);
	int newocr = ceil(newtop / 4);
	Serial.print("newOCR=");
	Serial.println(newocr);
	sigma = pulseneededX + pulseneededY;
	Serial.print("sigma=");
	Serial.println(sigma);
	if (newtop>65535| newtop<2)
	{
		Serial.println("TOPOVER/UNDERFLOW");
		return;
	}
//	Timer3 Timer_3(14,prescaler, newtop, newocr);
	Timer_3.setTOP(newtop);
	Timer_3.setOCR(newocr);
	Timer_3.setPrescaler(prescaler);
	TCNT3 = 0;
	Timer_3.enable();
	stepperx.isEnable = 1;
	sei();
}

ISR(TIMER3_COMPA_vect)
{
	if (sigma!=0)
	{
		if (currentPositionX==targetX|currentPositionY==targetY)
		{
			if (currentPositionX == targetX)
			{
				//digitalWrite(steppery.pinPUL, HIGH);
				PORTB |= (1<< PORTB7);
			}
			else
			{
				//digitalWrite(stepperx.pinPUL, HIGH);
				PORTB |= (1 << PORTB5);
			}

		}
		else
		{
			if (Fi >= 0)
			{
				//digitalWrite(stepperx.pinPUL, HIGH);
				PORTB |= (1 << PORTB7);
				Fi = Fi - deltaY;
			}
			else
			{
				//digitalWrite(steppery.pinPUL, HIGH);
				PORTB |= (1 << PORTB5);
				Fi = Fi + deltaX;
			}
		}
	}
}

ISR(TIMER3_OVF_vect)								//ISR that wraps a user defined function supplied by attachInterrupt
{
	//cli();
	//digitalWrite(stepperx.pinPUL, LOW);
	PORTB &= ~(1 << PORTB7);
	//digitalWrite(steppery.pinPUL, LOW);
	PORTB &= ~(1 << PORTB5);

	sigma--;
	if (sigma == 0)
	{
		currentPositionX = targetX;
		currentPositionY = targetY;
		//Serial.print(currentPositionX);
		//Serial.print(currentPositionY);
		//Serial.println("reached");
		Timer_3.disable();
		stepperx.isEnable = 0;
	}
	//sei();
}


void loop()
{
	START:
	//manualControl();
	
	linearMoveTo(10, 5, 1);
	linearMoveTo(0.0, 0.0, 1);
//	linearMoveTo(0, 0.1, 5);
//	linearMoveTo(0, 0, 5);
	


}

int sgn(int x)
{
	if (x == 0) //当x==0时，函数返回0
		return 0;
	else if (x > 0) //当x>0时，函数返回1
		return 1;
	else  //当x<0时，函数返回－1
		return -1;
}

void manualControl() 
{
	int offsetX_Joystick = map(analogRead(pin_JOYSTICK_X), 0, 1024, -100, 100);
	int offsetY_Joystick = map(analogRead(pin_JOYSTICK_Y), 0, 1024, -100, 100);
	int offset = sqrt(pow(offsetX_Joystick,2) + pow(offsetY_Joystick, 2));
	
	if (offset>2) 
	{
		if (offsetX_Joystick >= 50 & offsetY_Joystick>= 50) {
			linearMoveTo(currentPositionX + 0.1, currentPositionY + 0.1, 0.14);
		}
		if (offsetX_Joystick >= 50 & offsetY_Joystick <= -50) {
			linearMoveTo(currentPositionX + 0.1, currentPositionY - 0.1, 0.14);
		}
		if (offsetX_Joystick <= -50 & offsetY_Joystick >= 50) {
			linearMoveTo(currentPositionX - 0.1, currentPositionY + 0.1, 0.14);
		}
		if (offsetX_Joystick <= -50 & offsetY_Joystick <= -50) {
			linearMoveTo(currentPositionX - 0.1, currentPositionY - 0.1, 0.14);
		}
		if (offsetX_Joystick > 50 & abs(offsetY_Joystick) < 50) {
			linearMoveTo(currentPositionX + 0.1, currentPositionY,0.1);
		}
		if (offsetX_Joystick < -50 & abs(offsetY_Joystick) < 50) {
			linearMoveTo(currentPositionX - 0.1, currentPositionY, 0.1);
		}
		if (offsetY_Joystick > 50 & abs(offsetX_Joystick) < 50) {
			linearMoveTo(currentPositionX, currentPositionY+0.1, 0.1);
		}
		if (offsetY_Joystick < -50 & abs(offsetX_Joystick) < 50) {
			linearMoveTo(currentPositionX, currentPositionY-0.1, 0.1);
		}

	}
}

//PE4(2)触发中断 
ISR(INT4_vect) {
	currentPositionX = 0;
	currentPositionY = 0;
	targetX = 0;
	targetY = 0;
	linearMoveTo(10, 0, 5);
	currentPositionX = 0;
	currentPositionY = 0;
	targetX = 0;
	targetY = 0;
	Serial.println("X limit triggered, X position reset.");
	loop();

}
//PE5(3)触发中断 
ISR(INT5_vect) {
}

void FindZero() {
	Serial.println("Finding Zero point of X axis, please stand by...");
	while (true)
	{
		linearMoveTo(-999, 0, 500);

	}

}