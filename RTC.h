#include "LCD.h"

#ifndef RTC_H_
#define RTC_H_

// DS1307 RTC ROUTINES
#define DS1307 0xD0 // I2C bus address of DS1307 RTC

//--------------------------------------------functions

void GetTime(byte *hours, byte *minutes, byte *seconds);
void GetDate(byte *months, byte *days, byte *years);
void setTime(int data, int reg);
void setDate(int data, int reg);
void setDay(int data);
void LCD_TwoDigits(byte data);
void WriteDate();
void WriteTime();
void LCD_TimeDate();
void MainLoop();

void GetDay(byte *day);
void WriteDay();
void WhichDay(int day);



#endif /* RTC_H_ */
