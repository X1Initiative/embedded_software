#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <pthread.h>

/* STATUS
 * Merge_sort seems to be broken for switching stuff in the zero place. 
 * This is most likely due to the other code because the sort works fine on
 * its own, just not in the rest of the code. 
 * Other than that, code is tested, and can send indivudla signals to all motors. 
 */


// Pulse for all motors set to 1000
int global_PULSE[4]     = {1000,1000,1000,1000};
int order[4]            = {0,1,2,3};
int buffer[4]           = {0,0,0,0};
int buffer2[4]          = {0,0,0,0};
int difference[4]   	= {0,0,0,0};
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
    // Speed controller expects to see low thruttle signal on startup
    // This corresponds to 1ms on, 19ms off.
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
void merging(int *copy, int low, int mid, int high) {
    int l1, l2, i;


    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
        if(copy[l1] <= copy[l2])
        {
            buffer[i] = copy[l1];
            buffer2[i] = order[l1];
            l1++;
        }
        else
        {
            buffer[i] = copy[l2];
            buffer2[i] = order[l2];
            l2++;
        }
    }

    while(l1 <= mid)
    {
        buffer[i] = copy[l1];
        buffer2[i]= order[l1];
        i++;l1++;
    }
    while(l2 <= high)
    {
        buffer[i] = copy[l2];
        buffer2[i] = order[l2];
        i++;l2++;
    }

    for(i = low; i <= high; i++)
    {
        copy[i] = buffer[i];
        order[i] = buffer2[i];
    }
}

void sort(int *copy, int low, int high) {
    int mid;
    order[0] = 0;order[1] = 1;order[2] = 2;order[3]=3;

    if(low < high)
    {
        mid = (low + high) / 2;
        sort(copy, low, mid);
        sort(copy, mid+1, high);
        merging(copy, low, mid, high);
   }
   else
   {
      return;
   }
}


void input_wait(void *ptr)
{
    int *current_val;
    current_val = (int *) ptr;
    int copy[4];

    while (1)
    {
        pthread_mutex_lock(&lock);
        printf("Enter New Value:");
        // Input value in format 1000 1000 1000 1000
		scanf("%d %d %d %d", &copy[0], &copy[1], &copy[2], &copy[3]);
        pthread_mutex_unlock(&lock);
        sort(copy,0,3);
        int i;
        for (i = 0; i < 3; i++)
        {
			difference[i] = copy[i+1]-copy[i];
		}
        for (i = 0; i < 4; i++)
        {		
			printf("%d ",order[i]);
		}
		for (i = 0; i < 4; i++)
        {
			global_PULSE[i] = copy[i];
		}
		printf("\n");

        // perform calcs here to set output values for the order of which motors will be turned off
        // along with their speeds.
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

        //Adjust code here to deal with new algorithm of starting with the greatest
        // pulse, and waiting after each one so that all are sinked up.

        // all motors start at same time.
        // motors turn off from low throttle -> high throttle.

		digitalWrite(PIN[order[0]],HIGH);
		digitalWrite(PIN[order[1]],HIGH);
		digitalWrite(PIN[order[2]],HIGH);
		digitalWrite(PIN[order[3]],HIGH);

		delayMicroseconds(global_PULSE[0]);
		digitalWrite(PIN[order[0]],LOW);
        delayMicroseconds(difference[0]);
		digitalWrite(PIN[order[1]],LOW);
        delayMicroseconds(difference[1]);
		digitalWrite(PIN[order[2]],LOW);
        delayMicroseconds(difference[2]);
		digitalWrite(PIN[order[3]],LOW);

		delay(20 - (global_PULSE[3]/1000));
    }

    pthread_join(thread,NULL);

    printf("\nCurrent: %d\n", global_PULSE);

    return (0);

}
