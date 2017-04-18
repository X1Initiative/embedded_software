#include <stdio>
#include <stdlib>
#include <wiringPi>
#include <time>

//github test
//#define TRUE 1
 
int TRIG = 27;
int ECHO1A = 2;
int ECHO1B = 3;
int ECHO2A = 4;
int ECHO2B = 17;
int ECHO3A = 23;
int ECHO3B = 24;
int ECHO4A = 8;
int ECHO4B = 7;
 
void setup() {
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
        setup();
		clock_t t;
		t = clock();
		while ((clock() - t) < 30/CLOCKS_PER_SEC){
        printf("Distance: %dcm\n", getCM(ECHO1A),getCM(ECHO1B),getCM,(ECHO2A),getCM(ECHO2B),getCM(ECHO3A),getCM(ECHO3B),getCM(ECHO4A),getCM(ECHO4B));
		}
        return 0;
}
