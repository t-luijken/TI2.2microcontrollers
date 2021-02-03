/*
 * main.c
 *
 * Created: 2/3/2021 2:34:09 PM
 *  Author: teunl
 */ 

#include <xc.h>
#include <util/delay.h>

void wait( int ms )

{
    for (int i=0; i<ms; i++) {
        _delay_ms( 1 );        
    }
}



int main(void)
{
	DDRD = 0xFF;
	
	
    while(1)
    {
	PORTD = 0x01;
     for(int i = 0; i < 7; i++ ){
		 	wait( 2500);
		PORTD =  PORTD << 1;
		
	 }
    }
	return 1;
}