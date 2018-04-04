#include "RTC.h"
#include "delay.h"
#include "I2C.h"

void readTime(byte *hours, byte *minutes, byte *seconds) //pointers are made with data and when called the function their address is returned (&)
{
	*hours = readRegister(RTC,0x02);
	*minutes = readRegister(RTC,0x01);
	*seconds = readRegister(RTC,0x00);
}
void readDate(byte *months, byte *days, byte *years) //pointers are made with data and when called the function their address is returned (&)
{
	*months = readRegister(RTC,0x05);
	*days = readRegister(RTC,0x04);
	*years = readRegister(RTC,0x06);
}
void readDay(byte *day) //pointers are made with data and when called the function their address is returned (&)
{
	*day = readRegister(RTC,0x03);
}
void writeTime(int data, int reg) //reg=1 is hours, reg=2 is minutes, reg=3 is seconds and will always be set to 0
{
	if (reg == 1)
		writeRegister(RTC,0x02, data);
	else if (reg == 2)
		writeRegister(RTC,0x01, data);
	else if (reg == 3)
		writeRegister(RTC,0x00, data);
}
void writeDays(int data, int reg)//reg=1 is year, reg=2 is month, reg=3 is date
{
	if (reg == 1)
		writeRegister(RTC,0x06, data);
	else if (reg == 2)
		writeRegister(RTC,0x05, data);
	else if (reg == 3)
		writeRegister(RTC,0x04, data);
}

void writeWeekday(int data) //weekday set
{
	writeRegister(RTC,0x03, data);
}

void LCD_BCD(byte data) //prints out datain BCD format
{
	byte temp = data>>4;
	printChar(temp+'0');
	data &= 0x0F;
	printChar(data+'0');
}

void dispDays()
{
	byte months, days, years;
	readDate(&months,&days,&years);
	LCD_BCD(days);
	printChar('/');
	LCD_BCD(months);
	printChar('/');
	LCD_BCD(years);
}

void dispTime()
{
	byte hours, minutes, seconds;
	readTime(&hours,&minutes,&seconds);
	LCD_BCD(hours);
	printChar(':');
	LCD_BCD(minutes);
	printChar(':');
	LCD_BCD(seconds);
}

void dispDay()
{
	byte day;
	readDay(&day);
	WhichDay(day);
}
void WhichDay(int day)
{
	switch(day)
	{
	case 1:
		printString("MON-");
		break;
	case 2:
		printString("TUE-");
		break;
	case 3:
		printString("WED-");
		break;
	case 4:
		printString("THU-");
		break;
	case 5:
		printString("FRI-");
		break;
	case 6:
		printString("SAT-");
		break;
	case 7:
		printString("SUN-");
		break;
	}
}
void LCD_TimeDate()
{
	LCDline(0);
	dispTime();
	LCDline(1);
	dispDay();
	//LCD_line(4,1);
	dispDays();
}

