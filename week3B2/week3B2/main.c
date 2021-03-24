/*
 * main.c
 *
 * Created: 2/10/2021 2:49:35 PM
 *  Author: teunl
 */ 

#include <xc.h>
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * counter_t2_interrupt.c
 *
 * Created: 21/02/2021 13:00:25
 * Author : Etienne
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h


volatile int TimerPreset = -1;  
volatile int tenthValue = 0;

// Interrupt routine timer2 overflow
ISR( TIMER2_OVF_vect ) {
	TCNT2 = TimerPreset;	
	tenthValue++;		   
	
		lcd_clear();
		
		char string[20];
		
		itoa(tenthValue,string,10);
		
		display_text(&string);
		//sprintf()
}

// Initialize timer2
void timer2Init( void ) {
	TCNT2 = TimerPreset;	
	TIMSK |= BIT(6);		
	sei();				    
	TCCR2 = 0x07;		    
}

int main(void) {
	
	init();
	
	DDRD &= ~BIT(7);		// PD7 op input: DDRD=xxxx xxx0
	
	//port a en b output
	DDRA = 0xFF;			
	DDRB = 0xFF;			
	
	timer2Init();
	

   lcd_clear();
   char string0[] = "0";
   display_text(&string0);

	while (1) {
		PORTA = TCNT2;		// show value counter 2
		PORTB = tenthValue;	// show value tenth counter	
		
		wait(10);
	}
}
