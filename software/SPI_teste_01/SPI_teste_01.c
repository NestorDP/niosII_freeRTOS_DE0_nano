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

#include <stdio.h>

#include <altera_avalon_spi.h>
#include <altera_avalon_spi_regs.h>
#include "system.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"

char edge_capture_ptr;
alt_u32 status;

static void spi_ISR(void* context, alt_u32 id)
{
	printf("SPI INTERRUPT DETECTED!\n");

	IOWR_ALTERA_AVALON_SPI_CONTROL(SPI_BASE, 0);


	//*edge_capture_ptr = (volatile int*) context;
	edge_capture_ptr = IORD_ALTERA_AVALON_SPI_RXDATA(SPI_BASE);

	//reset the interrupt flags
	IOWR_ALTERA_AVALON_SPI_STATUS(SPI_BASE, 0x10);

	//reset flags
	IOWR_ALTERA_AVALON_SPI_CONTROL(SPI_BASE, ALTERA_AVALON_SPI_CONTROL_SSO_MSK | ALTERA_AVALON_SPI_CONTROL_IRRDY_MSK);
}



int main()
{
  printf("Hello from Nios II!\n");


  //enable receive interrupt

  IOWR_ALTERA_AVALON_SPI_STATUS(SPI_BASE, 0x0);

  //reset flags
  IOWR_ALTERA_AVALON_SPI_CONTROL(SPI_BASE, ALTERA_AVALON_SPI_CONTROL_SSO_MSK | ALTERA_AVALON_SPI_CONTROL_IRRDY_MSK);

  //when status flag and control flag are both 1 interrupt occurs
  alt_irq_register(SPI_IRQ, NULL, spi_ISR);





  while(1){
	  while (!(IORD_ALTERA_AVALON_SPI_STATUS(SPI_BASE) & ALTERA_AVALON_SPI_STATUS_TRDY_MSK));

	    IOWR_ALTERA_AVALON_SPI_TXDATA(SPI_BASE,'D');
  }

  return 0;
}


