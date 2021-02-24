#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)            (1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );            // library function (max 30 ms at 8MHz)
	}
}

volatile int msCount = 0;

void timer2Init( void ) {
	OCR2 = 250;                // Compare value of counter 2
	TIMSK |= BIT(7);        // T2 compare match interrupt enable
	sei();                    // turn_on intr all
	TCCR2 = 0b0001101;        // Initialize T2: timer, prescaler=32, compare output disconnected,CTC,RUN
}

ISR( TIMER2_COMP_vect ) {
	msCount++;
	if (	msCount == 1)
	{
		PORTC ^= BIT(0);  
		msCount = 0;  
	}
	
}

int main( void ) {
	DDRC = 0xFF;                // set PORTC for output (toggle PC0)
	timer2Init();

	while (1) {
		// do something else
		wait(10);            // every 10 ms (busy waiting
	}
}