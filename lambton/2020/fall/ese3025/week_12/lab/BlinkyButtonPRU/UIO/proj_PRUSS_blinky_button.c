//
//      PRUSS Blinky-Button Project
//          A simple project to acquaint one with the AM335x PRUSS.
//          This is a host program that runs on the Beaglebone's Cortex-A core 
//      under Linux, and must be accompanied by two PRU assembly-language programs,
//      one written for PRU0, and the other for PRU1, described elsewhere in the project
//
//     author: Takis Zourntos (takis.zourntos@emads.org)
//     date: April 25, 2019
//

// libraries
#include<stdio.h>
#include<prussdrv.h>
#include<pruss_intc_mapping.h>

// definitions
#define PRU0	0
#define PRU1	1
#define MIN_DELAY               10*1000*(200/2) // a 10-ms is as short as it gets
#define MAX_DELAY               MIN_DELAY*1000 // a 10-second delay is as long as it gets


int main(void)
{
    unsigned int ret;
	// initialize interrupt data structure
	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

	// allocate and initialize memory
	prussdrv_init();

  /* Open PRU0 Interrupt */
	ret = prussdrv_open(PRU_EVTOUT_0);
	if (ret)
	{
		printf("prussdrv_open open failed\n");
		return (ret);
	}

	/* Open PRU1 Interrupt */
	ret = prussdrv_open(PRU_EVTOUT_1);
	if (ret)
	{
		printf("prussdrv_open open failed\n");
		return (ret);
	}

	// map PRU interrupts
	prussdrv_pruintc_init(&pruss_intc_initdata);

	// place the delay parameters into shared memory
	unsigned int initial_delay = 50*MIN_DELAY; // for a 200-MHz clock, this corresponds to 1 second
	prussdrv_pru_write_memory(PRUSS0_SHARED_DATARAM, 0, &initial_delay, 4);	// written at offset 0x00
	unsigned int min_delay = MIN_DELAY;
	prussdrv_pru_write_memory(PRUSS0_SHARED_DATARAM, 1, &min_delay, 4); 	// written at offset 0x04
	unsigned int max_delay = MAX_DELAY;
	prussdrv_pru_write_memory(PRUSS0_SHARED_DATARAM, 2, &min_delay, 4); 	// written at offset 0x08

	// place the initial exit status into shared memory, 0x0C-bytes after the delay
	unsigned int exit_status = 0; // this can be either 0 or not 0; 0 means keep going!
	prussdrv_pru_write_memory(PRUSS0_SHARED_DATARAM, 3, &exit_status, 4); 	// written at offset 0x0C

	// load and execute binary on PRU0
	prussdrv_exec_program(PRU0, "./PRUSS_blinky.bin");
	printf("PRU0 program initiated... \n");

	// load and execute binary on PRU1
	prussdrv_exec_program(PRU1, "./PRUSS_button.bin");
	printf("PRU1 program initiated... \n");

	// wait for PRU0 completion
	prussdrv_pru_wait_event(PRU_EVTOUT_0);
	printf("PRU0 program completed.\n");
	prussdrv_pru_clear_event (PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);
	
	// wait for PRU1 completion
	prussdrv_pru_wait_event(PRU_EVTOUT_1);
	printf("PRU1 program completed.\n");
	prussdrv_pru_clear_event (PRU_EVTOUT_1, PRU1_ARM_INTERRUPT);
	

	// disable PRUs, close memory mappings and exit from PRUSS
	prussdrv_pru_disable(PRU0);
	prussdrv_pru_disable(PRU1);
	prussdrv_exit();

	// exit from here
	return 0;
}
