#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h> // deal with port registers
typedef uint8_t byte; // I just like byte

#define cbi(x,y) x &= ~(1<<y) //_BV(y) // equivalent to cbi(x,y)
#define sbi(x,y) x |= (1<<y) //)_BV(y) // equivalent to sbi(x,y)

void Set4Bit(byte data);
void SendByte (byte data);
void LCD_byte (byte cmd);
void LCD_Char (byte ch);
void LCD_Clear();
void LCD_line(byte line);
void LCD_String(char text[5]);
void LCD_Integer(int data);

#endif /* LCD_H_ */
