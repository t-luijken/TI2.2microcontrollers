/*
 * main.c
 *
 * Created: 2/3/2021 1:13:55 PM
 *  Author: Rkoed
 */ 

#define F_CPU 8e6


#include <avr/io.h>
#include <util/delay.h>

typedef struct {
    unsigned char data;
    unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
    {0x00, 100}, {0x01, 100}, {0x02, 100}, {0x04, 100}, {0x10, 100}, {0x20, 100}, {0x40, 100}, {0x80, 100},
    {0x00, 100},
    {0xAA,  50}, {0x55,  50},
    {0xAA,  50}, {0x55,  50},
    {0xAA,  50}, {0x55,  50},
    {0x00, 100},
    {0x81, 100}, {0x42, 100}, {0x24, 100}, {0x18, 100}, {0x0F, 200}, {0xF0, 200}, {0x0F, 200}, {0xF0, 200},
    {0x00, 0x00}
};



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

    DDRD = 0b11111111;                    // PORTD all output
    
    while (1) {
        // Set index to begin of pattern array
        int index = 0;
        // as long as delay has meaningful content
        while( pattern[index].delay != 0 ) {
            // Write data to PORTD
            PORTD = pattern[index].data;
            // wait
            wait(pattern[index].delay);
            // increment for next round
            index++;
        }
    }
return 1;
}