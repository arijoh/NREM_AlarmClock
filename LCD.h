#ifndef LCD_H_
#define LCD_H_

#define LCD_RS 0 // pin for LCD R/S (eg PB0)
#define LCD_E 1 // pin for LCD enable
#define DAT4 2 // pin for d4
#define DAT5 3 // pin for d5
#define DAT6 4 // pin for d6
#define DAT7 5 // pin for d7


#define LED 5 // Boarduino LED on PB5
#define ClearBit(x,y) x &= ~_BV(y) // equivalent to cbi(x,y)
#define SetBit(x,y) x |= _BV(y) // equivalent to sbi(x,y)


#include <avr/io.h> // deal with port registers
typedef uint8_t byte; // I just like byte


void FlashLED();
void PulseEnableLine ();
void SendNibble(byte data);
void SendByte (byte data);
void LCD_Cmd (byte cmd);
void LCD_Char (byte ch);
void LCD_Clear(); // clear the LCD display
void LCD_Cursor(byte x, byte y); // put LCD cursor on specified line
void LCD_String(const char *text); // display string on LCD

void LCD_Integer(int data); // displays the integer value of DATA at current LCD cursor position

#endif /* LCD_H_ */
