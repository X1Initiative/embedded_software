#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
 
//#define TRUE 1
// Pins for wiring Pi are real fucked up. 
// Use the site below as hard reference for all pinouts while calling
// WiringPi Library. 
// http://wiringpi.com/pins/
//
//	To run:	gcc a.c -o test1 -lwiringPi
//			./test1

/* Code is currently working and up to date for sensor bed tests.
*/

#define TRIG 2
int ECHO[8] = {3,4,7,11,16,18,24,26};
int distance[8] = {0,0,0,0,0,0,0,0};
pthread_mutex_t lock;
 
void setup() {
        wiringPiSetup();
        
        // Setup TRIG as output
        pinMode(TRIG, OUTPUT);
        
        // Setup ECHO as input for each sensor
        pinMode(ECHO[0], INPUT);
        pinMode(ECHO[1], INPUT);
        pinMode(ECHO[2], INPUT);
        pinMode(ECHO[3], INPUT);
        pinMode(ECHO[4], INPUT);
        pinMode(ECHO[5], INPUT);
        pinMode(ECHO[6], INPUT);
        pinMode(ECHO[7], INPUT);
 
        //TRIG pin must start LOW
        digitalWrite(TRIG, LOW);
        delay(30);
}
 
/*
int getCM() {
        //Send trig pulse
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(20);
        digitalWrite(TRIG, LOW);
 
        char ECHO_test = 0x00;
        while(ECHO_test != 0xFF)
        {
			if (digitalRead(ECHO[0]) == HIGH)
			{
				ECHO_test += 1<<7; 
			}
			else if (digitalRead(ECHO[1]) == HIGH)
			{
				ECHO_test += 1<<6; 
			}
			else if (digitalRead(ECHO[2]) == HIGH)
			{
				ECHO_test += 1<<5; 
			}
			else if (digitalRead(ECHO[3]) == HIGH)
			{
				ECHO_test += 1<<4; 
			}
			else if (digitalRead(ECHO[4]) == HIGH)
			{
				ECHO_test += 1<<3; 
			}
			else if (digitalRead(ECHO[5]) == HIGH)
			{
				ECHO_test += 1<<2; 
			}
			else if (digitalRead(ECHO[6]) == HIGH)
			{
				ECHO_test += 1<<1; 
			}
			else if (digitalRead(ECHO[7]) == HIGH)
			{
				ECHO_test += 1; 
			}
		}
 
 
        //Wait for echo end
        long startTime = micros();
        while(digitalRead(ECHO) == HIGH);
        long travelTime = micros() - startTime;
 
        //Get distance in cm
        int distance = travelTime / 58;
 
        return distance;
}*/

void *get_CM(void *ptr)
{
   int *sensor_num;
   sensor_num = (int *) ptr;
   int index = *sensor_num - 1;
    
   printf("Printing Value for Thread Number: %d\n", *sensor_num);
   
   //Wait for echo start
   while (1)
   {
	   while(digitalRead(ECHO[index]) == LOW);
	   
	   //Wait for echo end
	   long startTime = micros();
	   while(digitalRead(ECHO[index]) == HIGH);
	   long travelTime = micros() - startTime;
	 
	   //Get distance in cm
	   distance[index] = travelTime / 58;
	}
}

 
int main(void) {
        setup();
		pthread_mutex_init (&lock,NULL);
		pthread_t thread[8];
		void *status;
		
		int order[8] = {1,2,3,4,5,6,7,8};
		int i, rc;
		for (i = 0; i < 8; i++) {
			rc = pthread_create(&thread[i], NULL, (void *) &get_CM, (void *) &order[i]);
			
			if (rc){
				printf("Error:unable to create thread, %d\n", rc);
			}
		}
		
		// Send pulse through TRIG for all sensors
		while (1) {
			digitalWrite(TRIG, HIGH);
			delayMicroseconds(20);
			digitalWrite(TRIG, LOW);
			delayMicroseconds(500);
		}
		
		for (i = 0; i < 8; i++) {
			rc = pthread_join(thread[i], &status);
			printf("Distance for sensor %d: %d\n", i, distance[i]);
			
			if (rc){
				printf("Error:unable to join, %d\n", rc);
			}
		}
		
        //printf("Distance: %dcm\n", getCM());
 
        return 0;
}
