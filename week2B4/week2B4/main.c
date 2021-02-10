

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );        // library function (max 30 ms at 8MHz)
	}
}

const unsigned int numbers [] = {
	//dPgfedcba
	0b00000001, //0
	0b00000010, //1
	0b00000100, //2
	0b00001000, //3
	0b00010000, //4
	0b00100000, //5
	0b01000000, //6
	0b00000011, //7
	0b00000110, //8
	0b00001100, //9
	0b00011000, //A
	0b00110000, //B
	0b01100000, //C
	0b00000111, //D
	0b00001110, //E
	0b00011100, //F
	0b00111000,
	0b01110000,
	0b00011110,
	0b00111100,
	0b01111000,
	0b00011111,
	0b00111110,
	0b01111100,
	0b00111111,
	0b01111110,
	0b01111111,
};



int main( void ) {
	// Init I/O
	
	DDRD = 0xFF;
	
	
	
	while (1)
	{
	for (int i =0; i<27; i++)
	{
		PORTD = numbers[i];
		wait( 250 );
		
	}
	
	
	}

	return 1;
}