/*
 * main.c
 *
 * Created: 2/10/2021 2:49:35 PM
 *  Author: teunl
 */ 

#include <xc.h>
#include "main.h"
#include "LCD.h"

int main(void)
{
	
	init();
	
	
	
	char string[] = "Test Jtag!";
	
	display_text(&string);
	
	char string2[]=  "Jtag Test";
	
	display_text(&string2);
	
	
	
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
	return 1;
}