#ifndef RTC_H_
#define RTC_H_

#include "LCD.h"

#define RTC 0xD0

void readTime(byte *hours, byte *minutes, byte *seconds);
void readDate(byte *months, byte *days, byte *years);
void writeTime(int data, int reg);
void writeDays(int data, int reg);
void writeWeekday(int data);
void LCD_TwoDigits(byte data);
void dispDays();
void dispTime();
void LCD_TimeDate();
void MainLoop();
void readDay(byte *day);
void dispDay();
void WhichDay(int day);

#endif /* RTC_H_ */
