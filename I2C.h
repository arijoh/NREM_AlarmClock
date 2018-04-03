#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h> // deal with port registers
typedef uint8_t byte; // I just like byte



//#define ACK 0xC4 // return ACK to slave
//#define NACK 0x84 // don't return ACK to slave gæti valdið usla

#define SEND (1 << TWINT) | (1 << TWEN)
#define START (1<<TWINT) | (1<<TWSTA) | (1<<TWEN)
#define TW_STATUS (TWSR & 0xF8) //SKOÐA
#define STOP() TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO) // inline macro for stop condition

byte I2C_Write (byte data); // sends a data byte to slave
byte I2C_ReadNACK (); // reads a data byte from slave
void I2C_WriteRegister(byte busAddr, byte deviceRegister, byte data);
byte I2C_ReadRegister(byte busAddr, byte deviceRegister);
byte I2C_Start(byte address);

#endif /* I2C_H_ */
