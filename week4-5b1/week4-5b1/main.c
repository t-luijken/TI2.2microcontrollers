/*
 * main.c
 *
 * Created: 3/10/2021 12:57:09 PM
 *  Author: teunl
 */ 

#include <xc.h>
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );            // library function (max 30 ms at 8MHz)
	}
}

void adcInit(){
	ADMUX = 0b01100001;
	
	ADCSRA = 0b11100110;

}


int main(void)
{
   
		//port f voor input
       DDRF = 0x00;			
	   
	   //port a b output	
       DDRA = 0xFF;				
       DDRB = 0xFF;	
	   
	   //adc aan			
       adcInit();					
       while (1)
       {
	       PORTB = ADCL;			//adc lsb op port b
	       PORTA = ADCH;			//adc msb op port a 
	       wait(10);				
       }
    
}