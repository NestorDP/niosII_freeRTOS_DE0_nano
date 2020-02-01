/*
 *
 * [File Name]     hello_world.c
 * [Platform]      DE0-nano
 * [Project]       NiosII & FreeRTOS
 * [Version]       1.00
 * [Author]        ea.rincon11
 * [Date]          24/07/2017
 * [Language]      'C'
 * [History]       1.20 - Edited from original file included in FreeRTOS V9.0.0 Nios Example
 */
//-----------------------------------------------------------------------
// Standard C/C++ Includes
//-----------------------------------------------------------------------
#include <stddef.h>
#include <stdio.h>
#include <string.h>
//-----------------------------------------------------------------------
// Scheduler Includes
//-----------------------------------------------------------------------
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "partest.h"
//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/* The rate at which the Print out message controlled by the 'Task1' */
#define mainTASK1_PERIOD	( 500 )
/* The rate at which the Print out message controlled by the 'Task2' */
#define mainTASK2_PERIOD	( 1000 )

/* Priority definitions for the tasks in the demo application. */
#define mainTASK1_PRIORITY		( tskIDLE_PRIORITY + 1 )
/* Priority definitions for the tasks in the demo application. */
#define mainTASK2_PRIORITY		( tskIDLE_PRIORITY + 2 )
//-----------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------
static void prvPrintTask1( void *pvParameters );
static void prvPrintTask2( void *pvParameters );
//-----------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------
int main()
{
	//
	// Configure any hardware required for this demo.
	//
	vParTestInitialise();

	printf("Hello from Nios II!\n");

	//
	//prvPrintTask1 uses sprintf so requires more stack.
	//
	xTaskCreate( prvPrintTask1, "Task1", configMINIMAL_STACK_SIZE, NULL, mainTASK1_PRIORITY, NULL );

	//
	// prvPrintTask2 uses sprintf so requires more stack.
	//
	xTaskCreate( prvPrintTask2, "Task2", configMINIMAL_STACK_SIZE, NULL, mainTASK2_PRIORITY, NULL );

	//
    //Finally start the scheduler.
	//
	vTaskStartScheduler();

	//
	// Will only reach here if there is insufficient heap available to start the scheduler.
	//
	for( ;; );

  return 0;
}
/*-----------------------------------------------------------*/
static void prvPrintTask1( void *pvParameters )
{
	FILE* stream_UART;
	stream_UART = fopen ("/dev/uart", "w");
	if (stream_UART == NULL)
	{
		printf("Nao foi criada stream UART");
	}
	for( ;; )
	{
		/* Wait until it is time to run the tests again. */
		vTaskDelay( mainTASK1_PERIOD / portTICK_PERIOD_MS);

        /* Print out an message */
        printf( "NIOS II Task1 from jtag\r\n" );
        fprintf(stream_UART, "NIOS II Task1 from uart\r\n ");
        /*Control LED 1 DE0-NANO*/
        vParTestToggleLED(1);
	}
}
/*-----------------------------------------------------------*/
static void prvPrintTask2( void *pvParameters )
{
	char str[10];

	FILE* stream_UART;
	stream_UART = fopen ("/dev/uart", "w");
	if (stream_UART == NULL)
	{
		printf("Nao foi criada stream UART");
	}

	for( ;; )
	{
		/* Wait until it is time to run the tests again. */
		vTaskDelay( mainTASK2_PERIOD / portTICK_PERIOD_MS);

		fscanf(stream_UART,"%s",&str);

        /* Print out an message */
        printf("NIOS II Task2 %s\r\n", str );

        /*Control LED 2 DE0-NANO*/
        vParTestToggleLED(2);
	}
}
/*-----------------------------------------------------------*/

