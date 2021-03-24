/*
 * main.c
 *
 * Created: 3/17/2021 1:27:10 PM
 *  Author: teunl
 */ 

#define F_CPU 8e6

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h> 



#define BIT(x)		( 1<<x )
#define DDR_SPI		DDRB					// spi Data direction register
#define PORT_SPI	PORTB					// spi Output register
#define SPI_SCK		1						// PB1: spi Pin System Clock
#define SPI_MOSI	2						// PB2: spi Pin MOSI
#define SPI_MISO	3						// PB3: spi Pin MISO
#define SPI_SS		0						// PB0: spi Pin Slave 

#define GOOD 2
#define SEMI_GOOD 1
#define BAD 0
//PABCDEFG
#define BAD_DIGIT  0b00110111

#define GOOD_DIGIT 0b01111110
#define SEMI_GOOD_DIGIT 0b00010011

#define true 1
#define false 0

unsigned int readVal = 0;

unsigned int placeOfNumber = 0;

unsigned int guessedNumber[4];
unsigned int generatedNumber[4];
unsigned int checkedNumbers[4];
unsigned int placed[4];



// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );            // library function (max 30 ms at 8MHz)
	}
}
void newNumber(){
	for (int i = 0; i < 4; i++)
	{
		generatedNumber[i] = rand()%10;
	}
}

int contains(int checkNumber){
	for (int i = 0; i < 4; i++)
	{
		if (checkNumber == generatedNumber[i]&& placed[i] != 1)
		{
			placed[i] = 1;
			return true;
			
		}
	}
	
	//default
	return false;
}

int check(){
	
	for (int i = 0; i < 4; i++)
	{
		placed[i] = 0;
		if (guessedNumber[i] != generatedNumber[i])
		{
			
			checkedNumbers[i] = BAD;
			
			if (contains(guessedNumber[i])){
				
				checkedNumbers[i] = SEMI_GOOD;
			}
		}
		else{
			checkedNumbers[i] = GOOD;
		}
	}
	for (int i = 0; i< 4; i++)
	{
		if (checkedNumbers[i] != GOOD)
		{
			return false;
		}
	}
	return true;
	
}

ISR( INT1_vect ) {
	
	 
	placeOfNumber++;
	if (placeOfNumber > 3)
	{
		placeOfNumber = 0;
	}
	
	
	
}

ISR( INT2_vect ) {
	
	if(check()){
		newNumber();
	}
	
}



// Initialize ADC:
void adcInit( void )
{
	ADMUX = 0b11100001;            // AREF=2,56 V, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b10000110;        // ADC-enable, no interrupt, no free running, division by 64
}
void spi_masterInit(void)
{
	DDR_SPI = 0xff;							// All pins output: MOSI, SCK, SS, SS_display as output
	DDR_SPI &= ~BIT(SPI_MISO);				// 	except: MISO input
	PORT_SPI |= BIT(SPI_SS);				// SS_ADC == 1: deselect slave
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);	// or: SPCR = 0b11010010;
	// Enable spi, MasterMode, Clock rate fck/64, bitrate=125kHz
	// Mode = 0: CPOL=0, CPPH=0;
}


// Write a byte from master to slave
void spi_write( unsigned char data )
{
	SPDR = data;							// Load byte to Data register --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); 			// Wait for transmission complete
}

// Write a byte from master to slave and read a byte from slave
// nice to have; not used here
char spi_writeRead( unsigned char data )
{
	SPDR = data;							// Load byte to Data register --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); 			// Wait for transmission complete
	data = SPDR;							// New received data (eventually, MISO) in SPDR
	return data;							// Return received byte
}

// Select device on pinnumer PORTB
void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}

// Deselect device on pinnumer PORTB
void spi_slaveDeSelect(unsigned char chipNumber)
{

	PORTB |= BIT(chipNumber);
}


// Initialize the driver chip (type MAX 7219)
void displayDriverInit()
{
	spi_slaveSelect(0);				// Select display chip (MAX7219)
	spi_write(0x09);      			// Register 09: Decode Mode
	spi_write(0x0F);				// 	-> 1's = BCD mode for all digits
	spi_slaveDeSelect(0);			// Deselect display chip

	spi_slaveSelect(0);				// Select dispaly chip
	spi_write(0x0A);      			// Register 0A: Intensity
	spi_write(0x04);    			//  -> Level 4 (in range [1..F])
	spi_slaveDeSelect(0);			// Deselect display chip

	spi_slaveSelect(0);				// Select display chip
	spi_write(0x0B);  				// Register 0B: Scan-limit
	spi_write(0x07);   				// 	-> 1 = Display digits 0..1
	spi_slaveDeSelect(0);			// Deselect display chip

	spi_slaveSelect(0);				// Select display chip
	spi_write(0x0C); 				// Register 0B: Shutdown register
	spi_write(0x01); 				// 	-> 1 = Normal operation
	spi_slaveDeSelect(0);			// Deselect display chip
}

void spi_writeWord (unsigned char adress, unsigned char data){
	
	spi_slaveSelect(0);
	spi_write(adress);
	spi_write(data);
	spi_slaveDeSelect(0);
}


void writeNumber(){
		
		for (char i = 1; i <= 4; i++)
		{
			spi_writeWord(i,guessedNumber[i-1]);
		}
		for(int i = 5; i <= 8; i++){
			switch(checkedNumbers[i-5]){
				case GOOD: spi_writeWord(i,GOOD_DIGIT); break;
				case BAD: spi_writeWord(i,BAD_DIGIT); break;
				case SEMI_GOOD: spi_writeWord(i,SEMI_GOOD_DIGIT); break;	
				}	
		}
		
	}
	
	


// Set display on ('normal operation')
void displayOn()
{
	spi_slaveSelect(0);				// Select display chip
	spi_write(0x0C); 				// Register 0B: Shutdown register
	spi_write(0x01); 				// 	-> 1 = Normal operation
	spi_slaveDeSelect(0);			// Deselect display chip
}

// Set display off ('shut down')
void displayOff()
{
	spi_slaveSelect(0);				// Select display chip
	spi_write(0x0C); 				// Register 0B: Shutdown register
	spi_write(0x00); 				// 	-> 1 = Normal operation
	spi_slaveDeSelect(0);			// Deselect display chip
}




int main(void)
{
	DDRB=0x01;	
	
	DDRD = 0x00;	
	
	DDRC = 0xFF;
	
	EICRA |= 0b00101010;       //int2 fall int 1 fall
	  
	EIMSK |= 0x06;			// Enable INT1 & INT0
	
	sei();
	
	
					  	// Set PB0 pin as output for display select
	DDRF = 0x00;
	DDRA = 0xFF;
	adcInit();
	
	
	spi_masterInit();              	// Initialize spi module
	displayDriverInit();            // Initialize display chip
	
	newNumber();
	
	
    while(1)
    {
		ADCSRA |= BIT(6);                // Start ADC
		while ( ADCSRA & BIT(6) ) ;        // Wait for completion
       readVal = ADCH/28;
	   PORTA = ADCH;
	   
	   guessedNumber[placeOfNumber] = readVal;
	
	  writeNumber();
	 
	   
	   wait(100);
    }
	return 1;
}