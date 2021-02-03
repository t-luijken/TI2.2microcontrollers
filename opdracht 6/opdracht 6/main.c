/*
 * main.c
 *
 * Created: 2/3/2021 3:05:29 PM
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
	 int freqState = 0;
	 int states[] = {1000,4000};
	 int pressed = 0;
	
	
	
	DDRD = 0xFF;
	DDRC = 0x00;
	
    while(1)
    {
        if ((PINC == 0x01))
        {
			if (pressed == 0)
			{
				pressed = 1;
				if (freqState == 0)
				{
					freqState = 1;
					}else{
					freqState = 0;
				}
			}
			
        }else{
			pressed = 0;
		}
		
		PORTD = 0x40;
		wait(states[freqState]);
		PORTD = 0x00;
		wait(states[freqState]);
		
    }
	return 1;
}