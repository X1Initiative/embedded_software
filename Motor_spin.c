#include <stdio.h>
#include <wiringPi.h>
#include <time.h>


int PIN = 7; 

void setup()
{
	
	wiringPiSetup (); 
	int PULSE = 1000; 
	pinMode (PIN,OUTPUT);
	int arming_time; 
	digitalWrite(PIN,HIGH);
	
	for (arming_time = 0; arming_time < 200; arming_time++)
	{
		digitalWrite(PIN,HIGH); 
		delayMicroseconds(PULSE); 
		digitalWrite(PIN,LOW); 
		delay(20 - (PULSE/1000));
		printf("Here");
	}
}

void sample()
{
	int PULSE = 1000; 
	for (PULSE = 1000; PULSE <= 2000; PULSE+=10)
	{
		digitalWrite(PIN,HIGH); 
		delayMicroseconds(PULSE); 
		digitalWrite(PIN,LOW); 
		delay(20 - (PULSE/1000));
	}
	
	for (PULSE = PULSE; PULSE >= 1000; PULSE -= 10)
	{
	
		digitalWrite(PIN,HIGH); 
		delayMicroseconds(PULSE); 
		digitalWrite(PIN,LOW); 
		delay(20 - (PULSE/1000));
	}	
}
int main(void)
{
	setup(); 
	while (1)
	{
		sample();
	}
	return(0);		
}
