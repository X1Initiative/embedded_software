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
/* Helper function for finding the max of two numbers */
int max(int x, int y)
{
    if(x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

/* left is the index of the leftmost element of the subarray; right is one
 * past the index of the rightmost element */
void merge_helper(int *input, int left, int right, int *scratch)
{
    /* base case: one element */
    if(right == left + 1)
    {
        return;
    }
    else
    {
        int i = 0;
        int length = right - left;
        int midpoint_distance = length/2;
        /* l and r are to the positions in the left and right subarrays */
        int l = left, r = left + midpoint_distance;

        /* sort each subarray */
        merge_helper(input, left, left + midpoint_distance, scratch);
        merge_helper(input, left + midpoint_distance, right, scratch);

        /* merge the arrays together using scratch for temporary storage */ 
        for(i = 0; i < length; i++)
        {
            /* Check to see if any elements remain in the left array; if so,
             * we check if there are any elements left in the right array; if
             * so, we compare them.  Otherwise, we know that the merge must
             * use take the element from the left array */
            if(l < left + midpoint_distance && 
                    (r == right || max(input[l], input[r]) == input[l]))
            {
                scratch[i] = input[l];
                l++;
            }
            else
            {
                scratch[i] = input[r];
                r++;
            }
        }
        /* Copy the sorted subarray back to the input */
        for(i = left; i < right; i++)
        {
            input[i] = scratch[i - left];
        }
    }
}

/* mergesort returns true on success.  Note that in C++, you could also
 * replace malloc with new and if memory allocation fails, an exception will
 * be thrown.  If we don't allocate a scratch array here, what happens? 
 *
 * Elements are sorted in reverse order -- greatest to least */

int mergesort(int *input, int size)
{
    int *scratch = (int *)malloc(size * sizeof(int));
    if(scratch != NULL)
    {
        merge_helper(input, 0, size, scratch);
        free(scratch);
        return 1;
    }
    else
    {
        return 0;
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
