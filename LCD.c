#include "LCD.h"
#include "itoa.h"
#include "delay.h"


void Set4Bit(byte data)
{
	PORTB &= 0xC3; //Clear data lines

	if (data & (1<<4))
		sbi(PORTB,2); //2 is pin for d4
	if (data & (1<<5))
		sbi(PORTB,3);//3 is pin for d5
	if (data & (1<<6))
		sbi(PORTB,4);//4 is pin for d6
	if (data & (1<<7))
		sbi(PORTB,5);//5 is pin for d7

	sbi(PORTB,1); //enable pin set, 1 is EN pin.
	usDelay(1); //wait
	cbi(PORTB,1); //enable pin cleared
}

void SendByte (byte data)
{
	Set4Bit(data); //send first 4 bits
	Set4Bit(data<<4); // send second 4 bits
	//cbi(PORTB,5); // turn off boarduino LED
}
void LCD_byte (byte command)
{
	cbi(PORTB,0); //clear RS line to indicate a command
	SendByte(command); //send the command
}
void LCD_Char (byte ch)
{
	sbi(PORTB,0); //set RS line to indicate a data
	SendByte(ch); //send data
}

void LCD_Clear() // clear the LCD display
{
	LCD_byte(0x01);//0x01 is the clear screen command
	msDelay(3); //give some time to clear display
}
void LCD_line(byte line) // put LCD cursor on specified line
{
	byte cursor = 0x80; // line 0 begins at cursor 0x00

	if(line == 1)
		cursor = 0x40 + cursor; //0x40 is added to 0x80 for the line 1 command

	LCD_byte(cursor); //send command for row
}

void LCD_String(char text[5])
{
	int n = 0;
	char data;
	while (text[n]) //print one letter at a time
	{
		data = text[n];
		LCD_Char(data);
		n++;
	}

}

void LCD_Integer(int data) // displays the integer value of DATA at current LCD cursor position
{
	int_itoa(data, st); //convert to string st
	LCD_String(st); //send string (one char by one) to LCD
}
