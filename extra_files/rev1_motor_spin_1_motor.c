#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <pthread.h>



int global_PULSE = 1000;
int PIN = 7; 	
pthread_mutex_t lock;
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
        scanf("%d",current_val);
        pthread_mutex_unlock(&lock);
    }
}

// Main takes initial input for
int main()
{
    setup();

    pthread_mutex_init (&lock,NULL);
    printf("Enter Starting Motor Pulse Speed in MicroSecond: ");
    scanf("%d",&global_PULSE);
    pthread_t thread;
    pthread_create(&thread, NULL, (void *) &input_wait, (void *) &global_PULSE);

    int test = global_PULSE;
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

    		digitalWrite(PIN,HIGH);
    		delayMicroseconds(global_PULSE);
    		digitalWrite(PIN,LOW);
    		delay(20 - (global_PULSE/1000));
    	
    	
        
    }

    pthread_join(&thread,NULL);

    printf("\nCurrent: %d\n", global_PULSE);

    return (0);

}
