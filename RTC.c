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
void setTime()
// simple, hard-coded way to set the date.
{
	I2C_WriteRegister(DS1307,0x02, 0x20); // add 0x40 for PM
	I2C_WriteRegister(DS1307,0x01, 0x30);
	I2C_WriteRegister(DS1307,0x00, 0x00);
}
void setDate(char months[4], char days[4], char years[4])
{
	I2C_WriteRegister(DS1307,0x05, 0x02);
	I2C_WriteRegister(DS1307,0x04, 0x25);
	I2C_WriteRegister(DS1307,0x06, 0x18);
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
		LCD_String("Manudagur");
		break;
	case 2:
		LCD_String("Thridjudagur");
		break;
	case 3:
		LCD_String("Midvikudagur");
		break;
	case 4:
		LCD_String("Fimtudagur");
		break;
	case 5:
		LCD_String("Fostudagur");
		break;
	case 6:
		LCD_String("Laugardagur");
		break;
	case 7:
		LCD_String("Sunnudagur");
		break;
	}
}
void LCD_TimeDate()
{
	LCD_Cursor(0,0);
	WriteTime();
	LCD_Cursor(0,1);
	//WriteDate();
	WriteDay();
}

