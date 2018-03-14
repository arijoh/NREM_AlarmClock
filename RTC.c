#include "RTC.h"

void GetTime(byte *hours, byte *minutes, byte *seconds)
// returns hours, minutes, and seconds in BCD format
{
	*hours = I2C_ReadRegister(DS1307,0x02);
	*minutes = I2C_ReadRegister(DS1307,0x01);
	*seconds = I2C_ReadRegister(DS1307,0x00);
}
void GetDate(byte *months, byte *days, byte *years)
// returns months, days, and years in BCD format
{
	*months = I2C_ReadRegister(DS1307,0x05);
	*days = I2C_ReadRegister(DS1307,0x04);
	*years = I2C_ReadRegister(DS1307,0x06);
}
void GetDay(byte *day)
// returns months, days, and years in BCD format
{
	*day = I2C_ReadRegister(DS1307,0x03);
}
void setTime(int data, int reg)
// simple, hard-coded way to set the date.
{
	if (reg == 1)
		I2C_WriteRegister(DS1307,0x02, data); // add 0x40 for PM
	else if (reg == 2)
		I2C_WriteRegister(DS1307,0x01, data);
	else if (reg == 3)
		I2C_WriteRegister(DS1307,0x00, data);
}
void setDate(int data, int reg)
{
	if (reg == 1)
		I2C_WriteRegister(DS1307,0x06, data);
	else if (reg == 2)
		I2C_WriteRegister(DS1307,0x05, data);
	else if (reg == 3)
		I2C_WriteRegister(DS1307,0x04, data);
}

void setDay(int data)
{
	I2C_WriteRegister(DS1307,0x03, data);
}


// ---------------------------------------------------------------------------
// APPLICATION ROUTINES

void LCD_TwoDigits(byte data)
// helper function for WriteDate()
// input is two digits in BCD format
// output is to LCD display at current cursor position
{
	byte temp = data>>4;
	LCD_Char(temp+'0');
	data &= 0x0F;
	LCD_Char(data+'0');
}
void WriteDate()
{
	byte months, days, years;
	GetDate(&months,&days,&years);
	LCD_TwoDigits(days);
	LCD_Char('/');
	LCD_TwoDigits(months);
	LCD_Char('/');
	LCD_TwoDigits(years);
}
void WriteTime()
{
	byte hours, minutes, seconds;
	GetTime(&hours,&minutes,&seconds);
	LCD_TwoDigits(hours);
	LCD_Char(':');
	LCD_TwoDigits(minutes);
	LCD_Char(':');
	LCD_TwoDigits(seconds);
}
void WriteDay()
{
	byte day;
	GetDay(&day);
	WhichDay(day);
}
void WhichDay(int day)
{
	switch(day)
	{
	case 1:
		LCD_String("MON-");
		break;
	case 2:
		LCD_String("TUE-");
		break;
	case 3:
		LCD_String("WED-");
		break;
	case 4:
		LCD_String("THU-");
		break;
	case 5:
		LCD_String("FRI-");
		break;
	case 6:
		LCD_String("SAT-");
		break;
	case 7:
		LCD_String("SUN-");
		break;
	}
}
void LCD_TimeDate()
{
	LCD_Cursor(0,0);
	WriteTime();
	LCD_Cursor(0,1);
	WriteDay();
	LCD_Cursor(4,1);
	WriteDate();
}

