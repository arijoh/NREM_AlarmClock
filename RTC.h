#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h> // deal with port registers
typedef uint8_t byte; // I just like byte


#define RTC 0xD0

void readTime(byte *hours, byte *minutes, byte *seconds);//pointers are made with data and when called the function their address is returned (&)
void readDate(byte *months, byte *days, byte *years);
void readDay(byte *day);
void writeTime(int data, int reg);
void writeDays(int data, int reg);
void writeWeekday(int data);
void LCD_TwoDigits(byte data);
void dispDays(); //displays days on LCD
void dispTime(); //displays time on LCD
void dispDay(); //displays day on LCD
void LCD_TimeDate(); //arranges time in upper row of LCD and days in lower row.
void WhichDay(int day); //used to convert int into char of day

#endif /* RTC_H_ */
