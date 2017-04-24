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

#define TRIG 2
#define ECHO 8
 
void setup() {
        wiringPiSetup();
        pinMode(TRIG, OUTPUT);
        pinMode(ECHO, INPUT);
 
        //TRIG pin must start LOW
        digitalWrite(TRIG, LOW);
        delay(30);
}
 
int getCM() {
        //Send trig pulse
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(20);
        digitalWrite(TRIG, LOW);
 
        //Wait for echo start
        while(digitalRead(ECHO) == LOW)
        {
			printf("Hello"); 
		}
 
        //Wait for echo end
        long startTime = micros();
        while(digitalRead(ECHO) == HIGH);
        long travelTime = micros() - startTime;
 
        //Get distance in cm
        int distance = travelTime / 58;
 
        return distance;
}
 
int main(void) {
        setup();
 
        printf("Distance: %dcm\n", getCM());
 
        return 0;
}
