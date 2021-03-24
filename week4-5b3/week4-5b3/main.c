#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include <stdio.h>
#include <stdlib.h>

#define BIT(x)    (1 << (x))




// Initialize ADC:
void adcInit( void )
{
	ADMUX = 0b11100001;            // AREF=2,56 V, result left adjusted, channel1 at pin PF1
	
	ADCSRA = 0b10000110;        // ADC-enable, no interrupt, no free running, division by 64
}


// Main program: Counting on T1
int main( void )
{
	
	DDRF = 0x00;                    // set PORTF for input (ADC)
	DDRA = 0xFF;                    // set PORTA for output
	adcInit();                        // initialize ADC
	init();
	
	while (1)
	{
		lcd_clear();
		ADCSRA |= BIT(6);                // Start ADC
		while ( ADCSRA & BIT(6) ) ;        // Wait for completion
		PORTA = ADCH;                    // Show MSB (bit 9:2) of ADC
		
		int temp = 2* (2 + ADCH);
		
		char str[20];
		
		itoa(temp, str, 10);
		
		display_text(&str);
		wait(5000);                        // every 50 ms (busy waiting)
	}
}