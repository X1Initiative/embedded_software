#include <stdio.h>
#include <wiringPi.h>
#include "Motor.c"

struct Motor	{
	int on;
	int pin;
	int pulse;
	void (* setup)(Motor *this);
	void (* run)(Motor *this);
	void (* off)();
};