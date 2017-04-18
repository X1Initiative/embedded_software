#include <stdio.h>
#include <wiringPi.h>
#include "Motor.h"

void setup(Motor *self)	
{
	self->on = 1;
	
	wiringPiSetup ();
	int PULSE = 1000; 
	pinMode (PIN,OUTPUT);
	int arming_time; 
	for (arming_time = 0; arming_time < 200; arming_time++)
	{
		digitalWrite(PIN,HIGH); 
		delayMicroseconds(PULSE); 
		digitalWrite(PIN,LOW); 
		delay(20 - (PULSE/1000));
	}
}

void run(*Motor self)
{
	int i = 0;
	for (i = 0; i < 20; i++)	
	{
		int PULSE = self->pulse;
		digitalWrite(PIN,HIGH); 
		delayMicroseconds(PULSE); 
		digitalWrite(PIN,LOW); 
		delay(20 - (PULSE/1000));
	}
}

void off(*Motor self)
{
	self->on = 0;

	int PULSE = self->pulse;
	for (PULSE = PULSE; PULSE >= 1000; PULSE -= 100)
	{
	
		digitalWrite(PIN,HIGH); 
		delayMicroseconds(PULSE); 
		digitalWrite(PIN,LOW); 
		delay(20 - (PULSE/1000));
	}
}