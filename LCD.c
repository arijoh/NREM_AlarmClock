#include "LCD.h"
#include "itoa.h"
#include "delay.h"


void SendNibble(byte data)
{
	PORTB &= 0xC3; // 1100.0011 = clear 4 data lines
	if (data & _BV(4))
		SetBit(PORTB,DAT4);
	if (data & _BV(5))
		SetBit(PORTB,DAT5);
	if (data & _BV(6))
		SetBit(PORTB,DAT6);
	if (data & _BV(7))
		SetBit(PORTB,DAT7);
	SetBit(PORTB,LCD_E); //EN set
	usDelay(1); // wait 40 microseconds
	ClearBit(PORTB,LCD_E); // EN cleared
}
void SendByte (byte data)
{
	SendNibble(data); // send upper 4 bits
	SendNibble(data<<4); // send lower 4 bits
	ClearBit(PORTB,5); // turn off boarduino LED
}
void LCD_byte (byte cmd)
{
	ClearBit(PORTB,LCD_RS); // R/S line 0 = command data
	SendByte(cmd); // send it
}
void LCD_Char (byte ch)
{
	SetBit(PORTB,LCD_RS); // R/S line 1 = character data
	SendByte(ch); // send it
}

void LCD_Clear() // clear the LCD display
{
	LCD_byte(0x01);//0x01 hreinsar skjá
	msDelay(3); // wait for LCD to process command
}
void LCD_Cursor(byte x, byte y) // put LCD cursor on specified line
{
	byte addr = 0; // line 0 begins at addr 0x00
	switch (y)
	{
	case 1:
		addr = 0x40;
		break; // line 1 begins at addr 0x40
	case 2:
		addr = 0x14;
		break;
	case 3:
		addr = 0x54;
		break;
	}
	LCD_byte(0x80+addr+x); // update cursor with x,y position 0x80 is home curosr (I think)
}

void LCD_String(const char *text) // display string on LCD
{
	while (*text) // do until /0 character
		LCD_Char(*text++); // send char & update char pointer
}


void LCD_Integer(int data)
// displays the integer value of DATA at current LCD cursor position
{
	int_itoa(data, st);
	LCD_String(st); // display in on LCD
}
