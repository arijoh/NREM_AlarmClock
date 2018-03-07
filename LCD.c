#include "LCD.h"

void setPorts()
{
	DDRB = 0x3F; // 0011.1111; set B0-B5 as outputs
	DDRC = 0x00; // 0000.0000; set PORTC as inputs
}

void msDelay(long unsigned int miS ) //delay function
{
	unsigned volatile long ulMax , ulCount ;
	ulMax = 380 * miS ;
	ulCount=0;
	while (ulCount != ulMax ) {
		ulCount++;
	}
}

void usDelay(long unsigned int uiS ) //delay function
{
	unsigned volatile long ulMax , ulCount ;
	ulMax = 19 * uiS ;
	ulCount=0;
	while (ulCount != ulMax ) {
		ulCount++;
	}
}

void FlashLED()
{
	SetBit(PORTB,LED);
	msDelay(250);
	ClearBit(PORTB,LED);
	msDelay(250);
}
// ---------------------------------------------------------------------------

void PulseEnableLine ()
{
	SetBit(PORTB,LCD_E); // take LCD enable line high
	usDelay(1); // wait 40 microseconds //changed to 100/2 microseconds
	ClearBit(PORTB,LCD_E); // take LCD enable line low
}
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
	PulseEnableLine(); // clock 4 bits into controller
}
void SendByte (byte data)
{
	SendNibble(data); // send upper 4 bits
	SendNibble(data<<4); // send lower 4 bits
	ClearBit(PORTB,5); // turn off boarduino LED
}
void LCD_Cmd (byte cmd)
{
	ClearBit(PORTB,LCD_RS); // R/S line 0 = command data
	SendByte(cmd); // send it
}
void LCD_Char (byte ch)
{
	SetBit(PORTB,LCD_RS); // R/S line 1 = character data
	SendByte(ch); // send it
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
void LCD_Clear() // clear the LCD display
{
	LCD_Cmd(0x01);//0x01 hreinsar skjá
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
	LCD_Cmd(0x80+addr+x); // update cursor with x,y position 0x80 is home curosr (I think)
}
void LCD_String(const char *text) // display string on LCD
{
	while (*text) // do until /0 character
		LCD_Char(*text++); // send char & update char pointer
}

char st[8]; // save enough space for result

void int_itoa( int n , char s[])
{
	int i ,sign;

	if((sign = n) < 0) // record s i gn
		n = -n ; // make n p o s i t i v e

	i = 0 ;

	do { // generate digits in reverse order
		s[i++] = n % 10 + '0' ; // get next digit
	} while ((n /= 10) > 0) ; // delete it
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0' ;
	int_reverse(s);
}
int int_stringlen(char s[])
{
	int i = 0;
	while (s[i] !=0 )
		i++;
	return i;
}

void int_reverse(char s[])
{
	int i , j ;
	char c ;

	for (i = 0 , j = int_stringlen(s) - 1; i<j ; i++, j--) {
		c = s[i] ;
		s[i] = s[j] ;
		s[j] = c;
	}
}

void LCD_Integer(int data)
// displays the integer value of DATA at current LCD cursor position
{
	int_itoa(data, st);
	LCD_String(st); // display in on LCD
}
