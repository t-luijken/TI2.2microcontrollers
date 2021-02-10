/*
 * main.c
 *
 * Created: 2/3/2021 1:13:55 PM
 *  Author: Rkoed
 */ 

#define F_CPU 8e6


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
*******************************************************************/
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int startState (){
	if (PIND == 0x10)
	{
		return 2;
	}
	
	if (PIND == 0x20)
	{
		return 1;
	}
	return 0;
}

int S1State () {
	if (PIND == 0x40)
	{
		return 0;
	}
	
	if (PIND == 0x10)
	{
		return 2;
	}
	return 1;
}

int S2State(){
	if (PIND == 0x20)
	{
		return 1;
	}
	
	if (PIND == 0x10)
	{
		return 3;
	}
	
	if (PIND == 0x40)
	{
		return 0;
	}
	return 2;
}

int S3State (){
	if (PIND == 0x40)
	{
		return 0;
	}
	
	if (PIND == 0x10 || PIND == 0x20)
	{
		return 4;
	}
	return 3;
}

int EndState () {
	if (PIND == 0x40)
	{
		return 0;
	}
	return 4;
}

/******************************************************************/
int main( void ) {
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, flipping bits on PORTD
*******************************************************************/

	DDRD = 0x00;					// PORTD all output
	//int states[] = {0, 1, 2, 3, 4};
	int state = 0;
	while (1) {
	/*0 = start
	  1 = S1
	  2 = S2
	  3 = S3
	  4 = end*/
		switch (state)
		{
			case 0:
				state = startState();
				printf("%d", state);
				break;
				
			case 1:
				state = S1State();
				printf("%d", state);
				break;
			
			case 2:
				state = S2State();
				printf("%d", state);
				break;
				
			case 3:
				state = S3State();
				printf("%d", state);
				break;
				
			case 4:
				state = EndState();
				printf("%d", state);
				break;			
		}
		
	}
return 1;
}

