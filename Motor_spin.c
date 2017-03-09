
#include <stdio.h>
#include <wiringPi.h>

int PIN = 7; 

void setup()
{
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

void sample()
{
	int PULSE = 1000; 
	for (PULSE = 1000; PULSE <= 1900; PULSE++)
	{
		digitalWrite(PIN,HIGH); 
		delayMicroseconds(PULSE); 
		digitalWrite(PIN,LOW); 
		delay(20 - (PULSE/1000));
		if (PULSE == 1250 || PULSE == 1500 || PULSE == 1750)
		{
			printf("STEP\n");
		}
		
	}
	
	for (PULSE = PULSE; PULSE >= 1000; PULSE -= 100)
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




