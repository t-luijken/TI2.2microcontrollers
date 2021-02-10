

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR( INT1_vect ) {
	if (PORTC == 0)
	{
		PORTC = 1;
	}else{
		 PORTC = PORTC << 1;	
	}
	
   	
}


ISR( INT2_vect ) {
	if (PORTC == 0)
	{
		PORTC = 0b10000000;
	}else{
		
    PORTC = PORTC >> 1;		
	}
}


int main( void ) {
	// Init I/O
	DDRC = 0xFF;
	DDRD = 0x00;			

	// Init Interrupt hardware
	
	
    EICRA |= 0b00101000;       //int2 fall int 1 fall
	
	EIMSK |= 0x06;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();				

	while (1) {

	}

	return 1;
}