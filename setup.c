#include "LCD.h"
#include "i2C.h"
#include "checkAlarm.h"
#include "setup.h"
#include "delay.h"

void setup()
{
	setupI2C();
	setupLCD();
	setupButtons();
	setupUart();
	setupInterrupt();
	sei();
}

void setupButtons()
{
	DDRD &= ~(1 << PD2); //interrupt button
	DDRD &= ~(1 << PD7); //confirm button
	DDRD &= ~(1 << PD6); //plus button
	DDRD &= ~(1 << PD5); //minus button
}

void setupUart()  //set baud rate, enable tx,tx communications
{
	UBRR0H=0;
	UBRR0L=207; //we select UBRR0L=207 for 4800 BAUD.
	// enable receiver and transmitter , Rx complete interruptenable
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0) ;
	UCSR0C=(1<<USBS0)|(3<<UCSZ00); // set frame format
}

void setPorts()
{
	DDRB = 0x3F; // 0011.1111; set B0-B5 as outputs
	DDRC = 0x00; // 0000.0000; set PORTC as inputs
}

void setupInterrupt()
{
	DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
	PORTD |= (1 << PORTD2);    // turn On the Pull-up
	EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY logic change
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);     // Turns on INT0
}

void setupI2C()
{
 TWSR = 0; //Prescaler set to 1
 TWBR = ((Clock_frequency/SCL_frequency)-16)/2; //The TW Bit Register set to 72.
}

void setupLCD()
{
	setPorts(); //set port output for LCD
	printByte(0x33); //Turns on display and cursor. Entire display is in space mode because of initialization.
	printByte(0x32); // 4-bit
	printByte(0x28); // 2 line
	printByte(0x0C); // turn cursor off
	printByte(0x06); // direction of cursor
	printByte(0x01); // clear display
	msDelay(3);
	clearLCD();
}
