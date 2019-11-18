/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "sys/alt_irq.h"
#include "system.h"




int main()
{
	char str  = 0;

	FILE* stream_UART;
	stream_UART = fopen ("/dev/uart", "r+");
	if (stream_UART == NULL)
	{
		printf("Nao foi criada stream UART");
	}
	printf("Hello from Nios II!\n");

	while(1)
	{
		str = getc(stream_UART);
		fprintf(stream_UART, "NIOS II Task1 from uart %c \n ",str);
	}

	printf("Hello from Nios II!\n");

	return 0;
}
