/*
 * main.c
 *
 * Created: 2/3/2021 1:06:57 PM
 *  Author: teunl
 */ 

#include <xc.h>
#include <util/delay.h>

void wait( int ms )
/* 
short:            Busy wait number of millisecs
inputs:            int ms (Number of millisecs to busy wait)
outputs:    
notes:            Busy wait, not very accurate. Make sure (external)
                clock value is set. This is used by _delay_ms inside
                util/delay.h
*******************************************************************/
{
    for (int i=0; i<ms; i++) {
        _delay_ms( 1 );        // library function (max 30 ms at 8MHz)
    }
}


int main(void)
{
   
       DDRD = 0b11111111;            // All pins PORTD are set to output 

    while (1) {
        PORTD = 0x00;           
		wait( 5000 );
        PORTD = 0x60;          
		wait( 5000 );
    }

    

}