/*Salma Mobasher
8120214
Due: Feb 22, 2021

Task create makes an instance of a task.
*/
/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "supporting_functions.h"

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT	( 0xffffff )

static const char* eStateString[] =
{
"eRunning", /* A task is querying the state of itself, so must be running. */
"eReady", /* The task being queried is in a read or pending ready list. */
"eBlocked", /* The task being queried is in the Blocked state. */
"eSuspended",
"eDeleted",
"eInvalid"
};

TaskHandle_t xHandlerTask1 = NULL;
TaskHandle_t xHandlerTask2 = NULL;

/* The task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );
void vTask3(void *pvParameters);
void vTask4(void *pvParameters);

/*-----------------------------------------------------------*/

int main( void )
{
	
	/* Create one of the two tasks. */
	xTaskCreate(	vTask1,		/* Pointer to the function that implements the task. */
					"Task 1",	/* Text name for the task.  This is to facilitate debugging only. */
					1000,		/* Stack depth - most small microcontrollers will use much less stack than this. */
					NULL,		/* We are not using the task parameter. */
					1,			/* This task will run at priority 1. */
		&xHandlerTask1);		/*handle */

	/* Create the other task in exactly the same way. */
	xTaskCreate( vTask2, "Task 2", 1000, NULL, 2, &xHandlerTask2);
	xTaskCreate(vTask3, "Task 3", 1000, NULL, 3, NULL);
	xTaskCreate(vTask4, "Task 4", 1000, NULL, 3, NULL);

	/* Start the scheduler to start the tasks executing. */
	vTaskStartScheduler();	

	/* The following line should never be reached because vTaskStartScheduler() 
	will only return if there was not enough FreeRTOS heap memory available to
	create the Idle and (if configured) Timer tasks.  Heap management, and
	techniques for trapping heap exhaustion, are described in the book text. */
	for( ;; );


	return 0;
}


/*************************************************************/

void vTask1( void *pvParameters )
{
const char *pcTaskName = "Task 1 is running\r\n";
volatile uint32_t ul;
const char *statess;
eTaskState taskState;
taskState = eTaskGetState(xHandlerTask2);
statess = eStateString[taskState]; //print the state
	
	for( int i=0;i<20; i++ ) /////////////////////////so now the loop is only running 20 times
	{
		/* Print out the name of this task. */
		vPrintString( pcTaskName );
		vPrintString(statess);
		
	}
}
/*-----------------------------------------------------------*/

void vTask2( void *pvParameters )
{
const char *pcTaskName = "Task 2 is running\r\n";
volatile uint32_t ul;
const char *statess;
TickType_t xLastWakeTime;
eTaskState taskState;
const TickType_t xFrequency = 250; //250ms delay
// Initialise the xLastWakeTime variable with the current time.
xLastWakeTime = xTaskGetTickCount();
vTaskDelayUntil(&xLastWakeTime, xFrequency);
	for(int i = 0; i < 20; i++) //////////////So now the loop is only running 20 times 
	{
		/* Print out the name of this task. */
		vPrintString(pcTaskName);
		taskState = eTaskGetState(xHandlerTask1); //get state of the other
		statess= eStateString[taskState]; //print the state
		vPrintString(statess);
	}
}

void vTask3(void *pvParameters) /////////////please pass the task name using the task parameters
{
	const char *pcTaskName = "Task 3 is running\r\n";
	volatile uint32_t ul;
        TickType_t xLastWakeTime;
        const TickType_t xFrequency = 500;
        // Initialise the xLastWakeTime variable with the current time.
        xLastWakeTime = xTaskGetTickCount ();
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	for (int i = 0; i < 20; i++) //////////////So now the loop is only running 20 times 
	{
		/* Print out the name of this task. */
		vPrintString(pcTaskName);
	}
}

void vTask4(void *pvParameters) 
{
	const char *pcTaskName = "Task 4 is running\r\n";
	volatile uint32_t ul;
       TickType_t xLastWakeTime;
        const TickType_t xFrequency = 500;
        // Initialise the xLastWakeTime variable with the current time.
        xLastWakeTime = xTaskGetTickCount ();
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	for (int i = 0; i < 20; i++) //////////////So now the loop is only running 20 times 
	{
		/* Print out the name of this task. */
		vPrintString(pcTaskName);


	}
}



