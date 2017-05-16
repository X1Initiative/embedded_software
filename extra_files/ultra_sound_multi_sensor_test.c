#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>

//#define TRUE 1
 
int TRIG = 13;
int ECHO1A = 3;
int ECHO1B = 4;
int ECHO2A = 7;
int ECHO2B = 11;
int ECHO3A = 16;
int ECHO3B = 18;
int ECHO4A = 24;
int ECHO4B = 26;
 
void setup() {
	printf("Hello");
        wiringPiSetup();
        pinMode(TRIG, OUTPUT);
        pinMode(ECHO1A, INPUT);
		pinMode(ECHO1B, INPUT);
		pinMode(ECHO2A, INPUT);
		pinMode(ECHO2B, INPUT);
		pinMode(ECHO3A, INPUT);
		pinMode(ECHO3B, INPUT);
		pinMode(ECHO4A, INPUT);
		pinMode(ECHO4B, INPUT);
 
        //TRIG pin must start LOW
        digitalWrite(TRIG, LOW);
        delay(30);
}
 
int getCM(int ECHO) {
        //Send trig pulse
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(20);
        digitalWrite(TRIG, LOW);
 
        //Wait for echo start
        while(digitalRead(ECHO) == LOW);
 
        //Wait for echo end
        long startTime = micros();
        while(digitalRead(ECHO) == HIGH);
        long travelTime = micros() - startTime;
 
        //Get distance in cm
        int distance = travelTime / 58;
 
        return distance;
}
 
int main(void) {
	printf("Setting up\n");
        setup();
		/*clock_t t;
		t = clock();
		printf("%Lf", (long double)(t));
		while ((clock() - t)/CLOCKS_PER_SEC < 30.0/CLOCKS_PER_SEC){
printf("looping\n");
        printf("Distance: %dcm\n", getCM(ECHO1A),getCM(ECHO1B),getCM,(ECHO2A),getCM(ECHO2B),getCM(ECHO3A),getCM(ECHO3B),getCM(ECHO4A),getCM(ECHO4B));
		}*/
	printf("Distance: %dcm", getCM(ECHO1A));


        return 0;
}