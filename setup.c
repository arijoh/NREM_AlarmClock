#include "LCD.h"
#include "i2C.h"
#include "checkAlarm.h"
#include "setup.h"
#include "delay.h"

void setup()
{
	setPorts(); // set port output for LCD
	LCD_Init(); // initialize HD44780 LCD controller
	setupI2C(); // set I2C clock frequency
	LCD_Clear();
	setupInterrupt();
	InitUart();
	sei();
	DDRD &= ~(1 << PD2);
	DDRD &= ~(1 << PD7);
	DDRD &= ~(1 << PD6);
	DDRD &= ~(1 << PD5);
}

void InitUart()  //set baud rate, enable tx,tx communications
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
	// PD2 (PCINT0 pin) is now an input
	PORTD |= (1 << PORTD2);    // turn On the Pull-up
	// PD2 is now an input with pull-up enabled
	EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY logic change
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);     // Turns on INT0
}

void setupI2C()
{
 TWSR = (1 << TWPS1) && (1 << TWPS0); //set prescalar to zero         //was TWST = 0
 TWBR = ((Clock_frequency/SCL_frequency)-16)/2; // set SCL frequency in TWI bit register
}

void LCD_Init()
{
	LCD_Cmd(0x33); // Controller initialized
	LCD_Cmd(0x32); // 4bit input mode
	LCD_Cmd(0x28); // 2 line, 5x7 matrix
	LCD_Cmd(0x0C); // turn cursor off (0x0E to enable)
	LCD_Cmd(0x06); // cursor direction = right
	LCD_Cmd(0x01); // start with clear display
	msDelay(3); // wait for LCD to initialize
}
