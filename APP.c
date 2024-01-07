/******************************************************************************
 *
 * Layer: Application
 *
 * File Name: App.c
 *
 * Description: Source file for the Application Layer
 *
 * Author: Abdulla Nagy
 *
 *******************************************************************************/


#include"ultrasonic.h"
#include"avr/io.h"

int main (void){

uint16 distance=0 ;

/* Enable Global Interrupt I-Bit */
SREG |= (1<<7);

/* Initialization LCD and Ultra_sonic Sensor */
Ultrasonic_init();
LCD_init();

/* Display on the LCD */
LCD_displayString("Distance =    CM");
LCD_moveCursor(2,0);
LCD_displayString("Free Palestine");

			while(1)
			{
				distance = Ultrasonic_readDistance(); /* Read The Measured Distance */

				LCD_moveCursor(0, 11);

				/* Display The Measured Distance on LCD */

				if(distance >= 100)
				{
					LCD_intgerToString(distance);
				}
				else if((distance < 100) && (distance>=10))
				{
					LCD_intgerToString(distance);
					LCD_displayCharacter(' ');
				}
				else
				{
					LCD_intgerToString(distance);
					LCD_displayCharacter(' ');
				}
			}


	}

