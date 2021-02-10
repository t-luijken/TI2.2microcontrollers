

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );        // library function (max 30 ms at 8MHz)
	}
}

const unsigned char numbers [] = {
	//dPgfedcba
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111, //9
	0b01110111, //A
	0b01111100, //B
	0b00111001, //C
	0b01011110, //D
	0b01111001, //E
	0b01110001, //F
};



int main( void ) {
	// Init I/O
	DDRC = 0x00;
	DDRD = 0xFF;	
	
	int index = 0;
			
	while (1)
	{
		PORTD = numbers[index];
		
		if (index > 16)
		{
			wait(250);
			index = 0;
		}

		if (PINC == 0x01)
		{
			wait(250);
			index ++;
		}

		if (PINC == 0x02)
		{
			wait(250);
			index --;
		}

		if (PINC == 0x03)
		{
			wait(250);
			index = 0;
		}
		
	
	}

	return 1;
}