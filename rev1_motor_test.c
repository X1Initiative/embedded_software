#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <pthread.h>


// Pulse for all motors set to 1000
int global_PULSE[4] = {1000};
// Pins for all motors
int PIN[4]= {7,0,2,3}; 	
pthread_mutex_t lock;

void setup()
{
	wiringPiSetup (); 
	int PULSE = 1000; 
	
	// Setup all motors	
	pinMode (PIN[0],OUTPUT);
	digitalWrite(PIN[0],HIGH);
	pinMode (PIN[1],OUTPUT);
	digitalWrite(PIN[1],HIGH);
	pinMode (PIN[2],OUTPUT);
	digitalWrite(PIN[2],HIGH);
	pinMode (PIN[3],OUTPUT);
	digitalWrite(PIN[3],HIGH);

	// Arm all motors.
	int arming_time;
	for (arming_time = 0; arming_time < 200; arming_time++)
	{
		digitalWrite(PIN[0],HIGH);
		digitalWrite(PIN[1],HIGH);
		digitalWrite(PIN[2],HIGH); 
		digitalWrite(PIN[3],HIGH);
		 
		delayMicroseconds(PULSE);
		
		digitalWrite(PIN[0],LOW);
		digitalWrite(PIN[1],LOW);
		digitalWrite(PIN[2],LOW);
		digitalWrite(PIN[3],LOW);
		 
		delay(20 - (PULSE/1000));
	}
}

void input_wait(void *ptr)
{
    int *current_val;
    current_val = (int *) ptr;

    while (1)
    {
        pthread_mutex_lock(&lock);
        printf("Enter New Value:");
        // Input value in format 1000 1000 1000 1000
		scanf("%d %d %d %d", &current_val[0], &current_val[1], &current_val[2], &current_val[3]);
        pthread_mutex_unlock(&lock);
    }
}

// Main takes initial input for
int main()
{
    setup();
	
    pthread_mutex_init (&lock,NULL);
    
    // Input initial pulse
    int PULSE;
    printf("Enter Starting Motor Pulse Speed in MicroSecond: ");
    scanf("%d",&PULSE);
    // Update pulse for all motors
    global_PULSE[0] = PULSE;
    global_PULSE[1] = PULSE;
    global_PULSE[2] = PULSE;
    global_PULSE[3] = PULSE;
    
    pthread_t thread;
    pthread_create(&thread, NULL, (void *) &input_wait, (void *) &global_PULSE);

    //int test = global_PULSE;
    while (1)
    {
        //This code here will run on an infinite loop until the program stops
        // The Threaded function will continue to look for new inputs
        // test code below.
        
        /* Test code: Not for use. 
        if (test != global_PULSE)
        {
            test = global_PULSE;
            pthread_mutex_lock(&lock);
            printf("New Pulse being run: %d\n",global_PULSE);
            pthread_mutex_unlock(&lock);
        }*/
        
			digitalWrite(PIN[0],HIGH);
			digitalWrite(PIN[1],HIGH);
			digitalWrite(PIN[2],HIGH);
			digitalWrite(PIN[3],HIGH);

			delayMicroseconds(global_PULSE[0]);
			delayMicroseconds(global_PULSE[1]);
			delayMicroseconds(global_PULSE[2]);
			delayMicroseconds(global_PULSE[3]);
			
			digitalWrite(PIN[0],LOW);
			digitalWrite(PIN[1],LOW);
			digitalWrite(PIN[2],LOW);
			digitalWrite(PIN[3],LOW);
			
			delay(20 - (global_PULSE[0]/1000));
			delay(20 - (global_PULSE[1]/1000));
			delay(20 - (global_PULSE[2]/1000));
			delay(20 - (global_PULSE[3]/1000));
    }

    pthread_join(thread,NULL);

    printf("\nCurrent: %d\n", global_PULSE);

    return (0);

}
