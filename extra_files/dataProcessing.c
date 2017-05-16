#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "Motor.h"

#define NUM_MOTORS 1


*void motorThreadFunction(*void motor)
{
	struct Motor *my_motor = (struct Motor*)motor;

	// Setup motor
	my_motor->setup();

	// Run motor on loop
	while(1)
	{
		// Check for stop flag
		if (my_motor->on)
		{
			my_motor->off();
			break;
		}

		// Continue running
		my_motor->run();
	}
}

*void dataProcessingThreadFunction(*void motors)
{
	// On inifinite loop
	// Get user input
	// Change pulse to user input
	struct Motor *my_motors = (struct Motor*)motors;

	while(1)
	{
		char line[256];
		int i;
		if (fgets(line, sizeof(line), stdin)) {
			 if (strlen(line) == 6) {
				// Cast to int and check first character == 1,2,3,4
				int motor_num = (line[0] - '0');
				if (motor_num > 0 && motor_num < 5){
					int p = 0;
					for (int i = 2; i < 6; i++) {
						p = p * 10 + (line[i] - '0');
					}

					 // Check that pulse is between 1000 <-> 2000
					if (p >= 1000 && p <= 2000) {
						my_motor[motor_num].pulse = p;
					}
				}
			}
		}
	}
}

int main()
{
	// Initialize motors
	Motor motors[NUM_MOTORS];

	// Create motor threads
	pthread_t motor_threads[NUM_MOTORS];
	for (int i = 0; i < NUM_MOTORS; i++)
	{
		printf("Starting motor (%d)\n", i+1);

		motors[i].pin = 7 + i;
		motors[i].pulse = 1000;
		int result = pthread_create(&motor_threads[i]; NULL, &motorThreadFunction, &motors[i]);
		if (result != 0)	{
			fprintf(stderr, "Could not open motor thread %d. Error code: %d\n", i, result);
			exit(-1);
		}
	}

	pthread_t *data_processing_thread;
	int dp_result = pthread_create(data_processing_thread; NULL, &dataProcessingThreadFunction, motors);
	if (dp_result != 0)	{
			fprintf(stderr, "Could not open data processing thread. Error code: %d\n", result);
			exit(-1);
		}

	// Wait for motor threads
	for (int i = 0; i < NUM_MOTORS; i++)	{
		int result = pthread_join(motor_threads[i], NULL);
		if (result != 0)	{
			fprintf(stderr, "Error joining motor thread: %d. Error code: %d\n", i, result);
			exit(-1);
		}
	}

	// Wait for data processing thread
	dp_result = pthread_join(data_processing_thread, NULL);
		if (dp_result != 0)	{
			fprintf(stderr, "Error joining data processing thread. Error code: %d\n", dp_result);
			exit(-1);
		}
}
