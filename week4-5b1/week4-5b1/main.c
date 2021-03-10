/*
 * main.c
 *
 * Created: 3/10/2021 12:57:09 PM
 *  Author: teunl
 */ 

#include <xc.h>

void adcInit(){
	ADMUX = 0b01100001;
	
	ADCSRA = 0b11100110;

}


int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
    }
}