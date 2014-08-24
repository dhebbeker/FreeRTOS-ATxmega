/*
 * main.c
 *
 * Created: 24.8.2014 15:10:04
 *  Author: klaxalk
 */ 


#include <avr/io.h>
#include <util/delay.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "ioport.h"

#define BLINK_DELAY_MS 1000

// RED LED on PORTA-4
#define	RED	IOPORT_CREATE_PIN(PORTA, 4)

// YELLOW LED on PORTA-0
#define	YELLOW	IOPORT_CREATE_PIN(PORTA, 0)

void blink1(void *p) {
	
	while (1) {
		
        ioport_set_pin_level(RED, true);
		vTaskDelay(1000);
        ioport_set_pin_level(RED, false);
        vTaskDelay(1000);
	}
}

void blink2(void *p) {
	
	while (1) {
		
		ioport_set_pin_level(YELLOW, true);
		vTaskDelay(100);
		ioport_set_pin_level(YELLOW, false);
		vTaskDelay(100);
	}
}

int main(void)
{	
	
	// prepare the i/o for LEDs
	ioport_init();
	ioport_set_pin_dir(RED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(YELLOW, IOPORT_DIR_OUTPUT);
			
	// start tasks
	xTaskCreate(blink1, (signed char*) "blink1", 1024, NULL, 1, NULL);
	xTaskCreate(blink2, (signed char*) "blink2", 1024, NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	return 0;
}