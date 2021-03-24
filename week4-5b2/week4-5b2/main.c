#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)    (1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );            // library function (max 30 ms at 8MHz)
	}
}


// Initialize ADC:
void adcInit( void )
{
	ADMUX = 0b11100001;            
	ADCSRA = 0b10000110;        
}



int main( void )
{
	DDRF = 0x00;                    
	DDRA = 0xFF;                   
	adcInit();                        

	while (1)
	{
		//start de adc
		ADCSRA |= BIT(6);
		
		//wachten totdat de adc klaar is 
		while ( ADCSRA & BIT(6) ) ;       
		PORTA = ADCH;                   
		
		wait(500);                        
	}
}