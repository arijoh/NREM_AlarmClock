#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h> // deal with port registers
typedef uint8_t byte; // I just like byte

#define cbi(x,y) x &= ~(1<<y) //_BV(y) // equivalent to cbi(x,y)
#define sbi(x,y) x |= (1<<y) //)_BV(y) // equivalent to sbi(x,y)

void Set4Bit(byte data);
void SendByte (byte data);
void printByte (byte command);
void printChar (byte ch);
void clearLCD();
void LCDline(byte line);
void printString(char text[5]);
void printInt(int data);

#endif /* LCD_H_ */
