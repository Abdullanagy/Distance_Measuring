/******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the AVR ULTRASONIC driver
 *
 * Author: Abdulla Nagy
 *
 *******************************************************************************/
#include"icu.h"
#include"gpio.h"
#include"ultrasonic.h"
#include "util/delay.h"

static volatile uint8 g_edgeCount = 0;
static volatile uint16 g_timeHigh = 0;

static void Ultrasonic_Trigger(void); /***********private function***********/

void Ultrasonic_init(void){

	    /* Create configuration structure for ICU driver */
	ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};

		/* Initialize ICU driver */
	ICU_init(&ICU_Configurations);
		/* Set the Call back function pointer in the ICU driver */
	ICU_setCallBack( Ultrasonic_edgeProcessing);

	    /* SET the bit of this port to input bin */
	GPIO_setupPinDirection(TRIGGER_PORT , TRIGGER_PIN, PIN_OUTPUT);

}

void Ultrasonic_Trigger(void){


	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT,TRIGGER_PIN, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void){

	uint16 distance=0 ;
	Ultrasonic_Trigger();

	while (g_edgeCount !=2); //wait the come back wave
	distance =(1+(g_timeHigh/58)); //calculate the distance
	g_edgeCount=0; //reset counter tick of timer


return distance;
}

void Ultrasonic_edgeProcessing(void){

	g_edgeCount++;

	if(g_edgeCount == 1)
		{
			/* Clear the timer counter register to start measurements from the
			 * first detected rising edge*/

			ICU_clearTimerValue();
			/* Detect falling edge */
			ICU_setEdgeDetectionType(FALLING);
		}
		else if(g_edgeCount == 2)
		{
			/* Store the High time value */
			g_timeHigh = ICU_getInputCaptureValue();

			/* Detect rising edge */
			ICU_setEdgeDetectionType(RAISING);

		}


}
