/*
 * main.c
 *
 * Created: 2/3/2021 1:13:55 PM
 *  Author: Rkoed
 */ 

#define F_CPU 8e6


#include <avr/io.h>
#include <util/delay.h>



/******************************************************************/
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

/******************************************************************/
int main( void ) {
/* 
short:            main() loop, entry point of executable
inputs:            
outputs:    
notes:            Looping forever, flipping bits on PORTD
*******************************************************************/

    DDRD = 0b11111111;            // All pins PORTD are set to output 
    DDRC = 0x00;

    while (1) {
        if (PINC == 0x01)
        {
            PORTD = 0x40;            // Write 01010101b PORTD
            wait(500);
            PORTD = 0x00;
            wait(500);

        } else {
            PORTD = 0x00;
                                
        }
    }
return 1;
}